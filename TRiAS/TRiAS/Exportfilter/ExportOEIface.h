///////////////////////////////////////////////////////////////////////////////
// Interfacefunktionen die von den Exportmodulen im alten Stil bereitgestellt
// werden müssen

ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode, HWND, LPCTSTR lpszDatasource );
ErrCode ExportComment (OFSTRUCT &of, const char *lpCommentString);
ErrCode ExportHeader (OFSTRUCT &of, const char *lpHeaderString);
ErrCode ExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);
ErrCode ExportDescriptionEx (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo, DWORD dwStyle);

// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO );
//ErrCode ExportIDDescription(char* lpszOKS, char* lpszShortDescription, char* lpszLongDescription, long lVisType, DWORD * pVis);
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO ,long lIdent);
ErrCode ExportIDDescription(char* lpszOKS, char* lpszShortDescription, char* lpszLongDescription, long lVisType, DWORD * pVis, long lIdent);

ErrCode ExportMerkmalDescription(long lMCode, char *pBuf, short ityp, short iLen );
ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, LPCTSTR pUniqueIdent, LPCTSTR lpszGUID, LPCTSTR pParentClass );
ErrCode ExportTrailer (OFSTRUCT &of, const char *lpTrailerString);
ErrCode ExportEnd (OFSTRUCT &of);
short GetExportCaps (ExportCapability);
ErrCode ExportBreak (OFSTRUCT &of);
