#include "calculator.hpp"
#include <deque>
#include <numeric>

std::vector<double> Calculator::calculateSMA(const std::vector<PricePoint>& prices, int windowSize){
    std::vector<double> smaResults;
    std::deque<double> window;
    double sum = 0.0;

    for(const auto&p : prices){
        window.push_back(p.close);
        sum += p.close;

        if(window.size() > windowSize) { 
            sum -= window.front();
            window.pop_front();
        }

        if(window.size() == windowSize){
            smaResults.push_back(sum / windowSize);
        }else{
            smaResults.push_back(0.0); // Backup flag to tell not enough data yet
        }
    }
    return smaResults;
}

std::vector<double> Calculator::calculateEMA(const std::vector<PricePoint>& prices, int windowSize) {
    std::vector<double> emaResults;
    double multiplier = 2.0 / (windowSize + 1);
    double currentEma = 0.0;

    for (size_t i = 0; i < prices.size(); ++i){
        if(i == 0){
            currentEma = prices[i].close;
        }else{
            currentEma = (prices[i].close - currentEma) * multiplier + currentEma;
        }
        emaResults.push_back(currentEma);
    }
    return emaResults;
}

std::vector<Signal> Calculator::generateSignals(const std::vector<double>& fastMA, const std::vector<double>& slowMA){
    std::vector<Signal> signals;
    // safety checkpoint
    if(fastMA.size() != slowMA.size()) return signals;

    bool wasFastUP = false;
    bool firstValid = false;

    for(size_t i = 0; i < fastMA.size(); ++i){
        if(fastMA[i] == 0.0 || slowMA[i] == 0.0){
            signals.push_back(Signal::HOLD);
            continue;
        }

        bool isFastUP = fastMA[i] > slowMA[i];

        if(!firstValid){
            wasFastUP = isFastUP;
            firstValid = true;
            signals.push_back(Signal::HOLD);
            continue;
        }

            if(isFastUP && !wasFastUP) {
                signals.push_back(Signal::BUY);
            } // THE GOLDEN CROSS - SONE KI GATH
            else if(!isFastUP && wasFastUP){
                signals.push_back(Signal::SELL);
            } // DEATH CROSS - MRITYU
            else {
                signals.push_back(Signal::HOLD); // PEHLA VALID DAY, NO HISTORY TO COMPARE GENTLEMEN
            }

            wasFastUP = isFastUP;

    }
    return signals;
}