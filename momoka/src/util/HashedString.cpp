#include "stdafx.h"
#include "util/HashedString.h"

std::ostream& operator<<(std::ostream& message, HashedString& string) {
	message << string.GetString();
	return message;
}

HashedString::HashedString(const std::string string): hash(0), string(string) {
	const std::hash<std::string> hashingFunction;
	hash = hashingFunction(string);
}

HashedString::~HashedString() {
}

bool HashedString::operator==(const HashedString& other) const {
	return GetHash() == other.GetHash();
}

bool HashedString::operator!=(const HashedString& other) const {
	return GetHash() != other.GetHash();
}

const std::size_t HashedString::GetHash() const {
	return hash;
}

const std::string& HashedString::GetString() const {
	return string;
}
