
#ifndef BONUS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "cipher.h"

#define ENCODE "encode"
#define DECODE "decode"
#define FAIL 1
#define NUM_OF_ARGUMENTS 5
#define DEF_BUFFER_SIZE 2
#define COMMAND 1
#define SHIFTS 2
#define SOURCE_FILE 3
#define OUTPUT_FILE 4
#define DEF_BASE 10

int main (int argc, const char *argv[])
{
  //// check number of arguments
  if (argc != NUM_OF_ARGUMENTS)
    {
      fprintf (stderr,"Usage: cipher <encode|decode> <k> <source path file>"
              " <output path file>\n");
      return FAIL;
    }
  //// check K value
  char *t;
  long k = strtol (argv[SHIFTS], &t, DEF_BASE);
  if (strcmp (t, "") != 0)
    {
      fprintf (stderr,"The given shifts value is invalid\n");
      return FAIL;
    }
  //// check valid command
  if (strcmp (argv[COMMAND], ENCODE) != 0
      && strcmp (argv[COMMAND], DECODE) != 0)
    {
      fprintf (stderr,"The given command is invalid\n");
      return FAIL;
    }
  //// check files
  FILE *source_file = fopen (argv[SOURCE_FILE], "r");
  FILE *output_file = fopen (argv[OUTPUT_FILE], "w");
  if (source_file == NULL || output_file == NULL)
    {
      fprintf (stderr,"The given file is invalid\n");
      return FAIL;
    }
  //// run cipher program with valid arguments
  char buffer[DEF_BUFFER_SIZE] = {0};
  while (fgets (buffer, DEF_BUFFER_SIZE, source_file) != NULL)
    {
      if (strcmp (argv[COMMAND], ENCODE) == 0)
        {
          if (k < 0)
            {
              decode (buffer, (int) -k);
            }
          else
            {
              encode (buffer, (int) k);
            }
        }
      if (strcmp (argv[COMMAND], DECODE) == 0)
        {
          decode (buffer, (int) k);
        }
      fprintf (output_file, "%s", buffer);

    }
  //// close files
  fclose (source_file);
  fclose (output_file);
  return 0;
}

#endif
