#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include "hash_utility.h"
#include "edit_distance.h"

static long edit_distance_dyn_function(char* s1, char* s2, HashTable *T);
static long edit_distance_rec_function(char *s1, char *s2);

long edit_distance_dyn(char* s1, char* s2){
  if(s1 == NULL || s2 == NULL){
    fprintf(stderr, "edit_distance_dyn: input strings cannot be NULL");
    return GENERIC_ERROR;
  }

  HashTable *T = create_hash_table((strlen(s1)*strlen(s2)*50)+1);
  if(T == NULL)
    exit(EXIT_FAILURE);
  
  long distance_value = edit_distance_dyn_function(s1, s2, T);

  if(free_hash_table(T) == ERROR_CODE)
    exit(EXIT_FAILURE);

  return distance_value;
}

static long edit_distance_dyn_function(char* s1, char* s2, HashTable *T){
  long search = ITEM_NOT_FOUND;
  if(strlen(s1) == 0)
    return (long)strlen(s2);
  if(strlen(s2) == 0)
    return (long)strlen(s1);

  unsigned long key = strings_to_key(s1,s2);
  if(key == ERROR_CODE)
    exit(EXIT_FAILURE);
  search = hash_search(T, key);
  if(search != ITEM_NOT_FOUND)
    return search;

  unsigned long key_opposite = strings_to_key(s2,s1);
  if(key_opposite == ERROR_CODE)
    exit(EXIT_FAILURE);
  search = hash_search(T, key_opposite);
  if(search != ITEM_NOT_FOUND)
    return search;

  long d_noop;
  long d_canc;
  long d_ins;
  if(s1[0] == s2[0])
    d_noop = edit_distance_dyn_function(s1 + 1, s2 + 1, T);
  else
    d_noop = LONG_MAX;
  
  d_canc = 1 + edit_distance_dyn_function(s1, s2+1, T);
  d_ins = 1 + edit_distance_dyn_function(s1+1, s2, T);
  
  if((d_noop < d_canc) && (d_noop < d_ins)){
    hash_insert(T, key, d_noop);
    return d_noop;
  }else if((d_canc < d_noop) && (d_canc < d_ins)){
    hash_insert(T, key, d_canc);
    return d_canc;
  }else{
    hash_insert(T, key, d_ins);
    return d_ins;
  }
}

long edit_distance_rec(char *s1, char *s2){
  if (s1 == NULL || s2 == NULL)
  {
    fprintf(stderr, "edit_distance_rec: input strings cannot be NULL");
    return GENERIC_ERROR;
  } else
    return edit_distance_rec_function(s1, s2);
}

static long edit_distance_rec_function(char* s1, char* s2){
  if(strlen(s1) == 0)
    return (long)strlen(s2);
  else if(strlen(s2) == 0)
    return (long)strlen(s1);
  
  long d_noop;
  long d_canc;
  long d_ins;

  if(s1[0] == s2[0])
    d_noop = edit_distance_rec_function(s1+1,s2+1);
  else
    d_noop = INT_MAX;
  
  d_canc = 1 + edit_distance_rec_function(s1, s2+1);

  d_ins = 1 + edit_distance_rec_function(s1+1, s2);
  
  if((d_noop < d_canc) && (d_noop < d_ins))
    return d_noop;
  else if((d_canc < d_noop) && (d_canc < d_ins))
    return d_canc;
  else
    return d_ins;
}
