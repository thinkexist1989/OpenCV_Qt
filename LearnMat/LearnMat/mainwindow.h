#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = nullptr);
~MainWindow();

private:
Ui::MainWindow *ui;

QPixmap pixmap;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
