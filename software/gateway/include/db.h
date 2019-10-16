#ifndef DB_H_
#define DB_H_

#define DB_OK 1
#define DB_ERROR 0

int db_init(const char *filename);
void db_deinit(void);

int db_register_node(uint8_t node_id, uint8_t node_type_id, uint64_t firmware_hash);
int db_add_measurement(uint8_t node_id, time_t timestamp, double humidity, double temperature, double vcc, double vmid);
int db_add_debug_message(uint8_t node_id, time_t timestamp, char *message, int message_len);
int db_check_firmware_is_uptodate(uint8_t node_id);
uint64_t db_get_latest_firmware_hash(void);

#endif
