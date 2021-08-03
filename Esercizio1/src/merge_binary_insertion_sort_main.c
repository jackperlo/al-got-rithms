#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merge_binary_insertion_sort.h"

#define BUFFER_SIZE 1024 //number of bytes ridden from file

//It will contain each record ridden from the .csv file with its three fields
typedef struct _record {
  int integer_field;
  char *string_field;
  float float_field;
} Record;

//It will contain the list of records ridden from the .csv file 
typedef struct record_list{
  Record *record_item;
  struct record_list *record_next;
} RecordList;

static int precedes_record_int_field(void *r1_p, void *r2_p);
static int precedes_record_string_field(void *r1_p, void *r2_p);
static int precedes_record_float_field(void *r1_p, void *r2_p);
static void free_list(RecordList *head_list);
static void print_array(InputArray *array, char * myType);
RecordList *read_file(const char *file_name);
static InputArray* load_array(RecordList *head, int (*compare)(void*, void*));
static void order_array(RecordList *head,int (*compare)(void*, void*), char *myType, int reverse_ordering);

/*
 * It takes as input two parameters specifying the filepath of the data file and the sort type.
 * (argv[2](=reverse_ordering) == 0) ==> keeps the sort by what specified in the precedes function (example: a<b, asc)
 * (argv[2](=reverse_ordering) == 1) ==> reverses the sort by what specified in the precedes function (a<b => a>=b, desc)
 * It returns EXIT_SUCCESS(0) iff the sorts are done correctly, EXIT_FAILURE(-1) otherwise
*/
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Usage: merge_binary_sort_main <file_name> <reverse_ordering>\n");
    exit(EXIT_FAILURE);
  }

  RecordList* head = read_file(argv[1]);
  if(head == NULL)
    fprintf(stderr, "\nmerge_binary_insertion_sort_main.c: file %s is empty\n", argv[1]);
  
  order_array(head, precedes_record_string_field, "string", atoi(argv[2]));
  order_array(head, precedes_record_int_field, "int", atoi(argv[2]));
  order_array(head, precedes_record_float_field, "float", atoi(argv[2]));  

  free_list(head);

  return EXIT_SUCCESS;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the integer field of the first record is smaller than
 * the integer field of the second one (0 otherwise)
