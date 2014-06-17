#include <QProcess>
#include <QWheelEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"

#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), 
	ui(new Ui::MainWindow) {

	ui->setupUi(this);

	highlighter = new Highlighter(ui->textEdit->document());
	connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(Run()));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(HideShowOutput()));
	ui->textEdit_2->setHidden(true);
}

bool output_hidden = true;
void MainWindow::HideShowOutput() {
	ui->textEdit_2->setHidden( output_hidden = !output_hidden );
}

void MainWindow::wheelEvent(QWheelEvent *event) {
	double degrees = event->delta() / 50.0;
	if (event->modifiers().testFlag(Qt::ControlModifier)) {
			ui->textEdit->zoomIn(degrees);
	}
	event->accept();
}

void MainWindow::Run() {
	QByteArray bytes = ui->textEdit->toPlainText().toLocal8Bit();
	QProcess proc;
	proc.start("./erun");
	proc.waitForStarted();
	proc.write(bytes.data(), bytes.size());
	proc.closeWriteChannel();
	proc.waitForFinished(3000);
	bytes = proc.readAll();
	ui->textEdit_2->append(bytes);
	if (output_hidden == true) {
		HideShowOutput();
	}
}

MainWindow::~MainWindow() {
	delete ui;
}
