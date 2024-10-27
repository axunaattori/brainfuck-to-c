#include "bf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      for (int i = 0; i < amount; i++)
      {
      fprintf(outputFile, "while (*ptr){\n"); // doesn't need
      }
      break;
    case 6:
      for (int i = 0; i < amount; i++)
      {
      fprintf(outputFile, "}\n"); // doesn't need
      }
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
