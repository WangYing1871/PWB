#include <thread>
#include <iostream>

#include "pwb_v1.h"

int main(int argc, char *argv[]){

  QApplication app(argc,argv);
  pwb_v1 widget00;
  widget00.show();

  return app.exec();
}
