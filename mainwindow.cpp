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
    scene->addItem(new ResizableRectItem(QRectF(100, 100, 200, 180)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
