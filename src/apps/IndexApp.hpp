// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <dirent.h>
#include <iostream>
#include <string>
#include "HTTPApplication.hpp"
#ifndef INDEX_H
#define INDEX_H

class IndexApp : public HTTPApplication {
 private:
  DIR *dirP;
  struct dirent *element;
  std::string requestForIndexApp = "";
  int filesAmount = 0;
  int64_t totalBytesByDIrectory = 0;

 public:
  IndexApp();
  IndexApp(const IndexApp& indexApp);
  ~IndexApp();
  std::string getCurrentDir();
  void setMyPath(std::string request);
  bool isDirectory();
  bool existFile(std::string fileName);
  void loadIndexXHTML(HTTPResponse &httpResponse, std::string fileName);
  void showDirectories(HTTPResponse &httpResponse);
  std::string getParentDirectory(std::string requestForIndexApp);
  bool isMyPackege(Socket &client, HTTPRequest &httpRequest,
               HTTPResponse &httpResponse) override;
  void errorIndexApp(HTTPResponse &httpResponse, std::string message);
  bool uploadFile(HTTPResponse &httpResponse);

 protected:
  void insertFilesRows(std::ostringstream &webXHTML);
  void createResponse(Socket &client, HTTPRequest &httpRequest,
                  HTTPResponse &httpResponse) override;
};
#endif
