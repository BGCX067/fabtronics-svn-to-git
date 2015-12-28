

#include <gtest\gtest.h>

TEST(MyTestCategoryName, MyTestName )
{
	int i=7;
	int j=10;
	int result = i * j;
	EXPECT_EQ(70,result);
	EXPECT_TRUE(result==70);

}
