#include "OriginalCard.h"

OriginalCard::OriginalCard(QWidget* parent):
    QWidget(parent), expanded(false)
    {
        this-> setObjectName("OriginalCard");
        this-> setAttribute(Qt::WA_StyledBackground);
        this-> resize(200, 200);
    }

void OriginalCard::expand(void){
    this->resize(this->parentWidget()->width(), parentWidget()->height());
    onExpand();
    setExpanded(true);

}

void OriginalCard::return_(void){
    this-> resize(200, 200);
    onReturn();
    setExpanded(false);

}

void OriginalCard::setExpanded(bool value){
    expanded = value;
}

bool OriginalCard::getExpanded(void){
    return expanded;
}

void OriginalCard::mousePressEvent(QMouseEvent* event){
    if (event-> button() == Qt::LeftButton && getExpanded() != true){
        expand();
    }
}

void OriginalCard::mouseDoubleClickEvent(QMouseEvent* event){
    if( event->button() == Qt::LeftButton && getExpanded() == true){
        return_();
    }
}

void OriginalCard::resizeEvent(QResizeEvent* event){
    qDebug()<< "Resized widget: " << this->objectName();
    QWidget::resizeEvent(event);
}

void OriginalCard::onExpand(void){
    std::cout<<"\nonExpand()"<<std::endl;
}

void OriginalCard::onReturn(void){
    std::cout<<"\nonReturn()"<<std::endl;
}