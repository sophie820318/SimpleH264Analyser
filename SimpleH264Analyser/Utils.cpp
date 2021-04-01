#include "stdafx.h"
#include "Utils.h"


int Get_bit_at_position(UINT8 * buf, UINT8 & bytePosition, UINT8 & bitPosition)
{
	UINT8 mask = 0, val = 0;
	mask = 1 << (7 - bitPosition);
	val = ((buf[bytePosition] & mask) != 0);
	if (++bitPosition > 7)
	{
		bytePosition++;
		bitPosition = 0;
	}
	return val;
}

//0阶指数哥伦布编码，codeNum= 2^(leadingzerobits) -1 +readbits(leadingzerobits)
int Get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
	assert(bitPosition < 8);
	UINT8 val = 0,prefixZeroCount = 0;//前置0
	int prefix = 0, surfix = 0;
	while (true)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		if (val == 0)
		{
			prefixZeroCount++;
		}
		else
		{
			break;
		}
	}
	//2^(leadingzerobits) -1
	prefix = (1 << prefixZeroCount) - 1;
	//将后面的二进制转换为10进制
	for (size_t i = 0; i < prefixZeroCount; i++)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		surfix += val*(1 << (prefixZeroCount-i-1));
	}
	prefix += surfix;
	return prefix;
}

//在有符号指数哥伦布编码的方式的基础上，增加(-1)^(K+1)*Ceil(K/2)
int Get_sev_code_num(UINT8 * buf, UINT8 & bytePosition, UINT8 & bitPosition)
{
	int uev = Get_uev_code_num(buf, bytePosition, bitPosition);
	int sign = (uev % 2) ? 1 : -1;
	//取上限 = （数加1）/2的方式
	int sev = sign*((uev + 1) >> 1);
	return sev;
}

int Get_uint_code_num(UINT8 * buf, UINT8 & bytePosition, UINT8 & bitPosition, UINT8 length)
{
	UINT32 uVal = 0;
	for (int idx = 0; idx < length; idx++)
	{
		uVal += Get_bit_at_position(buf, bytePosition, bitPosition)<<idx;
	}
	return uVal;
}
