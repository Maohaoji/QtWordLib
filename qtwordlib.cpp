#include "qtwordlib.h"

#pragma execution_character_set("utf-8")

QtWordLib::QtWordLib(QWidget *parent)
	: QMainWindow(parent)
{
	nRet=0;

	ui.setupUi(this);
	ui.treeWord->setColumnCount(1); //��������
	XmlOp.ReadFile(QCoreApplication::applicationDirPath() + QString("\\test.xml"));
	XmlOp.PresentTree(ui.treeWord);
	
	connect(ui.BtnAddWord,SIGNAL(pressed()),this,SLOT(on_menu_addListItem()));
	connect(ui.BtnEdtWord,SIGNAL(pressed()),this,SLOT(on_menu_edtListItem()));
	connect(ui.BtnDelWord,SIGNAL(pressed()),this,SLOT(on_menu_delListItem()));
	connect(ui.BtnAddTree,SIGNAL(pressed()),this,SLOT(on_menu_addTreeItem()));
	connect(ui.BtnEdtTree,SIGNAL(pressed()),this,SLOT(on_menu_edtTreeItem()));
	connect(ui.BtnDelTree,SIGNAL(pressed()),this,SLOT(on_menu_delTreeItem()));
	connect(ui.BtnAddGTree,SIGNAL(pressed()),this,SLOT(on_menu_addGTreeItem()));
	connect(ui.BtnUp,SIGNAL(pressed()),this,SLOT(on_menu_upListItem()));
	connect(ui.BtnDown,SIGNAL(pressed()),this,SLOT(on_menu_downListItem()));
	
	connect(ui.act_AddGTree,SIGNAL(triggered()),this,SLOT(on_menu_addGTreeItem()));
	connect(ui.act_AddTree,SIGNAL(triggered()),this,SLOT(on_menu_addTreeItem()));
	connect(ui.act_EdtTree,SIGNAL(triggered()),this,SLOT(on_menu_edtTreeItem()));
	connect(ui.act_DelTree,SIGNAL(triggered()),this,SLOT(on_menu_delTreeItem()));

	connect(ui.act_AddList,SIGNAL(triggered()),this,SLOT(on_menu_addListItem()));
	connect(ui.act_EdtList,SIGNAL(triggered()),this,SLOT(on_menu_edtListItem()));
	connect(ui.act_DelList,SIGNAL(triggered()),this,SLOT(on_menu_delListItem()));
	connect(ui.act_uplist,SIGNAL(triggered()),this,SLOT(on_menu_upListItem()));
	connect(ui.act_downlist,SIGNAL(triggered()),this,SLOT(on_menu_downListItem()));
	//connect(ui.treeWord,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowTreeMenu(QPoint)));
}

QtWordLib::~QtWordLib()
{

}


void QtWordLib::QuerylistItemAttr(QTreeWidgetItem *Item)
{
	//��ýڵ�·��
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	vector<QString> strlist;
	XmlOp.QueryAttribute(strSearch,strlist);         //��ѯ��Ӧ�ڵ�����
	ui.listWordItem->clear();
	for ( int i=0 ; i<strlist.size() ; i++ )
	{
		ui.listWordItem->addItem(strlist.at(i));
	}
}

void QtWordLib::ShowListMenu(QPoint pt)
{
	QListWidgetItem *its = ui.listWordItem->itemAt(pt);
	QMenu* popMenu = new QMenu(ui.listWordItem);
	m_Action1 = new QAction("������", ui.listWordItem);
	m_Action2 = new QAction("�޸����", ui.listWordItem);
	m_Action3 = new QAction("ɾ�����", ui.listWordItem);
	m_Action4 = new QAction("�������", ui.listWordItem);
	m_Action5 = new QAction("�������", ui.listWordItem);

	//ѡ���б�ĳһ�������1��2��3������ֻ����1
	if ( its )
	{
		 
         popMenu->addAction(m_Action1);
		 popMenu->addAction(m_Action2);
         popMenu->addAction(m_Action3);
		 popMenu->addAction(m_Action4);
         popMenu->addAction(m_Action5);
         
	}
	else
	{
		popMenu->addAction(m_Action1);
	}

	connect(m_Action1,SIGNAL(triggered()),this,SLOT(on_menu_addListItem()));
	connect(m_Action2,SIGNAL(triggered()),this,SLOT(on_menu_edtListItem()));
	connect(m_Action3,SIGNAL(triggered()),this,SLOT(on_menu_delListItem())); 
	connect(m_Action4,SIGNAL(triggered()),this,SLOT(on_menu_upListItem())); 
	connect(m_Action5,SIGNAL(triggered()),this,SLOT(on_menu_downListItem())); 
	
	popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
	
}

