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

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

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
    if(pixmap.load(file.absoluteFilePath())){
        ui->label->setPixmap(pixmap.scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else {
        QMessageBox::critical(this, tr("error"), tr("The image file cannot be read"));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(!pixmap.isNull()){
        ui->label->setPixmap(pixmap.scaled(ui->label->width()-5,ui->label->height()-5,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
