#pragma once
#include <iostream>
#include <QtWidgets>
#include <QMouseEvent>


class OriginalCard : public QWidget{
    Q_OBJECT

    private:
    QPixmap cardIcon;
    QLabel *iconLabel;
    bool expanded;
    std::vector<OriginalCard*>& cardsOnDisplay; // Store a reference

    protected:
    virtual void onExpand(void);
    virtual void onReturn(void);

    public:
    OriginalCard(QWidget* parent, std::vector<OriginalCard*>& cardsOnDisplay);

    void expand(void);
    void return_(void);
    
    void setExpanded(bool value);
    bool getExpanded(void);
   
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    
    void resizeEvent(QResizeEvent* event);

    void hideOtherCards(std::vector<OriginalCard*>& cardsOnDisplay);
    void showOtherCards(std::vector<OriginalCard*>& cardsOnDisplay);
    void setCardIcon(QString iconPath);
};