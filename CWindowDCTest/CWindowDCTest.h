// CWindowDCTest.h : main header file for the CWINDOWDCTEST application
//

#if !defined(AFX_CWINDOWDCTEST_H__86185285_E30A_46B5_9031_5E998948BBFE__INCLUDED_)
#define AFX_CWINDOWDCTEST_H__86185285_E30A_46B5_9031_5E998948BBFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCWindowDCTestApp:
// See CWindowDCTest.cpp for the implementation of this class
//

class CCWindowDCTestApp : public CWinApp
{
public:
	CCWindowDCTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCWindowDCTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCWindowDCTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINDOWDCTEST_H__86185285_E30A_46B5_9031_5E998948BBFE__INCLUDED_)
