// Sammeln von ProtokollInformationen zur Datenbasis --------------------------
// File PROTOCOL.HXX

#if !defined(_PROTOCOL_HXX)
#define _PROTOCOL_HXX

class CProtocol {
private:
	string m_strOut;

public:
		CProtocol (void) {}
		~CProtocol (void) {}

	void Out (const char *pOut) { m_strOut += pOut; }
	const char *FResult (void) { return m_strOut.c_str(); }
};

#endif // _PROTOCOL_HXX

