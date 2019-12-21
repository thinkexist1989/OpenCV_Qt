#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>

#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QMessageBox>
#include <QResizeEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setAcceptDrops(true);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setScene(&scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList acceptedFileTypes;
    acceptedFileTypes <<"jpg" << "png" << "bmp";

    if(event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1){
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if(acceptedFileTypes.contains(file.suffix().toLower())){
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
    QPixmap pixmap;
    if(pixmap.load(file.absoluteFilePath())){
        //scene.addPixmap(pixmap);
        scene.clear();
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        scene.addItem(item);
        qDebug() <<scene.items().count();

        scene.addEllipse(-100.0, 100.0, 200.0, 100.0,
                         QPen(QBrush(Qt::SolidLine), 2.0),
                         QBrush(Qt::Dense2Pattern));
        QVector<QPoint> points;
        points.append(QPoint(150, 250));
        points.append(QPoint(250, 250));
        points.append(QPoint(165, 280));
        points.append(QPoint(150, 250));
        scene.addPolygon(QPolygon(points));


    }
    else {
        QMessageBox::critical(this, tr("error"), tr("The image file cannot be read"));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
//    if(!pixmap.isNull()){
//        ui->label->setPixmap(pixmap.scaled(ui->label->width()-5,ui->label->height()-5,Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    }
}
