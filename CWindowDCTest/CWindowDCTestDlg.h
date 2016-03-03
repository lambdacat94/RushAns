// CWindowDCTestDlg.h : header file
//

#if !defined(AFX_CWINDOWDCTESTDLG_H__4AC42339_F330_4C03_A563_C24947F3742F__INCLUDED_)
#define AFX_CWINDOWDCTESTDLG_H__4AC42339_F330_4C03_A563_C24947F3742F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCWindowDCTestDlg dialog
#define UM_SOCK WM_USER + 1
#include <winsock2.h>

class CCWindowDCTestDlg : public CDialog
{
// Construction
public:
	BOOL InitSocket();
	CCWindowDCTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCWindowDCTestDlg)
	enum { IDD = IDD_CWINDOWDCTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCWindowDCTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCWindowDCTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg void OnSock(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINDOWDCTESTDLG_H__4AC42339_F330_4C03_A563_C24947F3742F__INCLUDED_)
