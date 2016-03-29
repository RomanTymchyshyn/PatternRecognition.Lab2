#pragma once

#include <vector>
#include "IMeasureCalculator.h"
#include "Patient.h"

enum AverageType { FirstFirst, FirstSecond, SecondSecond, SecondFirst };

class Calculator
{
	private:
		
		std::vector<Patient> _group1;

		std::vector<Patient> _group2;

		std::vector<Patient> GetPatientsPair(const AverageType & typeOfAverage, const int & i, const int & j);
		
		double Measure(const AverageType & typeOfAverage, const int & indicator, const int & firstPatientIndex, const int & secondPatientIndex, IMeasureCalculator* calculator);

		double AverageByPatientAndIndicator(const AverageType & typeOfAverage, const int & indicator, const int & patient, IMeasureCalculator* calculator);

		std::vector<double> AllAverageByPatientAndIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator);

		double AverageByIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator);

	public:
		
		Calculator(std::vector<Patient> group1, std::vector<Patient> group2);

		std::vector<std::vector<double>> AverageMatrix(const int & numOfIndicators, IMeasureCalculator* calculator);
};