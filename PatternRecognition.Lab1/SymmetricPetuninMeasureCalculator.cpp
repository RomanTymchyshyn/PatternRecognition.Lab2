#include "SymmetricPetuninMeasureCalculator.h"

double SymmetricPetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y) const
{
	return (_petuninMeasureCalculator->Calculate(x, y) 
		+ _petuninMeasureCalculator->Calculate(y, x)) / 2.0;
}