#include <mainFIleFunctions.h>

void loadQtStyleSheet(const QString& path){
    QFile styleFile(path);
    if(styleFile.open(QFile::ReadOnly)){
        qApp->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
}
