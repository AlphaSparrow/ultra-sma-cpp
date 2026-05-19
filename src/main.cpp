#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include "parser.hpp"
#include "calculator.hpp"

int main(){
    std::string path = "data/big_data.csv";
    std::cout << "SMA Truck on the highway!!" << '\n';

    std::vector<PricePoint> prices = Parser::parseCSV(path);

    if(prices.empty()) {
        std::cout << "No Data inbound, check if your brotherrr" << path << "exists" << '\n';
        return 1;
    }

    std::vector<double> fastSma;
    std::vector<double> slowSma;
    std::vector<double> ema;
    std::vector<Signal> signals;

    // Start Clock just before the W16 Quad Turbo Engine
    auto start = std::chrono::high_resolution_clock::now();

    Calculator::calculateSMA(prices, 3, fastSma);
    Calculator::calculateSMA(prices, 5, slowSma);
    Calculator::calculateEMA(prices, 5, ema);

    Calculator::generateSignals(fastSma, slowSma, signals);

    auto end = std::chrono::high_resolution_clock::now();

    if(!signals.empty()){
        std::cout << "(Engine internal check: " << (int)signals[0] << ")" << '\n';
    }

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << std::fixed << std::setprecision(2);

    // BHAI COMMIT DEKH RAHE HO TO BHAI BATA DU, ISKO TYPE KRNE ME G** FAT GAYI THI
    std::cout << std::left  << std::setw(12) << "DATE"   << " | "
              << std::right << std::setw(10) << "CLOSE"  << " | "
              << std::right << std::setw(10) << "SMA(3)" << " | "
              << std::right << std::setw(10) << "SMA(5)" << " | "
              << std::right << std::setw(10) << "EMA(5)" << " | "
              << "SIGNALSS" << '\n';

    std::cout << std::string(78, '=') << '\n';
    
    for(size_t i = 0; i < prices.size(); ++i){
        std::string sigText = "HOLD";
        if(signals[i] == Signal::BUY) sigText = "BUY";
        if(signals[i] == Signal::SELL) sigText = "SELL";
        
        std::cout << std::left  << std::setw(12) << prices[i].date  << " | "
        << std::right << std::setw(10) << prices[i].close << " | "
        << std::right << std::setw(10) << fastSma[i]      << " | "
        << std::right << std::setw(10) << slowSma[i]      << " | "
        << std::right << std::setw(10) << ema[i]          << " | "
        << sigText << '\n'; 
    }
    
    std::cout << std::string(78, '-') << '\n';
    std::cout << "Completed itna: " << prices.size() << "rowss" << '\n';

    std::cout << "Latency Time baby" << '\n';
    std::cout << "Time taken: " << duration.count() << "nanoseconds" << '\n';
    std::cout << std::string(78, '=') << '\n';

    return 0;
}