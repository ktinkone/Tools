#include<stdio.h>
#include "global.h"
#include "extract.h"

#pragma   warning(disable:4996)

void print_hex(const char *str,size_t len){
    unsigned char *str_u =(unsigned char *)str;
    for(size_t i=0;i<len;i++){
        printf("%x ",str_u[i]);
    }
}

/**********************************************************************************
*Init Global var
**********************************************************************************/
void global_init(Global_Var* global_var, const char* file_name) {
    global_var->fp = open_elf(file_name);
    read_Elf_Header(global_var->fp, &global_var->elf_hdr);
    
    global_var->pht_offset = global_var->elf_hdr.e_phoff;
    global_var->ph_num = global_var->elf_hdr.e_phnum;

    global_var->sect_num = global_var->elf_hdr.e_shnum;
    global_var->sht_offset = global_var->elf_hdr.e_shoff;
}

/**********************************************************************************
*Open Elf file
**********************************************************************************/
FILE * open_elf(const char *file_name){
    FILE *fp=fopen(file_name,"rb+");
    if(fp==NULL){
        printf("Open Elf file : %s failed\n",file_name);
        exit(-1);
    }
    return fp;
}


/**********************************************************************************
*打印section table 中所有内容 （测试用）
**********************************************************************************/
int print_all_sections(Global_Var *global_var) {
    unsigned int index = 0;
    Elf32_Shdr tmp;
    for (index; index < global_var->sect_num; index++) {
        tmp = global_var->sht[index].shdr;
        printf("virtual addr->%x   elf offset->%x   section size->%x", tmp.sh_addr, tmp.sh_offset, tmp.sh_size);
    }
    return 0;
}

