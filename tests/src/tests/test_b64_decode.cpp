#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "b64_decode.h"
#include "gtest/gtest.h"
#include "predicates.hpp"
#include "tests/test_b64_decode.hpp"

TestGetDecodeLen::TestCase::TestCase(
    std::string b64_str, size_t expected_decode_len)
    : TestGetDecodeLen::TestCase::TestCase(b64_str) {
  this->expected_decode_len = expected_decode_len;
}

TestGetDecodeLen::TestCase::TestCase(std::string b64_str) {
  size_t b64_str_len = b64_str.length();
  this->b64_str = (char *)malloc(b64_str_len + 1);
  if (!this->b64_str) {
    throw new std::runtime_error("Malloc failed");
  }
  memcpy(this->b64_str, b64_str.c_str(), b64_str_len);
  this->b64_str[b64_str_len] = '\0';
  this->expected_decode_len = 0;
}

TestGetDecodeLen::TestCase::TestCase::~TestCase() { free(b64_str); }

void TestGetDecodeLen::AddNormalTestCases() {
  TestCase *tc;
  tc = new TestCase("Zm9vYmFy", 6);
  normal_test_cases.push_back(tc);
  tc = new TestCase("Zm9vYmE=", 5);
  normal_test_cases.push_back(tc);
  tc = new TestCase("Zm9vYg==", 4);
  normal_test_cases.push_back(tc);
  tc = new TestCase("Zm9v", 3);
  normal_test_cases.push_back(tc);
  tc = new TestCase("Zm8=", 2);
  normal_test_cases.push_back(tc);
  tc = new TestCase("Zg==", 1);
  normal_test_cases.push_back(tc);
  tc = new TestCase("", 0);
  normal_test_cases.push_back(tc);
}

void TestGetDecodeLen::AddInvalidTestCases() {
  TestCase *tc;
  tc = new TestCase("Zm9vYmF");
  invalid_test_cases.push_back(tc);
  tc = new TestCase("Zm9vY===");
  invalid_test_cases.push_back(tc);
}

void TestGetDecodeLen::AddInvalidButPassingTestCases() {
  TestCase *tc;
  tc = new TestCase("==9vYmFy", 6);
  invalid_but_passing_test_cases.push_back(tc);
  tc = new TestCase("Zm9vYg=;", 6);
  invalid_but_passing_test_cases.push_back(tc);
}

void TestGetDecodeLen::ReleaseTestCasesVec(
    std::vector<TestGetDecodeLen::TestCase *> test_cases) {
  std::vector<TestCase *>::iterator test_cases_iterator;
  for (test_cases_iterator = test_cases.begin();
       test_cases_iterator != test_cases.end(); test_cases_iterator++) {
    delete (*test_cases_iterator);
  }
}

void TestGetDecodeLen::SetUp() {
  TestGetDecodeLen::AddNormalTestCases();
  TestGetDecodeLen::AddInvalidTestCases();
  TestGetDecodeLen::AddInvalidButPassingTestCases();
}

void TestGetDecodeLen::TearDown() {
  ReleaseTestCasesVec(normal_test_cases);
  ReleaseTestCasesVec(invalid_test_cases);
  ReleaseTestCasesVec(invalid_but_passing_test_cases);
}

TEST_F(TestGetDecodeLen, NormalTests) {
  TestCase *tc;
  int status;
  size_t actual_decode_len;
  for (std::vector<TestCase *>::const_iterator it = normal_test_cases.begin();
       it != normal_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_decode_len(tc->b64_str, &actual_decode_len);
    if (status) {
      FAIL();
    }
    EXPECT_EQ(tc->expected_decode_len, actual_decode_len);
  }
}

TEST_F(TestGetDecodeLen, NullArgsTests) {
  std::string decode_str("Zm9vYmFy");
  size_t decode_len;
  int status = b64_get_decode_len(NULL, &decode_len);
  if (0 == status) FAIL();
  status = b64_get_decode_len(decode_str.c_str(), NULL);
  if (0 == status) FAIL();
  status = b64_get_decode_len(NULL, NULL);
  if (0 == status) FAIL();
}

