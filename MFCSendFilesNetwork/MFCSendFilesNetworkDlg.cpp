// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// MFCSendFilesNetworkDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCSendFilesNetwork.h"
#include "MFCSendFilesNetworkDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <vector>


//====================================================
// Описание работы классов и методов исходника на:
// https://www.interestprograms.ru
// Исходные коды программ и игр
//====================================================


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMFCSendFilesNetworkDlg



CMFCSendFilesNetworkDlg::CMFCSendFilesNetworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSENDFILESNETWORK_DIALOG, pParent)
	, m_BufferInfoOk(FALSE)
	, m_ResetSizeRcvBuffer(TRUE)
	, m_ResetSizeSndBuffer(TRUE)
	, m_CounterRecv(0)
	, m_InitRcvBufferSize(65536)
	, m_InitSndBufferSize(65536)
	, m_pReceiveBuffer(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSendFilesNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PORT, m_wndPort);
	DDX_Control(pDX, IDC_EDIT_IP, m_wndIP);
	DDX_Control(pDX, IDC_RADIO_SERVER, m_wndServer);
	DDX_Control(pDX, IDC_RADIO_CLIENT, m_wndClient);
	DDX_Control(pDX, IDC_BUTTON_STOPWORK, m_wndStop);

	DDX_Control(pDX, IDC_LIST_SERVICEMESSAGES, m_wndServiceMessages);

	DDX_Control(pDX, IDC_STATIC_SENDFILENAME, m_wndSendFileName);
	DDX_Control(pDX, IDC_STATIC_RCVFILENAME, m_wndRcvFileName);

	DDX_Control(pDX, IDC_STATIC_RESULTSENDBYTES, m_wndResultSend);
	DDX_Control(pDX, IDC_STATIC_RCVRESULTBYTES, m_wndRcvResultBytes);

	DDX_Control(pDX, IDC_STATIC_SENDFILESIZE, m_wndSendFileSize);
	DDX_Control(pDX, IDC_STATIC_RCVFILEBYTES, m_wndRcvFileSize);

	DDX_Control(pDX, IDC_EDIT_SIZERCVBUFFER, m_wndSizeRcvBuffer);
	DDX_Control(pDX, IDC_EDIT_SIZESNDBUFFER, m_wndSizeSndBuffer);

	DDX_Check(pDX, IDC_CHECK_DEFAULTSIZERCVBUFFER, m_ResetSizeRcvBuffer);
	DDX_Control(pDX, IDC_EDIT_SIZERCVBUFFERFACT, m_wndSizeRcvBufferFact);

	DDX_Check(pDX, IDC_CHECK_DEFAULTSIZESNDBUFFER, m_ResetSizeSndBuffer);
	DDX_Control(pDX, IDC_EDIT_SIZESNDBUFFERFACT, m_wndSizeSndBufferFact);
}

BEGIN_MESSAGE_MAP(CMFCSendFilesNetworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDFILE, &CMFCSendFilesNetworkDlg::OnBnClickedButtonAddfile)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, &CMFCSendFilesNetworkDlg::OnBnClickedButtonSendfile)
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CMFCSendFilesNetworkDlg::OnBnClickedRadioServer)
	ON_BN_CLICKED(IDC_RADIO_CLIENT, &CMFCSendFilesNetworkDlg::OnBnClickedRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_STOPWORK, &CMFCSendFilesNetworkDlg::OnBnClickedButtonStopwork)
	ON_BN_CLICKED(IDC_CHECK_DEFAULTSIZERCVBUFFER, &CMFCSendFilesNetworkDlg::OnBnClickedCheckDefaultsizercvbuffer)
	ON_BN_CLICKED(IDC_CHECK_DEFAULTSIZESNDBUFFER, &CMFCSendFilesNetworkDlg::OnBnClickedCheckDefaultsizesndbuffer)
	ON_BN_CLICKED(IDC_BUTTON_SETNEWRCVBUFFER, &CMFCSendFilesNetworkDlg::OnBnClickedButtonSetnewrcvbuffer)
	ON_BN_CLICKED(IDC_BUTTON_SETNEWSENDBUFFER, &CMFCSendFilesNetworkDlg::OnBnClickedButtonSetnewsendbuffer)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCSendFilesNetworkDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CMFCSendFilesNetworkDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCSendFilesNetworkDlg

