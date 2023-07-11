#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define buffer_max 128
#define bits 16

struct jump{
    const char nothing[4];
    const char JGT[4];
    const char JEQ[4];
    const char JGE[4];
    const char JLT[4];
    const char JNE[4];
    const char JLE[4];
    const char JMP[4];
};

struct jump const jmp_code = {
    .nothing = "000",
    .JGT = "001",
    .JEQ = "010",
    .JGE = "011",
    .JLT = "100",
    .JNE = "101",
    .JLE = "110",
    .JMP = "111",
};

char* get_jmp_adr(char code[4],char jmp_adr[4]){
    if(!strcmp(jmp_adr,"000")) strcpy(code,jmp_code.nothing);
    else if(!strcmp(jmp_adr,"JGT")) strcpy(code,jmp_code.JGT);
    else if(!strcmp(jmp_adr,"JEQ")) strcpy(code,jmp_code.JEQ);
    else if(!strcmp(jmp_adr,"JGE")) strcpy(code,jmp_code.JGE);
    else if(!strcmp(jmp_adr,"JLT")) strcpy(code,jmp_code.JLT);
    else if(!strcmp(jmp_adr,"JNE")) strcpy(code,jmp_code.JNE);
    else if(!strcmp(jmp_adr,"JLE")) strcpy(code,jmp_code.JLE);
    else if(!strcmp(jmp_adr,"JMP")) strcpy(code,jmp_code.JMP);
    return code;
}

struct dest{
    const char nothing[4];
    const char M[4];
    const char D[4];
    const char MD[4];
    const char A[4];
    const char AM[4];
    const char AD[4];
    const char AMD[4];
};

struct dest const dest_adr= {
    .nothing = "000",
    .M = "001",
    .D = "010",
    .MD = "011",
    .A = "100",
    .AM = "101",
    .AD = "110",
    .AMD = "111",
};

char* get_dest_adr(char code[4],char dest[4]){
    // returns destination adress for the expre
    // -ssion dest
    if (!strcmp(dest,"000")) strcpy(code, dest_adr.nothing);
    else if (!strcmp(dest,"M00")) strcpy(code, dest_adr.M);
    else if (!strcmp(dest,"D00")) strcpy(code, dest_adr.D);
    else if (!strcmp(dest,"MD0")) strcpy(code, dest_adr.MD);
    else if (!strcmp(dest,"A00")) strcpy(code, dest_adr.A);
    else if (!strcmp(dest,"AM0")) strcpy(code, dest_adr.AM);
    else if (!strcmp(dest,"AD0")) strcpy(code, dest_adr.AD);
    else if (!strcmp(dest,"AMD")) strcpy(code, dest_adr.AMD);
    return code;
}

struct comp{
    const char _0[7];
    const char _1[7];
    const char _neg_1[7];
    const char D[7];
    const char A[7];
    const char not_D[7];
    const char not_A[7];
    const char neg_D[7];
    const char neg_A[7];
    const char D_p_1[7];
    const char A_p_1[7];
    const char D_m_1[7];
    const char A_m_1[7];
    const char D_p_A[7];
    const char D_m_A[7];
    const char A_m_D[7];
    const char D_and_A[7];
    const char D_or_A[7];
};

struct comp const comp_code = {
    ._0 = "101010",
    ._1 = "111111",
    ._neg_1 = "111010",
    .D = "001100",
    .A = "110000",
    .not_D = "001101",
    .not_A = "110001",
    .neg_D = "001111",
    .neg_A = "110011",
    .D_p_1 = "011111",
    .A_p_1 = "110111",
    .D_m_1 = "001110",
    .A_m_1 = "110010",
    .D_p_A = "000010",
    .D_m_A = "010011",
    .A_m_D = "000111",
    .D_and_A = "000000",
    .D_or_A = "010101",
};

