#include <string>
#include <iostream>
#include <memory>

using namespace std;

void test() {
     std::string str1 =  (std::string)"I cast this thing 01" +  " -- then add this";
     cout << str1 << endl;
     std::string str2 =  std::string("I construct this thing") +  " -- then add this";
     cout << str2 << endl;
     const char* str3 =  ((std::string)"I cast this thing 02" +  " -- then add this").c_str();
     cout << str3 << endl;
     std::string str4 =  static_cast<std::string>("I cast this thing 03") +  " -- then add this";
     cout << str4 << endl;
}

int main() { test(); }
