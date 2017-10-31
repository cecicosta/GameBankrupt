#include "stdafx.h"
#include "ParseBoardValues.h"

#include <iostream>
#include <fstream>
#include <string>


ParseBoardValues::ParseBoardValues()
{}

ParseBoardValues::~ParseBoardValues()
{
	for each (Property* p in properties){
		delete p;
	}
	properties.clear();
}

void ParseBoardValues::Parse()
{
	ifstream io;
	io.open("gameConfig.txt");

	string line;
	while (io.is_open() && getline(io, line)) {
		int firstDelimiter = line.find(" ");

		const string selling = line.substr(0, firstDelimiter);
		const string rent = line.substr(firstDelimiter, line.length() - 1);

		//Create property with its rent and selling loaded values
		Property* property = new Property(std::atoi(selling.c_str()), std::atoi(rent.c_str()));

		properties.push_back(property);
	}
}

vector<Property*> ParseBoardValues::CopyProperties()
{
	vector<Property*> copy;
	for each (Property* p in properties)
	{
		copy.push_back(new Property(*p));
	}
	return copy;
}
