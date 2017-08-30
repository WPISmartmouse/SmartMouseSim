#include <QApplication>
#include <QWidget>

#include "main.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(on_exit()));
  connect(ui->play_button, SIGNAL(clicked()), this, SLOT(play()));
  connect(ui->pause_button, SIGNAL(clicked()), this, SLOT(pause()));

  world_control_pub = node.Advertise<ignition::msgs::WorldControl>("world_control");
  node.Subscribe("world_control", &MainWindow::on_world_control, this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_exit() {
  QApplication::quit();
}

void MainWindow::play() {
  ignition::msgs::WorldControl play_msg;
  play_msg.set_pause(false);
  world_control_pub.Publish(play_msg);
}

void MainWindow::pause() {
  ignition::msgs::WorldControl pause_msg;
  pause_msg.set_pause(true);
  world_control_pub.Publish(pause_msg);
}

void MainWindow::on_world_control(const ignition::msgs::WorldControl &msg) {
  std::cout << msg.DebugString() << std::endl;
}

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  MainWindow window;

  window.setWindowTitle("SmartMouse Simulator");
  window.show();

  return app.exec();
}

