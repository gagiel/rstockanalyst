#include "StdAfx.h"
#include "MainWindow.h"
#include "STKDRV.h"
#include <iostream>
using namespace std;

#define RSTOCK_ANALYST_MAINMSG (WM_USER+1)

CMainWindow::CMainWindow( QWidget* parent/*=0*/, Qt::WindowFlags flags/*=0 */ )
	: QMainWindow(parent,flags)
{

}

CMainWindow::~CMainWindow(void)
{

}

bool CMainWindow::setupStockDrv()
{
	if(CSTKDRV::Stock_Init(this->winId(),RSTOCK_ANALYST_MAINMSG,RCV_WORK_MEMSHARE)>0)
	{
		if(CSTKDRV::SetupReceiver(TRUE)>0)
			return true;
	}

	return false;
}

bool CMainWindow::winEvent( MSG* message, long* result )
{
	if(message->message == RSTOCK_ANALYST_MAINMSG)
	{
		*result = OnStockDrvMsg(message->wParam,message->lParam);
	}

	return QMainWindow::winEvent(message,result);
}

long CMainWindow::OnStockDrvMsg( WPARAM wParam,LPARAM lParam )
{
	RCV_DATA* pHeader;
	int i;

	pHeader = (RCV_DATA*)lParam;

	//  ���ڴ����ٶ�������������,��ý� pHeader->m_pData ָ������ݱ���,��������

	switch( wParam )
	{
	case RCV_REPORT:                        // �����������÷�ʽ,��Ʊ����
		cout<<"�ļ�����:"<<pHeader->m_wDataType<<endl;
		for(i=0; i<pHeader->m_nPacketNum; i++)
		{
			cout<<pHeader->m_pReport[i].m_szName<<endl;
//			RCV_REPORT_STRUCTEx pBuffer = pHeader->m_pReport[i];
//			cout<<pBuffer.m_szName<<endl;
		}
		break;

	case RCV_FILEDATA:                      // �����������÷�ʽ,�ļ�
		switch(pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:               // ����������
			break;

		case FILE_MINUTE_EX:                // ������������
			break;

		case FILE_BASE_EX:                  // Ǯ�����ݻ��������ļ�,m_szFileName�������ļ���
			break;

		case FILE_NEWS_EX:                  // ������,��������m_szFileName����Ŀ¼������
			break;
		}
		break;

	default:
		return 0;                           // unknown data
	}
	return 1;
}
