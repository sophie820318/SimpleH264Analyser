#include "stdafx.h"
#include "Stream.h"
#include "NALUnit.h"
#include "SeqParamSet.h"
#include "PicParamSet.h"
#include "I_Slice.h"

#include <iostream>
using namespace std;
CStreamFile::CStreamFile(TCHAR * fileName)
{
	m_fileName = fileName;
	m_sps = NULL;
	m_pps = NULL;
	m_IDRSlice = NULL;
	file_info();
	_tfopen_s(&m_inputFile, m_fileName, _T("rb"));
	if (NULL == m_inputFile)
	{
		file_error(0);
	}
#if TRACE_CONFIG_LOGOUT
	g_traceFile.open(L"trace.txt");
	if (g_traceFile.is_open())
	{
		file_error(1);
	}
	g_traceFile << "trace file:" << endl;
#endif
}

CStreamFile::~CStreamFile()
{
	if (NULL != m_inputFile)
	{
		fclose(m_inputFile);
		m_inputFile = NULL;
	}
	if (NULL != m_sps)
	{
		delete m_sps;
		m_sps = NULL;
	}
	if (NULL != m_pps)
	{
		delete m_pps;
		m_pps = NULL;
	}
	if (NULL != m_IDRSlice)
	{
		delete m_IDRSlice;
		m_IDRSlice = NULL;
	}
#if TRACE_CONFIG_LOGOUT
	if (g_traceFile.is_open())
	{
		g_traceFile.close();
	}
#endif	
}

void CStreamFile::file_info()
{
	if (m_fileName)
	{
		wcout << L"file name:" << m_fileName << endl;
	}
}

void CStreamFile::file_error(int idx)
{
	switch (idx)
	{
	case 0:
		wcout << L"Error :opening input file failed" << endl;
		break;
	case 1:
		wcout << L"Error :opening trace file failed" << endl;
		break;
	case 2:
		wcout << L"" << endl;
		break;
	default:
		break;
	}

}

int CStreamFile::Parse_h264_bitstream()
{
	int ret = 0;
	do
	{
		ret = find_nal_prefix();
		//解析nal unit
		if (m_nalVec.size())
		{
			UINT8 nalType = m_nalVec[0] & 0x1F;
			dump_NAL_type(nalType);
			//wcout << L"NAL Unit Type:" << nalType << endl;
			ebsp_to_sodb();
			CNALUnit nalUnit(&m_nalVec[1], m_nalVec.size() - 1);
			switch (nalType)
			{
			case 5:
					//parse idr nal....
					if (m_IDRSlice)
					{
						delete m_IDRSlice;
						m_IDRSlice = NULL;
					}
					m_IDRSlice = new I_Slice(nalUnit.Get_SODB(),m_sps,m_pps,nalType);
					m_IDRSlice->Parse();
					//nalUnit.Parse_as_seq_param_set(m_IDRSlice);
					break;
			case 1:
					//parse sps
					if (m_sps)
					{
						delete m_sps;
					}
					m_sps = new CSeqParamSet;
					nalUnit.Parse_as_seq_param_set(m_sps);
					break;
				case 7:
					//parse sps
					if (m_sps)
					{
						delete m_sps;
					}
					m_sps = new CSeqParamSet;
					nalUnit.Parse_as_seq_param_set(m_sps);
					break;
				case 8:
					//parse pps
					if (m_pps)
					{
						delete m_pps;
					}
					m_pps = new CPicParamSet;
					nalUnit.Parse_as_pic_param_set(m_pps);
					break;
				default:
					break;
			}
		}
	} while (ret);
	
	return 0;
}

/*
在文件中找到一些nalu单元
*/
int CStreamFile::find_nal_prefix()
{
	UINT8 prefix[3] = { 0 };
	UINT8 fileByte;
	m_nalVec.clear();
	int pos = 0, getPrefix = 0;
	for (int idx = 0; idx < 3; idx++)
	{
		////在末尾添加值为val的元素
		prefix[idx] = getc(m_inputFile);
		m_nalVec.push_back(prefix[idx]);
	}
	while (!feof(m_inputFile))//只要不到文件头
	{
		if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
		{
			//0x 00 00 01
			////弹出尾部元素
			getPrefix = 1;
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			m_nalVec.pop_back();
			break;
		}
		else if ((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
		{
			if (1 == getc(m_inputFile))
			{
				getPrefix = 2; 
				////弹出尾部元素
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				m_nalVec.pop_back();
				break;
			}
		}
		else
		{
			fileByte = getc(m_inputFile);
			prefix[(pos++) % 3] = fileByte;
			//在末尾添加值为val的元素
			m_nalVec.push_back(fileByte);
		}
	}
	return getPrefix;
}

void CStreamFile::ebsp_to_sodb()
{
	//00 00 x x x x 03;
	if (m_nalVec.size() < 3)
	{
		return;
	}
	//增长辐为空，在函数体中
	for (vector<UINT8>::iterator itor = m_nalVec.begin()+2; itor != m_nalVec.end();)
	{
		//如果这个迭代器当前的元素为3，前面的一个元素为0，再前面元素也为0
		if ((3 == *itor) && (0 == *(itor - 1)) && (0 == *(itor - 2)))
		{
			vector<UINT8>::iterator temp = m_nalVec.erase(itor);
			itor = temp;
		}
		else
		{
			itor++;
		}
	}
}

void CStreamFile::dump_NAL_type(UINT8 nalType)
{
#if TRACE_CONFIG_CONSOLE
	wcout << L"NAL Unit Type:"<< nalType << endl;
#endif


#if TRACE_CONFIG_LOGOUT
	g_traceFile << L"NAL Unit Type:" <<to_string(nalType) << endl;
#endif
}