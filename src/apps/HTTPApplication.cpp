// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include "HTTPApplication.hpp"
#include <sys/stat.h>
#include <vector>
#include <string>
#define SERVER_NAME "AVM"

HTTPApplication::HTTPApplication() {
}

HTTPApplication::HTTPApplication(const HTTPApplication& httpAplication) {
    (void) httpAplication;
}

HTTPApplication::~HTTPApplication() {
}

std::string HTTPApplication::getExtension(std::string fileName) {
    int position = 0;
    std::string extension;
    position = fileName.find('.');
    extension = fileName.erase(0, position+1);
    // converts the extension from uppercase to lowercase one by one
    for (std::size_t i = 0; i < extension.size(); i++) {
        extension[i] = tolower(extension[i]);
    }
    return extension;
}

std::string HTTPApplication::getMIMEtype(std::string extension) {
    std::string mime;
    std::unordered_map<std::string, std::string>::const_iterator
    it = MIMETYPES.find(extension);
    if (it != MIMETYPES.end()) {
        mime = it -> second;
    }
    return mime;
}

off_t HTTPApplication::getSizeFile(std::string pathFile) {
    struct stat st;
    stat(pathFile.c_str(), &st);
    return st.st_size;
}

void HTTPApplication::createStatusLine(HTTPResponse &httpResponse,
                                      int statusCode, std::string HTTPVersion) {
    std::ostringstream msg;
    msg << HTTPVersion << " " << statusCode << " ";
    switch (statusCode) {
        case HTTPResponse::STATUS_OK_200:
            msg << "OK";
        break;
        case HTTPResponse::STATUS_BAD_REQ_400:
            msg << "BAD REQUEST";
        break;
        case HTTPResponse::STATUS_FORBIDDEN_403:
            msg << "FORBIDDEN";
        break;
        case HTTPResponse::STATUS_NOT_FOUND_404:
            msg << "NOT FOUND";
        break;
        case HTTPResponse::STATUS_INTERNAL_SRV_ERR_500:
            msg << "INTERNAL SERVER ERROR";
        break;
        case HTTPResponse::STATUS_NOT_IMPLMTD_501:
            msg << "NOT IMPLEMENTED";
        break;
        case HTTPResponse::STATUS_HTTP_VRSN_NOT_SPPRTD_505:
            msg << "HTTP VERSION NOT SUPPORTED";
        break;
    }
    msg << "\r\n";
    httpResponse.setStatusLine(msg.str());
}

void HTTPApplication::createHeader(HTTPResponse &httpResponse,
                                   std::string contentType, int contentLength) {
    std::ostringstream header;
    httpResponse.addHeader("Server: ", SERVER_NAME);
    httpResponse.addHeader("Content-Type: ", contentType);
    httpResponse.addHeader("Content-Length: ", std::to_string(contentLength));
}

bool HTTPApplication::checkHiddenDir(std::string request) {
    bool contentHidden = false;
    std::istringstream split(request);
    std::vector<std::string> directory;  // it also could be a file
    for (std::string each; std::getline( split, each, '/');
        directory.push_back(each)) {}
    for ( std::vector<std::string>::iterator it = directory.begin();
          it != directory.end() && !contentHidden; it++) {
       std::string dir = *it;
       char d = dir[0];
       if (d == '.') {
           contentHidden = true;
       }
    }
    return contentHidden;
}
