#pragma once

#include <QScrollArea>
#include <QWheelEvent>
#include <QScrollBar>

class HorizontalScrollArea : public QScrollArea {
    Q_OBJECT

public:
    explicit HorizontalScrollArea(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};
