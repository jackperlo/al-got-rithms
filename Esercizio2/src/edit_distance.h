#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H
#include "hash_utility.h"

/*
 * It accepts as input two char and it returns the "edit distance" between
 * them calculated using recursive function. 
 * #GENERIC_ERROR(-1) iff any errors occurred
 * The input parameters must be not NULL
 */
long edit_distance_rec(char *, char *);

/*
 * It accepts as input two char and a pointer to an HashTable and it returns the "edit distance" between
 * the two strings calculated using dynamic funcion. 
 * #GENERIC_ERROR(-1) iff any errors occurred
 * The input parameters must be not NULL
 */
long edit_distance_dyn(char *, char *);

#endif // EDIT_DISTANCE_H

