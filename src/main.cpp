#include "MainWindow.h"
#include "mainFileFunctions.h"
#include "ItemCard.h"
#include "OriginalCard.h"

int main(int argc, char* argv[]) {
    
    QApplication app(argc, argv);
    MainWindow mainWindow;
    loadQtStyleSheet(":/styles/dark");




    mainWindow.show();
    return app.exec();
}
