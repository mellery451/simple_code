#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <vector>

// compile with:
//      g++ ptr_access.cpp -O3 -std=c++11

using namespace std;

class Print {
 public:
  void print() { i++; }

  int i{ 0 };
};

void test() {
  typedef vector<shared_ptr<Print>> sh_vec;
  typedef vector<unique_ptr<Print>> u_vec;
  typedef vector<Print*> raw_vec;

  sh_vec shvec;
  u_vec uvec;
  raw_vec rvec;

  // can't use initializer_list with unique_ptr
  for (int var = 0; var < 100; ++var) {
    shvec.push_back(make_shared<Print>());
    uvec.emplace_back(new Print());
    rvec.push_back(new Print());
  }

  //-------------test shared_ptr-------------------------
  auto time_sh_1 = std::chrono::system_clock::now();

  for (auto var = 0; var < 1000; ++var) {
    for (auto it = shvec.begin(), end = shvec.end(); it != end; ++it) {
      (*it)->print();
    }
  }

  auto time_sh_2 = std::chrono::system_clock::now();

  cout << "test shared_ptr : " << (time_sh_2 - time_sh_1).count()
       << " microseconds." << endl;

  //-------------test unique_ptr-------------------------
  auto time_u_1 = std::chrono::system_clock::now();

  for (auto var = 0; var < 1000; ++var) {
    for (auto it = uvec.begin(), end = uvec.end(); it != end; ++it) {
      (*it)->print();
    }
  }

  auto time_u_2 = std::chrono::system_clock::now();

  cout << "test unique_ptr : " << (time_u_2 - time_u_1).count()
       << " microseconds." << endl;

  //-------------test raw ptr-------------------------
  auto time_r_1 = std::chrono::system_clock::now();

  for (auto var = 0; var < 1000; ++var) {
    for (auto it = rvec.begin(), end = rvec.end(); it != end; ++it) {
      (*it)->print();
    }
  }

  auto time_r_2 = std::chrono::system_clock::now();

  cout << "test raw ptr : " << (time_r_2 - time_r_1).count()
       << " microseconds." << endl;

  for (auto ptr : rvec) {
    delete ptr;
  }

}

int main() { test(); }
