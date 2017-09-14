#pragma once
#include "exception/MomokaException.h"

class ServiceNotRegistedException : public MomokaException {
public:
	explicit ServiceNotRegistedException(const std::string& messages) : MomokaException(messages) {
	}

	virtual ~ServiceNotRegistedException() throw() {
	};
};

class ServiceRegistedTwiceException: public MomokaException {
public:
	explicit ServiceRegistedTwiceException(const std::string& messages) : MomokaException(messages) {
	}

	virtual ~ServiceRegistedTwiceException() throw() {
	};
};