#pragma once

#include <string>
#include <vector>

struct PricePoint{
    std::string date;
    double close;
    long long volume;
};

class Parser{
    public:
        static std::vector<PricePoint> parseCSV(const std::string& filename);
};
