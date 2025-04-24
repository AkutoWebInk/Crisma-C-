#include "OriginalCard.h"

OriginalCard::OriginalCard(QWidget* parent, std::vector<OriginalCard*>&cardsOnDisplay):
    QWidget(parent), cardsOnDisplay(cardsOnDisplay), expanded(false)
    {
        this-> setAttribute(Qt::WA_StyledBackground);
        this-> setFixedSize(200, 200);
        //this-> setObjectName("OriginalCard");  // OBS
        //this-> setCardIcon(nullptr);  // OBS
        /*
        OBS:
        When creating a new card for any new system feature:
        You only need to call setObjectName( ) and setCardIcon( ) and every other basic card behavior 
        (expansion, interaction with the GUI and etc...) will simply be inherited from this card, 
        simply override on_expand and on_return.
        */
    }


void OriginalCard::expand(void){
    iconLabel-> hide();
    hideOtherCards(cardsOnDisplay);
    this-> setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    this->resize(this->parentWidget()->width(), parentWidget()->height());
    onExpand();  //Call hooks to load insides
    setExpanded(true);  //Set flag to true
}

void OriginalCard::return_(void){
    this->setFixedSize(200, 200);
    this-> resize(200, 200);
    iconLabel-> show();
    onReturn();  //Call hooks to un-load inside widgets
    setExpanded(false);  //Set flag to false
    showOtherCards(cardsOnDisplay);

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
    QWidget::resizeEvent(event);
}

void OriginalCard::onExpand(void){
}

void OriginalCard::onReturn(void){
}

void OriginalCard::hideOtherCards(std::vector<OriginalCard*>& cardsOnDisplay) {
    for (int i = 0; i < cardsOnDisplay.size(); i++) {
        if(cardsOnDisplay[i]->objectName() != this->objectName()){
        cardsOnDisplay[i]->hide();
    }}
}

void OriginalCard::showOtherCards(std::vector<OriginalCard*>& cardsOnDisplay){
    for(int i=0; i< cardsOnDisplay.size(); i++){
        if(cardsOnDisplay[i]->objectName() != this->objectName()){
            cardsOnDisplay[i]->show();
        }
    }
}

void OriginalCard::setCardIcon(QString iconPath){
    cardIcon = QPixmap(iconPath).scaled(200,200,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    iconLabel = new QLabel(this);
    iconLabel-> setPixmap(cardIcon);
    iconLabel-> setFixedSize(200,200);
}