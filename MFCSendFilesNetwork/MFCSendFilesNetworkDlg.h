// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// MFCSendFilesNetworkDlg.h: файл заголовка
//

#pragma once
#include "CMyAsyncSocket.h"
#include "CMyStatic.h"


//====================================================
// Описание работы классов и методов исходника на:
// https://www.interestprograms.ru
// Исходные коды программ и игр
//====================================================




enum class CModeWork{mwReset,mwServer, mwClient};

const int g_PortInit = 30000;
const CString g_IPInit = L"127.0.0.1";


struct BUFF
{
	BUFF()
	{
		size = 0;
		pArray = NULL;
	}

	DWORD size;
	BYTE* pArray;
};


struct BUFFERINFO
{
	BUFFERINFO()
	{
		// Заполнение ну 
		//SecureZeroMemory(FileName, 512);
	}

	int FileLength = 0;
	TCHAR FileName[512];
};


// Диалоговое окно CMFCSendFilesNetworkDlg
class CMFCSendFilesNetworkDlg : public CDialogEx
{
// Создание
public:
	CMFCSendFilesNetworkDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSENDFILESNETWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddfile();
	afx_msg void OnBnClickedButtonSendfile();

	// ---------------------------------------

	CEdit m_wndPort;
	CEdit m_wndIP;
	CButton m_wndServer;
	CButton m_wndClient;
	afx_msg void OnBnClickedRadioServer();
	afx_msg void OnBnClickedRadioClient();
	void SelectMode(CModeWork mode);


	// Останавливает работу программы по сети.
	CButton m_wndStop;
	void StopWork();
	afx_msg void OnBnClickedButtonStopwork();


	// Сокеты
	// Сокет прослушивания клиентов
	CMyAsyncSocket m_AcceptSocket{ this };

	// Рабочий сокет, отправки и приёма сообщений.
	CMyAsyncSocket m_Socket{ this };



	void ShowServiceMessage(CString msg);
	CListBox m_wndServiceMessages;

	inline CString IntToStr(int number)
	{
		CString str;
		str.Format(L"%d", number);
		return str;
	}

	void InitProgram();
	void OnAccept();
	void OnConnect(BOOL error);
	void OnClose();

	void ProccesMessages();
	void SendBuffer(BYTE* pBuffer, DWORD size);
	void SendFile(CString pathFile);

	CMyStatic m_wndSendFileName;
	CStatic m_wndResultSend;
	CStatic m_wndSendFileSize;
	void OnReceive();

	BOOL ReceiveData();
	BOOL m_BufferInfoOk;
	DWORD m_CounterRecv;

	BYTE* m_pReceiveBuffer;

	CMyStatic m_wndRcvFileName;
	BUFFERINFO m_RcvBufferInfo;
	CStatic m_wndRcvFileSize;
	CStatic m_wndRcvResultBytes;
	void SaveFile(CString fileName, BYTE* pContent, DWORD size);
	CEdit m_wndSizeRcvBuffer;
	BOOL SetSizeRcvBuffer(BOOL reset=FALSE);
	
	afx_msg void OnBnClickedCheckDefaultsizercvbuffer();

	BOOL SetSizeSndBuffer(BOOL reset=FALSE);
	CEdit m_wndSizeSndBuffer;
	
	BOOL m_ResetSizeRcvBuffer;
	BOOL m_ResetSizeSndBuffer;


	afx_msg void OnBnClickedCheckDefaultsizesndbuffer();
	afx_msg void OnBnClickedButtonSetnewrcvbuffer();
	afx_msg void OnBnClickedButtonSetnewsendbuffer();

	CEdit m_wndSizeRcvBufferFact;
	CEdit m_wndSizeSndBufferFact;
	
	int ReceiveBufferInfo();
	int GetSizeBuffer(int typeByffer);
	int m_InitRcvBufferSize;
	int m_InitSndBufferSize;


	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMClickSyslink1(NMHDR* pNMHDR, LRESULT* pResult);

	BOOL m_IsCanSend{TRUE};
};
