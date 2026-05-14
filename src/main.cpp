#include <iostream>
#include <iomanip>
#include "parser.hpp"
#include "calculator.hpp"

int main(){
    std::string path = "data/stock_data.csv";
    std::cout << "SMA Truck on the highway!!" << '\n';

    std::vector<PricePoint> prices = Parser::parseCSV(path);

    if(prices.empty()) {
        std::cout << "No Data inbound, check if your brotherrr" << path << "exists" << '\n';
        return 1;
    }

    std::vector<double> sma = Calculator::calculateSMA(prices, 5);
    std::vector<double> ema = Calculator::calculateEMA(prices, 5);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "DATE       |CLOSE    |SMA(5)   |EMA(5)" << '\n';
    std::cout << "=================================" << '\n';

    for(size_t i = 0; i < prices.size(); ++i){
        std::cout << prices[i].date << " | " << prices[i].close << " | " << sma[i] << "    | " << ema[i] << '\n';
    }
    return 0;
}