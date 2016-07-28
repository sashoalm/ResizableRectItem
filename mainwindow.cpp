#include "mainwindow.h"
#include "resizablerectitem.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600);
    QGraphicsRectItem *item = new ResizableRectItem(QRectF(0, 0, 100, 80));
    scene->addItem(item);
    item->setPos(100, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
