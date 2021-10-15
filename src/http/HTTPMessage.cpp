// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <string>
#include <utility>
#include "HTTPMessage.hpp"

HTTPMessage::HTTPMessage() {
}

HTTPMessage::HTTPMessage(const HTTPMessage& httpMessage) {
    this->HTTPVersion = httpMessage.HTTPVersion;
    this->header = httpMessage.header;
    this->body = httpMessage.body;
}

HTTPMessage::~HTTPMessage() {
}

std::string HTTPMessage::getBody() {
    return this->body;
}

std::string HTTPMessage::getHeader() {
    std::string headers;
    for ( auto it = header.begin(); it != this->header.end(); it++ ) {
            std::pair<std::string, std::string> map = *it;
            headers += it->first + it->second;
            headers += "<br>";
    }
    return headers;
}

std::string HTTPMessage::getHTTPVersion() {
    return this->HTTPVersion;
}

void HTTPMessage::setHTTPVersion(std::string httpVersion) {
    this->HTTPVersion = httpVersion;
}

void HTTPMessage::setAHeader(std::string key, std::string value) {
    this->header.insert(std::pair <std::string, std::string> (key, value));
}

void HTTPMessage::setBody(std::string body) {
    this->body = body;
}

