#include <vector>
#include <iostream>
#include <time.h> 
#include "IFileReader.h"
#include "IFileWriter.h"
#include "Patient.h"
#include "PokFileReader.h"
#include "FileWriter.h"
#include "Helper.h"
#include "IMeasureCalculator.h"
#include "PetuninMeasureCalculator.h"
#include "SymmetricPetuninMeasureCalculator.h"
#include "Calculator.h"

std::vector<std::vector<double>> TransposeMatrix(const std::vector<std::vector<double>> &  matrix);

int main()
{
	clock_t time = clock();

	IFileReader* reader = new PokFileReader();
	IFileWriter* writer = new FileWriter();

	Helper* helper = new Helper(reader, writer);

	std::vector<Patient> group1 = helper->ReadGroup("ALLD2", "D2", ".POK", 60);
	std::vector<Patient> group2 = helper->ReadGroup("ALLD3", "D3", ".POK", 42);

	IMeasureCalculator* nonSymmetricCalculator = new PetuninMeasureCalculator();
	IMeasureCalculator* symmetricCalculator = new SymmetricPetuninMeasureCalculator();

	Calculator* calculator = new Calculator(group1, group2);

	std::ofstream fout("result.txt");


	std::cout << "Calculating Non-Symmetric ...\n\n";

	std::vector<std::vector<double>> averageMatrix = calculator->AverageMatrix(15, nonSymmetricCalculator);
	
	averageMatrix = TransposeMatrix(averageMatrix);

	writer->WriteText(fout, "Non-Symmetric\n");
	writer->WriteMatrix(fout, averageMatrix);

	time = clock() - time;

	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << "Finished Non-Symmetric!\nTime elapsed: " << ms << " ms" << std::endl << std::endl;
	
	std::cout << "Calculating Symmetric ...\n\n";

	averageMatrix = calculator->AverageMatrix(15, symmetricCalculator);

	averageMatrix = TransposeMatrix(averageMatrix);

	writer->WriteText(fout, "\n\nSymmetric\n");
	writer->WriteMatrix(fout, averageMatrix);

	std::cout << "Finished Symmetric!\nTime elapsed: " << ms << " ms" << std::endl << std::endl;

	fout.close();
	delete calculator;
	delete nonSymmetricCalculator;
	delete symmetricCalculator;
	delete helper;
	delete reader;
	delete writer;

	time = clock() - time;

	ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << "Press any key.\n";
	std::cin.get();

	return 0;
}

std::vector<std::vector<double>> TransposeMatrix(const std::vector<std::vector<double>> &  matrix)
{
	int cols = matrix.size();
	int rows = matrix[0].size();

	std::vector<std::vector<double>> result = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));

	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			result[i][j] = matrix[j][i];
		}
	}

	return result;
}