void QtWordLib::ShowTreeMenu(QPoint pt)
{
	QTreeWidgetItem *its = ui.treeWord->itemAt(pt);
	QMenu* popTMenu = new QMenu(ui.treeWord);
	m_TAction1 = new QAction("��ӷ�֧", ui.treeWord);
	m_TAction2 = new QAction("�޸���", ui.treeWord);
	m_TAction3 = new QAction("ɾ����", ui.treeWord);
	m_TAction4 = new QAction("��Ӹ���֧",ui.treeWord);

	//ѡ�����ؼ�ĳһ������1��2��3��������4
	if ( its )
	{
		 
         popTMenu->addAction(m_TAction1);
		 popTMenu->addAction(m_TAction2);
         popTMenu->addAction(m_TAction3);
         
	}
	else
	{
		popTMenu->addAction(m_TAction4);
	}

	connect(m_TAction1,SIGNAL(triggered()),this,SLOT(on_menu_addTreeItem()));
	connect(m_TAction2,SIGNAL(triggered()),this,SLOT(on_menu_edtTreeItem()));
	connect(m_TAction3,SIGNAL(triggered()),this,SLOT(on_menu_delTreeItem())); 
	connect(m_TAction4,SIGNAL(triggered()),this,SLOT(on_menu_addGTreeItem())); 
	popTMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}

