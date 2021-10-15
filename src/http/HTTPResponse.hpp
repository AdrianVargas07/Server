// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include "HTTPMessage.hpp"
#include "Socket.hpp"

class HTTPResponse : public HTTPMessage{
 private:
    std::string statusLine = "";
    // int statusCode = 0;

 public:
    HTTPResponse();
    HTTPResponse(const HTTPResponse& HTTPResponse);
    ~HTTPResponse();
    std::string getStatusLine();
    std::string getHeaderString();
    void setStatusLine(std::string statusLine);
    void addHeader(std::string key, std::string value);
    std::string response();
    void send(Socket &client);
    int getEnumStatusCOde();

    enum STATUS_CODES{
        STATUS_CONTINUE_100 = 100,
        STATUS_OK_200 = 200,
        STATUS_BAD_REQ_400 = 400,
        STATUS_FORBIDDEN_403 = 403,
        STATUS_NOT_FOUND_404 = 404,
        STATUS_INTERNAL_SRV_ERR_500 = 500,
        STATUS_NOT_IMPLMTD_501 = 501,
        STATUS_HTTP_VRSN_NOT_SPPRTD_505 = 505
    };
};

#endif
