#include "InformationHolder.h"

InformationHolder::InformationHolder(const QString& name, const QString& reference, const QString& code, const QString& line, double capacity, int quantity, QWidget* parent):
name(name),
reference(reference),
code(code),
line(line),
capacity(capacity),
quantity(quantity){

// Class settings
this-> setObjectName("ItemCard_InformationHolder");
this-> setAttribute(Qt::WA_TransparentForMouseEvents);

//Load Layout
QGridLayout* gridLayout = new QGridLayout(this);
gridLayout->setVerticalSpacing(1);  // Reduce vertical gap between rows
gridLayout->setHorizontalSpacing(1); // Optional: Adjust horizontal gap

// Labels
QLabel* itemName = QTextLabel(name, "itemName");
QLabel* itemReference = QTextLabel( reference, "itemReference");
QLabel* itemCode = QTextLabel(code, "itemCode");
QLabel* itemLine = QTextLabel(line, "itemLine");
QLabel* itemCapacity = QTextLabel(QString::number(capacity), "itemCapacity");
QLabel* itemQuantity = QTextLabel(QString::number(quantity), "itemQuantity");

// Layout
gridLayout-> addWidget(itemName, 0, 0, 1,2, Qt::AlignHCenter);
gridLayout-> addWidget(itemReference, 1, 0, 1,2, Qt::AlignLeft);
gridLayout-> addWidget(itemCode, 2, 0, 1,2,Qt::AlignLeft);
gridLayout-> addWidget(itemLine, 3, 0, 1,2,Qt::AlignLeft);
gridLayout-> addWidget(itemCapacity, 4, 0, 1,2, Qt::AlignLeft);
gridLayout-> addWidget(itemQuantity, 5,0, 1,2, Qt::AlignLeft);

setLayout(gridLayout);
}

QLabel* InformationHolder::QTextLabel(const QString& labelText, const QString& objectName){
    
    QLabel* label = new QLabel(this);
    label-> setText(labelText);
    label-> setObjectName("ItemCard_" + objectName);
    return label;
}

QLabel* InformationHolder::QImageLabel(const QString& path, const QString& objectName, int imgWidth, int imgHeight){
    //Load the image:
    QPixmap image(path);
    image = image.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // Create the label and set the image inside it
    QLabel* label= new QLabel(this);
    label-> setPixmap(image);
    label-> setObjectName("ItemCard_"+objectName);
    return label;
}
