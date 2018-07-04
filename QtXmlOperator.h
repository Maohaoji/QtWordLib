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
	void Save();   //�����xml�ļ���
	bool ReadFile(const QString &fileName);  //��ȡxml�ļ�
	void QueryAttribute(QString strQue ,vector<QString> &strList); //��ѯĳ���ڵ������ֵ����
	void QueryAttributeNamebyValue(QDomElement ele,QString strAttrValue,QString &strAttrName);   //������ֵ��ѯ��������
	void QueryAttributeNameMax(QDomElement ele,int &nMax);   //����Ϊan����ѯn�����ֵ
	void QueryNode(QString strQue,QDomElement &ele);     //��ѯĳ���ڵ�Ԫ��
	void SearchChild(vector<QDomElement> eleParentList,QString strQue,vector<QDomElement> &eleList);//����������Ϊ������һ�����ӽڵ��з��������Ľڵ�
	void PresentTree(QTreeWidget *tree);    //��xml�ṹ��ʾ�����ؼ���
	void CycleTree(QTreeWidgetItem *treeitem , QDomElement eleParent);
	void AddChildElement(QDomElement &eleParent , QString strName);    //����ĳһ�ڵ���ӽڵ㣬�ڵ�����ΪstrName
	void AddRootElement(QString strName);                              //���Ӹ��ڵ����Ԫ��
	void ResetAttributes(QDomElement &ele, QListWidget *list);      //��list�������ԣ�������������ԣ������θ�ֵ
	QDomDocument m_doc;
	QFile m_file;
};

