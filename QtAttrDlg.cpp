#include "QtAttrDlg.h"
#include <qmessagebox.h>
#pragma execution_character_set("utf-8")
QtAttrDlg::QtAttrDlg(QWidget *parent)
{
	ui.setupUi(this);
	m_strAttr = QString("");
}


QtAttrDlg::~QtAttrDlg(void)
{
}

void QtAttrDlg::getValue()
{
	m_strAttr = ui.textEditAttr->toPlainText();
	if ( m_strAttr.length() <= 0 )
	{
		QMessageBox a(QString("提示"),QString("输入不能为空！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	this->accept();
}

void QtAttrDlg::SetEditText(QString str)
{
	m_strAttr = str;
	ui.textEditAttr->setText(m_strAttr);
}