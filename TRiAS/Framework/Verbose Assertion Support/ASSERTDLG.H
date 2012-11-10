// AssertDlg.H

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#ifndef ASSERT_DIALOG_


#define ASSERT_DIALOG_


class DumpBuffer ;

class AssertDialog
  {
  public :
    enum Choice { abort, ignore, debug } ;
    AssertDialog( const DumpBuffer& buf ) ;
    Choice GetUserChoice() ;
  private :
    static BOOL CALLBACK AssertDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam ) ;
    static Choice userChoice ;
	static int iOrigHeight;
  } ;


#endif // #ifndef ASSERT_DIALOG_
