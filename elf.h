#include <stdint.h>

#ifndef INCLUDE_ELF_H
#define INCLUDE_ELF_H

#define EI_MAG0 		(0)
#define EI_MAG1 		(1)
#define EI_MAG2 		(2)
#define EI_MAG3 		(3)
#define EI_CLASS 		(4)
#define EI_DATA 		(5)
#define EI_VERSION	(6)
#define EI_PAD 			(7)
#define EI_NIDENT 	(16)

#define ELFCLASSNONE	(0)
#define ELFCLASS32		(1)
#define ELFCLASS64		(2)

#define ELFDATANONE		(0)
#define ELFDATA2LSB		(1)
#define ELFDATA2MSB		(2)

#define ET_NONE		(0)
#define ET_REL		(1)
#define ET_EXEC		(2)
#define ET_DYN		(3)
#define ET_CORE		(4)
#define ET_LOPROC	(0xff00)
#define ET_HIPROC	(0xffff)

#define EM_NONE		(0)
#define EM_M32		(1)
#define EM_SPARC	(2)
#define EM_386		(3)
#define EM_68K		(4)
#define EM_88K		(5)
#define EM_486		(6)
#define EM_860		(7)
#define EM_MIPS		(8)
#define EM_MIPS_RS3_LE (10)
#define EM_RS6000	(11)
#define EM_PA_RISC (15)
#define EM_nCUBE	(16)
#define EM_VPP500 (17)
#define EM_SPARC32PLUS (18)
#define EM_PPC		(20)
#define EM_SPARCV9 (43)

typedef uint32_t	Elf32_Addr;
typedef uint16_t	Elf32_Half;
typedef uint32_t	Elf32_Off;
typedef int32_t 	Elf_Sword;
typedef uint32_t	Elf32_Word;

typedef uint64_t	Elf64_Addr;
typedef uint16_t	Elf64_Half;
typedef uint64_t	Elf64_Off;
typedef int32_t 	Elf64_Sword;
typedef uint32_t 	Elf64_Word;
typedef uint64_t 	Elf64_Xword;
typedef int64_t 	Elf64_Sxword;

typedef struct {
	unsigned char	e_ident[EI_NIDENT];
	Elf32_Half		e_type;
	Elf32_Half		e_machne;
	Elf32_Word		e_version;
	Elf32_Addr		e_entry;
	Elf32_Off			e_phoff;
	Elf32_Off			e_shoff;
	Elf32_Word		e_flags;
	Elf32_Half		e_ehsize;
	Elf32_Half		e_phentsize;
	Elf32_Half		e_phnum;
	Elf32_Half		e_shentsize;
	Elf32_Half		e_shnum;
	Elf32_Half		e_shstrndx;
}	Elf32_Ehdr;
	
typedef struct {
	unsigned char	e_ident[EI_NIDENT];
	Elf64_Half		e_type;
	Elf64_Half		e_machine;
	Elf64_Word		e_version;
	Elf64_Addr		e_entry;
	Elf64_Off			e_phoff;
	Elf64_Off			e_shoff;
	Elf64_Word		e_flags;
	Elf64_Half		e_ehsize;
	Elf64_Half		e_phentsize;
	Elf64_Half		e_phnum;
	Elf64_Half		e_shentsize;
	Elf64_Half		e_shnum;
	Elf64_Half		e_shstrndx;
} Elf64_Ehdr;

	
#endif /*INCLUDE_ELF_H*/
