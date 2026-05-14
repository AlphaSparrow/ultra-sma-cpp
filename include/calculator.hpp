#pragma once
#include "parser.hpp"
#include <vector>
#include <string>

enum class Signal{
    HOLD, // CALMA CALMA
    BUY, // Khareedo yaaro
    SELL // BECHO BC
};

class Calculator {
    public:
        // Calculates SMA using a sliding Window
        static std::vector<double> calculateSMA(const std::vector<PricePoint>& prices,int windowSize);

        // Calculates EMA using thee recusrive O)1) Formula
        static std::vector<double> calculateEMA(const std::vector<PricePoint>& prices,int windowSize);

        // Checking Crossovers
        static std::vector<Signal> generateSignals(const std::vector<double>& fastMA, const std::vector<double>& slowMA);
};