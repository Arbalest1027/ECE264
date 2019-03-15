#include "frequency.h"
static int Compare(const void *, const void *);

// Counting the frequencies of the characters in the frequency table
int CountFrequency(char * filename, CharFreq * freq){
  // open the file
  // get through each element of the file and get each character
  // read each character from the file
  // put the value in the freq table except for the newline character i.e '\n'
	// close the file and return success
  FILE * fp = fopen(filename,"r");
  int i;
  while (!feof(fp)){
    i = fgetc(fp);
    freq[i].freq++;
  }
  return EXIT_SUCCESS;
}


// Print statement for the print the frequency table
void PrintFreq (CharFreq *charFreqArray){
  // for each element of charFreqArray call PrintSingleCharFreq
  for (int i = 0; i < NUMLETTER;i++){
    if (charFreqArray[i].freq != 0 && charFreqArray[i].data != '\n'){
      PrintSingleCharFreq(charFreqArray[i]);
    }
  }
}



// Sort function for sorting frequencies
void SortFrequency(CharFreq * freq){
	// sort the frequencies in the ascending order
	// if frequencies are same then the character with lower ascii value will be first
  qsort(freq,256,sizeof(CharFreq),Compare);
}

// Print frequency function
//
void PrintSingleCharFreq(CharFreq charfreq){
	printf("char=%c, freq=%d\n",charfreq.data, charfreq.freq );
}

static int Compare(const void * s1, const void * s2) {
  CharFreq * a = (CharFreq *)s1;
  CharFreq * b = (CharFreq *)s2;
  return (a -> freq - b -> freq);
}
