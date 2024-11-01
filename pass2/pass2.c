 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 int main(){
    FILE *symtab,*inter,*optab,*length,*input;
    char label[20],opcode[20],operand[20],*temp,sym_lab[20],addr[20],mnemonic[20],code[20];
    int locctr;
    symtab=fopen("symtab.txt","w+");
    optab=fopen("optab.txt","r");
    inter=fopen("intermediate.txt","w");
    input=fopen("input.txt","r");
    if(optab!=NULL && input!=NULL){
        fscanf(input,"%s%s%s",label,opcode,operand);
        if(strcmp(opcode,"START")==0){
            locctr=strtol(operand,&temp,16);
            fprintf(inter,"\t%s\t%s\t%s\n",label,opcode,operand);
            fscanf(input,"%s%s%s",label,opcode,operand);
        }
        else{
            locctr=0;
        }
        while(strcmp(opcode,"END")!=0){
            fprintf(inter,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            if(strcmp(label,"**")!=0){
                int flag=0;
                rewind(symtab);
                while(fscanf(symtab,"%s%s",sym_lab,addr)!=EOF){
                    if(strcmp(label,sym_lab)==0){
                        flag=1;
                        break;
                    }
                }
                if(flag){
                    printf("Error\n");
                }
                else{
                    fprintf(symtab,"%s\t%x\n",label,locctr);
                }
            }
            rewind(optab);
            while(fscanf(optab,"%s%s",mnemonic,code)!=EOF){
                if(strcmp(opcode,mnemonic)==0){
                    locctr+=3;
                    break;
                }
            }
            if(strcmp(opcode,"WORD")==0)
                locctr+=3;
            else if (strcmp(opcode,"RESW")==0)
                locctr+=(3*atoi(operand));
            else if (strcmp(opcode,"RESB")==0)
                locctr+=atoi(operand);
            else if (strcmp(opcode,"BYTE")==0){
                if(operand[0] == 'C')
                    locctr += strlen(operand) - 3;
                else    
                    locctr += (strlen(operand) - 3) / 2;
            }
        fscanf(input,"%s%s%s",label,opcode,operand);
        }
    }
    fclose(symtab);
    fclose(optab);
    fclose(input);
    fclose(inter);
    return 0;
 }
