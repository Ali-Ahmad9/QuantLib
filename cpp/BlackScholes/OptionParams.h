//
// Created by Ali Ahmad on 24/04/2022.
//

#pragma once

/* Class to encapsulate all the parameters needed to price options.
 * Using this as a cleaner way of passing this data between functions
 * additionally provides default arguments */

class OptionParams {
public:
    double SpotPrice;
    double Volatility;
    double RiskFreeRate;
    double Time;
    double Expiry;
    double StrikePrice;
    double DividendYield;
    double Tau;

public:
    OptionParams(double s = 100, double vol = 0.2, double r = 0.05, double t = 0, double T = 1, double e = 100,
                 double d = 0);
};
