#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>

#include "node.h"

//////// Global variables //////////////////////////////////////////////////////

extern struct node *first_node;

//////// Mocked functions //////////////////////////////////////////////////////


//////// Helper functions //////////////////////////////////////////////////////

void free_nodes(void)
{
    struct node *node = first_node;
    while(node) {
        struct node *next = node->next;
        free(node);
        node = next;
    }
    first_node = 0;
}

//////// Tests /////////////////////////////////////////////////////////////////

static void test__node_register__can_add_one_node(void **states)
{
    struct node *node = node_register(49, 0xFEDCBA9876543210, 0);

    assert_non_null(node);
    assert_int_equal(node->node_id, 49);
    assert_int_equal(node->firmware_hash, 0xFEDCBA9876543210);
    assert_int_equal(node->protocol_version, 0);
    assert_ptr_equal(first_node, node);

    free_nodes();
}

static void test__node_register__can_add_several_nodes(void **states)
{
    struct node *node1 = node_register(49, 0xFEDCBA9876543210, 0);
    struct node *node2 = node_register(51, 0x0123456789ABCDEF, 1);

    assert_non_null(node1);
    assert_int_equal(node1->node_id, 49);
    assert_int_equal(node1->firmware_hash, 0xFEDCBA9876543210);
    assert_int_equal(node1->protocol_version, 0);

    assert_non_null(node2);
    assert_int_equal(node2->node_id, 51);
    assert_int_equal(node2->firmware_hash, 0x0123456789ABCDEF);
    assert_int_equal(node2->protocol_version, 1);

    free_nodes();
}

static void test__node_register__updates_the_old_node_if_registering_a_duplicate(void **states)
{
    node_register(48, 0, 0);
    struct node *node_old = node_register(49, 0xFEDCBA9876543210, 1);
    node_register(51, 0, 0);
    struct node *node_new = node_register(49, 0x0123456789ABCDEF, 2);

    assert_non_null(node_old);
    assert_non_null(node_new);
    assert_ptr_equal(node_old, node_new);

    assert_int_equal(node_old->node_id, 49);
    assert_int_equal(node_old->firmware_hash, 0x0123456789ABCDEF);
    assert_int_equal(node_old->protocol_version, 2);

    assert_int_equal(node_new->node_id, 49);
    assert_int_equal(node_new->firmware_hash, 0x0123456789ABCDEF);
    assert_int_equal(node_new->protocol_version, 2);

    free_nodes();
}

static void test__node_get__can_find_the_only_node(void **states)
{
    node_register(49, 0xFEDCBA9876543210, 0);

    struct node *node = node_get(49);

    assert_non_null(node);
    assert_int_equal(node->node_id, 49);
    assert_int_equal(node->firmware_hash, 0xFEDCBA9876543210);
    assert_int_equal(node->protocol_version, 0);

    free_nodes();
}

static void test__node_get__can_find_any_node(void **states)
{
    node_register(49, 0xFEDCBA9876543210, 0);
    node_register(50, 0x0123456789ABCDEF, 1);
    node_register(51, 0x76543210FEDCBA98, 2);

    struct node *node;

    node = node_get(49);

    assert_non_null(node);
    assert_int_equal(node->node_id, 49);
    assert_int_equal(node->firmware_hash, 0xFEDCBA9876543210);
    assert_int_equal(node->protocol_version, 0);

    node = node_get(50);

    assert_non_null(node);
    assert_int_equal(node->node_id, 50);
    assert_int_equal(node->firmware_hash, 0x0123456789ABCDEF);
    assert_int_equal(node->protocol_version, 1);

    node = node_get(51);

    assert_non_null(node);
    assert_int_equal(node->node_id, 51);
    assert_int_equal(node->firmware_hash, 0x76543210FEDCBA98);
    assert_int_equal(node->protocol_version, 2);

    free_nodes();
}

static void test__node_get__returns_null_if_node_not_found(void **states)
{
    node_register(49, 0xFEDCBA9876543210, 0);
    node_register(50, 0x0123456789ABCDEF, 1);
    node_register(51, 0x76543210FEDCBA98, 2);

    struct node *node = node_get(52);

    assert_null(node);

    free_nodes();
}

static void test__node_get__returns_null_if_there_are_no_nodes(void **states)
{
    struct node *node = node_get(52);

    assert_null(node);

    free_nodes();
}

const struct CMUnitTest tests_for_node_register[] = {
    cmocka_unit_test(test__node_register__can_add_one_node),
    cmocka_unit_test(test__node_register__can_add_several_nodes),
    cmocka_unit_test(test__node_register__updates_the_old_node_if_registering_a_duplicate),
};

const struct CMUnitTest tests_for_node_get[] = {
    cmocka_unit_test(test__node_get__can_find_the_only_node),
    cmocka_unit_test(test__node_get__can_find_any_node),
    cmocka_unit_test(test__node_get__returns_null_if_node_not_found),
    cmocka_unit_test(test__node_get__returns_null_if_there_are_no_nodes),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_node_register, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_node_get, NULL, NULL);

    return fails;
}
