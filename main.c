#include<stdio.h>
#include "global.h"
#include "read.h"
#include "write.h"
#include "init.h"

//const char file[] = "C:/Users/ktink/source/repos/ELF_inject/Debug/test";
const char file[] = "C:/Users/my_pc/source/repos/Elf_inject/Debug/test";
const char target[] = "C:/Users/my_pc/source/repos/Elf_inject/Debug/target";

Global_Var global_var;


int main(){

    global_init(&global_var, file,target);

    //read_section_table(&global_var);

    //print_all_sections(&global_var);

    construct_target_file(&global_var);

    //print_hex((char *)&elf_hdr,sizeof(Elf32_Ehdr));
    return 0;
}
