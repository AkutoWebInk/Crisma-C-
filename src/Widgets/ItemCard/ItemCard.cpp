#include "ItemCard.h"



// Constructor to pass values on initialization:
ItemCard::ItemCard(int id, const QString& name, const QString& reference, const QString& code, const QString& line, double capacity, int quantity,  const QString& imagepath, QWidget* parent):
QWidget(parent), id(id), name(name), reference(reference), code(code), line(line), capacity(capacity), quantity(quantity), imagepath(imagepath)
{
this-> setObjectName("ItemCard");
this-> setFixedSize(300, 400);
this-> setAttribute(Qt::WA_StyledBackground);
this-> setAttribute(Qt::WA_Hover);

QGridLayout* gridLayout = new QGridLayout(this);
gridLayout->setVerticalSpacing(1);  // Reduce vertical gap between rows
gridLayout->setHorizontalSpacing(1); // Optional: Adjust horizontal gap


Transparent2DLayer* transparentLayer = new Transparent2DLayer(imagepath, this);
InformationHolder *itemInformation = new InformationHolder(name, reference, code, line, capacity, quantity, this);

gridLayout-> addWidget(transparentLayer, 0,0, 1,2, Qt::AlignHCenter);
gridLayout-> addWidget(itemInformation, 1,0, 1,2, Qt::AlignBottom); 

setLayout(gridLayout);
}
