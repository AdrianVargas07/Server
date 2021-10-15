// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <vector>
#include "TcpServer.hpp"
#include "Consumer.hpp"
#include "Socket.hpp"
#include "HTTPConnectionHandler.hpp"
#include "Queue.hpp"

#ifndef HTTP_SERVER
#define HTTP_SERVER

class HTTPServer : public TcpServer{
 private:
    const char* port = "";
    int numberThreads = 0;
    Queue<Socket> socketQueue;
    std::vector<HTTPApplication*> apps;

 public:
    DISABLE_COPY(HTTPServer);
    void start(char *argv[]);
    void stop();
    void startThreads(int numberThreads);
    void connectApp(HTTPApplication *app);
    static HTTPServer& getInstance();
    std::vector<HTTPApplication*> getApps();

 protected:
    HTTPServer() = default;
    ~HTTPServer() = default;
    void analyzeArguments(char *argv[]);
    void handleClientConnection(Socket& client) override;
};

#endif
