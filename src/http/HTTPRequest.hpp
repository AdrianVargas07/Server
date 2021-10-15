// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include "HTTPMessage.hpp"
#include "Utilities.hpp"
#include "Socket.hpp"

class HTTPRequest : public HTTPMessage{
 private:
    std::string method = "";
    std::string URI = "";

 public:
    HTTPRequest();
    HTTPRequest(const HTTPRequest& httpRequest);
    ~HTTPRequest();
    std::string getURI();
    std::string getMethod();
    void setMethod(std::string);
    void setURI(std::string);
    bool load(Socket &client, HTTPRequest &httpRequest);

    enum HTTP_METHOD{
      GET_METHOD = 1,
      HEAD_METHOD = 2,
      OPTIONS_METHOD = 3
    };
};

#endif
