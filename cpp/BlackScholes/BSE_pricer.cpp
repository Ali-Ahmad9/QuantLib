// Black-Scholes Equation Pricer C++ Program

#include<iostream>
#include<cmath>
#include<fstream>
#include "OptionParams.h"
#include "OptionPricingFunctions.h"

using namespace std;


/* Second parameter is a pointer to the function that calculates the option price
 * Each option type has its own option price calculation function
 * Therefore WriteResultsToFile can take any of these functions as a parameter and call it inside */
void WriteResultsToFile(OptionParams optionParams, double (*optionPriceFunction)(const OptionParams &));

OptionParams GetParams();

/* Handles inputting parameters for option price calculation
 * Creates a OptionParams object with all parameters and returns it */
OptionParams GetParams() {
    double spotPrice, volatility, riskFreeRate, time, expiry, strikePrice, dividendYield;
    cout << "Enter Spot Price: ";
    cin >> spotPrice;

    cout << "Enter Volatility: ";
    cin >> volatility;

    cout << "Enter Risk-Free Rate: ";
    cin >> riskFreeRate;

    cout << "Enter Time: ";
    cin >> time;

    cout << "Enter Expiry: ";
    cin >> expiry;

    cout << "Enter Strike Price: ";
    cin >> strikePrice;

    cout << "Enter Continuous constant dividend yield: ";
    cin >> dividendYield;

    OptionParams optionParams(spotPrice, volatility, riskFreeRate, time, expiry, strikePrice, dividendYield);
    return optionParams;
}

/* Main entry point into program
 * Takes in user choice on what option type to price
 * Then takes in option parameters  (e.g. Strike Price, Risk-free rate etc) by calling GetParams()
 * Displays the option price for the given spot price
 * Then calls WriteResultsToFile() to write a list of option prices over a range of spot prices around the one given
 * */
int main() {
    bool validChoice = false;
    double (*optionPriceFunction)(const OptionParams &); // the function to calculate the option price based on type
    while (!validChoice) {
        validChoice = true;
        cout << "What type of option?" << endl;
        cout << "1. European Call" << endl;
        cout << "2. European Put" << endl;
        cout << "3. Binary Call" << endl;
        cout << "4. Binary Put" << endl;
        int choice;
        cin >> choice;
        if (cin.fail()) { // if user enters not a int, has to re-enter
            cin.clear();
            cin.ignore();
            cout << "Not a valid number. Please re-enter" << endl;
        } else {
            switch (choice) {
                case 1:
                    cout << "You have chosen European Call" << endl;
                    optionPriceFunction = &EuroCall; // The function to calculate European Call options
                    break;
                case 2:
                    cout << "You have chosen European Put" << endl;
                    optionPriceFunction = &EuroPut;
                    break;
                case 3:
                    cout << "You have chosen Binary Call" << endl;
                    optionPriceFunction = &BinaryCall;
                    break;
                case 4:
                    cout << "You have chosen Binary Put" << endl;
                    optionPriceFunction = &BinaryPut;
                    break;
                default: // has to enter choice again
                    cout << "Unrecognised choice. Please enter choice again" << endl;
                    validChoice = false;
                    break;
            }
        }
    }
    OptionParams optionParams = GetParams(); // get option parameters
    double optionPrice = optionPriceFunction(optionParams); // execute price calculation function
    cout << "Option Price for spot price " << optionParams.SpotPrice << " is: " << optionPrice << endl; // Display price
    WriteResultsToFile(optionParams, optionPriceFunction); // writes results to .xls file
    cout << "Program Finished" << endl;
    return 0;
}


/* Function to write results to .xls file
 * Takes in the parameters of the option and the specific option pricing function
 * executes this function over a range of different spot prices to produce an option price curve visible in the .xls
 * */
void WriteResultsToFile(OptionParams optionParams, double (*optionPriceFunction)(const OptionParams &)) {
    cout << "Writing results to file..." << endl;
    ofstream out;
    out.open("BSE.xls"); // opens a file
    out << "Stock Price" << '\t' << "Option Price" << endl;
    double S, optionPrice;
    double lowerLimit = optionParams.SpotPrice - 90; // range of spot price is +\-90 of the spot price given
    double upperLimit = optionParams.SpotPrice + 90;
    for (S = lowerLimit; S <= upperLimit; S += 5.0) {
        optionParams.SpotPrice = S;
        optionPrice = optionPriceFunction(optionParams);
        out << S << '\t' << optionPrice << endl; // writes it to the file stream
    }
    cout << "Finished writing, closing file..." << endl;
    out.close(); // closes file
}