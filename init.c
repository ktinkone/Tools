#include "init.h"


/**********************************************************************************
*Init Global var
**********************************************************************************/
void global_init(Global_Var* global_var, const char* file_name,const char *target) {
    
    open_elf(global_var, file_name);
    create_new_elf(global_var, target);

    read_Elf_Header(global_var);
    global_var->pht_offset = global_var->elf_hdr.e_phoff;
    global_var->ph_num = global_var->elf_hdr.e_phnum;

    global_var->sect_num = global_var->elf_hdr.e_shnum;
    global_var->sht_offset = global_var->elf_hdr.e_shoff;

	//ÔÝÊ±·ÅÕâ
	init_target_file(global_var);

	//¶Ápht
	read_prog_header(global_var);

	//¶Ásht
	read_section_table(global_var);

}


/**********************************************************************************
*init target file
**********************************************************************************/
int init_target_file(Global_Var* global_var) {
	unsigned int index;
	unsigned int len;
	unsigned int count;
	char buf[1024];
	memset(buf, 0x00, 1024);
	len = global_var->sht_offset + global_var->sect_num * global_var->elf_hdr.e_shentsize;
	printf("target file len :%8x\n", len);
	//constrcut target file
	for (index = 0; index < len;) {
		count = (len - index) > 1024 ? 1024 : len - index;
		if (fwrite(buf, count, 1, global_var->tgt_fp) != 1) {
			printf("init_target_file -> fwrite  error !\n");
		}
		index += count;
	}
}