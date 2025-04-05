#pragma once
#include <iostream>
#include <QtWidgets>
#include <QMouseEvent>


class OriginalCard : public QWidget{
    Q_OBJECT

    private:
    bool expanded;

    
    public:
    OriginalCard(QWidget* parent);

    void expand(void);
    void return_(void);
    void setExpanded(bool value);
    bool getExpanded(void);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
    void onExpand(void);
    void onReturn(void);

};