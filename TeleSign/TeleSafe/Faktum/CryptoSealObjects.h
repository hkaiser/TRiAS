// library CryptoSealObjects declaration file
// Copyright (C) 1999 by Faktum GmbH, Germany. Created 1999. All rights reserved.
// Author: Hans-Peter Baron
//////////////////////////////////////////////////////////////////////

#ifndef _CRYPTOSEALOBJECTS_
#define _CRYPTOSEALOBJECTS_



enum CSERROR {
	CSOK=0,
	CS_UNSPECIFIED,
	CS_MEMORY,
	CS_DB_PATHNAME,
	CS_CANT_OPEN_PKCS11,
	CS_TOKEN,
	CS_CANT_OPEN_SESSION,
	CS_PCSC,
	CS_CARD_MISSING,
	CS_PIN_INVALID,
	CS_LOGIN_FAILED,
	CS_CANT_CLOSE_PKCS11,
	CS_CANT_LOAD_CERTIFICATES,
	CS_NOT_INITIALIZED,
	CS_PRIVATE_KEY_NOT_FOUND,
	CS_OWN_CERTIFICATE_NOT_FOUND,
	CS_PUBLIC_KEY_CANT_DELETE,
	CS_FILE_CANT_CREATE,
	CS_FILE_CANT_OPEN,
	CS_FILE_CANT_READ,
	CS_FILE_CANT_WRITE,
	CS_FILE_CANT_SEEK,
	CS_FILE_CANT_CLOSE,
	CS_CERTIFICATE_CANT_ENTER,
	CS_CERTIFICATE_CANT_RETRIEVE,
	CS_CERTIFICATE_CANT_DELETE,
	CS_CERTIFICATE_CANT_READ,
	CS_CERTIFICATE_CANT_WRITE,
	CS_CERTIFICATE_NOT_OWN,
	CS_CERTIFICATE_NOT_VALID,
	CS_CERTIFICATE_MULTIPLE_NOT_VALID,
	CS_CERTIFICATE_CANT_EXTRACT_PUBLIC_KEY,
	CS_CERTIFICATE_ISSUER_MISSING,
	CS_CERTIFICATE_ALGORITHM_UNKNOWN,
	CS_CERTIFICATE_OUT_OF_PERIOD,
	CS_CERTIFICATE_DATA,
	CS_CERTIFICATE_SIGNATURE_INVALID,
	CS_CERTIFICATE_SELFSIGNED_NOT_TRUSTED,
	CS_DOCUMENT_CANT_RETRIEVE,
	CS_DOCUMENT_CANT_DELETE,
	CS_DOCUMENT_HAS_CONTENTS,
	CS_DOCUMENT_NO_CONTENTS,
	CS_DOCUSER_CANT_ADD,
	CS_DOCUSER_CANT_RETRIEVE,
	CS_DOCUSER_NO_CERTIFICATE,
	CS_DOCUSER_NO_SIGNATURE,
	CS_SIGNATURE_LENGTH,
	CS_SIGNATURE_CANT_CALC,
	CS_SIGNATURE_CANT_LOAD,
	CS_SIGNATURE_CANT_SET,
	CS_SIGNATURE_NOT_VALID,
	CS_SIGNATURE_ALGORITHM_UNKNOWN,
	CS_SIGNATURE_NOT_SAME_ISSUER,
	CS_SIGNATURE_NOT_SAME_CERTIFICATE_NO
};



class CSO_IMPORT CCryptoSealCertificate
{
protected: // don't mess around with these
	CCryptoSealCertificate();
	virtual ~CCryptoSealCertificate();
	explicit CCryptoSealCertificate(const CCryptoSealCertificate &);
	const CCryptoSealCertificate &operator=(const CCryptoSealCertificate &);

public:
	virtual const char *GetOwnerCommonName() const =0;
	virtual const char *GetOwnerEmailAddress() const =0;
	virtual const char *GetOwner254Component(int componentNo) const =0;

	virtual const char *GetIssuerCommonName() const =0;
	virtual const char *GetIssuerEmailAddress() const =0;
	virtual const char *GetIssuer254Component(int componentNo) const =0;

	virtual const unsigned char *GetSerialNumber(int &noLength) const =0;

	// TODO: (const char*) will become time_t later on
	virtual const char *GetNotBefore() const =0;
	virtual const char *GetNotAfter() const =0;

	virtual bool IsTrusted() const =0;
	virtual CSERROR SetTrusted(bool trusted) =0;

	virtual bool IsOwnCertificate() const =0;

	virtual const char *GetLabel() const =0;
	virtual CSERROR SetLabel(const char *label) =0;

	virtual int GetKeyLength() const =0;
	virtual const char *GetKeyType() const =0;

	virtual CSERROR IsValid() const =0;
};



