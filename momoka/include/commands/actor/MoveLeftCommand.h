#pragma once
#include "commands/Command.h"
#include "objects/Entity.h"

class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(Entity* actor);
	~MoveLeftCommand() override;
	void Execute() override;
private:
	Entity* m_pEntity_;
};

inline MoveLeftCommand::MoveLeftCommand(Entity* entity) : m_pEntity_(entity) {
}

inline MoveLeftCommand::~MoveLeftCommand() {
}

inline void MoveLeftCommand::Execute() {
	m_pEntity_->MoveLeft();
}
