#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfoList>
#include <QMessageBox>
#include <QPluginLoader>


#include <opencv2/opencv.hpp>
#include <cvplugininterface.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputImgButton_pressed();

    void on_helpButton_pressed();

    void on_filterButton_pressed();

private:
    Ui::MainWindow *ui;

    void getPluginsList();
};

#endif // MAINWINDOW_H
