#ifndef B64_C_TESTS_TEST_B64_DECODE_HPP
#define B64_C_TESTS_TEST_B64_DECODE_HPP

#include "gtest/gtest.h"

class TestGetDecodeLen : public ::testing::Test {
 public:
  class TestCase {
   private:
    TestCase();

   public:
    TestCase(std::string b64_str);
    TestCase(std::string b64_str, size_t expected_decode_len);
    ~TestCase();
    char *b64_str;
    size_t expected_decode_len;
  };

  std::vector<TestCase *> normal_test_cases;
  std::vector<TestCase *> invalid_test_cases;
  std::vector<TestCase *> invalid_but_passing_test_cases;

  virtual void SetUp();
  virtual void TearDown();

 private:
  void AddNormalTestCases();
  void AddInvalidTestCases();
  void AddInvalidButPassingTestCases();
  void ReleaseTestCasesVec(std::vector<TestCase *> test_cases);
};

class TestDecode : public ::testing::Test {
 public:
  class TestCase {
   private:
    TestCase();

   public:
    TestCase(std::string b64_str, const unsigned char *expected_decoded,
        const size_t expected_decoded_len);
    ~TestCase();

    char *b64_str;
    unsigned char *expected_decoded;
    size_t expected_decoded_len;
  };

  std::vector<TestCase *> normal_test_cases;

  virtual void SetUp();
  virtual void TearDown();

 private:
  void AddNormalTestCases();
  void ReleaseTestCasesVec(std::vector<TestCase *> test_cases);
};

class TestIsValid : public ::testing::Test {
 public:
  class TestCase {
   private:
    TestCase();

   public:
    TestCase(std::string b64_str);
    ~TestCase();

    char *b64_str;
  };

  std::vector<TestCase *> valid_test_cases;
  std::vector<TestCase *> invalid_test_cases;

  virtual void SetUp();
  virtual void TearDown();

 private:
  void AddValidTestCases();
  void AddInvalidTestCases();
  void ReleaseTestCasesVec(std::vector<TestCase *> test_cases);
};

#endif