class CSO_IMPORT CCryptoSealDocumentUser
{
protected: // don't mess around with these
	CCryptoSealDocumentUser();
	explicit CCryptoSealDocumentUser(const CCryptoSealDocumentUser &);
	const CCryptoSealDocumentUser &operator=(const CCryptoSealDocumentUser &);
	virtual ~CCryptoSealDocumentUser();

public:
	virtual CSERROR GetLastError() const =0;

	virtual const CCryptoSealCertificate *GetCertificate() const =0;

	virtual CSERROR SetSignature(const char *signature, int signatureLength) =0;
	virtual const char *GetSignature(int *signatureLength=0) const =0;

	virtual CSERROR SetSignerInfo(const char *signerInfo, int signerInfoLength) =0;
	virtual char *GetSignerInfo(int *signerInfoLength=NULL) =0;
	virtual CSERROR SetSignerInfo(const char *filename) =0;
	virtual CSERROR GetSignerInfo(const char *filename) =0;

	virtual CSERROR IsValidSignature(bool checkCertificate=true) const =0;
};



class CSO_IMPORT CCryptoSealDocument
{
protected: // don't mess around with these
	CCryptoSealDocument();
	explicit CCryptoSealDocument(const CCryptoSealDocument &);
	const CCryptoSealDocument &operator=(const CCryptoSealDocument &);
	virtual ~CCryptoSealDocument();

public:
	virtual CSERROR GetLastError() const =0;
	virtual void Clear() =0;

	enum ENCRYPTIONTYPE { EC_NONE=0, EC_DES, EC_TRIPLEDES, EC_IDEA, EC_MAX };
	ENCRYPTIONTYPE EncryptionType;
	bool DoDecrypt;

	bool AddCertificates;

	virtual int AddUser(const CCryptoSealCertificate*) =0; // returns index or -1
	virtual int AddUser(const char *signerInfo, int signerInfoLength) =0;
	virtual int AddUser(const char *signerInfoFilename) =0;
	virtual CCryptoSealDocumentUser *GetUser(int index) =0;
	virtual CCryptoSealDocumentUser *GetUser(const CCryptoSealCertificate*) =0;
	virtual int GetUserCount() const =0;
	virtual CSERROR SetUsers(CCryptoSealCertificate **certificates, int certificateCount) =0;
	virtual bool RemoveUser(int index) =0;
	virtual bool RemoveUser(const CCryptoSealCertificate*) =0;
	virtual void RemoveAllUsers() =0;

	virtual CSERROR SetContents(const char *contents, int contentsLength) =0;
	virtual CSERROR SetContents(const char *filename) =0;
	virtual CSERROR GetContents(const char *&contents, int &contentsLength) const =0;
	virtual CSERROR GetContents(const char *filename) const =0;
	virtual bool HasContents() =0;

	virtual CSERROR SetDocument(const char *document, int documentLength) =0;
	virtual CSERROR SetDocument(const char *filename) =0;
	virtual CSERROR GetDocument(const char *&document, int &documentLength) const =0;
	virtual CSERROR GetDocument(const char *filename) const =0;

	virtual CSERROR Sign(bool add, const CCryptoSealCertificate *) =0;
	virtual int SignerCount() const =0;
	virtual CSERROR DeleteSignature(const CCryptoSealCertificate *) =0;
};



class CSO_IMPORT CCryptoSealInterface
{
protected: // don't mess around with these
	CCryptoSealInterface();
	virtual ~CCryptoSealInterface();
	explicit CCryptoSealInterface(const CCryptoSealInterface &);
	const CCryptoSealInterface &operator=(const CCryptoSealInterface &);

public:
	static CCryptoSealInterface *Initialize();

	virtual CSERROR Open(const char *pin) =0;
	virtual CSERROR Close() =0;

	virtual CSERROR GetLastError() const =0;

	// Certificates
	virtual CCryptoSealCertificate *GetOwnCertificate(int index) const =0;
	virtual CCryptoSealCertificate *GetFirstCertificate() =0;
	virtual CCryptoSealCertificate *GetNextCertificate() =0;

	virtual CSERROR ExportCertificates(const char *filename, const CCryptoSealCertificate *const certlist[]) const =0;
	virtual CSERROR ImportCertificates(const char *filename) =0;
	virtual const CCryptoSealCertificate *GetImportedCertificate(int index) const =0;

	virtual CSERROR Add(const CCryptoSealCertificate*) =0; // to DB
	virtual CSERROR Remove(const CCryptoSealCertificate*) =0; // from DB
	virtual bool Find(const CCryptoSealCertificate*) const =0; // in DB
	virtual bool FindAll(const CCryptoSealCertificate*) const =0; // anywhere

	// Documents
	virtual CCryptoSealDocument *GetNewDocument() =0;
	virtual bool Find(const CCryptoSealDocument*) const =0;
	virtual CSERROR Remove(const CCryptoSealDocument*) =0;

	virtual void Delete(void*) =0;
};



extern CSO_IMPORT CCryptoSealInterface *CryptoSealInterface;



#endif
