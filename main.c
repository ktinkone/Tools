#include<stdio.h>
#include "global.h"
#include "extract.h"
#include "inject.h"

const char file[] = "C:/Users/ktink/source/repos/ELF_inject/Debug/test";
//const char file[] = "C:/Users/my_pc/source/repos/elf-inject/Debug/test";

Global_Var global_var;


int main(){

    global_init(&global_var, file);

    read_section_table(&global_var);

    print_all_sections(&global_var);

    
    //print_hex((char *)&elf_hdr,sizeof(Elf32_Ehdr));
    return 0;
}
