#ifndef HASH_UTILITY_H
#define HASH_UTILITY_H

#define ITEM_NOT_FOUND -1
#define ERROR_CODE 0
#define SUCCESS_CODE 1
#define FREE_HASH_TABLE_ERROR_CODE -1
#define GENERIC_ERROR -1

/*
 * This struct is used to one single element of the hash table rapresented 
 * by a key and is value
 */
typedef struct _HashTableItem
{
    unsigned long key;
    long value;
}HashTableItem;

/*
 * This struct is used to store inside the hash table, the actual
 * size and the maximum size of elements that can be contained in the
 * hash table
 */
typedef struct _HashTable
{
    unsigned long m;
    unsigned long actual_size;
    HashTableItem **table;
}HashTable;

/*
 * It creates an HashTable and return a pointer to it.
 * NULL iff any errors occurred
 * It accepts as input an unsigned long rapresenting the length of the HashTable 
 * to create.
 * The input parameter must be >0 
 */
HashTable *create_hash_table(unsigned long);

/*
 * It accepts as input a pointer to an HashTable and a key. 
 * It returns the long value corresponding to the key in the HashTable. 
 * Iff there isn't an element in the key position it returns #ITEM_NOT_FOUND(-1) error
 * The parameters must be not NULL
 */
long hash_search(HashTable *T, unsigned long k);

/*
 * It accepts as input a pointer to an HashTable, a key and a value.
 * It returns a #SUCCESS_CODE(1) iff in the HashTable the function managed to insert in
 * the key position the value parameter. 
 * #ERROR_CODE(0) otherwise
 * The parameters must be not NULL
 */
int hash_insert(HashTable *T, unsigned long k, long value);

/*
 * It accepts as input two strings and it returns a unique unsigned long key using the
 * function pow. 
 * #ERROR_CODE(0) iff any errors occurred
 * The input parameters must be not NULL
 */
unsigned long strings_to_key(char *s1, char *s2);

/*
 * It accepts as input a pointer to an HashTable and it frees the memory allocated
 * to store the HashTable.
 * It returns #ERROR_CODE(0) iff any erros occurredm #SUCCESS_CODE(1) otherwise
 * The input parameter must be not NULL
 */
int free_hash_table(HashTable *T);

#endif // HASH_UTILITY_H