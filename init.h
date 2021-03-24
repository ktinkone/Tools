#ifndef _INIT_H
#define	_INIT_H

#include "global.h"
#include "read.h"
#include "write.h"


void global_init(Global_Var* global_var, const char* file_name,const char *target);

//初始化待写入文件
int init_target_file(Global_Var* global_var);


#endif