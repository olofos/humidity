#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <sqlite3.h>

#include "db.h"

static sqlite3 *db;

static sqlite3_stmt *stmt_insert_measurement = 0;
static sqlite3_stmt *stmt_insert_debug_message = 0;
static sqlite3_stmt *stmt_insert_node = 0;
static sqlite3_stmt *stmt_select_latest_firmware_hash = 0;
static sqlite3_stmt *stmt_select_firmware_is_latest = 0;

static int db_prepare_statements(void)
{
    const char *sql_insert_measurement =
        "INSERT OR IGNORE INTO measurements (node_id, timestamp, temperature, humidity, battery1_level, battery2_level) "
        "VALUES (@node_id, @timestamp, @temperature, @humidity, @battery1_level, @battery2_level)";

    const char *sql_insert_debug_message =
        "INSERT INTO debug_messages (node_id, timestamp, message) "
        "VALUES (@node_id, @timestamp, @message)";

    const char *sql_insert_node =
        "INSERT OR REPLACE INTO nodes (id, type_id, firmware_id, name) "
        "VALUES ("
        "@node_id, "
        "@type_id, "
        "(SELECT id FROM firmware_versions WHERE hash=@firmware_hash), "
        "(SELECT name FROM nodes WHERE id=@node_id)"
        ")";

    const char *sql_select_latest_firmware_hash =
        "SELECT hash FROM firmware_versions ORDER BY timestamp DESC LIMIT 1";

    const char *sql_select_firmware_is_latest =
        "SELECT (SELECT firmware_id FROM nodes WHERE id = @node_id) = (SELECT id FROM firmware_versions ORDER BY timestamp DESC LIMIT 1)";

    if(sqlite3_prepare_v2(db, sql_insert_measurement, -1, &stmt_insert_measurement, 0) != SQLITE_OK) goto err;
    if(sqlite3_prepare_v2(db, sql_insert_debug_message, -1, &stmt_insert_debug_message, 0) != SQLITE_OK) goto err;
    if(sqlite3_prepare_v2(db, sql_insert_node, -1, &stmt_insert_node, 0) != SQLITE_OK) goto err;
    if(sqlite3_prepare_v2(db, sql_select_latest_firmware_hash, -1, &stmt_select_latest_firmware_hash, 0) != SQLITE_OK) goto err;
    if(sqlite3_prepare_v2(db, sql_select_firmware_is_latest, -1, &stmt_select_firmware_is_latest, 0) != SQLITE_OK) goto err;

    return DB_OK;

err:
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return DB_ERROR;
}

static void db_finalize_statements(void)
{
    sqlite3_finalize(stmt_insert_measurement);
    sqlite3_finalize(stmt_insert_debug_message);
    sqlite3_finalize(stmt_insert_node);
    sqlite3_finalize(stmt_select_latest_firmware_hash);
    sqlite3_finalize(stmt_select_firmware_is_latest);
}

int db_init(const char *filename)
{
    if(sqlite3_open(filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return DB_ERROR;
    }

    sqlite3_busy_timeout(db, 50);

    const char *sql_pragma_foreign_keys = "PRAGMA foreign_keys = ON";

    if(sqlite3_exec(db, sql_pragma_foreign_keys, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute pragma: %s\n", sqlite3_errmsg(db));
    }

    if(db_prepare_statements() != DB_OK) {
        db_deinit();
        return DB_ERROR;
    }

    return DB_OK;
}

void db_deinit(void)
{
    db_finalize_statements();
    sqlite3_close(db);
}

int db_register_node(uint8_t node_id, uint8_t node_type_id, uint64_t firmware_hash)
{
    int result = DB_OK;

    sqlite3_stmt *stmt = stmt_insert_node;

    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@node_id"), node_id);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@type_id"), node_type_id);
    sqlite3_bind_int64(stmt, sqlite3_bind_parameter_index(stmt, "@firmware_hash"), firmware_hash);

    if (sqlite3_step(stmt) != SQLITE_DONE ) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        result = DB_ERROR;
    }

    sqlite3_reset(stmt);

    return result;
}

int db_add_measurement(uint8_t node_id, time_t timestamp, double humidity, double temperature, double vcc, double vmid)
{
    int result = DB_OK;

    sqlite3_stmt *stmt = stmt_insert_measurement;

    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@node_id"), node_id);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@timestamp"), timestamp);
    sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@humidity"), humidity);
    sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@temperature"), temperature);
    sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@battery1_level"), vcc - vmid);
    sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@battery2_level"), vmid);

    int ret = sqlite3_step(stmt);
    if (ret != SQLITE_DONE ) {
        fprintf(stderr, "SQL error (%d): %s\n", ret, sqlite3_errmsg(db));
        if(ret == SQLITE_CONSTRAINT) {
            result = DB_NOT_REGISTERED;
        } else {
            result = DB_ERROR;
        }
    }

    sqlite3_reset(stmt);

    return result;
}

int db_add_debug_message(uint8_t node_id, time_t timestamp, char *message, int message_len)
{
    int result = DB_OK;

    sqlite3_stmt *stmt = stmt_insert_debug_message;

    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@node_id"), node_id);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@timestamp"), timestamp);
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, "@message"), message, message_len, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE ) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        result = DB_ERROR;
    }

    sqlite3_reset(stmt);

    return result;
}

int db_check_firmware_is_uptodate(uint8_t node_id)
{
    int result = 0;

    sqlite3_stmt *stmt = stmt_select_firmware_is_latest;

    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@node_id"), node_id);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        if(sqlite3_column_type(stmt,0) == SQLITE_INTEGER) {
            if(sqlite3_column_int(stmt,0) > 0) {
                result = 1;
            }
        }
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        result = -1;
    }

    sqlite3_reset(stmt);

    return result;
}

uint64_t db_get_latest_firmware_hash(void)
{
    uint64_t hash = 0;

    sqlite3_stmt *stmt = stmt_select_latest_firmware_hash;

    int rc = sqlite3_step(stmt);

    if(rc == SQLITE_ROW) {
        hash = sqlite3_column_int64(stmt, 0);
    } else if(rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_reset(stmt);

    return hash;
}

#ifdef DB_TEST_MAIN
int main(void)
{
    db_init("humidity.db");

    db_register_node(1, 1, 0x01234UL);

    db_add_measurement(1, time(0), 50.0, 22.0, 3.3, 1.6);

    db_add_debug_message(1, time(0), "This is a test", -1);

    for(int node_id = 1; node_id <= 4; node_id++) {
        printf("%d: ", node_id);

        if(db_check_firmware_is_uptodate(node_id)) {
            printf("up-to-date\n");
        } else {
            printf("update to version %016lX\n", db_get_latest_firmware_hash());
        }
    }

    db_deinit();

    return 0;
}
#endif
