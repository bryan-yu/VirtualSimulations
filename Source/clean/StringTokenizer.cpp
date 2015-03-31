#include "StdAfx.h"
#include "StringTokenizer.h"

void AABSEngine::Utility::StringTokenizer::TokenizeString(std::string line, std::vector<std::string> &container, char delimiter)
{
	//tokenize the string
	std::stringstream splitter(line);
	std::string data;

	while(std::getline(splitter, data, delimiter))
	{
		if(data != "")
		{
			//add the data to the custom vector for processing
			container.push_back(data);
		}
	}
}