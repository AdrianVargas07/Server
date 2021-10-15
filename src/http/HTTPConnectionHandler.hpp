// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <unistd.h>
#include <iostream>
#include <vector>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "HTTPApplication.hpp"
#include "Consumer.hpp"


#ifndef HTTPCONNECTIONHANDLER_h
#define HTTPCONNECTIONHANDLER_H

class HTTPConnectionHandler : public Consumer<Socket> {
 private:
    std::vector<HTTPApplication*> *appsFromHTTPServer;

 public:
    explicit HTTPConnectionHandler(std::vector<HTTPApplication*> *apps);
    explicit HTTPConnectionHandler(const HTTPConnectionHandler&
                                   httpConnectionHandler);
    ~HTTPConnectionHandler();

 protected:
    void consume(Socket client) override;
    int run() override;
    // Response in case the package does not correspond to any application
    void responseBadRequest(Socket &client, HTTPResponse &httpResponse);
};

#endif
