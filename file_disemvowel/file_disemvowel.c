#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "file_disemvowel.h"

void disemvowel(FILE* input, FILE* output) {
    char *str;
    size_t size;

    size = 100;
    str = (char*) malloc (size + 1);

    while (getline(&str, &size, input) > 0){
    int i;
    int numVowel = 0;
    for (i=0; i<strlen(str); i++){
        switch(tolower(str[i])){
	    case 'a':
            case 'e':
            case 'i':
	    case 'o':
            case 'u':
                numVowel = numVowel + 1;
		break;
	}
    }
    char *newstr = (char*) calloc(strlen(str) - numVowel + 1, sizeof(char));
    int j=0;
    for (i=0; i<strlen(str); i++){
        switch(tolower(str[i])){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                break;
            default:
		newstr[j] = str[i];
		j = j + 1;
		break;
	}
    }
    fprintf(output, newstr);
    free(newstr);
    }
    free(str);
    
}

int main (int argc, char** argv){  
  FILE* in;
  FILE* out;

  if(argc == 1){
    in = stdin;
    out = stdout;
  }else if(argc == 2){
    in = fopen(argv[1], "r");
    out = stdout;
  }else{
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w+");
  }
  disemvowel(in, out);
  fclose(in);
  fclose(out);
  return 0;
}
