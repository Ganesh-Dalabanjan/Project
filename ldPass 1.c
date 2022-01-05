#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    char label[50], opcodeval[50], operandval[50];
    char symb[50];
    char value[10];
    char mnemo[50];
    int len;


    int searchSymtab()
    {
        FILE *fp4=fopen("symtab.txt","r");
        int found = 0;

        while(!feof(fp4))
        {
            fscanf(fp4,"%s\t%s",symb,value);
            if(strcmp(symb,label)==0)
            {
                found = 1;
                break;
            }
            fscanf(fp4,"%s\t%s",symb,value);
        }

        fclose(fp4);
        return found;
    }

    int searchOptab()
    {
        FILE *fp5=fopen("Optab.txt","r");
        if(fp5 == NULL)
            printf("Error opening Optab.txt");

        int found = 0;
        while(!feof(fp5))
        {
            fscanf(fp5,"%s\t%s",mnemo,value);
            if(strcmp(mnemo, opcodeval)==0)
            {
                found = 1;
                break;
            }
        }

        fclose(fp5);
        return found;
    }


    void pass1(){
        char delimit[]=" \t\r\n";
        int locctr,start;
        char line[100];
        size_t len = 100 * sizeof(char);
        locctr = 4096;

        FILE *fp1 = fopen("Inputfile.txt", "r");
        if (fp1 == NULL)
            exit(EXIT_FAILURE);

        FILE *fp2, *fp3, *fp4;

        fp2 = fopen("symtab.txt", "w");
        fp3 = fopen("intermediate.txt", "w");
        fclose(fp2);


        while ((fgets(&line, &len, fp1)) != NULL)
        {
            int len = 0;
            strcpy(label, " ");
            strcpy(opcodeval, " ");
            strcpy(operandval, " ");
            char *p = strtok(line, delimit);
            char *array[4];

            while (p != NULL)
            {
                array[len++] = p;
                p = strtok (NULL, delimit);
            }

            if(len == 1){
                strcpy(opcodeval, array[0]);
            }
            else if(len == 2){
                strcpy(opcodeval, array[0]);
                strcpy(operandval, array[1]);
            }
            else if(len == 3){
                strcpy(label, array[0]);
                strcpy(opcodeval, array[1]);
                strcpy(operandval, array[2]);
            }
            if(strcmp(opcodeval, "END")==0)
                break;

            if (strcmp(opcodeval, "START") == 0) {
                start = (int)strtol(operandval, NULL, 16);
                printf("Start address = %x\n",start);
                locctr = start;
                fprintf(fp3, "\t%s\t%s\t%s\n", label, opcodeval, operandval);
                continue;
            }


            if((!strcmp(label, " ")==0) || (!strcmp(opcodeval, " ")==0) || (!strcmp(operandval, " ")==0)){

                fprintf(fp3, "%x\t%s\t%s\t%s\n", locctr, label, opcodeval, operandval);

                if (strcmp(label, " ") != 0)
                    if(!searchSymtab()){
                        fp2 = fopen("symtab.txt", "a");
                        fprintf(fp2, "%s\t%x\n", label, locctr);
                        fclose(fp2);
                    }
                    else{
                        printf("Error - Duplicate symb %s\n", label);
                        exit(EXIT_FAILURE);
                    }

                if(searchOptab())
                    locctr += 3;

                else if (strcmp(opcodeval, "WORD") == 0) {
                    locctr += 3;
                }

                else if (strcmp(opcodeval, "RESW") == 0) {
                    locctr += 3 * atoi(operandval);
                }
                else if (strcmp(opcodeval, "RESB") == 0) {
                    locctr += 1 * atoi(operandval);
                }
                else if (strcmp(opcodeval, "BYTE") == 0) {
                    if(operandval[0] == 'C' || operandval[0] == 'c')
                        locctr += (strlen(operandval) - 3);
                    else
                        locctr ++;
                }
                else{
                    printf("Error - Invalid opcodeval \n opcodeval Value %s\n", opcodeval);
                }

              }
        }

        len = locctr - start;
        printf("\nTotal len of code is %x",len);
        FILE *flen=fopen("length.txt","w");

        fprintf(flen,"%x",len);

        fprintf(fp3, "%x\t%s\t%s\t%s\n", locctr, label, opcodeval, operandval);


        fclose(fp1);
        fclose(fp3);
    }


    void show_intermediate_file(){
        FILE *fp6 = fopen("intermediate.txt", "r");

        if(fp6== NULL)
            printf("Error Opening intermediate.txt\n");

        printf("\n\n");

        char line[100];
        size_t len = 100 * sizeof(char);

        while ((fgets(&line, &len, fp6)) != NULL)
            printf("%s", line);


        fclose(fp6);

    }

    void symtab()
    {
        FILE *fp7=fopen("symtab.txt","r");
        if(fp7 == NULL)
            printf("Error Opening symtab.txt\n");

        printf("\n\n");

        fscanf(fp7,"%s\t%s",symb,value);
        while(!feof(fp7))
        {
            printf("%s\t%s\n", symb, value);
            fscanf(fp7,"%s\t%s",symb,value);
        }

        fclose(fp7);

    }

    int main()
    {
        pass1();
        symtab();
        show_intermediate_file();

        return 0;
    }
