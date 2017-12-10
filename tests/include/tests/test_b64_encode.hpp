#ifndef B64_C_TESTS_TEST_B64_ENCODE_HPP
#define B64_C_TESTS_TEST_B64_ENCODE_HPP

#include <vector>

#include "gtest/gtest.h"

class TestGetEncodingLen : public ::testing::Test {
 public:
  class TestCase {
   private:
    TestCase();

   public:
    TestCase(size_t data_len, size_t expected_encoding);
    ~TestCase();
    size_t data_len;
    size_t expected_encoding_len;
  };

  std::vector<TestCase *> normal_test_cases;

  virtual void SetUp();
  virtual void TearDown();

 private:
  void AddNormalTestCases();
  void ReleaseTestCasesVec(std::vector<TestCase *> test_cases);
};

class TestEncode : public ::testing::Test {
 public:
  class TestCase {
   private:
    TestCase();

   public:
    TestCase(std::vector<unsigned char> data, std::string expected_encoding);
    ~TestCase();
    unsigned char *data;
    size_t data_len;
    char *expected_encoding;
  };

  std::vector<TestCase *> normal_test_cases;

  virtual void SetUp();
  virtual void TearDown();

 private:
  void AddNormalTestCases();
  void ReleaseTestCasesVec(std::vector<TestCase *> test_cases);
};

#endif