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


//
//函数名称: HexStrToByte
//功能描述:十六进制字符串转换为字节流
//参数： 参数1 十六进制字符buff， 参数2 存放转化字符流的buff， 参数3 十六进制字符buff的长度， 
//注意：参数2申请的存放转化字符流的buff长度需要大于等于十六进制字符buff的1/2。
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);

//函数名称: Hex2Str
//功能描述:字节流转换为十六进制字符串
//参数： 参数1 字节流原buff， 参数2 存放转化十六进制后的buff， 参数3 字节流原buff的长度， 
//注意： 参数2申请的存放十六进制的buff长度需要大于或等于原buff的2倍。
void Hex2Str(const char *source, char *dest, int sourceLen);

#endif