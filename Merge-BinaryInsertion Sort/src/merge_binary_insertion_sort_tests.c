#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "merge_binary_insertion_sort.h"

#define N_ELEMENTS_TO_TEST 20000000 //number of elements which will be tested on some unit tests
#define ASCII_BIT_SIZE 128 //size of ascii table. Useful to test the complete ascii charset in the worst case and best case

/* 
* Redefine of the RUN_TEST function for custom function with int argument
*/
#define RUN_TEST_CUSTOM_INT(func, argument) run_test_custom_int(func, #func, __LINE__, argument)

/* 
* Redefine of the UnityTestFunction type for custom function with int argument
*/
typedef void (*UnityTestFunctionIntArgument)(int);

/* 
* Redefine of the RUN_TEST function for custom function with argument
*/
void run_test_custom_int(UnityTestFunctionIntArgument Func, const char* FuncName, const int FuncLineNum, int arguments){
  Unity.CurrentTestName = FuncName;
  Unity.CurrentTestLineNumber = (UNITY_LINE_TYPE)FuncLineNum;
  Unity.NumberOfTests++;
  UNITY_CLR_DETAILS();
  if (TEST_PROTECT())
  {
      setUp();
      Func(arguments);
  }
  if (TEST_PROTECT())
  {
      tearDown();
  }
  UnityConcludeTest();
}

/*
 * Test suite for InputArray data structure and algorithms
*/

// precedence relation used in tests for INTEGER
static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int *)i1_p;
  int *int2_p = (int *)i2_p;

  if(*int1_p < *int2_p)
    return -1;
  else if(*int1_p == *int2_p)
    return 0;
  else
    return 1;
}

// precedence relation used in tests for STRINGS
static int precedes_string(void *c1_p, void *c2_p) {
  char *char1_p = (char *)c1_p;
  char *char2_p = (char *)c2_p;
  if(strcmp(char1_p, char2_p)<0)
    return -1;
  else if(strcmp(char1_p, char2_p)==0)
    return 0;
  else
    return 1;
}

// precedence relation used in tests for FLOAT
static int precedes_float(void *f1_p, void *f2_p) {
  float *float1_p = (float *)f1_p;
  float *float2_p = (float *)f2_p;
  
  if(*float1_p < *float2_p)
    return -1;
  else if (*float1_p == *float2_p)
    return 0;
  else
    return 1;
}

/*TESTING EMPTY METHOD with 0 and 1 elements for INT type*/
static void test_input_array_int_is_empty_zero_el() {
  InputArray *input_array_int = input_array_create(precedes_int);
  TEST_ASSERT_TRUE(input_array_is_empty(input_array_int));
  input_array_free_memory(input_array_int);
}
static void test_input_array_int_is_empty_one_el() {
  int i = -33;
  InputArray *input_array_int = input_array_create(precedes_int);
  input_array_add(input_array_int, &i);
  TEST_ASSERT_FALSE(input_array_is_empty(input_array_int));
  input_array_free_memory(input_array_int);
}

/*TESTING EMPTY METHOD with 0 and 1 elements for STRING type*/
static void test_input_array_string_is_empty_zero_el() {
  InputArray *input_array_string = input_array_create(precedes_string);
  TEST_ASSERT_TRUE(input_array_is_empty(input_array_string));
  input_array_free_memory(input_array_string);
}
static void test_input_array_string_is_empty_one_el() {
  char i = 'z';
  InputArray *input_array_string = input_array_create(precedes_string);
  input_array_add(input_array_string, &i);
  TEST_ASSERT_FALSE(input_array_is_empty(input_array_string));
  input_array_free_memory(input_array_string);
}

/*TESTING EMPTY METHOD with 0 and 1 elements for STRING type*/
static void test_input_array_float_is_empty_zero_el() {
  InputArray *input_array_float = input_array_create(precedes_float);
  TEST_ASSERT_TRUE(input_array_is_empty(input_array_float));
  input_array_free_memory(input_array_float);
}
static void test_input_array_float_is_empty_one_el() {
  float i = 33.16f;
  InputArray *input_array_float = input_array_create(precedes_float);
  input_array_add(input_array_float, &i);
  TEST_ASSERT_FALSE(input_array_is_empty(input_array_float));
  input_array_free_memory(input_array_float);
}

