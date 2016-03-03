// CWindowDCTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CWindowDCTest.h"
#include "CWindowDCTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
BOOL connected = FALSE;
#define HOTKEY_F4 1004
#define HOTKEY_F3 1003
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCWindowDCTestDlg dialog

CCWindowDCTestDlg::CCWindowDCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCWindowDCTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCWindowDCTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCWindowDCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCWindowDCTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCWindowDCTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCWindowDCTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SOCK, OnSock)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCWindowDCTestDlg message handlers
void CCWindowDCTestDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(lParam))
	{
	case FD_READ:
		WSABUF wsabuf;
		wsabuf.buf = new char[200];
		wsabuf.len = 200;
		DWORD dwRead;
		DWORD dwFlag = 0;
		SOCKADDR_IN addrFrom;
		int len = sizeof(SOCKADDR);
		CString str;
		CString strTemp;
		if(SOCKET_ERROR == WSARecvFrom(m_socket, &wsabuf, 1, &dwRead, &dwFlag,
			(SOCKADDR *)&addrFrom, &len, NULL, NULL))
		{
			MessageBox("Receive Failed");
			delete [] wsabuf.buf;
			return;
		}
		CString strRecv;
		strRecv.Format("%s", wsabuf.buf);
		//MessageBox(strRecv);
		if(connected)
		{
			CWindowDC dc(NULL);
			CFont myFont;
			myFont.CreateFont(
				120, 40, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
				"Arial");
			CFont *oldFont = dc.SelectObject(&myFont);
			dc.SetTextColor(RGB(255, 0, 0));
			dc.SetBkMode(OPAQUE);
			dc.SetBkColor(RGB(0, 255, 0));
		//	CString str( "ÆÁÄ»ÎÄ×Ö");
			dc.TextOut(200, 200, strRecv);
			dc.SelectObject(oldFont);
			connected = FALSE;
		}
		delete [] wsabuf.buf;
		break;
	}
}

BOOL CCWindowDCTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitSocket();
	RegisterHotKey(this->m_hWnd, HOTKEY_F4, 0, VK_F4);
	RegisterHotKey(this->m_hWnd, HOTKEY_F3, 0, VK_F3);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCWindowDCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCWindowDCTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCWindowDCTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//DEL void CCWindowDCTestDlg::OnBtnPrint() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	CWindowDC dc(NULL);
//DEL 	CFont myFont;
//DEL 	myFont.CreateFont(
//DEL 		120, 40, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,OUT_DEFAULT_PRECIS,
//DEL 		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
//DEL 		"Arial");
//DEL 	CFont *oldFont = dc.SelectObject(&myFont);
//DEL 	dc.SetTextColor(RGB(255, 0, 0));
//DEL 	dc.SetBkMode(OPAQUE);
//DEL 	dc.SetBkColor(RGB(0, 255, 0));
//DEL 	CString str( "1ºÅ¶ÓÎé");
//DEL 	dc.TextOut(200, 200, str);
//DEL 	dc.SelectObject(oldFont);
//DEL }


BOOL CCWindowDCTestDlg::InitSocket()
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
	if(INVALID_SOCKET == m_socket)
	{
		MessageBox("Create Socket Failed");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	if(SOCKET_ERROR == bind(m_socket, (SOCKADDR *)&addrSock, sizeof(SOCKADDR)))
	{
		int res = WSAGetLastError();
		CString strErr;
		strErr.Format("Bind Error %d", res);
		MessageBox(strErr);
		return FALSE;
	}
	if(SOCKET_ERROR == WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ))
	{
		MessageBox("Regester Net Event Error");
		return FALSE;
	}
	return TRUE;
}

BOOL CCWindowDCTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_HOTKEY:
		switch(pMsg->wParam)
		{
		case HOTKEY_F4:
			connected = TRUE;
			break;
		case HOTKEY_F3:
			{
				CWindowDC dc(NULL);
				CFont myFont;
				myFont.CreateFont(
					120, 40, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					"Arial");
				CFont *oldFont = dc.SelectObject(&myFont);
				dc.SetTextColor(RGB(255, 0, 0));
				dc.SetBkMode(TRANSPARENT);
				dc.SetBkColor(RGB(0, 255, 0));
			//	CString str( "ÆÁÄ»ÎÄ×Ö");
				dc.TextOut(200, 200, "                     ");
				dc.SelectObject(oldFont);
			
			}
			break;
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
