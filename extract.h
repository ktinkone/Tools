#ifndef _EXTRACT_H
#define _EXTRACT_H

#include<stdio.h>
#include "global.h"


int read_Elf_Header(Global_Var* global_var);
int read_prog_header(Global_Var* global_var);
int read_section_table(Global_Var* global_var);
int read_section(Global_Var* global_var, Section_Unit* sec_unit);
int read_all_sections(Global_Var* global_var);
#endif