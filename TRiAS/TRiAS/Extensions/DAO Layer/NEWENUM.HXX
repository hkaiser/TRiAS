// BScript-Erweiterung (DaoLayer) ---------------------------------------------
// File: DAOEXTF.CPP

#if !defined(_DAOEXTF_H)
#define _DAOEXTF_H

void WorkSpaces_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void WorkSpace_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Errors_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Databases_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDefs_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Fields_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Indexes_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Containers_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Documents_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDefs_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSets_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameters_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Properties_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relations_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Groups_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Users_NewEnum_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Next_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _BSCREXTF_H
