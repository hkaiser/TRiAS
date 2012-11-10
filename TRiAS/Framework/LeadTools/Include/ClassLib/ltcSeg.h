/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2001 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcSeg.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_SEGMENT_H_
#define  _LEAD_SEGMENT_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LSegment                                                        |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 2001                                                  |
+----------------------------------------------------------------------------*/

class LWRP_EXPORT LSegment : public LBase
{
protected:
   HSEGMENTATION m_hSeg;

private:
   static L_INT EXT_CALLBACK  MrcSegmentBitmapCS(HSEGMENTATION hSegment, L_INT nStripeNo, L_INT nStripeStartRow, L_INT nStripeEndRow, L_INT nSegmentCount, pSEGMENTDATA pSegment, L_VOID * pUserData);
   static L_INT EXT_CALLBACK  MrcEnumSegmentsCS(HSEGMENTATION hSegment, const pSEGMENTDATA pSegment, L_INT nSegId, L_VOID * pUserData);

protected:
   virtual L_INT MrcSegmentBitmapCallBack(L_INT nStripeNo, L_INT nStripeStartRow, L_INT nStripeEndRow, L_INT nSegmentCount, pSEGMENTDATA pSegment);
   virtual L_INT MrcEnumSegmentsCallBack(const pSEGMENTDATA pSegment, L_INT nSegId);

public:
   LSegment();
   virtual ~LSegment();

   L_INT MrcStartBitmapSegmentation(L_INT nWidth, L_INT nHeight, COLORREF clrBackground, COLORREF clrForeground);
   L_INT MrcEndBitmapSegmentation(L_VOID);
   L_INT MrcSegmentBitmap(LBitmapBase * pBitmap, pMINSEGMENT pMinSeg, L_UINT32 uSegFactor);
   L_INT MrcSetNewStripe(L_INT nStripeStartRow, L_INT nStripeEndRow);
   L_INT MrcSetStripeSegment(L_INT nStripeIndex, pSEGMENTDATA pSegment);
   L_INT MrcSetStripeMaxHeight(L_INT nStripeMaxHeight);
   L_INT MrcEnumSegments(L_UINT32 dwFlags);
   L_INT MrcUpdateSegmentData(L_INT nSegId, pSEGMENTDATA pSegmentData, L_BOOL bVerifyUpdate);
   L_INT MrcDeleteSegment(L_INT nSegId);
   L_INT MrcSaveBitmap(LBitmapBase * pBitmap, pCOMPRESSIONOPTIONS pCmpOption, L_CHAR * pszFileName);
   L_INT MrcSaveBitmapT44(LBitmapBase * pBitmap, pCOMPRESSIONOPTIONS pCmpOption, L_CHAR * pszFileName);
   L_INT MrcLoadBitmap(L_CHAR * pszFileName, LBitmapBase * pBitmap, L_INT nPageNo);
   L_INT MrcGetPagesCount(L_CHAR * pszFileName);
};

#endif // _LEAD_SEGMENT_H_
