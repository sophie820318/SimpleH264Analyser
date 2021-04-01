#ifndef _I_SLICE_H_
#define _I_SLICE_H_
//前向声明
class CSliceHeader;
class CSeqParamSet;
class CPicParamSet;

class I_Slice
{
public:
	I_Slice(UINT8 *pSODB, CSeqParamSet* sps, CPicParamSet *pps,UINT8 nalType);
	~I_Slice();
	UINT32 Parse();
private:
	UINT8 *m_pSODB;
	//是5还是1
	UINT8 m_nalType;


	CSeqParamSet * m_sps_active;
	CPicParamSet * m_pps_active;

	CSliceHeader * m_sliceHeader;

	UINT16 m_max_mb_number;
};




#endif // !_I_SLICE_H_

