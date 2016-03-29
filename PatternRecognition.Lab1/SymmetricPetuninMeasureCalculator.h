#pragma once

#include <vector>
#include <algorithm>
#include "IMeasureCalculator.h"
#include "PetuninMeasureCalculator.h"

class SymmetricPetuninMeasureCalculator: public IMeasureCalculator
{
	private:
		IMeasureCalculator* _petuninMeasureCalculator;
	public:
		SymmetricPetuninMeasureCalculator()
		{
			_petuninMeasureCalculator = new PetuninMeasureCalculator();
		};
		virtual double Calculate(std::vector<double> sample1, std::vector<double> sample2) const;
		~SymmetricPetuninMeasureCalculator()
		{
			delete _petuninMeasureCalculator;
		};
};