// Copyright 2021 Jeisson Hidalgo-Cespedes.University of Costa Rica. CC BY 4.0.
// Modified by Adrian Vargas Martinez

#include <signal.h>
#include <iostream>
#include <sstream>

#include "Socket.hpp"
#include "HTTPServer.hpp"
#include "EchoApp.hpp"
#include "IndexApp.hpp"

void handleSignal(int signal) {
  HTTPServer::getInstance().stop();
  std::cout << "Signal: " << signal << std::endl;
}

int main(int argc, char* argv[]) {
    if ( argc == 3 ) {  //  Three arguments couting executable name
    ::signal(SIGINT, ::handleSignal);
    ::signal(SIGTERM, ::handleSignal);

    try {
      Utilities::colorGreen();
      printf(" * Running AVM web server *\n");
      Utilities::colorReset();
      HTTPServer::getInstance().connectApp(new EchoApp());
      HTTPServer::getInstance().connectApp(new IndexApp());
      HTTPServer::getInstance().start(argv);
      } catch (std::runtime_error& error) {
    }
    } else {
      Utilities::colorRed();
      printf(" * AVM web server *\n * Problems running AVM Server.\n");
      Utilities::colorReset();
      printf(" * Insufficient parameters: Three parameters are needed.\n");
      printf(" * Correct use: <Executable> <Port> <Number of threads>\n");
      Utilities::colorRed();
      printf(" * Aborting program...\n");
      Utilities::colorReset();
  }
  return 0;
}
