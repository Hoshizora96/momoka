#pragma once
#include <stdexcept>
#include <string>

class MomokaException : public std::runtime_error {
public:
	explicit MomokaException(const std::string& message);
	virtual ~MomokaException() throw() {}
};

inline MomokaException::MomokaException(const std::string& message) : runtime_error(message){
}