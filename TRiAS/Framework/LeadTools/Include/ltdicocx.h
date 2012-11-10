#ifndef _LTDICOCX_H_
#define _LTDICOCX_H_
   typedef enum
   {
      VR_AE = 0x4145U,   // Application Entity
      VR_AS = 0x4153U,   // Age String
      VR_AT = 0x4154U,   // Attribute Tag
      VR_CS = 0x4353U,   // Code String
      VR_DA = 0x4441U,   // Date
      VR_DS = 0x4453U,   // Decimal String
      VR_DT = 0x4454U,   // Date Time
      VR_FD = 0x4644U,   // Floating Point Double
      VR_FL = 0x464CU,   // Floating Point Single
      VR_IS = 0x4953U,   // Integer String
      VR_LO = 0x4C4FU,   // Long String
      VR_LT = 0x4C54U,   // Long Text
      VR_OB = 0x4F42U,   // Other Byte String
      VR_OW = 0x4F57U,   // Other Word String
      VR_PN = 0x504EU,   // Person Name
      VR_SH = 0x5348U,   // Short String
      VR_SL = 0x534CU,   // Signed Long
      VR_SQ = 0x5351U,   // Sequence of Items
      VR_SS = 0x5353U,   // Signed Short
      VR_ST = 0x5354U,   // Short Text
      VR_TM = 0x544DU,   // Time
      VR_UI = 0x5549U,   // Unique Identifier
      VR_UL = 0x554CU,   // Unsigned Long
      VR_UN = 0x554EU,   // Unknown
      VR_US = 0x5553U,   // Unsigned Short
      VR_UT = 0x5554U,   // Unlimited Text
   } DicomVRCodeConstants;

   typedef enum
   {
      DICOM_VR_FIXED = 0,       // DICOMVR.nLength bytes fixed
      DICOM_VR_MAXIMUM,         // DICOMVR.nLength bytes maximum
      DICOM_VR_MAXIMUM_GROUP,   // DICOMVR.nLength maximum per component group
      DICOM_VR_ANY,             // Any length valid for any of the other DICOM Value Representations
      DICOM_VR_NOT_APPLICABLE,  // DICOMVR.nLength not applicable
      DICOM_VR_MAX,
      DICOM_VR_BINARY = 0x0100, // Binary value
      DICOM_VR_STRING = 0x0200, // String value (The character '\' is used as the delimiter between values for multiple data elements)
      DICOM_VR_TEXT   = 0x0400, // Text value (Data Elements with this VR shall not be multi-valued)
   } DicomVRRestrictionConstants;

   typedef enum
   {
      VALUE_AGE_DAYS    = 'D',
      VALUE_AGE_WEEKS   = 'W',
      VALUE_AGE_MONTHS  = 'M',
      VALUE_AGE_YEARS   = 'Y',
   } DicomAgeValueConstants;

   typedef enum
   {
      CALLBACK_ERROR_UNKNOWN_CLASS   = 0x0001,
      CALLBACK_ERROR_UNKNOWN_TAG     = 0x0002,
      CALLBACK_ERROR_UNKNOWN_VR      = 0x0004,
      CALLBACK_ERROR_WRONG_VR        = 0x0008,
      CALLBACK_ERROR_MIN_VM          = 0x0010,
      CALLBACK_ERROR_MAX_VM          = 0x0020,
      CALLBACK_ERROR_DIVIDE_VM       = 0x0040,
      CALLBACK_ERROR_IMAGE           = 0x0080,
   } DicomConformanceStatusFlags;

   typedef enum
   {
      DS_METAHEADER_PRESENT         = 0x0001U,
      DS_METAHEADER_ABSENT          = 0x0002U,
      DS_LITTLE_ENDIAN              = 0x0004U,
      DS_BIG_ENDIAN                 = 0x0008U,
      DS_IMPLICIT_VR                = 0x0010U,
      DS_EXPLICIT_VR                = 0x0020U,
      DS_GROUP_LENGTHS              = 0x0040U,
      DS_LENGTH_EXPLICIT            = 0x0080U,
      DS_EXCLUDE_METAHEADER_GROUP   = 0x0100U,
      DS_LOAD_CLOSE                 = 0x0200U,
   } DicomDataSetFlags;

