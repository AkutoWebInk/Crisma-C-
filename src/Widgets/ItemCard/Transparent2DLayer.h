#pragma once
#include <QtWidgets>
#include <iostream>
#include <QMouseEvent>

class Transparent2DLayer : public QWidget{
    Q_OBJECT
    
    private:
    QWidget *parent;
    QString itemImagePath;
    QGraphicsRectItem *rectangleItem;
    QGraphicsRotation *xAxis;
    QGraphicsRotation *yAxis;
    QGraphicsRotation *zAxis;
    float zAngle = 0.0f;
    


    public:
    Transparent2DLayer(const QString& itemImagePath, QWidget *parent=nullptr);
    void mouseMoveEvent(QMouseEvent* event);
};