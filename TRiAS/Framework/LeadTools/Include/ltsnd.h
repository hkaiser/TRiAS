#ifndef _LTSND_H_
#define _LTSND_H_

/* general waveform format structure (information common to all formats) */
typedef struct capwaveformat_tag {
    L_UINT16   wFormatTag;        /* format type */
    L_UINT16   nChannels;         /* number of channels (i.e. mono, stereo...) */
    L_UINT32   nSamplesPerSec;    /* sample rate */
    L_UINT32   nAvgBytesPerSec;   /* for buffer estimation */
    L_UINT16   nBlockAlign;       /* block size of data */
} CAPWAVEFORMAT, FAR  *LPCAPWAVEFORMAT;


/* waveform format structure for PCM data */
typedef struct cappcmwaveformat_tag {
    CAPWAVEFORMAT  wf;
    L_UINT16       wBitsPerSample;
} CAPPCMWAVEFORMAT, FAR  *LPCAPPCMWAVEFORMAT;


/* waveform format structure for MS ADPCM */

typedef struct capadpcmcoef_tag {
        L_INT16   iCoef1;
        L_INT16   iCoef2;
} CAPADPCMCOEFSET;

/*
 *  this pragma disables the warning issued by the Microsoft C compiler
 *  when using a zero size array as place holder when compiling for
 *  C++ or with -W4.
 *
 */
#ifdef _MSC_VER
#pragma warning(disable:4200)
#endif

typedef struct capadpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16            wSamplesPerBlock;
        L_UINT16            wNumCoef;
        CAPADPCMCOEFSET    aCoef[];
} CAPADPCMWAVEFORMAT, L_FAR  *LPCAPADPCMWAVEFORMAT;

#ifdef _MSC_VER
#pragma warning(default:4200)
#endif


//
//  Intel's DVI ADPCM structure definitions
//
//      for CAP_WAVE_FORMAT_DVI_ADPCM   (0x0011)
//
//

typedef struct capdvi_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16            wSamplesPerBlock;
} CAPDVIADPCMWAVEFORMAT, L_FAR  *LPCAPDVIADPCMWAVEFORMAT;

//
//  IMA endorsed ADPCM structure definitions--note that this is exactly
//  the same format as Intel's DVI ADPCM.
//
//      for CAP_WAVE_FORMAT_IMA_ADPCM   (0x0011)
//
//

typedef struct capima_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wSamplesPerBlock;
} CAPIMAADPCMWAVEFORMAT, L_FAR  *LPCAPIMAADPCMWAVEFORMAT;

/*
//VideoLogic's Media Space ADPCM Structure definitions
// for  CAP_WAVE_FORMAT_MEDIASPACE_ADPCM    (0x0012)
//
//
*/
typedef struct capmediaspace_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPMEDIASPACEADPCMWAVEFORMAT, L_FAR      *LPCAPMEDIASPACEADPCMWAVEFORMAT;

//
//  Sierra Semiconductor
//
//      for CAP_WAVE_FORMAT_SIERRA_ADPCM   (0x0013)
//
//

typedef struct capsierra_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPSIERRAADPCMWAVEFORMAT, L_FAR       *LPCAPSIERRAADPCMWAVEFORMAT;

//
//  Antex Electronics  structure definitions
//
//      for CAP_WAVE_FORMAT_G723_ADPCM   (0x0014)
//
//

typedef struct capg723_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        cbExtraSize;
        L_UINT16        nAuxBlockSize;
} CAPG723_ADPCMWAVEFORMAT, L_FAR  *LPCAPG723_ADPCMWAVEFORMAT;

//
//  DSP Solutions (formerly DIGISPEECH) structure definitions
//
//      for CAP_WAVE_FORMAT_DIGISTD   (0x0015)
//
//

typedef struct capdigistdwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAP_DIGISTDWAVEFORMAT, L_FAR  *LPCAPDIGISTDWAVEFORMAT;

//
//  DSP Solutions (formerly DIGISPEECH) structure definitions
//
//      for CAP_WAVE_FORMAT_DIGIFIX   (0x0016)
//
//

typedef struct capdigifixwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPDIGIFIXWAVEFORMAT, L_FAR  *LPCAPDIGIFIXWAVEFORMAT;

//
//   Dialogic Corporation
// CAP_WAVE_FORMAT_DIALOGIC_OKI_ADPCM   (0x0017)
//
typedef struct capcreative_fastspeechformat_tag{
        WAVEFORMATDATA  ewf;
}CAPDIALOGICOKIADPCMWAVEFORMAT, L_FAR  *LPCAPDIALOGICOKIADPCMWAVEFORMAT;

//
//  Yamaha Compression's ADPCM structure definitions
//
//      for CAP_WAVE_FORMAT_YAMAHA_ADPCM   (0x0020)
//
//

typedef struct capyamaha_adpmcwaveformat_tag {
        WAVEFORMATDATA  wfx;
        
} CAPYAMAHA_ADPCMWAVEFORMAT, L_FAR  *LPCAPYAMAHA_ADPCMWAVEFORMAT;

