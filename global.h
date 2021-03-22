#ifndef _GLOBAL_H
#define _GLOBAL_H
#include<stdio.h>
#include<stdint.h>


#define EI_NIDENT 16
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf32_Off;


Elf32_Phdr  pht[50];
Section_Unit sht[50];

typedef struct {
    FILE         *fp;
    Elf32_Ehdr   elf_hdr;
    unsigned int file_size;
    unsigned int sht_offset;
    unsigned int pht_offset;
    unsigned int ph_num;
    unsigned int sect_num;
    Elf32_Phdr*  pht;
    Elf32_Shdr*  sht;

}Global_Var;


/*ELF Header*/
typedef struct
{
  unsigned char    e_ident[EI_NIDENT];    /* Magic number */
  Elf32_Half    e_type;             /* Object file type */
  Elf32_Half    e_machine;          /* Architecture */
  Elf32_Word    e_version;          /* Object file version */
  Elf32_Addr    e_entry;            /* Entry point virtual address */
  Elf32_Off    e_phoff;             /* Program header table file offset */
  Elf32_Off    e_shoff;             /* Section header table file offset */
  Elf32_Word    e_flags;            /* Processor-specific flags */
  Elf32_Half    e_ehsize;           /* ELF header size in bytes */
  Elf32_Half    e_phentsize;        /* Program header table entry size */
  Elf32_Half    e_phnum;            /* Program header table entry count */
  Elf32_Half    e_shentsize;        /* Section header table entry size */
  Elf32_Half    e_shnum;            /* Section header table entry count */
  Elf32_Half    e_shstrndx;         /* Section header string table index */
} Elf32_Ehdr;

/* Section Header */
typedef struct {
    Elf32_Word    sh_name;    /* name - index into section header
                       string table section */
    Elf32_Word    sh_type;    /* type */
    Elf32_Word    sh_flags;    /* flags */
    Elf32_Addr    sh_addr;    /* address */
    Elf32_Off     sh_offset;    /* file offset */
    Elf32_Word    sh_size;    /* section size */
    Elf32_Word    sh_link;    /* section header table index link */
    Elf32_Word    sh_info;    /* extra information */
    Elf32_Word    sh_addralign;    /* address alignment */
    Elf32_Word    sh_entsize;    /* section entry size */
} Elf32_Shdr;


/* Program Header */
typedef struct {
    Elf32_Word    p_type;     /* segment type */
    Elf32_Off     p_offset;   /* segment offset */
    Elf32_Addr    p_vaddr;    /* virtual address of segment */
    Elf32_Addr    p_paddr;    /* physical address - ignored? */
    Elf32_Word    p_filesz;   /* number of bytes in file for seg. */
    Elf32_Word    p_memsz;    /* number of bytes in mem. for seg. */
    Elf32_Word    p_flags;    /* flags */
    Elf32_Word    p_align;    /* memory alignment */
} Elf32_Phdr;


void global_init(Global_Var *global_var,const char * file_name);
void print_hex(const char *str,size_t len);
FILE * open_elf(const char *file_name);



typedef struct{
    Elf32_Shdr shdr;
    unsigned int section_size;
    char* ptr;
}Section_Unit;

#endif