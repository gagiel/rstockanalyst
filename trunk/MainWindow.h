#pragma once
#include <QtGui>
#include "BaseWidget.h"
#include "BaseMarketWidget.h"
#include "RMdiCtrl.h"

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow();
	~CMainWindow();


public:
	bool setupStockDrv();
	void initTemplates();			//��ʼ������ģ��

protected slots:
	void onAddTemplate();			//���Ӱ���
	void onSaveTemplate();			//�������а���

protected:
	virtual bool winEvent( MSG* message, long* result );


protected:
	virtual long OnStockDrvMsg(WPARAM wParam,LPARAM lParam);

private:
	CBaseWidget* getSubWindows(const QString& title);

private:
	QTabWidget* m_pTabWidget;
	QMenuBar* m_pMenuBar;
	QString m_qsTemplateDir;		//��������ļ����ڵ�Ŀ¼
};
