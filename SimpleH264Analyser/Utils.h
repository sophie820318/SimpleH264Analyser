
#ifndef  _UTILS_H_
#define _UTILS_H_
#include "Global.h"
//�൱��helper ��
int Get_bit_at_position(UINT8 *buf,UINT8 &bytePosition, UINT8 &bitPosition);
//����޷���0�׸��ײ�ָ�����룬���ʽ
int Get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition);
//����з���ָ�����ײ����룬���ʽ
int Get_sev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition);
//
int Get_uint_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition,UINT8 length);
#endif // ! _UTILS_H_

