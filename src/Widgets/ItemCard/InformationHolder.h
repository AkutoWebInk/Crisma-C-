#pragma once
#include <QtWidgets>

class InformationHolder: public QWidget{
    Q_OBJECT

    private:
    QString name;
    QString reference;
    QString code;
    QString line;
    double capacity;
    int quantity;
   
    QLabel* itemImage;
    QLabel* itemName;
    QLabel* itemReference;
    QLabel* itemCode;
    QLabel* itemLine;
    QLabel* itemCapacity;
    QLabel* itemQuantity;

    public:
    InformationHolder(const QString& name, const QString& reference, const QString& code, const QString& line, double capacity, int quantity, QWidget* parent=nullptr);
    QLabel* QTextLabel(const QString& labelText, const QString& objectName);
    QLabel* QImageLabel(const QString& path, const QString& objectName, int imgWidth, int imgHeight);
};