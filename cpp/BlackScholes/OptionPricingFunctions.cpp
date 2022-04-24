//
// Created by Ali Ahmad on 24/04/2022.
//

#include "OptionPricingFunctions.h"


/* Price calculation function for European Call Options */
double EuroCall(const OptionParams &optionParams) {
    double d1 = D1(optionParams);
    double d2 = D2(optionParams);
    double callOption = optionParams.SpotPrice * exp(-optionParams.DividendYield * optionParams.Tau) * CDF(d1) -
                        optionParams.StrikePrice * exp(-optionParams.RiskFreeRate * optionParams.Tau) * CDF(d2);
    return callOption > 0 ? callOption : 0;
}

/* Price calculation function for European Put Options */
double EuroPut(const OptionParams &optionParams) {
    double d1 = D1(optionParams);
    double d2 = D2(optionParams);
    double putOption = -optionParams.SpotPrice * exp(-optionParams.DividendYield * optionParams.Tau) * CDF(-d1) +
                       optionParams.StrikePrice * exp(-optionParams.RiskFreeRate * optionParams.Tau) * CDF(-d2);
    return putOption > 0 ? putOption : 0;
}

/* Price calculation function for Binary Call Options */
double BinaryCall(const OptionParams &optionParams) {
    double d2 = D2(optionParams);
    double binaryCall = exp(-optionParams.RiskFreeRate * optionParams.Tau) * CDF(d2);
    return binaryCall > 0 ? binaryCall : 0;
}

/* Price calculation function for Binary Put Options */
double BinaryPut(const OptionParams &optionParams) {
    double d2 = D2(optionParams);
    double binaryPut = exp(-optionParams.RiskFreeRate * optionParams.Tau) * (1 - CDF(d2));
    return binaryPut > 0 ? binaryPut : 0;
}

/* Part of the BSE equation, encapsulated in own function for decoupling and readability */
double D1(OptionParams optionParams) {
    return (log(optionParams.SpotPrice / optionParams.StrikePrice) +
            (optionParams.RiskFreeRate - optionParams.DividendYield +
             0.5 * optionParams.Volatility * optionParams.Volatility) * optionParams.Tau) /
           (optionParams.Volatility * sqrt(optionParams.Tau));
}

/* Part of the BSE equation, encapsulated in own function for decoupling and readability */
double D2(OptionParams optionParams) {
    return (D1(optionParams) - optionParams.Volatility * sqrt(optionParams.Tau));
}

/* Cumulative distribution function for Normal Distribution */
double CDF(double X) {
    const double a1 = 0.319381530, a2 = -0.356563782, a3 = 1.781477937, a4 = -1.821255978, a5 = 1.330274429, pi =
            4.0 * atan(1.0);
    double x = fabs(X);
    double k = 1 / (1 + 0.2316419 * x);
    double n = (1 / sqrt(2 * pi)) * exp(-0.5 * x * x);
    double N = 1 - n * (a1 * k + a2 * k * k + a3 * pow(k, 3) + a4 * pow(k, 4) + a5 * pow(k, 5));
    double CDF = N;
    if (X < 0)
        CDF = 1 - N;
    return CDF;
}
