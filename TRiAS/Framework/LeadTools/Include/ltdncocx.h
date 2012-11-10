#ifndef _LTDNCOCX_H_
#define _LTDNCOCX_H_

// ActiveX error codes
#include "L_OcxErr.h"

// L_SUPPORT_XXX constants
#include "ltlck_.h"

   typedef enum
   {
      PDU_ACCEPT_RESULT_SUCCESS          = 0,  // Acceptance
      PDU_ACCEPT_RESULT_USER_REJECT      = 1,  // User rejection
      PDU_ACCEPT_RESULT_PROVIDER_REJECT  = 2,  // No reason (provider rejection)
      PDU_ACCEPT_RESULT_ABSTRACT_SYNTAX  = 3,  // Abstract syntax not supported (provider rejection)
      PDU_ACCEPT_RESULT_TRANSFER_SYNTAX  = 4,  // Transfer syntaxes not supported (provider rejection)
   } AssociateAcceptConstants;

   typedef enum
   {
      PDU_REJECT_RESULT_PERMANENT        = 1,  // Rejected permanent
      PDU_REJECT_RESULT_TRANSIENT        = 2,  // Rejected transient

      PDU_REJECT_SOURCE_USER             = 1,  // DICOM UL service-user
      PDU_REJECT_SOURCE_PROVIDER1        = 2,  // DICOM UL service-provider (ASCE related function)
      PDU_REJECT_SOURCE_PROVIDER2        = 3,  // DICOM UL service-provider (Presentation related function)

      PDU_REJECT_REASON_UNKNOWN          = 1,  // No reason given (User)
      PDU_REJECT_REASON_APPLICATION      = 2,  // Application context name not supported (User)
      PDU_REJECT_REASON_CALLING          = 3,  // Calling AE Title not recognized (User)
      PDU_REJECT_REASON_CALLED           = 7,  // Called AE Title not recognized (User)

//      PDU_REJECT_REASON_UNKNWON          = 1,  // No reason given (Provider1)
      PDU_REJECT_REASON_VERSION          = 2,  // Protocol version not supported (Provider1)

      PDU_REJECT_REASON_CONGESTION       = 1,  // Temporary congestion (Provider2)
      PDU_REJECT_REASON_LIMIT            = 2,  // Local limit exceeded (Provider2)
   } AssociateRejectConstants;

   typedef enum
   {
      PDU_ABORT_SOURCE_USER              = 0,  // Service user
      PDU_ABORT_SOURCE_PROVIDER          = 2,  // Service provider

      PDU_ABORT_REASON_UNKNOWN            = 0,  // Reason no specified (Provider)
      PDU_ABORT_REASON_UNRECOGNIZED       = 1,  // Unrecognized PDU (Provider)
      PDU_ABORT_REASON_UNEXPECTED         = 2,  // Unexpected PDU (Provider)
      PDU_ABORT_REASON_UNRECOGNIZED_PARAM = 4,  // Unrecognized PDU parameter (Provider)
      PDU_ABORT_REASON_UNEXPECTED_PARAM   = 5,  // Unexpected PDU parameter (Provider)
      PDU_ABORT_REASON_INVALID_PARAM      = 6,  // Invalid PDU parameter value (Provider)
   } AbortConstants;

#ifndef UID_MAX_SIZE
   #define UID_MAX_SIZE   64
#endif

