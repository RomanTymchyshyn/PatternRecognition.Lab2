#pragma once

#include <vector>
#include <string>

class IFileWriter
{
	public:
		
		virtual bool WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append = false) const = 0;
		
		virtual bool WriteText(const std::string & nameOfFile, const std::string & text, bool append = false) const = 0;

		virtual bool WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const = 0;
		
		virtual bool WriteText(std::ofstream & fout, const std::string & text) const = 0;
};