//
//  Speech Compression's Sonarc structure definitions
//
//      for CAP_WAVE_FORMAT_SONARC   (0x0021)
//
//

typedef struct capsonarcwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wCompType;
} CAPSONARCWAVEFORMAT, L_FAR  *LPCAPSONARCWAVEFORMAT;

//
//  DSP Groups's TRUESPEECH structure definitions
//
//      for CAP_WAVE_FORMAT_DSPGROUP_TRUESPEECH   (0x0022)
//
//

typedef struct captruespeechwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
        L_UINT16        nSamplesPerBlock;
        L_UCHAR         abReserved[28];
} CAPTRUESPEECHWAVEFORMAT, L_FAR  *LPCAPTRUESPEECHWAVEFORMAT;

//
//  Echo Speech Corp structure definitions
//
//      for CAP_WAVE_FORMAT_ECHOSC1   (0x0023)
//
//

typedef struct capechosc1waveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPECHOSC1WAVEFORMAT, L_FAR  *LPCAPECHOSC1WAVEFORMAT;

//
//  Audiofile Inc.structure definitions
//
//      for CAP_WAVE_FORMAT_AUDIOFILE_AF36   (0x0024)
//
//

typedef struct capaudiofile_af36waveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPAUDIOFILE_AF36WAVEFORMAT, L_FAR  *LPCAPAUDIOFILE_AF36WAVEFORMAT;

//
//  Audio Processing Technology structure definitions
//
//      for CAP_WAVE_FORMAT_APTX   (0x0025)
//
//

typedef struct capaptxwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPAPTXWAVEFORMAT, L_FAR  *LPCAPAPTXWAVEFORMAT;

//
//  Audiofile Inc.structure definitions
//
//      for CAP_WAVE_FORMAT_AUDIOFILE_AF10   (0x0026)
//
//

typedef struct capaudiofile_af10waveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPAUDIOFILE_AF10WAVEFORMAT, L_FAR  *LPCAPAUDIOFILE_AF10WAVEFORMAT;

//
// Dolby's AC-2 structure definition
//
//      for CAP_WAVE_FORMAT_DOLBY_AC2    (0x0030)
//
//

typedef struct capdolbyac2waveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        nAuxBitsCode;
} CAPDOLBYAC2WAVEFORMAT, L_FAR*LPCAPDOLBYAC2WAVEFORMAT;

//
// Microsoft structure definition
//
//      for CAP_WAVE_FORMAT_GSM 610       (0x0031)
//
//

typedef struct capgsm610waveformat_tag {
WAVEFORMATDATA  wfx;
L_UINT16        wSamplesPerBlock;
} CAPGSM610WAVEFORMAT, L_FAR     *LPCAPGSM610WAVEFORMAT;

//
//      Antex Electronics Corp structure definition
//
//      for CAP_WAVE_FORMAT_ADPCME                  (0x0033)
//
//

typedef struct capadpcmewaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wSamplesPerBlock;
} CAPADPCMEWAVEFORMAT, L_FAR    *LPCAPADPCMEWAVEFORMAT;

//
//       Control Resources Limited structure definition
//
//       for CAP_WAVE_FORMAT_CONTROL_RES_VQLPC      (0x0034)
//
//

typedef struct capcontres_vqlpcwaveformat_tag {
         WAVEFORMATDATA    wfx;
         L_UINT16          wSamplesPerBlock;
} CAPCONTRESVQLPCWAVEFORMAT, L_FAR       *LPCAPCONTRESVQLPCWAVEFORMAT;

//
//
//
//      for CAP_WAVE_FORMAT_DIGIREAL                   (0x0035)
//
//

typedef struct capdigirealwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wSamplesPerBlock;
} CAPDIGIREALWAVEFORMAT, L_FAR *LPCAPDIGIREALWAVEFORMAT;

//
//  DSP Solutions
//
//      for CAP_WAVE_FORMAT_DIGIADPCM   (0x0036)
//
//

typedef struct capdigiadpcmmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wSamplesPerBlock;
} CAPDIGIADPCMWAVEFORMAT, L_FAR  *LPCAPDIGIADPCMWAVEFORMAT;

//
//       Control Resources Limited structure definition
//
//       for CAP_WAVE_FORMAT_CONTROL_RES_CR10     (0x0037)
//
//

typedef struct capcontres_cr10waveformat_tag {
      WAVEFORMATDATA  wfx;
      L_UINT16        wSamplesPerBlock;
} CAPCONTRESCR10WAVEFORMAT, L_FAR        *LPCAPCONTRESCR10WAVEFORMAT;

//
//  Natural Microsystems
//
//      for CAP_WAVE_FORMAT_NMS_VBXADPCM   (0x0038)
//
//

typedef struct capnms_vbxadpcmmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wSamplesPerBlock;
} CAPNMS_VBXADPCMWAVEFORMAT, L_FAR  *LPCAPNMS_VBXADPCMWAVEFORMAT;

//
//  Antex Electronics  structure definitions
//
//      for CAP_WAVE_FORMAT_G721_ADPCM   (0x0040)
//
//