// ActiveX error codes
#include "L_OcxErr.h"

   typedef enum
   {
      DICOM_SUCCESS                           = 0,
         DICOM_ERROR_LOCKED                      = 20001,
         DICOM_ERROR_MEMORY                      = 20002,
         DICOM_ERROR_OPEN                        = 20003,
         DICOM_ERROR_READ                        = 20004,
         DICOM_ERROR_WRITE                       = 20005,
         DICOM_ERROR_SEEK                        = 20006,
         DICOM_ERROR_END                         = 20007,
         DICOM_ERROR_FORMAT                      = 20008,
         DICOM_ERROR_PARAMETER                   = 20009,
         DICOM_ERROR_IMAGE                       = 20010,
         DICOM_ERROR_COMPRESSION                 = 20011,
         DICOM_ERROR_PHOTOMETRIC                 = 20012,
         DICOM_ERROR_CONVERSION                  = 20013,
         DICOM_ERROR_RANGE                       = 20014,
         DICOM_ERROR_BITSPERPIXEL                = 20015,
         DICOM_ERROR_QFACTOR                     = 20016,
         DICOM_ERROR_PDU_TYPE                    = 20017,
         DICOM_ERROR_PDU_LENGTH                  = 20018,
         DICOM_ERROR_PDU_ID                      = 20019,
         DICOM_ERROR_NET_FAILURE                 = 20029,
         DICOM_ERROR_NET_ACCESS                  = 20030,  // The address is a broadcast address
         DICOM_ERROR_NET_ADDRESS_IN_USE          = 20031,  // The address is already in use
         DICOM_ERROR_NET_ADDRESS_NOT_AVAILABLE   = 20032,  // The address is not available from the local computer
         DICOM_ERROR_NET_ADDRESS_NOT_SUPPORTED   = 20033,  // The address family is not supported
         DICOM_ERROR_NET_CONNECTION_ABORTED      = 20034,  // The virtual circuit was aborted
         DICOM_ERROR_NET_CONNECTION_REFUSED      = 20035,  // The attempt to connect was forcefully rejected
         DICOM_ERROR_NET_CONNECTION_RESET        = 20036,  // The virtual circuit was reset by the remote side
         DICOM_ERROR_NET_DESTINATION_REQUIRED    = 20037,  // A destination address is required
         DICOM_ERROR_NET_ARGUMENT_INCORRECT      = 20038,  // The namelen argument is incorrect
         DICOM_ERROR_NET_IN_PROGRESS             = 20039,  // A blocking operation is in progress
         DICOM_ERROR_NET_BLOCKING_CANCELED       = 20040,  // The blocking call was canceled
         DICOM_ERROR_NET_INVALID                 = 20041,  // The socket has not been bound with bind
         DICOM_ERROR_NET_IS_CONNECTED            = 20042,  // The socket is already connected
         DICOM_ERROR_NET_NO_MORE_FILE            = 20043,  // No more file descriptors are available
         DICOM_ERROR_NET_MESSAGE_SIZE            = 20044,  // The datagram is larger than the maximum supported
         DICOM_ERROR_NET_DOWN                    = 20045,  // The network subsystem has failed
         DICOM_ERROR_NET_RESET                   = 20046,  // The connection must be reset
         DICOM_ERROR_NET_UN_REACH                = 20047,  // The network can't be reached from this host at this time
         DICOM_ERROR_NET_NO_BUFFERS              = 20048,  // No buffer space is available
         DICOM_ERROR_NET_NOT_CONNECTED           = 20049,  // The socket is not connected
         DICOM_ERROR_NET_NOT_SOCKET              = 20050,  // The descriptor is not a socket
         DICOM_ERROR_NET_OPERATION_NOT_SUPPORTED = 20051,  // The type does not support connection-oriented service
         DICOM_ERROR_NET_PROTOCOL_NOT_SUPPORTED  = 20052,  // The specified protocol is not supported
         DICOM_ERROR_NET_PROTOCOL_TYPE           = 20053,  // The specified protocol is the wrong type
         DICOM_ERROR_NET_SHUTDOWN                = 20054,  // The socket has been shut down
         DICOM_ERROR_NET_SOCKET_NOT_SUPPORTED    = 20055,  // The type is not supported in this address family
         DICOM_ERROR_NET_TIME_OUT                = 20056,  // Attempt to connect timed out without establishing a connection
         DICOM_ERROR_NET_WOULD_BLOCK             = 20057,  // The socket is marked as nonblocking and the requested operation would block
         DICOM_ERROR_NET_HOST_NOT_FOUND          = 20058,  // Authoritative Answer Host not found
         DICOM_ERROR_NET_NO_DATA                 = 20059,  // Valid name, no data record of requested type
         DICOM_ERROR_NET_NO_RECOVERY             = 20060,  // Nonrecoverable errors
         DICOM_ERROR_NET_NOT_INITIALISED         = 20061,  // The system was not initialized
         DICOM_ERROR_NET_SYSTEM_NOT_READY        = 20062,  // Not ready for network communication
         DICOM_ERROR_NET_TRY_AGAIN               = 20063,  // Non-Authoritative Host not found, or server faild
         DICOM_ERROR_NET_VERSION_NOT_SUPPORTED   = 20064,  // The version requested is not provided by this implementation
         DICOM_ERROR_NET_SECURITY_BREACH         = 20065,  // There is an cryptographic error. 
         DICOM_ERROR_TLS                         = 20066,  // TLS internal error
         DICOM_ERROR_SECURITY_LOCKED             = 20067,  // DICOM Security Features are locked
         DICOM_ERROR_TLS_DLL_NOT_LOADED          = 20068,  // TLS and/or CRY DLL not loaded
         DICOM_ERROR_BAD_SECURE_MODE             = 20069,  // if I do ISCL operations on TLS objects
         DICOM_ERROR_ANN                         = 20070,
         DICOM_ERROR_ANN_LOCKED                  = 20071,  // Annotation support is locked
         DICOM_ERROR_ANN_MISSING                 = 20072,  // Annotation dll is missing
         DICOM_ERROR_TAG_ALREADY_EXISTS          = 20073,  // LEAD private creator element already exists
         DICOM_ERROR_ANN_NO_EXIST                = 20074,  // Requested annotation file or page does not exist
         DICOM_ERROR_ELEMENT_LENGTH_ODD          = 20100,
         DICOM_ERROR_DICOMDIR_FOLDER             = 20200,
         DICOM_ERROR_FILE                        = 20201,
         DICOM_ERROR_FILEID                      = 20202,
         DICOM_ERROR_J2K_LOCKED                  = 20203,
   } DicomSpecificErrorCodes;

   typedef enum
   {
      DICOM_CLASS_CR_IMAGE_STORAGE=0,
      DICOM_CLASS_CT_IMAGE_STORAGE,
      DICOM_CLASS_MR_IMAGE_STORAGE,
      DICOM_CLASS_NM_IMAGE_STORAGE,
      DICOM_CLASS_NM_IMAGE_STORAGE_RETIRED,
      DICOM_CLASS_US_IMAGE_STORAGE,
      DICOM_CLASS_US_IMAGE_STORAGE_RETIRED,
      DICOM_CLASS_US_MULTI_FRAME_IMAGE_STORAGE,
      DICOM_CLASS_US_MULTI_FRAME_IMAGE_STORAGE_RETIRED,
      DICOM_CLASS_SC_IMAGE_STORAGE,
      DICOM_CLASS_STANDALONE_OVERLAY_STORAGE,
      DICOM_CLASS_STANDALONE_CURVE_STORAGE,
      DICOM_CLASS_BASIC_STUDY_DESCRIPTOR,
      DICOM_CLASS_STANDALONE_MODALITY_LUT_STORAGE,
      DICOM_CLASS_STANDALONE_VOI_LUT_STORAGE,
      DICOM_CLASS_XA_IMAGE_STORAGE,
      DICOM_CLASS_XA_BIPLANE_IMAGE_STORAGE_RETIRED,
      DICOM_CLASS_XRF_IMAGE_STORAGE,
      DICOM_CLASS_RT_IMAGE_STORAGE,
      DICOM_CLASS_RT_DOSE_STORAGE,
      DICOM_CLASS_RT_STRUCTURE_SET_STORAGE,
      DICOM_CLASS_RT_PLAN_STORAGE,
      DICOM_CLASS_PET_IMAGE_STORAGE,
      DICOM_CLASS_STANDALONE_PET_CURVE_STORAGE,
      DICOM_CLASS_STORED_PRINT_STORAGE,
      DICOM_CLASS_HC_GRAYSCALE_IMAGE_STORAGE,
      DICOM_CLASS_HC_COLOR_IMAGE_STORAGE,
      DICOM_CLASS_DX_IMAGE_STORAGE_PRESENTATION,
      DICOM_CLASS_DX_IMAGE_STORAGE_PROCESSING,
      DICOM_CLASS_DX_MAMMOGRAPHY_IMAGE_STORAGE_PRESENTATION,
      DICOM_CLASS_DX_MAMMOGRAPHY_IMAGE_STORAGE_PROCESSING,
      DICOM_CLASS_DX_INTRAORAL_IMAGE_STORAGE_PRESENTATION,
      DICOM_CLASS_DX_INTRAORAL_IMAGE_STORAGE_PROCESSING,
      DICOM_CLASS_RT_BEAMS_TREATMENT_RECORD_STORAGE,
      DICOM_CLASS_RT_BRACHY_TREATMENT_RECORD_STORAGE,
      DICOM_CLASS_RT_TREATMENT_SUMMARY_RECORD_STORAGE,
      DICOM_CLASS_VL_ENDOSCOPIC_IMAGE_STORAGE,
      DICOM_CLASS_VL_MICROSCOPIC_IMAGE_STORAGE,
      DICOM_CLASS_VL_SLIDE_COORDINATES_MICROSCOPIC_IMAGE_STORAGE,
      DICOM_CLASS_VL_PHOTOGRAPHIC_IMAGE_STORAGE,
   
      DICOM_CLASS_PATIENT,
      DICOM_CLASS_VISIT,
      DICOM_CLASS_STUDY,
      DICOM_CLASS_STUDY_COMPONENT,
      DICOM_CLASS_RESULTS,
      DICOM_CLASS_INTERPRETATION,
      DICOM_CLASS_BASIC_FILM_SESSION,
      DICOM_CLASS_BASIC_FILM_BOX,
      DICOM_CLASS_BASIC_GRAYSCALE_IMAGE_BOX,
      DICOM_CLASS_BASIC_COLOR_IMAGE_BOX,
      DICOM_CLASS_BASIC_ANNOTATION_BOX,
      DICOM_CLASS_PRINT_JOB,
      DICOM_CLASS_PRINTER,
      DICOM_CLASS_VOI_LUT_BOX_RETIRED,
      DICOM_CLASS_IMAGE_OVERLAY_BOX_RETIRED,
      DICOM_CLASS_STORAGE_COMMITMENT_PUSH_MODEL,
      DICOM_CLASS_STORAGE_COMMITMENT_PULL_MODEL,
      DICOM_CLASS_PRINT_QUEUE,
      DICOM_CLASS_MODALITY_PERFORMED_PROCEDURE_STEP,
      DICOM_CLASS_PRESENTATION_LUT,
      DICOM_CLASS_PULL_PRINT_REQUEST,
      DICOM_CLASS_PATIENT_META,
      DICOM_CLASS_STUDY_META,
      DICOM_CLASS_RESULTS_META,
      DICOM_CLASS_BASIC_GRAYSCALE_PRINT_META,
      DICOM_CLASS_BASIC_COLOR_PRINT_META,
      DICOM_CLASS_REFERENCED_GRAYSCALE_PRINT_META_RETIRED,
      DICOM_CLASS_REFERENCED_COLOR_PRINT_META_RETIRED,
      DICOM_CLASS_PULL_STORED_PRINT_META,
      DICOM_CLASS_PRINTER_CONFIGURATION,
      DICOM_CLASS_BASIC_PRINT_IMAGE_OVERLAY_BOX,

      DICOM_CLASS_BASIC_DIRECTORY,

      DICOM_CLASS_PATIENT_ROOT_QUERY_PATIENT,
      DICOM_CLASS_PATIENT_ROOT_QUERY_STUDY,
      DICOM_CLASS_PATIENT_ROOT_QUERY_SERIES,
      DICOM_CLASS_PATIENT_ROOT_QUERY_IMAGE,
      DICOM_CLASS_STUDY_ROOT_QUERY_STUDY,
      DICOM_CLASS_STUDY_ROOT_QUERY_SERIES,
      DICOM_CLASS_STUDY_ROOT_QUERY_IMAGE,
      DICOM_CLASS_PATIENT_STUDY_QUERY_PATIENT,
      DICOM_CLASS_PATIENT_STUDY_QUERY_STUDY,

      DICOM_CLASS_BASIC_TEXT_SR,
      DICOM_CLASS_ENHANCED_SR,
      DICOM_CLASS_COMPREHENSIVE_SR,

      DICOM_CLASS_MODALITY_WORKLIST,

      DICOM_CLASS_GRAYSCALE_SOFTCOPY_PRESENTATION_STATE,
      DICOM_CLASS_BASIC_VOICE_AUDIO,                    
      DICOM_CLASS_12_LEAD_ECG,                          
      DICOM_CLASS_GENERAL_ECG,                          
      DICOM_CLASS_AMBULATORY_ECG,                       
      DICOM_CLASS_HEMODYNAMIC,                          
      DICOM_CLASS_BASIC_CARDIAC_EP,                     

      DICOM_CLASS_MAX,

      DICOM_CLASS_UNKNOWN = 65535,
   } DicomClassConstants;
      
   typedef enum
   {
      DICOM_MODULE_PATIENT=0,
      DICOM_MODULE_GENERAL_STUDY,
      DICOM_MODULE_PATIENT_STUDY,
      DICOM_MODULE_GENERAL_SERIES,
      DICOM_MODULE_CR_SERIES,
      DICOM_MODULE_GENERAL_EQUIPMENT,
      DICOM_MODULE_GENERAL_IMAGE,
      DICOM_MODULE_IMAGE_PIXEL,
      DICOM_MODULE_CONTRAST_BOLUS,
      DICOM_MODULE_CR_IMAGE,
      DICOM_MODULE_OVERLAY_PLANE,
      DICOM_MODULE_CURVE,
      DICOM_MODULE_MODALITY_LUT,
      DICOM_MODULE_VOI_LUT,
      DICOM_MODULE_SOP_COMMON,
      DICOM_MODULE_FRAME_OF_REFERENCE,
      DICOM_MODULE_IMAGE_PLANE,
      DICOM_MODULE_CT_IMAGE,
      DICOM_MODULE_MR_IMAGE,
      DICOM_MODULE_NM_PET_PATIENT_ORIENTATION,
      DICOM_MODULE_NM_IMAGE_PIXEL,
      DICOM_MODULE_MULTI_FRAME,
      DICOM_MODULE_NM_MULTI_FRAME,
      DICOM_MODULE_NM_IMAGE,
      DICOM_MODULE_NM_ISOTOPE,
      DICOM_MODULE_NM_DETECTOR,
      DICOM_MODULE_NM_TOMO_ACQUISITION,
      DICOM_MODULE_NM_MULTI_GATED_ACQUISITION,
      DICOM_MODULE_NM_PHASE,
      DICOM_MODULE_NM_RECONSTRUCTION,
      DICOM_MODULE_MULTI_FRAME_OVERLAY,
      DICOM_MODULE_US_FRAME_OF_REFERENCE,
      DICOM_MODULE_PALETTE_COLOR_LOOCKUP_TABLE,
      DICOM_MODULE_US_REGION_CALIBRATION,
      DICOM_MODULE_US_IMAGE,
      DICOM_MODULE_CURVE_IDENTIFICATION,
      DICOM_MODULE_AUDIO,
      DICOM_MODULE_CINE,
      DICOM_MODULE_SC_EQUIPMENT,
      DICOM_MODULE_SC_IMAGE,
      DICOM_MODULE_OVERLAY_IDENTIFICATION,
      DICOM_MODULE_PATIENT_SUMMARY,
      DICOM_MODULE_STUDY_CONTENT,
      DICOM_MODULE_LUT_IDENTIFICATION,
      DICOM_MODULE_FRAME_POINTERS,
      DICOM_MODULE_MASK,
      DICOM_MODULE_DISPLAY_SHUTTER,
      DICOM_MODULE_DEVICE,
      DICOM_MODULE_THERAPY,
      DICOM_MODULE_XA_IMAGE,
      DICOM_MODULE_XA_ACQUISITION,
      DICOM_MODULE_XA_COLLIMATOR,
      DICOM_MODULE_XA_TABLE,
      DICOM_MODULE_XA_POSITIONER,
      DICOM_MODULE_BIPLANE_SEQUENCE,
      DICOM_MODULE_BIPLANE_OVERLAY,
      DICOM_MODULE_BIPLANE_IMAGE,
      DICOM_MODULE_XRF_POSITIONER,
      DICOM_MODULE_XRF_TOMO_ACQUISITION,
      DICOM_MODULE_RT_SERIES,
      DICOM_MODULE_RT_IMAGE,
      DICOM_MODULE_APPROVAL,
      DICOM_MODULE_RT_DOSE,
      DICOM_MODULE_RT_DVH,
      DICOM_MODULE_STRUCTURE_SET,
      DICOM_MODULE_ROI_CONTOUR,
      DICOM_MODULE_RT_DOSE_ROI,
      DICOM_MODULE_RT_OBSERVATIONS,
      DICOM_MODULE_RT_GENERAL_PLAN,
      DICOM_MODULE_RT_PRESCRIPTION,
      DICOM_MODULE_RT_TOLERANCE_TABLES,
      DICOM_MODULE_RT_PATIENT_SETUP,
      DICOM_MODULE_RT_FRACTION_SCHEME,
      DICOM_MODULE_RT_BEAMS,
      DICOM_MODULE_RT_BRACHY_APPLICATION_SETUPS,
      DICOM_MODULE_PET_SERIES,
      DICOM_MODULE_PET_ISOTOPE,
      DICOM_MODULE_PET_MULTIGATED_ACQUISITION,
      DICOM_MODULE_PET_IMAGE,
      DICOM_MODULE_PET_CURVE,
      DICOM_MODULE_PRINTER_CHARACTERISTICS,
      DICOM_MODULE_FILM_BOX,
      DICOM_MODULE_IMAGE_BOX_LIST,
      DICOM_MODULE_ANNOTATION_LIST,
      DICOM_MODULE_IMAGE_OVERLAY_BOX_LIST,
      DICOM_MODULE_PRESENTATION_LUT_LIST,
      DICOM_MODULE_HC_EQUIPMENT,
      DICOM_MODULE_HC_GRAYSCALE_IMAGE,
      DICOM_MODULE_HC_COLOR_IMAGE,
      DICOM_MODULE_PATIENT_RELATIONSHIP,
      DICOM_MODULE_PATIENT_IDENTIFICATION,
      DICOM_MODULE_PATIENT_DEMOGRAPHIC,
      DICOM_MODULE_PATIENT_MEDICAL,
      DICOM_MODULE_VISIT_RELATIONSHIP,
      DICOM_MODULE_VISIT_IDENTIFICATION,
      DICOM_MODULE_VISIT_ADMISSION,
      DICOM_MODULE_VISIT_STAY,
      DICOM_MODULE_VISIT_DISCHARGE,
      DICOM_MODULE_VISIT_SCHEDULING,
      DICOM_MODULE_STUDY_RELATIONSHIP,
      DICOM_MODULE_STUDY_IDENTIFICATION,
      DICOM_MODULE_STUDY_CLASSIFICATION,
      DICOM_MODULE_STUDY_SCHEDULING,
      DICOM_MODULE_STUDY_ACQUISITION,
      DICOM_MODULE_STUDY_READ,
      DICOM_MODULE_STUDY_COMPONENT_RELATIONSHIP,
      DICOM_MODULE_STUDY_COMPONENT_ACQUISITION,
      DICOM_MODULE_STUDY_COMPONENT,
      DICOM_MODULE_RESULTS_RELATIONSHIP,
      DICOM_MODULE_RESULTS_IDENTIFICATION,
      DICOM_MODULE_RESULTS_IMPRESSIONS,
      DICOM_MODULE_INTERPRETATION_RELATIONSHIP,
      DICOM_MODULE_INTERPRETATION_IDENTIFICATION,
      DICOM_MODULE_INTERPRETATION_STATE,
      DICOM_MODULE_INTERPRETATION_RECORDING,
      DICOM_MODULE_INTERPRETATION_TRANSCRIPTION,
      DICOM_MODULE_INTERPRETATION_APPROVAL,
      DICOM_MODULE_BASIC_FILM_SESSION_PRESENTATION,
      DICOM_MODULE_BASIC_FILM_SESSION_RELATIONSHIP,
      DICOM_MODULE_BASIC_FILM_BOX_PRESENTATION,
      DICOM_MODULE_BASIC_FILM_BOX_RELATIONSHIP,
      DICOM_MODULE_IMAGE_BOX_PRESENTATION_GRAYSCALE,
      DICOM_MODULE_IMAGE_BOX_PRESENTATION_COLOR,
      DICOM_MODULE_IMAGE_BOX_RELATIONSHIP,
      DICOM_MODULE_BASIC_ANNOTATION_PRESENTATION,
      DICOM_MODULE_PRINT_JOB,
      DICOM_MODULE_PRINTER,
      DICOM_MODULE_IMAGE_OVERLAY_BOX_PRESENTATION,
      DICOM_MODULE_IMAGE_OVERLAY_BOX_RELATIONSHIP,
      DICOM_MODULE_STORAGE_COMMITMENT,
      DICOM_MODULE_GENERAL_QUEUE,
      DICOM_MODULE_PRINT_QUEUE,
      DICOM_MODULE_PERFORMED_PROCEDURE_STEP_RELATIONSHIP,
      DICOM_MODULE_PERFORMED_PROCEDURE_STEP_INFORMATION,
      DICOM_MODULE_IMAGE_ACQUISITION_RESULTS,
      DICOM_MODULE_RADIATION_DOSE,
      DICOM_MODULE_BILLING_AND_MATERIAL_MANAGEMENT_CODES,
      DICOM_MODULE_PRESENTATION_LUT,
      DICOM_MODULE_PRINT_REQUEST,
      DICOM_MODULE_PATIENT_RELATIONSHIP_META,
      DICOM_MODULE_NM_SERIES_RETIRED,                      
      DICOM_MODULE_NM_EQUIPMENT_RETIRED,                   
      DICOM_MODULE_NM_IMAGE_RETIRED,                               
      DICOM_MODULE_NM_SPECT_ACQUISITION_IMAGE_RETIRED,     
      DICOM_MODULE_NM_MULTI_GATED_ACQUISITION_IMAGE_RETIRED,
      DICOM_MODULE_US_FRAME_OF_REFERENCE_RETIRED,
      DICOM_MODULE_US_REGION_CALIBRATION_RETIRED,
      DICOM_MODULE_US_IMAGE_RETIRED,             
   
      DICOM_MODULE_FILESET_IDENTIFICATION,
      DICOM_MODULE_DIRECTORY_INFORMATION,
      DICOM_MODULE_PATIENT_KEY,
      DICOM_MODULE_STUDY_KEY,
      DICOM_MODULE_SERIES_KEY,
      DICOM_MODULE_IMAGE_KEY,
      DICOM_MODULE_OVERLAY_KEY,
      DICOM_MODULE_MODALITY_LUT_KEY,
      DICOM_MODULE_VOI_LUT_KEY,
      DICOM_MODULE_CURVE_KEY,
      DICOM_MODULE_STORED_PRINT_KEY,
      DICOM_MODULE_RT_DOSE_KEY,
      DICOM_MODULE_RT_STRUCTURE_SET_KEY,
      DICOM_MODULE_RT_PLAN_KEY,
      DICOM_MODULE_RT_TREATMENT_RECORD_KEY,
      DICOM_MODULE_TOPIC_KEY,
      DICOM_MODULE_VISIT_KEY,
      DICOM_MODULE_RESULTS_KEY,
      DICOM_MODULE_INTERPRETATION_KEY,
      DICOM_MODULE_STUDY_COMPONENT_KEY,
      DICOM_MODULE_PRIVATE_KEY,

      DICOM_MODULE_SPECIMEN_IDENTIFICATION,
      DICOM_MODULE_DX_SERIES,
      DICOM_MODULE_DX_ANATOMY_IMAGED,
      DICOM_MODULE_DX_IMAGE,         
      DICOM_MODULE_DX_DETECTOR,      
      DICOM_MODULE_DX_POSITIONING,
      DICOM_MODULE_ACQUISITION_CONTEXT,
      DICOM_MODULE_XA_ACQUISITION_DOSE,
      DICOM_MODULE_XA_GENERATION,
      DICOM_MODULE_XA_FILTRATION,
      DICOM_MODULE_XA_GRID,
      DICOM_MODULE_IMAGE_HISTOGRAM,
      DICOM_MODULE_MAMMOGRAPHY_SERIES,
      DICOM_MODULE_MAMMOGRAPHY_IMAGE,
      DICOM_MODULE_INTRAORAL_SERIES,
      DICOM_MODULE_INTRAORAL_IMAGE,

      DICOM_MODULE_RT_GENERAL_TREATMENT_RECORD,
      DICOM_MODULE_RT_TREATMENT_MACHINE_RECORD,
      DICOM_MODULE_MEASURED_DOSE_REFERENCE_RECORD,
      DICOM_MODULE_CALCULATED_DOSE_REFERENCE_RECORD,
      DICOM_MODULE_RT_BEAMS_SESSION_RECORD,
      DICOM_MODULE_RT_TREATMENT_SUMMARY_RECORD,
      DICOM_MODULE_RT_BRACHY_SESSION_RECORD,

      DICOM_MODULE_VL_IMAGE,
      DICOM_MODULE_SLIDE_COORDINATES,

      DICOM_MODULE_BASIC_PRINT_IMAGE_OVERLAY_BOX,
      DICOM_MODULE_PRINTER_CONFIGURATION,

      DICOM_MODULE_SR_DOCUMENT_SERIES,
      DICOM_MODULE_SR_DOCUMENT_GENERAL,
      DICOM_MODULE_SR_DOCUMENT_CONTENT,
      DICOM_MODULE_SR_DOCUMENT_KEY,

      DICOM_MODULE_SCHEDULED_PROCEDURE_STEP,
      DICOM_MODULE_REQUESTED_PROCEDURE,
      DICOM_MODULE_IMAGING_SERVICE_REQUEST,

      DICOM_MODULE_PRESENTATION_SERIES,
      DICOM_MODULE_PRESENTATION_STATE,
      DICOM_MODULE_BITMAP_DISPLAY_SHUTTER,
      DICOM_MODULE_OVERLAY_CURVE_ACTIVATION,
      DICOM_MODULE_DISPLAYED_AREA,
      DICOM_MODULE_GRAPHIC_ANNOTATION,
      DICOM_MODULE_SPATIAL_TRANSFORMATION,
      DICOM_MODULE_GRAPHIC_LAYER,
      DICOM_MODULE_SOFTCOPY_VOI_LUT,
      DICOM_MODULE_SOFTCOPY_PRESENTATION_LUT,
      DICOM_MODULE_SYNCHRONIZATION,
      DICOM_MODULE_WAVEFORM_IDENTIFICATION,
      DICOM_MODULE_WAVEFORM,
      DICOM_MODULE_WAVEFORM_ANNOTATION,
      DICOM_MODULE_PRESENTATION_KEY,
      DICOM_MODULE_WAVEFORM_KEY,

      DICOM_MODULE_MAX,
   } DicomModuleConstants;
      
   typedef enum
   {
      TAG_FILE_META_INFORMATION_VERSION                          = 0x00020001UL,
      TAG_MEDIA_STORAGE_SOP_CLASS_UID                            = 0x00020002UL,
      TAG_MEDIA_STORAGE_SOP_INSTANCE_UID                         = 0x00020003UL,
      TAG_TRANSFER_SYNTAX_UID                                    = 0x00020010UL,
      TAG_IMPLEMENTATION_CLASS_UID                               = 0x00020012UL,
      TAG_IMPLEMENTATION_VERSION_NAME                            = 0x00020013UL,
      TAG_SOURCE_APPLICATION_ENTITY_TITLE                        = 0x00020016UL,
      TAG_PRIVATE_INFORMATION_CREATOR_UID                        = 0x00020100UL,
      TAG_PRIVATE_INFORMATION                                    = 0x00020102UL,

      TAG_FILE_SET_ID                                            = 0x00041130UL,
      TAG_FILE_SET_DESCRIPTOR_FILE_ID                            = 0x00041141UL,
      TAG_SPECIFIC_CHARACTER_SET_OF_FILE                         = 0x00041142UL,
      TAG_OFFSET_FIRST_ROOT_DIRECTORY                            = 0x00041200UL,
      TAG_OFFSET_LAST_ROOT_DIRECTORY                             = 0x00041202UL,
      TAG_FILE_SET_CONSISTENCY_FLAG                              = 0x00041212UL,
      TAG_DIRECTORY_RECORD_SEQUENCE                              = 0x00041220UL,
      TAG_OFFSET_NEXT_DIRECTORY                                  = 0x00041400UL,
      TAG_RECORD_IN_USE_FLAG                                     = 0x00041410UL,
      TAG_OFFSET_CHILD_DIRECTORY                                 = 0x00041420UL,
      TAG_DIRECTORY_RECORD_TYPE                                  = 0x00041430UL,
      TAG_PRIVATE_RECORD_UID                                     = 0x00041432UL,
      TAG_REFERENCED_FILE_ID                                     = 0x00041500UL,
      TAG_OFFSET_MRDR_DIRECTORY                                  = 0x00041504UL,
      TAG_REFERENCED_SOP_CLASS_UID_IN_FILE                       = 0x00041510UL,
      TAG_REFERENCED_SOP_INSTANCE_UID_IN_FILE                    = 0x00041511UL,
      TAG_REFERENCED_TRANSFER_SYNTAX_UID_IN_FILE                 = 0x00041512UL,
      TAG_NUMBER_OF_REFERENCES                                   = 0x00041600UL,

      TAG_SPECIFIC_CHARACTER_SET                                 = 0x00080005UL,
      TAG_IMAGE_TYPE                                             = 0x00080008UL,
      TAG_INSTANCE_CREATION_DATE                                 = 0x00080012UL,
      TAG_INSTANCE_CREATION_TIME                                 = 0x00080013UL,
      TAG_INSTANCE_CREATOR_UID                                   = 0x00080014UL,
      TAG_SOP_CLASS_UID                                          = 0x00080016UL,
      TAG_SOP_INSTANCE_UID                                       = 0x00080018UL,
      TAG_STUDY_DATE                                             = 0x00080020UL,
      TAG_SERIES_DATE                                            = 0x00080021UL,
      TAG_ACQUISITION_DATE                                       = 0x00080022UL,
      TAG_IMAGE_DATE                                             = 0x00080023UL,
      TAG_OVERLAY_DATE                                           = 0x00080024UL,
      TAG_CURVE_DATE                                             = 0x00080025UL,
      TAG_STUDY_TIME                                             = 0x00080030UL,
      TAG_SERIES_TIME                                            = 0x00080031UL,
      TAG_ACQUISITION_TIME                                       = 0x00080032UL,
      TAG_IMAGE_TIME                                             = 0x00080033UL,
      TAG_OVERLAY_TIME                                           = 0x00080034UL,
      TAG_CURVE_TIME                                             = 0x00080035UL,
      TAG_NUCLEAR_MEDICINE_SERIES_TYPE_RETIRED                   = 0x00080042UL,
      TAG_ACCESSION_NUMBER                                       = 0x00080050UL,
      TAG_QUERY_RETRIEVE_LEVEL                                   = 0x00080052UL,
      TAG_RETRIEVE_AE_TITLE                                      = 0x00080054UL,
      TAG_FAILED_SOP_INSTANCE_UID_LIST                           = 0x00080058UL,
      TAG_MODALITY                                               = 0x00080060UL,
      TAG_MODALITIES_IN_STUDY                                    = 0x00080061UL,
      TAG_CONVERSION_TYPE                                        = 0x00080064UL,
      TAG_PRESENTATION_INTENT_TYPE                               = 0x00080068UL,
      TAG_MANUFACTURER                                           = 0x00080070UL,
      TAG_INSTITUTION_NAME                                       = 0x00080080UL,
      TAG_INSTITUTION_ADDRESS                                    = 0x00080081UL,
      TAG_INSTITUTION_CODE_SEQUENCE                              = 0x00080082UL,
      TAG_REFERRING_PHYSICIAN_NAME                               = 0x00080090UL,
      TAG_REFERRING_PHYSICIAN_ADDRESS                            = 0x00080092UL,
      TAG_REFERRING_PHYSICIAN_TELEPHONE_NUMBERS                  = 0x00080094UL,
      TAG_CODE_VALUE                                             = 0x00080100UL,
      TAG_CODING_SCHEME_DESIGNATOR                               = 0x00080102UL,
      TAG_CODE_MEANING                                           = 0x00080104UL,
      TAG_CONTEXT_GROUP_LOCAL_VERSION                            = 0x00080107UL,
      TAG_STATION_NAME                                           = 0x00081010UL,
      TAG_STUDY_DESCRIPTION                                      = 0x00081030UL,
      TAG_PROCEDURE_CODE_SEQUENCE                                = 0x00081032UL,
      TAG_SERIES_DESCRIPTION                                     = 0x0008103EUL,
      TAG_INSTITUTIONAL_DEPARTMENT_NAME                          = 0x00081040UL,
      TAG_PHYSICIAN_OF_RECORD                                    = 0x00081048UL,
      TAG_PERFORMING_PHYSICIAN_NAME                              = 0x00081050UL,
      TAG_NAME_OF_PHYSICIAN_READING_STUDY                        = 0x00081060UL,
      TAG_OPERATORS_NAME                                         = 0x00081070UL,
      TAG_ADMITTING_DIAGNOSES_DESCRIPTION                        = 0x00081080UL,
      TAG_ADMITTING_DIAGNOSIS_CODE_SEQUENCE                      = 0x00081084UL,
      TAG_MANUFACTURER_MODEL_NAME                                = 0x00081090UL,
      TAG_REFERENCED_RESULTS_SEQUENCE                            = 0x00081100UL,
      TAG_REFERENCED_STUDY_SEQUENCE                              = 0x00081110UL,
      TAG_REFERENCED_STUDY_COMPONENT_SEQUENCE                    = 0x00081111UL,
      TAG_REFERENCED_SERIES_SEQUENCE                             = 0x00081115UL,
      TAG_REFERENCED_PATIENT_SEQUENCE                            = 0x00081120UL,
      TAG_REFERENCED_VISIT_SEQUENCE                              = 0x00081125UL,
      TAG_REFERENCED_OVERLAY_SEQUENCE_0008                       = 0x00081130UL,
      TAG_REFERENCED_IMAGE_SEQUENCE                              = 0x00081140UL,
      TAG_REFERENCED_CURVE_SEQUENCE                              = 0x00081145UL,
      TAG_REFERENCED_SOP_CLASS_UID                               = 0x00081150UL,
      TAG_REFERENCED_SOP_INSTANCE_UID                            = 0x00081155UL,
      TAG_SOP_CLASSES_SUPPORTED                                  = 0x0008115AUL,
      TAG_REFERENCED_FRAME_NUMBER                                = 0x00081160UL,
      TAG_TRANSACTION_UID                                        = 0x00081195UL,
      TAG_FAILURE_REASON                                         = 0x00081197UL,
      TAG_FAILED_SOP_SEQUENCE                                    = 0x00081198UL,
      TAG_REFERENCED_SOP_SEQUENCE                                = 0x00081199UL,
      TAG_LOSSY_IMAGE_COMPRESSION_RETIRED                        = 0x00082110UL,
      TAG_DERIVATION_DESCRIPTION                                 = 0x00082111UL,
      TAG_SOURCE_IMAGE_SEQUENCE                                  = 0x00082112UL,
      TAG_STAGE_NAME                                             = 0x00082120UL,
      TAG_STAGE_NUMBER                                           = 0x00082122UL,
      TAG_NUMBER_OF_STAGES                                       = 0x00082124UL,
      TAG_VIEW_NUMBER                                            = 0x00082128UL,
      TAG_NUMBER_OF_EVENT_TIMERS                                 = 0x00082129UL,
      TAG_NUMBER_OF_VIEWS_IN_STAGE                               = 0x0008212AUL,
      TAG_EVENT_ELAPSED_TIME                                     = 0x00082130UL,
      TAG_EVENT_TIMER_NAME                                       = 0x00082132UL,
      TAG_START_TRIM                                             = 0x00082142UL,
      TAG_STOP_TRIM                                              = 0x00082143UL,
      TAG_RECOMMENDED_DISPLAY_FRAME_RATE                         = 0x00082144UL,
      TAG_TRANSDUCER_POSITION_RETIRED                            = 0x00082200UL,
      TAG_TRANSDUCER_ORIENTATION_RETIRED                         = 0x00082204UL,
      TAG_ANATOMIC_STRUCTURE_RETIRED                             = 0x00082208UL,
      TAG_ANATOMIC_REGION_SEQUENCE                               = 0x00082218UL,
      TAG_ANATOMIC_REGION_MODIFIER_SEQUENCE                      = 0x00082220UL,
      TAG_PRIMARY_ANATOMIC_STRUCTURE_SEQUENCE                    = 0x00082228UL,
      TAG_ANATOMIC_STRUCTURE_SPACE_OR_REGION_SEQUENCE            = 0x00082229UL,
      TAG_PRIMARY_ANATOMIC_STRUCTURE_MODIFIER_SEQUENCE           = 0x00082230UL,
      TAG_TRANSDUCER_POSITION_SEQUENCE                           = 0x00082240UL,
      TAG_TRANSDUCER_POSITION_MODIFIER_SEQUENCE                  = 0x00082242UL,
      TAG_TRANSDUCER_ORIENTATION_SEQUENCE                        = 0x00082244UL,
      TAG_TRANSDUCER_ORIENTATION_MODIFIER_SEQUENCE               = 0x00082246UL,

      TAG_PATIENT_NAME                                           = 0x00100010UL,
      TAG_PATIENT_ID                                             = 0x00100020UL,
      TAG_ISSUER_OF_PATIENT_ID                                   = 0x00100021UL,
      TAG_PATIENT_BIRTH_DATE                                     = 0x00100030UL,
      TAG_PATIENT_BIRTH_TIME                                     = 0x00100032UL,
      TAG_PATIENT_SEX                                            = 0x00100040UL,
      TAG_PATIENT_INSURANCE_PLAN_CODE_SEQUENCE                   = 0x00100050UL,
      TAG_OTHER_PATIENT_IDS                                      = 0x00101000UL,
      TAG_OTHER_PATIENT_NAMES                                    = 0x00101001UL,
      TAG_PATIENT_BIRTH_NAME                                     = 0x00101005UL,
      TAG_PATIENT_AGE                                            = 0x00101010UL,
      TAG_PATIENT_SIZE                                           = 0x00101020UL,
      TAG_PATIENT_WEIGHT                                         = 0x00101030UL,
      TAG_PATIENT_ADDRESS                                        = 0x00101040UL,
      TAG_PATIENT_MOTHER_BIRTH_NAME                              = 0x00101060UL,
      TAG_MILITARY_RANK                                          = 0x00101080UL,
      TAG_BRANCH_OF_SERVICE                                      = 0x00101081UL,
      TAG_MEDICAL_RECORD_LOCATOR                                 = 0x00101090UL,
      TAG_MEDICAL_ALERTS                                         = 0x00102000UL,
      TAG_CONTRAST_ALLERGIES                                     = 0x00102110UL,
      TAG_COUNTRY_OF_RESIDENCE                                   = 0x00102150UL,
      TAG_REGION_OF_RESIDENCE                                    = 0x00102152UL,
      TAG_PATIENT_TELEPHONE_NUMBERS                              = 0x00102154UL,
      TAG_ETHNIC_GROUP                                           = 0x00102160UL,
      TAG_OCCUPATION                                             = 0x00102180UL,
      TAG_SMOKING_STATUS                                         = 0x001021A0UL,
      TAG_ADDITIONAL_PATIENT_HISTORY                             = 0x001021B0UL,
      TAG_PREGNANCY_STATUS                                       = 0x001021C0UL,
      TAG_LAST_MENSTRUAL_DATE                                    = 0x001021D0UL,
      TAG_PATIENT_RELIGIOUS_PREFERENCE                           = 0x001021F0UL,
      TAG_PATIENT_COMMENTS                                       = 0x00104000UL,

      TAG_CONTRAST_BOLUS_AGENT                                   = 0x00180010UL,
      TAG_CONTRAST_BOLUS_AGENT_SEQUENCE                          = 0x00180012UL,
      TAG_CONTRAST_BOLUS_ADMINISTRATION_ROUTE_SEQUENCE           = 0x00180014UL,
      TAG_BODY_PART_EXAMINED                                     = 0x00180015UL,
      TAG_SCANNING_SEQUENCE                                      = 0x00180020UL,
      TAG_SEQUENCE_VARIANT                                       = 0x00180021UL,
      TAG_SCAN_OPTIONS                                           = 0x00180022UL,
      TAG_MR_ACQUISITION_TYPE                                    = 0x00180023UL,
      TAG_SEQUENCE_NAME                                          = 0x00180024UL,
      TAG_ANGIO_FLAG                                             = 0x00180025UL,
      TAG_INTERVENTION_DRUG_INFORMATION_SEQUENCE                 = 0x00180026UL,
      TAG_INTERVENTION_DRUG_STOP_TIME                            = 0x00180027UL,
      TAG_INTERVENTION_DRUG_DOSE                                 = 0x00180028UL,
      TAG_INTERVENTION_DRUG_CODE_SEQUENCE                        = 0x00180029UL,
      TAG_ADDITIONAL_DRUG_SEQUENCE                               = 0x0018002AUL,
      TAG_RADIONUCLIDE_RETIRED                                   = 0x00180030UL,
      TAG_RADIOPHARMACEUTICAL                                    = 0x00180031UL,
      TAG_ENERGY_WINDOW_CENTERLINE_RETIRED                       = 0x00180032UL,
      TAG_ENERGY_WINDOW_TOTAL_WIDTH_RETIRED                      = 0x00180033UL,
      TAG_INTERVENTION_DRUG_NAME                                 = 0x00180034UL,
      TAG_INTERVENTION_DRUG_START_TIME                           = 0x00180035UL,
      TAG_INTERVENTIONAL_THERAPY_SEQUENCE                        = 0x00180036UL,
      TAG_THERAPY_TYPE                                           = 0x00180037UL,
      TAG_INTERVENTIONAL_STATUS                                  = 0x00180038UL,
      TAG_THERAPY_DESCRIPTION                                    = 0x00180039UL,
      TAG_CINE_RATE                                              = 0x00180040UL,
      TAG_SLICE_THICKNESS                                        = 0x00180050UL,
      TAG_KVP                                                    = 0x00180060UL,
      TAG_COUNTS_ACCUMULATED                                     = 0x00180070UL,
      TAG_ACQUISITION_TERMINATION_CONDITION                      = 0x00180071UL,
      TAG_EFFECTIVE_SERIES_DURATION                              = 0x00180072UL,
      TAG_ACQUISITION_START_CONDITION                            = 0x00180073UL,
      TAG_ACQUISITION_START_CONDITION_DATA                       = 0x00180074UL,
      TAG_ACQUISITION_TERMINATION_CONDITION_DATA                 = 0x00180075UL,
      TAG_REPETITION_TIME                                        = 0x00180080UL,
      TAG_ECHO_TIME                                              = 0x00180081UL,
      TAG_INVERSION_TIME                                         = 0x00180082UL,
      TAG_NUMBER_OF_AVERAGES                                     = 0x00180083UL,
      TAG_IMAGING_FREQUENCY                                      = 0x00180084UL,
      TAG_IMAGED_NUCLEUS                                         = 0x00180085UL,
      TAG_ECHO_NUMBER                                            = 0x00180086UL,
      TAG_MAGNETIC_FIELD_STRENGTH                                = 0x00180087UL,
      TAG_SPACING_BETWEEN_SLICES                                 = 0x00180088UL,
      TAG_NUMBER_OF_PHASE_ENCODING_STEPS                         = 0x00180089UL,
      TAG_DATA_COLLECTION_DIAMETER                               = 0x00180090UL,
      TAG_ECHO_TRAIN_LENGTH                                      = 0x00180091UL,
      TAG_PERCENT_SAMPLING                                       = 0x00180093UL,
      TAG_PERCENT_PHASE_FIELD_OF_VIEW                            = 0x00180094UL,
      TAG_PIXEL_BANDWIDTH                                        = 0x00180095UL,
      TAG_DEVICE_SERIAL_NUMBER                                   = 0x00181000UL,
      TAG_PLATE_ID                                               = 0x00181004UL,
      TAG_SECONDARY_CAPTURE_DEVICE_ID                            = 0x00181010UL,
      TAG_HARDCOPY_CREATION_DEVICE_ID                            = 0x00181011UL,
      TAG_DATE_OF_SECONDARY_CAPTURE                              = 0x00181012UL,
      TAG_TIME_OF_SECONDARY_CAPTURE                              = 0x00181014UL,
      TAG_SECONDARY_CAPTURE_DEVICE_MANUFACTURER                  = 0x00181016UL,
      TAG_HARDCOPY_DEVICE_MANUFACTURER                           = 0x00181017UL,
      TAG_SECONDARY_CAPTURE_DEVICE_MANUFACTURER_MODEL_NAME       = 0x00181018UL,
      TAG_SECONDARY_CAPTURE_DEVICE_SOFTWARE_VERSION              = 0x00181019UL,
      TAG_HARDCOPY_DEVICE_SOFTWARE_VERSION                       = 0x0018101AUL,
      TAG_HARDCOPY_DEVICE_MANFUACTURER_MODEL_NAME                = 0x0018101BUL,
      TAG_SOFTWARE_VERSION                                       = 0x00181020UL,
      TAG_VIDEO_IMAGE_FORMAT_ACQUIRED                            = 0x00181022UL,
      TAG_DIGITAL_IMAGE_FORMAT_ACQUIRED                          = 0x00181023UL,
      TAG_PROTOCOL_NAME                                          = 0x00181030UL,
      TAG_CONTRAST_BOLUS_ROUTE                                   = 0x00181040UL,
      TAG_CONTRAST_BOLUS_VOLUME                                  = 0x00181041UL,
      TAG_CONTRAST_BOLUS_START_TIME                              = 0x00181042UL,
      TAG_CONTRAST_BOLUS_STOP_TIME                               = 0x00181043UL,
      TAG_CONTRAST_BOLUS_TOTAL_DOSE                              = 0x00181044UL,
      TAG_SYRINGE_COUNTS                                         = 0x00181045UL,
      TAG_CONTRAST_FLOW_RATE                                     = 0x00181046UL,
      TAG_CONTRAST_FLOW_DURATION                                 = 0x00181047UL,
      TAG_CONTRAST_BOLUS_INGREDIENT                              = 0x00181048UL,
      TAG_CONTRAST_BOLUS_INGREDIENT_CONCENTRATION                = 0x00181049UL,
      TAG_SPATIAL_RESOLUTION                                     = 0x00181050UL,
      TAG_TRIGGER_TIME                                           = 0x00181060UL,
      TAG_TRIGGER_SOURCE_OR_TYPE                                 = 0x00181061UL,
      TAG_NOMINAL_INTERVAL                                       = 0x00181062UL,
      TAG_FRAME_TIME                                             = 0x00181063UL,
      TAG_FRAMING_TYPE                                           = 0x00181064UL,
      TAG_FRAME_TIME_VECTOR                                      = 0x00181065UL,
      TAG_FRAME_DELAY                                            = 0x00181066UL,
      TAG_RADIOPHARMACEUTICAL_ROUTE                              = 0x00181070UL,
      TAG_RADIOPHARMACEUTICAL_VOLUME                             = 0x00181071UL,
      TAG_RADIOPHARMACEUTICAL_START_TIME                         = 0x00181072UL,
      TAG_RADIOPHARMACEUTICAL_STOP_TIME                          = 0x00181073UL,
      TAG_RADIONUCLIDE_TOTAL_DOSE                                = 0x00181074UL,
      TAG_RADIONUCLIDE_HALF_LIFE                                 = 0x00181075UL,
      TAG_RADIONUCLIDE_POSITRON_FRACTION                         = 0x00181076UL,
      TAG_RADIOPHARMACEUTICAL_SPECIFIC_ACTIVITY                  = 0x00181077UL,
      TAG_BEAT_REJECTION_FLAG                                    = 0x00181080UL,
      TAG_LOW_R_R_VALUE                                          = 0x00181081UL,
      TAG_HIGH_R_R_VALUE                                         = 0x00181082UL,
      TAG_INTERVALS_ACQUIRED                                     = 0x00181083UL,
      TAG_INTERVALS_REJECTED                                     = 0x00181084UL,
      TAG_PVC_REJECTION                                          = 0x00181085UL,
      TAG_SKIP_BEATS                                             = 0x00181086UL,
      TAG_HEART_RATE                                             = 0x00181088UL,
      TAG_CARDIAC_NUMBER_OF_IMAGES                               = 0x00181090UL,
      TAG_TRIGGER_WINDOW                                         = 0x00181094UL,
      TAG_RECONSTRUCTION_DIAMETER                                = 0x00181100UL,
      TAG_DISTANCE_SOURCE_TO_DETECTOR                            = 0x00181110UL,
      TAG_DISTANCE_SOURCE_TO_PATIENT                             = 0x00181111UL,
      TAG_ESTIMATED_RADIOGRAPHIC_MAGNIFICATION_FACTOR            = 0x00181114UL,
      TAG_GANTRY_DETECTOR_TILT                                   = 0x00181120UL,
      TAG_GANTRY_DETECTOR_SLEW                                   = 0x00181121UL,
      TAG_TABLE_HEIGHT                                           = 0x00181130UL,
      TAG_TABLE_TRAVERSE                                         = 0x00181131UL,
      TAG_TABLE_MOTION                                           = 0x00181134UL,
      TAG_TABLE_VERTICAL_INCREMENT                               = 0x00181135UL,
      TAG_TABLE_LATERAL_INCREMENT                                = 0x00181136UL,
      TAG_TABLE_LONGITUDINAL_INCREMENT                           = 0x00181137UL,
      TAG_TABLE_ANGLE                                            = 0x00181138UL,
      TAG_ROTATION_DIRECTION                                     = 0x00181140UL,
      TAG_ANGULAR_POSITION                                       = 0x00181141UL,
      TAG_RADIAL_POSITION                                        = 0x00181142UL,
      TAG_SCAN_ARC                                               = 0x00181143UL,
      TAG_ANGULAR_STEP                                           = 0x00181144UL,
      TAG_CENTER_OF_ROTATION_OFFSET                              = 0x00181145UL,
      TAG_ROTATION_OFFSET_RETIRED                                = 0x00181146UL,
      TAG_FIELD_OF_VIEW_SHAPE                                    = 0x00181147UL,
      TAG_FIELD_OF_VIEW_DIMENSION                                = 0x00181149UL,
      TAG_EXPOSURE_TIME                                          = 0x00181150UL,
      TAG_X_RAY_TUBE_CURRENT                                     = 0x00181151UL,
      TAG_EXPOSURE                                               = 0x00181152UL,
      TAG_EXPOSURE_IN_UAS                                        = 0x00181153UL,
      TAG_AVERAGE_PULSE_WIDTH                                    = 0x00181154UL,
      TAG_RADIATION_SETTING                                      = 0x00181155UL,
      TAG_RADIATION_MODE                                         = 0x0018115AUL,
      TAG_IMAGE_AREA_DOSE_PRODUCT                                = 0x0018115EUL,
      TAG_FILTER_TYPE                                            = 0x00181160UL,
      TAG_TYPE_OF_FILTERS                                        = 0x00181161UL,
      TAG_INTENSIFIER_SIZE                                       = 0x00181162UL,
      TAG_IMAGER_PIXEL_SPACING                                   = 0x00181164UL,
      TAG_GRID                                                   = 0x00181166UL,
      TAG_GENERATOR_POWER                                        = 0x00181170UL,
      TAG_COLLIMATOR_GRID_NAME                                   = 0x00181180UL,
      TAG_COLLIMATOR_TYPE                                        = 0x00181181UL,
      TAG_FOCAL_DISTANCE                                         = 0x00181182UL,
      TAG_X_FOCUS_CENTER                                         = 0x00181183UL,
      TAG_Y_FOCUS_CENTER                                         = 0x00181184UL,
      TAG_FOCAL_SPOT                                             = 0x00181190UL,
      TAG_DATE_OF_LAST_CALIBRATION                               = 0x00181200UL,
      TAG_TIME_OF_LAST_CALIBRATION                               = 0x00181201UL,
      TAG_CONVOLUTION_KERNEL                                     = 0x00181210UL,
      TAG_ACTUAL_FRAME_DURATION                                  = 0x00181242UL,
      TAG_COUNT_RATE                                             = 0x00181243UL,
      TAG_PREFERRED_PLAYBACK_SEQUENCING                          = 0x00181244UL,
      TAG_RECEIVING_COIL                                         = 0x00181250UL,
      TAG_TRANSMITTING_COIL                                      = 0x00181251UL,
      TAG_PLATE_TYPE                                             = 0x00181260UL,
      TAG_PHOSPHOR_TYPE                                          = 0x00181261UL,
      TAG_SCAN_VELOCITY                                          = 0x00181300UL,
      TAG_WHOLE_BODY_TECHNIQUE                                   = 0x00181301UL,
      TAG_SCAN_LENGTH                                            = 0x00181302UL,
      TAG_ACQUISITION_MATRIX                                     = 0x00181310UL,
      TAG_PHASE_ENCODING_DIRECTION                               = 0x00181312UL,
      TAG_FLIP_ANGLE                                             = 0x00181314UL,
      TAG_VARIABLE_FLIP_ANGLE_FLAG                               = 0x00181315UL,
      TAG_SAR                                                    = 0x00181316UL,
      TAG_DB_DT                                                  = 0x00181318UL,
      TAG_ACQUISITION_DEVICE_PROCESSING_DESCRIPTION              = 0x00181400UL,
      TAG_ACQUISITION_DEVICE_PROCESSING_CODE                     = 0x00181401UL,
      TAG_CASSETTE_ORIENTATION                                   = 0x00181402UL,
      TAG_CASSETTE_SIZE                                          = 0x00181403UL,
      TAG_EXPOSURES_ON_PLATE                                     = 0x00181404UL,
      TAG_RELATIVE_X_RAY_EXPOSURE                                = 0x00181405UL,
      TAG_COLUMN_ANGULATION                                      = 0x00181450UL,
      TAG_TOMO_LAYER_HEIGHT                                      = 0x00181460UL,
      TAG_TOMO_ANGLE                                             = 0x00181470UL,
      TAG_TOMO_TIME                                              = 0x00181480UL,
      TAG_POSITIONER_MOTION                                      = 0x00181500UL,
      TAG_POSITIONER_TYPE                                        = 0x00181508UL,
      TAG_POSITIONER_PRIMARY_ANGLE                               = 0x00181510UL,
      TAG_POSITIONER_SECONDARY_ANGLE                             = 0x00181511UL,
      TAG_POSITIONER_PRIMARY_ANGLE_INCREMENT                     = 0x00181520UL,
      TAG_POSITIONER_SECONDARY_ANGLE_INCREMENT                   = 0x00181521UL,
      TAG_DETECTOR_PRIMARY_ANGLE                                 = 0x00181530UL,
      TAG_DETECTOR_SECONDARY_ANGLE                               = 0x00181531UL,
      TAG_SHUTTER_SHAPE                                          = 0x00181600UL,
      TAG_SHUTTER_LEFT_VERTICAL_EDGE                             = 0x00181602UL,
      TAG_SHUTTER_RIGHT_VERTICAL_EDGE                            = 0x00181604UL,
      TAG_SHUTTER_UPPER_HORIZONTAL_EDGE                          = 0x00181606UL,
      TAG_SHUTTER_LOWER_HORIZONTAL_EDGE                          = 0x00181608UL,
      TAG_CENTER_OF_CIRCULAR_SHUTTER                             = 0x00181610UL,
      TAG_RADIUS_OF_CIRCULAR_SHUTTER                             = 0x00181612UL,
      TAG_VERTICES_OF_THE_POLYGONAL_SHUTTER                      = 0x00181620UL,
      TAG_COLLIMATOR_SHAPE                                       = 0x00181700UL,
      TAG_COLLIMATOR_LEFT_VERTICAL_EDGE                          = 0x00181702UL,
      TAG_COLLIMATOR_RIGHT_VERTICAL_EDGE                         = 0x00181704UL,
      TAG_COLLIMATOR_UPPER_HORIZONTAL_EDGE                       = 0x00181706UL,
      TAG_COLLIMATOR_LOWER_HORIZONTAL_EDGE                       = 0x00181708UL,
      TAG_CENTER_OF_CIRCULAR_COLLIMATOR                          = 0x00181710UL,
      TAG_RADIUS_OF_CIRCULAR_COLLIMATOR                          = 0x00181712UL,
      TAG_VERTICES_OF_THE_POLYGONAL_COLLIMATOR                   = 0x00181720UL,
      TAG_OUTPUT_POWER                                           = 0x00185000UL,
      TAG_TRANSDUCER_DATA                                        = 0x00185010UL,
      TAG_FOCUS_DEPTH                                            = 0x00185012UL,
      TAG_PROCESSING_FUNCTION                                    = 0x00185020UL,
      TAG_POSTPROCESSING_FUNCTION                                = 0x00185021UL,
      TAG_MECHANICAL_INDEX                                       = 0x00185022UL,
      TAG_THERMAL_INDEX                                          = 0x00185024UL,
      TAG_CRANIAL_THERMAL_INDEX                                  = 0x00185026UL,
      TAG_SOFT_TISSUE_THERMAL_INDEX                              = 0x00185027UL,
      TAG_SOFT_TISSUE_FOCUS_THERMAL_INDEX                        = 0x00185028UL,
      TAG_SOFT_TISSUE_SURFACE_THERMAL_INDEX                      = 0x00185029UL,
      TAG_DEPTH_OF_SCAN_FIELD                                    = 0x00185050UL,
      TAG_PATIENT_POSITION                                       = 0x00185100UL,
      TAG_VIEW_POSITION                                          = 0x00185101UL,
      TAG_IMAGE_TRANSFORMATION_MATRIX                            = 0x00185210UL,
      TAG_IMAGE_TRANSLATION_VECTOR                               = 0x00185212UL,
      TAG_SENSITIVITY                                            = 0x00186000UL,
      TAG_SEQUENCE_OF_ULTRASOUND_REGIONS                         = 0x00186011UL,
      TAG_REGION_SPATIAL_FORMAT                                  = 0x00186012UL,
      TAG_REGION_DATA_TYPE                                       = 0x00186014UL,
      TAG_REGION_FLAGS                                           = 0x00186016UL,
      TAG_REGION_LOCATION_MIN_X_0                                = 0x00186018UL,
      TAG_REGION_LOCATION_MIN_Y_0                                = 0x0018601AUL,
      TAG_REGION_LOCATION_MAX_X_1                                = 0x0018601CUL,
      TAG_REGION_LOCATION_MAX_Y_1                                = 0x0018601EUL,
      TAG_REFERENCE_PIXEL_X_0                                    = 0x00186020UL,
      TAG_REFERENCE_PIXEL_Y_0                                    = 0x00186022UL,
      TAG_PHYSICAL_UNITS_X_DIRECTION                             = 0x00186024UL,
      TAG_PHYSICAL_UNITS_Y_DIRECTION                             = 0x00186026UL,
      TAG_REFERENCE_PIXEL_PHYSICAL_VALUE_X                       = 0x00186028UL,
      TAG_REFERENCE_PIXEL_PHYSICAL_VALUE_Y                       = 0x0018602AUL,
      TAG_PHYSICAL_DELTA_X                                       = 0x0018602CUL,
      TAG_PHYSICAL_DELTA_Y                                       = 0x0018602EUL,
      TAG_TRANSDUCER_FREQUENCY                                   = 0x00186030UL,
      TAG_TRANSDUCER_TYPE                                        = 0x00186031UL,
      TAG_PULSE_REPETITION_FREQUENCY                             = 0x00186032UL,
      TAG_DOPPLER_CORRECTION_ANGLE                               = 0x00186034UL,
      TAG_STEERING_ANGLE                                         = 0x00186036UL,
      TAG_DOPPLER_SAMPLE_VOLUME_X_POSITION                       = 0x00186038UL,
      TAG_DOPPLER_SAMPLE_VOLUME_Y_POSITION                       = 0x0018603AUL,
      TAG_TM_LINE_POSITION_X_0                                   = 0x0018603CUL,
      TAG_TM_LINE_POSITION_Y_0                                   = 0x0018603EUL,
      TAG_TM_LINE_POSITION_X_1                                   = 0x00186040UL,
      TAG_TM_LINE_POSITION_Y_1                                   = 0x00186042UL,
      TAG_PIXEL_COMPONENT_ORGANIZATION                           = 0x00186044UL,
      TAG_PIXEL_COMPONENT_MASK                                   = 0x00186046UL,
      TAG_PIXEL_COMPONENT_RANGE_START                            = 0x00186048UL,
      TAG_PIXEL_COMPONENT_RANGE_STOP                             = 0x0018604AUL,
      TAG_PIXEL_COMPONENT_PHYSICAL_UNITS                         = 0x0018604CUL,
      TAG_PIXEL_COMPONENT_DATA_TYPE                              = 0x0018604EUL,
      TAG_NUMBER_OF_TABLE_BREAK_POINTS                           = 0x00186050UL,
      TAG_TABLE_OF_X_BREAK_POINTS                                = 0x00186052UL,
      TAG_TABLE_OF_Y_BREAK_POINTS                                = 0x00186054UL,
      TAG_NUMBER_OF_TABLE_ENTRIES                                = 0x00186056UL,
      TAG_TABLE_OF_PIXEL_VALUES                                  = 0x00186058UL,
      TAG_TABLE_OF_PARAMETER_VALUES                              = 0x0018605AUL,
      TAG_DETECTOR_TYPE                                          = 0x00187004UL,

      TAG_STUDY_INSTANCE_UID                                     = 0x0020000DUL,
      TAG_SERIES_INSTANCE_UID                                    = 0x0020000EUL,
      TAG_STUDY_ID                                               = 0x00200010UL,
      TAG_SERIES_NUMBER                                          = 0x00200011UL,
      TAG_ACQUISITION_NUMBER                                     = 0x00200012UL,
      TAG_INSTANCE_NUMBER                                        = 0x00200013UL,
      TAG_ISOTOPE_NUMBER_RETIRED                                 = 0x00200014UL,
      TAG_PHASE_NUMBER_RETIRED                                   = 0x00200015UL,
      TAG_INTERVAL_NUMBER_RETIRED                                = 0x00200016UL,
      TAG_TIME_SLOT_NUMBER_RETIRED                               = 0x00200017UL,
      TAG_ANGLE_NUMBER_RETIRED                                   = 0x00200018UL,
      TAG_ITEM_NUMBER                                            = 0x00200019UL,
      TAG_PATIENT_ORIENTATION                                    = 0x00200020UL,
      TAG_OVERLAY_NUMBER                                         = 0x00200022UL,
      TAG_CURVE_NUMBER                                           = 0x00200024UL,
      TAG_LOOKUP_TABLE_NUMBER                                    = 0x00200026UL,
      TAG_IMAGE_POSITION_PATIENT                                 = 0x00200032UL,
      TAG_IMAGE_ORIENTATION_PATIENT                              = 0x00200037UL,
      TAG_FRAME_OF_REFERENCE_UID                                 = 0x00200052UL,
      TAG_LATERALITY                                             = 0x00200060UL,
      TAG_TEMPORAL_POSITION_IDENTIFIER                           = 0x00200100UL,
      TAG_NUMBER_OF_TEMPORAL_POSITIONS                           = 0x00200105UL,
      TAG_TEMPORAL_RESOLUTION                                    = 0x00200110UL,
      TAG_SERIES_IN_STUDY                                        = 0x00201000UL,
      TAG_IMAGES_IN_ACQUISITION                                  = 0x00201002UL,
      TAG_ACQUISITIONS_IN_STUDY                                  = 0x00201004UL,
      TAG_POSITION_REFERENCE_INDICATOR                           = 0x00201040UL,
      TAG_SLICE_LOCATION                                         = 0x00201041UL,
      TAG_OTHER_STUDY_NUMBERS                                    = 0x00201070UL,
      TAG_NUMBER_OF_PATIENT_RELATED_STUDIES                      = 0x00201200UL,
      TAG_NUMBER_OF_PATIENT_RELATED_SERIES                       = 0x00201202UL,
      TAG_NUMBER_OF_PATIENT_RELATED_INSTANCES                    = 0x00201204UL,
      TAG_NUMBER_OF_STUDY_RELATED_SERIES                         = 0x00201206UL,
      TAG_NUMBER_OF_STUDY_RELATED_INSTANCES                      = 0x00201208UL,
      TAG_NUMBER_OF_SERIES_RELATED_INSTANCES                     = 0x00201209UL,
      TAG_IMAGE_COMMENTS                                         = 0x00204000UL,

      TAG_SAMPLES_PER_PIXEL                                      = 0x00280002UL,
      TAG_PHOTOMETRIC_INTERPRETATION                             = 0x00280004UL,
      TAG_PLANAR_CONFIGURATION                                   = 0x00280006UL,
      TAG_NUMBER_OF_FRAMES                                       = 0x00280008UL,
      TAG_FRAME_INCREMENT_POINTER                                = 0x00280009UL,
      TAG_ROWS                                                   = 0x00280010UL,
      TAG_COLUMNS                                                = 0x00280011UL,
      TAG_PLANES                                                 = 0x00280012UL,
      TAG_ULTRASOUND_COLOR_DATA_PRESENT                          = 0x00280014UL,
      TAG_PIXEL_SPACING                                          = 0x00280030UL,
      TAG_ZOOM_FACTOR                                            = 0x00280031UL,
      TAG_ZOOM_CENTER                                            = 0x00280032UL,
      TAG_PIXEL_ASPECT_RATIO                                     = 0x00280034UL,
      TAG_CORRECTED_IMAGE                                        = 0x00280051UL,
      TAG_BITS_ALLOCATED                                         = 0x00280100UL,
      TAG_BITS_STORED                                            = 0x00280101UL,
      TAG_HIGH_BIT                                               = 0x00280102UL,
      TAG_PIXEL_REPRESENTATION                                   = 0x00280103UL,
      TAG_SMALLEST_IMAGE_PIXEL_VALUE                             = 0x00280106UL,
      TAG_LARGEST_IMAGE_PIXEL_VALUE                              = 0x00280107UL,
      TAG_SMALLEST_PIXEL_VALUE_IN_SERIES                         = 0x00280108UL,
      TAG_LARGEST_PIXEL_VALUE_IN_SERIES                          = 0x00280109UL,
      TAG_SMALLEST_IMAGE_PIXEL_VALUE_IN_PLANE                    = 0x00280110UL,
      TAG_LARGEST_IMAGE_PIXEL_VALUE_IN_PLANE                     = 0x00280111UL,
      TAG_PIXEL_PADDING_VALUE                                    = 0x00280120UL,
      TAG_BURNED_IN_ANNOTATION                                   = 0x00280301UL,
      TAG_PIXEL_INTENSITY_RELATIONSHIP                           = 0x00281040UL,
      TAG_WINDOW_CENTER                                          = 0x00281050UL,
      TAG_WINDOW_WIDTH                                           = 0x00281051UL,
      TAG_RESCALE_INTERCEPT                                      = 0x00281052UL,
      TAG_RESCALE_SLOPE                                          = 0x00281053UL,
      TAG_RESCALE_TYPE                                           = 0x00281054UL,
      TAG_WINDOW_CENTER_WIDTH_EXPLANATION                        = 0x00281055UL,
      TAG_RECOMMENDED_VIEWING_MODE                               = 0x00281090UL,
      TAG_RED_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR              = 0x00281101UL,
      TAG_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR            = 0x00281102UL,
      TAG_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR             = 0x00281103UL,
      TAG_PALETTE_COLOR_LOOKUP_TABLE_UID                         = 0x00281199UL,
      TAG_RED_PALETTE_COLOR_LOOKUP_TABLE_DATA                    = 0x00281201UL,
      TAG_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DATA                  = 0x00281202UL,
      TAG_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DATA                   = 0x00281203UL,
      TAG_SEGMENTED_RED_PALETTE_COLOR_LOOKUP_TABLE_DATA          = 0x00281221UL,
      TAG_SEGMENTED_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DATA        = 0x00281222UL,
      TAG_SEGMENTED_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DATA         = 0x00281223UL,
      TAG_LOSSY_IMAGE_COMPRESSION                                = 0x00282110UL,
      TAG_MODALITY_LUT_SEQUENCE                                  = 0x00283000UL,
      TAG_LUT_DESCRIPTOR                                         = 0x00283002UL,
      TAG_LUT_EXPLANATION                                        = 0x00283003UL,
      TAG_MODALITY_LUT_TYPE                                      = 0x00283004UL,
      TAG_LUT_DATA                                               = 0x00283006UL,
      TAG_VOI_LUT_SEQUENCE                                       = 0x00283010UL,
      TAG_BIPLANE_ACQUISITION_SEQUENCE                           = 0x00285000UL,
      TAG_REPRESENTATIVE_FRAME_NUMBER                            = 0x00286010UL,
      TAG_FRAME_NUMBERS_OF_INTEREST_FOI                          = 0x00286020UL,
      TAG_FRAME_OF_INTEREST_DESCRIPTION                          = 0x00286022UL,
      TAG_MASK_POINTER                                           = 0x00286030UL,
      TAG_R_WAVE_POINTER                                         = 0x00286040UL,
      TAG_MASK_SUBTRACTION_SEQUENCE                              = 0x00286100UL,
      TAG_MASK_OPERATION                                         = 0x00286101UL,
      TAG_APPLICABLE_FRAME_RANGE                                 = 0x00286102UL,
      TAG_MASK_FRAME_NUMBERS                                     = 0x00286110UL,
      TAG_CONTRAST_FRAME_AVERAGING                               = 0x00286112UL,
      TAG_MASK_SUB_PIXEL_SHIFT                                   = 0x00286114UL,
      TAG_TID_OFFSET                                             = 0x00286120UL,
      TAG_MASK_OPERATION_EXPLANATION                             = 0x00286190UL,

      TAG_STUDY_STATUS_ID                                        = 0x0032000AUL,
      TAG_STUDY_PRIORITY_ID                                      = 0x0032000CUL,
      TAG_STUDY_ID_ISSUER                                        = 0x00320012UL,
      TAG_STUDY_VERIFIED_DATE                                    = 0x00320032UL,
      TAG_STUDY_VERIFIED_TIME                                    = 0x00320033UL,
      TAG_STUDY_READ_DATE                                        = 0x00320034UL,
      TAG_STUDY_READ_TIME                                        = 0x00320035UL,
      TAG_SCHEDULED_STUDY_START_DATE                             = 0x00321000UL,
      TAG_SCHEDULED_STUDY_START_TIME                             = 0x00321001UL,
      TAG_SCHEDULED_STUDY_STOP_DATE                              = 0x00321010UL,
      TAG_SCHEDULED_STUDY_STOP_TIME                              = 0x00321011UL,
      TAG_SCHEDULED_STUDY_LOCATION                               = 0x00321020UL,
      TAG_SCHEDULED_STUDY_LOCATION_AE_TITLE                      = 0x00321021UL,
      TAG_REASON_FOR_STUDY                                       = 0x00321030UL,
      TAG_REQUESTING_PHYSICIAN                                   = 0x00321032UL,
      TAG_REQUESTING_SERVICE                                     = 0x00321033UL,
      TAG_STUDY_ARRIVAL_DATE                                     = 0x00321040UL,
      TAG_STUDY_ARRIVAL_TIME                                     = 0x00321041UL,
      TAG_STUDY_COMPLETION_DATE                                  = 0x00321050UL,
      TAG_STUDY_COMPLETION_TIME                                  = 0x00321051UL,
      TAG_STUDY_COMPONENT_STATUS_ID                              = 0x00321055UL,
      TAG_REQUESTED_PROCEDURE_DESCRIPTION                        = 0x00321060UL,
      TAG_REQUESTED_PROCEDURE_CODE_SEQUENCE                      = 0x00321064UL,
      TAG_REQUESTED_CONTRAST_AGENT                               = 0x00321070UL,
      TAG_STUDY_COMMENTS                                         = 0x00324000UL,

      TAG_REFERENCED_PATIENT_ALIAS_SEQUENCE                      = 0x00380004UL,
      TAG_VISIT_STATUS_ID                                        = 0x00380008UL,
      TAG_ADMISSION_ID                                           = 0x00380010UL,
      TAG_ISSUER_OF_ADMISSION_ID                                 = 0x00380011UL,
      TAG_ROUTE_OF_ADMISSIONS                                    = 0x00380016UL,
      TAG_SCHEDULED_ADMISSION_DATE                               = 0x0038001AUL,
      TAG_SCHEDULED_ADMISSION_TIME                               = 0x0038001BUL,
      TAG_SCHEDULED_DISCHARGE_DATE                               = 0x0038001CUL,
      TAG_SCHEDULED_DISCHARGE_TIME                               = 0x0038001DUL,
      TAG_SCHEDULED_PATIENT_INSTITUTION_RESIDENCE                = 0x0038001EUL,
      TAG_ADMITTING_DATE                                         = 0x00380020UL,
      TAG_ADMITTING_TIME                                         = 0x00380021UL,
      TAG_DISCHARGE_DATE                                         = 0x00380030UL,
      TAG_DISCHARGE_TIME                                         = 0x00380032UL,
      TAG_DISCHARGE_DIAGNOSIS_DESCRIPTION                        = 0x00380040UL,
      TAG_DISCHARGE_DIAGNOSIS_CODE_SEQUENCE                      = 0x00380044UL,
      TAG_SPECIAL_NEEDS                                          = 0x00380050UL,
      TAG_CURRENT_PATIENT_LOCATION                               = 0x00380300UL,
      TAG_PATIENT_INSTITUTION_RESIDENCE                          = 0x00380400UL,
      TAG_PATIENT_STATE                                          = 0x00380500UL,
      TAG_VISIT_COMMENTS                                         = 0x00384000UL,

      TAG_SCHEDULED_STATION_AE_TITLE                             = 0x00400001UL,
      TAG_SCHEDULED_PROCEDURE_STEP_START_DATE                    = 0x00400002UL,
      TAG_SCHEDULED_PROCEDURE_STEP_START_TIME                    = 0x00400003UL,
      TAG_SCHEDULED_PROCEDURE_STEP_END_DATE                      = 0x00400004UL,
      TAG_SCHEDULED_PROCEDURE_STEP_END_TIME                      = 0x00400005UL,
      TAG_SCHEDULED_PERFORMING_PHYSICIAN_NAME                    = 0x00400006UL,
      TAG_SCHEDULED_PROCEDURE_STEP_DESCRIPTION                   = 0x00400007UL,
      TAG_SCHEDULED_ACTION_ITEM_CODE_SEQUENCE                    = 0x00400008UL,
      TAG_SCHEDULED_PROCEDURE_STEP_ID                            = 0x00400009UL,
      TAG_SCHEDULED_STATION_NAME                                 = 0x00400010UL,
      TAG_SCHEDULED_PROCEDURE_STEP_LOCATION                      = 0x00400011UL,
      TAG_PRE_MEDICATION                                         = 0x00400012UL,
      TAG_SCHEDULED_PROCEDURE_STEP_STATUS                        = 0x00400020UL,
      TAG_SCHEDULED_PROCEDURE_STEP_SEQUENCE                      = 0x00400100UL,
      TAG_REFERENCED_STANDALONE_SOP_INSTANCE_SEQUENCE            = 0x00400220UL,
      TAG_PERFORMED_STATION_AE_TITLE                             = 0x00400241UL,
      TAG_PERFORMED_STATION_NAME                                 = 0x00400242UL,
      TAG_PERFORMED_LOCATION                                     = 0x00400243UL,
      TAG_PERFORMED_PROCEDURE_STEP_START_DATE                    = 0x00400244UL,
      TAG_PERFORMED_PROCEDURE_STEP_START_TIME                    = 0x00400245UL,
      TAG_PERFORMED_PROCEDURE_STEP_END_DATE                      = 0x00400250UL,
      TAG_PERFORMED_PROCEDURE_STEP_END_TIME                      = 0x00400251UL,
      TAG_PERFORMED_PROCEDURE_STEP_STATUS                        = 0x00400252UL,
      TAG_PERFORMED_PROCEDURE_STEP_ID                            = 0x00400253UL,
      TAG_PERFORMED_PROCEDURE_STEP_DESCRIPTION                   = 0x00400254UL,
      TAG_PERFORMED_PROCEDURE_TYPE_DESCRIPTION                   = 0x00400255UL,
      TAG_PERFORMED_ACTION_ITEM_SEQUENCE                         = 0x00400260UL,
      TAG_SCHEDULED_STEP_ATTRIBUTES_SEQUENCE                     = 0x00400270UL,
      TAG_REQUEST_ATTRIBUTES_SEQUENCE                            = 0x00400275UL,
      TAG_COMMENTS_ON_THE_PERFORMED_PROCEDURE_STEPS              = 0x00400280UL,
      TAG_QUANTITY_SEQUENCE                                      = 0x00400293UL,
      TAG_QUANTITY                                               = 0x00400294UL,
      TAG_MEASURING_UNITS_SEQUENCE                               = 0x00400295UL,
      TAG_BILLING_ITEM_SEQUENCE                                  = 0x00400296UL,
      TAG_TOTAL_TIME_OF_FLUOROSCOPY                              = 0x00400300UL,
      TAG_TOTAL_NUMBER_OF_EXPOSURES                              = 0x00400301UL,
      TAG_ENTRANCE_DOSE                                          = 0x00400302UL,
      TAG_EXPOSED_AREA                                           = 0x00400303UL,
      TAG_DISTANCE_SOURCE_TO_ENTRANCE                            = 0x00400306UL,
      TAG_COMMENTS_ON_RADIATION_DOSE                             = 0x00400310UL,
      TAG_ORGAN_EXPOSED                                          = 0x00400318UL,
      TAG_BILLING_PROCEDURE_STEP_SEQUENCE                        = 0x00400320UL,
      TAG_FILM_CONSUMPTION_SEQUENCE                              = 0x00400321UL,
      TAG_BILLING_SUPPLIES_AND_DEVICES_SEQUENCE                  = 0x00400324UL,
      TAG_REFERENCED_PROCEDURE_STEP_SEQUENCE                     = 0x00400330UL,
      TAG_PERFORMED_SERIES_SEQUENCE                              = 0x00400340UL,
      TAG_COMMENTS_ON_THE_SCHEDULED_PROCEDURE_STEP               = 0x00400400UL,
      TAG_REQUESTED_PROCEDURE_ID                                 = 0x00401001UL,
      TAG_REASON_FOR_THE_REQUESTED_PROCEDURE                     = 0x00401002UL,
      TAG_REQUESTED_PROCEDURE_PRIORITY                           = 0x00401003UL,
      TAG_PATIENT_TRANSPORT_ARRANGEMENTS                         = 0x00401004UL,
      TAG_REQUESTED_PROCEDURE_LOCATION                           = 0x00401005UL,
      TAG_PLACER_ORDER_NUMBER_PROCEDURE_RETIRED                  = 0x00401006UL,
      TAG_FILLER_ORDER_NUMBER_PROCEDURE_RETIRED                  = 0x00401007UL,
      TAG_CONFIDENTIALITY_CODE                                   = 0x00401008UL,
      TAG_REPORTING_PRIORITY                                     = 0x00401009UL,
      TAG_NAMES_OF_INTENDED_RECIPIENTS_OF_RESULTS                = 0x00401010UL,
      TAG_REQUESTED_PROCEDURE_COMMENTS                           = 0x00401400UL,
      TAG_REASON_FOR_THE_IMAGING_SERVICE_REQUEST                 = 0x00402001UL,
      TAG_ISSUE_DATE_OF_IMAGING_SERVICE_REQUEST                  = 0x00402004UL,
      TAG_ISSUE_TIME_OF_IMAGING_SERVICE_REQUEST                  = 0x00402005UL,
      TAG_PLACER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST_RETIRED    = 0x00402006UL,
      TAG_FILLER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST_RETIRED    = 0x00402007UL,
      TAG_ORDER_ENTERED_BY                                       = 0x00402008UL,
      TAG_ORDER_ENTERER_LOCATION                                 = 0x00402009UL,
      TAG_ORDER_CALLBACK_PHONE_NUMBER                            = 0x00402010UL,
      TAG_PLACER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST            = 0x00402016UL,
      TAG_FILLER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST            = 0x00402017UL,
      TAG_IMAGING_SERVICE_REQUEST_COMMENTS                       = 0x00402400UL,
      TAG_CONFIDENTIALITY_CONSTRAINT_ON_PATIENT_DATA_DESCRIPTION = 0x00403001UL,

      TAG_CALIBRATION_IMAGE                                      = 0x00500004UL,
      TAG_DEVICE_SEQUENCE                                        = 0x00500010UL,
      TAG_DEVICE_LENGTH                                          = 0x00500014UL,
      TAG_DEVICE_DIAMETER                                        = 0x00500016UL,
      TAG_DEVICE_DIAMETER_UNITS                                  = 0x00500017UL,
      TAG_DEVICE_VOLUME                                          = 0x00500018UL,
      TAG_INTER_MARKER_DISTANCE                                  = 0x00500019UL,
      TAG_DEVICE_DESCRIPTION                                     = 0x00500020UL,

      TAG_ENERGY_WINDOW_VECTOR                                   = 0x00540010UL,
      TAG_NUMBER_OF_ENERGY_WINDOWS                               = 0x00540011UL,
      TAG_ENERGY_WINDOW_INFORMATION_SEQUENCE                     = 0x00540012UL,
      TAG_ENERGY_WINDOW_RANGE_SEQUENCE                           = 0x00540013UL,
      TAG_ENERGY_WINDOW_LOWER_LIMIT                              = 0x00540014UL,
      TAG_ENERGY_WINDOW_UPPER_LIMIT                              = 0x00540015UL,
      TAG_RADIOPHARMACEUTICAL_INFORMATION_SEQUENCE               = 0x00540016UL,
      TAG_RESIDUAL_SYRINGE_COUNTS                                = 0x00540017UL,
      TAG_ENERGY_WINDOW_NAME                                     = 0x00540018UL,
      TAG_DETECTOR_VECTOR                                        = 0x00540020UL,
      TAG_NUMBER_OF_DETECTORS                                    = 0x00540021UL,
      TAG_DETECTOR_INFORMATION_SEQUENCE                          = 0x00540022UL,
      TAG_PHASE_VECTOR                                           = 0x00540030UL,
      TAG_NUMBER_OF_PHASES                                       = 0x00540031UL,
      TAG_PHASE_INFORMATION_SEQUENCE                             = 0x00540032UL,
      TAG_NUMBER_OF_FRAMES_IN_PHASE                              = 0x00540033UL,
      TAG_PHASE_DELAY                                            = 0x00540036UL,
      TAG_PAUSE_BETWEEN_FRAMES                                   = 0x00540038UL,
      TAG_ROTATION_VECTOR                                        = 0x00540050UL,
      TAG_NUMBER_OF_ROTATIONS                                    = 0x00540051UL,
      TAG_ROTATION_INFORMATION_SEQUENCE                          = 0x00540052UL,
      TAG_NUMBER_OF_FRAMES_IN_ROTATION                           = 0x00540053UL,
      TAG_R_R_INTERVAL_VECTOR                                    = 0x00540060UL,
      TAG_NUMBER_OF_R_R_INTERVALS                                = 0x00540061UL,
      TAG_GATED_INFORMATION_SEQUENCE                             = 0x00540062UL,
      TAG_DATA_INFORMATION_SEQUENCE                              = 0x00540063UL,
      TAG_TIME_SLOT_VECTOR                                       = 0x00540070UL,
      TAG_NUMBER_OF_TIME_SLOTS                                   = 0x00540071UL,
      TAG_TIME_SLOT_INFORMATION_SEQUENCE                         = 0x00540072UL,
      TAG_TIME_SLOT_TIME                                         = 0x00540073UL,
      TAG_SLICE_VECTOR                                           = 0x00540080UL,
      TAG_NUMBER_OF_SLICES                                       = 0x00540081UL,
      TAG_ANGULAR_VIEW_VECTOR                                    = 0x00540090UL,
      TAG_TIME_SLICE_VECTOR                                      = 0x00540100UL,
      TAG_NUMBER_OF_TIME_SLICES                                  = 0x00540101UL,
      TAG_START_ANGLE                                            = 0x00540200UL,
      TAG_TYPE_OF_DETECTOR_MOTION                                = 0x00540202UL,
      TAG_TRIGGER_VECTOR                                         = 0x00540210UL,
      TAG_NUMBER_OF_TRIGGERS_IN_PHASE                            = 0x00540211UL,
      TAG_VIEW_CODE_SEQUENCE                                     = 0x00540220UL,
      TAG_VIEW_MODIFIER_CODE_SEQUENCE                            = 0x00540222UL,
      TAG_RADIONUCLIDE_CODE_SEQUENCE                             = 0x00540300UL,
      TAG_ADMINISTRATION_ROUTE_CODE_SEQUENCE                     = 0x00540302UL,
      TAG_RADIOPHARMACEUTICAL_CODE_SEQUENCE                      = 0x00540304UL,
      TAG_CALIBRATION_DATA_SEQUENCE                              = 0x00540306UL,
      TAG_ENERGY_WINDOW_NUMBER                                   = 0x00540308UL,
      TAG_IMAGE_ID                                               = 0x00540400UL,
      TAG_PATIENT_ORIENTATION_CODE_SEQUENCE                      = 0x00540410UL,
      TAG_PATIENT_ORIENTATION_MODIFIER_CODE_SEQUENCE             = 0x00540412UL,
      TAG_PATIENT_GANTRY_RELATIONSHIP_CODE_SEQUENCE              = 0x00540414UL,
      TAG_SERIES_TYPE                                            = 0x00541000UL,
      TAG_UNITS                                                  = 0x00541001UL,
      TAG_COUNTS_SOURCE                                          = 0x00541002UL,
      TAG_REPROJECTION_METHOD                                    = 0x00541004UL,
      TAG_RANDOMS_CORRECTION_METHOD                              = 0x00541100UL,
      TAG_ATTENUATION_CORRECTION_METHOD                          = 0x00541101UL,
      TAG_DECAY_CORRECTION                                       = 0x00541102UL,
      TAG_RECONSTRUCTION_METHOD                                  = 0x00541103UL,
      TAG_DETECTOR_LINES_OF_RESPONSE_USED                        = 0x00541104UL,
      TAG_SCATTER_CORRECTION_METHOD                              = 0x00541105UL,
      TAG_AXIAL_ACCEPTANCE                                       = 0x00541200UL,
      TAG_AXIAL_MASH                                             = 0x00541201UL,
      TAG_TRANSVERSE_MASH                                        = 0x00541202UL,
      TAG_DETECTOR_ELEMENT_SIZE                                  = 0x00541203UL,
      TAG_COINCIDENCE_WINDOW_WIDTH                               = 0x00541210UL,
      TAG_SECONDARY_COUNTS_TYPE                                  = 0x00541220UL,
      TAG_FRAME_REFERENCE_TIME                                   = 0x00541300UL,
      TAG_PRIMARY_PROMPTS_COUNTS_ACCUMULATED                     = 0x00541310UL,
      TAG_SECONDARY_COUNTS_ACCUMULATED                           = 0x00541311UL,
      TAG_SLICE_SENSITIVITY_FACTOR                               = 0x00541320UL,
      TAG_DECAY_FACTOR                                           = 0x00541321UL,
      TAG_DOSE_CALIBRATION_FACTOR                                = 0x00541322UL,
      TAG_SCATTER_FRACTION_FACTOR                                = 0x00541323UL,
      TAG_DEAD_TIME_FACTOR                                       = 0x00541324UL,
      TAG_IMAGE_INDEX                                            = 0x00541330UL,
      TAG_COUNTS_INCLUDED                                        = 0x00541400UL,
      TAG_DEAD_TIME_CORRECTION_FLAG                              = 0x00541401UL,

      TAG_HISTOGRAM_SEQUENCE                                     = 0x00603000UL,
      TAG_HISTOGRAM_NUMBER_OF_BINS                               = 0x00603002UL,
      TAG_HISTOGRAM_FIRST_BIN_VALUE                              = 0x00603004UL,
      TAG_HISTOGRAM_LAST_BIN_VALUE                               = 0x00603006UL,
      TAG_HISTOGRAM_BIN_WIDTH                                    = 0x00603008UL,
      TAG_HISTOGRAM_EXPLANATION                                  = 0x00603010UL,
      TAG_HISTOGRAM_DATA                                         = 0x00603020UL,

      TAG_STORAGE_MEDIA_FILE_SET_ID                              = 0x00880130UL,
      TAG_STORAGE_MEDIA_FILE_SET_UID                             = 0x00880140UL,
      TAG_ICON_IMAGE_SEQUENCE                                    = 0x00880200UL,
      TAG_TOPIC_TITLE                                            = 0x00880904UL,
      TAG_TOPIC_SUBJECT                                          = 0x00880906UL,
      TAG_TOPIC_AUTHOR                                           = 0x00880910UL,
      TAG_TOPIC_KEY_WORDS                                        = 0x00880912UL,

      TAG_NUMBER_OF_COPIES                                       = 0x20000010UL,
      TAG_PRINTER_CONFIGURATION_SEQUENCE                         = 0x2000001EUL,
      TAG_PRINT_PRIORITY                                         = 0x20000020UL,
      TAG_MEDIUM_TYPE                                            = 0x20000030UL,
      TAG_FILM_DESTINATION                                       = 0x20000040UL,
      TAG_FILM_SESSION_LABEL                                     = 0x20000050UL,
      TAG_MEMORY_ALLOCATION                                      = 0x20000060UL,
      TAG_MAXIMUM_MEMORY_ALLOCATION                              = 0x20000061UL,
      TAG_COLOR_IMAGE_PRINTING_FLAG                              = 0x20000062UL,
      TAG_COLLATION_FLAG                                         = 0x20000063UL,
      TAG_ANNOTATION_FLAG                                        = 0x20000065UL,
      TAG_IMAGE_OVERLAY_FLAG                                     = 0x20000067UL,
      TAG_PRESENTATION_LUT_FLAG                                  = 0x20000069UL,
      TAG_IMAGE_BOX_PRESENTATION_LUT_FLAG                        = 0x2000006AUL,
      TAG_MEMORY_BIT_DEPTH                                       = 0x200000A0UL,
      TAG_PRINTING_BIT_DEPTH                                     = 0x200000A1UL,
      TAG_MEDIA_INSTALLED_SEQUENCE                               = 0x200000A2UL,
      TAG_OTHER_MEDIA_AVAILABLE_SEQUENCE                         = 0x200000A4UL,
      TAG_SUPPORTED_IMAGE_DISPLAY_FORMATS_SEQUENCE               = 0x200000A8UL,
      TAG_REFERENCED_FILM_BOX_SEQUENCE                           = 0x20000500UL,
      TAG_REFERENCED_STORED_PRINT_SEQUENCE                       = 0x20000510UL,

      TAG_IMAGE_DISPLAY_FORMAT                                   = 0x20100010UL,
      TAG_ANNOTATION_DISPLAY_FORMAT_ID                           = 0x20100030UL,
      TAG_FILM_ORIENTATION                                       = 0x20100040UL,
      TAG_FILM_SIZE_ID                                           = 0x20100050UL,
      TAG_PRINTER_RESOLUTION_ID                                  = 0x20100052UL,
      TAG_DEFAULT_PRINTER_RESOLUTION_ID                          = 0x20100054UL,
      TAG_MAGNIFICATION_TYPE                                     = 0x20100060UL,
      TAG_SMOOTHING_TYPE                                         = 0x20100080UL,
      TAG_DEFAULT_MAGNIFICATION_TYPE                             = 0x201000A6UL,
      TAG_OTHER_MAGNIFICATION_TYPES_AVAILABLE                    = 0x201000A7UL,
      TAG_DEFAULT_SMOOTHING_TYPE                                 = 0x201000A8UL,
      TAG_OTHER_SMOOTHING_TYPES_AVAILABLE                        = 0x201000A9UL,
      TAG_BORDER_DENSITY                                         = 0x20100100UL,
      TAG_EMPTY_IMAGE_DENSITY                                    = 0x20100110UL,
      TAG_MIN_DENSITY                                            = 0x20100120UL,
      TAG_MAX_DENSITY                                            = 0x20100130UL,
      TAG_TRIM                                                   = 0x20100140UL,
      TAG_CONFIGURATION_INFORMATION                              = 0x20100150UL,
      TAG_CONFIGURATION_INFORMATION_DESCRIPTION                  = 0x20100152UL,
      TAG_MAXIMUM_COLLATED_FILMS                                 = 0x20100154UL,
      TAG_ILLUMINATION                                           = 0x2010015EUL,
      TAG_REFLECTED_AMBIENT_LIGHT                                = 0x20100160UL,
      TAG_PRINTER_PIXEL_SPACING                                  = 0x20100376UL,
      TAG_REFERENCED_FILM_SESSION_SEQUENCE                       = 0x20100500UL,
      TAG_REFERENCED_IMAGE_BOX_SEQUENCE                          = 0x20100510UL,
      TAG_REFERENCED_BASIC_ANNOTATION_BOX_SEQUENCE               = 0x20100520UL,

      TAG_IMAGE_POSITION                                         = 0x20200010UL,
      TAG_POLARITY                                               = 0x20200020UL,
      TAG_REQUESTED_IMAGE_SIZE                                   = 0x20200030UL,
      TAG_REQUESTED_DECIMATE_CROP_BEHAVIOR                       = 0x20200040UL,
      TAG_REQUESTED_RESOLUTION_ID                                = 0x20200050UL,
      TAG_REQUESTED_IMAGE_SIZE_FLAG                              = 0x202000A0UL,
      TAG_DECIMATE_CROP_RESULT                                   = 0x202000A2UL,
      TAG_BASIC_GRAYSCALE_IMAGE_SEQUENCE                         = 0x20200110UL,
      TAG_BASIC_COLOR_IMAGE_SEQUENCE                             = 0x20200111UL,
      TAG_REFERENCED_IMAGE_OVERLAY_BOX_SEQUENCE_RETIRED          = 0x20200130UL,
      TAG_REFERENCED_VOI_LUT_BOX_SEQUENCE_RETIRED                = 0x20200140UL,

      TAG_ANNOTATION_POSITION                                    = 0x20300010UL,
      TAG_TEXT_STRING                                            = 0x20300020UL,

      TAG_REFERENCED_OVERLAY_PLANE_SEQUENCE                      = 0x20400010UL,
      TAG_REFERENCED_OVERLAY_PLANE_GROUPS                        = 0x20400011UL,
      TAG_OVERLAY_PIXEL_DATA_SEQUENCE                            = 0x20400020UL,
      TAG_OVERLAY_MAGNIFICATION_TYPE                             = 0x20400060UL,
      TAG_OVERLAY_SMOOTHING_TYPE                                 = 0x20400070UL,
      TAG_OVERLAY_OR_IMAGE_MAGNIFICATION                         = 0x20400072UL,
      TAG_MAGNIFY_TO_NUMBER_OF_COLUMNS                           = 0x20400074UL,
      TAG_OVERLAY_FOREGROUND_DENSITY                             = 0x20400080UL,
      TAG_OVERLAY_BACKGROUND_DENSITY                             = 0x20400082UL,
      TAG_OVERLAY_MODE_RETIRED                                   = 0x20400090UL,
      TAG_THRESHOLD_DENSITY_RETIRED                              = 0x20400100UL,
      TAG_REFERENCED_IMAGE_BOX_SEQUENCE_RETIRED                  = 0x20400500UL,

      TAG_PRESENTATION_LUT_SEQUENCE                              = 0x20500010UL,
      TAG_PRESENTATION_LUT_SHAPE                                 = 0x20500020UL,
      TAG_REFERENCED_PRESENTATION_LUT_SEQUENCE                   = 0x20500500UL,

      TAG_PRINT_JOB_ID                                           = 0x21000010UL,
      TAG_EXECUTION_STATUS                                       = 0x21000020UL,
      TAG_EXECUTION_STATUS_INFO                                  = 0x21000030UL,
      TAG_CREATION_DATE                                          = 0x21000040UL,
      TAG_CREATION_TIME                                          = 0x21000050UL,
      TAG_ORIGINATOR                                             = 0x21000070UL,
      TAG_DESTINATION_AE                                         = 0x21000140UL,
      TAG_OWNER_ID                                               = 0x21000160UL,
      TAG_NUMBER_OF_FILMS                                        = 0x21000170UL,
      TAG_REFERENCED_PRINT_JOB_SEQUENCE_2100                     = 0x21000500UL,

      TAG_PRINTER_STATUS                                         = 0x21100010UL,
      TAG_PRINTER_STATUS_INFO                                    = 0x21100020UL,
      TAG_PRINTER_NAME                                           = 0x21100030UL,
      TAG_PRINT_QUEUE_ID                                         = 0x21100099UL,

      TAG_QUEUE_STATUS                                           = 0x21200010UL,
      TAG_PRINT_JOB_DESCRIPTION_SEQUENCE                         = 0x21200050UL,
      TAG_REFERENCED_PRINT_JOB_SEQUENCE_2120                     = 0x21200070UL,

      TAG_PRINT_MANAGEMENT_CAPABILITIES_SEQUENCE                 = 0x21300010UL,
      TAG_PRINTER_CHARACTERISTICS_SEQUENCE                       = 0x21300015UL,
      TAG_FILM_BOX_CONTENT_SEQUENCE                              = 0x21300030UL,
      TAG_IMAGE_BOX_CONTENT_SEQUENCE                             = 0x21300040UL,
      TAG_ANNOTATION_CONTENT_SEQUENCE                            = 0x21300050UL,
      TAG_IMAGE_OVERLAY_BOX_CONTENT_SEQUENCE                     = 0x21300060UL,
      TAG_PRESENTATION_LUT_CONTENT_SEQUENCE                      = 0x21300080UL,
      TAG_PROPOSED_STUDY_SEQUENCE                                = 0x213000A0UL,
      TAG_ORIGINAL_IMAGE_SEQUENCE                                = 0x213000C0UL,

      TAG_RT_IMAGE_LABEL                                         = 0x30020002UL,
      TAG_RT_IMAGE_NAME                                          = 0x30020003UL,
      TAG_RT_IMAGE_DESCRIPTION                                   = 0x30020004UL,
      TAG_REPORTED_VALUES_ORIGIN                                 = 0x3002000AUL,
      TAG_RT_IMAGE_PLANE                                         = 0x3002000CUL,
      TAG_X_RAY_IMAGE_RECEPTOR_ANGLE                             = 0x3002000EUL,
      TAG_RT_IMAGE_ORIENTATION                                   = 0x30020010UL,
      TAG_IMAGE_PLANE_PIXEL_SPACING                              = 0x30020011UL,
      TAG_RT_IMAGE_POSITION                                      = 0x30020012UL,
      TAG_RADIATION_MACHINE_NAME                                 = 0x30020020UL,
      TAG_RADIATION_MACHINE_SAD                                  = 0x30020022UL,
      TAG_RADIATION_MACHINE_SSD                                  = 0x30020024UL,
      TAG_RT_IMAGE_SID                                           = 0x30020026UL,
      TAG_SOURCE_TO_REFERENCE_OBJECT_DISTANCE                    = 0x30020028UL,
      TAG_FRACTION_NUMBER                                        = 0x30020029UL,
      TAG_EXPOSURE_SEQUENCE                                      = 0x30020030UL,
      TAG_METERSET_EXPOSURE                                      = 0x30020032UL,

      TAG_DVH_TYPE                                               = 0x30040001UL,
      TAG_DOSE_UNITS                                             = 0x30040002UL,
      TAG_DOSE_TYPE                                              = 0x30040004UL,
      TAG_DOSE_COMMENT                                           = 0x30040006UL,
      TAG_NORMALIZATION_POINT                                    = 0x30040008UL,
      TAG_DOSE_SUMMATION_TYPE                                    = 0x3004000AUL,
      TAG_GRID_FRAME_OFFSET_VECTOR                               = 0x3004000CUL,
      TAG_DOSE_GRID_SCALING                                      = 0x3004000EUL,
      TAG_RT_DOSE_ROI_SEQUENCE                                   = 0x30040010UL,
      TAG_DOSE_VALUE                                             = 0x30040012UL,
      TAG_DVH_NORMALIZATION_POINT                                = 0x30040040UL,
      TAG_DVH_NORMALIZATION_DOSE_VALUE                           = 0x30040042UL,
      TAG_DVH_SEQUENCE                                           = 0x30040050UL,
      TAG_DVH_DOSE_SCALING                                       = 0x30040052UL,
      TAG_DVH_VOLUME_UNITS                                       = 0x30040054UL,
      TAG_DVH_NUMBER_OF_BINS                                     = 0x30040056UL,
      TAG_DVH_DATA                                               = 0x30040058UL,
      TAG_DVH_REFERENCED_ROI_SEQUENCE                            = 0x30040060UL,
      TAG_DVH_ROI_CONTRIBUTION_TYPE                              = 0x30040062UL,
      TAG_DVH_MINIMUM_DOSE                                       = 0x30040070UL,
      TAG_DVH_MAXIMUM_DOSE                                       = 0x30040072UL,
      TAG_DVH_MEAN_DOSE                                          = 0x30040074UL,

      TAG_STRUCTURE_SET_LABEL                                    = 0x30060002UL,
      TAG_STRUCTURE_SET_NAME                                     = 0x30060004UL,
      TAG_STRUCTURE_SET_DESCRIPTION                              = 0x30060006UL,
      TAG_STRUCTURE_SET_DATE                                     = 0x30060008UL,
      TAG_STRUCTURE_SET_TIME                                     = 0x30060009UL,
      TAG_REFERENCED_FRAME_OF_REFERENCE_SEQUENCE                 = 0x30060010UL,
      TAG_RT_REFERENCED_STUDY_SEQUENCE                           = 0x30060012UL,
      TAG_RT_REFERENCED_SERIES_SEQUENCE                          = 0x30060014UL,
      TAG_CONTOUR_IMAGE_SEQUENCE                                 = 0x30060016UL,
      TAG_STRUCTURE_SET_ROI_SEQUENCE                             = 0x30060020UL,
      TAG_ROI_NUMBER                                             = 0x30060022UL,
      TAG_REFERENCED_FRAME_OF_REFERENCE_UID                      = 0x30060024UL,
      TAG_ROI_NAME                                               = 0x30060026UL,
      TAG_ROI_DESCRIPTION                                        = 0x30060028UL,
      TAG_ROI_DISPLAY_COLOR                                      = 0x3006002AUL,
      TAG_ROI_VOLUME                                             = 0x3006002CUL,
      TAG_RT_RELATED_ROI_SEQUENCE                                = 0x30060030UL,
      TAG_RT_ROI_RELATIONSHIP                                    = 0x30060033UL,
      TAG_ROI_GENERATION_ALGORITHM                               = 0x30060036UL,
      TAG_ROI_GENERATION_DESCRIPTION                             = 0x30060038UL,
      TAG_ROI_CONTOUR_SEQUENCE                                   = 0x30060039UL,
      TAG_CONTOUR_SEQUENCE                                       = 0x30060040UL,
      TAG_CONTOUR_GEOMETRIC_TYPE                                 = 0x30060042UL,
      TAG_CONTOUR_SLAB_THICKNESS                                 = 0x30060044UL,
      TAG_CONTOUR_OFFSET_VECTOR                                  = 0x30060045UL,
      TAG_NUMBER_OF_CONTOUR_POINTS                               = 0x30060046UL,
      TAG_CONTOUR_DATA                                           = 0x30060050UL,
      TAG_RT_ROI_OBSERVATIONS_SEQUENCE                           = 0x30060080UL,
      TAG_OBSERVATION_NUMBER                                     = 0x30060082UL,
      TAG_REFERENCED_ROI_NUMBER                                  = 0x30060084UL,
      TAG_ROI_OBSERVATION_LABEL                                  = 0x30060085UL,
      TAG_RT_ROI_IDENTIFICATION_CODE_SEQUENCE                    = 0x30060086UL,
      TAG_ROI_OBSERVATION_DESCRIPTION                            = 0x30060088UL,
      TAG_RELATED_RT_ROI_OBSERVATIONS_SEQUENCE                   = 0x300600A0UL,
      TAG_RT_ROI_INTERPRETED_TYPE                                = 0x300600A4UL,
      TAG_ROI_INTERPRETER                                        = 0x300600A6UL,
      TAG_ROI_PHYSICAL_PROPERTIES_SEQUENCE                       = 0x300600B0UL,
      TAG_ROI_PHYSICAL_PROPERTY                                  = 0x300600B2UL,
      TAG_ROI_PHYSICAL_PROPERTY_VALUE                            = 0x300600B4UL,
      TAG_FRAME_OF_REFERENCE_RELATIONSHIP_SEQUENCE               = 0x300600C0UL,
      TAG_RELATED_FRAME_OF_REFERENCE_UID                         = 0x300600C2UL,
      TAG_FRAME_OF_REFERENCE_TRANSFORMATION_TYPE                 = 0x300600C4UL,
      TAG_FRAME_OF_REFERENCE_TRANSFORMATION_MATRIX               = 0x300600C6UL,
      TAG_FRAME_OF_REFERENCE_TRANSFORMATION_COMMENT              = 0x300600C8UL,

      TAG_MEASURED_DOSE_REFERENCE_SEQUENCE                       = 0x30080010UL,
      TAG_MEASURED_DOSE_DESCRIPTION                              = 0x30080012UL,
      TAG_MEASURED_DOSE_TYPE                                     = 0x30080014UL,
      TAG_MEASURED_DOSE_VALUE                                    = 0x30080016UL,
      TAG_TREATMENT_SESSION_BEAM_SEQUENCE                        = 0x30080020UL,
      TAG_CURRENT_FRACTION_NUMBER                                = 0x30080022UL,
      TAG_TREATMENT_CONTROL_POINT_DATE                           = 0x30080024UL,
      TAG_TREATMENT_CONTROL_POINT_TIME                           = 0x30080025UL,
      TAG_TREATMENT_TERMINATION_STATUS                           = 0x3008002AUL,
      TAG_TREATMENT_TERMINATION_CODE                             = 0x3008002BUL,
      TAG_TREATMENT_VERIFICATION_STATUS                          = 0x3008002CUL,  
      TAG_REFERENCED_TREATMENT_RECORD_SEQUENCE                   = 0x30080030UL,
      TAG_SPECIFIED_PRIMARY_METERSET                             = 0x30080032UL,
      TAG_SPECIFIED_SECONDARY_METERSET                           = 0x30080033UL,
      TAG_DELIVERED_PRIMARY_METERSET                             = 0x30080036UL,
      TAG_DELIVERED_SECONDARY_METERSET                           = 0x30080037UL,
      TAG_SPECIFIED_TREATMENT_TIME                               = 0x3008003AUL,
      TAG_DELIVERED_TREATMENT_TIME                               = 0x3008003BUL,
      TAG_CONTROL_POINT_DELIVERY_SEQUENCE                        = 0x30080040UL,
      TAG_SPECIFIED_METERSET                                     = 0x30080042UL,
      TAG_DELIVERED_METERSET                                     = 0x30080044UL,
      TAG_DOSE_RATE_DELIVERED                                    = 0x30080048UL,
      TAG_TREATMENT_SUMMARY_CALCULATED_DOSE_REFERENCE_SEQUENCE   = 0x30080050UL,
      TAG_CUMULATIVE_DOSE_TO_DOSE_REFERENCE                      = 0x30080052UL,
      TAG_FIRST_TREATMENT_DATE                                   = 0x30080054UL,
      TAG_MOST_RECENT_TREATMENT_DATE                             = 0x30080056UL,
      TAG_NUMBER_OF_FRACTIONS_DELIVERED                          = 0x3008005AUL,
      TAG_OVERRIDE_SEQUENCE                                      = 0x30080060UL,
      TAG_OVERRIDE_PARAMETER_POINTER                             = 0x30080062UL,
      TAG_MEASURED_DOSE_REFERENCE_NUMBER                         = 0x30080064UL,
      TAG_OVERRIDE_REASON                                        = 0x30080066UL,
      TAG_CALCULATED_DOSE_REFERENCE_SEQUENCE                     = 0x30080070UL,
      TAG_CALCULATED_DOSE_REFERENCE_NUMBER                       = 0x30080072UL,
      TAG_CALCULATED_DOSE_REFERENCE_DESCRIPTION                  = 0x30080074UL,
      TAG_CALCULATED_DOSE_REFERENCE_DOSE_VALUE                   = 0x30080076UL,
      TAG_START_METERSET                                         = 0x30080078UL,
      TAG_END_METERSET                                           = 0x3008007AUL,
      TAG_REFERENCED_MEASURED_DOSE_REFERENCE_SEQUENCE            = 0x30080080UL,
      TAG_REFERENCED_MEASURED_DOSE_REFERENCE_NUMBER              = 0x30080082UL,
      TAG_REFERENCED_CALCULATED_DOSE_REFERENCE_SEQUENCE          = 0x30080090UL,
      TAG_REFERENCED_CALCULATED_DOSE_REFERENCE_NUMBER            = 0x30080092UL,
      TAG_BEAM_LIMITING_DEVICE_LEAF_PAIRS_SEQUENCE               = 0x300800A0UL,
      TAG_RECORDED_WEDGE_SEQUENCE                                = 0x300800B0UL,
      TAG_RECORDED_COMPENSATOR_SEQUENCE                          = 0x300800C0UL,
      TAG_RECORDED_BLOCK_SEQUENCE                                = 0x300800D0UL,
      TAG_TREATMENT_SUMMARY_MEASURED_DOSE_REFERENCE_SEQUENCE     = 0x300800E0UL,
      TAG_RECORDED_SOURCE_SEQUENCE                               = 0x30080100UL,
      TAG_SOURCE_SERIAL_NUMBER                                   = 0x30080105UL,
      TAG_TREATMENT_SESSION_APPLICATION_SETUP_SEQUENCE           = 0x30080110UL,
      TAG_APPLICATION_SETUP_CHECK                                = 0x30080116UL,
      TAG_RECORDED_BRACHY_ACCESSORY_DEVICE_SEQUENCE              = 0x30080120UL,
      TAG_REFERENCED_BRACHY_ACCESSORY_DEVICE_NUMBER              = 0x30080122UL,
      TAG_RECORDED_CHANNEL_SEQUENCE                              = 0x30080130UL,
      TAG_SPECIFIED_CHANNEL_TOTAL_TIME                           = 0x30080132UL,
      TAG_DELIVERED_CHANNEL_TOTAL_TIME                           = 0x30080134UL,
      TAG_SPECIFIED_NUMBER_OF_PULSES                             = 0x30080136UL,
      TAG_DELIVERED_NUMBER_OF_PULSES                             = 0x30080138UL,
      TAG_SPECIFIED_PULSE_REPETITION_INTERVAL                    = 0x3008013AUL,
      TAG_DELIVERED_PULSE_REPETITION_INTERVAL                    = 0x3008013CUL,
      TAG_RECORDED_SOURCE_APPLICATOR_SEQUENCE                    = 0x30080140UL,
      TAG_REFERENCED_SOURCE_APPLICATOR_NUMBER                    = 0x30080142UL,
      TAG_RECORDED_CHANNEL_SHIELD_SEQUENCE                       = 0x30080150UL,
      TAG_REFERENCED_CHANNEL_SHIELD_NUMBER                       = 0x30080152UL,
      TAG_BRACHY_CONTROL_POINT_DELIVERED_SEQUENCE                = 0x30080160UL,
      TAG_SAFE_POSITION_EXIT_DATE                                = 0x30080162UL,
      TAG_SAFE_POSITION_EXIT_TIME                                = 0x30080164UL,
      TAG_SAFE_POSITION_RETURN_DATE                              = 0x30080166UL,
      TAG_SAFE_POSITION_RETURN_TIME                              = 0x30080168UL,
      TAG_CURRENT_TREATMENT_STATUS                               = 0x30080200UL,
      TAG_TREATMENT_STATUS_COMMENT                               = 0x30080202UL,
      TAG_FRACTION_GROUP_SUMMARY_SEQUENCE                        = 0x30080220UL,
      TAG_REFERENCED_FRACTION_NUMBER                             = 0x30080223UL,
      TAG_FRACTION_GROUP_TYPE                                    = 0x30080224UL,
      TAG_BEAM_STOPPER_POSITION                                  = 0x30080230UL,
      TAG_FRACTION_STATUS_SUMMARY_SEQUENCE                       = 0x30080240UL,
      TAG_TREATMENT_DATE                                         = 0x30080250UL,
      TAG_TREATMENT_TIME                                         = 0x30080251UL,

      TAG_RT_PLAN_LABEL                                          = 0x300A0002UL,
      TAG_RT_PLAN_NAME                                           = 0x300A0003UL,
      TAG_RT_PLAN_DESCRIPTION                                    = 0x300A0004UL,
      TAG_RT_PLAN_DATE                                           = 0x300A0006UL,
      TAG_RT_PLAN_TIME                                           = 0x300A0007UL,
      TAG_TREATMENT_PROTOCOLS                                    = 0x300A0009UL,
      TAG_TREATMENT_INTENT                                       = 0x300A000AUL,
      TAG_TREATMENT_SITES                                        = 0x300A000BUL,
      TAG_RT_PLAN_GEOMETRY                                       = 0x300A000CUL,
      TAG_PRESCRIPTION_DESCRIPTION                               = 0x300A000EUL,
      TAG_DOSE_REFERENCE_SEQUENCE                                = 0x300A0010UL,
      TAG_DOSE_REFERENCE_NUMBER                                  = 0x300A0012UL,
      TAG_DOSE_REFERENCE_STRUCTURE_TYPE                          = 0x300A0014UL,
      TAG_NOMINAL_BEAM_ENERGY_UNIT                               = 0x300A0015UL,
      TAG_DOSE_REFERENCE_DESCRIPTION                             = 0x300A0016UL,
      TAG_DOSE_REFERENCE_POINT_COORDINATES                       = 0x300A0018UL,
      TAG_NOMINAL_PRIOR_DOSE                                     = 0x300A001AUL,
      TAG_DOSE_REFERENCE_TYPE                                    = 0x300A0020UL,
      TAG_CONSTRAINT_WEIGHT                                      = 0x300A0021UL,
      TAG_DELIVERY_WARNING_DOSE                                  = 0x300A0022UL,
      TAG_DELIVERY_MAXIMUM_DOSE                                  = 0x300A0023UL,
      TAG_TARGET_MINIMUM_DOSE                                    = 0x300A0025UL,
      TAG_TARGET_PRESCRIPTION_DOSE                               = 0x300A0026UL,
      TAG_TARGET_MAXIMUM_DOSE                                    = 0x300A0027UL,
      TAG_TARGET_UNDERDOSE_VOLUME_FRACTION                       = 0x300A0028UL,
      TAG_ORGAN_AT_RISK_FULL_VOLUME_DOSE                         = 0x300A002AUL,
      TAG_ORGAN_AT_RISK_LIMIT_DOSE                               = 0x300A002BUL,
      TAG_ORGAN_AT_RISK_MAXIMUM_DOSE                             = 0x300A002CUL,
      TAG_ORGAN_AT_RISK_OVERDOSE_VOLUME_FRACTION                 = 0x300A002DUL,
      TAG_TOLERANCE_TABLE_SEQUENCE                               = 0x300A0040UL,
      TAG_TOLERANCE_TABLE_NUMBER                                 = 0x300A0042UL,
      TAG_TOLERANCE_TABLE_LABEL                                  = 0x300A0043UL,
      TAG_GANTRY_ANGLE_TOLERANCE                                 = 0x300A0044UL,
      TAG_BEAM_LIMITING_DEVICE_ANGLE_TOLERANCE                   = 0x300A0046UL,
      TAG_BEAM_LIMITING_DEVICE_TOLERANCE_SEQUENCE                = 0x300A0048UL,
      TAG_BEAM_LIMITING_DEVICE_POSITION_TOLERANCE                = 0x300A004AUL,
      TAG_PATIENT_SUPPORT_ANGLE_TOLERANCE                        = 0x300A004CUL,
      TAG_TABLE_TOP_ECCENTRIC_ANGLE_TOLERANCE                    = 0x300A004EUL,
      TAG_TABLE_TOP_VERTICAL_POSITION_TOLERANCE                  = 0x300A0051UL,
      TAG_TABLE_TOP_LONGITUDINAL_POSITION_TOLERANCE              = 0x300A0052UL,
      TAG_TABLE_TOP_LATERAL_POSITION_TOLERANCE                   = 0x300A0053UL,
      TAG_RT_PLAN_RELATIONSHIP                                   = 0x300A0055UL,
      TAG_FRACTION_GROUP_SEQUENCE                                = 0x300A0070UL,
      TAG_FRACTION_GROUP_NUMBER                                  = 0x300A0071UL,
      TAG_NUMBER_OF_FRACTIONS_PLANNED                            = 0x300A0078UL,
      TAG_NUMBER_OF_FRACTIONS_PER_DAY                            = 0x300A0079UL,
      TAG_REPEAT_FRACTION_CYCLE_LENGTH                           = 0x300A007AUL,
      TAG_FRACTION_PATTERN                                       = 0x300A007BUL,
      TAG_NUMBER_OF_BEAMS                                        = 0x300A0080UL,
      TAG_BEAM_DOSE_SPECIFICATION_POINT                          = 0x300A0082UL,
      TAG_BEAM_DOSE                                              = 0x300A0084UL,
      TAG_BEAM_METERSET                                          = 0x300A0086UL,
      TAG_NUMBER_OF_BRACHY_APPLICATION_SETUPS                    = 0x300A00A0UL,
      TAG_BRACHY_APPLICATION_SETUP_DOSE_SPECIFICATION_POINT      = 0x300A00A2UL,
      TAG_BRACHY_APPLICATION_SETUP_DOSE                          = 0x300A00A4UL,
      TAG_BEAM_SEQUENCE                                          = 0x300A00B0UL,
      TAG_TREATMENT_MACHINE_NAME                                 = 0x300A00B2UL,
      TAG_PRIMARY_DOSIMETER_UNIT                                 = 0x300A00B3UL,
      TAG_SOURCE_AXIS_DISTANCE                                   = 0x300A00B4UL,
      TAG_BEAM_LIMITING_DEVICE_SEQUENCE                          = 0x300A00B6UL,
      TAG_RT_BEAM_LIMITING_DEVICE_TYPE                           = 0x300A00B8UL,
      TAG_SOURCE_TO_BEAM_LIMITING_DEVICE_DISTANCE                = 0x300A00BAUL,
      TAG_NUMBER_OF_LEAF_JAW_PAIRS                               = 0x300A00BCUL,
      TAG_LEAF_POSITION_BOUNDARIES                               = 0x300A00BEUL,
      TAG_BEAM_NUMBER                                            = 0x300A00C0UL,
      TAG_BEAM_NAME                                              = 0x300A00C2UL,
      TAG_BEAM_DESCRIPTION                                       = 0x300A00C3UL,
      TAG_BEAM_TYPE                                              = 0x300A00C4UL,
      TAG_RADIATION_TYPE                                         = 0x300A00C6UL,
      TAG_REFERENCE_IMAGE_NUMBER                                 = 0x300A00C8UL,
      TAG_PLANNED_VERIFICATION_IMAGE_SEQUENCE                    = 0x300A00CAUL,
      TAG_IMAGING_DEVICE_SPECIFIC_ACQUISITION_PARAMETERS         = 0x300A00CCUL,
      TAG_TREATMENT_DELIVERY_TYPE                                = 0x300A00CEUL,
      TAG_NUMBER_OF_WEDGES                                       = 0x300A00D0UL,
      TAG_WEDGE_SEQUENCE                                         = 0x300A00D1UL,
      TAG_WEDGE_NUMBER                                           = 0x300A00D2UL,
      TAG_WEDGE_TYPE                                             = 0x300A00D3UL,
      TAG_WEDGE_ID                                               = 0x300A00D4UL,
      TAG_WEDGE_ANGLE                                            = 0x300A00D5UL,
      TAG_WEDGE_FACTOR                                           = 0x300A00D6UL,
      TAG_WEDGE_ORIENTATION                                      = 0x300A00D8UL,
      TAG_SOURCE_TO_WEDGE_TRAY_DISTANCE                          = 0x300A00DAUL,
      TAG_NUMBER_OF_COMPENSATORS                                 = 0x300A00E0UL,
      TAG_MATERIAL_ID                                            = 0x300A00E1UL,
      TAG_TOTAL_COMPENSATOR_TRAY_FACTOR                          = 0x300A00E2UL,
      TAG_COMPENSATOR_SEQUENCE                                   = 0x300A00E3UL,
      TAG_COMPENSATOR_NUMBER                                     = 0x300A00E4UL,
      TAG_COMPENSATOR_ID                                         = 0x300A00E5UL,
      TAG_SOURCE_TO_COMPENSATOR_TRAY_DISTANCE                    = 0x300A00E6UL,
      TAG_COMPENSATOR_ROWS                                       = 0x300A00E7UL,
      TAG_COMPENSATOR_COLUMNS                                    = 0x300A00E8UL,
      TAG_COMPENSATOR_PIXEL_SPACING                              = 0x300A00E9UL,
      TAG_COMPENSATOR_POSITION                                   = 0x300A00EAUL,
      TAG_COMPENSATOR_TRANSMISSION_DATA                          = 0x300A00EBUL,
      TAG_COMPENSATOR_THICKNESS_DATA                             = 0x300A00ECUL,
      TAG_NUMBER_OF_BOLI                                         = 0x300A00EDUL,
      TAG_COMPENSATOR_TYPE                                       = 0x300A00EEUL,
      TAG_NUMBER_OF_BLOCKS                                       = 0x300A00F0UL,
      TAG_TOTAL_BLOCK_TRAY_FACTOR                                = 0x300A00F2UL,
      TAG_BLOCK_SEQUENCE                                         = 0x300A00F4UL,
      TAG_BLOCK_TRAY_ID                                          = 0x300A00F5UL,
      TAG_SOURCE_TO_BLOCK_TRAY_DISTANCE                          = 0x300A00F6UL,
      TAG_BLOCK_TYPE                                             = 0x300A00F8UL,
      TAG_BLOCK_DIVERGENCE                                       = 0x300A00FAUL,
      TAG_BLOCK_NUMBER                                           = 0x300A00FCUL,
      TAG_BLOCK_NAME                                             = 0x300A00FEUL,
      TAG_BLOCK_THICKNESS                                        = 0x300A0100UL,
      TAG_BLOCK_TRANSMISSION                                     = 0x300A0102UL,
      TAG_BLOCK_NUMBER_OF_POINTS                                 = 0x300A0104UL,
      TAG_BLOCK_DATA                                             = 0x300A0106UL,
      TAG_APPLICATOR_SEQUENCE                                    = 0x300A0107UL,
      TAG_APPLICATOR_ID                                          = 0x300A0108UL,
      TAG_APPLICATOR_TYPE                                        = 0x300A0109UL,
      TAG_APPLICATOR_DESCRIPTION                                 = 0x300A010AUL,
      TAG_CUMULATIVE_DOSE_REFERENCE_COEFFICIENT                  = 0x300A010CUL,
      TAG_FINAL_CUMULATIVE_METERSET_WEIGHT                       = 0x300A010EUL,
      TAG_NUMBER_OF_CONTROL_POINTS                               = 0x300A0110UL,
      TAG_CONTROL_POINT_SEQUENCE                                 = 0x300A0111UL,
      TAG_CONTROL_POINT_INDEX                                    = 0x300A0112UL,
      TAG_NOMINAL_BEAM_ENERGY                                    = 0x300A0114UL,
      TAG_DOSE_RATE_SET                                          = 0x300A0115UL,
      TAG_WEDGE_POSITION_SEQUENCE                                = 0x300A0116UL,
      TAG_WEDGE_POSITION                                         = 0x300A0118UL,
      TAG_BEAM_LIMITING_DEVICE_POSITION_SEQUENCE                 = 0x300A011AUL,
      TAG_LEAF_JAW_POSITIONS                                     = 0x300A011CUL,
      TAG_GANTRY_ANGLE                                           = 0x300A011EUL,
      TAG_GANTRY_ROTATION_DIRECTION                              = 0x300A011FUL,
      TAG_BEAM_LIMITING_DEVICE_ANGLE                             = 0x300A0120UL,
      TAG_BEAM_LIMITING_DEVICE_ROTATION_DIRECTION                = 0x300A0121UL,
      TAG_PATIENT_SUPPORT_ANGLE                                  = 0x300A0122UL,
      TAG_PATIENT_SUPPORT_ROTATION_DIRECTION                     = 0x300A0123UL,
      TAG_TABLE_TOP_ECCENTRIC_AXIS_DISTANCE                      = 0x300A0124UL,
      TAG_TABLE_TOP_ECCENTRIC_ANGLE                              = 0x300A0125UL,
      TAG_TABLE_TOP_ECCENTRIC_ROTATION_DIRECTION                 = 0x300A0126UL,
      TAG_TABLE_TOP_VERTICAL_POSITION                            = 0x300A0128UL,
      TAG_TABLE_TOP_LONGITUDINAL_POSITION                        = 0x300A0129UL,
      TAG_TABLE_TOP_LATERAL_POSITION                             = 0x300A012AUL,
      TAG_ISOCENTER_POSITION                                     = 0x300A012CUL,
      TAG_SURFACE_ENTRY_POINT                                    = 0x300A012EUL,
      TAG_SOURCE_TO_SURFACE_DISTANCE                             = 0x300A0130UL,
      TAG_CUMULATIVE_METERSET_WEIGHT                             = 0x300A0134UL,
      TAG_PATIENT_SETUP_SEQUENCE                                 = 0x300A0180UL,
      TAG_PATIENT_SETUP_NUMBER                                   = 0x300A0182UL,
      TAG_PATIENT_ADDITIONAL_POSITION                            = 0x300A0184UL,
      TAG_FIXATION_DEVICE_SEQUENCE                               = 0x300A0190UL,
      TAG_FIXATION_DEVICE_TYPE                                   = 0x300A0192UL,
      TAG_FIXATION_DEVICE_LABEL                                  = 0x300A0194UL,
      TAG_FIXATION_DEVICE_DESCRIPTION                            = 0x300A0196UL,
      TAG_FIXATION_DEVICE_POSITION                               = 0x300A0198UL,
      TAG_SHIELDING_DEVICE_SEQUENCE                              = 0x300A01A0UL,
      TAG_SHIELDING_DEVICE_TYPE                                  = 0x300A01A2UL,
      TAG_SHIELDING_DEVICE_LABEL                                 = 0x300A01A4UL,
      TAG_SHIELDING_DEVICE_DESCRIPTION                           = 0x300A01A6UL,
      TAG_SHIELDING_DEVICE_POSITION                              = 0x300A01A8UL,
      TAG_SETUP_TECHNIQUE                                        = 0x300A01B0UL,
      TAG_SETUP_TECHNIQUE_DESCRIPTION                            = 0x300A01B2UL,
      TAG_SETUP_DEVICE_SEQUENCE                                  = 0x300A01B4UL,
      TAG_SETUP_DEVICE_TYPE                                      = 0x300A01B6UL,
      TAG_SETUP_DEVICE_LABEL                                     = 0x300A01B8UL,
      TAG_SETUP_DEVICE_DESCRIPTION                               = 0x300A01BAUL,
      TAG_SETUP_DEVICE_PARAMETER                                 = 0x300A01BCUL,
      TAG_SETUP_REFERENCE_DESCRIPTION                            = 0x300A01D0UL,
      TAG_TABLE_TOP_VERTICAL_SETUP_DISPLACEMENT                  = 0x300A01D2UL,
      TAG_TABLE_TOP_LONGITUDINAL_SETUP_DISPLACEMENT              = 0x300A01D4UL,
      TAG_TABLE_TOP_LATERAL_SETUP_DISPLACEMENT                   = 0x300A01D6UL,
      TAG_BRACHY_TREATMENT_TECHNIQUE                             = 0x300A0200UL,
      TAG_BRACHY_TREATMENT_TYPE                                  = 0x300A0202UL,
      TAG_TREATMENT_MACHINE_SEQUENCE                             = 0x300A0206UL,
      TAG_SOURCE_SEQUENCE                                        = 0x300A0210UL,
      TAG_SOURCE_NUMBER                                          = 0x300A0212UL,
      TAG_SOURCE_TYPE                                            = 0x300A0214UL,
      TAG_SOURCE_MANUFACTURER                                    = 0x300A0216UL,
      TAG_ACTIVE_SOURCE_DIAMETER                                 = 0x300A0218UL,
      TAG_ACTIVE_SOURCE_LENGTH                                   = 0x300A021AUL,
      TAG_SOURCE_ENCAPSULATION_NOMINAL_THICKNESS                 = 0x300A0222UL,
      TAG_SOURCE_ENCAPSULATION_NOMINAL_TRANSMISSION              = 0x300A0224UL,
      TAG_SOURCE_ISOTOPE_NAME                                    = 0x300A0226UL,
      TAG_SOURCE_ISOTOPE_HALF_LIFE                               = 0x300A0228UL,
      TAG_REFERENCE_AIR_KERMA_RATE                               = 0x300A022AUL,
      TAG_AIR_KERMA_RATE_REFERENCE_DATE                          = 0x300A022CUL,
      TAG_AIR_KERMA_RATE_REFERENCE_TIME                          = 0x300A022EUL,
      TAG_APPLICATION_SETUP_SEQUENCE                             = 0x300A0230UL,
      TAG_APPLICATION_SETUP_TYPE                                 = 0x300A0232UL,
      TAG_APPLICATION_SETUP_NUMBER                               = 0x300A0234UL,
      TAG_APPLICATION_SETUP_NAME                                 = 0x300A0236UL,
      TAG_APPLICATION_SETUP_MANUFACTURER                         = 0x300A0238UL,
      TAG_TEMPLATE_NUMBER                                        = 0x300A0240UL,
      TAG_TEMPLATE_TYPE                                          = 0x300A0242UL,
      TAG_TEMPLATE_NAME                                          = 0x300A0244UL,
      TAG_TOTAL_REFERENCE_AIR_KERMA                              = 0x300A0250UL,
      TAG_BRACHY_ACCESSORY_DEVICE_SEQUENCE                       = 0x300A0260UL,
      TAG_BRACHY_ACCESSORY_DEVICE_NUMBER                         = 0x300A0262UL,
      TAG_BRACHY_ACCESSORY_DEVICE_ID                             = 0x300A0263UL,
      TAG_BRACHY_ACCESSORY_DEVICE_TYPE                           = 0x300A0264UL,
      TAG_BRACHY_ACCESSORY_DEVICE_NAME                           = 0x300A0266UL,
      TAG_BRACHY_ACCESSORY_DEVICE_NOMINAL_THICKNESS              = 0x300A026AUL,
      TAG_BRACHY_ACCESSORY_DEVICE_NOMINAL_TRANSMISSION           = 0x300A026CUL,
      TAG_CHANNEL_SEQUENCE                                       = 0x300A0280UL,
      TAG_CHANNEL_NUMBER                                         = 0x300A0282UL,
      TAG_CHANNEL_LENGTH                                         = 0x300A0284UL,
      TAG_CHANNEL_TOTAL_TIME                                     = 0x300A0286UL,
      TAG_SOURCE_MOVEMENT_TYPE                                   = 0x300A0288UL,
      TAG_NUMBER_OF_PULSES                                       = 0x300A028AUL,
      TAG_PULSE_REPETITION_INTERVAL                              = 0x300A028CUL,
      TAG_SOURCE_APPLICATOR_NUMBER                               = 0x300A0290UL,
      TAG_SOURCE_APPLICATOR_ID                                   = 0x300A0291UL,
      TAG_SOURCE_APPLICATOR_TYPE                                 = 0x300A0292UL,
      TAG_SOURCE_APPLICATOR_NAME                                 = 0x300A0294UL,
      TAG_SOURCE_APPLICATOR_LENGTH                               = 0x300A0296UL,
      TAG_SOURCE_APPLICATOR_MANUFACTURER                         = 0x300A0298UL,
      TAG_SOURCE_APPLICATOR_WALL_NOMINAL_THICKNESS               = 0x300A029CUL,
      TAG_SOURCE_APPLICATOR_WALL_NOMINAL_TRANSMISSION            = 0x300A029EUL,
      TAG_SOURCE_APPLICATOR_STEP_SIZE                            = 0x300A02A0UL,
      TAG_TRANSFER_TUBE_NUMBER                                   = 0x300A02A2UL,
      TAG_TRANSFER_TUBE_LENGTH                                   = 0x300A02A4UL,
      TAG_CHANNEL_SHIELD_SEQUENCE                                = 0x300A02B0UL,
      TAG_CHANNEL_SHIELD_NUMBER                                  = 0x300A02B2UL,
      TAG_CHANNEL_SHIELD_ID                                      = 0x300A02B3UL,
      TAG_CHANNEL_SHIELD_NAME                                    = 0x300A02B4UL,
      TAG_CHANNEL_SHIELD_NOMINAL_THICKNESS                       = 0x300A02B8UL,
      TAG_CHANNEL_SHIELD_NOMINAL_TRANSMISSION                    = 0x300A02BAUL,
      TAG_FINAL_CUMULATIVE_TIME_WEIGHT                           = 0x300A02C8UL,
      TAG_BRACHY_CONTROL_POINT_SEQUENCE                          = 0x300A02D0UL,
      TAG_CONTROL_POINT_RELATIVE_POSITION                        = 0x300A02D2UL,
      TAG_CONTROL_POINT_3D_POSITION                              = 0x300A02D4UL,
      TAG_CUMULATIVE_TIME_WEIGHT                                 = 0x300A02D6UL,

      TAG_REFERENCED_RT_PLAN_SEQUENCE                            = 0x300C0002UL,
      TAG_REFERENCED_BEAM_SEQUENCE                               = 0x300C0004UL,
      TAG_REFERENCED_BEAM_NUMBER                                 = 0x300C0006UL,
      TAG_REFERENCED_REFERENCE_IMAGE_NUMBER                      = 0x300C0007UL,
      TAG_START_CUMULATIVE_METERSET_WEIGHT                       = 0x300C0008UL,
      TAG_END_CUMULATIVE_METERSET_WEIGHT                         = 0x300C0009UL,
      TAG_REFERENCED_BRACHY_APPLICATION_SETUP_SEQUENCE           = 0x300C000AUL,
      TAG_REFERENCED_BRACHY_APPLICATION_SETUP_NUMBER             = 0x300C000CUL,
      TAG_REFERENCED_SOURCE_NUMBER                               = 0x300C000EUL,
      TAG_REFERENCED_FRACTION_GROUP_SEQUENCE                     = 0x300C0020UL,
      TAG_REFERENCED_FRACTION_GROUP_NUMBER                       = 0x300C0022UL,
      TAG_REFERENCED_VERIFICATION_IMAGE_SEQUENCE                 = 0x300C0040UL,
      TAG_REFERENCED_REFERENCE_IMAGE_SEQUENCE                    = 0x300C0042UL,
      TAG_REFERENCED_DOSE_REFERENCE_SEQUENCE                     = 0x300C0050UL,
      TAG_REFERENCED_DOSE_REFERENCE_NUMBER                       = 0x300C0051UL,
      TAG_BRACHY_REFERENCED_DOSE_REFERENCE_SEQUENCE              = 0x300C0055UL,
      TAG_REFERENCED_STRUCTURE_SET_SEQUENCE                      = 0x300C0060UL,
      TAG_REFERENCED_PATIENT_SETUP_NUMBER                        = 0x300C006AUL,
      TAG_REFERENCED_DOSE_SEQUENCE                               = 0x300C0080UL,
      TAG_REFERENCED_TOLERANCE_TABLE_NUMBER                      = 0x300C00A0UL,
      TAG_REFERENCED_BOLUS_SEQUENCE                              = 0x300C00B0UL,
      TAG_REFERENCED_WEDGE_NUMBER                                = 0x300C00C0UL,
      TAG_REFERENCED_COMPENSATOR_NUMBER                          = 0x300C00D0UL,
      TAG_REFERENCED_BLOCK_NUMBER                                = 0x300C00E0UL,
      TAG_REFERENCED_CONTROL_POINT_INDEX                         = 0x300C00F0UL,

      TAG_APPROVAL_STATUS                                        = 0x300E0002UL,
      TAG_REVIEW_DATE                                            = 0x300E0004UL,
      TAG_REVIEW_TIME                                            = 0x300E0005UL,
      TAG_REVIEWER_NAME                                          = 0x300E0008UL,

      TAG_RESULTS_ID                                             = 0x40080040UL,
      TAG_RESULTS_ID_ISSUER                                      = 0x40080042UL,
      TAG_REFERENCED_INTERPRETATION_SEQUENCE                     = 0x40080050UL,
      TAG_INTERPRETATION_RECORDED_DATE                           = 0x40080100UL,
      TAG_INTERPRETATION_RECORDED_TIME                           = 0x40080101UL,
      TAG_INTERPRETATION_RECORDER                                = 0x40080102UL,
      TAG_REFERENCE_TO_RECORDED_SOUND                            = 0x40080103UL,
      TAG_INTERPRETATION_TRANSCRIPTION_DATE                      = 0x40080108UL,
      TAG_INTERPRETATION_TRANSCRIPTION_TIME                      = 0x40080109UL,
      TAG_INTERPRETATION_TRANSCRIBER                             = 0x4008010AUL,
      TAG_INTERPRETATION_TEXT                                    = 0x4008010BUL,
      TAG_INTERPRETATION_AUTHOR                                  = 0x4008010CUL,
      TAG_INTERPRETATION_APPROVER_SEQUENCE                       = 0x40080111UL,
      TAG_INTERPRETATION_APPROVAL_DATE                           = 0x40080112UL,
      TAG_INTERPRETATION_APPROVAL_TIME                           = 0x40080113UL,
      TAG_PHYSICIAN_APPROVING_INTERPRETATION                     = 0x40080114UL,
      TAG_INTERPRETATION_DIAGNOSIS_DESCRIPTION                   = 0x40080115UL,
      TAG_INTERPRETATION_DIAGNOSIS_CODE_SEQUENCE                 = 0x40080117UL,
      TAG_RESULTS_DISTRIBUTION_LIST_SEQUENCE                     = 0x40080118UL,
      TAG_DISTRIBUTION_NAME                                      = 0x40080119UL,
      TAG_DISTRIBUTION_ADDRESS                                   = 0x4008011AUL,
      TAG_INTERPRETATION_ID                                      = 0x40080200UL,
      TAG_INTERPRETATION_ID_ISSUER                               = 0x40080202UL,
      TAG_INTERPRETATION_TYPE_ID                                 = 0x40080210UL,
      TAG_INTERPRETATION_STATUS_ID                               = 0x40080212UL,
      TAG_IMPRESSIONS                                            = 0x40080300UL,
      TAG_RESULTS_COMMENTS                                       = 0x40084000UL,

      TAG_CURVE_DIMENSIONS                                       = 0x50000005UL,
      TAG_NUMBER_OF_POINTS                                       = 0x50000010UL,
      TAG_TYPE_OF_DATA                                           = 0x50000020UL,
      TAG_CURVE_DESCRIPTION                                      = 0x50000022UL,
      TAG_AXIS_UNITS                                             = 0x50000030UL,
      TAG_AXIS_LABELS                                            = 0x50000040UL,
      TAG_DATA_VALUE_REPRESENTATION                              = 0x50000103UL,
      TAG_MINIMUM_COORDINATE_VALUE                               = 0x50000104UL,
      TAG_MAXIMUM_COORDINATE_VALUE                               = 0x50000105UL,
      TAG_CURVE_RANGE                                            = 0x50000106UL,
      TAG_CURVE_DATA_DESCRIPTOR                                  = 0x50000110UL,
      TAG_COORDINATE_START_VALUE                                 = 0x50000112UL,
      TAG_COORDINATE_STEP_VALUE                                  = 0x50000114UL,
      TAG_AUDIO_TYPE                                             = 0x50002000UL,
      TAG_AUDIO_SAMPLE_FORMAT                                    = 0x50002002UL,
      TAG_NUMBER_OF_CHANNELS                                     = 0x50002004UL,
      TAG_NUMBER_OF_SAMPLES                                      = 0x50002006UL,
      TAG_SAMPLE_RATE                                            = 0x50002008UL,
      TAG_TOTAL_TIME                                             = 0x5000200AUL,
      TAG_AUDIO_SAMPLE_DATA                                      = 0x5000200CUL,
      TAG_AUDIO_COMMENTS                                         = 0x5000200EUL,
      TAG_CURVE_LABEL                                            = 0x50002500UL,
      TAG_REFERENCED_OVERLAY_SEQUENCE_50XX                       = 0x50002600UL,
      TAG_REFERENCED_OVERLAY_GROUP                               = 0x50002610UL,
      TAG_CURVE_DATA                                             = 0x50003000UL,

      TAG_OVERLAY_ROWS                                           = 0x60000010UL,
      TAG_OVERLAY_COLUMNS                                        = 0x60000011UL,
      TAG_OVERLAY_PLANES                                         = 0x60000012UL,
      TAG_NUMBER_OF_FRAMES_IN_OVERLAY                            = 0x60000015UL,
      TAG_OVERLAY_DESCRIPTION                                    = 0x60000022UL,
      TAG_OVERLAY_TYPE                                           = 0x60000040UL,
      TAG_OVERLAY_SUBTYPE                                        = 0x60000045UL,
      TAG_OVERLAY_ORIGIN                                         = 0x60000050UL,
      TAG_IMAGE_FRAME_ORIGIN                                     = 0x60000051UL,
      TAG_OVERLAY_PLANE_ORIGIN                                   = 0x60000052UL,
      TAG_OVERLAY_BITS_ALLOCATED                                 = 0x60000100UL,
      TAG_OVERLAY_BIT_POSITION                                   = 0x60000102UL,
      TAG_OVERLAY_DESCRIPTOR_GRAY_RETIRED                        = 0x60001100UL,
      TAG_OVERLAY_DESCRIPTOR_RED_RETIRED                         = 0x60001101UL,
      TAG_OVERLAY_DESCRIPTOR_GREEN_RETIRED                       = 0x60001102UL,
      TAG_OVERLAY_DESCRIPTOR_BLUE_RETIRED                        = 0x60001103UL,
      TAG_OVERLAYS_GRAY_RETIRED                                  = 0x60001200UL,
      TAG_OVERLAYS_RED_RETIRED                                   = 0x60001201UL,
      TAG_OVERLAYS_GREEN_RETIRED                                 = 0x60001202UL,
      TAG_OVERLAYS_BLUE_RETIRED                                  = 0x60001203UL,
      TAG_ROI_AREA                                               = 0x60001301UL,
      TAG_ROI_MEAN                                               = 0x60001302UL,
      TAG_ROI_STANDARD_DEVIATION                                 = 0x60001303UL,
      TAG_OVERLAY_LABEL                                          = 0x60001500UL,
      TAG_OVERLAY_DATA                                           = 0x60003000UL,

      TAG_PIXEL_DATA                                             = 0x7FE00010UL,
      TAG_LEAD_BITMAP                                            = 0x7FE00010UL,

      TAG_DATA_SET_TRAILING_PADDING                              = 0xFFFCFFFCUL,

      TAG_ITEM                                                   = 0xFFFEE000UL,
      TAG_ITEM_DELIMITATION_ITEM                                 = 0xFFFEE00DUL,
      TAG_SEQUENCE_DELIMITATION_ITEM                             = 0xFFFEE0DDUL,
   } DicomDataSetTagConstants;

   typedef enum
   {
      TAG_COMMAND_LENGTH_TO_END                                  = 0x00000001UL,
      TAG_AFFECTED_SOP_CLASS_UID                                 = 0x00000002UL,
      TAG_REQUESTED_SOP_CLASS_UID                                = 0x00000003UL,
      TAG_COMMAND_RECOGNITION_CODE                               = 0x00000010UL,
      TAG_COMMAND_FIELD                                          = 0x00000100UL,
      TAG_MESSAGE_ID                                             = 0x00000110UL,
      TAG_MESSAGE_ID_BEING_RESPONDED_TO                          = 0x00000120UL,
      TAG_INITIATOR                                              = 0x00000200UL,
      TAG_RECEIVER                                               = 0x00000300UL,
      TAG_FIND_LOCATION                                          = 0x00000400UL,
      TAG_MOVE_DESTINATION                                       = 0x00000600UL,
      TAG_PRIORITY                                               = 0x00000700UL,
      TAG_DATA_SET_TYPE                                          = 0x00000800UL,
      TAG_NUMBER_OF_MATCHES                                      = 0x00000850UL,
      TAG_RESPONSE_SEQUENCE_NUMBER                               = 0x00000860UL,
      TAG_STATUS                                                 = 0x00000900UL,
      TAG_OFFENDING_ELEMENT                                      = 0x00000901UL,
      TAG_ERROR_COMMENT                                          = 0x00000902UL,
      TAG_ERROR_ID                                               = 0x00000903UL,
      TAG_AFFECTED_SOP_INSTANCE_UID                              = 0x00001000UL,
      TAG_REQUESTED_SOP_INSTANCE_UID                             = 0x00001001UL,
      TAG_EVENT_TYPE_ID                                          = 0x00001002UL,
      TAG_ATTRIBUTE_IDENTIFIER_LIST                              = 0x00001005UL,
      TAG_ACTION_TYPE_ID                                         = 0x00001008UL,
      TAG_NUMBER_OF_REMAINING_SUBOPERATIONS                      = 0x00001020UL,
      TAG_NUMBER_OF_COMPLETED_SUBOPERATIONS                      = 0x00001021UL,
      TAG_NUMBER_OF_FAILED_SUBOPERATIONS                         = 0x00001022UL,
      TAG_NUMBER_OF_WARNING_SUBOPERATIONS                        = 0x00001023UL,
      TAG_MOVE_ORIGINATOR_APPLICATION_ENTITY_TITLE               = 0x00001030UL,
      TAG_MOVE_ORIGINATOR_MESSAGE_ID                             = 0x00001031UL,
      TAG_DIALOG_RECEIVER                                        = 0x00004000UL,
      TAG_TERMINAL_TYPE                                          = 0x00004010UL,
      TAG_MESSAGE_SET_ID                                         = 0x00005010UL,
      TAG_END_MESSAGE_SET                                        = 0x00005020UL,
      TAG_DISPLAY_FORMAT                                         = 0x00005110UL,
      TAG_PAGE_POSITION_ID                                       = 0x00005120UL,
      TAG_TEXT_FORMAT_ID                                         = 0x00005130UL,
      TAG_NORMAL_REVERSE                                         = 0x00005140UL,
      TAG_ADD_GRAY_SCALE                                         = 0x00005150UL,
      TAG_BORDERS                                                = 0x00005160UL,
      TAG_COPIES                                                 = 0x00005170UL,
      TAG_OLD_MAGNIFICATION_TYPE                                 = 0x00005180UL,
      TAG_ERASE                                                  = 0x00005190UL,
      TAG_PRINT                                                  = 0x000051A0UL,
      TAG_OVERLAYS                                               = 0x000051B0UL,
   } DicomCommandSetTagConstants;


