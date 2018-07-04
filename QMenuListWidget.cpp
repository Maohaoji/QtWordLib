#include "QMenuListWidget.h"


QMenuListWidget::QMenuListWidget(QWidget *parent):QListWidget(parent)
{
}


QMenuListWidget::~QMenuListWidget(void)
{
}

void QMenuListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
    QMenu* popMenu = new QMenu(this);
    popMenu->addAction(new QAction("添加", this));
    popMenu->addAction(new QAction("删除", this));
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //如果有item则添加"修改"菜单 [1]*
    {
        popMenu->addAction(new QAction("修改", this));
    }
    
    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}