BOOL CMFCSendFilesNetworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	InitProgram();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCSendFilesNetworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCSendFilesNetworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCSendFilesNetworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/// <summary>
/// Выбор файла
/// </summary>
void CMFCSendFilesNetworkDlg::OnBnClickedButtonAddfile()
{
	CFileDialog fd(true);

	if(fd.DoModal() == IDOK)
	{

		CFile* pFile = new CFile(fd.GetPathName(), CFile::modeRead);
		ULONGLONG lengthFile = pFile->GetLength();
		pFile->Close();
		delete pFile;

		m_wndSendFileSize.SetWindowText(IntToStr(lengthFile));

		// Запоминаем путь выбранного файла.
		m_wndSendFileName.m_FilePath = fd.GetPathName();

		// Для пользователей выводим имя файла с расширением.
		m_wndSendFileName.SetWindowText(fd.GetFileName());

		// Обновляем данные в окне связанных с переменными.
		UpdateData(FALSE);
	}
}


/// <summary>
/// Отправка файла
/// </summary>
void CMFCSendFilesNetworkDlg::OnBnClickedButtonSendfile()
{
	SendFile(m_wndSendFileName.m_FilePath);
}


void CMFCSendFilesNetworkDlg::OnBnClickedRadioServer()
{
	CString strPort;
	m_wndPort.GetWindowText(strPort);


	if (m_AcceptSocket.Create(StrToInt(strPort)) == FALSE)
	{
		AfxMessageBox(L"Ошибка создания прослушивающего сокета!");
	}
	else
	{
		if (m_AcceptSocket.Listen() == FALSE)
		{
			AfxMessageBox(L"Ошибка включения прослушивания!");
		}
		else
		{
			SelectMode(CModeWork::mwServer);

			SetWindowText(L"Сервер ждет подключения!");
		}
	}
}


void CMFCSendFilesNetworkDlg::OnBnClickedRadioClient()
{
	if (m_Socket.Create() == FALSE)
	{
		AfxMessageBox(L"Ошибка создания сокета!");
	}
	else
	{
		CString strAddress;
		m_wndIP.GetWindowText(strAddress);

		CString strPort;
		m_wndPort.GetWindowText(strPort);

		if (m_Socket.Connect(strAddress, StrToInt(strPort)) == FALSE)
		{
			// В ассинхронном режиме код этой ошибки
			// считается как ожидание события подключения,
			// т.е. практически успешный возврат.
			if (GetLastError() == WSAEWOULDBLOCK)
			{
				SetWindowText(L"Ожидание ответа от сервера!");
			}
			else
			{
				// Если какая-либо ошибка возникла,
				// приводим приложение в первоначальное состояние,
				// готовое к следующей попытке соединения.
				StopWork();
			}
		}
	}

	SelectMode(CModeWork::mwClient);
}


void CMFCSendFilesNetworkDlg::SelectMode(CModeWork mode)
{
	switch (mode)
	{
	case CModeWork::mwReset:
		m_wndServer.SetCheck(BST_UNCHECKED);
		m_wndServer.EnableWindow(TRUE);

		m_wndClient.SetCheck(BST_UNCHECKED);
		m_wndClient.EnableWindow(TRUE);

		m_wndStop.EnableWindow(FALSE);
		m_wndIP.EnableWindow(TRUE);
		m_wndPort.EnableWindow(TRUE);
		break;
	case CModeWork::mwServer:
		m_wndServer.SetCheck(BST_CHECKED);
		m_wndClient.EnableWindow(FALSE);

		m_wndStop.EnableWindow(TRUE);
		m_wndIP.EnableWindow(FALSE);
		m_wndPort.EnableWindow(FALSE);
		break;
	case CModeWork::mwClient:
		m_wndClient.SetCheck(BST_CHECKED);
		m_wndServer.EnableWindow(FALSE);

		m_wndStop.EnableWindow(TRUE);
		m_wndIP.EnableWindow(FALSE);
		m_wndPort.EnableWindow(FALSE);
		break;
	default:
		break;
	}
}

