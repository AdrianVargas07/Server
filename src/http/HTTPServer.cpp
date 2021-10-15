// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <iostream>
#include <vector>
#include "HTTPServer.hpp"

void HTTPServer::start(char *argv[]) {
    this->analyzeArguments(argv);
    this->startThreads(this->numberThreads);
    this->listenForConnections(this->port);
    while (true) {
        this->acceptConnectionRequest();
    }
}

void HTTPServer::stop() {
    std::cout << "Server stopped" << std::endl;
    this->stopListening();
}

HTTPServer& HTTPServer::getInstance() {
    static HTTPServer server;
    return server;
}

std::vector<HTTPApplication*> HTTPServer::getApps() {
    return this->apps;
}

void HTTPServer::startThreads(int numberThreads) {
    for (int i=0; i < numberThreads; i++) {
        HTTPConnectionHandler *threads = new HTTPConnectionHandler(&this->apps);
        threads->setConsumingQueue(&this->socketQueue);
        threads->startThread();
    }
}

void HTTPServer::analyzeArguments(char *argv[]) {
    this->port = argv[1];
    this->numberThreads = (int) *argv[2];
}

void HTTPServer::handleClientConnection(Socket& client) {
    socketQueue.push(client);
}

void HTTPServer::connectApp(HTTPApplication *app) {
    apps.push_back(app);
}


