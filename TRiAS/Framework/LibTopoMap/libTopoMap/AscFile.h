#ifndef __ASC_FILE_H__
#define __ASC_FILE_H__

/////////////////////////////////////////////////////////////////////////////
// ASC-File-Export

class ASC_HEADER {
public:
	CString	m_strCoordTrans;
	double	m_dwOffsetX;
	double	m_dwOffsetY;
	double	m_dwScale11;
	double	m_dwScale12;
	double	m_dwScale21;
	double	m_dwScale22;

	void Init();
	ASC_HEADER& operator=( const ASC_HEADER& hdr );
};

#endif // __ASC_FIEL_H__