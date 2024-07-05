/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Lucas Zanotti <lucas.zanotti@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Lucas Zanotti <lucas.zanotti@usp.br>
 */

/* This source file implements the kernel entry function 'kmain' called
   by the bootloader, and the command-line interpreter. Other kernel functions
   were implemented separately in another source file for legibility. */

#include "bios1.h"		/* For kwrite() etc.            */
#include "bios2.h"		/* For kread() etc.             */
#include "kernel.h"		/* Essential kernel functions.  */
#include "kaux.h"		/* Auxiliary kernel functions.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kernel's entry function. */

void kmain(void)
{
  int i, j;
  
  register_syscall_handler();	/* Register syscall handler at int 0x21.*/

  splash();			/* Uncessary spash screen.              */

  shell();			/* Invoke the command-line interpreter. */
  
  halt();			/* On exit, halt.                       */
  
}

/* Tiny Shell (command-line interpreter). */

char buffer[BUFF_SIZE];
int go_on = 1;

void shell()
{
  int i;
  clear();
  kwrite ("Oh boy, here we go again... :(\n");
  kwrite ("How can I serve you today? Enter 'help' if you need it.\n\n");

  while (go_on)
    {

      /* Read the user input. 
	 Commands are single-word ASCII tokens with no blanks. */
      do
	{
	  kwrite(PROMPT);
	  kread (buffer);
	}
      while (!buffer[0]);

      /* Check for matching built-in commands */
      
      i=0;
      while (cmds[i].funct)
	{
	  if (!strcmp(buffer, cmds[i].name))
	    {
	      cmds[i].funct();
	      break;
	    }
	  i++;
	}

      /* If the user input does not match any built-in command name, just
	 ignore and read the next command. If we were to execute external
	 programs, on the other hand, this is where we would search for a 
	 corresponding file with a matching name in the storage device, 
	 load it and transfer it the execution. Left as exercise. */
      
      if (!cmds[i].funct)
	kwrite ("Command not found. Enter 'help' if you need it.\n");
    }
}


/* Array with built-in command names and respective function pointers. 
   Function prototypes are in kernel.h. */

struct cmd_t cmds[] =
  {
    {"help",    f_help},     /* Print a help message.       */
    {"list",    f_list},     /* List files.                 */
    {"end",    f_quit},     /* Exit TyDOS.                 */
    {0, 0}
  };


/* Build-in shell command: help. */

void f_help()
{
  kwrite ("Just choose your command from the ones available below:\n\n");
  kwrite (" -> list   (all the files on disk)\n");
  kwrite (" -> end    (this pain and free this poor soul)\n");
}

void f_quit()
{
  kwrite ("I am finally FREE! :D");
  go_on = 0;
}

// Structure for the file system header
struct fs_header_t {
    unsigned char  signature[FS_SIGLEN];
    unsigned short total_number_of_sectors;
    unsigned short number_of_boot_sectors;
    unsigned short number_of_file_entries;
    unsigned short max_file_size;
    unsigned int unused_space;
} __attribute__((packed)) fs_header;

// File pointer for the volume
FILE *volume_fp = NULL;

// Function to check if volume is open
int volume_is_open() {
    if (!volume_fp) {
        printf("No open volume\n");
        return 0;
    }
    return 1;
}

// Function to check if volume has a valid TyFS header
int volume_is_fs_header() {
    if (memcmp(fs_header.signature, FS_SIGNATURE, FS_SIGLEN)) {
        printf("Fs_Header signature not found in the volume\n");
        return 0;
    }
    return 1;
}

// Function to list files in the volume
void f_list() {
    if (!volume_is_open() || !volume_is_fs_header()) {
        return;
    }

    // Seek to the beginning of the directory region
    fseek(volume_fp, fs_header.number_of_boot_sectors * 512, SEEK_SET);

    kwrite ("We currently have these files on disk:\n\n");

    // Read and print all entries
    for (int i = 0; i < fs_header.number_of_file_entries; i++) {
        char name[DIR_ENTRY_LEN];
        fread(name, DIR_ENTRY_LEN, 1, volume_fp);
        if (name[0]) {
            printf("%.*s\n", DIR_ENTRY_LEN, name);
        }
    }
}

// Function to open the volume
int open_volume(const char *volume_name) {
    volume_fp = fopen(volume_name, "r+");
    if (!volume_fp) {
        perror("Error opening volume");
        return 1;
    }

    // Read volume header
    if (fread(&fs_header, sizeof(fs_header), 1, volume_fp) != 1) {
        perror("Error reading volume header");
        return 1;
    }

    // Check if it's a valid TyFS volume
    if (!volume_is_fs_header()) {
        return 1;
    }

    return 0;
}

// Function to close the volume
void close_volume() {
    if (volume_fp) {
        fclose(volume_fp);
        volume_fp = NULL;
    }
}

/* Built-in shell command: example.

   Execute an example user program which invokes a syscall.

   The example program (built from the source 'prog.c') is statically linked
   to the kernel by the linker script (tydos.ld). In order to extend the
   example, and load and external C program, edit 'f_exec' and 'prog.c' choosing
   a different name for the entry function, such that it does not conflict with
   the 'main' function of the external program.  Even better: remove 'f_exec'
   entirely, and suppress the 'example_program' section from the tydos.ld, and
   edit the Makefile not to include 'prog.o' and 'libtydos.o' from 'tydos.bin'.

  */

extern int main();

