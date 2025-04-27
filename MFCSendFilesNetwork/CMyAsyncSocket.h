// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once

#include <afxsock.h>


//====================================================
// Описание работы классов и методов исходника на:
// https://www.interestprograms.ru
// Исходные коды программ и игр
//====================================================

// Целевой объект команды CMyAsyncSocket

class CMyAsyncSocket : public CAsyncSocket
{
public:
	
	CWnd* m_pWnd;

	CMyAsyncSocket(CWnd* pWnd);
	virtual ~CMyAsyncSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);



	
};


