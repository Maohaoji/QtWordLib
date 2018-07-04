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
    popMenu->addAction(new QAction("���", this));
    popMenu->addAction(new QAction("ɾ��", this));
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //�����item�����"�޸�"�˵� [1]*
    {
        popMenu->addAction(new QAction("�޸�", this));
    }
    
    popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}
