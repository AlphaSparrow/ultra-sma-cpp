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
        static void calculateSMA(const std::vector<PricePoint>& prices,int windowSize, std::vector<double>& smaResults);

        // Calculates EMA using thee recusrive O)1) Formula
        static void calculateEMA(const std::vector<PricePoint>& prices,int windowSize, std::vector<double>& emaResults);

        // Checking Crossovers
        static void generateSignals(const std::vector<double>& fastMA, const std::vector<double>& slowMA, std::vector<Signal>& signals);
};