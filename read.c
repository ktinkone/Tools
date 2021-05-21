#include<stdio.h>
#include<string.h>

#include "read.h"


#pragma   warning(disable:4996)

/**********************************************************************************
*Open Elf file
**********************************************************************************/
int open_elf(Global_Var* global_var, const char* file_name) {
    FILE* fp = fopen(file_name, "rb+");
    if (fp == NULL) {
        printf("Open Elf file : %s failed\n", file_name);
        exit(-1);
    }
    global_var->fp = fp;
    return 0;
}



/**********************************************************************************
*Create new elf file
**********************************************************************************/
int create_new_elf(Global_Var* global_var, const char* file_name) {
    FILE* fp = fopen(file_name, "wb+");
    if (fp == NULL) {
        printf("Open Elf file : %s failed\n", file_name);
        exit(-1);
    }
    global_var->tgt_fp = fp;

    return 0;
}

/**********************************************************************************
*read Elf_Header from elf file
**********************************************************************************/
int read_Elf_Header(Global_Var* global_var) {
    unsigned int index;
    //fseek
    if (fseek(global_var->fp, 0, SEEK_SET) != 0) {
        printf("read elf header -> fseek error!\n");
        exit(-1);
    }
    if (fread(&global_var->elf_hdr, sizeof(Elf32_Ehdr), 1, global_var->fp) != 1) {
        printf("read elf header failed!\n");
        return -1;
    }
    //简单判断一下是不是ELF文件，判断开头两个魔术数
    if (global_var->elf_hdr.e_ident[0] == 0x7f && global_var->elf_hdr.e_ident[1] == 0x45) {
        printf("read elf  header success!\n");
        return 1;
    }
    else {
        printf("File is not a elf file !\n");
        return -1;
    }
}


/**********************************************************************************
*read programe header table
**********************************************************************************/
int read_prog_header(Global_Var* global_var) {
    unsigned int  index = 0;
    //fseek
    if (fseek(global_var->fp, global_var->pht_offset, SEEK_SET) != 0) {
        printf("read prog header table-> fseek error!\n");
        exit(-1);
    }
    //read pht
    for (index; index < global_var->ph_num; index++) {
        if (fread(&global_var->pht[index], sizeof(Elf32_Phdr), 1, global_var->fp) != 1) {
            printf("read prog header table-> fread error!\n");
            exit(-1);
        }
    }
    return 1;
}


/**********************************************************************************
*read section table
*读取section table ，顺便读取所有的section
**********************************************************************************/
int read_section_table(Global_Var* global_var) {
    int index = 0;
    printf("---------------------------read_section_table--------------------------\n");
    Section_Unit* tmp;
    //置位文件读取指针
    if (fseek(global_var->fp, global_var->sht_offset, SEEK_SET) != 0) {
        printf("read section table -> fseek error!\n");
        exit(-1);
    }
    //读取section table中所有的内容   (读结构体时，不用fread一次性读完，先分开读，不知道会不会存在结构体对齐的问题)
    for (index; index < global_var->sect_num; index++) {
        tmp = &(global_var->sht[index]);
        if (fread(&tmp->shdr, sizeof(Elf32_Shdr), 1, global_var->fp) != 1) {
            printf("read section table -> fread error!\n");
        }

        tmp->section_offset = tmp->shdr.sh_offset;
        tmp->section_size = tmp->shdr.sh_size;
        tmp->ptr = NULL;
    }

    read_all_sections(global_var);
    return 1;
}


/**********************************************************************************
*根据section unit 中的内容读取单个section的内容
**********************************************************************************/
int read_section(Global_Var* global_var, Section_Unit* sec_unit) {

    //如果size=0，就什么都不用读
    if (sec_unit->section_size == 0) {
        sec_unit->ptr = NULL;
        return 1;
    }
    //为每个section分配空间
    sec_unit->ptr = malloc(sec_unit->section_size);
    if (sec_unit->ptr == NULL) {
        printf("read section -> malloc error!\n");
        exit(-1);
    }

    //根据Elf32_Shdr结构体，读取单个section的内容
    //置位fp指针
    if (fseek(global_var->fp, sec_unit->section_offset, SEEK_SET) != 0) {
        printf("read section -> fseek error!\n");
        free(sec_unit->ptr);
        sec_unit->ptr = NULL;
        exit(-1);
    }
    //读取section内容
    if (fread(sec_unit->ptr, sec_unit->section_size, 1, global_var->fp) != 1) {
        printf("read section -> fread error!\n");
        free(sec_unit->ptr);
        sec_unit->ptr = NULL;
        exit(-1);
    }
    return 1;
}

/**********************************************************************************
*根据section table 中的内容  读取所有section的内容
**********************************************************************************/
int read_all_sections(Global_Var* global_var) {
    Section_Unit* tmp;
    unsigned int index = 0;
    for (index; index < global_var->sect_num; index++) {
        tmp = &global_var->sht[index];
        read_section(global_var, tmp);
    }
    read_all_section_name(global_var);
    return 0;
}

/***********************************************************
* Desc:读取所有section的名字，根据section的名字再shstrtab段中的偏移来读取
*
* Args:
***********************************************************/
int read_all_section_name(Global_Var* global_var) {
    //获取shstrtab段内容
    int index = global_var->elf_hdr.e_shstrndx;
    char* shstr = global_var->sht[index].ptr;

    for (int i = 1; i < global_var->sect_num; i++) {
        Section_Unit *tmp = &global_var->sht[i];
        //setcion name 在shstartab段中的偏移
        int section_name_offset;
        section_name_offset = tmp->shdr.sh_name;
        //read section name
        memset(tmp->name, 0, 50);
        char* p = shstr + section_name_offset;
        strcpy(tmp->name, p);
    }
}