// SimpleH264Analyser.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Stream.h"
#include "Utils.h"

int _tmain(int argc,_TCHAR* argv[])
{
	/*UINT8 strArray[6] = { 0xA6,0x42,0x98,0xE2,0x04,0xBA };
	UINT8 bytePosition = 0, bitPosision = 0;
	UINT8 dataLengthInBits = sizeof(strArray) * 8;
	int codeNum = 0;
	while (bytePosition*8+ bitPosision<dataLengthInBits)
	{
		codeNum = Get_uev_code_num(strArray, bytePosition, bitPosision);
		printf("ExpoColumb codeNum = %d\n", codeNum);
	}
	return 0;*/

	CStreamFile h264stream(argv[1]);
	h264stream.Parse_h264_bitstream();
    return 0;
}

