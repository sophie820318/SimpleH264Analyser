
#ifndef  _UTILS_H_
#define _UTILS_H_
#include "Global.h"
//相当于helper 类
int Get_bit_at_position(UINT8 *buf,UINT8 &bytePosition, UINT8 &bitPosition);
//获得无符号0阶哥伦布指数编码，查表方式
int Get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition);
//获得有符号指数哥伦布编码，查表方式
int Get_sev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition);
//
int Get_uint_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition,UINT8 length);
#endif // ! _UTILS_H_

