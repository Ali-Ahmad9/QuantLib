//
// Created by Ali Ahmad on 24/04/2022.
//

#include "OptionParams.h"

OptionParams::OptionParams(double s, double vol, double r, double t, double T, double e,
                              double d) {
            SpotPrice = s;
            Volatility = vol;
            RiskFreeRate = r;
            Time = t;
            Expiry = T;
            StrikePrice = e;
            DividendYield = d;
            Tau = Expiry - Time; // tau is calculated when class is instantiated
};