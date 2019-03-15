#include "frequency.h"
static int Compare(const void *, const void *);

// Counting the frequencies of the characters in the frequency table
#ifndef COUNT_FREQ
int CountFrequency(char * filename, CharFreq * freq){
  // as compared to HW13 please do not exclude newline character.
  FILE * fp = fopen(filename,"r");
  if (fp == NULL){
    printf("Wrong arguments\n");
    return EXIT_FAILURE;
  }
  int i;
  while (!feof(fp)){
    i = fgetc(fp);
    if (i != EOF){
      freq[i].data = (char)i;
      freq[i].freq++;
    }
  }
  fclose(fp);
  return EXIT_SUCCESS;
}

#endif

#ifndef SORT_FREQ


// Sort function for sorting frequencies
void SortFrequency(CharFreq * freq){
  qsort(freq,NUMLETTER,sizeof(CharFreq),Compare);
}
#endif

static int Compare(const void * s1, const void * s2) {
  CharFreq * a = (CharFreq *)s1;
  CharFreq * b = (CharFreq *)s2;
  return (a -> freq - b -> freq);
}