/* TESTING SIZE METHOD:0,1,2 elements for INT type */
static void test_input_array_int_size_zero_el() {
  InputArray *input_array_int = input_array_create(precedes_int);
  TEST_ASSERT_EQUAL_INT(0, input_array_size(input_array_int));
  input_array_free_memory(input_array_int);
}
static void test_input_array_int_size_one_el() {
  int i1 = -33;
  InputArray *input_array_int = input_array_create(precedes_int);
  input_array_add(input_array_int, &i1);
  TEST_ASSERT_EQUAL_INT(1, input_array_size(input_array_int));
  input_array_free_memory(input_array_int);
}
static void test_input_array_int_size_two_el() {
  int i1 = -33;
  int i2 = 2;
  InputArray *input_array_int = input_array_create(precedes_int);
  input_array_add(input_array_int, &i1);
  input_array_add(input_array_int, &i2);
  TEST_ASSERT_EQUAL_INT(2, input_array_size(input_array_int));
  input_array_free_memory(input_array_int);
}

/* TESTING SIZE METHOD:0,1,2 elements for STRING type */
static void test_input_array_string_size_zero_el() {
  InputArray *input_array_string = input_array_create(precedes_string);
  TEST_ASSERT_EQUAL_INT(0, input_array_size(input_array_string));
  input_array_free_memory(input_array_string);
}
static void test_input_array_string_size_one_el() {
  int s1 = 'z';
  InputArray *input_array_string = input_array_create(precedes_string);
  input_array_add(input_array_string, &s1);
  TEST_ASSERT_EQUAL_INT(1, input_array_size(input_array_string));
  input_array_free_memory(input_array_string);
}
static void test_input_array_string_size_two_el()
{
  int s1 = 'z';
  int s2 = 'a';
  InputArray *input_array_string = input_array_create(precedes_string);
  input_array_add(input_array_string, &s1);
  input_array_add(input_array_string, &s2);
  TEST_ASSERT_EQUAL_INT(2, input_array_size(input_array_string));
  input_array_free_memory(input_array_string);
}

/* TESTING SIZE METHOD:0,1,2 elements for FLOAT type */
static void test_input_array_float_size_zero_el() {
  InputArray *input_array_float = input_array_create(precedes_float);
  TEST_ASSERT_EQUAL_INT(0, input_array_size(input_array_float));
  input_array_free_memory(input_array_float);
}
static void test_input_array_float_size_one_el() {
  float f1 = 33.16f;
  InputArray *input_array_float = input_array_create(precedes_float);
  input_array_add(input_array_float, &f1);
  TEST_ASSERT_EQUAL_INT(1, input_array_size(input_array_float));
  input_array_free_memory(input_array_float);
}
static void test_input_array_float_size_two_el() {
  float f1 = -33.16f;
  float f2 = 12.8f;
  InputArray *input_array_float = input_array_create(precedes_float);
  input_array_add(input_array_float, &f1);
  input_array_add(input_array_float, &f2);
  TEST_ASSERT_EQUAL_INT(2, input_array_size(input_array_float));
  input_array_free_memory(input_array_float);
}

/* TESTING ADD/GET METHOD:1,3 elements for INT type */
static void test_input_array_int_add_get_one_el() {
  int i1 = -12;
  InputArray *input_array_int = input_array_create(precedes_int);
  input_array_add(input_array_int, &i1);
  TEST_ASSERT_EQUAL_PTR(&i1, input_array_get(input_array_int, 0));
  input_array_free_memory(input_array_int);
}
static void test_input_array_int_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int* exp_arr[] = {&i1, &i2, &i3};

  InputArray *input_array_int = input_array_create(precedes_int);
  input_array_add(input_array_int, &i1);
  input_array_add(input_array_int, &i2);
  input_array_add(input_array_int, &i3);

  int **act_arr = malloc(3 * sizeof(int *));
  for (unsigned long i = 0; i < 3; ++i) {
    act_arr[i] = (int *)input_array_get(input_array_int, i);
  }

  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);
  input_array_free_memory(input_array_int);
}