// L_SUPPORT_XXX constants
#include "ltlck_.h"

   typedef enum
   {
      DICOM_IOD_TYPE_CLASS=0,             // Class type
      DICOM_IOD_TYPE_MODULE,              // Module type
      DICOM_IOD_TYPE_ELEMENT,             // Element type
      DICOM_IOD_TYPE_MAX,
   } DicomIODTypeConstants;

   typedef enum
   {
      DICOM_IOD_USAGE_M,                  // Mandatory IOD   - M - (U - Unique for key)
      DICOM_IOD_USAGE_C,                  // Conditional IOD - C - (R - Required for key)
      DICOM_IOD_USAGE_U,                  // Optional IOD    - U - (O - Optional for key)
      DICOM_IOD_USAGE_1,                  // Mandatory IOD   - 1  (type 1)
      DICOM_IOD_USAGE_1C,                 // Conditional IOD - 1C (type 1)
      DICOM_IOD_USAGE_2,                  // Mandatory IOD   - 2  (type 2)
      DICOM_IOD_USAGE_2C,                 // Conditional IOD - 2C (type 2)
      DICOM_IOD_USAGE_3,                  // Optional IOD    - 3  (type 3)
      DICOM_IOD_USAGE_MAX,
   } DicomIODUsageConstants;

   typedef enum
   {
      DS_PREAMBLE_LENGTH          =   128,
      DS_PREFIX_LENGTH            =   4,

      ELEMENT_LENGTH_MAX          =   0xFFFFFFFFUL,
      ELEMENT_INDEX_MAX           =   0xFFFFFFFFUL,
   } DicomMiscConstants;

      typedef enum
   {
      ORDER_RGB               =  0, /* RGB ordering */
      ORDER_BGR               =  1, /* BRG ordering */
      ORDER_GRAY              =  2, /* Gray pixels */
      ORDER_RGBORGRAY         =  3, /* Valid only for L_LoadXXX functions - gray or RGB */
      ORDER_BGRORGRAY         =  4, /* Valid only for L_LoadXXX functions - gray or BGR */
   } DicomColorOrderConstants;

   typedef enum
   {
      DICOM_IMAGE_COMPRESSION_NONE=0,
      DICOM_IMAGE_COMPRESSION_RLE,
      DICOM_IMAGE_COMPRESSION_JPEG_LOSSLESS,
      DICOM_IMAGE_COMPRESSION_JPEG_LOSSY,
      DICOM_IMAGE_COMPRESSION_JPEG_LS_LOSSLESS,
      DICOM_IMAGE_COMPRESSION_JPEG_LS_LOSSY,
      DICOM_IMAGE_COMPRESSION_J2K_LOSSLESS,
      DICOM_IMAGE_COMPRESSION_J2K_LOSSY
   } DicomImageCompressionConstants;

   typedef enum
   {
      DICOM_IMAGE_PHOTOMETRIC_MONOCHROME1=0,
      DICOM_IMAGE_PHOTOMETRIC_MONOCHROME2,
      DICOM_IMAGE_PHOTOMETRIC_PALETTE_COLOR,
      DICOM_IMAGE_PHOTOMETRIC_RGB,
      DICOM_IMAGE_PHOTOMETRIC_ARGB,
      DICOM_IMAGE_PHOTOMETRIC_CMYK,
      DICOM_IMAGE_PHOTOMETRIC_YBR_FULL_422,
      DICOM_IMAGE_PHOTOMETRIC_YBR_FULL,
   } DicomImagePhotometricConstants;

   typedef enum
   {
      COMMAND_C_STORE           = 0x0001,
      COMMAND_C_FIND            = 0x0020,
      COMMAND_C_GET             = 0x0010,
      COMMAND_C_MOVE            = 0x0021,
      COMMAND_C_CANCEL          = 0x0FFF,
      COMMAND_C_ECHO            = 0x0030,
      COMMAND_N_REPORT          = 0x0100,
      COMMAND_N_GET             = 0x0110,
      COMMAND_N_SET             = 0x0120,
      COMMAND_N_ACTION          = 0x0130,
      COMMAND_N_CREATE          = 0x0140,
      COMMAND_N_DELETE          = 0x0150,

      COMMAND_REQUEST           = 0x0000,
      COMMAND_RESPONSE          = 0x8000,
   } DicomCommandSetConstants;

   typedef enum
   {
      DICOM_PRIORITY_LOW        = 0x0002,
      DICOM_PRIORITY_MEDIUM     = 0x0000,
      DICOM_PRIORITY_HIGH       = 0x0001,
   } DicomCommandSetMessagePriorities;

   typedef enum
   {
      COMMAND_PRIORITY_LOW          =  0x0002,
      COMMAND_PRIORITY_MEDIUM       =  0x0000,
      COMMAND_PRIORITY_HIGH         =  0x0001,
   } DicomCommandPriorities;

   typedef enum
   {
      COMMAND_DATASET_PRESENT    = 0x0000,
      COMMAND_DATASET_IDENTIFIER = 0x0102,
      COMMAND_DATASET_ABSENT     = 0x0101,
   } DicomCommandSetDataSetTypes;

   typedef enum
   {
      COMMAND_STATUS_SUCCESS                  = 0x0000,   // Success
      COMMAND_STATUS_CANCEL                   = 0xFE00,   // Cancel
      COMMAND_STATUS_ATTRIBUTE_LIST_ERROR     = 0x0107,   // Attribute list error
      COMMAND_STATUS_ATTRIBUTE_OUT_OF_RANGE   = 0x0116,   // Attribute Value Out of Range
      COMMAND_STATUS_CLASS_NOT_SUPPORTED      = 0x0122,   // Class not supported
      COMMAND_STATUS_CLASE_INSTANCE_CONFLICT  = 0x0119,   // Class-instance conflict
      COMMAND_STATUS_DUPLICATE_INSTANCE       = 0x0111,   // Duplicate instance
      COMMAND_STATUS_DUPLICATE_INVOCATION     = 0x0210,   // Duplicate invocation
      COMMAND_STATUS_INVALID_ARGUMENT_VALUE   = 0x0115,   // Invalid argument value
      COMMAND_STATUS_INVALID_ATTRIBUTE_VALUE  = 0x0106,   // Invalid attribute value
      COMMAND_STATUS_INVALID_OBJECT_INSTANCE  = 0x0117,   // Ivalid object instance
      COMMAND_STATUS_MISSING_ATTRIBUTE        = 0x0120,   // Missing attribute
      COMMAND_STATUS_MISSING_ATTRIBUTE_VALUE  = 0x0121,   // Missing attribute value
      COMMAND_STATUS_MISTYPED_ARGUMENT        = 0x0212,   // Mistyped argument
      COMMAND_STATUS_NO_SUCH_ARGUMENT         = 0x0114,   // No such argument
      COMMAND_STATUS_NO_SUCH_ATTRIBUTE        = 0x0105,   // No such attribute
      COMMAND_STATUS_NO_SUCH_EVENT_TYPE       = 0x0113,   // No such event type
      COMMAND_STATUS_NO_SUCH_OBJECT_INSTANCE  = 0x0112,   // No such object instance
      COMMAND_STATUS_NO_SUCH_CLASS            = 0x0118,   // No such class
      COMMAND_STATUS_PROCESSING_FAILURE       = 0x0110,   // Proccesing failure
      COMMAND_STATUS_RESOURCE_LIMITATION      = 0x0213,   // Resource limitation
      COMMAND_STATUS_UNRECOGNIZED_OPERATION   = 0x0211,   // Unrecognized operation
      COMMAND_STATUS_PENDING                  = 0xFF00,   // Matches are continuing - Current Match is supplied and any Optional Keys were supported in the same manner as Required Keys.
      COMMAND_STATUS_PENDING_WARNING          = 0xFF01,   // Matches are continuing - Warning that one or more Optional Keys were not supported for existence and/or matching for this Identifier.
   } DicomCommandStatusConstants;

   typedef enum
   {
      DICOM_UID_TYPE_OTHER          = 0,     // Unknown
      DICOM_UID_TYPE_TRANSFER1      = 1,     // Transfer Syntax - Uncompressed Image
      DICOM_UID_TYPE_TRANSFER2      = 2,     // Transfer Syntax - Compressed Image
      DICOM_UID_TYPE_CLASS          = 3,     // SOP Class
      DICOM_UID_TYPE_META_CLASS     = 4,     // Meta SOP Class
      DICOM_UID_TYPE_INSTANCE       = 5,     // SOP Instance
      DICOM_UID_TYPE_APPLICATION    = 6,     // Application Context Name
   } DicomUIDTypes;


