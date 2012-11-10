#ifndef _TMPLMAN_H
#define _TMPLMAN_H

class CTemplateManagement
{
public:
	CTemplateManagement();
	~CTemplateManagement();

	HRESULT Load			(int iResID, LPSTR lpstrType);
	HRESULT Set				(LPSTR lpstrTemplate) ;
	HRESULT GetComment			(LPSTR lpstr, int iLen);
	HRESULT GetType			(LPSTR lpstr, int iLen);
	HRESULT GetDeclaration	(LPSTR lpstr, int iLen);
	HRESULT GetName			(LPSTR lpstr, int iLen);
	HRESULT GetParams		(LPSTR lpstr, int iLen);
	int		GetResID()		{ return m_iResID; }

private:
	int m_iResID;
	CString m_strTemplate;
	CString m_strComment;

	HRESULT LoadFunction		(int iResID, LPCSTR lpcstrTemplateType, LPSTR lpstr, int iLen, LPSTR lpstr2, int iLen2);
	HRESULT GetFunctionName		(LPSTR lpstr, int iLen);
	HRESULT GetFunctionType		(LPSTR lpstr, int iLen);
	HRESULT GetFnctDeclaration	(LPSTR lpstr, int iLen);
	HRESULT GetFnctParams		(LPSTR lpstr, int iLen);
};

#endif //_TMPLMAN_H