/* TESTING ADD/GET METHOD:1,3 elements for STRING type */
static void test_input_array_string_add_get_one_el() {
  char *s1 = "z";
  InputArray *input_array_string = input_array_create(precedes_string);
  input_array_add(input_array_string, &s1);
  TEST_ASSERT_EQUAL_PTR(&s1, input_array_get(input_array_string, 0));
  input_array_free_memory(input_array_string);
}
static void test_input_array_string_add_get_three_el() {
  char *s1 = "z";
  char *s2 = "qwerty";
  char *s3 = "poiuytr";
  char** exp_arr[] = {&s1, &s2, &s3};

  InputArray *input_array_string = input_array_create(precedes_string);
  input_array_add(input_array_string, &s1);
  input_array_add(input_array_string, &s2);
  input_array_add(input_array_string, &s3);

  char **act_arr = malloc(3 * sizeof(char *));
  for (unsigned long i = 0; i < 3; ++i) {
    act_arr[i] = (char *)input_array_get(input_array_string, i);
  }

  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);
  input_array_free_memory(input_array_string);
}

/* TESTING ADD/GET METHOD:1,3 elements for FLOAT type */
static void test_input_array_float_add_get_one_el() {
  float f1 = 33.16f;
  InputArray *input_array_float = input_array_create(precedes_float);
  input_array_add(input_array_float, &f1);
  TEST_ASSERT_EQUAL_PTR(&f1, input_array_get(input_array_float, 0));
  input_array_free_memory(input_array_float);
}
static void test_input_array_float_add_get_three_el() {
  float f1 = 33.16f;
  float f2 = 8.1f;
  float f3 = 0.345f;
  float* exp_arr[] = {&f1, &f2, &f3};

  InputArray *input_array_float = input_array_create(precedes_float);
  input_array_add(input_array_float, &f1);
  input_array_add(input_array_float, &f2);
  input_array_add(input_array_float, &f3);

  float **act_arr = malloc(3*sizeof(float*));
  for (unsigned long i=0; i < 3; ++i) {
    act_arr[i] = (float *)input_array_get(input_array_float, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);
  free(act_arr);
  input_array_free_memory(input_array_float);
}

/* TESTING SORT METHOD:0,1,3,n elements worst sorting case and best case FOR INT TYPE*/
static void test_merge_binary_insertion_sort_array_int_zero_el(){
  InputArray *test_array = input_array_create(precedes_int);

  test_array = merge_binary_insertion_sort(test_array, 0);
  TEST_ASSERT_TRUE(input_array_is_empty(test_array));

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_int_one_el(){
  InputArray *test_array = input_array_create(precedes_int);
  int i1 = 10;
  input_array_add(test_array, &i1);
  int expected_array[] = {10};

  test_array = merge_binary_insertion_sort(test_array, 0);
  int *act_arr = malloc(1 * sizeof(int *));
  for (unsigned long i = 0; i < 1; ++i) {
    act_arr[i] = *(int*)input_array_get(test_array, i);
  }
 
  TEST_ASSERT_EQUAL_INT_ARRAY(expected_array, act_arr, 1);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_int_three_el(){
  InputArray *test_array = input_array_create(precedes_int);
  int i1 = 10;
  int i2 = 0;
  int i3 = 7;
  input_array_add(test_array, &i1);
  input_array_add(test_array, &i2);
  input_array_add(test_array, &i3);
  int expected_array[] = {0, 7, 10};

  test_array = merge_binary_insertion_sort(test_array, 0);
  int *act_arr = malloc(3 * sizeof(int *));
  for (unsigned long i = 0; i < 3; ++i) {
    act_arr[i] = *(int *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_INT_ARRAY(expected_array, act_arr, 3);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_int_ten_el(){
  InputArray *test_array = input_array_create(precedes_int);
  int i1 = 8;
  int i2 = 0;
  int i3 = 7;
  int i4 = 4;
  int i5 = 3;
  int i6 = 2;
  int i7 = 5;
  int i8 = 6;
  int i9 = 9;
  int i10 = 1;
  input_array_add(test_array, &i1);
  input_array_add(test_array, &i2);
  input_array_add(test_array, &i3);
  input_array_add(test_array, &i4);
  input_array_add(test_array, &i5);
  input_array_add(test_array, &i6);
  input_array_add(test_array, &i7);
  input_array_add(test_array, &i8);
  input_array_add(test_array, &i9);
  input_array_add(test_array, &i10);
  int expected_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  test_array = merge_binary_insertion_sort(test_array, 0);
  int *act_arr = malloc(10 * sizeof(int *));
  for (unsigned long i = 0; i < 10; ++i) {
    act_arr[i] = *(int *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_INT_ARRAY(expected_array, act_arr, 10);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_int_n_el(int n){
  InputArray *test_array = input_array_create(precedes_int);
  srand((unsigned int)time(NULL));
  for(int i=0; i<n; i++){
    int elements = rand() % n;
    input_array_add(test_array, &elements);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  int max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(int *)input_array_get(test_array, i) >= max)
       max = *(int *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_int_worst_case(int n){
  InputArray *test_array = input_array_create(precedes_int);

  for(int i=(n-1); i>=0; i--){
    int aus = i;  
    input_array_add(test_array, &aus);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  int max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(int *)input_array_get(test_array, i) >= max)
      max = *(int *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_int_best_case(int n){
  InputArray *test_array = input_array_create(precedes_int);

  for(int i=0; i<n; i++){
    int aus = i;  
    input_array_add(test_array, &aus);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  int max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(int *)input_array_get(test_array, i) >= max)
      max = *(int *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}

/*TESTING SORT METHOD:0,1,3,n elements, worst sorting case and best case FOR STRING TYPE*/
static void test_merge_binary_insertion_sort_array_string_one_el(){
  InputArray *test_array = input_array_create(precedes_string);
  char *s1 = "z";
  input_array_add(test_array, s1);
  char *expected_array[] = {"z"};

  test_array = merge_binary_insertion_sort(test_array, 0);

  char **act_arr = malloc(1 * sizeof(char *));
  for (unsigned int i = 0; i < 1; ++i) {
    act_arr[i] = (char *)input_array_get(test_array, i);
  }
 
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_array, act_arr, 1);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_string_three_el(){
  InputArray *test_array = input_array_create(precedes_string);
  char *s1 = "z";
  char *s2 = "qwerty";
  char *s3 = "poiuytr";
  input_array_add(test_array, s1);
  input_array_add(test_array, s2);
  input_array_add(test_array, s3);
  char *expected_array[] = {s3, s2, s1};

  test_array = merge_binary_insertion_sort(test_array, 0);
  char **act_arr = malloc(3 * sizeof(char *));
  for (unsigned long i = 0; i < 3; ++i) {
    act_arr[i] = (char *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_array, act_arr, 3);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_string_ten_el(){
  InputArray *test_array = input_array_create(precedes_string);
  char *s1 = "z";
  char *s2 = "qwerty";
  char *s3 = "soiuytr";
  char *s4 = "rlger";
  char *s5 = "pgebdv";
  char *s6 = "ofsee";
  char *s7 = "nwrweg";
  char *s8 = "mewiwe";
  char *s9 = "krrf";
  char *s10 = "keeer";
  input_array_add(test_array, s1);
  input_array_add(test_array, s2);
  input_array_add(test_array, s3);
  input_array_add(test_array, s4);
  input_array_add(test_array, s5);
  input_array_add(test_array, s6);
  input_array_add(test_array, s7);
  input_array_add(test_array, s8);
  input_array_add(test_array, s9);
  input_array_add(test_array, s10);
  char *expected_array[] = {"keeer", "krrf", "mewiwe", "nwrweg", "ofsee", "pgebdv", "qwerty", "rlger", "soiuytr", "z"};

  test_array = merge_binary_insertion_sort(test_array, 0);
  char **act_arr = malloc(10 * sizeof(char *));
  for (unsigned long i = 0; i < 10; ++i) {
    act_arr[i] = (char *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_array, act_arr, 10);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_string_n_el(int n){
  InputArray *test_array = input_array_create(precedes_string);
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?-+";
  srand((unsigned int)time(NULL));
  char *elements = (char *)malloc((unsigned long)1 * sizeof(char));
  
  for(int i=0; i<n; i++){
    int l = 1 + rand() % 5;
    elements = (char *)realloc(elements, (unsigned long)(l+1) * sizeof(char));
   
    for(int j=0; j<l;j++){
      int key = rand() % (int)(sizeof(charset) -1);
      elements[j] = charset[key];
    }
    elements[l] = '\0';
    input_array_add(test_array, elements);
  }
  free(elements);
  
  test_array = merge_binary_insertion_sort(test_array, 0);
  char *prec = (char *)malloc(7 * sizeof(char));
  strcpy(prec, "");
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(strcmp(prec, input_array_get(test_array, i)) <= 0){
      prec = (char *)malloc(sizeof(input_array_get(test_array, i)));
      strcpy(prec, input_array_get(test_array, i));
    }else{
      dprintf(1, "Before: %s, Found: %s, In position: %ld, Their strcmp is: %d\n", prec, (char *)input_array_get(test_array, i), i, strcmp(prec, input_array_get(test_array, i)));
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_string_worst_case(){
  InputArray *test_array = input_array_create(precedes_string);
  char *elements = (char *)malloc((unsigned long)2 * sizeof(char));
  
  /*this array will contain every character of the ASCII table in the worst sorting case: 127->0*/
  for(int i=127; i>=0; i--){
    elements[0] = (char)i;
    input_array_add(test_array, elements);
  }
  free(elements);

  test_array = merge_binary_insertion_sort(test_array, 0);
  
  char *prec = (char *)malloc(2* sizeof(char));
  strcpy(prec, "");
  for (unsigned long i = 0; i < (unsigned long)128; i++){
    if(strcmp(prec, input_array_get(test_array, i)) <= 0){
      prec = (char *)malloc(sizeof(input_array_get(test_array, i)));
      strcpy(prec, input_array_get(test_array, i));
    }else{
      dprintf(1, "Before: %s, Found: %s, In position: %ld, Their strcmp is: %d\n", prec, (char *)input_array_get(test_array, i), i, strcmp(prec, input_array_get(test_array, i)));
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_string_best_case(){
  InputArray *test_array = input_array_create(precedes_string);
  char *elements = (char *)malloc((unsigned long)2 * sizeof(char));
  
  /*this array will contain every character of the ASCII table in the best sorting case: 0->127*/
  for(int i=0; i<128; i++){
    elements[0] = (char)i;
    input_array_add(test_array, elements);
  }
  free(elements);
  
  test_array = merge_binary_insertion_sort(test_array, 0);
  char *prec = (char *)malloc(7 * sizeof(char));
  strcpy(prec, "");
  for (unsigned long i = 0; i < (unsigned long)128; i++){
    if(strcmp(prec, input_array_get(test_array, i)) <= 0){
      prec = (char *)malloc(sizeof(input_array_get(test_array, i)));
      strcpy(prec, input_array_get(test_array, i));
    }else{
      dprintf(1, "Before: %s, Found: %s, In position: %ld, Their strcmp is: %d\n", prec, (char *)input_array_get(test_array, i), i, strcmp(prec, input_array_get(test_array, i)));
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}


/*TESTING SORT METHOD:0,1,3,n elements, worst sorting case and best sorting case FOR FLOAT TYPE*/
static void test_merge_binary_insertion_sort_array_float_one_el(){
  InputArray *test_array = input_array_create(precedes_float);
  float f1 = 33.16f;
  input_array_add(test_array, &f1);
  float expected_array[] = {33.16f};

  test_array = merge_binary_insertion_sort(test_array, 0);

  float *act_arr = malloc(1 * sizeof(float *));
  for (unsigned int i = 0; i < 1; ++i) {
    act_arr[i] = *(float *)input_array_get(test_array, i);
  }
 
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_array, act_arr, 1);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_float_three_el(){
  InputArray *test_array = input_array_create(precedes_float);
  float f1 = -33.16f;
  float f2 = 12.8f;
  float f3 = 43.3f;
  input_array_add(test_array, &f1);
  input_array_add(test_array, &f2);
  input_array_add(test_array, &f3);
  float expected_array[] = {-33.16f, 12.8f, 43.3f};

  test_array = merge_binary_insertion_sort(test_array, 0);
  float *act_arr = malloc(3 * sizeof(float *));
  for (unsigned long i = 0; i < 3; ++i) {
    act_arr[i] = *(float *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_array, act_arr, 3);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_float_ten_el(){
  InputArray *test_array = input_array_create(precedes_float);
  float f1 = -33.16f;
  float f2 = 12.8f;
  float f3 = 43.3f;
  float f4 = -23.4f;
  float f5 = 11.456f;
  float f6 = 39.34f;
  float f7 = -0.132f;
  float f8 = -0.123f;
  float f9 = 10.01f;
  float f10 = 3678.3f;
  input_array_add(test_array, &f1);
  input_array_add(test_array, &f2);
  input_array_add(test_array, &f3);
  input_array_add(test_array, &f4);
  input_array_add(test_array, &f5);
  input_array_add(test_array, &f6);
  input_array_add(test_array, &f7);
  input_array_add(test_array, &f8);
  input_array_add(test_array, &f9);
  input_array_add(test_array, &f10);
  float expected_array[] = {-33.16f, -23.4f, -0.132f, -0.123f, 10.01f, 11.456f, 12.8f, 39.34f, 43.3f, 3678.3f};

  test_array = merge_binary_insertion_sort(test_array, 0);
  float *act_arr = malloc(10 * sizeof(float *));
  for (unsigned long i = 0; i < 10; ++i) {
    act_arr[i] = *(float *)input_array_get(test_array, i);
  }

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_array, act_arr, 10);

  input_array_free_memory(test_array);
}
static void test_merge_binary_insertion_sort_array_float_n_el(int n){
  InputArray *test_array = input_array_create(precedes_float);
  srand((unsigned int)time(NULL));

  for(int i=0; i<n; i++){  
    float elements = (float)rand() / (float)n;
    input_array_add(test_array, &elements);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  float max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(float *)input_array_get(test_array, i) >= max)
      max = *(float *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_float_worst_case(int n){
  InputArray *test_array = input_array_create(precedes_float);

  for(int i=(n-1); i>=0; i--){
    float aus = (float)i;  
    input_array_add(test_array, &aus);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  float max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(float *)input_array_get(test_array, i) >= max)
      max = *(float *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}
static void test_merge_binary_insertion_sort_array_float_best_case(int n){
  InputArray *test_array = input_array_create(precedes_float);

  for(int i=0; i<n; i++){
    float aus = (float)i;  
    input_array_add(test_array, &aus);
  }  
  test_array = merge_binary_insertion_sort(test_array, 0);
  float max = 0;
  for (unsigned long i = 0; i < (unsigned long)n; i++){
    if(*(float *)input_array_get(test_array, i) >= max)
      max = *(float *)input_array_get(test_array, i);
    else{
      input_array_free_memory(test_array);
      TEST_FAIL();
    }
  }

  input_array_free_memory(test_array);
  TEST_PASS();
}

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_input_array_int_is_empty_zero_el);
  RUN_TEST(test_input_array_int_is_empty_one_el);
  RUN_TEST(test_input_array_string_is_empty_zero_el);
  RUN_TEST(test_input_array_string_is_empty_one_el);
  RUN_TEST(test_input_array_float_is_empty_zero_el);
  RUN_TEST(test_input_array_float_is_empty_one_el);

  RUN_TEST(test_input_array_int_size_zero_el);
  RUN_TEST(test_input_array_int_size_one_el);
  RUN_TEST(test_input_array_int_size_two_el);
  RUN_TEST(test_input_array_string_size_zero_el);
  RUN_TEST(test_input_array_string_size_one_el);
  RUN_TEST(test_input_array_string_size_two_el);
  RUN_TEST(test_input_array_float_size_zero_el);
  RUN_TEST(test_input_array_float_size_one_el);
  RUN_TEST(test_input_array_float_size_two_el);

  RUN_TEST(test_input_array_int_add_get_one_el);
  RUN_TEST(test_input_array_int_add_get_three_el);
  RUN_TEST(test_input_array_string_add_get_one_el);
  RUN_TEST(test_input_array_string_add_get_three_el);
  RUN_TEST(test_input_array_float_add_get_one_el);
  RUN_TEST(test_input_array_float_add_get_three_el);
  
  RUN_TEST(test_merge_binary_insertion_sort_array_int_zero_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_int_one_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_int_three_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_int_ten_el);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_int_n_el, N_ELEMENTS_TO_TEST);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_int_worst_case, ASCII_BIT_SIZE);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_int_best_case, ASCII_BIT_SIZE);  

  RUN_TEST(test_merge_binary_insertion_sort_array_string_one_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_string_three_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_string_ten_el);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_string_n_el, N_ELEMENTS_TO_TEST);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_string_worst_case, ASCII_BIT_SIZE);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_string_best_case, ASCII_BIT_SIZE);

  RUN_TEST(test_merge_binary_insertion_sort_array_float_one_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_float_three_el);
  RUN_TEST(test_merge_binary_insertion_sort_array_float_ten_el);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_float_n_el, N_ELEMENTS_TO_TEST);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_float_worst_case, ASCII_BIT_SIZE);
  RUN_TEST_CUSTOM_INT(test_merge_binary_insertion_sort_array_float_best_case, ASCII_BIT_SIZE);
  
  return UNITY_END();
}
