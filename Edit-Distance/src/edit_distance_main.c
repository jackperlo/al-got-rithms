#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "hash_utility.h"
#include "edit_distance.h"

#define BUFFER_SIZE 1024
#define PRINT_FILE_CORRECTED_NAME "corrected_file.txt" //file on which printing the result of the text corrected

/**
 * This struct is used to store inside all the
 * words ridden from the dictionary file and the 
 * file which needs to be corrected
*/
typedef struct _WordList{
    unsigned long size;
    char** words;
    int** is_uppercase;
}WordList;

WordList read_dictionary(char* file_name);
WordList read_words_from_file(char* file_name);
HashTable *load_hash_dictionary(WordList dictionary);
WordList correct_words(WordList words_to_correct, WordList dictionary, HashTable *hash_dictionary);
char *correct_a_word(char *word, WordList dictionary);
void print_corrected_words(WordList corrected_words);

/**
 * argv[1] = dictionary file
 * argv[2] = file bad written
*/
int main(int argc, char *argv[]){
  if(argc > 3)
    fprintf(stderr, "edit_distance_main:%d: Too many arguments. Usage: edit_distance_main correct_file dictionary_file.\n", __LINE__);
  else if(argc < 3)
    fprintf(stderr, "edit_distance_main:%d: Too few arguments. Usage: edit_distance_main correct_file dictionary_file.\n", __LINE__);

  WordList dictionary = read_dictionary(argv[2]);
  HashTable *dictionary_hash = load_hash_dictionary(dictionary);
  WordList words_to_correct = read_words_from_file(argv[1]);
  WordList corrected_words = correct_words(words_to_correct, dictionary, dictionary_hash);
  if(free_hash_table(dictionary_hash) == ERROR_CODE)
    exit(EXIT_FAILURE);
  print_corrected_words(corrected_words);

  exit(EXIT_SUCCESS);
}

/**
 * This method returns the WordList containing all the words of the dictionary
 * file which is passed as parameter
*/
WordList read_dictionary(char* file_name){
  WordList dictionary;
  dictionary.size = 0;

  FILE *fp;
  char buffer[BUFFER_SIZE];
  
  dprintf(1, "\nLoading dictionary from file %s...  ", file_name);
  fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "\nedit_distance_main.c:%d: unable to open the file %s\n", __LINE__, file_name);
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
  {
    if(dictionary.size==0)
      dictionary.words = (char**)calloc(1, sizeof(char*));
    else
      dictionary.words = (char**)realloc(dictionary.words, (dictionary.size+1) * sizeof(char*));

    dictionary.words[dictionary.size] = (char*)calloc(strlen(buffer), sizeof(char));
    dictionary.words[dictionary.size] = strncpy(dictionary.words[dictionary.size], buffer, (strlen(buffer)-1));
    dictionary.words[dictionary.size][(int)strlen(buffer)-1] = '\0';
    dictionary.size++;
  }
  fclose(fp);
  dprintf(1, "Read from dictionary ended\n");
  return dictionary;
}

/**
 * This method creates the hash table containing all the words stored in the WordList passed.
 * It returns an hash table pointer and accepts a wordlist as a parameter
 * es. string_to_key(ciao, ciao) = 123456
 *     hash_table[123456] = 0
 * This means that when we can compare ciao (contained in the bad written file) with itself to direct
 * access to the hash table [O(1)] and know that the word is contained in the dictionary (so it basically
 * has edit distance equal to zero), skipping the correction of it
*/
HashTable *load_hash_dictionary(WordList dictionary){  
  HashTable *T = create_hash_table(2 * dictionary.size);
  if(T == NULL)
    exit(EXIT_FAILURE);
  unsigned long k;

  for(unsigned long i = 0; i < dictionary.size; i++) {
    k = strings_to_key(dictionary.words[i], dictionary.words[i]);
    if(k == ERROR_CODE)
      exit(EXIT_FAILURE);
    hash_insert(T, k, 0);
  }

  return T;
}

