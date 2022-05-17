#include <stdio.h>
#include <stdlib.h>
#include "elf.h"

int main(void){
	FILE *fp;
	char file_name[100];

	printf("Enter file name >");
	scanf("%s", file_name);
	//fprintf(stderr, "%s",file_name);
	printf("\n");
	fp = fopen(file_name, "rb");
	if(fp == NULL) {
		fprintf(stderr, "main: file open error\n");
		exit(1);
	}
	
	Elf64_Ehdr *buf = (Elf64_Ehdr*)malloc(sizeof(Elf64_Ehdr));
	
	fread(buf, sizeof(char), sizeof(Elf64_Ehdr), fp);
	if(buf->e_ident[EI_MAG0] == 0x7f && 
			buf->e_ident[EI_MAG1] == 'E' && 
			buf->e_ident[EI_MAG2] == 'L' && 
			buf->e_ident[EI_MAG3] == 'F') {
		//printf("This is ELF file.\n");
	} else {
		fprintf(stderr, "This is not Elf file.\n");
		exit(1);
	}
	
	int mode = 0;
	//printf("mode: ");
	if(buf->e_ident[EI_CLASS] == ELFCLASS32) {
		//printf("32bit\n");
		mode = 32;
	} else if (buf->e_ident[EI_CLASS] == ELFCLASS64) {
		//printf("64bit\n");
		mode = 64;
	} else {
		fprintf(stderr, "Invalid class.\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	if(mode == 32) {
		fread(buf, sizeof(char), sizeof(Elf32_Ehdr), fp);
		printf("mode: 32bit\n");
	} else if (mode == 64) {
		fread(buf, sizeof(char), sizeof(Elf32_Ehdr), fp);
	}

	if(mode == 64) {
		printf("----Elf Header----\n");
		printf("e_ident[EI_MAG0] =    0x%x\n", buf->e_ident[EI_MAG0]);
		printf("e_ident[EI_MAG1] =    '%c'\n", buf->e_ident[EI_MAG1]);
		printf("e_ident[EI_MAG2] =    '%c'\n", buf->e_ident[EI_MAG2]);
		printf("e_ident[EI_MAG3] =    '%c'\n", buf->e_ident[EI_MAG3]);
		printf("e_ident[EI_CLASS] =   %d\n", buf->e_ident[EI_CLASS]);
		printf("e_ident[EI_DATA] =    %d\n", buf->e_ident[EI_DATA]);
		printf("e_ident[EI_VERSION] = %d\n", buf->e_ident[EI_VERSION]);
		printf("e_ident[EI_PAD] =     %d\n", buf->e_ident[EI_PAD]);
		printf("e_type =      %d\n", buf->e_type);
		printf("e_machine =   %d\n", buf->e_machine);
		printf("e_version =   %d\n", buf->e_version);
		printf("e_entry =     %p\n", buf->e_entry);
		printf("e_phoff =     %p\n", buf->e_phoff);
		printf("e_shoff =     %p\n", buf->e_shoff);
		printf("e_flags =     %d\n", buf->e_flags);
		printf("e_ehsize =    %d\n", buf->e_ehsize);
		printf("e_phentsize = %d\n", buf->e_phentsize);
		printf("e_phnum =     %d\n", buf->e_phnum);
		printf("e_shentsize = %d\n", buf->e_shentsize);
		printf("e_shnum =     %d\n", buf->e_shnum);
		printf("e_shstrndx =  %d\n\n", buf->e_shstrndx);
		printf("------------------\n\n");

		fseek(fp, (long)buf->e_phoff, SEEK_SET);

		Elf64_Phdr *phead = (Elf64_Phdr*)malloc(buf->e_phentsize*buf->e_phnum);
		fread(phead, buf->e_phentsize, buf->e_phnum, fp);
		printf("----Program Header----\n");
		int i;
		for(i = 0; i < buf->e_phnum; i++) {
			if(i != 0) printf("\n");
			printf("[%d]p_type =   0x%x\n", i, phead[i].p_type);
			printf("[%d]p_flags =  0x%x\n", i, phead[i].p_flags);
			printf("[%d]p_offset = 0x%x\n", i, phead[i].p_offset);
			printf("[%d]p_vaddr =  0x%x\n", i, phead[i].p_vaddr);
			printf("[%d]p_paddr =  0x%x\n", i, phead[i].p_paddr);
			printf("[%d]p_filesz = 0x%x\n", i, phead[i].p_filesz);
			printf("[%d]p_memsz =  0x%x\n", i, phead[i].p_memsz);
			printf("[%d]p_flags =  0x%x\n", i, phead[i].p_flags);
			printf("[%d]p_align =  0x%x\n", i, phead[i].p_align);
		}
		printf("----------------------\n\n");

	}
	return 0;
}
