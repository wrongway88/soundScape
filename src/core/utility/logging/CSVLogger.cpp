#include "CSVLogger.h"

#include <ctime>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>

const std::string CSVLogger::s_filePath = "data/log/";

CSVLogger::CSVLogger()
	: m_fileNamePrefix("")
{
	setupFileName();
	createDirectory();
}

CSVLogger::CSVLogger(const std::string& fileNamePrefix)
	: m_fileNamePrefix(fileNamePrefix)
{
	setupFileName();
	createDirectory();
}

CSVLogger::~CSVLogger()
{
}

void CSVLogger::logValue(const float value)
{
	writeToFile(value);
}

void CSVLogger::logValue(const std::string& value)
{
	writeToFile(value);
}

void CSVLogger::nextLine()
{
	std::ofstream fileStream;
	fileStream.open(s_filePath + m_fileName, std::ios::app);
	fileStream << std::endl;
	fileStream.close();
}

void CSVLogger::setupFileName()
{
	time_t time;
	std::time(&time);
	tm localTime = *std::localtime(&time);

	std::stringstream filename;
	filename << "table_";
	filename << m_fileNamePrefix << "_";
	filename << localTime.tm_mon << "-" << localTime.tm_mday << "_";
	filename << localTime.tm_hour << "-" << localTime.tm_min << "-" << localTime.tm_sec << ".csv";

	m_fileName = filename.str();
}

void CSVLogger::createDirectory()
{
	boost::filesystem::create_directory(s_filePath);
}

void CSVLogger::writeToFile(const std::string& message)
{
	std::ofstream fileStream;
	fileStream.open(s_filePath + m_fileName, std::ios::app);
	fileStream << message << ",";
	fileStream.close();
}

void CSVLogger::writeToFile(const float value)
{
	std::stringstream message;
	message << value;
	writeToFile(message.str());
}
