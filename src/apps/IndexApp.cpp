// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include "IndexApp.hpp"
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstddef>
#include <iostream>
#define SERVER_NAME "AVM"
#define HTTP_VERSION "HTTP/1.0"

IndexApp::IndexApp() : HTTPApplication() {
}

IndexApp::IndexApp(const IndexApp& indexApp) : HTTPApplication() {
    (void) indexApp;
}

IndexApp::~IndexApp() {
    closedir(this->dirP);
}

bool IndexApp::isMyPackege(Socket &client, HTTPRequest &httpRequest,
                           HTTPResponse &httpResponse) {
    std::string identifierIndexApp = "/";
    std::string identifierIndexApp2 = "/index";
    std::string identifierIndexApp3 = "/index/";
    bool isMyPackage = false;
    std::string uriHttpRequest = httpRequest.getURI();
    std::vector<std::string> identifierApp =
    Utilities::split(uriHttpRequest, " ", 1);

    // this procedure is important if the uri has more
    // indications besides the /index
    if (uriHttpRequest.length() > 7) {
        identifierApp.insert(identifierApp.begin(),
        uriHttpRequest.substr(0, 7) );
    }

    // if the packege is of this app, will create the response
    if ( (identifierApp.at(0).compare(identifierIndexApp) ) == 0 ||
         (identifierApp.at(0).compare(identifierIndexApp2) ) == 0 ||
         (identifierApp.at(0).compare(identifierIndexApp3) ) == 0 ) {
        isMyPackage = true;
        createResponse(client, httpRequest, httpResponse);
    }
    return isMyPackage;
}

void IndexApp::createResponse(Socket &client, HTTPRequest &httpRequest,
                              HTTPResponse &httpResponse) {
    this->requestForIndexApp = "";
    this->totalBytesByDIrectory = 0;
    this->filesAmount = 0;

    // this line get path without the identifier App, that's to say, the /index
    if (httpRequest.getURI().length() > 7) {
        this->setMyPath(httpRequest.getURI());
    }
    if ((httpRequest.getMethod().compare("GET")) == 0) {
        if (this->isDirectory()) {
            bool hiddenDir = this->checkHiddenDir(requestForIndexApp);
            if (!hiddenDir) {
                if (this->existFile("index.html")) {
                    this->loadIndexXHTML(httpResponse, "/index.html");
                    this->createHeader(httpResponse,
                    getMIMEtype(getExtension("/index.html")),
                    httpResponse.getBody().length() );
                    this->createStatusLine(httpResponse,
                    httpResponse.STATUS_OK_200, HTTP_VERSION);
                } else {
                    if (this->existFile("index.xhtml")) {
                        this->loadIndexXHTML(httpResponse, "/index.xhtml");
                        this->createHeader(httpResponse,
                        getMIMEtype(getExtension("/index.xhtml")),
                        httpResponse.getBody().length());
                        this->createStatusLine(httpResponse,
                        httpResponse.STATUS_OK_200, HTTP_VERSION);
                    } else {
                        this->showDirectories(httpResponse);
                        this->createHeader(httpResponse,
                        getMIMEtype(getExtension("/index.xhtml")),
                        httpResponse.getBody().length() );
                        this->createStatusLine(httpResponse,
                        httpResponse.STATUS_OK_200, HTTP_VERSION);
                    }
                }
            } else {
                this->errorIndexApp(httpResponse, "FORBIDDEN 403");
                this->createHeader(httpResponse,
                getMIMEtype(getExtension("/index.html")),
                httpResponse.getBody().length() );
                this->createStatusLine(httpResponse,
                httpResponse.STATUS_FORBIDDEN_403, HTTP_VERSION);
            }
            client << httpResponse.response();
        } else {
            bool hiddenDir = this->checkHiddenDir(requestForIndexApp);
            bool openFile = uploadFile(httpResponse);
            if (!hiddenDir) {
                // if the path isn't hidden, is checked if is
                // possible to open the file or not
                if (openFile) {
                    this->createHeader(httpResponse,
                    getMIMEtype(requestForIndexApp),
                    getSizeFile(getCurrentDir() + requestForIndexApp) );
                    this->createStatusLine(httpResponse,
                    httpResponse.STATUS_OK_200, HTTP_VERSION);
                } else {
                    this->errorIndexApp(httpResponse, "NOT FOUND 404");
                    this->createHeader(httpResponse,
                    getMIMEtype(getExtension("/index.html")),
                    httpResponse.getBody().length() );
                    this->createStatusLine(httpResponse,
                    httpResponse.STATUS_NOT_FOUND_404, HTTP_VERSION);
                }
            } else {
                // if the path is hidden, also is necessary to check if the
                // path exists or not, to know if there is to return
                // 403 or 404 ERROR
                if (openFile) {
                    this->errorIndexApp(httpResponse, "FORBIDDEN 403");
                    this->createHeader(httpResponse,
                    getMIMEtype(getExtension("/index.html")),
                    httpResponse.getBody().length() );
                    this->createStatusLine(httpResponse,
                    httpResponse.STATUS_FORBIDDEN_403, HTTP_VERSION);
                } else {
                     this->errorIndexApp(httpResponse, "NOT FOUND 404");
                     this->createHeader(httpResponse,
                     getMIMEtype(getExtension("/index.html")),
                     httpResponse.getBody().length() );
                    this->createStatusLine(httpResponse,
                    httpResponse.STATUS_NOT_FOUND_404, HTTP_VERSION);
                 }
            }
            client << httpResponse.response();
        }
    } else {
       // HEAD METHOD
       // OPTIONS METHOD
       // Could be used other structure for evaluate the Method,
       // as switch, etc...
    }
}

