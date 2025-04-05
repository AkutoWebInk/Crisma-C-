#include "MainWindow.h"
#include "OriginalCard.h"
#include <QToolBar>
#include <QMenuBar>
#include <QGridLayout>
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent): 
    QMainWindow(parent)
    {
        this-> setObjectName("Main_Window");
        this-> setWindowTitle("AKT Manager");
        this-> resize(1360,420);
        this-> setMinimumSize(900, 400);
        
        QWidget* backgroud = new QWidget(this);
        
        OriginalCard* originalCard = new OriginalCard(backgroud);

        setCentralWidget(backgroud);
    }

