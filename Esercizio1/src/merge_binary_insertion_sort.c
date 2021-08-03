#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "merge_binary_insertion_sort.h"

#define ERROR_CODE -1 
#define SUCCESS_CODE 0
#define INITIAL_CAPACITY 2 //Initial capacity for the InputArray
#define K 64 //parameter which manages to switch from merge-sort to binary-insertion-sort and vice-versa

//It represents the internal structure of this implementation of InputArrays
struct _InputArray
{
  void **array;
  unsigned long size;
  unsigned long array_capacity;
  int (*precedes)(void *, void *);
};
static void merge_sort(InputArray *input_array, unsigned long from_point, unsigned long to_point);
static void merge(InputArray *input_array, unsigned long from_point, unsigned long middle, unsigned long to_point);
static void binary_insertion_sort(InputArray *input_array, long from_point, long to_point);
static long binary(InputArray *input_array, long from_point, long to_point, long to_compare);
static int wrap_compare(void*, void*);
static int (*original_precedes)(void*, void*);
static int reverse;

InputArray *input_array_create(int (*precedes)(void *, void *))
{
  if (precedes == NULL)
  {
    fprintf(stderr, "input_array_create: precedes parameter cannot be NULL");
    return NULL;
  }
  InputArray *input_array = (InputArray *)malloc(sizeof(InputArray));
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_create: unable to allocate memory for the input array");
    return NULL;
  }
  input_array->array = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
  if (input_array->array == NULL)
  {
    fprintf(stderr, "input_array_create: unable to allocate memory for the internal array");
    return NULL;
  }
  input_array->size = 0;
  input_array->array_capacity = INITIAL_CAPACITY;
  input_array->precedes = precedes;
  return input_array;
}

int input_array_is_empty(InputArray *input_array)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_is_empty: input_array parameter cannot be NULL");
    return ERROR_CODE;
  }
  return input_array->size == 0;
}

long input_array_size(InputArray *input_array)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_size: input_array parameter cannot be NULL");
    return ERROR_CODE;
  }
  return (long)input_array->size;
}

int input_array_add(InputArray *input_array, void *element)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_add: input_array parameter cannot be NULL");
    return ERROR_CODE;
  }
  if (element == NULL)
  {
    fprintf(stderr, "input_array_add: element parameter cannot be NULL");
    return ERROR_CODE;
  }

  if (input_array->size >= input_array->array_capacity)
  {
    input_array->array_capacity = 2 * input_array->array_capacity;
    input_array->array = (void **)realloc(input_array->array, input_array->array_capacity * sizeof(void *));
    if (input_array->array == NULL)
    {
      fprintf(stderr, "input_array_add: unable to reallocate memory to host the new element");
      return ERROR_CODE;
    }
  }
  input_array->array[input_array->size] = element;
  input_array->size++;

  return 0;
}

void *input_array_get(InputArray *input_array, unsigned long i)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_get: input_array parameter cannot be NULL");
    return NULL;
  }
  if (i >= input_array->size)
  {
    fprintf(stderr, "input_array_get: Index %lu is out of the array bounds", i);
    return NULL;
  }
  return input_array->array[i];
}

int input_array_set(InputArray *input_array, unsigned long i, void *element)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_set: input_array parameter cannot be NULL");
    return ERROR_CODE;
  }
  if (i >= input_array->size)
  {
    fprintf(stderr, "input_array_set: Index %lu is out of the array bounds", i);
    return ERROR_CODE;
  }
  if (element == NULL)
  {
    fprintf(stderr, "input_array_set: element parameter cannot be NULL");
    return ERROR_CODE;
  }
  
  input_array->array[i] = element;

  return SUCCESS_CODE;
}

int input_array_free_memory(InputArray *input_array)
{
  if (input_array == NULL)
  {
    fprintf(stderr, "input_array_free_memory: input_array parameter cannot be NULL");
    return ERROR_CODE;
  }
  free(input_array->array);
  free(input_array);

  return SUCCESS_CODE;
}


