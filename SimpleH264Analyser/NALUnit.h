#pragma once
class CSeqParamSet;
class CPicParamSet;
	
class CNALUnit
{
public:
	CNALUnit(UINT8 * pSODB, UINT32 SODBlength);
	~CNALUnit();
	//sps
	int Parse_as_seq_param_set(CSeqParamSet *sps);
	int Parse_as_pic_param_set(CPicParamSet *pps);
	//pps
	//idr
	UINT8* Get_SODB();
	//non_idr

private:
	UINT8 * m_pSODB;
	UINT32 m_SODBlength;
};
