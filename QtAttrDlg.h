#pragma once
#include "qdialog.h"
#include "ui_DlgAttr.h"
class QtAttrDlg :
	public QDialog
{
	Q_OBJECT
public:
	QtAttrDlg(QWidget *parent = 0);
	~QtAttrDlg(void);
	void SetEditText(QString str);
	QString m_strAttr;               //��Ӧ�ı�����ı��ַ���
private:
	Ui::DlgAttr ui;

private slots:
	void getValue(); 
};