void CMFCSendFilesNetworkDlg::StopWork()
{
	m_AcceptSocket.Close();
	m_Socket.Close();

	SetWindowText(L"Нет сети!");

	SelectMode(CModeWork::mwReset);
}


void CMFCSendFilesNetworkDlg::OnBnClickedButtonStopwork()
{
	StopWork();
}


void CMFCSendFilesNetworkDlg::ShowServiceMessage(CString msg)
{
	int numMsg = m_wndServiceMessages.GetCount() + 1;

	m_wndServiceMessages.InsertString(0, IntToStr(numMsg) + "." + msg);
}


void CMFCSendFilesNetworkDlg::InitProgram()
{
	m_wndPort.SetWindowText(IntToStr(g_PortInit));
	m_wndIP.SetWindowText(g_IPInit);

	m_wndSendFileName.SetWindowTextW(L"");
	m_wndSendFileSize.SetWindowTextW(L"");

	m_wndRcvFileName.SetWindowTextW(L"");
	m_wndRcvFileSize.SetWindowTextW(L"");

	SetWindowText(L"Нет сети!");

	m_wndSizeRcvBuffer.SetWindowTextW(L"8192");
	m_wndSizeSndBuffer.SetWindowTextW(L"8192");
}


void CMFCSendFilesNetworkDlg::OnAccept()
{
	if (m_AcceptSocket.Accept(m_Socket) == FALSE)
	{
		AfxMessageBox(L"Ошибка акцепта рабочего сокета!");
	}
	else
	{
		SetWindowText(L"Сеть работает!");

		m_InitRcvBufferSize = GetSizeBuffer(SO_RCVBUF);
		m_wndSizeRcvBufferFact.SetWindowText(IntToStr(m_InitRcvBufferSize));

		m_InitSndBufferSize = GetSizeBuffer(SO_SNDBUF);
		m_wndSizeSndBufferFact.SetWindowText(IntToStr(m_InitSndBufferSize));
	}
}


void CMFCSendFilesNetworkDlg::OnConnect(BOOL error)
{
	if (error == TRUE)
	{
		AfxMessageBox(L"Попытка подключения была отвергнута!\nВозможно сервер еще не создан!");
		StopWork();
	}
	else
	{
		SetWindowText(L"Сеть работает!");

		m_InitRcvBufferSize = GetSizeBuffer(SO_RCVBUF);
		m_wndSizeRcvBufferFact.SetWindowText(IntToStr(m_InitRcvBufferSize));

		m_InitSndBufferSize = GetSizeBuffer(SO_SNDBUF);
		m_wndSizeSndBufferFact.SetWindowText(IntToStr(m_InitSndBufferSize));
	}
}


void CMFCSendFilesNetworkDlg::OnClose()
{
	StopWork();
	
	SetWindowText(L"Нет сети!");
}

void CMFCSendFilesNetworkDlg::ProccesMessages()
{
	// Для тестирования
	//return;

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return;
		}
	}
}