bool IndexApp::isDirectory() {
    bool existDirectory;
    std::string path = this->getCurrentDir() + this->requestForIndexApp;
    dirP = opendir(path.c_str());
    if (dirP != NULL) {
        existDirectory = true;
    } else {
        existDirectory = false;
    }
    return existDirectory;
}

void IndexApp::setMyPath(std::string request) {
    this->requestForIndexApp = "/" + request.substr(7, request.length());
}

std::string IndexApp::getCurrentDir() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd);
}

bool IndexApp::existFile(std::string fileName) {
    bool existeArchivo = false;
    bool found = false;
    while ((element = readdir(this->dirP)) != NULL && !found) {
        if (strcmp(element->d_name, fileName.c_str()) == 0) {
            existeArchivo = true;
            found = true;
        }
    }
    rewinddir(dirP);
    return existeArchivo;
}

void IndexApp::loadIndexXHTML(HTTPResponse &httpResponse,
                              std::string fileName) {
    std::fstream myFile;
    std::string line;
    std::string file;
    std::string s =  getCurrentDir() + requestForIndexApp + fileName;
    myFile.open(getCurrentDir() + requestForIndexApp + fileName, std::ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            file += line;
        }
    myFile.close();
    }
    httpResponse.setBody(file);
}

void IndexApp::showDirectories(HTTPResponse &httpResponse) {
    std::ostringstream webXHTML;
    std::string pathForShow = this->requestForIndexApp;

    webXHTML << "<!DOCTYPE html>";
    webXHTML << "<html lang=\"es\" xmlns=\"http://www.w3.org/1999/xhtml\">";
    webXHTML << "<head>";
    webXHTML << "<meta charset=\"utf-8\"/>";
    webXHTML << "<title>Index App</title>";
    webXHTML << "</head>";
    webXHTML << "<body>";
    if (pathForShow.length() != 0) {
        webXHTML << "<h1>Index of " << "/" <<
        pathForShow.substr(1, pathForShow.length())  << "</h1>";
    } else {
        webXHTML << "<h1>Index of / </h1>";
    }
    webXHTML << "<table><thead><tr> <th>Name</th>" <<
                "<th>Size</th> <th>Last modification</th> </tr></thead>";
    webXHTML << "<tbody><tr> <th colspan=\"3\"><hr></hr></th> </tr>";
    this->insertFilesRows(webXHTML);
    webXHTML << "</tbody><tfoot><tr> <th> Total files " <<
    this->filesAmount << "</th>";
    webXHTML << "<th> Total bytes " << this->totalBytesByDIrectory << "</th>";
    // The following if is responsible for not showing the link of the "parent
    // directory" if it is already in the root directory, in the other cases if
    // said link is added
    if (requestForIndexApp.length() != 0) {
        webXHTML << "<th> <a href= \"/index" <<
        getParentDirectory(requestForIndexApp) <<
        "\">Parent Directory</a></th></tr>";
    } else {
        webXHTML << "</tr>";
    }
    webXHTML << "<tr> <th colspan=\"3\"><hr></hr></th> </tr></tfoot>";
    webXHTML << "</table>";
    webXHTML << "</body>";
    webXHTML << "</html>";
    httpResponse.setBody(webXHTML.str());
}

void IndexApp::insertFilesRows(std::ostringstream &webXHTML) {
    struct stat buffer;
    std::string fileName;
    char lastModified[80];
    while ((element = readdir(this->dirP)) != NULL) {
        stat((getCurrentDir() + requestForIndexApp + "/" +
               element->d_name).c_str() , &buffer);
        fileName = element->d_name;
        if (fileName.compare(".") != 0 &&
            fileName.compare("..") != 0 &&
            fileName.at(0) != *".") {
            webXHTML << "<tr><td><a href= \"/index" <<
            this->requestForIndexApp + "/" + element->d_name << "\">";
            webXHTML << element->d_name << "</a></td>";
            webXHTML << "<td>" << buffer.st_size << "</td>";
            webXHTML << "<td>" << ctime_r(&buffer.st_mtime, lastModified)  <<
                     "</td></tr>";
            this->filesAmount++;
            this->totalBytesByDIrectory += buffer.st_size;
        }
    }
}

void IndexApp::errorIndexApp(HTTPResponse &httpResponse, std::string message) {
    std::ostringstream error;
    error << "<!DOCTYPE html>";
    error << "<html lang=\"es\" xmlns=\"http://www.w3.org/1999/xhtml\">";
    error << "<html xmlns=\"http://www.w3.org/1999/xhtml\">";
    error << "<head>";
    error << "<meta http-equiv=\"Content-Type\"" <<
            "content=\"application/xhtml+xml; charset=utf-8\"/>";
    error << "<title>" << message << "</title>";
    error << "</head>";
    error << "<body>";
    error << "<h1>" << message << "</h1><br><hr>";
    error << "<p>Generated by " << SERVER_NAME << " Server</p>";
    error << "</body>";
    error << "</html>";
    httpResponse.setBody(error.str());
}

std::string IndexApp::getParentDirectory(std::string requestForIndexApp) {
    // It is analyzed from back to front
    int position = requestForIndexApp.rfind("/");
    std::string parentDirectory = requestForIndexApp.substr(0, position);
    return parentDirectory;
}

bool IndexApp::uploadFile(HTTPResponse &httpResponse) {
    bool fileOpen = false;
    std::ifstream ifs(getCurrentDir()+requestForIndexApp,
                        std::ifstream::binary);
    if (ifs.is_open()) {
        fileOpen = true;
        std::ostringstream binaryFile;
        char binaryData = ifs.get();
        while (ifs.good()) {
            binaryFile << binaryData;
            binaryData = ifs.get();
        }
        ifs.close();
        httpResponse.setBody(binaryFile.str());
    }
    return fileOpen;
}
