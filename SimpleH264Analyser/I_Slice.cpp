//貌似的经验是在实现的地方才开始引入使用到的包含
#include "stdafx.h"
#include "I_Slice.h"
#include "SliceHeader.h"
#include "SeqParamSet.h"


I_Slice::I_Slice(UINT8 *pSODB, CSeqParamSet* sps, CPicParamSet *pps, UINT8 nalType)
{
	memset(this, 0, sizeof(I_Slice));
	m_pSODB = pSODB;
	m_sps_active = sps;
	m_pps_active = pps;
	m_nalType = nalType;
	m_max_mb_number = m_sps_active->Get_pic_width_in_mbs() * m_sps_active->Get_pic_height_in_mbs();
}

I_Slice::~I_Slice()
{
	if (NULL != m_sliceHeader)
	{
		delete m_sliceHeader;
		m_sliceHeader = NULL;
	}
}

UINT32 I_Slice::Parse()
{
	m_sliceHeader = new	 CSliceHeader(m_pSODB, m_sps_active, m_pps_active, m_nalType);
	m_sliceHeader->Parse_slice_header();
	return 0;
}