void CMFCSendFilesNetworkDlg::SendBuffer(BYTE* pBuffer, DWORD size)
{

	// TODO: запрашивается один раз перед отправкой. Надо выяснить может такой запрос надо делать перед отправкой каждого сегмента.
	// Размер буфера отправки. 
	// Для наибольшего КПД, размер пакета должен быть не меньше размера буфера отправки.
	// Для упрощения получения размера буфера отправки возьмём только сокет первого клиента.
	int sizeBuffer = 0;

	// Размер переменной sizeBuffer.
	int len = 4;

	// Реально отправленное количество
	int actualSendBytes = 0;

	// Отправка данных пакетами.
	while (actualSendBytes < size)
	{

		if (m_Socket.GetSockOpt(SO_SNDBUF, &sizeBuffer, &len) == FALSE)
		{
			ShowServiceMessage(L"Клиент: Ошибка размера буфера отправки!");
			return;
		}


		// Если размер буфера позволит, отправим всё сразу.
		int sizeCompute = (size - actualSendBytes);

		// Но если размер отправляемых данных больше буфера,
		// размер пакета устанавливаем равным буферу. 
		// Если меньше остатки меньше размера буфера, 
		// размер пакета устанавливаем равным отправляемому остатку.
		if (sizeCompute > sizeBuffer)
		{
			sizeCompute = sizeBuffer;
		}


		if (m_IsCanSend == TRUE)
		{
			ShowServiceMessage(L"Размер буфера отправки - " + IntToStr(sizeBuffer));


			// Подсчитываем реально отправляемые данные.
			int sent = m_Socket.Send(pBuffer + actualSendBytes, sizeCompute);

			
			// Ошибка WSAEWOULDBLOCK блокировки буфера отправки.
			if (sent == SOCKET_ERROR)
			{
				m_IsCanSend = FALSE;

				DWORD error = GetLastError();

				if (error == WSAEWOULDBLOCK)
				{
					// Необходимо подождать пока сработает разрешение OnSend сокета.
					ShowServiceMessage(L"Буфер отправки временно недоступен!");
				}
				else
					ShowServiceMessage(L"Ошибка при отправке - " + IntToStr(error));
				
			}
			else
			{
				// Подсчёт общего количества отправленных байтов.
				actualSendBytes += sent;
			}

			ShowServiceMessage(L"Отправлено  факт - " + IntToStr(sent));
		}
		else
			ShowServiceMessage(L"Ожидание события OnSend()!");


		ProccesMessages();


		m_wndResultSend.SetWindowText(IntToStr(actualSendBytes));
	}

	// Сброс данных для отправки следующей партии.
	if (actualSendBytes == size)
	{
		// TODO: Код обработки успешной отправки.
	}

}


void CMFCSendFilesNetworkDlg::SendFile(CString pathFile)
{
	// Получаем контент прикрепленного к отправке файла
	CFile* pFile = new CFile(pathFile, CFile::modeRead);

	UINT fileLength = (UINT)pFile->GetLength();

	// Создаём буфер равный размеру файла.
	BYTE* pFileContent = new BYTE[fileLength];

	// Заполняем буфер нулями (очистка буфера от случайного мусора).
	ZeroMemory(pFileContent, sizeof(BYTE) * fileLength);

	// Получили содержимое выбранного для отправки файла
	int num = pFile->Read(pFileContent, fileLength);

	pFile->Close();

	// Очистка памяти.
	delete pFile;



	// --- Непосредственно отправка файла ---

	// В первую очередь отправляется информация о файле в
	// константном по размеру буфере.
	CString fileName(PathFindFileName(pathFile));

	BUFFERINFO bufferInfo;

	wcscpy_s(bufferInfo.FileName, fileName);

	// Информация о размере файла записывается в информационный буфер.
	bufferInfo.FileLength = fileLength;

	SendBuffer((BYTE*)&bufferInfo, sizeof(BUFFERINFO));

	SendBuffer(pFileContent, fileLength);

	// Буфер файла больше не нужен. Освобождаем память.
	delete[] pFileContent;

	// Правило хорошего тона.
	pFileContent = NULL;
}


void CMFCSendFilesNetworkDlg::OnReceive()
{
	ReceiveData();
}



