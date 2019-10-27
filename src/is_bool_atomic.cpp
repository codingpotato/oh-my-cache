#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
  bool request_to_finish = false;

  std::thread t{[&request_to_finish]() {
    std::cout << "Thread is starting...\n";
    while (!request_to_finish) {
    }
    std::cout << "Thread exit\n";
  }};

  std::this_thread::sleep_for(2s);
  std::cout << "Request to finish\n";
  request_to_finish = true;
  t.join();
}