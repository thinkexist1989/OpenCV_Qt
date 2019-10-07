#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FILTERS_SUBFOLDER "/filter_plugins/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getPluginsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getPluginsList()
{
    qDebug() << qApp->applicationDirPath();
    QDir filtersDir(qApp->applicationDirPath() + FILTERS_SUBFOLDER);
    QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach (QFileInfo filter, filters) {
        if(QLibrary::isLibrary(filter.absoluteFilePath())){
            QPluginLoader pluginLoader(filter.absoluteFilePath(), this);
            if(dynamic_cast<CvPluginInterface*>(pluginLoader.instance())){
                ui->filtersList->addItem(filter.fileName());
                pluginLoader.unload();
            }
            else {
                QMessageBox::warning(this, tr("Warning"),QString(tr("Make sure %1 is a corrent plugin for this application!")).arg(filter.fileName()));
            }
        }
        else {
            QMessageBox::warning(this,tr("Warning"),QString(tr("Make sure only plugins exist in plugins folder. %1 is not a plugin")).arg(filter.fileName()));
        }
    }

    if(ui->filtersList->count() <= 0){
        QMessageBox::critical(this, tr("No Plugins"), tr("This application cannot work without plugins!"));
        this->setEnabled(false);
    }

}

void MainWindow::on_inputImgButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Input Image"), QDir::currentPath(), tr("Image")+"(*.jpg *.png *.bmp)");
    if(QFile::exists(fileName)){
        ui->inputImgEdit->setText(fileName);
    }
}

void MainWindow::on_helpButton_pressed()
{
    if(ui->filtersList->currentRow() >= 0){
        QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if(plugin){
            QMessageBox::information(this, tr("Plugin Description"), plugin->description());
        }
        else {
            QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure %1 exists and is usable.")).arg(ui->filtersList->currentItem()->text()));
        }
    }
    else {
        QMessageBox::warning(this, tr("Warning"), QString(tr("Please select a filter plugin from the list")));
    }
}

void MainWindow::on_filterButton_pressed()
{
    if(ui->filtersList->currentRow() >= 0 && !ui->inputImgEdit->text().isEmpty()){
        QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if(plugin){
            if(QFile::exists(ui->inputImgEdit->text())){
                cv::Mat inpImage, outImage;
                inpImage = cv::imread(ui->inputImgEdit->text().toStdString());
                plugin->processImage(inpImage,outImage);
                cv::imshow(tr("Filtered Image").toStdString(),outImage);
            }
            else {
               QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure %1 exists.")).arg(ui->inputImgEdit->text()));
            }
        }
        else {
            QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure %1 exists and is usable.")).arg(ui->filtersList->currentItem()->text()));
        }
    }
    else {
        QMessageBox::warning(this, tr("Warning"), QString(tr("Please select a filter plugin from the list")));
    }
}
