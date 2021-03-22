#include<stdio.h>
#include<string.h>
#include "extract.h"
#include "global.h"


extern Elf32_Phdr  pht[50];

/**********************************************************************************
*read Elf_Header from elf file
**********************************************************************************/
int read_Elf_Header(FILE *fp,Elf32_Ehdr *elf_header){
    size_t i;
    if(fp==NULL){
        printf("fp can not be NULL\n");
        return -1;
    }
    if(fread(elf_header,sizeof(Elf32_Ehdr),1,fp)!=1){
        printf("read elf header failed!\n");
        return -1;
    }
    //simple judge if file is elf file
    if(((char *) elf_header)[0]==0x7f&&((char *) elf_header)[1]==0x45){
        printf("read elf  header success!\n");
        return 1;
    }else{
        printf("File is not a elf file !\n");
        return -1;
    }
}


/**********************************************************************************
*read programe header table
**********************************************************************************/
int read_prog_header(Global_Var *global_var){
    int index = 0;
    //fseek
    if (fseek(global_var->fp, global_var->pht_offset, SEEK_SET) != 0) {
        printf("read prog header table-> fseek error!\n");
        exit(-1);
    }
    //read pht
    for (index; index < global_var->ph_num; index++) {
        if (fread(&pht[index], sizeof(Elf32_Phdr), 1, global_var->fp) != 1) {
            printf("read prog header table-> fread error!\n");
            exit(-1);
        }
    }
    global_var->pht = &pht[0];
    return 1;
}


/**********************************************************************************
*read section table
*读取section表的同时，一道把每个section给读了
**********************************************************************************/
int read_section_table(Global_Var* global_var) {
    int index = 0;
    //fseek
    if (fseek(global_var->fp, global_var->sht_offset, SEEK_SET) != 0) {
        printf("read section header table -> fseek error!\n");
        exit(-1);
    }
    //read  s
    for (index; index < global_var->sect_num; index++) {
        if (fread(&sht[index], sizeof(Elf32_Shdr), 1, global_var->fp) != 1) {
            printf("read section header table-> fread error!\n");
            exit(-1);
        }
    }
    global_var->sht=&sht[0]; 
    return 1;
}



/**********************************************************************************
*read signal sections unit
**********************************************************************************/




