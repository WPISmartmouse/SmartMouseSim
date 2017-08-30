#include <QApplication>
#include <QWidget>
#include <getopt.h>

#include "main.h"
#include "ui_mainwindow.h"
#include "Server.h"

void PrintVersionInfo();

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));
  connect(ui->play_button, SIGNAL(clicked()), this, SLOT(Play()));
  connect(ui->pause_button, SIGNAL(clicked()), this, SLOT(Pause()));

  world_control_pub = node.Advertise<ignition::msgs::WorldControl>("world_control");
  node.Subscribe("world_control", &MainWindow::OnWorldControl, this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::OnExit() {
  ignition::msgs::WorldControl quit_msg;
  quit_msg.set_quit(true);
  world_control_pub.Publish(quit_msg);
  QApplication::quit();
}

void MainWindow::Play() {
  ignition::msgs::WorldControl play_msg;
  play_msg.set_pause(false);
  world_control_pub.Publish(play_msg);
}

void MainWindow::Pause() {
  ignition::msgs::WorldControl pause_msg;
  pause_msg.set_pause(true);
  world_control_pub.Publish(pause_msg);
}

void MainWindow::OnWorldControl(const ignition::msgs::WorldControl &msg) {
  std::cout << msg.DebugString() << std::endl;
}

int main(int argc, char *argv[]) {
  int c;

  while (1) {
    c = getopt_long(argc, argv, "-v", nullptr, nullptr);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
      case 'v':PrintVersionInfo();
        return EXIT_SUCCESS;
      case '?':break;
      default:abort();
    }
  }

  // Start physics thread
  Server server;
  server.start();

  QApplication app(argc, argv);

  MainWindow window;

  window.setWindowTitle("SmartMouse Simulator");
  window.show();

  int ret_code = app.exec();

  server.join();

  return ret_code;
}

void PrintVersionInfo() {
  printf("SmartmouseSim v 0.0.0\n");
}

