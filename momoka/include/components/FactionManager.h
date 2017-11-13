#pragma once
#include <map>
#include <list>
#include "objects/GameObject.h"
#include "util/HashedString.h"

class FactionManager {
private:
	
public:
	void RegisterFaction(const HashedString& hashedString);
	void UnRegisterFaction(const HashedString& hashedString);
};