typedef struct capg721_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        nAuxBlockSize;
} CAPG721_ADPCMWAVEFORMAT, L_FAR  *LPCAPG721_ADPCMWAVEFORMAT;

//
//
// Microsoft MPEG audio WAV definition
//
// for  CAP_WAVE_FORMAT_MPEG.   (0x0050)
//
//      MPEG-1 audio wave format (audio layer only)
//
//

typedef struct capmpeg1waveformat_tag {
    WAVEFORMATDATA  wfx;
    L_UINT16        fwHeadLayer;
    L_UINT32        dwHeadBitrate;
    L_UINT16        fwHeadMode;
    L_UINT16        fwHeadModeExt;
    L_UINT16        wHeadEmphasis;
    L_UINT16        fwHeadFlags;
    L_UINT32        dwPTSLow;
    L_UINT32        dwPTSHigh;
} CAPMPEG1WAVEFORMAT, L_FAR            *LPCAPMPEG1WAVEFORMAT;

#define CAP_ACM_MPEG_LAYER1             (0x0001)
#define CAP_ACM_MPEG_LAYER2             (0x0002)
#define CAP_ACM_MPEG_LAYER3             (0x0004)
#define CAP_ACM_MPEG_STEREO             (0x0001)
#define CAP_ACM_MPEG_JOINTSTEREO        (0x0002)
#define CAP_ACM_MPEG_DUALCHANNEL        (0x0004)
#define CAP_ACM_MPEG_SINGLECHANNEL      (0x0008)
#define CAP_ACM_MPEG_PRIVATEBIT         (0x0001)
#define CAP_ACM_MPEG_COPYRIGHT          (0x0002)
#define CAP_ACM_MPEG_ORIGINALHOME       (0x0004)
#define CAP_ACM_MPEG_PROTECTIONBIT      (0x0008)
#define CAP_ACM_MPEG_ID_MPEG1           (0x0010)

//
//  Creative's ADPCM structure definitions
//
//      for CAP_WAVE_FORMAT_CREATIVE_ADPCM   (0x0200)
//
//

typedef struct capcreative_adpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPCREATIVEADPCMWAVEFORMAT, L_FAR  *LPCAPCREATIVEADPCMWAVEFORMAT;

//
//    Creative FASTSPEECH structure definition
//
//       for CAP_WAVE_FORMAT_CREATIVE_FASTSPEECH8   (0x0202)
//
//

typedef struct capcreative_fastspeech8format_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPCREATIVEFASTSPEECH8WAVEFORMAT, L_FAR  *LPCAPCREATIVEFASTSPEECH8WAVEFORMAT;

//
//    Creative FASTSPEECH structure definition
//
//       for CAP_WAVE_FORMAT_CREATIVE_FASTSPEECH10   (0x0203)
//
//

typedef struct capcreative_fastspeech10format_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPCREATIVEFASTSPEECH10WAVEFORMAT, L_FAR  *LPCAPCREATIVEFASTSPEECH10WAVEFORMAT;

//
//  Fujitsu FM Towns 'SND' structure
//
//      for CAP_WAVE_FORMAT_FMMTOWNS_SND   (0x0300)
//
//

typedef struct capfmtowns_snd_waveformat_tag {
        WAVEFORMATDATA  wfx;
        L_UINT16        wRevision;
} CAPFMTOWNS_SND_WAVEFORMAT, L_FAR  *LPCAPFMTOWNS_SND_WAVEFORMAT;

//
//  Olivetti structure
//
//      for CAP_WAVE_FORMAT_OLIGSM   (0x1000)
//
//

typedef struct capoligsmwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPOLIGSMWAVEFORMAT, L_FAR  *LPCAPOLIGSMWAVEFORMAT;

//
//  Olivetti structure
//
//      for CAP_WAVE_FORMAT_OLIADPCM   (0x1001)
//
//

typedef struct capoliadpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPOLIADPCMWAVEFORMAT, L_FAR  *LPCAPOLIADPCMWAVEFORMAT;

//
//  Olivetti structure
//
//      for CAP_WAVE_FORMAT_OLICELP   (0x1002)
//
//

typedef struct capolicelpwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPOLICELPWAVEFORMAT, L_FAR  *LPCAPOLICELPWAVEFORMAT;

//
//  Olivetti structure
//
//      for CAP_WAVE_FORMAT_OLISBC   (0x1003)
//
//

typedef struct capolisbcwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPOLISBCWAVEFORMAT, L_FAR  *LPCAPOLISBCWAVEFORMAT;

//
//  Olivetti structure
//
//      for CAP_WAVE_FORMAT_OLIOPR   (0x1004)
//
//

typedef struct capolioprwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPOLIOPRWAVEFORMAT, L_FAR  *LPCAPOLIOPRWAVEFORMAT;

//
//  Crystal Semiconductor IMA ADPCM format
//
//      for CAP_WAVE_FORMAT_CS_IMAADPCM   (0x0039)
//
//

typedef struct capcsimaadpcmwaveformat_tag {
        WAVEFORMATDATA  wfx;
} CAPCSIMAADPCMWAVEFORMAT, L_FAR  *LPCAPCSIMAADPCMWAVEFORMAT;





#endif //_LTSND_H_
