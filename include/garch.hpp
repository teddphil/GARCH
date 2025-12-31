#pragma once
#include <vector>

class GARCH {
public:
    GARCH(double omega, double alpha, double beta);

    double logLikelihood(const std::vector<double>& returns);
    std::vector<double> computeVariance(const std::vector<double>& returns);

    void setParams(double omega, double alpha, double beta);

private:
    double omega_;
    double alpha_;
    double beta_;
};