#include <iostream>
#include "parser.hpp"

int main(){
    std::string path = "data/stock_data.csv";
    std::cout << "SMA Truck on the highway!!" << '\n';

    std::vector<PricePoint> prices = Parser::parseCSV(path);

    if(prices.empty()) {
        std::cout << "No Data inbound, check if your brotherrr" << path << "exists" << '\n';
        return 1;
    }

    std::cout << "Loaded " << prices.size() << " data points" << '\n';
    std::cout << "Latest Price: " << prices.back().close << " on " << prices.back().date << '\n';
    
    return 0;
}