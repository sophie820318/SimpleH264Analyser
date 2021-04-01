#ifndef _STREAM_H_
#define _STREAM_H_
#endif // !_STREAM_H_
//using namespace std ��ò�Ҫ��cpp�ļ��иı�ʹ�����ַ�ʽ��������ı���������cpp�ļ������������Ļ���
#include <vector>
//ǰ������
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
	////using namespace std ��ò�Ҫ��cpp�ļ��иı�ʹ�����ַ�ʽ��
	//������ı���������cpp�ļ������������Ļ���
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

