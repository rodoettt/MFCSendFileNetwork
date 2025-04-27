// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// CMyAsyncSocket.cpp: файл реализации
//

#include "pch.h"
#include "MFCSendFilesNetwork.h"
#include "CMyAsyncSocket.h"
#include "MFCSendFilesNetworkDlg.h"


//====================================================
// Описание работы классов и методов исходника на:
// https://www.interestprograms.ru
// Исходные коды программ и игр
//====================================================


// CMyAsyncSocket


CMyAsyncSocket::CMyAsyncSocket(CWnd* pWnd):
	m_pWnd(NULL)
{
	m_pWnd = pWnd;
}


CMyAsyncSocket::~CMyAsyncSocket()
{
}


// функции-члены CMyAsyncSocket


void CMyAsyncSocket::OnAccept(int nErrorCode)
{
	((CMFCSendFilesNetworkDlg*)m_pWnd)->OnAccept();

	CAsyncSocket::OnAccept(nErrorCode);
}


void CMyAsyncSocket::OnClose(int nErrorCode)
{
	((CMFCSendFilesNetworkDlg*)m_pWnd)->OnClose();

	CAsyncSocket::OnClose(nErrorCode);
}


void CMyAsyncSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode != 0) ((CMFCSendFilesNetworkDlg*)m_pWnd)->OnConnect(TRUE);
	else ((CMFCSendFilesNetworkDlg*)m_pWnd)->OnConnect(FALSE);

	CAsyncSocket::OnConnect(nErrorCode);
}


void CMyAsyncSocket::OnReceive(int nErrorCode)
{
	((CMFCSendFilesNetworkDlg*)m_pWnd)->OnReceive();

	CAsyncSocket::OnReceive(nErrorCode);
}


void CMyAsyncSocket::OnSend(int nErrorCode)
{
	if (nErrorCode == 0) ((CMFCSendFilesNetworkDlg*)m_pWnd)->m_IsCanSend = TRUE;
	
	((CMFCSendFilesNetworkDlg*)m_pWnd)->ShowServiceMessage(L"Событие OnSend()!");

	CAsyncSocket::OnSend(nErrorCode);
}
