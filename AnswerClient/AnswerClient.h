// AnswerClient.h : main header file for the ANSWERCLIENT application
//

#if !defined(AFX_ANSWERCLIENT_H__C80E7D7A_8FA3_46D7_99FF_021F2607CAD8__INCLUDED_)
#define AFX_ANSWERCLIENT_H__C80E7D7A_8FA3_46D7_99FF_021F2607CAD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <winsock2.h>
/////////////////////////////////////////////////////////////////////////////
// CAnswerClientApp:
// See AnswerClient.cpp for the implementation of this class
//

class CAnswerClientApp : public CWinApp
{
public:
	CAnswerClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnswerClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnswerClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANSWERCLIENT_H__C80E7D7A_8FA3_46D7_99FF_021F2607CAD8__INCLUDED_)
