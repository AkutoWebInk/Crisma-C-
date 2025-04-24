#pragma once
#include "OriginalCard.h"
#include "ItemCard.h"
#include "HorizontalScrollArea.h"

class InventoryCard: public OriginalCard{
    Q_OBJECT

    private:
        QHBoxLayout *contentsLayout;
        QWidget *contentsHolder;
        QGridLayout *cardLayout;
        HorizontalScrollArea *scrollArea;
        QGridLayout *layout;
        
    protected:
        void onExpand() override;
        void onReturn() override;


    public:
    InventoryCard(QWidget* parent, std::vector<OriginalCard*>& cardsOnDisplay);
    void initializeScrollArea(void);
    void loadItemInventory(void);
};