*/
static int precedes_record_int_field(void *r1_p, void *r2_p)
{
  if (r1_p == NULL)
  {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL)
  {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record *)r1_p;
  Record *rec2_p = (Record *)r2_p;
  
  if(rec1_p->integer_field < rec2_p->integer_field)
    return -1;
  else if(rec1_p->integer_field == rec2_p->integer_field)
    return 0;
  else
    return 1;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is smaller than
 * the string field of the second one (0 otherwise)
 */
static int precedes_record_string_field(void *r1_p, void *r2_p)
{
  if (r1_p == NULL)
  {
    fprintf(stderr, "precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL)
  {
    fprintf(stderr, "precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record *)r1_p;
  Record *rec2_p = (Record *)r2_p;

  if(strcmp(rec1_p->string_field, rec2_p->string_field)<0)
    return -1;
  else if(strcmp(rec1_p->string_field, rec2_p->string_field)==0)
    return 0;
  else
    return 1;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is smaller than
 * the string field of the second one (0 otherwise)
 */
static int precedes_record_float_field(void *r1_p, void *r2_p)
{
  if (r1_p == NULL)
  {
      fprintf(stderr, "precedes_float: the first parameter is a null pointer");
      exit(EXIT_FAILURE);
  }
  if (r2_p == NULL)
  {
      fprintf(stderr, "precedes_float: the second parameter is a null pointer");
      exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record *)r1_p;
  Record *rec2_p = (Record *)r2_p;

  if(rec1_p->float_field < rec2_p->float_field)
    return -1;
  else if(rec1_p->float_field == rec2_p->float_field)
    return 0;
  else
    return 1;
}

/*
 * It takes as input a pointer to a list of rercords (RecordList *) and frees it
 */
static void free_list(RecordList *head_list)
{
  RecordList *next_ptr = NULL;
  while(head_list != NULL){
    next_ptr = head_list->record_next;
    free(head_list->record_item->string_field);
    free(head_list->record_item);
    head_list = next_ptr;
  }
}

/*
 * It takes as input a pointer to an array (InputArray *) and a string  
 * myType which specifies the field on which the sorting has been done.
 * It will also be the first "coloumn" to be printed on the .csv file, 
 * followed by the other two fields.
 * Iff an error occurs, the method exits with code EXIT_FAILURE(1)
 */
static void print_array(InputArray *array, char * myType)
{
  if(input_array_size(array) == -1)
    exit(EXIT_FAILURE);
  unsigned long size = (unsigned long)input_array_size(array);

  Record *array_element;
  dprintf(1, "Printing on file the ordered array of %s records...  ",  myType);

  FILE *fpt;
  char output_file_name[100] = "ordered_array_of_";
  strcat(output_file_name, myType);
  strcat(output_file_name, ".csv");
  fpt = fopen(output_file_name, "w+");

  for (unsigned long i = 0; i < size; ++i)
  {
    array_element = (Record *)input_array_get(array, i);
    if(array_element == NULL)
      exit(EXIT_FAILURE);
    if(strcmp(myType, "string") == 0)
      fprintf(fpt, "%s,%i,%f\n", array_element->string_field, array_element->integer_field, array_element->float_field);
    else if(strcmp(myType, "int") == 0)
      fprintf(fpt, "%i,%s,%f\n", array_element->integer_field, array_element->string_field, array_element->float_field);
    else
      fprintf(fpt, "%f,%s,%i\n", array_element->float_field, array_element->string_field, array_element->integer_field);
  }

  dprintf(1, "Printed. \n\n");
  fclose(fpt);
}

/*
 * It takes as input the filepath of the input file.
 * It copies the records from the .csv file to the RecordList 
 * Iff an error occurs, the method exits with code EXIT_FAILURE(1)
 */
RecordList *read_file(const char *file_name)
{
  RecordList *record_list_previous = NULL;
  RecordList *head = NULL;
  FILE *fp;
  char buffer[BUFFER_SIZE];
  
  dprintf(1, "\nLoading data from file %s...  ", file_name);
  fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "\nmerge_binary_insertion_sort_main.c: unable to open the file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
  {
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL)
    {
      fprintf(stderr, "\nmerge_binary_insertion_sort_main.c: unable to allocate memory for the read record\n");
      exit(EXIT_FAILURE);
    }

    strtok(buffer, ",");
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *float_field_in_read_line_p = strtok(NULL, ",");

    record_p->string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
    if (record_p->string_field == NULL)
    {
      fprintf(stderr, "\nmerge_binary_insertion_sort_main.c: unable to allocate memory for the string field of the read record\n");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    record_p->float_field = strtof(float_field_in_read_line_p, NULL);

    RecordList *record_list = malloc(sizeof(RecordList));
    record_list->record_item = record_p;

    if(record_list_previous != NULL)
      record_list_previous->record_next = record_list;
    else
      head = record_list;

    record_list_previous = record_list;
  }
  record_list_previous->record_next = NULL;
  fclose(fp);
  dprintf(1, "Data loaded.\n");
  return head;
}

/*
 * It takes as input RecordList which contains the complete records (with the 3 fields)
 * of the input file and the compare relation.
 * It copies the records from the RecordList to a local InputArray, ready to be sorted 
 * Iff an error occurs, the method exits with code EXIT_FAILURE(1)
 */
InputArray *load_array(RecordList *list_head, int (*compare)(void*, void*)){
  InputArray *array = input_array_create(compare);
  if(array == NULL)
    exit(EXIT_FAILURE);

  RecordList *actual_element = list_head;
  if(actual_element==NULL){
    fprintf(stderr, "\n\nThe head of RecordList is empty\n");
    exit(EXIT_FAILURE);
  }
  while(actual_element!=NULL){
    if(input_array_add(array, actual_element->record_item) == -1)
      exit(EXIT_FAILURE);
    actual_element = actual_element->record_next;
  }
  dprintf(1, "\nData loaded from list.\n");
  return array;
}

/*
 * It takes as input a pointer to a list of rercords (RecordList *), the compare relation 
 * and a string myType which specifies the field on which the sorting will be done.
 * The reverse_ordering parameter allows to reverse the ordering specified int the precedes_function
 * permitting the asc/desc ordering.
 * It orders the array created depending on the compare relation using the merge_binary_insertion_sort
 * and it prints on file the results.
 * It calculates the time taken to order the array passed as parameter and prints it on console.
 */
void order_array(RecordList *head, int (*compare)(void*, void*), char *myType, int reverse_ordering){
  InputArray *array;
  clock_t start_t, end_t;
  
  array = load_array(head, compare);
  dprintf(1, "Ordering array by %s type....  ", myType);
  start_t = clock();
  array = merge_binary_insertion_sort(array, reverse_ordering);
  end_t = clock() - start_t;
  dprintf(1, "\nOrdered. Time taken: %fs.\n", (float)end_t/CLOCKS_PER_SEC);
  print_array(array, myType);

  if(input_array_free_memory(array) == -1)
    exit(EXIT_FAILURE);
}