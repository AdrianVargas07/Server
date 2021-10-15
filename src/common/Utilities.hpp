// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include <vector>
#include <iostream>
#include <string>

class Utilities{
 public:
    static std::vector<std::string> split(std::string line,
                                          std::string delimiter, int times);
    static void colorRed();
    static void colorReset();
    static void colorGreen();
    static void printRequestReceive(std::string requestFromClient);
};
