// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#ifndef HTTPAPPLICATION_H
#define HTTPAPPLICATION_H

#include <unordered_map>
#include <string>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class HTTPApplication {
 private:
  std::unordered_map<std::string, std::string> MIMETYPES {
  {"aac", "audio/aac"},
   {"abw", "application/x-abiword"},
   {"arc", "application/x-freearc"},
   {"avi", "video/x-msvideo"},
   {"azw", "application/vnd.amazon.ebook"},
   {"bin", "application/octet-stream"},
   {"bmp", "image/bmp"},
   {"bz", "application/x-bzip"},
   {"bz2", "application/x-bzip2"},
   {"csh", "application/x-csh"},
   {"css", "text/css"},
   {"csv", "text/csv"},
   {"doc", "application/msword"},
   {"docx",
   "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
   {"eot", "application/vnd.ms-fontobject"},
   {"epub", "application/epub+zip"},
   {"gz", "application/gzip"},
   {"gif", "image/gif"},
   {"htm", "text/html"},
   {"html", "text/html"},
   {"ico", "image/vnd.microsoft.icon"},
   {"ics", "text/calendar"},
   {"jar", "application/java-archive"},
   {"jpeg", "image/jpeg"},
   {"jpg", "image/jpeg"},
   {"js", "text/javascript"},
   {"json", "application/json"},
   {"jsonld", "application/ld+json"},
   {"mid", "audio/midi"},
   {"midi", "audio/x-midi"},
   {"mjs", "text/javascript"},
   {"mp3", "audio/mpeg"},
   {"cda", "application/x-cdf"},
   {"mp4", "video/mp4"},
   {"mpeg", "video/mpeg"},
   {"mpkg", "application/vnd.apple.installer+xml"},
   {"odp", "application/vnd.oasis.opendocument.presentation"},
   {"ods", "application/vnd.oasis.opendocument.spreadsheet"},
   {"odt", "application/vnd.oasis.opendocument.text"},
   {"oga", "audio/ogg"},
   {"ogv", "video/ogg"},
   {"ogx", "application/ogg"},
   {"opus", "audio/opus"},
   {"otf", "font/otf"},
   {"png", "image/png"},
   {"pdf", "application/pdf"},
   {"php", "application/x-httpd-php"},
   {"ppt", "application/vnd.ms-powerpoint"},
   {"pptx",
   "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
   {"rar", "application/vnd.rar"},
   {"rtf", "application/rtf"},
   {"sh", "application/x-sh"},
   {"svg", "image/svg+xml"},
   {"swf", "application/x-shockwave-flash"},
   {"tar", "application/x-tar"},
   {"tif", "image/tiff"},
   {"tiff", "image/tiff"},
   {"ts", "video/mp2t"},
   {"ttf", "font/ttf"},
   {"txt", "text/plain"},
   {"vsd", "application/vnd.visio"},
   {"wav", "audio/wav"},
   {"weba", "audio/webm"},
   {"webm", "video/webm"},
   {"webp", "image/webp"},
   {"woff", "font/woff"},
   {"woff2", "font/woff2"},
   {"xhtml", "application/xhtml+xml"},
   {"xls", "application/vnd.ms-excel"},
   {"xlsx",
   "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
   {"xml", "application/xml"},
   {"xul", "application/vnd.mozilla.xul+xml"},
   {"zip", "application/zip"},
  {"3gp", "audio/3gpp"},  // It only if it doesn't contain video
  {"3g2", "audio/3gpp2"},  // It only if it doesn't contain video
  {"7z", "application/x-7z-compressed"}
};

 public:
  HTTPApplication();
  HTTPApplication(const HTTPApplication& httpAplication);
  ~HTTPApplication();
  std::string getExtension(std::string fileName);
  std::string getMIMEtype(std::string extension);
  off_t getSizeFile(std::string pathFile);
  void createStatusLine(HTTPResponse &httpResponse, int statusCode,
                        std::string HTTPVersion);
  void createHeader(HTTPResponse &httpResponse, std::string contentType,
               int contentLength);
  bool checkHiddenDir(std::string request);
  virtual bool isMyPackege(Socket &client, HTTPRequest &httpRequest,
                        HTTPResponse &httpResponse) = 0;
  virtual void createResponse(Socket &client, HTTPRequest &httpRequest,
                           HTTPResponse &httpResponse) = 0;
};
#endif
