#pragma once
#include <string>
#include <functional>
#include <ostream>

class HashedString {
private:
	std::size_t hash;
	std::string string;

public:
	explicit HashedString(const std::string string);
	~HashedString();

	bool operator==(const HashedString& other) const;
	bool operator!=(const HashedString& other) const;
	const std::size_t GetHash() const;
	const std::string& GetString() const;
};
