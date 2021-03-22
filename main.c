#include<stdio.h>
#include "global.h"
#include "extract.h"
#include "inject.h"

const char file[] = "C:/Users/my_pc/source/repos/elf-inject/Debug/test";
FILE *fp;

int main(){

    Elf32_Ehdr elf_hdr;

    if((fp=open_Elf(file))==NULL){
        return 0;
    }

    if(read_Elf_Header(fp,&elf_hdr)==-1){
        return 0;
    }

    //print_hex((char *)&elf_hdr,sizeof(Elf32_Ehdr));

}
