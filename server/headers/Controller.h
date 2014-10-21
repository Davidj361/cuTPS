#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
  public:
    Controller();
    ~Controller();

    /*
    Function  : Run
    Purpose   : The main loop of the server process
    Variables : None
    Returns   : 1 - Success
                0 - Fail
    */
    int Run();
  private:
};
#endif