InputArray *merge_binary_insertion_sort(InputArray *input_array, int reverse_ordering)
{
  original_precedes = input_array->precedes;
  reverse = reverse_ordering;
  input_array->precedes = wrap_compare;
  merge_sort(input_array, (unsigned long)0, input_array->size);
  return input_array;
}

static void merge_sort(InputArray *input_array, unsigned long from_point, unsigned long to_point)
{
  if((K < (to_point-from_point)) && (from_point<to_point-1))
  {
    unsigned long middle = (unsigned long)floor((double)((to_point-from_point)/2));
 
    merge_sort(input_array, from_point, middle+from_point);
    merge_sort(input_array, middle+from_point, to_point);

    merge(input_array, from_point, middle+from_point, to_point);    
  }else if(to_point != 0 && from_point<to_point-1){
    binary_insertion_sort(input_array, (long)from_point, (long)to_point);
  }
}

static void merge(InputArray *input_array, unsigned long from_point, unsigned long middle, unsigned long to_point) 
{
  unsigned long i = 0;
  unsigned long j = 0;

  /* left_array[0...middle-1] */
  InputArray *left_array = input_array_create(input_array->precedes);
  left_array->array = realloc(left_array->array, (middle-from_point) * sizeof(void *));
  left_array->size = middle-from_point;
  left_array->array_capacity = middle-from_point;
  memcpy(left_array->array, input_array->array+from_point, left_array->size * sizeof(void *));

  /* right_array[middle...input_array->size] */
  InputArray *right_array = input_array_create(input_array->precedes);
  right_array->array = realloc(right_array->array, (to_point - middle) * sizeof(void *));
  right_array->size = to_point - middle;
  right_array->array_capacity = to_point - middle;
  memcpy(right_array->array, input_array->array+middle, right_array->size * sizeof(void *));

  for(unsigned long z = from_point; z < to_point; z++){
    if (i >= left_array->size)
    {
      input_array_set(input_array, z, input_array_get(right_array, j)); 
      j++;
    }
    else if (j >= right_array->size)
    {
      input_array_set(input_array, z, input_array_get(left_array, i));
      i++;
    }
    else if (input_array->precedes(input_array_get(left_array, i), input_array_get(right_array, j)) == -1)
    {
      input_array_set(input_array, z, input_array_get(left_array, i));
      i++;
    }
    else
    {
      input_array_set(input_array, z, input_array_get(right_array, j));
      j++;
    }
  }

  input_array_free_memory(left_array);
  input_array_free_memory(right_array);
}

static void binary_insertion_sort(InputArray *input_array, long from_point, long to_point)
{
  long j;
  for (long i = 1; i < (long)(to_point-from_point); i++)
  {
    j = i-1;
    void *selected = input_array_get(input_array, (unsigned long)(i+from_point));
    long pos = binary(input_array, from_point, j+from_point, i+from_point);

    while((j+from_point) >= pos){
      input_array_set(input_array, (unsigned long)(j + 1 + from_point), input_array_get(input_array, (unsigned long)(j+from_point)));
      j--;
    }

    input_array_set(input_array, (unsigned long)pos, selected);
  }
}

static long binary(InputArray *input_array, long from_point, long to_point, long to_compare){
  if(to_point <= from_point){
    if (input_array->precedes(input_array_get(input_array, (unsigned long)to_compare), input_array_get(input_array, (unsigned long)from_point)) == 1)
    {
      return (from_point + 1);
    }
    else
      return from_point;
  }
 
  long middle = (from_point + to_point) / 2;

  if (input_array->precedes(input_array_get(input_array, (unsigned long)to_compare), input_array_get(input_array, (unsigned long)middle)) == 0)
    return middle + 1;

  if (input_array->precedes(input_array_get(input_array, (unsigned long)to_compare), input_array_get(input_array, (unsigned long)middle)) == 1)
    return binary(input_array, middle + 1, to_point, to_compare);

  return binary(input_array, from_point, middle - 1, to_compare);
}

/*
 * It's a wrapping function for InputArray->precedes. If reverse (gloabl parameter) is 1,
 * it reverses the precedes function
 */
static int wrap_compare(void* a, void* b){
  if(!reverse)
    return original_precedes(a,b);
  else
    return original_precedes(a,b) * -1;
}