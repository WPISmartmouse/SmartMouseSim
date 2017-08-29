#pragma once

#include <QWidget>
#include <QtWidgets/QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
  MainWindow(QMainWindow *parent = 0);

  virtual ~MainWindow();

private slots:
  void on_exit();

private:
  Ui::MainWindow *ui;
};
