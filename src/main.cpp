#include <QApplication>
#include <QWidget>

#include "main.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  MainWindow window;

  window.setWindowTitle("Simple example");
  window.show();

  return app.exec();
}

