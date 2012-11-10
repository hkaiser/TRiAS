	enum InetDataTypes
   {
      INETDATA_IMAGE    = 0,
      INETDATA_MMEDIA   = 1,
      INETDATA_SOUND    = 2,
      INETDATA_USER1    = 3,
      INETDATA_USER2    = 4,
      INETDATA_USER3    = 5,
      INETDATA_USER4    = 6,
      INETDATA_COMMAND  = 7,
      INETDATA_RESPONSE = 8,
      INETDATA_LAST,
   };

   typedef enum
   {
      PARAM_TYPE_INT32,
      PARAM_TYPE_UINT32,
      PARAM_TYPE_CHAR,
      PARAM_TYPE_UCHAR,
      PARAM_TYPE_STRING,
      PARAM_TYPE_LONG,
      PARAM_TYPE_UINT16,
      PARAM_TYPE_INT16,
      PARAM_TYPE_USTRING,
   } InetParamType;

   typedef enum
   {
      INETCMD_LOAD                  = 0,
      INETCMD_SAVE                  = 1,
      INETCMD_CREATE_WIN            = 2,
      INETCMD_SIZE_WIN              = 3,
      INETCMD_CLOSE_WIN             = 4,
      INETCMD_SHOW_WIN              = 5,
      INETCMD_SET_RECT              = 6,
      INETCMD_SEND_ANN              = 7,
      INETCMD_ATTACH_BITMAP         = 8,
      INETCMD_FREE_BITMAP           = 9,
	   INETCMD_GET_MAGGLASS_DATA     = 10,
      INETCMD_USER_REG              = 10000,
      INETCMD_USER_CUSTOM           = 20000,
   } InetCmdType;

   typedef enum
   {
      DISPLAY_RECT_SRC,      /* source            */
      DISPLAY_RECT_SRCCLIP,  /* source clip       */
      DISPLAY_RECT_DST,      /* destination       */ 
      DISPLAY_RECT_DSTCLIP   /* destination clip  */
   } DisplayRectType;

   enum InetAddressType
   {
      HOST_NAME_DESCRP = 0,
      HOST_NAME_IP     = 1,
   };

   enum InetMessageType
   {
      INET_CONNECT = 0,
      INET_DATA_READY = 1,
      INET_CLOSE = 2,
      INET_CONNECT_REQUEST = 3,
      INET_DATA_SENT = 4,
      INET_DATA_SENDING = 5,
      INET_DATA_START = 6,
      INET_DATA_RECEIVING = 7,
      INET_IMAGE_RECEIVED = 8,
      INET_MMEDIA_RECEIVED = 9,
      INET_SOUND_RECEIVED = 10,
      INET_USER1_RECEIVED = 11,
      INET_USER2_RECEIVED = 12,
      INET_USER3_RECEIVED = 13,
      INET_USER4_RECEIVED = 14,
   };

// ActiveX error codes
#include "L_OcxErr.h"

// L_SUPPORT_XXX constants
#include "ltlck_.h"
