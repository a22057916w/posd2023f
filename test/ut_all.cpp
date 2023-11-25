#include <gtest/gtest.h>

#include "json_test.h"
#include "ut_visitor.h"
#include "ut_iterator.h"
#include "ut_scanner.h"
#include "ut_parser.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
