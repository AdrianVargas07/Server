// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include "EchoApp.hpp"
#include <iostream>
#include <vector>
#include <string>

EchoApp::EchoApp() : HTTPApplication() {
}

// EchoApp::EchoApp(const EchoApp& echoApp){
// }

EchoApp::~EchoApp() {
}

bool EchoApp::isMyPackege(Socket &client, HTTPRequest &httpRequest,
                          HTTPResponse &httpResponse) {
    std::string identifierEchoApp = "/echo";
    std::string identifierEchoApp2 = "/echo/";
    bool isMyPackage = false;

    std::string uriHttpRequest = httpRequest.getURI();
    std::vector<std::string> identifierApp =
    Utilities::split(uriHttpRequest, " ", 1);

    // this procedure is important if the uri has more
    // indications besides the /echo
    if (uriHttpRequest.length() > 6) {
        identifierApp.insert(identifierApp.begin(),
        uriHttpRequest.substr(0, 5));
    }

    //  check if the URI is echo which one always will be in vector[1]
    if ( (identifierApp.at(0).compare(identifierEchoApp) ) == 0 ||
         (identifierApp.at(0).compare(identifierEchoApp2) ) == 0) {
        isMyPackage = true;
        createResponse(client, httpRequest, httpResponse);
    }
    return isMyPackage;
}

void EchoApp::createResponse(Socket &client, HTTPRequest &httpRequest,
                            HTTPResponse &httpResponse) {
    //  At the moment, only is implemented the asnwer to get method
    if ( (httpRequest.getMethod().compare("GET") ) == 0 ) {
        const char* const SERVER_NAME = "AVM";
        std::ostringstream iniMsg, endMsg;

        iniMsg << "<!DOCTYPE html><html lang=\"en\"><meta charset=\"ascii\"/>";
        iniMsg << "<title> Hi from EchoApp!</title>";
        iniMsg << "<h1> Welcome from EchoApp!</h1>";
        iniMsg << "</html><h3>Showing web page that contains ";
        iniMsg << "identical text of the request that was made.</h3><br>";
        endMsg << "<hr><p>Generated by " <<SERVER_NAME<< " Server</p></html>";

        // Status line
        client << "HTTP/1.0 200 OK\r\n";

        // Response header
        client << "Server: " << SERVER_NAME << "\r\n";
        client << "Content-Type: text/html charset=ascii\r\nContent-Length: "
        << iniMsg.str().length() +
        this->getIdenticalTextFromRequest(httpRequest).length()
        + endMsg.str().length() << "\r\n\r\n";

        // Body
        httpResponse.setBody(this->getIdenticalTextFromRequest(httpRequest));

        client << iniMsg.str();
        client << httpResponse.getBody();
        client << endMsg.str();
    } else {
       //  HEAD METHOD
       //  OPTIONS METHOD
       //  Could be used other structure for evaluate the Method,
       //  as switch, etc...
    }
}

std::string EchoApp::getIdenticalTextFromRequest(HTTPRequest &httpRequest) {
    std::string message;
    message += httpRequest.getMethod() +" "+ httpRequest.getURI() +" "+
    httpRequest.getHTTPVersion() + "<br>";
    message += httpRequest.getHeader();
    return message;
}
