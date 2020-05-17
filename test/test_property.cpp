#include <Arduino.h>
#include <unity.h>

#include "property.hpp"

void test_propertyStoresValueCorrectly() {
  property<unsigned> src;
  src.set(5);
  TEST_ASSERT_EQUAL(src.get(), 5);
}

void test_propertyUpdatesRightAfterConnection() {
  property<unsigned> src;
  src.set(7);

  property<unsigned> dst;
  src.connect(&dst);

  TEST_ASSERT_EQUAL(src.get(), 7);
  TEST_ASSERT_EQUAL(dst.get(), 7);
}

void test_propertyUnidirectionalConnection() {
  property<unsigned> src;
  src.set(10);

  property<unsigned> dst;
  src.connect(&dst);

  TEST_ASSERT_EQUAL(dst.get(), 10);

  dst.set(12);

  TEST_ASSERT_EQUAL(dst.get(), 12);
  TEST_ASSERT_EQUAL(src.get(), 10);
}

void test_propertyBidirectionalConnection() {
  property<unsigned> src;
  src.set(12);

  property<unsigned> dst;
  src.connect_bi(&dst);

  TEST_ASSERT_EQUAL(dst.get(), 12);

  dst.set(14);

  TEST_ASSERT_EQUAL(src.get(), 14);
  TEST_ASSERT_EQUAL(dst.get(), 14);
}

void test_propertyOldConnectionDoesntWork() {
  property<unsigned> src;
  src.set(16);

  property<unsigned> dst;
  src.connect(&dst);

  TEST_ASSERT_EQUAL(dst.get(), 16);
  TEST_ASSERT_EQUAL(src.get(), 16);

  property<unsigned> dst2;
  src.connect(&dst2);

  src.set(18);

  TEST_ASSERT_EQUAL(dst2.get(), 18);
  TEST_ASSERT_EQUAL(src.get(), 18);  
  TEST_ASSERT_EQUAL(dst.get(), 16);
}

void setup() {
  delay(500);
}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(test_propertyStoresValueCorrectly);  
  RUN_TEST(test_propertyUpdatesRightAfterConnection);  
  RUN_TEST(test_propertyBidirectionalConnection);
  RUN_TEST(test_propertyUnidirectionalConnection);
  RUN_TEST(test_propertyOldConnectionDoesntWork);
  UNITY_END();
}
