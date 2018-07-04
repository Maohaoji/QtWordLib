#include "qtwordlib.h"

#pragma execution_character_set("utf-8")

QtWordLib::QtWordLib(QWidget *parent)
	: QMainWindow(parent)
{
	nRet=0;

	ui.setupUi(this);
	ui.treeWord->setColumnCount(1); //设置列数
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
	//获得节点路径
	QString strSearch = Item->text(0);
	QTreeWidgetItem *ItemParent = Item->parent();
	while (ItemParent)
	{
		strSearch = ItemParent->text(0) + QString("/") + strSearch;
		ItemParent = ItemParent->parent();
	}
	vector<QString> strlist;
	XmlOp.QueryAttribute(strSearch,strlist);         //查询对应节点属性
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
	m_Action1 = new QAction("添加语句", ui.listWordItem);
	m_Action2 = new QAction("修改语句", ui.listWordItem);
	m_Action3 = new QAction("删除语句", ui.listWordItem);
	m_Action4 = new QAction("上移语句", ui.listWordItem);
	m_Action5 = new QAction("下移语句", ui.listWordItem);

	//选中列表某一项就跳出1、2、3，否则只跳出1
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
	
	popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
	
}

void QtWordLib::ShowTreeMenu(QPoint pt)
{
	QTreeWidgetItem *its = ui.treeWord->itemAt(pt);
	QMenu* popTMenu = new QMenu(ui.treeWord);
	m_TAction1 = new QAction("添加分支", ui.treeWord);
	m_TAction2 = new QAction("修改项", ui.treeWord);
	m_TAction3 = new QAction("删除项", ui.treeWord);
	m_TAction4 = new QAction("添加根分支",ui.treeWord);

	//选中树控件某一项则跳1、2、3，否则跳4
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
	popTMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}

void QtWordLib::on_menu_delListItem()
{
	//QListWidgetItem *its = ui.listWordItem->currentItem();
	QListWidgetItem *its = ui.listWordItem->takeItem(ui.listWordItem->currentRow());

	if ( its == NULL )
	{
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//QString strAttrName;

	//获得节点路径，查询节点
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

	ui.listWordItem->removeItemWidget(its);//删除对应项
	delete its;
	//XmlOp.QueryAttributeNamebyValue(ele,its->text(),strAttrName);      //从属性值搜索属性名，程序默认无属性值相同的属性！
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
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//获得节点路径，查询节点
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
	if ( IsSameWordExist(dlg.m_strAttr) )           //有相同语句不添加
	{
		QMessageBox a(QString("提示"),QString("已有相同词句！"),QMessageBox::Warning,1,1,1,this);
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
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//获得节点路径，查询节点
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
	//XmlOp.QueryAttributeNamebyValue(ele,its->text(),strAttrName);      //从属性值搜索属性名，程序默认无属性值相同的属性！
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

void QtWordLib::on_menu_upListItem()                             //上移词句
{
	QListWidgetItem *its = ui.listWordItem->currentItem();
	if ( its == NULL )
	{
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	if ( ui.listWordItem->currentRow() <= 0 )
	{
		//QMessageBox a(QString("提示"),QString("无法上移！"),QMessageBox::Warning,1,1,1,this);
		//a.exec();
		return;
	}

	//获得节点路径，查询节点
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

void QtWordLib::on_menu_downListItem()                           //下移词句
{
	QListWidgetItem *its = ui.listWordItem->currentItem();
	if ( its == NULL )
	{
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	if ( ui.listWordItem->currentRow() >= ui.listWordItem->count()-1 )
	{
		//QMessageBox a(QString("提示"),QString("无法下移！"),QMessageBox::Warning,1,1,1,this);
		//a.exec();
		return;
	}

	//获得节点路径，查询节点
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
	ui.textEditResult->setText(Item->text());          //显示于结果文本框中
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
	if ( IsSameRootTreeItemExist(dlg.m_strAttr) )         //判断是否有相同名称的根节点子项
	{
		QMessageBox a(QString("提示"),QString("已有相同项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	
	//添加根节点子项
	QTreeWidgetItem *newItem = new QTreeWidgetItem(ui.treeWord,QStringList(dlg.m_strAttr));
	XmlOp.AddRootElement(dlg.m_strAttr);
	XmlOp.Save();
}

void QtWordLib::on_menu_addTreeItem()
{
	QTreeWidgetItem *Item = ui.treeWord->currentItem();
	if ( Item == NULL )
	{
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	QtAttrDlg dlg;
	int nRet = dlg.exec();
	if ( !nRet )
		return;

	if ( IsSameTreeItemExist(ui.treeWord->currentItem(),dlg.m_strAttr) )          //判断是否有名称相同的子节点
	{
		QMessageBox a(QString("提示"),QString("已有相同项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//添加树节点
	QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList(dlg.m_strAttr));
	Item->addChild(newItem);

	//获取xml节点路径，并在对应节点添加子节点
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
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}
	QtAttrDlg dlg;
	dlg.SetEditText(Item->text(0));
	int nRet = dlg.exec();
	if ( !nRet )
		return;

	//获取xml节点路径，并在对应节点修改名称
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
		
		QMessageBox a(QString("提示"),QString("未选中项！"),QMessageBox::Warning,1,1,1,this);
		a.exec();
		return;
	}

	//获取xml节点路径，并删除对应节点
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
	else        //根节点的子节点情况
	{
		this->ui.treeWord->removeItemWidget(Item,0);
		delete Item;
	}
	XmlOp.Save();
}

bool QtWordLib::IsSameWordExist(QString str)
{
	//遍历list进行判断
	for ( int i=0 ; i<ui.listWordItem->count(); i++ )
	{
		if ( str == ui.listWordItem->item(i)->text() )
			return true;
	}
	return false;
}

bool QtWordLib::IsSameTreeItemExist(QTreeWidgetItem *Item,QString str)
{
	//遍历某一个树形控件节点的子节点进行判断
	for ( int i=0 ; i<Item->childCount() ; i++ )
	{
		if ( Item->child(i)->text(0) == str )
			return true;
	}
	return false;

}

bool QtWordLib::IsSameRootTreeItemExist(QString str)
{
	//遍历树形控件根节点进行判断
	for ( int i=0 ; i<ui.treeWord->topLevelItemCount() ; i++ )
	{
		if ( ui.treeWord->topLevelItem(i)->text(0) == str )
			return true;
	}
	return false;
}