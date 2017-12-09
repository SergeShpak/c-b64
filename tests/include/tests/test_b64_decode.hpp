#ifndef B64_C_TESTS_TEST_B64_DECODE
#define B64_C_TESTS_TEST_B64_DECODE

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

#endif