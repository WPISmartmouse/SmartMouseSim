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

//private slots:
//  void on_inputSpinBox1_valueChanged(int value);
//  void on_inputSpinBox2_valueChanged(int value);

private:
  Ui::MainWindow *ui;
};
