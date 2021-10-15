// Copyright 2021 Adrian Vargas Martinez. University of Costa Rica.

#include "Utilities.hpp"
#include <string>

std::vector<std::string> Utilities::split(std::string line,
                                          std::string delimiter, int times) {
    std::vector<std::string> row;
    if ( line.size() > 0 ) {
        int    contador    = 0;
        size_t posicion    = 0;

        while (contador < times+1) {
            posicion = line.find(delimiter);
            if (posicion == std::string::npos)
                break;
            std::string subparte = line.substr(0, posicion);
            row.push_back(subparte);
            line.erase(0, posicion + delimiter.length());
            contador++;
        }
        if ( line.compare("") != 0 ) {
            row.push_back(line);
        }
    }
    return row;
}

void Utilities::colorRed() {
    printf("\033[31m");
}

void Utilities::colorReset() {
    printf("\033[0m");
}

void  Utilities::colorGreen() {
    printf("\033[32m");
}


void Utilities::printRequestReceive(std::string requestFromClient) {
    Utilities::colorGreen();
    printf(" * Request received: ");
    Utilities::colorReset();
    printf("%s \n", requestFromClient.c_str());
}
