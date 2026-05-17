#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

int main(){
    std::ofstream file("data/big_data.csv");
    file << "Date,Close,Volume\n";

    double price = 100.0;
    for(int i = 1; i <= 5000; ++i){
        double change = ((rand() % 200) - 100) / 100.0;
        price =+ change;
        file << "2026-01-" << i << "," << price << "," << (rand() % 1000000) << '\n';
    }

    file.close();
    std::cout << "bana di 5000 row, koi shak ?? babumoshai" << '\n';
    return 0;
}