TEST_F(TestGetDecodeLen, InvalidTests) {
  TestCase *tc;
  int status;
  size_t actual_decode_len;
  for (std::vector<TestCase *>::const_iterator it = invalid_test_cases.begin();
       it != invalid_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_decode_len(tc->b64_str, &actual_decode_len);
    if (0 == status) {
      FAIL();
    }
  }
}

TEST_F(TestGetDecodeLen, InvalidButPassingTests) {
  TestCase *tc;
  int status;
  size_t actual_decode_len;
  for (std::vector<TestCase *>::const_iterator it =
           invalid_but_passing_test_cases.begin();
       it != invalid_but_passing_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_decode_len(tc->b64_str, &actual_decode_len);
    if (0 != status) {
      FAIL();
    }
    EXPECT_EQ(tc->expected_decode_len, actual_decode_len);
  }
}

TestDecode::TestCase::TestCase(std::string b64_str,
    const unsigned char *expected_decoded, const size_t expected_decoded_len) {
  size_t b64_str_len = b64_str.length();
  this->b64_str = (char *)malloc(b64_str_len + 1);
  if (!this->b64_str) {
    throw new std::runtime_error("Malloc failed");
  }
  memcpy(this->b64_str, b64_str.c_str(), b64_str_len);
  this->b64_str[b64_str_len] = '\0';
  this->expected_decoded = (unsigned char *)malloc(expected_decoded_len);
  if (!this->expected_decoded) {
    free(this->b64_str);
    throw new std::runtime_error("Malloc failed");
  }
  memcpy(this->expected_decoded, expected_decoded, expected_decoded_len);
  this->expected_decoded_len = expected_decoded_len;
}

TestDecode::TestCase::TestCase::~TestCase() {
  free(b64_str);
  free(expected_decoded);
}

void TestDecode::AddNormalTestCases() {
  TestCase *tc;
  std::string expected;
  expected = std::string("foobar");
  tc = new TestCase(
      "Zm9vYmFy", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("fooba");
  tc = new TestCase(
      "Zm9vYmE=", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("foob");
  tc = new TestCase(
      "Zm9vYg==", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("foo");
  tc = new TestCase(
      "Zm9v", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("fo");
  tc = new TestCase(
      "Zm8=", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("f");
  tc = new TestCase(
      "Zg==", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string("");
  tc = new TestCase(
      "", (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
  expected = std::string(
      "Man is distinguished, not only by his reason, but by this singular"
      " passion from other animals, which is a lust of the mind, that"
      " by a perseverance of delight in the continued and indefatigable"
      " generation of knowledge, exceeds the short vehemence of any"
      " carnal pleasure.");
  tc = new TestCase(
      "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
      "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx"
      "1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB"
      "0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGd"
      "lLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4"
      "=",
      (const unsigned char *)expected.c_str(), expected.length());
  normal_test_cases.push_back(tc);
}

void TestDecode::ReleaseTestCasesVec(
    std::vector<TestDecode::TestCase *> test_cases) {
  std::vector<TestCase *>::iterator test_cases_iterator;
  for (test_cases_iterator = test_cases.begin();
       test_cases_iterator != test_cases.end(); test_cases_iterator++) {
    delete (*test_cases_iterator);
  }
}

void TestDecode::SetUp() { TestDecode::AddNormalTestCases(); }

void TestDecode::TearDown() { ReleaseTestCasesVec(normal_test_cases); }

TEST_F(TestDecode, NormalTests) {
  TestCase *tc;
  int status;
  size_t decode_buf_len;
  size_t actual_decode_len;
  for (std::vector<TestCase *>::const_iterator it = normal_test_cases.begin();
       it != normal_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_decode_len(tc->b64_str, &decode_buf_len);
    if (0 != status) {
      FAIL();
    }
    unsigned char *decoded_buf = (unsigned char *)malloc(decode_buf_len);
    status = b64_decode(tc->b64_str, decoded_buf, &actual_decode_len);
    EXPECT_EQ(0, status);
    EXPECT_EQ(decode_buf_len, actual_decode_len);
    EXPECT_TRUE(ArraysMatch(tc->expected_decoded, decoded_buf, decode_buf_len));
    free(decoded_buf);
  }
}