/**
 * This method reads the bad written file until it ends. 
 * It accepts the name of file and returns the worlist containing all the words written inside the file.
 * WordList example:
 *      Wordlist[0] = "Ciao"
 *      Wordlist[1] = " "
 *      Wordlist[2] = "Eccetera"
 *      Wordlist[3] = "."
*/
WordList read_words_from_file(char* file_name){
  FILE *fp;
  char letter;
  char* buffer = NULL;
  int* is_upper = NULL;
  long buffer_size = 0;
  WordList words_to_correct;
  words_to_correct.size = 0;
  
  dprintf(1, "\nReading file %s...  ", file_name);
  fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "\nedit_distance_main.c:%d: unable to open the file %s\n", __LINE__, file_name);
    exit(EXIT_FAILURE);
  }
  
  do
  {
    letter = (char)fgetc(fp);
    if(((int)letter)>=33 && ((int)letter) <= 125 && !ispunct((int)letter)){ //it only accepts ASCII character between '!'(33) and '}'(125)
      if(buffer_size==0){
        if(buffer != NULL)
          free(buffer);
        if(is_upper != NULL)
          free(is_upper);
        
        buffer = (char*)calloc(1, sizeof(char));
        is_upper = (int*)calloc(1, sizeof(int));
      }else{
        buffer = (char*)realloc(buffer, (unsigned long)(buffer_size+1) * sizeof(char));
        is_upper = (int*)realloc(is_upper, (unsigned long)(buffer_size+1) * sizeof(int));
      }

      if(((int)letter)>=65 && ((int)letter)<=90){ //UPPERCASE letters management
        letter = (char)((int)letter + 32);
        buffer = strcat(buffer, &letter);
        is_upper[buffer_size] = 1;
      }else{ //lowercase letters management
        buffer = strcat(buffer, &letter);
        is_upper[buffer_size] = 0;
      }

      buffer_size++;
    }else if(letter == ' ' || letter == '\n' || ispunct((int)letter) || letter == EOF){ //This means we have ridden a complete word and we can store it
      if(buffer_size!=0){ //we have to store a word followed by a space, a line feed or a punctation symbol
        if(words_to_correct.size == 0){
          words_to_correct.words = (char **)calloc(1, sizeof(char *));
          words_to_correct.is_uppercase = (int **)calloc(1, sizeof(int *));
        }else{
          words_to_correct.words = (char **)realloc(words_to_correct.words, (words_to_correct.size + 2) * sizeof(char *));
          words_to_correct.is_uppercase =  (int **)realloc(words_to_correct.is_uppercase, (words_to_correct.size + 2) * sizeof(int *));
        }
        
        words_to_correct.words[words_to_correct.size] = (char *)calloc((strlen(buffer)+1), sizeof(char));
        words_to_correct.is_uppercase[words_to_correct.size] = (int *)calloc((size_t)(buffer_size+1), sizeof(int));

        words_to_correct.words[words_to_correct.size] = strncpy(words_to_correct.words[words_to_correct.size], buffer, (strlen(buffer)+1));
        memcpy(words_to_correct.is_uppercase[words_to_correct.size], is_upper, ((unsigned long)buffer_size*sizeof(int)));
        words_to_correct.is_uppercase[words_to_correct.size][buffer_size] = 0;
        words_to_correct.size++;
      }else{
        if(words_to_correct.size == 0){
          words_to_correct.words = (char **)calloc(1, sizeof(char *));
          words_to_correct.is_uppercase = (int **)calloc(1, sizeof(int *));
        }else{
          words_to_correct.words = (char **)realloc(words_to_correct.words, (words_to_correct.size + 1) * sizeof(char *));
          words_to_correct.is_uppercase =  (int **)realloc(words_to_correct.is_uppercase, (words_to_correct.size + 1) * sizeof(int *));
        }
      }

      words_to_correct.words[words_to_correct.size] = (char *)calloc((strlen(&letter)+1), sizeof(char));
      words_to_correct.is_uppercase[words_to_correct.size] = (int *)calloc(1, sizeof(int));

      words_to_correct.words[words_to_correct.size] = strncpy(words_to_correct.words[words_to_correct.size], &letter, (strlen(&letter)+1));
      words_to_correct.is_uppercase[words_to_correct.size][0] = 0;
      words_to_correct.size++;
      
      buffer_size = 0;
    }
  }while ( letter!= EOF);
  
  if(buffer != NULL)
    free(buffer);

  fclose(fp);
  dprintf(1, "Done.\n");
  return words_to_correct;
}

