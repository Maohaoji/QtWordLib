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

	bool IsSameWordExist(QString str);                          //相同词句是否已存在
	bool IsSameTreeItemExist(QTreeWidgetItem *Item,QString str);    //相同树节点项是否已存在
	bool IsSameRootTreeItemExist(QString str);            //相同树根节点项是否已存在

	wstring GetResult();

public:
	int nRet;
private:
	Ui::QtWordLibClass ui;
	QtXmlOperator XmlOp;      //xml操作类对象

	QAction *m_Action1;    //添加语句
	QAction *m_Action2;    //修改语句
	QAction *m_Action3;    //删除语句
	QAction *m_Action4;    //上移语句
	QAction *m_Action5;    //下移语句

	QAction *m_TAction1;   //添加分支
	QAction *m_TAction2;   //修改项
	QAction *m_TAction3;   //删除项
	QAction *m_TAction4;   //添加根分支

private slots:
	void QuerylistItemAttr(QTreeWidgetItem *Item);         //查询树控件某一项对应的属性值，显示于列表中
	void ShowListMenu(QPoint pt);                          //弹出列表右键菜单
	void ShowTreeMenu(QPoint pt);                          //弹出树控件右键菜单
	void on_menu_delListItem();                            //删除列表项，同时删除xml文件中相关属性
	void on_menu_addListItem();                            //添加列表项，同时添加xml文件中相关属性
	void on_menu_edtListItem();                            //编辑列表项，同时修改xml文件中相关属性
	void on_menu_addTreeItem();                            //增加树控件子节点，同时增加xml文件中相关子节点
	void on_menu_edtTreeItem();                            //编辑树控件节点，同时修改xml文件中相关节点
	void on_menu_delTreeItem();                            //删除数控件节点，同时删除xml文件中相关节点
	void on_menu_addGTreeItem();                           //增加树控件根节点，同时增加xml文件中相关节点
	void on_menu_upListItem();                             //上移词句
	void on_menu_downListItem();                           //下移词句
	void PresentResult(QListWidgetItem *Item);             //将双击列表项内容显示于结果文本框
	void OnInsert();
	void OnQuit();
};

#endif // QTWORDLIB_H
