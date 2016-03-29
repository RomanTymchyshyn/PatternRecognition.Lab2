#include "Calculator.h"

Calculator::Calculator(std::vector<Patient> group1, 
	std::vector<Patient> group2)
{
	_group1 = group1;
	_group2 = group2;
}

std::vector<Patient> Calculator::GetPatientsPair(const AverageType & typeOfAverage, 
	const int & i, const int & j)
{
	std::vector<Patient> res;

	Patient p1 = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ?
		_group1[i] : _group2[i];
	res.push_back(p1);

	Patient p2 = typeOfAverage == FirstFirst || typeOfAverage == SecondFirst ?
		_group1[j] : _group2[j];
	res.push_back(p2);

	return res;
}

double Calculator::Measure(const AverageType & typeOfAverage, const int & indicator, 
	const int & firstPatientIndex, const int & secondPatientIndex, IMeasureCalculator* calculator)
{
	std::vector<Patient> patients = GetPatientsPair(typeOfAverage, firstPatientIndex, secondPatientIndex);

	return calculator->Calculate(patients[0].GetIndicatorSample(indicator), 
								 patients[1].GetIndicatorSample(indicator));
}

double Calculator::AverageByPatientAndIndicator(const AverageType & typeOfAverage, 
	const int & indicator, const int & patient, IMeasureCalculator* calculator)
{
	int numberOfComparedPatients = 0;

	switch(typeOfAverage)
	{
		case FirstFirst:
			numberOfComparedPatients = _group1.size() - 1;
			break;

		case FirstSecond:
			numberOfComparedPatients = _group2.size();
			break;

		case SecondFirst:
			numberOfComparedPatients = _group1.size();
			break;

		case SecondSecond:
			numberOfComparedPatients = _group2.size() - 1;
			break;
	}

	double sumOfMeasures = 0;
	int comparedToGroupSize = typeOfAverage == FirstFirst || typeOfAverage == SecondFirst ? 
		_group1.size() : _group2.size();

	for (int i = 0; i < comparedToGroupSize; ++i)
	{
		if ((typeOfAverage != FirstFirst && typeOfAverage != SecondSecond) || i != patient)
		{
			sumOfMeasures += Measure(typeOfAverage, indicator, patient, i, calculator);
		}
	}

	return sumOfMeasures / numberOfComparedPatients;
}

std::vector<double> Calculator::AllAverageByPatientAndIndicator(const AverageType & typeOfAverage, 
	const int & indicator, IMeasureCalculator* calculator)
{
	std::vector<double> res;
	int size = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ? 
		_group1.size() : _group2.size();

	for (int i = 0; i < size; ++i)
		res.push_back(AverageByPatientAndIndicator(typeOfAverage, indicator, i, calculator));

	return res;
}

double Calculator::AverageByIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator)
{
	int size = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ?
		_group1.size() : _group2.size();

	double sumOfAverages = 0;

	for (int i = 0; i < size; ++i)
		sumOfAverages += AverageByPatientAndIndicator(typeOfAverage, indicator, i, calculator);

	return sumOfAverages / size;
}

std::vector<std::vector<double>> Calculator::AverageMatrix(const int & numOfIndicators, IMeasureCalculator* measureCalculator)
{
	std::vector<std::vector<double>> res;

	for (int i = 0; i < 4; ++i)
	{
		std::vector<double> row;
		
		for (int j = 0; j < numOfIndicators; ++j)
		{
			row.push_back(AverageByIndicator((AverageType)i, j, measureCalculator));
		}

		res.push_back(row);
	}

	return res;
}