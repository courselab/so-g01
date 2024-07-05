/*
 *    SPDX-FileCopyrightText: 2024 Lucas Zanotti <lucas.zanotti@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */
#include "tydos.h"

int main()
{    
  char name[64]
  
  puts ("Enter your name:\n");
  
  gets(name);
  
  puts ("Hello ");
  puts(name);
  puts("!\n");
  
  return 0;
}