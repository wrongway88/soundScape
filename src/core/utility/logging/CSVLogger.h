#ifndef CSV_LOGGER_H
#define CSV_LOGGER_H

#include <string>

// first draft
class CSVLogger
{
public:
	CSVLogger();
	CSVLogger(const std::string& fileNamePrefix);
	~CSVLogger();

	void logValue(const float value);
	void logValue(const std::string& value);

	void nextLine();

private:
	void setupFileName();
	void createDirectory();

	void writeToFile(const std::string& message);
	void writeToFile(const float value);

	static const std::string s_filePath;

	std::string m_fileNamePrefix;
	std::string m_fileName;
};

#endif // CSV_LOGGER_H