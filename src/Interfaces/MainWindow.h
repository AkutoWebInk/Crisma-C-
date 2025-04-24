#pragma once
#include <iostream>
#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include "OriginalCard.h"
#include "ItemCard.h"
#include "InventoryCard.h"


class MainWindow : public QMainWindow{
    Q_OBJECT

    private:
        QFrame *backgroundFrame;
        QGridLayout *backgroundLayout ;
        
        std::vector<OriginalCard*> cardsOnDisplay;

    public:
        MainWindow(QWidget* parent=nullptr);
        void loadCards(std::vector<OriginalCard*> &cardsOnDisplay);
        void initializeBackground(void); 
};



