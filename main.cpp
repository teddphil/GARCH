#include "garch.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<double> loadReturns(const std::string& path) {
    std::ifstream file(path);
    std::vector<double> returns;
    std::string line;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, ret;
        std::getline(ss, date, ',');
        std::getline(ss, ret, ',');
        returns.push_back(std::stod(ret));
    }
    return returns;
}

int main() {
    auto returns = loadReturns("../data/sp500_returns.csv");

    GARCH model(1e-6, 0.05, 0.9);

    double ll = model.logLikelihood(returns);
    std::cout << "Log-likelihood: " << ll << std::endl;

    auto var = model.computeVariance(returns);
    std::cout << "Last conditional volatility: "
              << std::sqrt(var.back()) << std::endl;

    return 0;
}