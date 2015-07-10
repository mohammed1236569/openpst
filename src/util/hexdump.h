/**
* LICENSE PLACEHOLDER
*
* @file hexdump.h
* @package OpenPST
* @brief hexdump helper functions
*
* @author Gassan Idriss <ghassani@gmail.com>
* @author https://github.com/posixninja/DLOADTool
*/

#ifndef _UTIL_HEXDUMP_H
#define _UTIL_HEXDUMP_H

#include "include/definitions.h"
#include <iostream>
#include <stdio.h>

#ifdef QT_CORE_LIB
#include <QVariant>
#endif

#define hexdump_tx(data, amount) \
            do { if (DEBUG_ENABLED) printf("Dumping %lu bytes written\n", amount); hexdump(data, amount); } while (0)
   
#define hexdump_rx(data, amount) \
            do { if (DEBUG_ENABLED) printf("Dumping %lu bytes read\n", amount); hexdump(data, amount); } while (0)

const char hex_trans[] =
    "................................ !\"#$%&'()*+,-./0123456789"
    ":;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklm"
    "nopqrstuvwxyz{|}~...................................."
    "....................................................."
    "........................................";

void hexdump(unsigned char *data, unsigned int amount);

#ifdef QT_CORE_LIB
void hexdump(unsigned char *data, unsigned int amount, QString& out);
#endif

#endif
