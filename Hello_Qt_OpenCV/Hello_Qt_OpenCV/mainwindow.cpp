#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	loadSettings();
	chineseTranslator = new QTranslator(this);
	chineseTranslator->load(":/translations/hello_qt_opencv_zh.qm");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_inputPushButton_pressed()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Input Image"),
		QDir::currentPath(),
		tr("Images (*.jpg *.png, *.bmp)"));
	if (QFile::exists(fileName)) {
		ui->inputLineEdit->setText(fileName);
	}
}

void MainWindow::loadSettings()
{
	QSettings settings("org", "Hello_Qt_OpenCV", this);
	ui->inputLineEdit->setText(settings.value("inputLineEdit", "").toString());
	ui->outputLineEdit->setText(settings.value("outputLineEdit", "").toString());
	ui->gaussianBlurRadioButton->setChecked(settings.value("gaussianBlurRadioButton", false).toBool());
	ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton", true).toBool());
	ui->displayImageCheckBox->setChecked(settings.value("displayImageCheckBox", false).toBool());
}

void MainWindow::saveSettings()
{
	QSettings settings("org", "Hello_Qt_OpenCV", this);
	settings.setValue("inputLineEdit", ui->inputLineEdit->text());
	settings.setValue("outputLineEdit", ui->outputLineEdit->text());
	settings.setValue("gaussianBlurRadioButton", ui->gaussianBlurRadioButton->isChecked());
	settings.setValue("medianBlurRadioButton", ui->medianBlurRadioButton->isChecked());
	settings.setValue("displayImageCheckBox", ui->displayImageCheckBox->isChecked());
}

void MainWindow::on_outputPushButton_pressed()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Select Output Image"),
		QDir::currentPath(),
		"*.jpg;;*.png;;*.bmp");
	if (!fileName.isEmpty()) {
		ui->outputLineEdit->setText(fileName);
		cv::Mat inpImg, outImg;
		inpImg = cv::imread(ui->inputLineEdit->text().toStdString());
		if (ui->medianBlurRadioButton->isChecked())
			cv::medianBlur(inpImg, outImg, 5);
		else if (ui->gaussianBlurRadioButton->isChecked())
			cv::GaussianBlur(inpImg, outImg, cv::Size(5, 5), 1.25);
		cv::imwrite(fileName.toStdString(), outImg);
		if (ui->displayImageCheckBox->isChecked())
			cv::imshow(tr("Output Image").toStdString(), outImg);
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	int result = QMessageBox::warning(this,
		tr("Exit"),
		tr("Are you sure you want to close this program?"),
		QMessageBox::Yes,
		QMessageBox::No);

	if (result == QMessageBox::Yes) {
		saveSettings();
		event->accept();
	}
	else {
		event->ignore();
	}
}

void MainWindow::changeEvent(QEvent * event)
{
	if (event->type() == QEvent::LanguageChange) {
		ui->retranslateUi(this);
	}
	else {
		QMainWindow::changeEvent(event);
	}
}

void MainWindow::on_actionChinese_triggered()
{
	qApp->installTranslator(chineseTranslator);
}

void MainWindow::on_actionEnglish_triggered()
{
	qApp->removeTranslator(chineseTranslator);
}
