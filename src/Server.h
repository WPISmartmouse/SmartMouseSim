#pragma once

#include <thread>
#include <ignition/transport/Node.hh>

class Server {

 public:
  void start();

  std::thread *thread;
  void RunLoop();

  void Step();

  void join();
 private:
  void OnWorldControl(const ignition::msgs::WorldControl &msg);

  ignition::transport::Node *node_ptr_;
  ignition::transport::Node::Publisher world_stats_pub;
  google::protobuf::uint64 iterations_ = 0UL;
  std::mutex physics_mutex;
  bool pause_;
  bool quit_;
};
