#include "write.h"


/**********************************************************************************
*write elf header 
**********************************************************************************/
int write_elf_header(Global_Var *global_var) {
	printf("write_elf_header\n");
	write_stream_by_offset(&global_var->elf_hdr, sizeof(Elf32_Ehdr), 0, global_var->tgt_fp);;
	return 0;
}

/**********************************************************************************
*write pht
**********************************************************************************/
int write_pht(Global_Var* global_var) {
	printf("write_pht\n");
	int index = 0;
	unsigned int offset = global_var->pht_offset;
	//可以不用每次都算便宜，直接一个fread直接写
	for (index; index < global_var->ph_num; index++) {
		write_stream_by_offset(&global_var->pht[index], sizeof(Elf32_Phdr),offset,global_var->tgt_fp);
		offset +=sizeof(Elf32_Phdr);
	}
	return 0;
}


/**********************************************************************************
*write  all sections
**********************************************************************************/
int write_all_sections(Global_Var* global_var) {
	printf("write_all_sections\n");
	int index = 0;
	unsigned int offset = 0;
	unsigned int len = 0;
	char* buf = NULL;
	for (index; index < global_var->sect_num; index++) {
		buf = global_var->sht[index].ptr;
		offset = global_var->sht[index].section_offset;
		len = global_var->sht[index].section_size;
		write_stream_by_offset(buf,len, offset, global_var->tgt_fp);
	}
	return 0;
}


/**********************************************************************************
*write  sht
**********************************************************************************/
int write_sht(Global_Var* global_var) {
	printf("write_sht\n");
	int index = 0;
	unsigned int offset = global_var->sht_offset;
	unsigned int len = 0;
	char* buf = NULL;
	for (index; index < global_var->sect_num; index++) {
		buf = &global_var->sht[index].shdr;
		len = sizeof(Elf32_Shdr);
		write_stream_by_offset(buf, len, offset, global_var->tgt_fp);
		offset += sizeof(Elf32_Shdr);
	}
	return 0;
}


/**********************************************************************************
*construct target file
**********************************************************************************/
int construct_target_file(Global_Var *global_var) {
	write_elf_header(global_var);
	write_pht(global_var);
	write_all_sections(global_var);
	write_sht(global_var);
}