#pragma once
#include<qxmlstream.h>
#include<qfile.h>
#include<qtreewidget.h>
#include<qdom.h>
#include<vector>
#include<qtextstream.h>
#include<qlistwidget.h>
using namespace std;

class QtXmlOperator
{
public:
	QtXmlOperator();
	~QtXmlOperator(void);
	void Save();   //保存进xml文件中
	bool ReadFile(const QString &fileName);  //读取xml文件
	void QueryAttribute(QString strQue ,vector<QString> &strList); //查询某个节点的属性值链表
	void QueryAttributeNamebyValue(QDomElement ele,QString strAttrValue,QString &strAttrName);   //从属性值查询属性名称
	void QueryAttributeNameMax(QDomElement ele,int &nMax);   //属性为an，查询n的最大值
	void QueryNode(QString strQue,QDomElement &ele);     //查询某个节点元素
	void SearchChild(vector<QDomElement> eleParentList,QString strQue,vector<QDomElement> &eleList);//第三个参数为符合这一级的子节点中符合条件的节点
	void PresentTree(QTreeWidget *tree);    //将xml结构显示与树控件中
	void CycleTree(QTreeWidgetItem *treeitem , QDomElement eleParent);
	void AddChildElement(QDomElement &eleParent , QString strName);    //增加某一节点的子节点，节点名称为strName
	void AddRootElement(QString strName);                              //增加根节点的子元素
	void ResetAttributes(QDomElement &ele, QListWidget *list);      //从list更新属性，先清除所有属性，再依次赋值
	QDomDocument m_doc;
	QFile m_file;
};

