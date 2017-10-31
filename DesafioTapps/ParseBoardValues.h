#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

#include "Property.h"

using namespace std;
class ParseBoardValues {
public:
	vector<Property*> properties;

	ParseBoardValues();
	~ParseBoardValues();
	void Parse();
	vector <Property*> CopyProperties();
};

