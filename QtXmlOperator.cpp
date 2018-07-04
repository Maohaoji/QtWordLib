#include "QtXmlOperator.h"

#pragma execution_character_set("utf-8")
QtXmlOperator::QtXmlOperator()
{
	
}


QtXmlOperator::~QtXmlOperator(void)
{
	//m_file.close();
}

void QtXmlOperator::Save()
{
	//QFile file(QString("d:\\test1.xml"));
	//m_file.setFileName(QString("d:\\test.xml"));
	if (!m_file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ))
        return ;
    QTextStream out(&m_file);
    out.setCodec("utf-8");
	QString str = m_doc.toString();
    m_doc.save(out,4,QDomNode::EncodingFromTextStream);
    m_file.close();
}

bool QtXmlOperator::ReadFile(const QString &fileName)
{
	m_file.setFileName(fileName);
	if (!m_file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
	QString errorStr;  
    int errorLine;  
    int errorCol;  
	if(!m_doc.setContent(&m_file,true,&errorStr,&errorLine,&errorCol))
	{
		m_file.close();
		return false;
	}
	m_file.close(); 
	return true;
}

void QtXmlOperator::PresentTree(QTreeWidget *tree)
{
	QDomElement root = m_doc.documentElement();  
	//QString strname = root.nodeName();
	//QTreeWidgetItem *Item = new QTreeWidgetItem(tree,QStringList(strname));
    QDomElement ele = root.firstChildElement();

	//循环遍历树控件根节点的子节点，并递归遍历xml各节点，将结构显示于树控件中
    for(;!ele.isNull();ele = ele.nextSiblingElement()){  
		QString str = ele.nodeName();
		QTreeWidgetItem *Item_next = new QTreeWidgetItem(tree,QStringList(str));
		CycleTree(Item_next,ele); 
    }  
}

void QtXmlOperator::CycleTree(QTreeWidgetItem *treeitem , QDomElement eleParent)
{
	//递归遍历xml节点
	QDomElement ele = eleParent.firstChildElement();
	for(;!ele.isNull();ele = ele.nextSiblingElement()){  
		QString str = ele.nodeName();
		QTreeWidgetItem *Item_next = new QTreeWidgetItem(treeitem,QStringList(str));
		CycleTree(Item_next,ele);
    }  
}

void QtXmlOperator::QueryAttribute(QString strQue ,vector<QString> &strList)
{
	//strQue为类似“电器/PLC/芯片”结构，先分解
	QStringList Qstrlist = strQue.split(QString("/"));
	strList.clear();
	QDomElement root = m_doc.documentElement();
	vector<QDomElement> vecEle;
	vecEle.push_back(root);

	//从顶向下，查找对应节点
	for ( int k=0 ; k<Qstrlist.length() ; k++ )
	{
		vector<QDomElement> vecEleTemp = vecEle;
		SearchChild(vecEleTemp,Qstrlist.at(k),vecEle);
	}
	
	if ( vecEle.size() < 1 )
		return;
	QDomElement ele = vecEle.at(0).toElement();     //程序默认只有唯一的节点路径！
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int j=0 ; j<mapAtt.length() ; j++ )
	{
		QDomAttr eleAtt = mapAtt.item(j).toAttr();
		strList.push_back(eleAtt.nodeValue());
	}
	
}

void QtXmlOperator::QueryNode(QString strQue,QDomElement &ele)
{
	QStringList Qstrlist = strQue.split(QString("/"));
	QDomElement root = m_doc.documentElement();
	vector<QDomElement> vecEle;
	vecEle.push_back(root);

	//从顶向下，查找对应节点
	for ( int k=0 ; k<Qstrlist.length() ; k++ )
	{
		vector<QDomElement> vecEleTemp = vecEle;
		SearchChild(vecEleTemp,Qstrlist.at(k),vecEle);
	}
	if ( vecEle.size() < 1 )
		return;
	ele = vecEle.at(0).toElement();
}

void QtXmlOperator::SearchChild(vector<QDomElement> eleParentList,QString strQue,vector<QDomElement> &eleList)
{
	eleList.clear();
	for ( int j=0 ; j<eleParentList.size() ; j++ )
	{
		QDomNodeList nodelist = eleParentList.at(j).elementsByTagName(strQue);
	    for ( int i=0 ; i<nodelist.length() ; i++ )
	    {
		    QDomElement ele = nodelist.at(i).toElement();
		    if ( ele.parentNode() == eleParentList.at(j) )
			    eleList.push_back(ele);
	    }
	}
}

void QtXmlOperator::QueryAttributeNamebyValue(QDomElement ele,QString strAttrValue,QString &strAttrName)
{
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int j=0 ; j<mapAtt.length() ; j++ )
	{
		QDomAttr eleAtt = mapAtt.item(j).toAttr();
		if ( strAttrValue == eleAtt.nodeValue() )
		{
			strAttrName = eleAtt.nodeName();
			break;
		}
	}
}

void QtXmlOperator::QueryAttributeNameMax(QDomElement ele,int &nMax)
{
	//属性名称都为an，查找最大的n
	nMax = 0;
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int j=0 ; j<mapAtt.length() ; j++ )
	{
		QDomAttr eleAtt = mapAtt.item(j).toAttr();
		QString strName = eleAtt.nodeName();
		int i = strName.mid(1,strName.size()-1).toInt();
		if ( i>=nMax )
			nMax = i;
	}
}

void QtXmlOperator::AddChildElement(QDomElement &eleParent , QString strName)
{
	QDomElement newele = m_doc.createElement(strName);
	eleParent.appendChild(newele);
}

void QtXmlOperator::AddRootElement(QString strName)
{
	QDomElement newele = m_doc.createElement(strName);
	QDomElement root = m_doc.documentElement();
	root.appendChild(newele);
}

void QtXmlOperator::ResetAttributes(QDomElement &ele, QListWidget *list)
{
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int i=0 ; i<mapAtt.length() ; i++ )
	{
		QDomAttr eleAtt = mapAtt.item(i).toAttr();
		QString strName = eleAtt.nodeName();
	    ele.removeAttribute(strName);
	}
	for ( int j=0 ; j<list->count() ; j++ )
	{   
		QString strName;
		strName.sprintf("a%d",j+1);
		ele.setAttribute(strName,list->item(j)->text());
	}
}