BOOL CMFCSendFilesNetworkDlg::ReceiveData()
{

	if (m_BufferInfoOk == false)
	{
		if (ReceiveBufferInfo() == 0) m_BufferInfoOk = TRUE;
	}
	else
	{
		// Общий размер принимаемых данных
		UINT totalSize = sizeof(BUFFERINFO) + m_RcvBufferInfo.FileLength;

		DWORD canReadBytes = 0;
		m_Socket.IOCtl(FIONREAD, &canReadBytes);
		ShowServiceMessage(L"Размер данных в буфере приёма - " + IntToStr(canReadBytes));

		int sizeBuffer = 0;

		// Размер переменной sizeBuffer.
		int len = 4;

		if (m_Socket.GetSockOpt(SO_RCVBUF, &sizeBuffer, &len) == TRUE)
		{
			ShowServiceMessage(L"Размер буфера приёма - " + IntToStr(sizeBuffer));


			// Если остаток принимаемых данных меньше возможностей приёма,
			// размер для принимаемых данных установим равным размеру остатка.
			if (totalSize - m_CounterRecv < canReadBytes)
			{
				canReadBytes = totalSize - m_CounterRecv;
			}

			// Подсчёт реально принятых данных.
			int check = m_Socket.Receive(m_pReceiveBuffer + m_CounterRecv, canReadBytes);

			if (check != SOCKET_ERROR)
			{
				m_CounterRecv += check;

				m_wndRcvResultBytes.SetWindowText(IntToStr(m_CounterRecv));
			}
			else
			{
				DWORD error = GetLastError();

				if (error == WSAEWOULDBLOCK)
				{
					ShowServiceMessage(L"Блокировка приёма!");
				}
				else
				{

					ShowServiceMessage(L"Неизвестная ошибка приёма - " + IntToStr(error) + L". Очистка памяти!");

					// В случае ошибки работы сокета необходимо освободить используемые ресурсы.
					// Освобождаем память занятую главным буфером.
					delete[] m_pReceiveBuffer;
					m_pReceiveBuffer = NULL;

					AfxMessageBox(L"Принято с ошибками: " + IntToStr(m_CounterRecv) + L"; SOCKET_ERROR-" + IntToStr(error));

					// Сброс глобальных переменных-членов для следующего сеанса по сети.
					m_CounterRecv = 0;
					m_BufferInfoOk = FALSE;

					return FALSE;
				}
			}
		}
		else
		{
			ShowServiceMessage(L"Ошибка буфера приёма! -"  + IntToStr(GetLastError()));
		}

		if (totalSize > 0 && m_CounterRecv == totalSize)
		{

			m_wndRcvResultBytes.SetWindowText(IntToStr(m_CounterRecv - sizeof(BUFFERINFO)));

			SaveFile(m_RcvBufferInfo.FileName, m_pReceiveBuffer + sizeof(BUFFERINFO), m_RcvBufferInfo.FileLength);

			// Освобождаем память занятую главным буфером.
			delete[] m_pReceiveBuffer;
			m_pReceiveBuffer = NULL;


			// Сброс глобальных переменных-членов для следующего сеанса по сети.
			m_CounterRecv = 0;
			m_BufferInfoOk = FALSE;

			return TRUE;
		}
	}

	return FALSE;
}



int CMFCSendFilesNetworkDlg::ReceiveBufferInfo()
{
	int sizeBufferInfo = sizeof(BUFFERINFO);

	DWORD canReadBytes = 0;
	if (m_Socket.IOCtl(FIONREAD, &canReadBytes) == FALSE)
	{

	}
	else
	{
		ShowServiceMessage(L"Получаем буфер информации - " + IntToStr(canReadBytes));


		BYTE* pBuffer = new BYTE[canReadBytes];
		ZeroMemory(pBuffer, canReadBytes);

		UINT actualBytes = m_Socket.Receive(pBuffer, canReadBytes);

		static std::vector<BUFF> vec;

		BUFF buff;
		buff.size = actualBytes;
		buff.pArray = new BYTE[actualBytes];
		ZeroMemory(buff.pArray, actualBytes);
		memcpy_s(buff.pArray, actualBytes, pBuffer, actualBytes);
		vec.push_back(buff);

		delete[] pBuffer;
		pBuffer = NULL;

		DWORD check = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			check += vec[i].size;
		}

		if (check >= sizeBufferInfo)
		{
			m_CounterRecv = check;

			BYTE* pVecBuffer = new BYTE[check];
			int step = 0;
			for (int i = 0; i < vec.size(); i++)
			{
				memcpy_s(pVecBuffer + step, vec[i].size, vec[i].pArray, vec[i].size);

				step += vec[i].size;
			}

			// Расшифровываем информацию.
			memcpy_s(&m_RcvBufferInfo, sizeof(BUFFERINFO), pVecBuffer, sizeof(BUFFERINFO));

			m_wndRcvFileName.SetWindowText(m_RcvBufferInfo.FileName);
			m_wndRcvFileSize.SetWindowText(IntToStr(m_RcvBufferInfo.FileLength));

			int totalSize = sizeof(BUFFERINFO) + m_RcvBufferInfo.FileLength;

			m_pReceiveBuffer = new BYTE[totalSize];
			ZeroMemory(m_pReceiveBuffer, totalSize);

			memcpy_s(m_pReceiveBuffer, check, pVecBuffer, check);

			delete[] pVecBuffer;
			pVecBuffer = NULL;


			for (int i = 0; i < vec.size(); i++)
			{
				delete[] vec[i].pArray;
				vec[i].pArray = NULL;
			}
			vec.clear();

			ShowServiceMessage(L"Буфер информации принят!");

			return 0;
		}

	}

	return -1;
}


