#pragma once
#include "qlistwidget.h"
#include "qmenu.h"
#include "qaction.h"
class QMenuListWidget :
	public QListWidget
{
public:
	QMenuListWidget(QWidget *parent = (QWidget*)0);
	virtual ~QMenuListWidget(void);
	virtual void contextMenuEvent ( QContextMenuEvent * event );
};

