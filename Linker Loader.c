# include <stdio.h>
# include <conio.h>
# include <string.h>
#include<stdlib.h>
# define MAX 20
int newaddr;
struct estab
{
    char csname[10];
    char extsym[10];
    int address;
    int length;
}es[MAX];

struct exttable
{
  char csect[20], sname[20];
  int padd,plen;
}estab[20];
struct objectcode
{
 unsigned char code[15];
 int add;
}obcode[500];

int address1;
int pass1()
{
    char input[10],name[10],symbol[10],name1[10];
    char s1name, ssname;
    int length1, length2;
    int count=0,progaddr,csaddr,add,len;
    FILE *fp1,*fp2;
    fp1=fopen("input2.txt","r");
    fp2=fopen("pass1_output.txt","w");
    printf("Enter program Location to be laoded : ");
    scanf("%X",&progaddr);
    csaddr=progaddr;
    printf("\nName\tSYM Name\tAddress\tLength\n\n");
    fscanf(fp1,"%s",input);
    while(!feof(fp1))
    {
        if(strcmp(input,"H")==0)
        {
            fscanf(fp1,"%s",name);
            strcpy(es[count].csname,name);
            strcpy(es[count].extsym,"**");
            fscanf(fp1,"%x",&add);
            address1=add;
            newaddr=add;
            printf("%x",newaddr);
            es[count].address=0+csaddr;
            fscanf(fp1,"%X",&len);
            es[count].length=len;

            fprintf(fp2,"%s %s %X %X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
            printf("%s\t%s\t\t%X\t%X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
            //if(es)
            count++;
        }
        else if(strcmp(input,"D")==0)
        {
            fscanf(fp1,"%s",input);
            while(strcmp(input,"R")!=0)
            {
                strcpy(es[count].csname,"**");
                strcpy(es[count].extsym,input);
                fscanf(fp1,"%X",&add);
                es[count].address=add+csaddr-address1;
                es[count].length=0;

//                fscanf(fp2,"%s %s %X %X",length1, length2, s1name, ssname);

                if(es[count].length==0)
                {
                fprintf(fp2,"%s %s %X\n",es[count].csname,es[count].extsym,es[count].address);
                printf("%s\t%s\t\t%X\n",es[count].csname,es[count].extsym,es[count].address);
                count++;
                fscanf(fp1,"%s",input);
                }
                else{
                fprintf(fp2,"%s %s %X %X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
                printf("%s\t%s\t\t%X\t%X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
                count++;
                fscanf(fp1,"%s",input);
                }
            }
            csaddr=csaddr+len;
        }
        else if(strcmp(input,"T")==0)
        {
            while(strcmp(input,"E")!=0)
                fscanf(fp1,"%s",input);
        }
        fscanf(fp1,"%s",input);
    }
    fclose(fp1);
    fclose(fp2);
    printf("\nExternal SYMTAB generated\n");
    return(newaddr);
}

int pass2()
{
 printf("\n\t\t*** PASS TWO OF A DIRECT-LINKING LOADER ***\n");
 printf("\nThe contents of the output file (L2OUT.txt):");
 printf("\n---------------------------------------------------------------");
 printf("\nAddress\t\t\t\tContents");
 printf("\n---------------------------------------------------------------\n\t");
 FILE *fp4,*fp5,*fp6;
 int i,j,x,y,pstart,exeloc,saddr1,start,textloc,loc,textlen,length,location,st,s;
 int n=0,num=0,inc=0,count=0,record=0,mloc[30],mlen[30];
 signed long int newadd;
 char operation,lbl[10],input[10],label[50][10],opr[30],ch,*add1,address[10];
 fp4=fopen("input2.txt","r");
 fp5=fopen("pass1_output.txt","r");
 fp6=fopen("L2OUT.txt","w");
 while(!feof(fp5))
 {
  fscanf(fp5,"%s %s %x %x", estab[num].csect, estab[num].sname, &estab[num].padd,&estab[num].plen);
  num++;
 }
 exeloc=estab[0].padd;
 loc=exeloc;
 start=loc;
 st=start;
 while(!feof(fp4))
 {
  fscanf(fp4,"%s",input);
  if(strcmp(input,"H")==0)
  {
   fscanf(fp4,"%s",input);
   for(i=0;i<num;i++)
    if(strcmp(input,estab[i].csect)==0)
    {
     pstart=estab[i].padd;
     break;
    }
   while(strcmp(input,"T")!=0)
    fscanf(fp4,"%s",input);
  }
  do
  {
  if(strcmp(input,"T")==0)
  {
   fscanf(fp4,"%x",&textloc);
   textloc=textloc+pstart;
   for(i=0;i<(textloc-loc);i++)
   {
    strcpy(obcode[inc].code,"..");
    obcode[inc++].add=start++;
   }
   fscanf(fp4,"%x",&textlen);
   loc=textloc+textlen;
  }
  else if(strcmp(input,"M")==0)
  {
   fscanf(fp4,"%x",&mloc[record]);
   mloc[record]=mloc[record]+pstart;
   fscanf(fp4,"%x",&mlen[record]);
   fscanf(fp4,"%s",label[record++]);
  }
  else
  {
   length=strlen(input);
   x=0;
   for(i=0;i<length;i++)
   {
    obcode[inc].code[x++]=input[i];
    if(x>1)
    {
     obcode[inc++].add=start++;
     x=0;
    }
   }
   }
  fscanf(fp4,"%s",input);
 }while(strcmp(input,"E")!=0);
 if(strcmp(input,"E")==0)
   fscanf(fp4,"%s",input);
 }
 for(n=0;n<record;n++)
 {
  operation=label[n][0];
  length=strlen(label[n]);
  for(i=1;i<length;i++)
  {
   lbl[i-1]=label[n][i];
  }
  lbl[length-1]='\0';
  length=0;
  strcpy(address,"\0");
  location=mloc[n]-exeloc;
  loc=location;
  count=0;
  while(length<mlen[n])
  {
   strcat(address,obcode[location++].code);
   count++;
   length+=2;
  }
  for(i=0;i<num;i++)
  {
  if(strcmp(lbl,estab[i].csect)==0)
   break;
  if(strcmp(lbl,estab[i].sname)==0)
   break;
  }
  switch(operation)
  {
   case '+':
    newadd=strtol(address,&add1,16)+(long int)estab[i].padd;
    break;
   case '-':
    newadd=strtol(address,&add1,16)-(long int)estab[i].padd;
    break;
  }
  ltoa(newadd,address,16);
  x=0; y=0;
  while(count>0)
  {
   obcode[loc].code[x++]=address[y++];
   if(x>1)
   {
    x=0; loc++;
    count--;
   }
  }}
 count=0;
 n=0;
 s=st-16;
 fprintf(fp6,"%x\t",s);
 for(i=1;i<=16;i++)
 {
  fprintf(fp6,"xx");
  printf("xx");
  if(i==4||i==8||i==12)
  {
   fprintf(fp6,"\t");
   printf("\t");
  }
 }
 fprintf(fp6,"\n\n%x\t",obcode[0].add);
 printf("\n\n%x\t",obcode[0].add);
 for(i=0;i<inc;i++)
 {
  fprintf(fp6,"%s",obcode[i].code);
  printf("%s",obcode[i].code);
  n++;
  if(n>3)
  {
   fprintf(fp6,"\t");
   printf("\t");
   n=0;
   count++;
  }
  if(count>3)
  {
   fprintf(fp6,"\n\n%x\t",obcode[i+1].add);
   printf("\n\n%x\t",obcode[i+1].add);
   count=0;
  }}
 fp6=fopen("L2OUT.txt","r");
 ch=fgetc(fp6);
 while(ch!=EOF)
 {
  printf("%c",ch);
  ch=fgetc(fp6);
 }
 fclose(fp6);
 return 0;
}

void main()
{
    pass1();
    pass2();
    getch();
}
