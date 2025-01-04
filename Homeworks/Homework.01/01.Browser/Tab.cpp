#include "Tab.h"

Tab::Tab(std::string url) : url(url), timestamp(std::time(nullptr)) { }

const std::string& Tab::getURL() const {
	return url;
}

long Tab::getTimestamp() const {
	return timestamp;
}

void Tab::setURL(std::string url) {
	this->url = url;
	timestamp = std::time(nullptr);
}