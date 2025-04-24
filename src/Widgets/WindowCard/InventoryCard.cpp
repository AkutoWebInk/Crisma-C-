#include "InventoryCard.h"

InventoryCard::InventoryCard(QWidget* parent, std::vector<OriginalCard*>& cardsOnDisplay):
    OriginalCard(parent, cardsOnDisplay)
{
    this-> setObjectName("InventoryCard");                   //Identity used in QSS
    this-> setCardIcon("programIcons/BlueBox.png");  // card icon path

    cardLayout = new QGridLayout(this);  
    this-> setLayout(cardLayout);
    
    contentsHolder = new QWidget(nullptr);                  // central widget inside the scrollable area
    contentsHolder-> setObjectName("scrollAreaBackground"); 
    contentsHolder-> setMinimumWidth(2000);             // just setting a base width so it doesn't initialize at 0.
    contentsLayout = new QHBoxLayout(contentsHolder); // Setting a layout to it

    initializeScrollArea(); // initialized the scrollable area and keep it hidden until the card is selected and expands
    loadItemInventory(); // loads the item inventory on program launch and delivers it with no delay once the card is expanded 



}

void InventoryCard::onExpand(void) {
    scrollArea->show(); 
};

void InventoryCard::onReturn(void) { 
    scrollArea->hide();    
};

void InventoryCard::initializeScrollArea(void){
    scrollArea = new HorizontalScrollArea(this); //creates the object.
    scrollArea-> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // removes the vertical scrollbar
    scrollArea-> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea-> setWidget(contentsHolder); // set the contents holder widget to be the main widget inside the scrollable area
    cardLayout-> addWidget(scrollArea); // adds the scroll area inside the InventoryCard
    scrollArea-> hide(); //Keep it hidden until the card expands
};

void InventoryCard::loadItemInventory(void){
    //for now is a simple for loop of the same item just to populate the scrollable area  but later will receive the list returned by the CRUDE
    for(int i=0; i<15; i++){
        ItemCard* card = new ItemCard(i, "Nikon XPCO", "Ref: 90283", "Code: 21x12AB", "Line: STEEL ", 100.0, i, "src/Database/Items/image_64.jpg");
        contentsLayout-> addWidget(card);
    }
    contentsHolder-> adjustSize(); 
}