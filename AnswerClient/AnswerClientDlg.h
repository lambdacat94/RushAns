// AnswerClientDlg.h : header file
//

#if !defined(AFX_ANSWERCLIENTDLG_H__CB13BE56_C604_4E73_A4A4_BD417BE0E894__INCLUDED_)
#define AFX_ANSWERCLIENTDLG_H__CB13BE56_C604_4E73_A4A4_BD417BE0E894__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define UM_SOCK WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CAnswerClientDlg dialog
#include <winsock2.h>
class CAnswerClientDlg : public CDialog
{
// Construction
public:
	BOOL InitSocket();

	CAnswerClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAnswerClientDlg)
	enum { IDD = IDD_ANSWERCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnswerClientDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnswerClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		SOCKET m_socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANSWERCLIENTDLG_H__CB13BE56_C604_4E73_A4A4_BD417BE0E894__INCLUDED_)
