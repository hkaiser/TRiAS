unit LTISIOCX;
interface

const
   {ISISFlagsConstants}
   ISIS_SHOWUI       = $0001;
   ISIS_MULTI_NOSAVE = $0002;

   {ISISTagConstants}
   TAG_XRESOLUTION =                $011A;
   TAG_YRESOLUTION =                $011B;
   TAG_XPOSITION =                  $011E;
   TAG_YPOSITION =                  $011F;
   TAG_IMAGELENGTH =                $0101;
   TAG_IMAGEWIDTH =                 $0100;

   TAG_FEEDER =                     $0503;
      TAG_FEEDER_FEED =                $00000001;
      TAG_FEEDER_FLAT =                $00000002;
      TAG_FEEDER_MANUAL =              $00000004;
      TAG_FEEDER_TELLFEED =            $00010000;
      TAG_FEEDER_TELLFLAT =            $00020000;
      TAG_FEEDER_TELLSCAN =            $00040000;
      TAG_FEEDER_CENTERFEED =          $00080000;
      TAG_FEEDER_CENTERFLAT =          $00100000;
      TAG_FEEDER_PAUSE =               $00200000;

   TAG_SAMPLESPERPIXEL =            $0115;

   TAG_BITSPERSAMPLE =              $0102;

   TAG_CONTRAST =                   $0501;
      TAG_CONTRAST_AUTO =              0;

   TAG_BRIGHTNESS =                 $0502;
      TAG_BRIGHTNESS_AUTO =            -3;
      TAG_BRIGHTNESS_DARKEN =          -2;
      TAG_BRIGHTNESS_NORM =            -1;
      TAG_BRIGHTNESS_LIGHTEN =         0;

   TAG_COMPRESSION =                $0103;
      TAG_COMPRESSION_NONE =           1;
      TAG_COMPRESSION_MG3 =            2;
      TAG_COMPRESSION_G3 =             3;
      TAG_COMPRESSION_G4 =             4;
      TAG_COMPRESSION_LZW =            5;
      TAG_COMPRESSION_JPEG =           6;
      TAG_COMPRESSION_PACK =           32773;
      TAG_COMPRESSION_32771 =          32771;
      TAG_COMPRESSION_JBIG =           34661;
      TAG_COMPRESSION_PCX =            50000;
      TAG_COMPRESSION_4BYTE =          50001;
      TAG_COMPRESSION_GIF =            50005;
      TAG_COMPRESSION_BMP =            50006;

   TAG_PLANARCONFIGURATION =        $011c;
      TAG_PLANARCONFIG_LINE =          1;
      TAG_PLANARCONFIG_LINE_PACK =     1;
      TAG_PLANARCONFIG_PAGE =          2;
      TAG_PLANARCONFIG_LINE_UNPACK =   5000;

   TAG_SCANORIENTATION =            $0113;
      TAG_SCANORIENTATION_PORT =   1;
      TAG_SCANORIENTATION_LAND =   2;
      TAG_SCANORIENTATION_180 =    3;
      TAG_SCANORIENTATION_270 =    4;
      TAG_SCANORIENTATION_PORTM =  5;
      TAG_SCANORIENTATION_LANDM =  6;
      TAG_SCANORIENTATION_180M =   7;
      TAG_SCANORIENTATION_270M =   8;

   TAG_MAXPAGES =                   $0504;

   TAG_SCANAHEAD =                  $050d;
      TAG_SCANAHEAD_NO =               0;
      TAG_SCANAHEAD_YES =              1;

   TAG_GAMMA =                      $050f;
      TAG_GAMMA_NORMAL =               $0;
      TAG_GAMMA_AUTO =                 $0;
      TAG_GAMMA_DOWNLOAD1 =            $1;
      TAG_GAMMA_DOWNLOAD2 =            $2;
      TAG_GAMMA_DOWNLOAD3 =            $3;
      TAG_GAMMA_DOWNLOAD4 =            $4;
      TAG_GAMMA_DOWNLOAD5 =            $5;
      TAG_GAMMA_DOWNLOAD6 =            $6;
      TAG_GAMMA_CRT =                  $7;
      TAG_GAMMA_BOTTOMCLIP =           (-3);
      TAG_GAMMA_1TO1INVERT =           (-2);
      TAG_GAMMA_SCURVE =               (-1);
      TAG_GAMMA_SHARP_61 =             1;
      TAG_GAMMA_SHARP_67 =             2;
      TAG_GAMMA_SHARP_75 =             3;
      TAG_GAMMA_SHARP_87 =             4;
      TAG_GAMMA_1TO1 =                 5;
      TAG_GAMMA_BLUR_1_20 =            6;
      TAG_GAMMA_BLUR_1_45 =            7;
      TAG_GAMMA_BLUR_1_78 =            8;
      TAG_GAMMA_BLUR_2_20 =            9;

   TAG_SCANAHEAD_MAXPAGES = $057c;

   TAG_SCANTYPE                 = $0514;   {specifies the scanning source}
      TAG_SCANTYPE_AUTOMATIC    =      $0000;  {default - scan from ADF if pages are detected, otherwise scan from flatbed}
      TAG_SCANTYPE_TRANSPARENCY =      $0001;  {scan from the transparency unit}
      TAG_SCANTYPE_FLATBED      =      $0002;  {scan from the flatbed}
      TAG_SCANTYPE_FEEDER       =      $0003;  {scan only the front side of the page from the feeder}
      TAG_SCANTYPE_FRONTONLY    =      $0003;  {scan only the front side of the page from the feeder}
      TAG_SCANTYPE_DUPLEX       =      $0004;  {scan in duplex mode from the feeder}
      TAG_SCANTYPE_FRONTBACK    =      $0004;  {scan in duplex mode from the feeder}
      TAG_SCANTYPE_BACKFRONT    =      $0005;  {scan in duplex and return back side of the page first from the feeder}
      TAG_SCANTYPE_BACKONLY     =      $0006;  {scan only the back side of the page from the feeder}


   TAG_PHOTOMETRICINTERPRETATION =$0106;
      TAG_PHOTOMETRIC_WHITE0    =      $0000;
      TAG_PHOTOMETRIC_WHITE1    =      $0001;
      TAG_PHOTOMETRIC_RGB       =      $0002;
      TAG_PHOTOMETRIC_PALETTE   =      $0003;
      TAG_PHOTOMETRIC_BGR       =      $0120;

   TAG_PAGESIZE                  =$050e;

   ISIS_DEFAULT = -99;

{$I LEADLock.pas}

implementation
end.

