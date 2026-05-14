#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<PricePoint> Parser::parseCSV(const std::string& filename){
    std::vector<PricePoint> data;
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cerr << "ERROR CANT OPEN UR FILE MAN" << filename << '\n';
        return data;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string date, closeStr, volStr;

        // Assume that CSV Data format is - Date, CLOSE, VOL
        if(std::getline(ss, date, ',') && std::getline(ss, closeStr, ',') && std::getline(ss, volStr, ',')){
            try {
                PricePoint pp;
                
                pp.date = date;
                pp.close = std::stod(closeStr);
                pp.volume = std::stoll(volStr);

                data.push_back(pp);
            }
            // Yeh jo ... dikha na bhai, it shows you that
            catch(...){
                continue;
            }
        }
    }
    
    file.close();
    return data;
}