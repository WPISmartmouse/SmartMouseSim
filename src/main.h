#pragma once
#include <time.h>

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

  void OnExit();

  void Play();

  void Pause();

  void ShowSourceCode();

  void ShowWiki();

private:
  void OnWorldControl(const ignition::msgs::WorldControl &msg);

  ignition::transport::Node node;
  Ui::MainWindow *ui;
  ignition::transport::Node::Publisher world_control_pub;
};
