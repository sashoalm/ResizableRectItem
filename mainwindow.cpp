#include "mainwindow.h"
#include "resizablerectitem.h"
#include "resizablerectitemsettings.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600);

    QBrush brush(QColor(255, 0, 0, 255/3));
    ResizableRectItemSettings *settings = new ResizableRectItemSettings(
                15, QSizeF(30, 30), QSizeF(200, 200),
                Qt::DashLine, brush);

    // Add item without rotation.
    ResizableRectItem *item = new ResizableRectItem(QRectF(QPointF(10, 20), QPointF(210, 120)), settings);
    item->setBrush(brush);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos(100, 100);    
    new QGraphicsTextItem("Foo", item);

    // Add item with 45 degrees rotation.
    item = new ResizableRectItem(QRectF(QPointF(10, 20), QPointF(210, 120)), settings);
    item->setBrush(brush);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos(100, 200);
    new QGraphicsTextItem("Foo", item);
    item->setTransform(QTransform().rotate(45));
}

MainWindow::~MainWindow()
{
    delete ui;
}
