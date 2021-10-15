// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>
#include <sstream>
#include <map>
#include <string>

class HTTPMessage{
 private:
    std::string HTTPVersion = "";
    std::string body;

 public:
    HTTPMessage();
    HTTPMessage(const HTTPMessage& httpMessage);
    ~HTTPMessage();
    std::string getBody();
    std::string getHTTPVersion();
    std::string getHeader();
    void setHTTPVersion(std::string httpVersion);
    void setAHeader(std::string key, std::string value);
    void setBody(std::string body);

 protected:
       std::map <std::string, std::string> header;
};
#endif
