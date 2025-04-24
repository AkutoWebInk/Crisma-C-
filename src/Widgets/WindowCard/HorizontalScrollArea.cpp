#include "HorizontalScrollArea.h"

HorizontalScrollArea::HorizontalScrollArea(QWidget *parent) : QScrollArea(parent) 
    {
        this-> setObjectName("HorizontalScrollArea");
    }

    void HorizontalScrollArea::wheelEvent(QWheelEvent *event) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - event->angleDelta().y() / 2);
        event->accept();
    }
    