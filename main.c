#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 32000

void addchar(FILE *outputFile, int type, int amount)
{
  switch(type)
  {
    case 1:
      if(amount != 1)
      {
        fprintf(outputFile, "ptr+=%d;\n", amount);
      }
      else
      {
        fprintf(outputFile, "ptr++;\n");
      }
      break;
    case 2:
      if(amount != 1)
      {
        fprintf(outputFile, "ptr-=%d;\n", amount);
      }
      else
      {
        fprintf(outputFile, "ptr--;\n");
      }
      break;
    case 3:
      if(amount != 1)
      {
        fprintf(outputFile, "(*ptr)+=%d;\n", amount);
      }
      else
      {
        fprintf(outputFile, "(*ptr)++;\n");
      }
      break;
    case 4:
      if(amount != 1)
      {
        fprintf(outputFile, "(*ptr)-=%d;\n", amount);
      }
      else
      {
        fprintf(outputFile, "(*ptr)--;\n");
      }
      break;
    case 5:
      fprintf(outputFile, "while (*ptr){\n"); // doesn't need, would fix errors too anyway
      break;
    case 6:
      fprintf(outputFile, "}\n"); // doesn't need, would fix errors too anyway
      break;
    case 7:
      for (int i = 0; i < amount; i++)
      {
        fprintf(outputFile, "putchar(*ptr);\n"); // doesn't need
      }
      break;
    case 8:
      for (int i = 0; i < amount; i++)
      {
        fprintf(outputFile, "scanf(\"%%c\", (char *)ptr); \n"); // doesn't need
      }
      break;
  }
  // just ignore it if it gets here
}


int switchcase(char character)
{
  switch(character)
  {
    case '>':
      return 1;
      break;
    case '<':
      return 2;
      break;
    case '+':
      return 3;
      break;
    case '-':
      return 4;
      break;
    case '[':
      return 5;
      break;
    case ']':
      return 6;
      break;
    case '.':
      return 7;
      break;
    case ',':
      return 8;
      break;
  }
  return 0;
}

//compile brainfuck to c!?!?!?!?!??!
void compilebf(const char *source, FILE *outputFile)
{
  //quit being a lazy fuck and actually code the features that i wanted 3 months ago
  int type = 0;
  int prevtype = 0;
  int amount = 0;

  size_t length = strlen(source);
  for (int i = 0; i < length; i++)
  {
    type = switchcase(source[i]);
    if(type == prevtype)
    {
      amount++;
    }
    else
    {
      addchar(outputFile, prevtype, amount);
      amount = 1;
    }
    prevtype = type;
  }
  addchar(outputFile, prevtype, amount);
}

int main(int argc, char *argv[])
{
  if (argc != 3) 
  {
    printf("Usage: %s <file> <output file name>\n", argv[0]);
    return 1;
  }

  const char *inFile = argv[1];

  FILE *inputFile = fopen(inFile, "r");
  if (inputFile == NULL)
  {
    printf("Error opening inputFile!\n");
    return 1;
  }
  
  const char *fileName = argv[2];

  // https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
  // go to the end of the file.
  
  char *source = NULL;
  if (fseek(inputFile, 0L, SEEK_END) == 0)
  {
    long bufsize = ftell(inputFile);
    if (bufsize == -1) { /* error */ }
    
    // allocate our buffer to that size
    source = malloc(sizeof(char) * (bufsize + 1));

    // go back to the start of the file
    if (fseek(inputFile, 0L, SEEK_SET) != 0) { /* error */ }

    // read the entire file into memory
    size_t newLen = fread(source, sizeof(char), bufsize, inputFile);
    if (ferror(inputFile) != 0)
    {
      fputs("Error reading file", stderr);
    }
    else
    {
      source[newLen++] = '\0'; // just to be safe
    }
  }
  fclose(inputFile);

  FILE *outputFile = fopen(fileName, "w");
  if (outputFile == NULL)
  {
    printf("Error opening outputFile!\n");
    return 1;
  }
  
  //create
  //#include <stdio.h>
  //int main(){
  //  int arr[ARRAY_SIZE] = {0};
  //  int *ptr = arr;
  fprintf(outputFile, "#include <stdio.h>\n");
  fprintf(outputFile, "int main(){\n");
  fprintf(outputFile, "int arr[%d] = {0};\n", ARRAY_SIZE);
  fprintf(outputFile, "int *ptr = arr;\n");

  compilebf(source, outputFile);

  fprintf(outputFile, "return 0;\n}");
  fclose(outputFile);

  free(source);

  printf("compilation done!");

  return 0;
}
