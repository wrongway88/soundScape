#include "FileLogger.h"

#include <fstream>
#include <sstream>

#include <time.h>

#include <filesystem>

const std::string FileLogger::s_filePath = "data/log/";

FileLogger::FileLogger()
	: Logger("FileLogger")
{
	setupFileName();
	createDirectory();
}

FileLogger::~FileLogger()
{
}

void FileLogger::logInfo(const LogMessage& message)
{
	logMessage("INFO", message);
}

void FileLogger::logWarning(const LogMessage& message)
{
	logMessage("WARNING", message);
}

void FileLogger::logError(const LogMessage& message)
{
	logMessage("ERROR", message);
}

void FileLogger::createDirectory()
{
	/*std::experimental::filesystem::path path = std::experimental::filesystem::current_path();
	path.append(s_filePath);

	std::experimental::filesystem::create_directory(path);*/
}

void FileLogger::setupFileName()
{
	time_t time;
	std::time(&time);
	tm localTime;
	__time64_t long_time;
	localtime_s(&localTime, &long_time);

	std::stringstream filename;
	filename << "log_";
	filename << localTime.tm_mon + 1 << "-" << localTime.tm_mday << "_";
	filename << localTime.tm_hour << "-" << localTime.tm_min << "-" << localTime.tm_sec << ".txt";

	m_fileName = filename.str();
}

void FileLogger::logMessage(const std::string& type, const LogMessage& message)
{
	std::ofstream fileStream;
	fileStream.open(s_filePath + m_fileName, std::ios::app);
	fileStream
		<< message.getTimeString("%H:%M:%S") << " | "
		<< message.getFileName() << ':' << message.line << ' ' << message.functionName << "() | "
		<< type << ": " << message.message
		<< std::endl;
	fileStream.close();
}
