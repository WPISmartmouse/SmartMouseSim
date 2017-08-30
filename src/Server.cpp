#include "Server.h"
#include "TopicNames.hh"
#include "Time.hh"

void Server::start() {
  this->thread = new std::thread(std::bind(&Server::RunLoop, this));
}

void Server::RunLoop() {
  node_ptr_ = new ignition::transport::Node();

  world_stats_pub = node_ptr_->Advertise<ignition::msgs::WorldStatistics>(TopicNames::kWorldStatistics);
  node_ptr_->Subscribe(TopicNames::kWorldControl, &Server::OnWorldControl, this);

  while (true) {
    Time update_rate = Time(0, 1000000U);
    Time expected_end_step_time = Time::GetWallTime();
    expected_end_step_time += update_rate;

    // Begin Critical Section
    {
      std::lock_guard<std::mutex> guard(physics_mutex);
      if (quit_) {
        break;
      }

      Step();
    }
    // End Critical Section

    Time end_step_time = Time::GetWallTime();
    if (end_step_time < expected_end_step_time) {
      Time sleep_time = expected_end_step_time - end_step_time;
      Time::Sleep(sleep_time);
    }
  }
}

void Server::Step() {
  if (pause_) {
    return;
  }

  // increment step counter
  ++iterations_;

  // announce completion of this step
  ignition::msgs::WorldStatistics world_stats_msg;
  world_stats_msg.set_iterations(iterations_);
  world_stats_pub.Publish(world_stats_msg);
}
void Server::OnWorldControl(const ignition::msgs::WorldControl &msg) {
  // Enter critical section
  {
    std::lock_guard<std::mutex> guard(physics_mutex);
    pause_ = msg.pause();
    quit_ = msg.quit();
  }
  // End critical section
}
void Server::join() {
  thread->join();
}