#ifndef UID_VERIFICATION_CLASS
   #define UID_VERIFICATION_CLASS                     "1.2.840.10008.1.1"              // Verification SOP Class
   #define UID_IMPLICIT_VR_LITTLE_ENDIAN              "1.2.840.10008.1.2"              // Implicit VR Little Endian
   #define UID_EXPLICIT_VR_LITTLE_ENDIAN              "1.2.840.10008.1.2.1"            // Explicit VR Little Endian
   #define UID_EXPLICIT_VR_BIG_ENDIAN                 "1.2.840.10008.1.2.2"            // Explicit VR Big Endian
   #define UID_JPEG_BASELINE_1                        "1.2.840.10008.1.2.4.50"         // JPEG Baseline (Process 1)
   #define UID_JPEG_EXTENDED_2_4                      "1.2.840.10008.1.2.4.51"         // JPEG Extended (Process 2 & 4)
   #define UID_JPEG_EXTENDED_3_5                      "1.2.840.10008.1.2.4.52"         // JPEG Extended (Process 3 & 5)
   #define UID_JPEG_SPECTRAL_NONHIER_6_8              "1.2.840.10008.1.2.4.53"         // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
   #define UID_JPEG_SPECTRAL_NONHIER_7_9              "1.2.840.10008.1.2.4.54"         // JPEG Spectral Selection, Non-Hierarchical (Process 7 & 9)
   #define UID_JPEG_FULL_NONHIER_10_12                "1.2.840.10008.1.2.4.55"         // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
   #define UID_JPEG_FULL_NONHIER_11_13                "1.2.840.10008.1.2.4.56"         // JPEG Full Progression, Non-Hierarchical (Process 11 & 13)
   #define UID_JPEG_LOSSLESS_NONHIER_14               "1.2.840.10008.1.2.4.57"         // JPEG Lossless, Non-Hierarchical (Process 14)
   #define UID_JPEG_LOSSLESS_NONHIER_15               "1.2.840.10008.1.2.4.58"         // JPEG Lossless, Non-Hierarchical (Process 15)
   #define UID_JPEG_EXTENDED_HIER_16_18               "1.2.840.10008.1.2.4.59"         // JPEG Extended, Hierarchical (Process 16 & 18)
   #define UID_JPEG_EXTENDED_HIER_17_19               "1.2.840.10008.1.2.4.60"         // JPEG Extended, Hierarchical (Process 17 & 19)
   #define UID_JPEG_SPECTRAL_HIER_20_22               "1.2.840.10008.1.2.4.61"         // JPEG Spectral Selection, Hierarchical (Process 20 & 22)
   #define UID_JPEG_SPECTRAL_HIER_21_23               "1.2.840.10008.1.2.4.62"         // JPEG Spectral Selection, Hierarchical (Process 21 & 23)
   #define UID_JPEG_FULL_HIER_24_26                   "1.2.840.10008.1.2.4.63"         // JPEG Full Progression, Hierarchical (Process 24 & 26)
   #define UID_JPEG_FULL_HIER_25_27                   "1.2.840.10008.1.2.4.64"         // JPEG Full Progression, Hierarchical (Process 25 & 27)
   #define UID_JPEG_LOSSLESS_HIER_PROCESS_28          "1.2.840.10008.1.2.4.65"         // JPEG Lossless, Hierarchical (Process 28)
   #define UID_JPEG_LOSSLESS_HIER_PROCESS_29          "1.2.840.10008.1.2.4.66"         // JPEG Lossless, Hierarchical (Process 29)
   #define UID_JPEG_LOSSLESS_NONHIER_14B              "1.2.840.10008.1.2.4.70"         // JPEG Lossless, Non-Hierarchical, First-Order Prediction (Process 14 [Selection Value 1])
   #define UID_RLE_LOSSLESS                           "1.2.840.10008.1.2.5"            // RLE Lossless
   #define UID_MEDIA_DIRECTORY_STORAGE                "1.2.840.10008.1.3.10"           // Media Storage Directory Storage
   #define UID_BASIC_STUDY_NOTIFICATION_CLASS         "1.2.840.10008.1.9"              // Basic Study Content Notification SOP Class
   #define UID_STORAGE_COMMITMENT_PUSH_CLASS          "1.2.840.10008.1.20.1"           // Storage Commitment Push Model SOP Class
   #define UID_STORAGE_COMMITMENT_PUSH_INSTANCE       "1.2.840.10008.1.20.1.1"         // Storage Commitment Push Model SOP Instance
   #define UID_STORAGE_COMMITMENT_PULL_CLASS          "1.2.840.10008.1.20.2"           // Storage Commitment Pull Model SOP Class
   #define UID_STORAGE_COMMITMENT_PULL_INSTANCE       "1.2.840.10008.1.20.2.1"         // Storage Commitment Pull Model SOP Instance
   #define UID_APPLICATION_CONTEXT_NAME               "1.2.840.10008.3.1.1.1"          // Application Context Name
   #define UID_DETACHED_PATIENT_CLASS                 "1.2.840.10008.3.1.2.1.1"        // Detached Patient Management SOP Class
   #define UID_DETACHED_PATIENT_META_CLASS            "1.2.840.10008.3.1.2.1.4"        // Detached Patient Management Meta SOP Class
   #define UID_DETACHED_VISIT_CLASS                   "1.2.840.10008.3.1.2.2.1"        // Detached Visit Management SOP Class
   #define UID_DETACHED_STUDY_CLASS                   "1.2.840.10008.3.1.2.3.1"        // Detached Study Management SOP Class
   #define UID_STUDY_COMPONENT_CLASS                  "1.2.840.10008.3.1.2.3.2"        // Study Component Management SOP Class
   #define UID_MODALITY_PERFORMED_CLASS               "1.2.840.10008.3.1.2.3.3"        // Modality Performed Procedure Step SOP Class
   #define UID_MODALITY_PERFORMED_RETRIEVE_CLASS      "1.2.840.10008.3.1.2.3.4"        // Modality Performed Procedure Step Retrieve SOP Class
   #define UID_MODALITY_PERFORMED_NOTIFICATION_CLASS  "1.2.840.10008.3.1.2.3.5"        // Modality Performed Procedure Step Notification SOP Class
   #define UID_DETACHED_RESULTS_CLASS                 "1.2.840.10008.3.1.2.5.1"        // Detached Results Management SOP Class
   #define UID_DETACHED_RESULTS_META_CLASS            "1.2.840.10008.3.1.2.5.4"        // Detached Results Management Meta SOP Class
   #define UID_DETACHED_STUDY_META_CLASS              "1.2.840.10008.3.1.2.5.5"        // Detached Study Management Meta SOP Class
   #define UID_DETACHED_INTERPRETATION_CLASS          "1.2.840.10008.3.1.2.6.1"        // Detached Interpretation Management SOP Class
   #define UID_BASIC_FILM_SESSION_CLASS               "1.2.840.10008.5.1.1.1"          // Basic Film Session SOP Class
   #define UID_BASIC_FILM_BOX_CLASS                   "1.2.840.10008.5.1.1.2"          // Basic Film Box SOP Class
   #define UID_BASIC_GRAYSCALE_IMAGE_BOX_CLASS        "1.2.840.10008.5.1.1.4"          // Basic Grayscale Image Box SOP Class
   #define UID_BASIC_COLOR_IMAGE_BOX_CLASS            "1.2.840.10008.5.1.1.4.1"        // Basic Color Image Box SOP Class
   #define UID_REFERENCED_IMAGE_BOX_CLASS             "1.2.840.10008.5.1.1.4.2"        // Referenced Image Box SOP Class
   #define UID_BASIC_GRAYSCALE_PRINT_META_CLASS       "1.2.840.10008.5.1.1.9"          // Basic Grayscale Print Management Meta SOP Class
   #define UID_REFERENCED_GRAYSCALE_PRINT_META_CLASS  "1.2.840.10008.5.1.1.9.1"        // Referenced Grayscale Print Management Meta SOP Class
   #define UID_PRINT_JOB_CLASS                        "1.2.840.10008.5.1.1.14"         // Print Job SOP Class
   #define UID_BASIC_ANNOTATION_BOX_CLASS             "1.2.840.10008.5.1.1.15"         // Basic Annotation Box SOP Class
   #define UID_PRINTER_CLASS                          "1.2.840.10008.5.1.1.16"         // Printer SOP Class
   #define UID_PRINTER_INSTANCE                       "1.2.840.10008.5.1.1.17"         // Printer SOP Instance
   #define UID_BASIC_COLOR_PRINT_META_CLASS           "1.2.840.10008.5.1.1.18"         // Basic Color Print Management Meta SOP Class
   #define UID_REFERENCED_COLOR_PRINT_META_CLASS      "1.2.840.10008.5.1.1.18.1"       // Referenced Color Print Management Meta SOP Class
   #define UID_VOI_LUT_BOX_CLASS                      "1.2.840.10008.5.1.1.22"         // VOI LUT Box SOP Class
   #define UID_PRESENTATION_LUT_CLASS                 "1.2.840.10008.5.1.1.23"         // Presentation LUT SOP Class
   #define UID_IMAGE_OVERLAY_BOX_CLASS                "1.2.840.10008.5.1.1.24"         // Image Overlay Box SOP Class
   #define UID_PRINT_QUEUE_INSTANCE                   "1.2.840.10008.5.1.1.25"         // Print Queue SOP Instance
   #define UID_PRINT_QUEUE_CLASS                      "1.2.840.10008.5.1.1.26"         // Print Queue Management SOP Class
   #define UID_STORED_PRINT_STORAGE_CLASS             "1.2.840.10008.5.1.1.27"         // Stored Print Storage SOP Class
   #define UID_HARDCOPY_GRAYSCALE_IMAGE_STORAGE_CLASS "1.2.840.10008.5.1.1.29"         // Hardcopy Grayscale Image Storage SOP Class
   #define UID_HARDCOPY_COLOR_IMAGE_STORAGE_CLASS     "1.2.840.10008.5.1.1.30"         // Hardcopy Color Image Storage SOP Class
   #define UID_PULL_PRINT_REQUEST_CLASS               "1.2.840.10008.5.1.1.31"         // Pull Print Request SOP Class
   #define UID_PULL_STORED_PRINT_META_CLASS           "1.2.840.10008.5.1.1.32"         // Pull Stored Print Management Meta SOP Class
   #define UID_CR_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.1"      // Computed Radiography Image Storage
   #define UID_CT_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.2"      // Computed Tomography Image Storage
   #define UID_US_MULTIFRAME_IMAGE_STORAGE_RETIRED    "1.2.840.10008.5.1.4.1.1.3"      // Ultrasound Multi-frame Image Storage (Retired)
   #define UID_US_MULTIFRAME_IMAGE_STORAGE            "1.2.840.10008.5.1.4.1.1.3.1"    // Ultrasound Multi-frame Image Storage
   #define UID_MR_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.4"      // Magnetic Resonance Image Storage
   #define UID_NM_IMAGE_STORAGE_RETIRED               "1.2.840.10008.5.1.4.1.1.5"      // Nuclear Medicine Image Storage (Retired)
   #define UID_US_IMAGE_STORAGE_RETIRED               "1.2.840.10008.5.1.4.1.1.6"      // Ultrasound Image Storage (Retired)
   #define UID_US_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.6.1"    // Ultrasound Image Storage
   #define UID_SC_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.7"      // Secondary Capture Image Storage
   #define UID_STANDALONE_OVERLAY_STORAGE             "1.2.840.10008.5.1.4.1.1.8"      // Standalone Overlay Storage
   #define UID_STANDALONE_CURVE_STORAGE               "1.2.840.10008.5.1.4.1.1.9"      // Standalone Curve Storage
   #define UID_STANDALONE_MODALITY_LUT_STORAGE        "1.2.840.10008.5.1.4.1.1.10"     // Standalone Modality LUT Storage
   #define UID_STANDALONE_VOI_LUT_STORAGE             "1.2.840.10008.5.1.4.1.1.11"     // Standalone VOI LUT Storage
   #define UID_XA_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.12.1"   // X-Ray Angiographic Image Storage
   #define UID_XRF_IMAGE_STORAGE                      "1.2.840.10008.5.1.4.1.1.12.2"   // X-Ray Radiofluoroscopic Image Storage
   #define UID_XA_BIPLANE_IMAGE_STORAGE               "1.2.840.10008.5.1.4.1.1.12.3"   // X-Ray Angiographic Bi-Plane Image Storage
   #define UID_NM_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.20"     // Nuclear Medicine Image Storage
   #define UID_PET_IMAGE_STORAGE                      "1.2.840.10008.5.1.4.1.1.128"    // Positron Emission Tomography Image Storage
   #define UID_STANDALONE_PET_CURVE_STORAGE           "1.2.840.10008.5.1.4.1.1.129"    // Standalone Positron Emission Tomography Curve Storage
   #define UID_RT_IMAGE_STORAGE                       "1.2.840.10008.5.1.4.1.1.481.1"  // Radiotherapy Image Storage
   #define UID_RT_DOSE_STORAGE                        "1.2.840.10008.5.1.4.1.1.481.2"  // Radiotherapy Dose Storage
   #define UID_RT_STRUCTURE_STORAGE                   "1.2.840.10008.5.1.4.1.1.481.3"  // Radiotherapy Structure Set Storage
   #define UID_RT_PLAN_STORAGE                        "1.2.840.10008.5.1.4.1.1.481.5"  // Radiotherapy Plan Storage
   #define UID_PATIENT_ROOT_QUERY_FIND                "1.2.840.10008.5.1.4.1.2.1.1"    // Patient Root Query/Retrieve Information Model - FIND
   #define UID_PATIENT_ROOT_QUERY_MOVE                "1.2.840.10008.5.1.4.1.2.1.2"    // Patient Root Query/Retrieve Information Model - MOVE
   #define UID_PATIENT_ROOT_QUERY_GET                 "1.2.840.10008.5.1.4.1.2.1.3"    // Patient Root Query/Retrieve Information Model - GET
   #define UID_STUDY_ROOT_QUERY_FIND                  "1.2.840.10008.5.1.4.1.2.2.1"    // Study Root Query/Retrieve Information Model - FIND
   #define UID_STUDY_ROOT_QUERY_MOVE                  "1.2.840.10008.5.1.4.1.2.2.2"    // Study Root Query/Retrieve Information Model - MOVE
   #define UID_STUDY_ROOT_QUERY_GET                   "1.2.840.10008.5.1.4.1.2.2.3"    // Study Root Query/Retrieve Information Model - GET
   #define UID_PATIENT_STUDY_QUERY_FIND               "1.2.840.10008.5.1.4.1.2.3.1"    // Patient/Study Only Query/Retrieve Information Model - FIND
   #define UID_PATIENT_STUDY_QUERY_MOVE               "1.2.840.10008.5.1.4.1.2.3.2"    // Patient/Study Only Query/Retrieve Information Model - MOVE
   #define UID_PATIENT_STUDY_QUERY_GET                "1.2.840.10008.5.1.4.1.2.3.3"    // Patient/Study Only Query/Retrieve Information Model - GET
   #define UID_MODALITY_WORKLIST_FIND                 "1.2.840.10008.5.1.4.31"         // Modality Worklist Information Model - FIND

   #define UID_PAPYRUS_3_IMPLICIT_VR_LITTLE_ENDIAN               "1.2.840.10008.1.20"             // Papyrus 3 Implicit VR Little Endian
   #define UID_DIGITAL_XR_IMAGE_STORAGE_PRESENTATION             "1.2.840.10008.5.1.4.1.1.1.1"    // Digital X-Ray Image Storage - For Presentation
   #define UID_DIGITAL_XR_IMAGE_STORAGE_PROCESSING               "1.2.840.10008.5.1.4.1.1.1.1.1"  // Digital X-Ray Image Storage - For Processing
   #define UID_DIGITAL_MAMMOGRAPHY_XR_IMAGE_STORAGE_PRESENTATION "1.2.840.10008.5.1.4.1.1.1.2"    // Digital Mammography X-Ray Image Storage - For Presentation
   #define UID_DIGITAL_MAMMOGRAPHY_XR_IMAGE_STORAGE_PROCESSING   "1.2.840.10008.5.1.4.1.1.1.2.1"  // Digital Mammography X-Ray Image Storage - For Processing
   #define UID_DIGITAL_INTRAORAL_XR_IMAGE_STORAGE_PRESENTATION   "1.2.840.10008.5.1.4.1.1.1.3"    // Digital Intra-oral X-Ray Image Storage - For Presentation
   #define UID_DIGITAL_INTRAORAL_XR_IMAGE_STORAGE_PROCESSING     "1.2.840.10008.5.1.4.1.1.1.3.1"  // Digital Intra-oral X-Ray Image Storage - For Processing
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

   typedef enum
   {
      PDU_ROLE_NON_SUPPORT              = 0,
      PDU_ROLE_SUPPORT                  = 1,
   } PDURoleSelectConstants;

   typedef enum
   {
      PDU_UNKNOWN                   =  0x00,
      PDU_ASSOCIATE_REQUEST         =  0x01,
      PDU_ASSOCIATE_ACCEPT          =  0x02,
      PDU_ASSOCIATE_REJECT          =  0x03,
      PDU_DATA_TRANSFER             =  0x04,
      PDU_RELEASE_REQUEST           =  0x05,
      PDU_RELEASE_RESPONSE          =  0x06,
      PDU_ABORT                     =  0x07,
   } PDUTypeConstants;

   typedef enum
   {
      DICOM_SECURE_NONE         =  0xABCD0000,
      DICOM_SECURE_ISCL         =  0xABCD0001,
      DICOM_SECURE_TLS          =  0xABCD0002,
   } DicomSecurityMode;

   typedef enum
   {
      DICOM_TLS_DHE_RSA_WITH_DES_CBC_SHA        = 0x12,
      DICOM_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA   = 0x13,  // mandatory standard
   } DicomCiphersuiteConstants;

   typedef enum
   {
      DICOM_CRYPT_DES   = 0x01,
      DICOM_CRYPT_3DES  = 0x02,
   } DicomEncryptionMethod;

   typedef enum
   {
      DICOM_MAC_SHA1  = 0x10,
   } DicomMACTypeConstants;

   typedef enum
   {
      DICOM_MUTUALAUTH_RSA = 0x20,
   } DicomMutualAuthMethod;

   typedef enum
   {
      DICOM_KEYEXCHANGE_RSA_SIGNED_DHE = 0x40,
   } DicomKeyExchangeAlgorithm;

   typedef enum
   {
      L_TLS_FILETYPE_PEM           =  1,
      L_TLS_FILETYPE_ASN1          =  2,
   } DicomTLSCertType;

   typedef enum
   {
      DICOM_ISCL_MUTUAL_AUTH_3P4W       =  0x00000000,
   } DicomMutualAuthMode;

   typedef enum
   {
      DICOM_ISCL_ENCRYPT_NONE        =  0x00000000,
      DICOM_ISCL_ENCRYPT_DESCBC      =  0x00001212,
   } DicomEncryptionMode;

   typedef enum
   {
      DICOM_ISCL_MAC_NONE               =  0x00000000,
      DICOM_ISCL_MAC_MD5                =  0x00001441,
      DICOM_ISCL_MAC_DESMAC             =  0x00004001,
   } DicomMsgAuthCode;

   typedef enum
   {
      DIC_ISCL_CRYPT_KEY_PAIR1 = 0x00000001,
      DIC_ISCL_CRYPT_KEY_PAIR2 = 0x00000002,
      DIC_ISCL_CRYPT_KEY_PAIR3 = 0x00000003,
      DIC_ISCL_CRYPT_KEY_PAIR4 = 0x00000004,
      DIC_ISCL_CRYPT_KEY_PAIR5 = 0x00000005,
      DIC_ISCL_CRYPT_KEY_PAIR6 = 0x00000006,
      DIC_ISCL_CRYPT_KEY_PAIR7 = 0x00000007,
      DIC_ISCL_CRYPT_KEY_PAIR8 = 0x00000008,
      DIC_ISCL_UNIQUE_SESSION_KEYS = 0x00000010
   } DicomISCLCryptKeyPair;

#endif