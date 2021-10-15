// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <string>
#include <vector>
#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest() : HTTPMessage() {
}

HTTPRequest::HTTPRequest(const HTTPRequest& httpRequest)
                        : HTTPMessage(httpRequest) {
}

HTTPRequest::~HTTPRequest() {
}

std::string HTTPRequest::getURI() {
    return this->URI;
}

std::string HTTPRequest::getMethod() {
    return this->method;
}

void HTTPRequest::setMethod(std::string method) {
     this->method = method;
}

void HTTPRequest::setURI(std::string URI) {
    this->URI = URI;
}

bool HTTPRequest::load(Socket &client, HTTPRequest &httpRequest) {
    std::string requestFromClient;
    client.readLine(requestFromClient, *"\r\n");

    if (!requestFromClient.empty()) {
        Utilities::printRequestReceive(requestFromClient);
        std::vector<std::string> requestSplitted =
        Utilities::split(requestFromClient, " ", 3);

        httpRequest.setMethod(requestSplitted.at(0));
        httpRequest.setURI(requestSplitted.at(1));
        httpRequest.setHTTPVersion(requestSplitted.at(2));

        bool header = true;
        while ( header ) {
            std::string headersClient;
            client.readLine(headersClient, * "\r\n\r\n");

            if ( headersClient.compare("\n") != 0 ) {
                std::vector<std::string> a_header =
                Utilities::split(headersClient, " ", 2);
                httpRequest.setAHeader(a_header.at(0), a_header.at(1));
            } else {
                header = false;
            }
        }
        return false;
    } else {
        return true;
    }
}
