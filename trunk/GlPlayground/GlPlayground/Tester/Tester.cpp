

#include <stdio.h>

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) 
{
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();

  // if (result != 0 )  getchar();
  getchar();
  return result;
}

