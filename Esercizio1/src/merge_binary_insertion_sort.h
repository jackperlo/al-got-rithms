#ifndef MERGE_BINARY_INSERTION_SORT_H
#define MERGE_BINARY_INSERTION_SORT_H

/*
 * An array of any number of elements of any kind,
 * which needs to be ordered according to a specific precedence relation
*/
typedef struct _InputArray InputArray;

/* It creates an empty InputArray and returns the created InputArray.
 * NULL iff any errors occurred
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and return -1 iff the first element does precede
 * the second one, 0 iff the first element is equal to the second one and 1 iff
 * the first does NOT precede the second one.
 * The input parameter cannot be NULL
*/
InputArray *input_array_create(int (*precedes)(void*, void*));

/* It accepts as input a pointer to an InputArray and
 * it returns 1 iff the InputArray is empty, #ERROR_CODE(-1) iff any errors occurred, #SUCCESS_CODE(0) otherwise.
 * The input parameter cannot be NULL
*/
int input_array_is_empty(InputArray*);

/* It accepts as input a pointer to an InputArray and it
 * returns the number of elements currently stored into the array.
 * #ERROR_CODE(-1) iff any errors occurred.
 * The input parameter cannot be NULL
*/
long input_array_size(InputArray*);

/* It accepts as input a pointer to an InputArray and a pointer to an
 * element. It adds the element to the InputArray at the bottom of the array.
 * The input parameters cannot be NULL.
 * It returns #ERROR_CODE(-1) iff any errors orccurred, #SUCCESS_CODE(0) otherwise
*/
int input_array_add(InputArray*, void*);

/* It accepts as input a pointer to an InputArray and an unsigned long "i"
 * it returns the pointer to the i-th element of the InputArray
 * It returns NULL iff any errors occurred
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the InputArray
*/
void *input_array_get(InputArray*, unsigned long);

/* It accepts as input a pointer to an InputArray, an unsigned long "i" and a pointer to an
 * element. It adds the element to the InputArray at the position i-th of the array.
 * The input parameters cannot be NULL.
 * It returns #ERROR_CODE(-1) iff any errors orccurred, #SUCCESS_CODE(0) otherwise
*/
int input_array_set(InputArray *, unsigned long, void*);

/* It accepts as input a pointer to an InputArray and
 * it frees the memory allocated to store the InputArray.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the InputArray was created. The input parameters cannot be NULL.
 * It returns #ERROR_CODE(-1) iff any errors orccurred, #SUCCESS_CODE(0) otherwise
 */
int input_array_free_memory(InputArray *);

/*
 * It accepts as input a pointer to an InputArray and an integer that is the reverse parameter for reverse the 
 * InputArray sorting function.
 * It returns the InputArray sorted depending on precedes function on which 
 * the InputArray is created.
 * It's an hybrid algorithm which combines Merge Sort and BinaryInsertionSort.
 * We take advantage of the idea from which BinaryInsertion Sort can be more efficient when
 * the subsequence to order is smaller. 
 * We modified the Merge Sort in which the subsequences with "k" length or smaller and we
 * ordered them using BinaryInsertionSort and than merged between them using the classical method
 * of the Merge Sort
*/
InputArray *merge_binary_insertion_sort(InputArray*, int);

#endif // MERGE_BINARY_INSERTION_SORT_H