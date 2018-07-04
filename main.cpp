#include "qtwordlib.h"
#include <QtWidgets/QApplication>
#include <qtextcodec.h>
#include <qstylefactory.h>

#pragma execution_character_set("utf-8")  
 
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("WindowsXP"));
	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec::setCodecForLocale(codec);
	
	QtWordLib w;
	w.show();
	int i=a.exec();
	return i;
}
 _declspec(dllexport) wstring WordLib()
{
	int argc=0;
	char *argv = "12345";
	QApplication a(argc, &argv);
	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec::setCodecForLocale(codec);
	QtWordLib w;
	//w.setWindowModality(Qt::WindowModal);
	w.show();
	a.exec();
	if ( w.nRet )
	    return w.GetResult();
	else
	{
		wstring wstr = L"";
		return wstr;
	}
}