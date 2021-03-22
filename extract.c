#include<stdio.h>
#include<string.h>
#include "extract.h"
#include "global.h"


extern Elf32_Phdr  pht[50];
extern Section_Unit sht[50];

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
*读取section table ，顺便读取所有的section
**********************************************************************************/
int read_section_table(Global_Var* global_var) {
    int index = 0;
    
    //置位文件读取指针
    if(fseek(global_var->fp,global_var->sht_offset,SEEK_SET)!=0){
        printf("read section table -> fseek error!\n");
        exit(-1);
    }

    //读取section table中所有的内容   (读结构体时，不用fread一次性读完，先分开读，不知道会不会存在结构体对齐的问题)
    for(index;index<global_var->sect_num;index++){
        if(fread(&sht[index],sizeof(Elf32_Shdr),1,global_var->fp)!=1){
            printf("read section table -> fread error!\n");
        }
        //
        sht[index].section_size= sht[index].shdr.sh_size;
        sht[index].section_offset=sht[index].shdr.sh_offset;
        sht[index].ptr=NULL;

        //读取单个section
        read_section(global_var,&sht[index]);
    }
    return 1;
}



/**********************************************************************************
*根据section table 中的内容读取单个section的内容
**********************************************************************************/
int read_section(Global_Var *global_var,Section_Unit *sec_unit){
    sec_unit->section_size=sec_unit->shdr.sh_size;
    
    //为每个section分配空间
    sec_unit->ptr=malloc(sec_unit->section_size);
    
    //根据Elf32_Shdr结构体，读取单个section的内容
    //置位fp指针
    if(fseek(global_var->fp,sec_unit->section_offset,SEEK_SET)!=0){
        printf("read section -> fseek error!\n");
        exit(-1);
    }
    //读取section内容
    if(fread(sec_unit->ptr,sec_unit->section_size,1,global_var->fp)!=1){
        printf("read section -> fread error!\n");
        exit(-1);
    }
    return 1;
}