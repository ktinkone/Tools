#ifndef _WRITE_H
#define _WRITE_H

#include<stdio.h>
#include<fcntl.h>
#include<string.h>

#include "global.h"



int write_elf_header		(Global_Var* global_var);
int write_pht				(Global_Var* global_var);
int write_all_sections		(Global_Var* global_var);
int write_sht				(Global_Var* global_var);
int construct_target_file	(Global_Var* global_var);

#endif