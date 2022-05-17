#include <stdio.h>
#include <stdlib.h>
#include "elf.h"

int main(void){
	FILE *fp;
	char file_name[100];

	printf("Enter file name >");
	scanf("%s", file_name);
	//fprintf(stderr, "%s",file_name);
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
		printf("This is ELF file.\n");
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
	} else if (mode == 64) {
		fread(buf, sizeof(char), sizeof(Elf32_Ehdr), fp);
	}

	if(mode == 64) {
		printf("e_ident[EI_MAG0] =\t0x%x\n", buf->e_ident[EI_MAG0]);
		printf("e_ident[EI_MAG1] =\t'%c'\n", buf->e_ident[EI_MAG1]);
		printf("e_ident[EI_MAG2] =\t'%c'\n", buf->e_ident[EI_MAG2]);
		printf("e_ident[EI_MAG3] =\t'%c'\n", buf->e_ident[EI_MAG3]);
		printf("e_ident[EI_CLASS] =\t%d\n", buf->e_ident[EI_CLASS]);
		printf("e_ident[EI_DATA] =\t%d\n", buf->e_ident[EI_DATA]);
		printf("e_ident[EI_VERSION] =\t%d\n", buf->e_ident[EI_VERSION]);
		printf("e_ident[EI_PAD] =\t%d\n", buf->e_ident[EI_PAD]);
		printf("e_type =\t%d\n", buf->e_type);
		printf("e_machine =\t%d\n", buf->e_machine);
		printf("e_version =\t%d\n", buf->e_version);
		printf("e_entry =\t%p\n", buf->e_entry);
		printf("e_phoff =\t%p\n", buf->e_phoff);
		printf("e_shoff =\t%p\n", buf->e_shoff);
		printf("e_flags =\t%d\n", buf->e_flags);
		printf("e_ehsize =\t%d\n", buf->e_ehsize);
		printf("e_phentsize =\t%d\n", buf->e_phentsize);
		printf("e_phnum =\t%d\n", buf->e_phnum);
		printf("e_shentsize =\t%d\n", buf->e_shentsize);
		printf("e_shnum =\t%d\n", buf->e_shnum);
		printf("e_shstrndx =\t%d\n", buf->e_shstrndx);
	}
	return 0;
}
