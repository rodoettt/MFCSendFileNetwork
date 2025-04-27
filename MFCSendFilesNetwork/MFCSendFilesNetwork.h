// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// MFCSendFilesNetwork.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCSendFilesNetworkApp:
// Сведения о реализации этого класса: MFCSendFilesNetwork.cpp
//

class CMFCSendFilesNetworkApp : public CWinApp
{
public:
	CMFCSendFilesNetworkApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCSendFilesNetworkApp theApp;
