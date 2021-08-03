#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "edit_distance.h"

/*TESTING EMPTY STRINGS WITH REC and DYN EDIT_DISTANCE*/
static void test_edit_distance_rec_empty_strings() {
  char *s1 = "";
  char *s2 = "";
  
  TEST_ASSERT_EQUAL_INT((int)edit_distance_rec(s1, s2),0);
}
static void test_edit_distance_dyn_empty_strings() {
  char *s1 = "";
  char *s2 = "";
  
  TEST_ASSERT_EQUAL_INT((int)edit_distance_dyn(s1, s2),0); 
}

/*TESTING FIRST STRING EMPTY WITH REC and DYN EDIT_DISTANCE*/
static void test_edit_distance_rec_s1_empty_string() {
  char *s1 = "";
  char *s2 = "ciao";
  
  TEST_ASSERT_EQUAL_INT((int)edit_distance_rec(s1, s2),4);
}
static void test_edit_distance_dyn_s1_empty_string() {
  char *s1 = "";
  char *s2 = "ciao";
  
  TEST_ASSERT_EQUAL_INT((int)edit_distance_dyn(s1, s2),4); 
}

/*TESTING SECOND STRING EMPTY WITH REC and DYN EDIT_DISTANCE*/
static void test_edit_distance_rec_s2_empty_string()
{
  char *s1 = "ciao";
  char *s2 = "";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_rec(s1, s2), 4);
}
static void test_edit_distance_dyn_s2_empty_string()
{
  char *s1 = "ciao";
  char *s2 = "";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_dyn(s1, s2), 4);
}

/*TESTING TWO EQUAL STRINGS WITH REC and DYN EDIT_DISTANCE*/
static void test_edit_distance_rec_equal_strings()
{
  char *s1 = "ciao";
  char *s2 = "ciao";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_rec(s1, s2), 0);
}
static void test_edit_distance_dyn_equal_strings()
{
  char *s1 = "ciao";
  char *s2 = "ciao";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_dyn(s1, s2), 0);
}

/*TESTING GENERIC STRING WITH REC and DYN EDIT_DISTANCE*/
static void test_edit_distance_rec_generic_strings()
{
  char *s1 = "tassa";
  char *s2 = "passato";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_rec(s1, s2), 4);
}
static void test_edit_distance_dyn_generic_strings()
{
  char *s1 = "tassa";
  char *s2 = "passato";

  TEST_ASSERT_EQUAL_INT((int)edit_distance_dyn(s1, s2), 4);
}

int main()
{
  UNITY_BEGIN();

  RUN_TEST(test_edit_distance_rec_empty_strings);
  RUN_TEST(test_edit_distance_dyn_empty_strings);

  RUN_TEST(test_edit_distance_rec_s1_empty_string);
  RUN_TEST(test_edit_distance_dyn_s1_empty_string);

  RUN_TEST(test_edit_distance_rec_s2_empty_string);
  RUN_TEST(test_edit_distance_dyn_s2_empty_string);

  RUN_TEST(test_edit_distance_rec_s2_empty_string);
  RUN_TEST(test_edit_distance_dyn_s2_empty_string);

  RUN_TEST(test_edit_distance_rec_equal_strings);
  RUN_TEST(test_edit_distance_dyn_equal_strings);

  RUN_TEST(test_edit_distance_rec_generic_strings);
  RUN_TEST(test_edit_distance_dyn_generic_strings);

  return UNITY_END();
}