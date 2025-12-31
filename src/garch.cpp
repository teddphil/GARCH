#include "garch.hpp"
#include <cmath>
#include <stdexcept>

GARCH::GARCH(double omega, double alpha, double beta)
    : omega_(omega), alpha_(alpha), beta_(beta) {}

void GARCH::setParams(double omega, double alpha, double beta) {
    omega_ = omega;
    alpha_ = alpha;
    beta_ = beta;
}

std::vector<double> GARCH::computeVariance(const std::vector<double>& r) {
    size_t n = r.size();
    std::vector<double> var(n);

    double var0 = 0.0;
    for (double x : r) var0 += x * x;
    var0 /= n;

    var[0] = var0;

    for (size_t t = 1; t < n; ++t) {
        var[t] = omega_
               + alpha_ * r[t - 1] * r[t - 1]
               + beta_  * var[t - 1];

        if (var[t] <= 0.0)
            throw std::runtime_error("Negative variance encountered");
    }

    return var;
}

double GARCH::logLikelihood(const std::vector<double>& r) {
    auto var = computeVariance(r);

    double ll = 0.0;
    for (size_t t = 0; t < r.size(); ++t) {
        ll += -0.5 * (std::log(var[t]) + r[t] * r[t] / var[t]);
    }
    return ll;
}