#ifndef PDU_MAX_UID_SIZE
   #define PDU_MAX_UID_SIZE                  64
   #define PDU_MAX_TITLE_SIZE                64
   #define PDU_MAX_VERSION_SIZE              16
   #define PDU_MIN_MAXIMUM_LENGTH             8
#endif

#ifndef UID_MAX_SIZE
   #define UID_MAX_SIZE   64
#endif

#ifndef UID_VERIFICATION_CLASS
   #define UID_VERIFICATION_CLASS                        "1.2.840.10008.1.1"              // Verification SOP Class
   #define UID_IMPLICIT_VR_LITTLE_ENDIAN                 "1.2.840.10008.1.2"              // Implicit VR Little Endian
   #define UID_EXPLICIT_VR_LITTLE_ENDIAN                 "1.2.840.10008.1.2.1"            // Explicit VR Little Endian
   #define UID_EXPLICIT_VR_BIG_ENDIAN                    "1.2.840.10008.1.2.2"            // Explicit VR Big Endian
   #define UID_JPEG_BASELINE_1                           "1.2.840.10008.1.2.4.50"         // JPEG Baseline (Process 1)
   #define UID_JPEG_EXTENDED_2_4                         "1.2.840.10008.1.2.4.51"         // JPEG Extended (Process 2 & 4)
   #define UID_JPEG_EXTENDED_3_5                         "1.2.840.10008.1.2.4.52"         // JPEG Extended (Process 3 & 5)
   #define UID_JPEG_SPECTRAL_NONHIER_6_8                 "1.2.840.10008.1.2.4.53"         // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
   #define UID_JPEG_SPECTRAL_NONHIER_7_9                 "1.2.840.10008.1.2.4.54"         // JPEG Spectral Selection, Non-Hierarchical (Process 7 & 9)
   #define UID_JPEG_FULL_NONHIER_10_12                   "1.2.840.10008.1.2.4.55"         // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
   #define UID_JPEG_FULL_NONHIER_11_13                   "1.2.840.10008.1.2.4.56"         // JPEG Full Progression, Non-Hierarchical (Process 11 & 13)
   #define UID_JPEG_LOSSLESS_NONHIER_14                  "1.2.840.10008.1.2.4.57"         // JPEG Lossless, Non-Hierarchical (Process 14)
   #define UID_JPEG_LOSSLESS_NONHIER_15                  "1.2.840.10008.1.2.4.58"         // JPEG Lossless, Non-Hierarchical (Process 15)
   #define UID_JPEG_EXTENDED_HIER_16_18                  "1.2.840.10008.1.2.4.59"         // JPEG Extended, Hierarchical (Process 16 & 18)
   #define UID_JPEG_EXTENDED_HIER_17_19                  "1.2.840.10008.1.2.4.60"         // JPEG Extended, Hierarchical (Process 17 & 19)
   #define UID_JPEG_SPECTRAL_HIER_20_22                  "1.2.840.10008.1.2.4.61"         // JPEG Spectral Selection, Hierarchical (Process 20 & 22)
   #define UID_JPEG_SPECTRAL_HIER_21_23                  "1.2.840.10008.1.2.4.62"         // JPEG Spectral Selection, Hierarchical (Process 21 & 23)
   #define UID_JPEG_FULL_HIER_24_26                      "1.2.840.10008.1.2.4.63"         // JPEG Full Progression, Hierarchical (Process 24 & 26)
   #define UID_JPEG_FULL_HIER_25_27                      "1.2.840.10008.1.2.4.64"         // JPEG Full Progression, Hierarchical (Process 25 & 27)
   #define UID_JPEG_LOSSLESS_HIER_PROCESS_28             "1.2.840.10008.1.2.4.65"         // JPEG Lossless, Hierarchical (Process 28)
   #define UID_JPEG_LOSSLESS_HIER_PROCESS_29             "1.2.840.10008.1.2.4.66"         // JPEG Lossless, Hierarchical (Process 29)
   #define UID_JPEG_LOSSLESS_NONHIER_14B                 "1.2.840.10008.1.2.4.70"         // JPEG Lossless, Non-Hierarchical, First-Order Prediction (Process 14 [Selection Value 1])
   #define UID_RLE_LOSSLESS                              "1.2.840.10008.1.2.5"            // RLE Lossless
   #define UID_MEDIA_DIRECTORY_STORAGE                   "1.2.840.10008.1.3.10"           // Media Storage Directory Storage
   #define UID_BASIC_STUDY_NOTIFICATION_CLASS            "1.2.840.10008.1.9"              // Basic Study Content Notification SOP Class
   #define UID_STORAGE_COMMITMENT_PUSH_CLASS             "1.2.840.10008.1.20.1"           // Storage Commitment Push Model SOP Class
   #define UID_STORAGE_COMMITMENT_PUSH_INSTANCE          "1.2.840.10008.1.20.1.1"         // Storage Commitment Push Model SOP Instance
   #define UID_STORAGE_COMMITMENT_PULL_CLASS             "1.2.840.10008.1.20.2"           // Storage Commitment Pull Model SOP Class
   #define UID_STORAGE_COMMITMENT_PULL_INSTANCE          "1.2.840.10008.1.20.2.1"         // Storage Commitment Pull Model SOP Instance
   #define UID_APPLICATION_CONTEXT_NAME                  "1.2.840.10008.3.1.1.1"          // Application Context Name
   #define UID_DETACHED_PATIENT_CLASS                    "1.2.840.10008.3.1.2.1.1"        // Detached Patient Management SOP Class
   #define UID_DETACHED_PATIENT_META_CLASS               "1.2.840.10008.3.1.2.1.4"        // Detached Patient Management Meta SOP Class
   #define UID_DETACHED_VISIT_CLASS                      "1.2.840.10008.3.1.2.2.1"        // Detached Visit Management SOP Class
   #define UID_DETACHED_STUDY_CLASS                      "1.2.840.10008.3.1.2.3.1"        // Detached Study Management SOP Class
   #define UID_STUDY_COMPONENT_CLASS                     "1.2.840.10008.3.1.2.3.2"        // Study Component Management SOP Class
   #define UID_MODALITY_PERFORMED_CLASS                  "1.2.840.10008.3.1.2.3.3"        // Modality Performed Procedure Step SOP Class
   #define UID_MODALITY_PERFORMED_RETRIEVE_CLASS         "1.2.840.10008.3.1.2.3.4"        // Modality Performed Procedure Step Retrieve SOP Class
   #define UID_MODALITY_PERFORMED_NOTIFICATION_CLASS     "1.2.840.10008.3.1.2.3.5"        // Modality Performed Procedure Step Notification SOP Class
   #define UID_DETACHED_RESULTS_CLASS                    "1.2.840.10008.3.1.2.5.1"        // Detached Results Management SOP Class
   #define UID_DETACHED_RESULTS_META_CLASS               "1.2.840.10008.3.1.2.5.4"        // Detached Results Management Meta SOP Class
   #define UID_DETACHED_STUDY_META_CLASS                 "1.2.840.10008.3.1.2.5.5"        // Detached Study Management Meta SOP Class
   #define UID_DETACHED_INTERPRETATION_CLASS             "1.2.840.10008.3.1.2.6.1"        // Detached Interpretation Management SOP Class
   #define UID_BASIC_FILM_SESSION_CLASS                  "1.2.840.10008.5.1.1.1"          // Basic Film Session SOP Class
   #define UID_BASIC_FILM_BOX_CLASS                      "1.2.840.10008.5.1.1.2"          // Basic Film Box SOP Class
   #define UID_BASIC_GRAYSCALE_IMAGE_BOX_CLASS           "1.2.840.10008.5.1.1.4"          // Basic Grayscale Image Box SOP Class
   #define UID_BASIC_COLOR_IMAGE_BOX_CLASS               "1.2.840.10008.5.1.1.4.1"        // Basic Color Image Box SOP Class
   #define UID_REFERENCED_IMAGE_BOX_CLASS                "1.2.840.10008.5.1.1.4.2"        // Referenced Image Box SOP Class
   #define UID_BASIC_GRAYSCALE_PRINT_META_CLASS          "1.2.840.10008.5.1.1.9"          // Basic Grayscale Print Management Meta SOP Class
   #define UID_REFERENCED_GRAYSCALE_PRINT_META_CLASS     "1.2.840.10008.5.1.1.9.1"        // Referenced Grayscale Print Management Meta SOP Class
   #define UID_PRINT_JOB_CLASS                           "1.2.840.10008.5.1.1.14"         // Print Job SOP Class
   #define UID_BASIC_ANNOTATION_BOX_CLASS                "1.2.840.10008.5.1.1.15"         // Basic Annotation Box SOP Class
   #define UID_PRINTER_CLASS                             "1.2.840.10008.5.1.1.16"         // Printer SOP Class
   #define UID_PRINTER_INSTANCE                          "1.2.840.10008.5.1.1.17"         // Printer SOP Instance
   #define UID_BASIC_COLOR_PRINT_META_CLASS              "1.2.840.10008.5.1.1.18"         // Basic Color Print Management Meta SOP Class
   #define UID_REFERENCED_COLOR_PRINT_META_CLASS         "1.2.840.10008.5.1.1.18.1"       // Referenced Color Print Management Meta SOP Class
   #define UID_VOI_LUT_BOX_CLASS                         "1.2.840.10008.5.1.1.22"         // VOI LUT Box SOP Class
   #define UID_PRESENTATION_LUT_CLASS                    "1.2.840.10008.5.1.1.23"         // Presentation LUT SOP Class
   #define UID_IMAGE_OVERLAY_BOX_CLASS                   "1.2.840.10008.5.1.1.24"         // Image Overlay Box SOP Class
   #define UID_PRINT_QUEUE_INSTANCE                      "1.2.840.10008.5.1.1.25"         // Print Queue SOP Instance
   #define UID_PRINT_QUEUE_CLASS                         "1.2.840.10008.5.1.1.26"         // Print Queue Management SOP Class
   #define UID_STORED_PRINT_STORAGE_CLASS                "1.2.840.10008.5.1.1.27"         // Stored Print Storage SOP Class
   #define UID_HARDCOPY_GRAYSCALE_IMAGE_STORAGE_CLASS    "1.2.840.10008.5.1.1.29"         // Hardcopy Grayscale Image Storage SOP Class
   #define UID_HARDCOPY_COLOR_IMAGE_STORAGE_CLASS        "1.2.840.10008.5.1.1.30"         // Hardcopy Color Image Storage SOP Class
   #define UID_PULL_PRINT_REQUEST_CLASS                  "1.2.840.10008.5.1.1.31"         // Pull Print Request SOP Class
   #define UID_PULL_STORED_PRINT_META_CLASS              "1.2.840.10008.5.1.1.32"         // Pull Stored Print Management Meta SOP Class
   #define UID_CR_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.1"      // Computed Radiography Image Storage
   #define UID_CT_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.2"      // Computed Tomography Image Storage
   #define UID_US_MULTIFRAME_IMAGE_STORAGE_RETIRED       "1.2.840.10008.5.1.4.1.1.3"      // Ultrasound Multi-frame Image Storage (Retired)
   #define UID_US_MULTIFRAME_IMAGE_STORAGE               "1.2.840.10008.5.1.4.1.1.3.1"    // Ultrasound Multi-frame Image Storage
   #define UID_MR_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.4"      // Magnetic Resonance Image Storage
   #define UID_NM_IMAGE_STORAGE_RETIRED                  "1.2.840.10008.5.1.4.1.1.5"      // Nuclear Medicine Image Storage (Retired)
   #define UID_US_IMAGE_STORAGE_RETIRED                  "1.2.840.10008.5.1.4.1.1.6"      // Ultrasound Image Storage (Retired)
   #define UID_US_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.6.1"    // Ultrasound Image Storage
   #define UID_SC_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.7"      // Secondary Capture Image Storage
   #define UID_STANDALONE_OVERLAY_STORAGE                "1.2.840.10008.5.1.4.1.1.8"      // Standalone Overlay Storage
   #define UID_STANDALONE_CURVE_STORAGE                  "1.2.840.10008.5.1.4.1.1.9"      // Standalone Curve Storage
   #define UID_STANDALONE_MODALITY_LUT_STORAGE           "1.2.840.10008.5.1.4.1.1.10"     // Standalone Modality LUT Storage
   #define UID_STANDALONE_VOI_LUT_STORAGE                "1.2.840.10008.5.1.4.1.1.11"     // Standalone VOI LUT Storage
   #define UID_XA_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.12.1"   // X-Ray Angiographic Image Storage
   #define UID_XRF_IMAGE_STORAGE                         "1.2.840.10008.5.1.4.1.1.12.2"   // X-Ray Radiofluoroscopic Image Storage
   #define UID_XA_BIPLANE_IMAGE_STORAGE                  "1.2.840.10008.5.1.4.1.1.12.3"   // X-Ray Angiographic Bi-Plane Image Storage
   #define UID_NM_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.20"     // Nuclear Medicine Image Storage
   #define UID_PET_IMAGE_STORAGE                         "1.2.840.10008.5.1.4.1.1.128"    // Positron Emission Tomography Image Storage
   #define UID_STANDALONE_PET_CURVE_STORAGE              "1.2.840.10008.5.1.4.1.1.129"    // Standalone Positron Emission Tomography Curve Storage
   #define UID_RT_IMAGE_STORAGE                          "1.2.840.10008.5.1.4.1.1.481.1"  // Radiotherapy Image Storage
   #define UID_RT_DOSE_STORAGE                           "1.2.840.10008.5.1.4.1.1.481.2"  // Radiotherapy Dose Storage
   #define UID_RT_STRUCTURE_STORAGE                      "1.2.840.10008.5.1.4.1.1.481.3"  // Radiotherapy Structure Set Storage
   #define UID_RT_PLAN_STORAGE                           "1.2.840.10008.5.1.4.1.1.481.5"  // Radiotherapy Plan Storage
   #define UID_PATIENT_ROOT_QUERY_FIND                   "1.2.840.10008.5.1.4.1.2.1.1"    // Patient Root Query/Retrieve Information Model - FIND
   #define UID_PATIENT_ROOT_QUERY_MOVE                   "1.2.840.10008.5.1.4.1.2.1.2"    // Patient Root Query/Retrieve Information Model - MOVE
   #define UID_PATIENT_ROOT_QUERY_GET                    "1.2.840.10008.5.1.4.1.2.1.3"    // Patient Root Query/Retrieve Information Model - GET
   #define UID_STUDY_ROOT_QUERY_FIND                     "1.2.840.10008.5.1.4.1.2.2.1"    // Study Root Query/Retrieve Information Model - FIND
   #define UID_STUDY_ROOT_QUERY_MOVE                     "1.2.840.10008.5.1.4.1.2.2.2"    // Study Root Query/Retrieve Information Model - MOVE
   #define UID_STUDY_ROOT_QUERY_GET                      "1.2.840.10008.5.1.4.1.2.2.3"    // Study Root Query/Retrieve Information Model - GET
   #define UID_PATIENT_STUDY_QUERY_FIND                  "1.2.840.10008.5.1.4.1.2.3.1"    // Patient/Study Only Query/Retrieve Information Model - FIND
   #define UID_PATIENT_STUDY_QUERY_MOVE                  "1.2.840.10008.5.1.4.1.2.3.2"    // Patient/Study Only Query/Retrieve Information Model - MOVE
   #define UID_PATIENT_STUDY_QUERY_GET                   "1.2.840.10008.5.1.4.1.2.3.3"    // Patient/Study Only Query/Retrieve Information Model - GET
   #define UID_MODALITY_WORKLIST_FIND                    "1.2.840.10008.5.1.4.31"         // Modality Worklist Information Model - FIND

   #define UID_DX_IMAGE_STORAGE_PRESENTATION             "1.2.840.10008.5.1.4.1.1.1.1"    // Digital X-Ray Image Storage - For Presentation
   #define UID_DX_IMAGE_STORAGE_PROCESSING               "1.2.840.10008.5.1.4.1.1.1.1.1"  // Digital X-Ray Image Storage - For Processing
   #define UID_DX_MAMMOGRAPHY_IMAGE_STORAGE_PRESENTATION "1.2.840.10008.5.1.4.1.1.1.2"    // Digital Mammography X-Ray Image Storage - For Presentation
   #define UID_DX_MAMMOGRAPHY_IMAGE_STORAGE_PROCESSING   "1.2.840.10008.5.1.4.1.1.1.2.1"  // Digital Mammography X-Ray Image Storage - For Processing
   #define UID_DX_INTRAORAL_IMAGE_STORAGE_PRESENTATION   "1.2.840.10008.5.1.4.1.1.1.3"    // Digital Intra-oral X-Ray Image Storage - For Presentation
   #define UID_DX_INTRAORAL_IMAGE_STORAGE_PROCESSING     "1.2.840.10008.5.1.4.1.1.1.3.1"  // Digital Intra-oral X-Ray Image Storage - For Processing

   #define UID_PAPYRUS_3_IMPLICIT_VR_LITTLE_ENDIAN               "1.2.840.10008.1.20"             // Papyrus 3 Implicit VR Little Endian
   #define UID_VISIBLE_LIGHT_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.77.1"   // Visible Light Image Storage
   #define UID_VISIBLE_LIGHT_MULTIFRAME_IMAGE_STORAGE            "1.2.840.10008.5.1.4.1.1.77.2"   // Visible Light Multiframe Image Storage
   #define UID_WAVEFORM_STORAGE                                  "1.2.840.10008.5.1.4.1.1.9.1"    // Waveform Storage
   #define UID_ECG_WAVEFORM_STORAGE                              "1.2.840.10008.5.1.4.1.1.9.1.1"  // ECG Waveform Storage
   #define UID_AUDIO_WAVEFORM_STORAGE                            "1.2.840.10008.5.1.4.1.1.9.1.2"  // Audio Waveform Storage
   #define UID_GE_MAGNETIC_RESONANCE_IMAGE_INFORMATION_OBJECT    "1.2.840.113619.4.2"             // GE Private Dicom Magnetic Resonance Image Information Object
   #define UID_GE_COMPUTED_TOMOGRAPHY_IMAGE_INFORMATION_OBJECT   "1.2.840.113619.4.3"             // GE Private Dicom Computed Tomography Image Information Object
   #define UID_GE_DISPLAY_IMAGERMATION_INFO_OBJECT               "1.2.840.113619.4.4"             // GE Private Dicom Display Imagermation Info Object
   #define UID_GE_ARM_MIGRATION                                  "1.2.840.113619.4.10"            // GE Private ARM Migration
   #define UID_GE_ARM_MIGRATION_INSTANCE                         "1.2.840.113619.7.2"             // GE Private ARM Migration Instance
   #define UID_BASIC_TEXT_SR                                     "1.2.840.10008.5.1.4.1.1.88.11"
   #define UID_ENHANCED_SR                                       "1.2.840.10008.5.1.4.1.1.88.22"
   #define UID_COMPREHENSIVE_SR                                  "1.2.840.10008.5.1.4.1.1.88.33"
   #define UID_JPEG_LS_LOSSLESS                                  "1.2.840.10008.1.2.4.80"
   #define UID_JPEG_LS_LOSSY                                     "1.2.840.10008.1.2.4.81"
   #define UID_AMBULATORY_ECG_WAVEFORM_STORAGE                   "1.2.840.10008.5.1.4.1.1.9.1.3"
   #define UID_HEMODYNAMIC_WAVEFORM_STORAGE                      "1.2.840.10008.5.1.4.1.1.9.2.1"
   #define UID_CARDIAC_ELECTROPHYSIOLOGY_WAVEFORM_STORAGE        "1.2.840.10008.5.1.4.1.1.9.3.1"
   #define UID_BASIC_VOICE_AUDIO_WAVEFORM_STORAGE                "1.2.840.10008.5.1.4.1.1.9.4.1"
   #define UID_GRAYSCALE_SOFTCOPY_PRESENTATION_STATE_STORAGE     "1.2.840.10008.5.1.4.1.1.11.1"
