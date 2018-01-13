/*
*Emmanuel S Akosah  
*Long Assignment #1             
*/
#include <stdio.h>
#include <math.h>
int stats1(double *mean, double *stddvtn,char file);
int itrstats(int *o,int *e,double *mean2, double *stddvtn2,char file);

int main(void)
 {
  char file,wish;
  FILE *ifile;
  int i,e,o,x,y;
  double dvtn, sumdvtn;
  double mean, stddvtn;
  
      printf("Please select the data file you want to analyze \n\n"           /* file menu*/
             "Enter 't' for tiny_data.txt \n"
             "      's' for small_data.txt\n"
             "      'm' for medium_data.txt\n"
             "      'b' for big_data.txt\n");
   do  {                                             /*Checking for valid input*/
        scanf("%c",&file);
        if (file != 't' && file != 's' && file != 'm' && file != 'b')
        printf("Invalid Response:Try again>\n");
        }
    while (file != 't' && file != 's' && file != 'm' && file != 'b');
        
  switch (file)                                      /* file selection*/
  {  case 't':
           ifile = fopen("tiny_data.txt","r");
     case 's':
           ifile = fopen("small_data.txt","r");
     case 'm':
           ifile = fopen("medium_data.txt","r");
     case 'b':
          ifile = fopen("big_data.txt","r");
  }
  if (ifile != NULL)
    printf("File has been succesfully opened :) \n");
  if (ifile == NULL)
    {printf("Failed to open file :( \n");
     return (1);
    }
   
   
     stats1(&mean,&stddvtn,file);             /*function "stats1" calcs stats for all data values*/
      
    o = 1; 
    e = 1;    
    while( o != 0)
   {
      itrstats(&o,&e,&mean,&stddvtn,file);         /*function "itrstats" calcs stats excluding outliers*/
      e++; 
   
          
  /*if (o == 0)                                       interactive repetiive feature
     { printf("Do you wish to continue?\n");          sorry, couldn't finish it(time up), have to pass all counters into
       printf("Enter 'y' for YES or 'n' for NO:>\n");   function again to change them 
       scanf(" %c",&wish);
       
        if (wish == 'n')
            printf("DONE:BYEEE\n");
        if (wish == 'y')
           o = 1;
           e = 1;
           x = 0;
           y = 0;
           i = 0;
                      
   else 
     printf("DONE:BYEEE");
      }
      */ 
   }
          printf("++++++++++++++++++++++++++++++++++++++++++\n");
          printf("++++    SUCCESSFULLY ANALYZED DATA    ++++\n");
          printf("++++++++++++++++++++++++++++++++++++++++++\n");
        
  fclose(ifile);
  return (0);
 }
 /* STATS for all data:mean and deviation calculation*/
 
  int stats1(double *mean, double *stddvtn,char file)
 {
   int i;
   double num, total, x, min, max;
   double dvtn, sumdvtn;
   FILE *ifile;

       if(file == 't')                         /*Opening the right file*/
           ifile = fopen("tiny_data.txt","r");
       if(file == 's')
           ifile = fopen("small_data.txt","r");
       if(file == 'm')
           ifile = fopen("medium_data.txt","r");
       if(file == 'b')
        {ifile = fopen("big_data.txt","r");
         printf("Patience:It's a big file...\n");
        }
   i = 0;
   total = 0;
  
   printf("Reading file...\n");
  while(fscanf(ifile,"%lf", &num) != EOF)
  {  if (i == 0)
    { max = num;
    }  min = num;
    
    if (num > max)
    max = num; 
    if (num < min)
     min = num;
   
    total += num;
    i++;
  }
  printf("Done reading file...\n");
  *mean = (total / i); 
    
      /*output of Stats function (mean)*/
  printf("      MAJOR STATS FOR ALL DATA VALUES\n");
  printf("------------------------------------------------\n");
  printf("Total number of data is           %d\n",i);
  printf("Min and max values are            %lf and %lf\n",min,max);
  printf("Mean(of all data) is              %lf \n", *mean) ;
  
      /*calculating deviation*/ 
    i = 0;
    sumdvtn = 0;
  
      rewind(ifile);
   while(fscanf(ifile,"%lf", &num) != EOF)
    { dvtn = pow( (num - *mean),2);
      sumdvtn += dvtn;
      i++;
    }
    *stddvtn = sqrt (sumdvtn / (i-1));
    
    /*output of Stats function (deviation)*/
     printf("sum of deviations of all data is  %lf\n", sumdvtn);  
     printf("Standard deviation is             %lf \n\n", *stddvtn);
    
     fclose(ifile);
  return (0);
 }
    /*iterative stats function:sets outliers level and recalc stats*/
  int itrstats(int *o,int *e,double *mean,double *stddvtn,char file)
  {
   int i,x,y;
   double num, total, min, max;
   double dvtn, sumdvtn,pmean;
   float lvl;
   FILE *ifile;
   
    printf("         ITERATION NUMBER %d\n",*e);
    printf("   ________________________________\n\n");
    
   if(file == 't')
           ifile = fopen("tiny_data.txt","r");
   if(file == 's')
           ifile = fopen("small_data.txt","r");
   if(file == 'm')
           ifile = fopen("medium_data.txt","r");
   if(file == 'b')
          ifile = fopen("big_data.txt","r");

 /* setting level for finding outliers*/
      if (*e == 1)
      {printf("Enter a number to set level for finding outliers> \n"); 
       scanf("%f",&lvl);
      }  
    
        
   /* recalculating deviation, excluding outliers*/
    i = 0;
    x = 0;
    total = 0;
    
    while(fscanf(ifile,"%lf", &num) != EOF)
    {  if ( (num >= ((lvl * *stddvtn) + *mean)) ||( num <= (*mean - (lvl * *stddvtn))))
       x++;
       else
      {total += num;  
       i++; }  
    }
    
  *mean = (total / i);
  printf("\nTotal number of data(used) is    %d\n",i);
  printf("Starting number of outliers is     %d \n", x);
  printf("New Mean is                        %lf\n\n", *mean) ;
  
  /*deviation*/
  i = 0;
  y = 0;
  sumdvtn = 0;
  rewind(ifile);
   while(fscanf(ifile,"%lf", &num) != EOF)
    {  if ( (num >= ((lvl * *stddvtn) + *mean)) ||( num <= (*mean - (lvl * *stddvtn))))
       y++;
      else
      { i++;
        dvtn = pow( (num - *mean),2);
         sumdvtn += dvtn;
         
        if (i == 1)
       { max = num;
        min = num;}
        if (num > max)
         max = num; 
        if (num < min)
         min = num;
      }
    }
          
       *stddvtn = sqrt (sumdvtn / (i-1));
       *o = y - x ;
       
       printf("Total number of outliers is      %d\n",y);
       printf("Outliers in this iteration       %d\n",*o);
       printf("New min and max values are       %lf and %lf\n",min,max);
       printf("Sum of deviations of all data is %lf\n", sumdvtn);
       printf("Standard deviation is            %lf \n\n\n", *stddvtn); 
       

    fclose(ifile);
      
  return (0);
 }