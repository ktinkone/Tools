#ifndef _EXTRACT_H
#define _EXTRACT_H

#include<stdio.h>
#include "global.h"

//���ö�������
Elf32_Phdr pht[100];
Elf32_Shdr sht[100];




int read_Elf_Header(FILE *fp,Elf32_Ehdr *elf_header);


#endif