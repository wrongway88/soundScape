#ifndef BASE_SETTINGS_H
#define BASE_SETTINGS_H

#include <string>

#include "cinder/Vector.h"
#include "cinder/Xml.h"

class BaseSettings
{
public:
	BaseSettings();
	virtual ~BaseSettings();

	void setFilePath(const std::string& filePath, const std::string& fileName);

	template<class T>
	T getValue(const std::string& valuePath, const T& standardValue);

	template<class T>
	void setValue(const std::string& valuePath, const T& value);

	void saveSettings();

private:
	void loadFile();
	void saveFile();
	void createFilePath(const std::string& filePath);

	std::vector<std::string> seperateNodePath(const std::string& valuePath) const;

	std::string m_filePath;
	std::string m_fileName;

	ci::XmlTree m_data;
};


template<class T>
T BaseSettings::getValue(const std::string& valuePath, const T& standardValue)
{
	ci::XmlTree* node = &m_data;

	std::vector<std::string> path = seperateNodePath(valuePath);

	for (unsigned int i = 0; i < path.size(); i++)
	{
		if (node->hasChild(path[i]))
		{
			node = &(node->getChild(path[i]));
		}
		else
		{
			ci::XmlTree newNode(path[i], "");
			node->push_back(newNode);
			node = &(node->getChild(path[i]));

			if (i == path.size() - 1)
			{
				node->setValue<T>(standardValue);
			}
		}
	}

	return node->getValue<T>(standardValue);
}

template<class T>
void BaseSettings::setValue(const std::string& valuePath, const T& value)
{
	ci::XmlTree* node = &m_data;

	std::vector<std::string> path = seperateNodePath(valuePath);

	for (unsigned int i = 0; i < path.size(); i++)
	{
		if (node->hasChild(path[i]))
		{
			node = &(node->getChild(path[i]));
		}
		else
		{
			ci::XmlTree newNode(path[i], "");
			node->push_back(newNode);
			node = &(node->getChild(path[i]));
		}
	}

	node->setValue<T>(value);
}

#endif // SETTINGS_H