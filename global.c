#include<stdio.h>
#include "global.h"

#pragma   warning(disable:4996)

void print_hex(const char *str,size_t len){
    unsigned char *str_u =(unsigned char *)str;
    for(size_t i=0;i<len;i++){
        printf("%x ",str_u[i]);
    }
}


/**********************************************************************************
*打印section table 中所有内容 （测试用）
**********************************************************************************/
int print_all_sections(Global_Var *global_var) {
    unsigned int index = 0;
    Elf32_Shdr tmp;
    for (index; index < global_var->sect_num; index++) {
        tmp = global_var->sht[index].shdr;
        printf("index : %d virtual addr->%8x:%d   elf offset->%8x:%d   section size->%8x:%d  \n",index, tmp.sh_addr, tmp.sh_addr, tmp.sh_offset, tmp.sh_offset, tmp.sh_size,tmp.sh_size);
    }
    return 0;
}


/**********************************************************************************
*将字符串写入文件流
**********************************************************************************/
void write_stream_by_offset(char *buf, unsigned int len,unsigned int start, FILE* fp) {
    

    if (len==0||buf==NULL||fp==NULL) {
        printf("write stream error -> len == 0 || buf = NULL!||fp==NULL\n");
        return ;
    }

    if (fseek(fp, start, SEEK_SET) != 0) {
        printf("write stream -> fseek error !\n");
        exit(-1);
    }

    if (fwrite(buf,len,1,fp) != 1) {
        printf("write stream -> fwrite error !\n");
    }
}