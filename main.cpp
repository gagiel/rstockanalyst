#include <QApplication>
#include <iostream>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QString qsSrcFile = app.applicationDirPath()+"/1.txt";
	QFile fileSrc(qsSrcFile);			//���ػ����ļ�

	if(!fileSrc.open(QFile::ReadOnly))		//���ļ�
	{
		std::cout<<"open src file '"<<qsSrcFile.toStdString()<<"' error."<<std::endl;
		return -1;							//ʧ���˳�
	}


	QImage image(500,500,QImage::Format_ARGB32);			//����һ��500*500�Ļ���
	QPainter painter(&image);								//��������QPainter�����
	painter.setRenderHint(QPainter::Antialiasing,true);		//���ÿ���ݣ���Ҫ������ֱֹ�߾��

	QString qsLine = fileSrc.readLine().trimmed();			//��ȡ��һ������

	QVector<QLineF> listLines;

	QPointF ptFront;
	{
		//��ȡ��ʼ��
		QStringList listPos = qsLine.split(",\t");
		if(listPos.size()>1)
			ptFront = QPointF((listPos[0].toFloat()+5.0)*50.0,(listPos[1].toFloat())*50.0);
		else
		{
			std::cout<<"read first point error."<<std::endl;
			return -1;
		}
	}

	//��ȡ��һ����
	qsLine = fileSrc.readLine().trimmed();

	while(!qsLine.isEmpty())
	{
		QStringList listPos = qsLine.split(",\t");
		if(listPos.size()>1)
		{
			QPointF ptNow = QPointF((listPos[0].toFloat()+5.0)*50.0,(listPos[1].toFloat())*50.0);
			listLines.push_back(QLineF(ptFront,ptNow));
			ptFront = ptNow;
		}
		else
		{
			std::cout<<"read point error."<<std::endl;
			return -1;
		}

		qsLine = fileSrc.readLine().trimmed();
	}

	painter.drawLines(listLines);			//����ֱ��


	//���������ͼƬ��ʾ��һ��QLabel�ϡ�
	{
		//��һ����ʾ��ʽ��ֱ�ӽ�label��ʾ����
		QLabel label(0);
		label.setPixmap(QPixmap::fromImage(image));
		label.show();
		return app.exec();
	}
/*	{
		//��lable����widget�У�����ʾ������
		QWidget widget(0);
		QLabel label(&widget);
		label.setPixmap(image);
		QVBoxLayout layout(&widget);
		layout.addWidget(&label);
		widget.setLayout(&layout);
		widget.show();
		return app.exec();
	}
*/
}
