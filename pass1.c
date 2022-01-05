# include <stdio.h>
# include <conio.h>
# include <string.h>
# define MAX 20
struct estab
{
    char csname[10];
    char extsym[10];
    int address;
    int length;
}es[MAX];

void main()
{
    char input[10],name[10],symbol[10],name1[10];
        char ccc[10],ssss[10],addd[10],llll[10];
    char s1name, ssname;
    int length1, length2;
    int count=0,progaddr,csaddr,add,len,address1;
    FILE *fp1,*fp2;
    fp1=fopen("input1.txt","r");
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
            fscanf(fp1,"%X",&add);
            address1=add;
            es[count].address=0+csaddr;
            fscanf(fp1,"%X",&len);
            es[count].length=len;

            fprintf(fp2,"%s %s %X %X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
            printf("%s\t%s\t\t%X\t%X\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
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
}
