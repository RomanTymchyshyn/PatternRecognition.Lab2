#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "IFileWriter.h"

class FileWriter: public IFileWriter
{
	public:
		virtual bool WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append = false) const;

		virtual bool WriteText(const std::string & nameOfFile, const std::string & text, bool append = false) const;

		virtual bool WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const;
		
		virtual bool WriteText(std::ofstream & fout, const std::string & text) const;
};