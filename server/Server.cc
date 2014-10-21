#include "headers/Controller.h"

using namespace std;

int main (int argC, char **argV) {
  Controller *controller = new Controller();

  return controller->Run ();
}