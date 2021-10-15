// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include "HTTPResponse.hpp"
#include <utility>

HTTPResponse::HTTPResponse() : HTTPMessage() {
}

HTTPResponse::HTTPResponse(const HTTPResponse& httpResponse)
                           : HTTPMessage(httpResponse) {
}

HTTPResponse::~HTTPResponse() {
}

std::string HTTPResponse::getStatusLine() {
    return this->statusLine;
}

void HTTPResponse::addHeader(std::string key, std::string value) {
    header.insert(std::pair<std::string, std::string>(key, value));
}

std::string HTTPResponse::getHeaderString() {
    std::ostringstream headerResponse;
    std::pair<std::string, std::string> map;
    for ( auto it = header.begin(); it != this->header.end(); it++ ) {
        map = *it;
        headerResponse << it->first << " " << it->second << "\r\n";
    }

    headerResponse << "\r\n";

    return headerResponse.str();
}

void HTTPResponse::send(Socket &client) {
    client.send();
}

void HTTPResponse::setStatusLine(std::string statusLine) {
    this->statusLine = statusLine;
}

std::string HTTPResponse::response() {
    return this->getStatusLine() + this->getHeaderString() + this->getBody();
}
