
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

namespace Ui {
	class MainWindow;
};

class Highlighter;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();
private slots:
	void Run();
	void wheelEvent(QWheelEvent *event);
	void HideShowOutput();
private:
	Ui::MainWindow *ui;
	Highlighter *highlighter;
};


#endif
