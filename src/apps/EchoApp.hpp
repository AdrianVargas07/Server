// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <iostream>
#include <string>
#include "HTTPApplication.hpp"

#ifndef ECHOAPP_H
#define ECHOAPP_H


class EchoApp : public HTTPApplication{
 public:
    EchoApp();
    EchoApp(const EchoApp& echoApp);
    ~EchoApp();
    bool isMyPackege(Socket &client, HTTPRequest &httpRequest,
    HTTPResponse &httpResponse) override;

 protected:
    std::string getIdenticalTextFromRequest(HTTPRequest &httpRequest);
    void createResponse(Socket &client, HTTPRequest &httpRequest,
    HTTPResponse &httpResponse) override;
};

#endif
