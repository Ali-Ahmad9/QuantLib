//
// Created by Ali Ahmad on 24/04/2022.
//
#include<cmath>
#include "OptionParams.h"
#pragma once


double CDF(double);

double D1(OptionParams);

double D2(OptionParams);

double EuroCall(const OptionParams &optionParams);

double EuroPut(const OptionParams &optionParams);

double BinaryCall(const OptionParams &optionParams);

double BinaryPut(const OptionParams &optionParams);
