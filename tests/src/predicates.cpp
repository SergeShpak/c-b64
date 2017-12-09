#include "gtest/gtest.h"

static int PrintArray(
    ::testing::AssertionResult *assert_result, uint8_t *arr, size_t arr_size);

::testing::AssertionResult ArraysMatch(
    unsigned char *expected, unsigned char *actual, size_t size) {
  for (size_t i(0); i < size; ++i) {
    if (expected[i] != actual[i]) {
      ::testing::AssertionResult failure = ::testing::AssertionFailure();
      failure << "Arrays ";
      PrintArray(&failure, actual, size);
      failure << " (actual) and ";
      PrintArray(&failure, expected, size);
      failure << " (expected) are different on position " << i;
      return failure;
    }
  }
  return ::testing::AssertionSuccess();
}

int PrintArray(::testing::AssertionResult *assert_result, unsigned char *arr,
    size_t arr_size) {
  *assert_result << "[";
  for (size_t i(0); i < arr_size - 1; i++) {
    *assert_result << (int)arr[i] << ", ";
  }
  *assert_result << (int)arr[arr_size - 1] << "]";
  return 0;
}