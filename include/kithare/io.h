/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#ifndef kh_HG_IO_H
#define kh_HG_IO_H
#ifdef __cplusplus
extern "C" {
#endif

#include <kithare/arrays.h>


void khPrint(khArray_char* string);
void khPrintln(khArray_char* string);


#ifdef __cplusplus
}
#endif
#endif