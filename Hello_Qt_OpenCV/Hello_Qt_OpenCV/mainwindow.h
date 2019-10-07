#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTranslator>

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
	void loadSettings();
	void saveSettings();
	QTranslator *chineseTranslator;

private slots:
	void on_inputPushButton_pressed();
	void on_outputPushButton_pressed();

	void on_actionChinese_triggered();
	void on_actionEnglish_triggered();

protected:
	void closeEvent(QCloseEvent * event);
	void changeEvent(QEvent *event);

};

#endif // MAINWINDOW_H
