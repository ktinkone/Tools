#ifndef _READ_H
#define _READ_H

#include<stdio.h>
#include "global.h"



int open_elf(Global_Var* global_var, const char* file_name);
int create_new_elf(Global_Var* global_var, const char* file_name);
int read_Elf_Header(Global_Var* global_var1);
int read_prog_header(Global_Var* global_var);
int read_section_table(Global_Var* global_var);
int read_section(Global_Var* global_var, Section_Unit* sec_unit);
int read_all_sections(Global_Var* global_var);

#endif