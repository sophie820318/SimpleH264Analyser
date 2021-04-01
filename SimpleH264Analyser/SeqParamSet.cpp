#include "stdafx.h"
#include "SeqParamSet.h"
//#include "stdafx.h"这个东西不写会造成编译有问题，如果写在下面也会

CSeqParamSet::CSeqParamSet()
{
	memset(this, 0, sizeof(CSeqParamSet));
}

CSeqParamSet::~CSeqParamSet()
{
}

void CSeqParamSet::Set_profile_level(UINT8 profile_idc, UINT8 level_idc)
{
	m_profile_idc = profile_idc;
	m_level_idc = level_idc;
}

void CSeqParamSet::Set_sps_id(UINT8 sps_id)
{
	m_sps_id = sps_id;
}

void CSeqParamSet::Set_chroma_format_idc(UINT8 chromaFormatIdc)
{
	m_chroma_format_idc = chromaFormatIdc;
}

void CSeqParamSet::Set_bit_depth(UINT8 bit_depth_luma,UINT8 bit_depth_chroma)
{
	m_bit_depth_luma = bit_depth_luma;
	m_bit_depth_chroma = bit_depth_chroma;
}

void CSeqParamSet::Set_max_frame_num(UINT32 log2maxframeNum)
{
	m_log2_max_frame_num = log2maxframeNum;
}

void CSeqParamSet::Set_poc_type(UINT8 pocType)
{
	m_poc_type = pocType;
}

void CSeqParamSet::Set_max_poc_cnt(UINT32 maxPocCnt)
{
	m_log2_max_poc_cnt = maxPocCnt;
}

void CSeqParamSet::Set_max_num_ref_frames(UINT32 maxRefFrames)
{
	m_max_num_ref_frames = maxRefFrames;
}

void CSeqParamSet::Set_sps_multiple_flags(UINT32 flags)
{
	m_separate_colour_plane_flag = flags&(1 << 21);
	m_qpprime_y_zero_transform_bypass_flag = flags&(1 << 20);
	m_seq_scaling_matrix_present_flag = flags&(1 << 19);

	m_gaps_in_frame_num_allowed_flag = flags&(1 << 5);
	m_frame_mbs_only_flag = flags&(1 << 4);
	m_mb_adaptive_frame_field_flag = flags&(1 << 3);
	m_direct_8x8_inference_flag = flags&(1 << 2);
	m_frame_cropping_flag = flags&(1 << 1);
	m_vui_parameters_present_flag = flags&(1 << 1);
}

void CSeqParamSet::Set_pic_reslution_in_mbs(UINT16 widthInMBs, UINT16 heightInMapUnits)
{
	m_pic_width_in_mbs = widthInMBs;
	m_pic_height_in_map_units = heightInMapUnits;
	//宏块是否为真，否则是场的高度，需要原值乘以2
	m_pic_height_in_mbs = m_frame_mbs_only_flag?m_pic_height_in_map_units:2*m_pic_height_in_map_units;
}

void CSeqParamSet::Set_frame_crop_offset(UINT32 offset[4])
{
	for (int idx = 0; idx <4; idx++)
	{
		m_frame_crop_offset[idx] = offset[idx];
	}
}

bool CSeqParamSet::Get_separate_colour_plane_flag()
{
	return false;
}

UINT32 CSeqParamSet::Get_log2_max_frame_num()
{
	return m_log2_max_frame_num;
}

bool CSeqParamSet::Get_frame_mbs_only_flag()
{
	return m_frame_mbs_only_flag;
}

UINT8 CSeqParamSet::Get_poc_type()
{
	return m_poc_type;
}

UINT32 CSeqParamSet::Get_log2_max_poc_cnt()
{
	return m_log2_max_poc_cnt;
}


UINT16 CSeqParamSet::Get_pic_width_in_mbs()
{
	return m_pic_width_in_mbs;
}

UINT16 CSeqParamSet::Get_pic_height_in_mbs()
{
	return m_pic_height_in_mbs;
}
