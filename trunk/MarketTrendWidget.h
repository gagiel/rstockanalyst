/************************************************************************/
/* �ļ����ƣ�MarketTrendWidget.h
/* ����ʱ�䣺2012-11-08 10:59
/*
/* ��    ����������ʾ�г�����ͼ�Ĵ��ڣ��̳���CBaseWidget
/************************************************************************/

#ifndef MARKET_TREND_WIDGET_H
#define	MARKET_TREND_WIDGET_H
#include "BaseWidget.h"
#include "StockInfoItem.h"

class CMarketTrendWidget : public CBaseWidget
{
	Q_OBJECT
	//struct stHeaderInfo
	//{
	//	QString text;
	//	int column;
	//};
public:
	CMarketTrendWidget(CBaseWidget* parent = 0);
	~CMarketTrendWidget(void);

public:
	//���ظ�K��ͼ��������Ϣ
	virtual bool loadPanelInfo(const QDomElement& eleWidget);
	//�����K��ͼ��������Ϣ
	virtual bool savePanelInfo(QDomDocument& doc,QDomElement& eleWidget);

public:
	void setStocks(const QList<CStockInfoItem*>& list);		//����Ҫ��ʾ�Ĺ�Ʊ�б�

public slots:
	void stockInfoChanged(const QString& code);				//ĳֻ��Ʊ����Ϣ�����ı�

private:
	void clearTmpData();						//�����������д������ڴ档
	void clickedHeader(int column);				//�����ͷ��ʱ����
	void clickedStock(CStockInfoItem* pItem);	//�������Ʊʱ����
	void offsetShowHeaderIndex(int offset);		//�ı䵱ǰͷ����ʾ�Ŀ�ʼλ��
	void clickedBlock(const QString& block);	//������ʱ����

protected:
	virtual void paintEvent(QPaintEvent* e);				//�����¼�
	virtual void resizeEvent(QResizeEvent* e);				//��С�ı���¼�
	virtual void mousePressEvent(QMouseEvent* e);			//������¼�
	virtual void wheelEvent(QWheelEvent* e);				//����м������¼�

	//�麯���������ؼ����Զ���˵���
	virtual QMenu* getCustomMenu();

private:
	QMenu* m_pMenuCustom;					//�Զ���˵�
	QStringList m_listHeader;				//ͷ������
	QList<CStockInfoItem*> m_listStocks;	//Ҫ��ʾ�Ĺ�Ʊ�б�
	QMap<CStockInfoItem*,int> m_mapStockIndex;	//�������ٲ���ĳֻ��Ʊ���ڵ�����
	CStockInfoItem* m_pSelectedStock;		//��ǰѡ�еĹ�Ʊ
	int m_iSortColumn;						//��ǰ�����������
	Qt::SortOrder m_sortOrder;				//��ǰ����ʽ

	/*���ڻ��Ƶĳ�Ա����*/
private:
	void updateDrawRect();					//���»�������Ĵ�С
	void updateBlockRect();					//���µײ���鰴ť����ʾ����
	void drawHeaders(QPainter& p);			//����ͷ����Ϣ
	void drawStocks(QPainter& p);			//���ƹ�Ʊ��Ϣ
	void drawBottom(QPainter& p);			//���Ƶײ���Ϣ
	void drawStock(QPainter& p,const QRect& rtStock,CStockInfoItem* pItem);	//���Ƶ�����Ʊ
	void drawBottomBtn(QPainter& p);		//���Ƶײ���������ť

	//�ж��������λ�ã�������Ӧ����Ӧ
	//void hitHeader(QPoint& ptCur);

	QString dataOfDisplay(CStockInfoItem* itemData,int column);
	QColor dataOfColor(CStockInfoItem* itemData,int column);
	QRect rectOfStock(CStockInfoItem* pItem);			//��ȡĳֻ��Ʊ��ʾ��λ��

	/*���ڻ��Ƶĳ�Ա����*/
private:
	QRect m_rtHeader;						//ͷ��Header����
	QRect m_rtClient;						//ʵ����������
	QRect m_rtBottom;						//�ײ��������ڻ��Ʒ��࣬����������Ϣ

	QRect m_rtPreIndex;						//��һ����ʼ��
	QRect m_rtNextIndex;					//��һ����ʼ��

	int m_iHeaderHeight;					//ͷ���ĸ߶�
	int m_iStockHeight;						//���������ĸ߶�
	int m_iBottomHeight;					//�ײ��ĸ߶�

	int showHeaderIndex;					//��ʼ��ʾ��ͷ������-����0,1,2,5��Ϊ5-3=2��
	int showStockIndex;						//��ʼ��ʾ�Ĺ�Ʊ����-����
	int showBlockIndex;						//��ʼ��ʾ�İ������-�ײ�����
	QList<int> m_listItemWidth;				//����item�Ŀ��ȡ�
	QList<QPair<QString,QRect>> m_listBlocks;	//�����������ڵľ���
	QString m_qsSelectedBlock;				//��ǰѡ�еİ��
};


#endif	//MARKET_TREND_WIDGET_H