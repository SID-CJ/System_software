 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 int main(){
    FILE *symtab,*inter,*optab,*length,*input;
    char label[20],opcode[20],operand[20],*temp;
    int locctr;
    symtab=fopen("symtab.txt","w+");
    optab=fopen("optab.txt","r");
    inter=fopen("intermediate.txt","w");
    length=fopen("length.txt","w");
    input=fopen("input.txt","r");
    if(symtab!=NULL){
        fscanf(input,"%s%s%s",label,opcode,operand);
        if(strcmp(opcode,"START")==0){
            locctr=strtol(operand,&temp,16);
            fprintf(inter,"\t%s\t%s\t%s\n",label,opcode,operand);
        }
    }
    fclose(symtab);
    fclose(optab);
    fclose(input);
    fclose(length);
    fclose(inter);
    return 0;
 }
