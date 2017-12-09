#ifndef B64_C_TESTS_PREDICATES_HPP
#define B64_C_TESTS_PREDICATES_HPP

#include "gtest/gtest.h"

::testing::AssertionResult ArraysMatch(
    uint8_t *expected, uint8_t *actual, size_t size);

#endif