#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 256

int main(int argc, char *argv[])
{
   char line[MAXLEN];
   char *str[MAXLEN];
   char *token;
   char whiteSpace[] = " \t\n";
   int count;

   FILE *finp;
   FILE *foutp;

   if(argc != 3)
   {
      printf("Usage: p2.out infile outfile\n"); fflush(stdout);
      exit(1);
   }

   if((finp = fopen(argv[1], "r")) == NULL)
   {
      printf("Could not open file %s for reading.\n", argv[1]); fflush(stdout);
      exit(1);
   }

   if((foutp = fopen(argv[2], "w")) == NULL)
   {
      printf("Could not open file %s for writing.\n", argv[2]); fflush(stdout);
      exit(1);
   }

   while(fgets(line, MAXLEN, finp) != NULL)
   {
      token = strtok(line, whiteSpace);

      while(token != NULL)
      {
         for(count = 0; token != NULL; count++)
         {
            str[count] = token;
            token = strtok(NULL, whiteSpace);
         }

         count--;

         for(; count >= 0; count--)
         {
            fputs(str[count], foutp);
            fputs(" ", foutp);
         }
      }
      fputs("\n", foutp);
   }

   if(fclose(finp) == EOF)
   {
      printf("Error in closing file %s.\n", argv[1]); fflush(stdout);
   }

   if(fclose(foutp) == EOF)
   {
      printf("Error in closing file %s.\n", argv[2]); fflush(stdout);
   }

   printf("Finished.\n"); fflush(stdout);

   return 0;
}