// AnswerClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnswerClient.h"
#include "AnswerClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define HOTKEY_SPACE 1001
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
// CAnswerClientDlg dialog

CAnswerClientDlg::CAnswerClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnswerClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnswerClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnswerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnswerClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnswerClientDlg, CDialog)
	//{{AFX_MSG_MAP(CAnswerClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnswerClientDlg message handlers

BOOL CAnswerClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitSocket();
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAnswerClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAnswerClientDlg::OnPaint() 
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
HCURSOR CAnswerClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAnswerClientDlg::InitSocket()
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
		MessageBox("Bind Error");
		return FALSE;
	}
	if(SOCKET_ERROR == WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ))
	{
		MessageBox("Regester Net Event Error");
		return FALSE;
	}
	return TRUE;
}

//DEL void CAnswerClientDlg::OnBtnSend() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	DWORD dwIP;
//DEL 	CString strSend;
//DEL 	WSABUF wsabuf;
//DEL 	DWORD dwSend;
//DEL 	int len;
//DEL 	SOCKADDR_IN addrTo;
//DEL 
//DEL 	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
//DEL 	addrTo.sin_addr.S_un.S_addr = htonl(dwIP);
//DEL 	addrTo.sin_family = AF_INET;
//DEL 	addrTo.sin_port = htons(6000);
//DEL 	GetDlgItemText(IDC_EDIT_SEND, strSend);
//DEL 	len = strSend.GetLength();
//DEL 	wsabuf.buf = strSend.GetBuffer(len);
//DEL 	wsabuf.len = len + 1;
//DEL 
//DEL 	SetDlgItemText(IDC_EDIT_SEND, "");
//DEL 	if(SOCKET_ERROR == WSASendTo(m_socket, &wsabuf, 1, &dwSend, 0,
//DEL 		(SOCKADDR *)&addrTo, sizeof(SOCKADDR), NULL, NULL))
//DEL 	{
//DEL 		MessageBox("Send Data Failed");
//DEL 		return;
//DEL 	}
//DEL }

BOOL CAnswerClientDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_HOTKEY:
		switch(pMsg->wParam)
		{
		case HOTKEY_SPACE:
			{
				CFile getFile("client.ini", CFile::modeRead);
				CArchive getAr(&getFile, CArchive::load);

				DWORD dwGet;
				CString strGet;
				WSABUF wsabuf;
				DWORD dwSend;
				int len;
				SOCKADDR_IN addrTo;
				getAr>>dwGet>>strGet;
	//			((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
				addrTo.sin_addr.S_un.S_addr = htonl(dwGet);
				addrTo.sin_family = AF_INET;
				addrTo.sin_port = htons(6000);
	//			GetDlgItemText(IDC_EDIT_SEND, strSend);
				len = strGet.GetLength();
				wsabuf.buf = strGet.GetBuffer(len);
				wsabuf.len = len + 1;

				//SetDlgItemText(IDC_EDIT_SEND, "");
				if(SOCKET_ERROR == WSASendTo(m_socket, &wsabuf, 1, &dwSend, 0,
					(SOCKADDR *)&addrTo, sizeof(SOCKADDR), NULL, NULL))
				{
					MessageBox("Send Data Failed");
					return FALSE;
				}
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CAnswerClientDlg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	RegisterHotKey(this->m_hWnd, HOTKEY_SPACE, 0, VK_SPACE);
	CFile setFile("client.ini", CFile::modeCreate | CFile::modeWrite);
	CArchive setAr(&setFile, CArchive::store);
	DWORD dwIP;
	CString strSend;
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
	GetDlgItemText(IDC_EDIT_SEND, strSend);
	setAr<<dwIP<<strSend;
	ShowWindow(SW_HIDE);
}
