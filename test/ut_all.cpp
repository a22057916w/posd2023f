#include <gtest/gtest.h>

#include "./ut_file.h"
#include "./ut_folder.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
