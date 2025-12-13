#include "unity/src/unity.h"
#include "brake_status.c"

void setUp(void) { }
void tearDown(void) { }

void test_invalid1(void)
{
    TEST_ASSERT_EQUAL_STRING("brake_invalid", brake_status(-1,1));
}

void test_invalid2(void)
{
    TEST_ASSERT_EQUAL_STRING("brake_invalid", brake_status(150,1));
}

void test_released(void)
{
    TEST_ASSERT_EQUAL_STRING("released", brake_status(0,0));
}

void test_inconclusive1(void)
{
    TEST_ASSERT_EQUAL_STRING("inconclusive", brake_status(0,1));
}

void test_inconclusive2(void)
{
    TEST_ASSERT_EQUAL_STRING("inconclusive", brake_status(5,0));
}

void test_light(void)
{
    TEST_ASSERT_EQUAL_STRING("brake_light", brake_status(15,1));
}

void test_hard(void)
{
    TEST_ASSERT_EQUAL_STRING("brake_hard", brake_status(70,1));
}

int main(){

    UNITY_BEGIN();

    RUN_TEST(test_invalid1);
    RUN_TEST(test_invalid2);
    RUN_TEST(test_released);
    RUN_TEST(test_inconclusive1);
    RUN_TEST(test_inconclusive2);
    RUN_TEST(test_light);
    RUN_TEST(test_hard);

    return UNITY_END();

}