/**
 * This method iterates above all words contained in the bad written file already ridden and corrects them (if necessary).
 * It accepts:
 *  First parameter, a WordList containing all the bad written words
 *  Second parameter, a WordList containing all the words stored in the dictionary file
 *  Third parameter, an HashTable pointer to the hash table created in the load_hash_dictionary method which permits to spped up the words check
 * 
*/
WordList correct_words(WordList words_to_correct, WordList dictionary, HashTable *hash_dictionary){
  unsigned long i = 0;
  unsigned long k;
  clock_t start_t, end_t;
  WordList corrected;
  corrected.size = words_to_correct.size;
  corrected.words = (char**)calloc(corrected.size, sizeof(char*));
  corrected.is_uppercase = (int**)calloc(1, sizeof(words_to_correct.is_uppercase));

  dprintf(1,"Correcting %ld words with a Dictionary of %ld words\n", words_to_correct.size, dictionary.size);

  start_t = clock();
  for(i = 0; i < words_to_correct.size; i++){
    //we skip the word check when we are considering a space, a line feed or a punctation symbol
    if(!ispunct((int)words_to_correct.words[i][0]) && words_to_correct.words[i][0] != ' ' && words_to_correct.words[i][0] != '\n' && words_to_correct.words[i][0] != EOF){
      k = strings_to_key(words_to_correct.words[i], words_to_correct.words[i]);
      if(k == ERROR_CODE)
        exit(EXIT_FAILURE);
      
      //word bad written and not found in the dictionary hash table. This means we have to search for the lowest edit distance throughout the dictionary
      if(hash_search(hash_dictionary, k) == ITEM_NOT_FOUND){
        char *curr = correct_a_word(words_to_correct.words[i], dictionary);
        dprintf(1,"[%ld] %s\t->\t%s\n", i, words_to_correct.words[i], curr);
        corrected.words[i] = (char*)calloc((strlen(curr)+1), sizeof(char));
        corrected.words[i] = strcpy(corrected.words[i], curr);
        corrected.words[i][strlen(curr)] = '\0';

      }else{ //word good written and found in the dictionary hash table
        dprintf(1, "[%ld] %s\t->\t%s\n", i, words_to_correct.words[i], words_to_correct.words[i]);
        corrected.words[i] = (char *)calloc((strlen(words_to_correct.words[i]) + 1), sizeof(char));
        corrected.words[i] = strcpy(corrected.words[i], words_to_correct.words[i]);
        corrected.words[i][strlen(words_to_correct.words[i])] = '\0';
      }
    }else{ //space, line feed or punctation symbol
      corrected.words[i] = (char *)calloc((strlen(words_to_correct.words[i]) + 1), sizeof(char));
      corrected.words[i] = strcpy(corrected.words[i], words_to_correct.words[i]);
      corrected.words[i][strlen(words_to_correct.words[i])] = '\0';
    }

    corrected.is_uppercase[i] = (int*)calloc(1, sizeof(words_to_correct.is_uppercase[i]));
    size_t size = sizeof(words_to_correct.is_uppercase[i]);
    memcpy(corrected.is_uppercase[i], words_to_correct.is_uppercase[i], size);
  }
  end_t = clock() - start_t;

  dprintf(1, "\nTOTAL time taken: %fs.\n", (float)end_t/CLOCKS_PER_SEC);
  return corrected;
}

/**
 * This method corrects a word which is for sure bad written (= it isn't contained in the dictionary 
 * and so needs to be replaced with a lowest edit distance word).
 * It accepts the word which needs to be replaced, and the entire dictionary list.
 * This method iterates above all the dictionary words contained in the WordList searching for the smaller
 * edit distance possible. 
 * If, while iterating, it finds an edit distance equal to 1, it breaks out the cycle to optimize the execution time
 * (we can assume that edit distance equal to 1 is the best case because we've already excluded that could exits
 * an edit distance equal to 0 (=word which does not require to be replaced))
*/
char* correct_a_word(char* word, WordList dictionary){
  clock_t start_t, end_t;
  int percent = 0;
  unsigned long i;
  int find = 1;
  char* min_distance_word = word;
  long min_distance = LONG_MAX;
  dprintf(1, "\nWord to correct: %s | length:%ld\n", word, (long)strlen(word));
  start_t = clock();

  for(i=0; i<dictionary.size && find; i++){
    /**
     * es. "ciao"=> bad written word, "ao"=>word from dictionary
     *     abs("ciao" - "a") = 3
     *     "ciao"/2 = 2
     *     so it will not consider "ao" from the dictionary (and it will not calculates the edit distance)
    */
    if (abs((int)strlen(word) - (int)strlen(dictionary.words[i])) <= (strlen(word)/2)){
      long current = edit_distance_dyn(word, dictionary.words[i]);
      if(current == 1){
        min_distance = 1;
        min_distance_word = dictionary.words[i];
        find = 0;
      }else if(current < min_distance){
        min_distance = current;
        min_distance_word = dictionary.words[i];
      }
      if((int)(((double)i/(double)dictionary.size) * 100) > percent){
        percent = (int)(((double)i/(double)dictionary.size) * 100);
        dprintf(1, "\rCorrecting... %d%%\t(Word %ld of %ld)", percent, i+1, dictionary.size);
      }
    }
  }

  end_t = clock() - start_t;
  dprintf(1, "\nTime taken: %fs.\n", (float)end_t/CLOCKS_PER_SEC);
  return min_distance_word;
}

/**
 * This method prints on file the text taken in input with the bad written words 
 * now replaced with the lowest edit distance corresponding words
*/
void print_corrected_words(WordList corrected_words){
  FILE *fpt;
  fpt = fopen(PRINT_FILE_CORRECTED_NAME, "w+");
  for(unsigned long i = 0; i < corrected_words.size; i++){
    char* actual = corrected_words.words[i];
    char now;
    int j;
    for(j=0; (now = actual[j]) != '\0' && !ispunct(actual[j]) && actual[j] != ' ' && actual[j] != '\n' && actual[j] != EOF; j++){
      if(corrected_words.is_uppercase[i][j] == 1)
        actual[j] = (char)((int)actual[j] - 32);
    }
    if(actual[0] != EOF)
      fprintf(fpt, "%s", actual);
  }

  fclose(fpt);
  dprintf(1, "\nCorrected text printed on file: %s\n", PRINT_FILE_CORRECTED_NAME);
}