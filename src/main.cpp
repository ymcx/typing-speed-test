#include "logic.h"
#include "status.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "You need to pass a text file as an argument." << endl;
    cout << "Each word needs to be on their own line." << endl;
    return 0;
  }

  string file = argv[1];
  int time = 60;
  Status status(file, time);
  render(status);
}