#endif

   // Ways of controlling the compression
   typedef enum DicomJ2KCompressionControl
   {      
      DICOM_J2K_COMP_RATIO,
      DICOM_J2K_COMP_TARGETSIZE,
      DICOM_J2K_COMP_QFACTOR,
   } DicomJ2KCompressionControl;

#ifndef J2K_CONSTANTS
#define J2K_CONSTANTS
   // JPEG 2000 Limitations imposed by the standard
   typedef enum J2KLimitConstants
   {
      J2K_MAX_COMPONENTS_NUM = 3,
      J2K_MAX_DECOMP_LEVEL = 20,
   } J2KLimitConstants;

   // Progressions Order
   typedef enum J2KProgressionFlags
   {
      J2K_LAYER_RESOLUTION_COMPONENT_POSITION = 0,
      J2K_RESOLUTION_LAYER_COMPONENT_POSITION = 1,
      J2K_RESOLUTION_POSITION_COMPONENT_LAYER = 2,
      J2K_POSITION_COMPONENT_RESOLUTION_LAYER = 3,
      J2K_COMPONENT_POSITION_RESOLUTION_LAYER = 4,
   } J2KProgressionFlags;
   // Ways of how to set the Region Of Interest 
   typedef enum J2KRegionOfInterest
   {
      J2K_USELEAD_REGION,          // Use LEAD bitmap region
      J2K_USEOPTION_RECT,          // Use rcROI member of FILEJ2KOPTIONS
   } J2KRegionOfInterest;

#endif

#endif                          /* _LTDICOCX_H_ */
