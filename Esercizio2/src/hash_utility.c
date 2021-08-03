#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_utility.h"

static unsigned long my_pow(unsigned long x, unsigned long y);
static unsigned long hash_function(unsigned long m, unsigned long key, unsigned long i);

long hash_search(HashTable *T, unsigned long k)
{
  unsigned long i = 0;
  while (i < T->m)
  {
    unsigned long j = hash_function(T->m, k, i);
    if (T->table[j] == NULL)
      return ITEM_NOT_FOUND;
    else if (T->table[j]->key == k)
      return T->table[j]->value;
    
    i++;
  }
  return ITEM_NOT_FOUND;
}

int hash_insert(HashTable *T, unsigned long k, long value)
{
  unsigned long i = 0;
  while (i < T->m)
  {
    unsigned long j = hash_function(T->m, k, i);
    if (T->table[j] == NULL)
    {
      T->table[j] = (HashTableItem *)calloc(1, sizeof(HashTableItem));
      T->table[j]->key = k;
      T->table[j]->value = value;
      T->actual_size++;
      return SUCCESS_CODE;
    }
    i++;
  }
  return ERROR_CODE;
}

static unsigned long hash_function(unsigned long m, unsigned long key, unsigned long i)
{
  /* 
   * h(k, i) = (h1(k) + (i *h2(k)) mod m, where
   * h1(k) = k % length and
   * h2(k) = 1 + (k % length - 1)
   */
  return ((key % m) + (i * (1 + (key % (m - 1))))) % m;
}

unsigned long strings_to_key(char* s1, char* s2){
  if(s1 == NULL || s2 == NULL){
    fprintf(stderr, "strings_to_key: input parameters must be not NULL");
    return ERROR_CODE;
  }

  unsigned long k = 0;
  char *key_string = (char *)calloc((strlen(s1) + strlen(s2) + 2), sizeof(char));
  key_string = strcat(key_string, s1);
  key_string = strcat(key_string, "~"); //cannot be inserted by the user
  key_string = strcat(key_string, s2);
  
  for(long i=(long)strlen(key_string)-1; i>=0; i--)
    k += (unsigned long)( (unsigned long)((int)key_string[i]-32) * my_pow(93, (unsigned long)i) ); // -32 becuase our ascii alphabet starts form !(33) to }(125) and 93 that is the length of our alphabet 
  
  free(key_string);
  return k;
}

HashTable *create_hash_table(unsigned long m)
{
  if(m <= 0){
    fprintf(stderr, "create_hash_table: length of HashTable must be >= 0");
    return NULL;
  }
  
  HashTable *T;
  T = (HashTable *)calloc(1, sizeof(HashTable));
  if(T == NULL){
    fprintf(stderr, "create_hash_table: unable to allocate a memory for the pointer to the HashTable");
    return NULL;
  }

  T->table = (HashTableItem **)calloc(m, sizeof(HashTableItem *));
  if(T->table == NULL){
    fprintf(stderr, "create_hash_table: unable to allocate a memory for the HashTable");
    return NULL;
  }

  T->m = m;
  T->actual_size = 0;
  
  return T;
}

int free_hash_table(HashTable *T){
  if(T == NULL){
    fprintf(stderr, "free_hash_table: HashTable cannot be NULL");
    return ERROR_CODE;
  }

  for (unsigned long i = 0; i < T->m; i++)
    if(T->table[i] != NULL)
      free(T->table[i]);

  free(T->table);
  free(T);

  return SUCCESS_CODE;
}

static unsigned long my_pow(unsigned long x, unsigned long y){
  unsigned long i =0;
  unsigned long result = 1;
  for(i=0; i < y; i++){
    result = result * x;
  }
  return result;
}