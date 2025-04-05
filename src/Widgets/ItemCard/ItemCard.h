#pragma once
#include <iostream>
#include <QtWidgets>
#include <QMouseEvent>
#include "InformationHolder.h"
#include "Transparent2DLayer.h"


class ItemCard : public QWidget{
    Q_OBJECT

    private:
    // Infos:
    int id;
    QString name;
    QString reference;
    QString code;
    QString line;
    double capacity;
    int quantity;
    QString imagepath;
    Transparent2DLayer* transparentLayer;
    InformationHolder *itemInformation;
    public:
    ItemCard(int id, const QString& name, const QString& reference, const QString& code, const QString& line, double capacity, int quantity,  const QString& imagepath, QWidget* parent=nullptr);

};
