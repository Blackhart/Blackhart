// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkString_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkString_RunTests(void)
{
	RUN_TEST(BkString_CreateFormatted_test);
	RUN_TEST(BkString_Compare_test);
}

void	BkString_CreateFormatted_test(void)
{
	char const* str1 = BkString_CreateFormatted("lol");
	TEST_ASSERT_EQUAL_STRING("lol", str1);

	char const* str2 = BkString_CreateFormatted("lol: %s", "lul");
	TEST_ASSERT_EQUAL_STRING("lol: lul", str2);

	char const* str3 = BkString_CreateFormatted("", 2);
	TEST_ASSERT_EQUAL_STRING("", str3);

	char const* str4 = BkString_CreateFormatted("number %d, %i", 5, 10);
	TEST_ASSERT_EQUAL_STRING("number 5, 10", str4);
}

void	BkString_Compare_test(void)
{
	TEST_ASSERT_TRUE(BkString_Compare("lol", "lol"));
	TEST_ASSERT_FALSE(BkString_Compare("lol", "olo"));
}