char* get_comp_code(char code[7],char comp[4]){
    // returns the comp code for the comp string 
    // comp
    if(!strcmp(comp, "000")) strcpy(code,comp_code._0);
    else if(!strcmp(comp, "100")) strcpy(code,comp_code._1);
    else if(!strcmp(comp, "-10")) strcpy(code,comp_code._neg_1);
    else if(!strcmp(comp, "D00")) strcpy(code,comp_code.D);
    else if(!strcmp(comp, "A00")) strcpy(code,comp_code.A);
    else if(!strcmp(comp, "M00")) strcpy(code,comp_code.A);
    else if(!strcmp(comp, "!D0")) strcpy(code,comp_code.not_D);
    else if(!strcmp(comp, "!A0")) strcpy(code,comp_code.not_A);
    else if(!strcmp(comp, "!M0")) strcpy(code,comp_code.not_A);
    else if(!strcmp(comp, "-D0")) strcpy(code,comp_code.neg_D);
    else if(!strcmp(comp, "-A0")) strcpy(code,comp_code.neg_A);
    else if(!strcmp(comp, "-M0")) strcpy(code,comp_code.neg_A);
    else if(!strcmp(comp, "D+1")) strcpy(code,comp_code.D_p_1);
    else if(!strcmp(comp, "A+1")) strcpy(code,comp_code.A_p_1);
    else if(!strcmp(comp, "M+1")) strcpy(code,comp_code.A_p_1);
    else if(!strcmp(comp, "D-1")) strcpy(code,comp_code.D_m_1);
    else if(!strcmp(comp, "A-1")) strcpy(code,comp_code.A_m_1);
    else if(!strcmp(comp, "M-1")) strcpy(code,comp_code.A_m_1);
    else if(!strcmp(comp, "D+A")) strcpy(code,comp_code.D_p_A);
    else if(!strcmp(comp, "D+M")) strcpy(code,comp_code.D_p_A);
    else if(!strcmp(comp, "D-A")) strcpy(code,comp_code.D_m_A);
    else if(!strcmp(comp, "D-M")) strcpy(code,comp_code.D_m_A);
    else if(!strcmp(comp, "A-D")) strcpy(code,comp_code.A_m_D);
    else if(!strcmp(comp, "M-D")) strcpy(code,comp_code.A_m_D);
    else if(!strcmp(comp, "D&A")) strcpy(code,comp_code.D_and_A);
    else if(!strcmp(comp, "D&M")) strcpy(code,comp_code.D_and_A);
    else if(!strcmp(comp, "D|A")) strcpy(code,comp_code.D_or_A);
    else if(!strcmp(comp, "D|M")) strcpy(code,comp_code.D_or_A);
    return code;
}

int is_memory_operation(char comp[4]){
    int a = 0;
    for (int i = 0;i < 3;i++){
        if ('M' == comp[i]){
            a = 1;
            break;
        }
    }
    return a;
}

char* process_line(char code[bits],int n, char line[n+1]){
     
    for (int i = 0;i < bits;i++){
        if (i < 3) code[i] = '1';
        else code[i] = '0';
    }
    // check for = or ; in line
    int eq = -1;
    for(int i = 0;i < n;i++){
        if (line[i] == '='){
            eq = 1;
            break;
        }
        else if(line[i] == ';'){
            eq = 0;
            break;
        }
        else if(line[i] == '@'){
            eq = 2;
            break;
        }
    }
    // dest = comp;jmp
    // if eq = 0 then it's a jump statement
    // if eq = 1 then the line is a computation
    // if eq = 2 then it's a @value type instruction
    char before[4] = "000";
    char after[4] = "000";
    char number[7] = "000000";
    char rev[4] = "000";
    int a = 0;
    int enc = 0;
    switch (eq) {
        case 0:
            for (int i = 0;i < n;i++){
                if (enc == 0 && line[i] != ';') before[i] = line[i];
                else if(line[i] == ';') enc = i;
                else if(enc != 0){
                    if(line[i] != '\0'){
                        after[i-enc-1] = line[i];
                    }
                    else break; 
                }
            }
            a = is_memory_operation(before);
            char comp[7];
            char* c = get_comp_code(comp,before);
            char jmp[4];
            char *j = get_jmp_adr(jmp,after);
            for (int i = 4;i < 10;i++){
                code[i] = c[i-4];
            }
            for (int i = 13;i<16;i++){
                code[i] = j[i-13];
            }

        case 1:
            for (int i = 0;i < n;i++){
                if (enc == 0 && line[i] != '=') before[i] = line[i];
                else if(line[i] == '=') enc = i;
                else if(enc != 0){
                    if(line[i] != '\0'){
                        after[i-enc-1] = line[i];
                    }
                    else break; 
                }
            }
            c = get_comp_code(comp,after);
            char dest[4];
            char *d = get_dest_adr(dest,before);
            for (int i = 4;i < 10;i++){
                code[i] = c[i-4];
            }
             for (int i = 10;i<13;i++){
                code[i] = d[i-10];
            }
            a = is_memory_operation(after);

        case 2:
            enc = -1;
            for (int i = 0;i < n;i++){
                if (enc == -1 && line[i] != '@') before[i] = line[i];
                else if(line[i] == '@'){
                    enc = i;
                }
                else if(enc != -1){
                    if(line[i] != '\0'){
                        number[(i-enc-1)] = line[i];
                        printf("%s\n",number);
                    }
                    else {
                        number[i-enc-1] = '\0';   
                        printf("%d\n",i);
                        break;
                    }
                }
            }

            int num = atoi(number);
    }
    if (a != 0) code[3] = '1';
    return code;
}



int main(int argc, char* argv[argc+1]){
   // FILE* progfile = fopen("max/MaxL.asm","r");
    //char buffer[buffer_max] = {0};
    //if (progfile){
    //    while(fgets(buffer, buffer_max, progfile)){
    //        if(buffer[0] != '/' && !isspace(buffer[0]))  fputs(buffer, stdout);
    //    }
    //    fclose(progfile);
    //}
    char code[bits];
    char* c = process_line(code, buffer_max, argv[1]);
    printf("%s\n",c);
    printf("%s",argv[1]);
    return 0;
}
