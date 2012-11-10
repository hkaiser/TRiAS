unit ltnetocx;

interface

const
      IDATA_IMAGE    = 0;
      IDATA_MMEDIA   = 1;
      IDATA_SOUND    = 2;
      IDATA_USER1    = 3;
      IDATA_USER2    = 4;
      IDATA_USER3    = 5;
      IDATA_USER4    = 6;

      HOST_NAME_DESCRP = 0;
      HOST_NAME_IP     = 1;

      INET_CONNECT         = 0;
      INET_DATA_READY      = 1;
      INET_CLOSE           = 2;
      INET_CONNECT_REQUEST = 3;
      INET_DATA_SENT       = 4;
      INET_DATA_SENDING    = 5;
      INET_DATA_START      = 6;
      INET_DATA_RECEIVING  = 7; 
      INET_IMAGE_RECEIVED  = 8; 
      INET_MMEDIA_RECEIVED = 9; 
      INET_SOUND_RECEIVED  = 10; 
      INET_USER1_RECEIVED  = 11; 
      INET_USER2_RECEIVED  = 12; 
      INET_USER3_RECEIVED  = 13; 
      INET_USER4_RECEIVED  = 14;

{$I LEADLock.pas}

implementation

end.
