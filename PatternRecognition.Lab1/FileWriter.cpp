#include "FileWriter.h"

bool FileWriter::WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append) const
{
	std::ofstream fout;
	try
	{
		if (append)
			fout.open(nameOfFile, std::fstream::app);
		else
			fout.open(nameOfFile, std::fstream::trunc);

		bool success = WriteMatrix(fout, matrix);

		fout.close();

		return success;
	}
	catch(const std::exception &)
	{
		if (fout.is_open())
			fout.close();

		return false;
	}
}

bool FileWriter::WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const
{
	try
	{
		if (!fout)
			return false;

		int numOfRows = matrix.size();
		fout.precision(10);

		for (int i = 0; i < numOfRows; ++i)
		{
			int numOfColumns = matrix[i].size();
			
			for (int j = 0; j < numOfColumns; ++j)
			{
				fout.width(15);
				fout << std::right << matrix[i][j];
			}
			
			if (i != numOfRows - 1)
				fout<< std::endl;
		}
		return true;
	}
	catch(const std::exception &)
	{
		return false;
	}
}

bool FileWriter::WriteText(const std::string & nameOfFile, const std::string & text, bool append) const
{
	std::ofstream fout;
	try
	{
		if (append)
			fout.open(nameOfFile, std::fstream::app);
		else
			fout.open(nameOfFile, std::fstream::trunc);

		bool success = WriteText(fout, text);

		fout.close();

		return success;
	}
	catch(const std::exception &)
	{
		if (fout.is_open())
			fout.close();

		return false;
	}
}

bool FileWriter::WriteText(std::ofstream & fout, const std::string & text) const
{
	try
	{
		if (!fout)
			return false;

		fout << text;

		return true;
	}
	catch(const std::exception &)
	{
		return false;
	}
}