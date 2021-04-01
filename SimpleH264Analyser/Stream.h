#ifndef _STREAM_H_
#define _STREAM_H_
#endif // !_STREAM_H_
//using namespace std 最好不要在cpp文件中改变使用这种方式，这样会改变所有引用cpp文件的运行上下文环境
#include <vector>
//前项声明
class CSeqParamSet;
class CPicParamSet;
class I_Slice;
class CStreamFile
{
public:
	CStreamFile(TCHAR *fileName);
	~CStreamFile();
	//Open API
	
	int Parse_h264_bitstream();

private:
	FILE *m_inputFile;
	TCHAR *m_fileName;
	////using namespace std 最好不要在cpp文件中改变使用这种方式，
	//这样会改变所有引用cpp文件的运行上下文环境
	std::vector<UINT8> m_nalVec;

	void file_info();
	void file_error(int idx);
	int find_nal_prefix();
	void ebsp_to_sodb();
	void dump_NAL_type(UINT8 nalType);
	CSeqParamSet * m_sps;
	CPicParamSet * m_pps;
	I_Slice *m_IDRSlice;
};

