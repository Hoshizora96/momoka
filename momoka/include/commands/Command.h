#pragma once

class Command {
public:
	virtual ~Command() = default;
private:
	virtual void Execute();
};
