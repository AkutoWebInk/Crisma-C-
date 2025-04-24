#include "Transparent2DLayer.h"

Transparent2DLayer::Transparent2DLayer(const QString& itemImagePath, QWidget *parent) : 
    QWidget(parent), itemImagePath(itemImagePath)
{   
    this-> setObjectName("ItemCard_Transparent2DLayer");      
    this-> setFixedSize(300, 410);                                                     
    this-> setAttribute(Qt::WA_StyledBackground);                       
    this-> setAttribute(Qt::WA_Hover);                                            
    this-> setMouseTracking(true);

    QGraphicsScene *Scene = new QGraphicsScene(this);            
    QGraphicsView *View = new QGraphicsView(Scene, this);
   
    View-> setObjectName("Transparent2DLayer_View");
    View-> setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); 
    View-> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View-> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); 
    View-> setAttribute(Qt::WA_TransparentForMouseEvents);
    View-> setGeometry(0,0, 300, 300);
    View-> show();

    QGraphicsRectItem *rectangleItem = new QGraphicsRectItem (-125,-125, 250 , 250);    
    rectangleItem-> setTransformOriginPoint(rectangleItem-> boundingRect().center());
    rectangleItem-> setPen(Qt::NoPen);


    QPixmap itemIMG(itemImagePath);
    QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(itemIMG, rectangleItem);
   
    imageItem->setTransformationMode(Qt::SmoothTransformation);  // Smooth scaling
    imageItem->setScale(250 / itemIMG.width());  // Fit inside rectangle
    imageItem->setPos(-125, -125);  // Align with rectangle's position

    Scene-> addItem(rectangleItem);

    xAxis = new QGraphicsRotation;
    yAxis = new QGraphicsRotation;
    zAxis = new QGraphicsRotation;

    xAxis-> setAxis(Qt::XAxis);
    yAxis-> setAxis(Qt::YAxis);
    zAxis->setAxis(Qt::ZAxis);
    
    rectangleItem->setTransformations({xAxis, yAxis, zAxis});
}

void Transparent2DLayer::mouseMoveEvent(QMouseEvent* event){
    float deltaX = event->pos().x() - (this->width()/2);  
    float deltaY = event->pos().y() - (this->height()/2); 
    float x = (deltaX / 10) * 1.8f;
    float y = -(deltaY / 10) * 1.2f;

    float smoothFactor = 0.05f; 
    float targetZ = (std::abs(x) + std::abs(y)) * smoothFactor * (x > 0 ? 3.0f : -3.0f);

    // Interpolation to prevent sudden jumps
    float interpSpeed = 0.02f; // Lower value for smoother movement
    
    zAngle += (targetZ - zAngle) * interpSpeed;
    zAxis->setProperty("angle", zAngle);
    xAxis->setProperty("angle", y);
    yAxis->setProperty("angle", x);

    //std::cout << "X: " << x << " Y: " << y << " Z: " << zAngle << std::endl;
}


