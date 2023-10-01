#include "unity.h"
#include "connect4.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean-up stuff up here
}

/////////////////////////////////////////////
//
// x_in_a_row Tests
//
/////////////////////////////////////////////

void sample_pass() {
  int array[] = {3, 3, 4, 5, 7, 2 };
  TEST_ASSERT_EQUAL(3, x_in_a_row(2, 6, array, 1, 0));
}

void sample_fail() {
  int array[] = {2, 2, 3, 3, 4, 5, 7};
  TEST_ASSERT_EQUAL(3, x_in_a_row(2, 7, array, 1, 0));
}


/////////////////////////////////////////////
//
// Main
//
/////////////////////////////////////////////

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(sample_pass);
    RUN_TEST(sample_fail);
    return UNITY_END();
}
