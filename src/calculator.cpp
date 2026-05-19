#include "calculator.hpp"
#include <numeric>
#include <algorithm>

void Calculator::calculateSMA(const std::vector<PricePoint>& prices, int windowSize, std::vector<double>& smaResults){
    smaResults.clear();
    if(prices.empty() || windowSize <= 0) return;

    smaResults.reserve(prices.size());
    double sum = 0.0;
    size_t i = 0;

    // No more fucking deques
    size_t warmUpLimit = std::min(prices.size(), static_cast<size_t>(windowSize));

    for(; i < warmUpLimit; ++i) {
        sum += prices[i].close;
        if(i < static_cast<size_t>(windowSize - 1)){
            smaResults.push_back(0.0); // This tells there aint enough data kid
        }
    }

    if(static_cast<size_t>(windowSize) <= prices.size()) {
        smaResults.push_back(sum / windowSize);
    }

    // Direct indexing instead of fricking DEQEEUE
    for(; i < prices.size(); ++i){
        sum = sum - prices[i - windowSize].close + prices[i].close;
        smaResults.push_back(sum / windowSize);
    }
}

void Calculator::calculateEMA(const std::vector<PricePoint>& prices, int windowSize, std::vector<double>& emaResults) {
    emaResults.clear();
    if(prices.empty()) return;

    emaResults.reserve(prices.size());
    double multiplier = 2.0 / (windowSize + 1);

    double currentEma = prices[0].close;
    emaResults.push_back(currentEma);

    for (size_t i = 1; i < prices.size(); ++i){
        currentEma = (prices[i].close - currentEma) * multiplier + currentEma;
        emaResults.push_back(currentEma);
    }
}

void Calculator::generateSignals(const std::vector<double>& fastMA, const std::vector<double>& slowMA, std::vector<Signal>& signals){
    signals.clear();
    // safety checkpoint
    if(fastMA.size() != slowMA.size() || fastMA.empty()) return;

    signals.reserve(fastMA.size());
    size_t i = 0;
    
    while(i < fastMA.size() && (fastMA[i] == 0.0 || slowMA[i] == 0)){
        signals.push_back(Signal::HOLD);
        ++i;
    }

    if(i < fastMA.size()){
        bool wasFasUp = fastMA[i] > slowMA[i];
        signals.push_back(Signal::HOLD);
        ++i;

        for(; i < fastMA.size(); ++i){
            bool isFastUp = fastMA[i] > slowMA[i];

            if(isFastUp && !wasFasUp){
                signals.push_back(Signal::BUY);
            }
            else if (!isFastUp && wasFasUp){
                signals.push_back(Signal::SELL);
            }else {
                signals.push_back(Signal::HOLD);
            }

        wasFasUp = isFastUp;
        }
    }
}