// Zwei EditControls für ein Koordinatenpaar ----------------------------------
// File: DBLCOORD.HXX

#if !defined(_DBLCOORD_HXX)
#define _DBLCOORD_HXX

#include <numedit.hxx>
#include <dblnumed.hxx>

#include <dllbind.hxx>
#include <ctf.hxx>

class _TRIAS03_ENTRY CCoordPairEdit {
private:
	class _TRIAS03_ENTRY CCoordEdit : public DoubleNumEdit {
	private:
		CCoordPairEdit *m_pCPE;

	protected:
		void FocusChange (FocusChangeEvt);

	public:
			CCoordEdit (pDialogWindow, ResID, CCoordPairEdit *pCPE);
			~CCoordEdit (void);
	};

	CoordTrans &m_rCTF;	// aktuelle Koordinatentransformation
	CCoordEdit m_EditX;
	CCoordEdit m_EditY;

	double m_dX, m_dY;	// derzeit eingestellte Werte

protected:
virtual	bool Validate (void);

public:
		CCoordPairEdit (pDialogWindow pW, CoordTrans &rCTF, 
				ResID resX, ResID resY);
		~CCoordPairEdit (void);

	bool GetValues (double &rX, double &rY, bool fCorrect = false);
	bool SetValues (double dX, double dY);

friend CCoordEdit;
};

#endif // _DBLCOORD_HXX
