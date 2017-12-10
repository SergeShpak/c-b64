#include <cstdlib>
#include <stdexcept>

#include "b64_c.h"
#include "gtest/gtest.h"
#include "predicates.hpp"
#include "tests/test_b64_encode.hpp"

TestGetEncodingLen::TestCase::TestCase(
    size_t data_len, size_t expected_encoding_len) {
  this->data_len = data_len;
  this->expected_encoding_len = expected_encoding_len;
}

TestGetEncodingLen::TestCase::~TestCase() {}

void TestGetEncodingLen::SetUp() { AddNormalTestCases(); }

void TestGetEncodingLen::TearDown() { ReleaseTestCasesVec(normal_test_cases); }

void TestGetEncodingLen::AddNormalTestCases() {
  TestCase *tc;
  tc = new TestCase(6, 9);
  normal_test_cases.push_back(tc);
  tc = new TestCase(5, 9);
  normal_test_cases.push_back(tc);
  tc = new TestCase(4, 9);
  normal_test_cases.push_back(tc);
  tc = new TestCase(3, 5);
  normal_test_cases.push_back(tc);
  tc = new TestCase(2, 5);
  normal_test_cases.push_back(tc);
  tc = new TestCase(1, 5);
  normal_test_cases.push_back(tc);
  tc = new TestCase(0, 1);
  normal_test_cases.push_back(tc);
}

void TestGetEncodingLen::ReleaseTestCasesVec(
    std::vector<TestGetEncodingLen::TestCase *> test_cases) {
  std::vector<TestCase *>::iterator test_cases_iterator;
  for (test_cases_iterator = test_cases.begin();
       test_cases_iterator != test_cases.end(); test_cases_iterator++) {
    delete (*test_cases_iterator);
  }
}

TEST_F(TestGetEncodingLen, NormalTests) {
  TestCase *tc;
  int status;
  size_t actual_encoding_len;
  for (std::vector<TestCase *>::const_iterator it = normal_test_cases.begin();
       it != normal_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_encoding_len(tc->data_len, &actual_encoding_len);
    if (status) {
      FAIL();
    }
    EXPECT_EQ(tc->expected_encoding_len, actual_encoding_len);
  }
}

TEST_F(TestGetEncodingLen, NullArgsTests) {
  int status = b64_get_encoding_len(10, NULL);
  EXPECT_NE(0, status);
}

TestEncode::TestCase::TestCase(
    std::vector<unsigned char> data, std::string expected_encoding) {
  this->data_len = data.size();
  this->data = (unsigned char *)malloc(this->data_len);
  if (!(this->data)) {
    throw new std::runtime_error("Malloc failed");
  }
  memcpy(this->data, &data[0], this->data_len);
  size_t expected_encoding_len = expected_encoding.length();
  this->expected_encoding = (char *)malloc(expected_encoding_len + 1);
  if (!(this->expected_encoding)) {
    throw new std::runtime_error("Malloc failed");
  }
  memcpy(this->expected_encoding, expected_encoding.c_str(),
      expected_encoding_len);
  this->expected_encoding[expected_encoding_len] = '\0';
}

TestEncode::TestCase::~TestCase() {
  free(this->data);
  free(this->expected_encoding);
}

void TestEncode::SetUp() { AddNormalTestCases(); }

void TestEncode::TearDown() { ReleaseTestCasesVec(normal_test_cases); }

void TestEncode::AddNormalTestCases() {
  TestCase *tc;
  std::vector<unsigned char> data;
  std::string expected_encoding;
  data = {'f', 'o', 'o', 'b', 'a', 'r'};
  expected_encoding = std::string("Zm9vYmFy");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {'f', 'o', 'o', 'b', 'a'};
  expected_encoding = std::string("Zm9vYmE=");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {'f', 'o', 'o', 'b'};
  expected_encoding = std::string("Zm9vYg==");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {'f', 'o', 'o'};
  expected_encoding = std::string("Zm9v");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {'f', 'o'};
  expected_encoding = std::string("Zm8=");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {'f'};
  expected_encoding = std::string("Zg==");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  data = {};
  expected_encoding = std::string("");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
  const char *data_str =
      "Man is distinguished, not only by his reason, but by this singular"
      " passion from other animals, which is a lust of the mind, that"
      " by a perseverance of delight in the continued and indefatigable"
      " generation of knowledge, exceeds the short vehemence of any"
      " carnal pleasure.";
  data = std::vector<unsigned char>((unsigned char *)data_str,
      (unsigned char *)(data_str + strlen(data_str)));
  expected_encoding = std::string(
      "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
      "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx"
      "1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB"
      "0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGd"
      "lLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4"
      "=");
  tc = new TestCase(data, expected_encoding);
  normal_test_cases.push_back(tc);
}

void TestEncode::ReleaseTestCasesVec(
    std::vector<TestEncode::TestCase *> test_cases) {
  std::vector<TestCase *>::iterator test_cases_iterator;
  for (test_cases_iterator = test_cases.begin();
       test_cases_iterator != test_cases.end(); test_cases_iterator++) {
    delete (*test_cases_iterator);
  }
}

TEST_F(TestEncode, NormalTests) {
  TestCase *tc;
  int status;
  char *encoding_buf;
  size_t encoding_buf_len;
  size_t actual_encoding_len;
  for (std::vector<TestCase *>::const_iterator it = normal_test_cases.begin();
       it != normal_test_cases.end(); it++) {
    tc = *it;
    status = b64_get_encoding_len(tc->data_len, &encoding_buf_len);
    if (status) {
      FAIL();
    }
    encoding_buf = (char *)malloc(encoding_buf_len);
    if (!encoding_buf) {
      throw new std::runtime_error("Malloc failed");
    }
    status = b64_encode(tc->data, tc->data_len, encoding_buf);
    EXPECT_EQ(0, status);
    EXPECT_TRUE(ArraysMatch((unsigned char *)tc->expected_encoding,
        (unsigned char *)encoding_buf, encoding_buf_len));
    free(encoding_buf);
  }
}

TEST_F(TestEncode, NullArgsTests) {
  const char *data = "foobar";
  char *encoding_buf = (char *)malloc(9);
  if (!encoding_buf) {
    throw new std::runtime_error("Malloc failed");
  }
  int status = b64_encode(NULL, 6, encoding_buf);
  EXPECT_NE(0, status);
  status = b64_encode((const unsigned char *)data, 6, NULL);
  EXPECT_NE(0, status);
  status = b64_encode(NULL, 6, NULL);
  EXPECT_NE(0, status);
  free(encoding_buf);
}