#pragma once

#include <ignition/transport.hh>
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
  ignition::transport::Node node;
  Ui::MainWindow *ui;
};
