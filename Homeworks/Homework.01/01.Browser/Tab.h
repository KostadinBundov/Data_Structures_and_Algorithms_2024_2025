#pragma once
#include <ctime>
#include <chrono>
#include <iostream>

class Tab {
private:
	std::string url;
	long timestamp;

public:
	Tab(std::string url);

	const std::string& getURL() const;
	long getTimestamp() const;

	void setURL(std::string url);
};