void QtWordLib::on_menu_delListItem()
{
	//QListWidgetItem *its = ui.listWordItem->currentItem();
	QListWidgetItem *its = ui.listWordItem->takeItem(ui.listWordItem->currentRow());

	if ( its == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//QString strAttrName;

	//��ýڵ�·������ѯ�ڵ�
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	QDomElement ele;
	XmlOp.QueryNode(strSearch,ele);

	ui.listWordItem->removeItemWidget(its);//ɾ����Ӧ��
	delete its;
	//XmlOp.QueryAttributeNamebyValue(ele,its->text(),strAttrName);      //������ֵ����������������Ĭ��������ֵ��ͬ�����ԣ�
	XmlOp.ResetAttributes(ele,ui.listWordItem);
	/*
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int i=0 ; i<mapAtt.length() ; i++ )
	{
		QDomAttr eleAtt = mapAtt.item(i).toAttr();
		QString strName = eleAtt.nodeName();
	    ele.removeAttribute(strName);
	}
	for ( int j=0 ; j<ui.listWordItem->count() ; j++ )
	{   
		QString strName;
		strName.sprintf("a%d",j+1);
		ele.setAttribute(strName,ui.listWordItem->item(j)->text());
	}*/
	//delete its;
	XmlOp.Save();
}

void QtWordLib::on_menu_addListItem()
{
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	if ( Item == NULL )
	{
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//��ýڵ�·������ѯ�ڵ�
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	QDomElement ele;
	XmlOp.QueryNode(strSearch,ele);
	QtAttrDlg dlg;
	int nRet = dlg.exec();
	if ( !nRet )
		return;
	if ( IsSameWordExist(dlg.m_strAttr) )           //����ͬ��䲻���
	{
		QMessageBox a(QString("��ʾ"),QString("������ͬ�ʾ䣡"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	//int nAttr;
	//XmlOp.QueryAttributeNameMax(ele,nAttr);
	//nAttr++;
	//QString strAttrName;
	//strAttrName = QString::number(nAttr,10);
	//ele.setAttribute(QString("a")+strAttrName,dlg.m_strAttr);
	ui.listWordItem->addItem(dlg.m_strAttr);
	XmlOp.ResetAttributes(ele,ui.listWordItem);
	/*
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int i=0 ; i<mapAtt.length() ; i++ )
	{
		QDomAttr eleAtt = mapAtt.item(i).toAttr();
		QString strName = eleAtt.nodeName();
	    ele.removeAttribute(strName);
	}
	for ( int j=0 ; j<ui.listWordItem->count() ; j++ )
	{   
		QString strName;
		strName.sprintf("a%d",j+1);
		ele.setAttribute(strName,ui.listWordItem->item(j)->text());
	}*/

	XmlOp.Save();
	
}

void QtWordLib::on_menu_edtListItem()
{
	QListWidgetItem *its = ui.listWordItem->currentItem();
	if ( its == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//��ýڵ�·������ѯ�ڵ�
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	QDomElement ele;
	//QString strAttrName;
	XmlOp.QueryNode(strSearch,ele);
	//XmlOp.QueryAttributeNamebyValue(ele,its->text(),strAttrName);      //������ֵ����������������Ĭ��������ֵ��ͬ�����ԣ�
	QtAttrDlg dlg;
	dlg.SetEditText(its->text());
	int nRet = dlg.exec();
	if ( !nRet )
		return;

	its->setText(dlg.m_strAttr);
	//ele.setAttribute(strAttrName,dlg.m_strAttr);

	XmlOp.ResetAttributes(ele,ui.listWordItem);
	/*
	QDomNamedNodeMap mapAtt = ele.attributes();
	for ( int i=0 ; i<mapAtt.length() ; i++ )
	{
		QDomAttr eleAtt = mapAtt.item(i).toAttr();
		QString strName = eleAtt.nodeName();
	    ele.removeAttribute(strName);
	}
	for ( int j=0 ; j<ui.listWordItem->count() ; j++ )
	{   
		QString strName;
		strName.sprintf("a%d",j+1);
		ele.setAttribute(strName,ui.listWordItem->item(j)->text());
	}
	*/
	XmlOp.Save();
}

void QtWordLib::on_menu_upListItem()                             //���ƴʾ�
{
	QListWidgetItem *its = ui.listWordItem->currentItem();
	if ( its == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	if ( ui.listWordItem->currentRow() <= 0 )
	{
		//QMessageBox a(QString("��ʾ"),QString("�޷����ƣ�"),QMessageBox::Warning,1,1,1,this);
		//a.exec();
		return;
	}

	//��ýڵ�·������ѯ�ڵ�
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	QDomElement ele;
	//QString strAttrName;
	XmlOp.QueryNode(strSearch,ele);

	QListWidgetItem *itsup = ui.listWordItem->item(ui.listWordItem->currentRow()-1);
	QString strUp = itsup->text();
	QString strCurrent = its->text();
	itsup->setText(strCurrent);
	its->setText(strUp);

	ui.listWordItem->setCurrentItem(itsup);

	XmlOp.ResetAttributes(ele,ui.listWordItem);
	XmlOp.Save();
}

void QtWordLib::on_menu_downListItem()                           //���ƴʾ�
{
	QListWidgetItem *its = ui.listWordItem->currentItem();
	if ( its == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	if ( ui.listWordItem->currentRow() >= ui.listWordItem->count()-1 )
	{
		//QMessageBox a(QString("��ʾ"),QString("�޷����ƣ�"),QMessageBox::Warning,1,1,1,this);
		//a.exec();
		return;
	}

	//��ýڵ�·������ѯ�ڵ�
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	QDomElement ele;
	//QString strAttrName;
	XmlOp.QueryNode(strSearch,ele);

	QListWidgetItem *itsdown = ui.listWordItem->item(ui.listWordItem->currentRow()+1);
	QString strDown = itsdown->text();
	QString strCurrent = its->text();
	itsdown->setText(strCurrent);
	its->setText(strDown);

	ui.listWordItem->setCurrentItem(itsdown);

	XmlOp.ResetAttributes(ele,ui.listWordItem);
	XmlOp.Save();
}

void QtWordLib::PresentResult(QListWidgetItem *Item)
{
	ui.textEditResult->setText(Item->text());          //��ʾ�ڽ���ı�����
}
wstring QtWordLib::GetResult()
{
	QString strResult = ui.textEditResult->toPlainText();
	wstring ba = strResult.toStdWString();
	return ba;
}
void QtWordLib::OnInsert()
{
	nRet=1;
	this->close();
}

void QtWordLib::OnQuit()
{
	nRet=0;
	this->close();
}

void QtWordLib::on_menu_addGTreeItem()
{
	QtAttrDlg dlg;
	int nRet = dlg.exec();
	if ( !nRet )
		return;
	if ( IsSameRootTreeItemExist(dlg.m_strAttr) )         //�ж��Ƿ�����ͬ���Ƶĸ��ڵ�����
	{
		QMessageBox a(QString("��ʾ"),QString("������ͬ�"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	
	//��Ӹ��ڵ�����
	QTreeWidgetItem *newItem = new QTreeWidgetItem(ui.treeWord,QStringList(dlg.m_strAttr));
	XmlOp.AddRootElement(dlg.m_strAttr);
	XmlOp.Save();
}

void QtWordLib::on_menu_addTreeItem()
{
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	if ( Item == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	QtAttrDlg dlg;
	int nRet = dlg.exec();
	if ( !nRet )
		return;

	if ( IsSameTreeItemExist(ui.treeWord->currentItem(),dlg.m_strAttr) )          //�ж��Ƿ���������ͬ���ӽڵ�
	{
		QMessageBox a(QString("��ʾ"),QString("������ͬ�"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//������ڵ�
	QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList(dlg.m_strAttr));
	Item->addChild(newItem);

	//��ȡxml�ڵ�·�������ڶ�Ӧ�ڵ�����ӽڵ�
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}

	//QDomElement root = m_doc.documentElement(); 
	QDomElement ele;
	XmlOp.QueryNode(strSearch,ele);
	XmlOp.AddChildElement(ele,dlg.m_strAttr);
	XmlOp.Save();
	//return;
	//ele.appendChild(
}

void QtWordLib::on_menu_edtTreeItem()
{
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	if ( Item == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	QtAttrDlg dlg;
	dlg.SetEditText(Item->text(0));
	int nRet = dlg.exec();
	if ( !nRet )
		return;

	//��ȡxml�ڵ�·�������ڶ�Ӧ�ڵ��޸�����
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}

	Item->setText(0,dlg.m_strAttr);
	//QDomElement root = m_doc.documentElement(); 
	QDomElement ele;
	XmlOp.QueryNode(strSearch,ele);

	


	ele.setTagName(dlg.m_strAttr);
	XmlOp.Save();
}

void QtWordLib::on_menu_delTreeItem()
{
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	if ( Item == NULL )
	{
		
		QMessageBox a(QString("��ʾ"),QString("δѡ���"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//��ȡxml�ڵ�·������ɾ����Ӧ�ڵ�
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}

	
	//QDomElement root = m_doc.documentElement(); 
	QDomElement ele;
	XmlOp.QueryNode(strSearch,ele);
	ele.parentNode().removeChild(ele);
	if( Item->parent() )
	{
	    
	    Item->parent()->removeChild(Item);
	    delete Item;
	    
	}
	else        //���ڵ���ӽڵ����
	{
		this->ui.treeWord->removeItemWidget(Item,0);
		delete Item;
	}
	XmlOp.Save();
}

bool QtWordLib::IsSameWordExist(QString str)
{
	//����list�����ж�
	for ( int i=0 ; i<ui.listWordItem->count(); i++ )
	{
		if ( str == ui.listWordItem->item(i)->text() )
			return true;
	}
	return false;
}

bool QtWordLib::IsSameTreeItemExist(QTreeWidgetItem *Item,QString str)
{
	//����ĳһ�����οؼ��ڵ���ӽڵ�����ж�
	for ( int i=0 ; i<Item->childCount() ; i++ )
	{
		if ( Item->child(i)->text(0) == str )
			return true;
	}
	return false;

}

bool QtWordLib::IsSameRootTreeItemExist(QString str)
{
	//�������οؼ����ڵ�����ж�
	for ( int i=0 ; i<ui.treeWord->topLevelItemCount() ; i++ )
	{
		if ( ui.treeWord->topLevelItem(i)->text(0) == str )
			return true;
	}
	return false;
}