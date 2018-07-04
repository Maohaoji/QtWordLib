#ifndef QTWORDLIB_H
#define QTWORDLIB_H

#include <QtWidgets/QMainWindow>
#include "ui_qtwordlib.h"
#include "QtXmlOperator.h"
#include "QtAttrDlg.h"
#include <qmessagebox.h>

 _declspec(dllexport) wstring WordLib();

class QtWordLib : public QMainWindow
{
	Q_OBJECT

public:
	QtWordLib(QWidget *parent = 0);
	~QtWordLib();

	bool IsSameWordExist(QString str);                          //��ͬ�ʾ��Ƿ��Ѵ���
	bool IsSameTreeItemExist(QTreeWidgetItem *Item,QString str);    //��ͬ���ڵ����Ƿ��Ѵ���
	bool IsSameRootTreeItemExist(QString str);            //��ͬ�����ڵ����Ƿ��Ѵ���

	wstring GetResult();

public:
	int nRet;
private:
	Ui::QtWordLibClass ui;
	QtXmlOperator XmlOp;      //xml���������

	QAction *m_Action1;    //������
	QAction *m_Action2;    //�޸����
	QAction *m_Action3;    //ɾ�����
	QAction *m_Action4;    //�������
	QAction *m_Action5;    //�������

	QAction *m_TAction1;   //��ӷ�֧
	QAction *m_TAction2;   //�޸���
	QAction *m_TAction3;   //ɾ����
	QAction *m_TAction4;   //��Ӹ���֧

private slots:
	void QuerylistItemAttr(QTreeWidgetItem *Item);         //��ѯ���ؼ�ĳһ���Ӧ������ֵ����ʾ���б���
	void ShowListMenu(QPoint pt);                          //�����б��Ҽ��˵�
	void ShowTreeMenu(QPoint pt);                          //�������ؼ��Ҽ��˵�
	void on_menu_delListItem();                            //ɾ���б��ͬʱɾ��xml�ļ����������
	void on_menu_addListItem();                            //����б��ͬʱ���xml�ļ����������
	void on_menu_edtListItem();                            //�༭�б��ͬʱ�޸�xml�ļ����������
	void on_menu_addTreeItem();                            //�������ؼ��ӽڵ㣬ͬʱ����xml�ļ�������ӽڵ�
	void on_menu_edtTreeItem();                            //�༭���ؼ��ڵ㣬ͬʱ�޸�xml�ļ�����ؽڵ�
	void on_menu_delTreeItem();                            //ɾ�����ؼ��ڵ㣬ͬʱɾ��xml�ļ�����ؽڵ�
	void on_menu_addGTreeItem();                           //�������ؼ����ڵ㣬ͬʱ����xml�ļ�����ؽڵ�
	void on_menu_upListItem();                             //���ƴʾ�
	void on_menu_downListItem();                           //���ƴʾ�
	void PresentResult(QListWidgetItem *Item);             //��˫���б���������ʾ�ڽ���ı���
	void OnInsert();
	void OnQuit();
};

#endif // QTWORDLIB_H
