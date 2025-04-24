    #include "MainWindow.h"

    MainWindow::MainWindow(QWidget* parent): 
        QMainWindow(parent)
        {
            this-> setObjectName("MainWindow");
            this-> setWindowTitle("AKT Manager");
            this-> resize(1360,600);
            this-> setMinimumSize(900, 600);
            this-> initializeBackground(); 

            // QDocker
            QDockWidget *docker = new QDockWidget("Docker", this);
            QWidget *dockerWidget = new QWidget(nullptr);
            dockerWidget-> setObjectName("Docker");
            docker-> setObjectName("Docker");
            docker-> setMinimumSize(200,130);
            docker-> setWidget(dockerWidget);

            QMainWindow::addDockWidget(Qt::LeftDockWidgetArea, docker);



            //Cards on Screen
            cardsOnDisplay = {
                new InventoryCard(backgroundFrame, cardsOnDisplay)
            };
            loadCards(cardsOnDisplay);
        }

void MainWindow::loadCards(std::vector<OriginalCard*> &cardsOnDisplay){
    for(int i=0; i<cardsOnDisplay.size(); i++){
        backgroundLayout-> addWidget(cardsOnDisplay[i]);
        std::cout << cardsOnDisplay[i]->objectName().toStdString() << " -> added to screen\n" << std::endl;
    }
};

void MainWindow::initializeBackground(void){
        // loads the widget that serves as background  and set a layout:
        backgroundFrame = new QFrame(this);
        backgroundLayout = new QGridLayout(backgroundFrame);
        backgroundFrame-> setLayout(backgroundLayout);
        this-> setCentralWidget(backgroundFrame);
};