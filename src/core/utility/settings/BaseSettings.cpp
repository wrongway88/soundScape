#include "BaseSettings.h"

#include "cinder/Filesystem.h"

BaseSettings::BaseSettings()
{

}

BaseSettings::~BaseSettings()
{

}

void BaseSettings::setFilePath(const std::string& filePath, const std::string& fileName)
{
	m_filePath = filePath;
	m_fileName = fileName;

	loadFile();
}

void BaseSettings::saveSettings()
{
	if (m_filePath.length() > 0 && m_fileName.length() > 0)
	{
		createFilePath(m_filePath);

		saveFile();
	}
}

void BaseSettings::loadFile()
{
	if (boost::filesystem::exists(m_filePath + "/" + m_fileName))
	{
		ci::XmlTree file = ci::XmlTree(ci::loadFile(m_filePath + "/" + m_fileName));
		m_data = file.getChild("settings");
	}
	else
	{
		m_data = ci::XmlTree("settings", "");
	}
}

void BaseSettings::saveFile()
{
	m_data.write(ci::writeFile(m_filePath + "/" + m_fileName));
}

void BaseSettings::createFilePath(const std::string& filePath)
{
	boost::filesystem::create_directory(m_filePath);
}

std::vector<std::string> BaseSettings::seperateNodePath(const std::string& valuePath) const
{
	std::vector<std::string> result;
	char seperator = '/';

	std::string path = valuePath;

	std::size_t pos = path.find(seperator);
	while (pos != std::string::npos)
	{
		result.push_back(path.substr(0, pos));
		path = path.substr(pos + 1);
		pos = path.find(seperator);
	}

	if (path.length() > 0)
	{
		result.push_back(path);
	}

	return result;
}