/*
 * Copyright (C)2015 Haxe Foundation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifdef __GNUC__
#ifdef ABI_ELF
#	define SEPARATE_SECTION_FOR_BYTECODE
#endif
#endif

/* None of this is needed on non-ELF platforms... */
#ifdef SEPARATE_SECTION_FOR_BYTECODE

#include <stdio.h>
#include <elf.h>
#include <neko.h>


value elf_read_header(FILE *exe);

int elf_is_32();

value elf_read_section(FILE *exe, int sec, char *buf);
value elf_write_section(FILE *exe, int sec, char *buf);

int elf_find_bytecode_section(FILE *exe);

void elf_free_section_string_table();


value elf_find_embedded_bytecode(const char *file, int *beg, int *end);
int elf_find_bytecode_section(FILE *exe);


#define elf_get_Ehdr(p,f)   (elf_is_32() ? ((Elf32_Ehdr*)p)->f : ((Elf64_Ehdr*)p)->f)
#define elf_get_Shdr(p,f)   (elf_is_32() ? ((Elf32_Shdr*)p)->f : ((Elf64_Shdr*)p)->f)

#define elf_set_Ehdr(p,f,v) { if (elf_is_32()) ((Elf32_Ehdr*)p)->f = v; else ((Elf64_Ehdr*)p)->f = v; }
#define elf_set_Shdr(p,f,v) { if (elf_is_32()) ((Elf32_Shdr*)p)->f = v; else ((Elf64_Shdr*)p)->f = v; }


extern int size_Ehdr; /* Big enough to hold Elf32_Ehdr or Elf64_Ehdr... */
extern int size_Shdr; /* Big enough to hold Elf32_Shdr or Elf64_Shdr... */


#endif
