#include "MainWindow.h"
#include "mainFileFunctions.h"
#include "ItemCard.h"
#include "OriginalCard.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    loadQtStyleSheet(":/styles/dark");


    //OriginalCard* Card = new OriginalCard(static_cast<QWidget*>(&mainWindow));
    
    //ItemCard* testCard = new ItemCard(1, "Nikon XPCO", "Ref: 90283", "Code: 21x12AB", "Line: STEEL ", 100.0, 10, "src/Database/Items/image_64.jpg");


    //mainWindow.setCentralWidget(testCard);

    mainWindow.show();  

    return app.exec();
}