void CMFCSendFilesNetworkDlg::SaveFile(CString fileName, BYTE* pContent, DWORD size)
{
	// Копирование принятого файла в подпапку с названием режима работы приложения
	// в каталоге приложения.

	CString nameDirectory("server");
	if(m_wndClient.GetCheck() == BST_CHECKED) nameDirectory = "client";

	CreateDirectory(nameDirectory, NULL);

	CString directory;
	directory = nameDirectory;
	directory.Append(L"\\");
	directory.Append(fileName);

	CFile* pFile = new CFile(directory, CFile::modeCreate | CFile::modeWrite);

	pFile->Write(m_pReceiveBuffer + sizeof(BUFFERINFO), size);
	pFile->Close();

	delete pFile;
	pFile = NULL;
}


BOOL CMFCSendFilesNetworkDlg::SetSizeRcvBuffer(BOOL reset)
{
	CString s;
	m_wndSizeRcvBuffer.GetWindowText(s);

	int rcvb = StrToInt(s);

	if (reset == TRUE) rcvb = m_InitRcvBufferSize;

	if (m_Socket.SetSockOpt(SO_RCVBUF, &rcvb, sizeof(int)) == TRUE)
	{
		int sizeBuffer = GetSizeBuffer(SO_RCVBUF);

		m_wndSizeRcvBufferFact.SetWindowText(IntToStr(sizeBuffer));

		return TRUE;
	}

	AfxMessageBox(L"Ошибка установки размера буфера - " + IntToStr(GetLastError()));

	return FALSE;
}


BOOL CMFCSendFilesNetworkDlg::SetSizeSndBuffer(BOOL reset)
{
	CString s;
	m_wndSizeSndBuffer.GetWindowText(s);
	int sndb = StrToInt(s);

	if (reset == TRUE) sndb = m_InitSndBufferSize;

	if(m_Socket.SetSockOpt(SO_SNDBUF, &sndb, sizeof(int)) == TRUE)
	{
		int sizeBuffer = GetSizeBuffer(SO_SNDBUF);
		m_wndSizeSndBufferFact.SetWindowText(IntToStr(sizeBuffer));

		return TRUE;
	}


	AfxMessageBox(L"Ошибка установки размера буфера - " + IntToStr(GetLastError()));

	return FALSE;
}


void CMFCSendFilesNetworkDlg::OnBnClickedCheckDefaultsizercvbuffer()
{
	if (SetSizeRcvBuffer(!m_ResetSizeRcvBuffer) == TRUE)
	{
		UpdateData(TRUE);

		m_wndSizeRcvBuffer.EnableWindow(!m_ResetSizeRcvBuffer);
	}
}

// Сброс на настройки по умолчанию.
void CMFCSendFilesNetworkDlg::OnBnClickedCheckDefaultsizesndbuffer()
{
	if (SetSizeSndBuffer(!m_ResetSizeSndBuffer) == TRUE)
	{
		UpdateData(TRUE);

		m_wndSizeSndBuffer.EnableWindow(!m_ResetSizeSndBuffer);
	}
	
}


void CMFCSendFilesNetworkDlg::OnBnClickedButtonSetnewrcvbuffer()
{
	SetSizeRcvBuffer();
}


void CMFCSendFilesNetworkDlg::OnBnClickedButtonSetnewsendbuffer()
{
	SetSizeSndBuffer();
}



int CMFCSendFilesNetworkDlg::GetSizeBuffer(int typeByffer)
{
	int sizebuff = 0;
	int len = sizeof(int);
	if (m_Socket.GetSockOpt(typeByffer, &sizebuff, &len) == FALSE) return -1;

	return sizebuff;
}


void CMFCSendFilesNetworkDlg::OnBnClickedButton1()
{
	m_wndServiceMessages.ResetContent();
}


void CMFCSendFilesNetworkDlg::OnNMClickSyslink1(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	PNMLINK pNMLink = (PNMLINK)pNMHDR;
	LITEM   item = pNMLink->item;

	ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOWNORMAL);
}
