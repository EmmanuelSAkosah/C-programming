/*
*Emmanuel S Akosah  
*Long Assignment            
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "recruitlib.h"
void rmv(details_t tophire[],int *l);
void sve(details_t tophire[],int *l);
void src(details_t tophire[],int *l);
void dpl(details_t tophire[],int *l);
void adr(details_t tophire[],int *l);
void ssort(details_t tophire[],int *l);


int main(void)
{ 
    int i,l,q,rtn;
    unsigned id;
    char nm[20];
    char nm2[20];
    char trm [3];
    unsigned rt1;
    unsigned rt2;
    FILE *ifile;
    char rm[3];             
    char filename[13];
   
    
    printf("          -----------------------------------------------------\n");
    printf("          |            WELCOME TO RECRUITBOOK                 |\n") ;
    printf("          -----------------------------------------------------\n");
    printf("You must enter a file to work with before you can proceed\n");
    
     /* opening file*/
  printf("Enter filename: >");
  scanf("%s",filename);  
   
  ifile = fopen(filename, "r");
  if (ifile != NULL)
    printf("File has been succesfully opened :) \n");
  if(ifile == NULL)
    {printf("Failed to open file :( \n");
    return (1);}
     
  printf("      %s        \n",filename );
  printf("---------------------------\n");
  
  struct details {                                 /*define structure*/
    unsigned ID;
    char lname[20];
    char fname[20];
    char term [3];
    unsigned rating1;
    unsigned rating2;
    unsigned index;
    unsigned index2;
  };
  typedef struct details details_t;
  
  details_t tophire[1000];            /*declare array of structures*/
  
  i=0;
  printf("\n reading values into array...");
  while(fscanf(ifile,"%u %s %s %s %u %u", &id,nm,nm2,trm,&rt1,&rt2) != EOF)   /*reading data into array*/
  {
    tophire[i].ID = id;
    strcpy(tophire[i].lname ,nm);
    strcpy(tophire[i].fname ,nm2);
    strcpy(tophire[i].term ,trm);
    tophire[i].rating1 = rt1;
    tophire[i].rating2 = rt2;
    tophire[i].index = i;
    tophire[i].index2 = i;
    i++;
  } 
    l = i - 1;
     
   rtn = strcmp(filename,"recruits.txt");        /*open codes.txt if recruits.txt is opened*/
   if (rtn == 0 );
  {   
     typedef struct {                           /*structure for codes.txt*/
     unsigned IDc;
     char lt;
     unsigned indexc;
    } crypt_t;
  
    crypt_t code[1000];
    char ltr;
    int lc;
    FILE *ifile1;
   
   ifile1 = fopen("codes.txt","r");
   
   i=0;
    while(fscanf(ifile1,"%u %c ", &id,&ltr) != EOF)   /*reading codes.txt into array*/
   {
     code[i].IDc = id;  
     code[i].lt = ltr;
     code[i].indexc = i;  
     i++;
   } 
    lc = i - 1;
  
  }
  /* MENU */
  char wish;
  q = 1;
  
   printf("          -----------------------------------------------------\n");
   printf("          |            WELCOME TO RECRUITBOOK                 |\n") ;
   printf("          -----------------------------------------------------\n");
 while(q)
 { printf("\n\n"
         "                             MENU:\n"
         " Please enter an option from the menu\n"
         "  For:    DISPLAY    SORT     ADD     SEARCH     REMOVE   SAVE    QUIT\n"
         "Enter:    d          t        a       e          r        s       q\n" );
         scanf(" %c",&wish);                   
                            
        
  printf("You selected option %c\n",wish);
  switch (wish)                                      /* file selection*/
  {        
     case 'd': 
            dpl(tophire,&l);
            break;
     case 't'   : 
            ssort(tophire,&l);
           break;
     case 'a'    :
           adr(tophire,&l);
           break;
     case 'e' : 
           src(tophire,&l);
          break;         
     case 'r' :
           rmv(tophire,&l);
           break;
     case 's'   : 
           sve(tophire,&l); 
           break;
     case 'q'   : 
        printf("Are you sure you want to quit?\n");
        printf("Enter 'yes' if sure,otherwise enter 'no'\n");
        scanf("%s",rm);
        rtn = strcmp("yes",rm);        
        if (rtn == 0)
        {printf("Thanks for using RECRUITBOOK\n"
                "Exiting...\n");
            return (-1);
        }            
    default : 
      printf("Invalid input: Try again");
      break;
      
   }
   
  } 

  return(0);
      
 }
    
 
  /*remove a recruit*/
  void rmv(details_t tophire[],int *l) 
 { 
   int i,f,rtn;
   char rm[3];
   unsigned id;
     
   printf("Enter the ID of the recruit you want to remove.\n");
   scanf("%u",&id);
   
   i = 0;
   f = 0;
   while( !f && (i < (*l+1)))
     {if (id == tophire[i].ID)
       { f = 1; 
        printf("Match found\n");
        printf("    Index %u\n",tophire[i].index);
        printf("-----------------\n");
        printf("ID       : %u \n",tophire[i].ID);
        printf("Name     : %s %s\n",tophire[i].fname,tophire[i].lname);
        printf("Term     : %s \n",tophire[i].term);
        printf("Rating 1 : %u \n",tophire[i].rating1);
        printf("Rating 2 : %u \n\n",tophire[i].rating2);
        printf("Are you sure you want to remove this recruit?\n");
        printf("Enter 'yes' if sure,otherwise enter 'no'\n");
        scanf("%s",rm);
         rtn = strcmp("yes",rm);
         
          /*removing*/
          if (rtn == 0)                    
          { 
           while (i < *l)
           {tophire[i].ID = tophire[i+1].ID;
           strcpy(tophire[i].lname ,tophire[i+1].lname);
           strcpy(tophire[i].fname ,tophire[i+1].fname);
           strcpy(tophire[i].term ,tophire[i+1].term);
           tophire[i].rating1 = tophire[i+1].rating1;
           tophire[i].rating2 = tophire[i+1].rating2;
         
           i++; 
           }
           tophire[*l].ID = 0;
           strcpy(tophire[*l].lname ,"/0");
           strcpy(tophire[*l].fname ,"/0");
           strcpy(tophire[*l].term ,"/0");
           tophire[*l].rating1 = 0;
           tophire[*l].rating2 = 0;
           printf("Recruit succesfully removed.\n");
           *l--;
          }         
         else
           printf("Remove operation aborted.\n");                       
       }
        i++;        
     } 
    if (f == 0)  
    {printf("The entered ID is not associated with any recruit.\n");  
     printf("Remove operation aborted.\n");
    }
     
 
 }
  void sve(details_t tophire[],int *l)
  
 {   
    int i,q,rtn;
    unsigned id;
    char nm[20];
    char nm2[20];
    char trm [3];
    unsigned rt1;
    unsigned rt2;
    FILE *ofile;
    
   ofile = fopen("updrecruits.txt","w");
    
   i = 0; 
   printf("\n saving file...");
   while (i < *l+1) 
  {  id = tophire[i].ID;
     strcpy(nm,tophire[i].lname);
     strcpy(nm2,tophire[i].fname);
     strcpy(trm,tophire[i].term);
     rt1 = tophire[i].rating1;
     rt2 = tophire[i].rating2;
        
     fprintf(ofile,"%09u %s %s %s %u %u",id,nm,nm2,trm,rt1,rt2);
     fprintf(ofile,"\n");
     i++;         
  } 
  printf("\n Done saving file..."
         "Your updated file has been saved to updrecruits.txt");
  
 } 
   /* search and display details*/
  void src(details_t tophire[],int *l)
   { 
  
   int i,m,match,rtn;
   char name[18];
   
   printf("Enter the lastname of the recruit you wanna find:\n");
   scanf("%s", name);
   printf("You entered:<%s>\n",name);
   
   match = 0;
   i = 0;
   m = 0;
   while((i < *l+1))
    { rtn = strcmp(name,tophire[i].lname);     
      if (rtn == 0)
      { match = 1;
                   
         {printf("A match was found: Details are below\n");
        printf("    Index %u\n",tophire[i].index);
        printf("-----------------\n");
        printf("ID       : %u \n",tophire[i].ID);
        printf("Name     : %s %s\n",tophire[i].fname,tophire[i].lname);
        printf("Term     : %s \n",tophire[i].term);
        printf("Rating 1 : %u \n",tophire[i].rating1);
        printf("Rating 2 : %u \n\n",tophire[i].rating2);
        }
       match = 0;
       m++; 
      } 
      i++;
    }
    if (m > 0)
      printf("%d match(es) were found in total.\n",m);
    else
      printf("Match was not found\n");
    
  }  
  
  /*Display*/
  
  void dpl(details_t tophire[],int *l)
  {
    int i;
    
   printf("           -----------------------------------------------------\n");
   printf("           |          List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term    Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
printf("\nDone\n");
/*
You can paste sample output here
*/
  }
  
  void adr(details_t tophire[],int *l)
  {
     /*add a name*/       
    FILE *afile;
    int i;
    unsigned id;
    char nm[20];
    char nm2[20];
    char trm [3];
    unsigned rt1;
    unsigned rt2;
    
    
    details_t nwrcrt;
    printf("%d",*l);
    printf("Enter details of the recruit you want to add in this format:\n"
            "ID Lastname Firstname Term Rating1 Rating2\n");     
     scanf("%u %s %s %s %u %u",&id,nm,nm2,trm,&rt1,&rt2);
    
    tophire[*l + 1].ID = id;
    strcpy(tophire[*l + 1].lname ,nm);
    strcpy(tophire[*l + 1].fname ,nm2);
    strcpy(tophire[*l + 1].term ,trm);
    tophire[*l + 1].rating1 = rt1;
    tophire[*l + 1].rating2 = rt2;
    tophire[*l + 1].index = *l + 1;  
    tophire[*l + 1].index2 = *l + 1;
    
    
     printf("The recruit you added is: \n");
     printf("    Index %u\n",tophire[*l + 1].index);
     printf("-----------------\n");
     printf("ID       : %u \n",tophire[*l + 1].ID);
     printf("Name     : %s %s\n",tophire[*l + 1].fname,tophire[*l + 1].lname);
     printf("Term     : %s \n",tophire[*l + 1].term);
     printf("Rating 1 : %u \n",tophire[*l + 1].rating1);
     printf("Rating 2 : %u \n\n",tophire[*l + 1].rating2);
    *l = *l + 1; 
    printf("%d\n",*l);
    printf("Done adding name\n");
    
  }
     
   void ssort(details_t tophire[],int *l)
 {  
    char wish,m;   
    int i,j;
    unsigned tmp;
    i = 0;
    j = 0;
    char temp[20];
   
   
   printf(" Please enter an option from the menu\n"
         "To sort by: ID(ascending)    ID(descending)  NAME    RATING1    RATING2\n"
         "Enter:      1                2               3        4         5\n" );
         scanf(" %c",&wish); 


  printf("You selected option %c\n",wish);
  switch (wish)                                      
  {        
     case '1': 
     /*sort by ID in ascending order*/
             printf("Sorting...please wait\n");  
          
    for (i = 0; i < (*l+1); ++i)
     {for (j = i + 1; j < (*l+1); ++j)
       {
          if (tophire[i].ID > tophire[j].ID)
             {  tmp =  tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
              
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp);
                
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);               
             
                tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
                
                tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
                
             }
       }
     }
     printf(" List in Ascending order.\n");
   printf("           -----------------------------------------------------\n");
   printf("           |          List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }
            break;
     case '2'   :
     /*sort by ID in descending order*/
            printf("Sorting...please wait\n");
   for (i = 0; i < (*l+1); ++i)
    {for (j = i + 1; j < (*l+1); ++j)
      {
          if (tophire[i].ID < tophire[j].ID)
            {   tmp =  tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
             
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp);
                
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);               
             
                tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
                
                tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
            }
      }
    }
    printf(" List in Descending order.\n");
   printf("           -----------------------------------------------------\n");
   printf("            |         List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
   printf("\nDone\n");
  
  
           break;
     case '3' : 
         /*sort by name*/
        
      printf("Enter 'f' to arrange by first names or 'l' to arrange by last names\n");
      scanf(" %c",&m);
      
      switch (m)
 {     case 'f':
      printf("Entering loop\n");
   for (i = 0; i < (*l+1) ; i++)
    {
        for (j = i + 1; j < (*l+1); j++)
        {
          if (strcmp(tophire[i].fname,tophire[j].fname) > 0)      /*by first name*/             
            {
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp);
                
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);
                
                tmp = tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
                                
                tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
                
                tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
                
            }
        }
    } 
    
   printf("Exited loop\n");
   
   printf("           -----------------------------------------------------\n");
   printf("           |          List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
   printf("\nDone\n"); 
       break;        
      case 'l':
       printf("Entering loop\n");
   for (i = 0; i < (*l+1) ; i++)
    {
        for (j = i + 1; j < (*l+1); j++)
        {
          if (strcmp(tophire[i].lname,tophire[j].lname) > 0)      /*by last name*/             
            {
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp);
                
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);
                
                tmp = tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
                               
                tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
                
                tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
                
            }
        }
    } 
    
   printf("Exited loop\n");  
   printf("           -----------------------------------------------------\n");
   printf("           |          List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
   printf("\nDone\n");
      break;
      default:
      printf("Invalid input: Try again");
      break;
      
 }
          break;        
     case '4' :
           /*sort by rating1*/
           
   printf("Sorting...please wait\n");
   for (i = 0; i < (*l+1); ++i)
    {for (j = i + 1; j < (*l+1); ++j)
      {
          if (tophire[i].rating1 < tophire[j].rating1)
            {   tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
                
                tmp =  tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
             
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp);
                
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);                             
                
                tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
            }
      }
    }
    printf(" List in Descending order.\n");
   printf("           -----------------------------------------------------\n");
   printf("            |         List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i<(*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
   printf("\nDone\n");
           break;
     case '5'   : 
          /*sort by rating2 */
   printf("Sorting...please wait\n");
   for (i = 0; i < (*l+1); ++i)
    {for (j = i + 1; j < (*l+1); ++j)
      {
          if (tophire[i].rating2 < tophire[j].rating2)
            {   tmp = tophire[i].rating2;
                tophire[i].rating2 = tophire[j].rating2;
                tophire[j].rating2 = tmp;
                
                tmp =  tophire[i].ID;
                tophire[i].ID = tophire[j].ID;
                tophire[j].ID = tmp;
             
                strcpy(temp, tophire[i].lname);
                strcpy(tophire[i].lname, tophire[j].lname);
                strcpy(tophire[j].lname, temp);
                
                strcpy(temp, tophire[i].fname);
                strcpy(tophire[i].fname, tophire[j].fname);
                strcpy(tophire[j].fname, temp); 

                strcpy(temp, tophire[i].term);
                strcpy(tophire[i].term, tophire[j].term);
                strcpy(tophire[j].term, temp);                             
                
                tmp = tophire[i].rating1;
                tophire[i].rating1 = tophire[j].rating1;
                tophire[j].rating1 = tmp;
            }
      }
    }
    printf(" List in Descending order.\n");
   printf("           -----------------------------------------------------\n");
   printf("            |         List Of All Potential Recruits           |\n") ;
   printf("           -----------------------------------------------------\n");   
   printf("Index    ID          First name        Last name      Term     Rating1   Rating2\n");
   printf("_____  _________     __________        _________      ____    _____     _____\n");
   for(i=0; i< (*l+1);i++)
   {printf("%03d   %09u      %-13s    %-15s %s      %04u      %04u\n",
           tophire[i].index,tophire[i].ID,tophire[i].fname,tophire[i].lname,tophire[i].term,
           tophire[i].rating1,tophire[i].rating2);
   }  
   printf("\nDone\n");
           break;
     
    default : 
      printf("Invalid input: Try again");
      break;
      
  }
 }
 
