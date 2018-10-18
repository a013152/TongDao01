#ifndef _COMMNIFUN_H
#define _COMMNIFUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//base64编码
char *encode(const char *buf, const long size, char *base64Char);


//base64解码
char *decode(const char *base64Char, const long base64CharSize, char *originChar, long originCharSize);


//十六进制字符串转换为字节流
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);

//字节流转换为十六进制字符串的另一种实现方式
void Hex2Str(const char *source, char *dest, int sourceLen);

#endif