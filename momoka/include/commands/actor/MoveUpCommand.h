#pragma once
#include "commands/Command.h"
#include "objects/Entity.h"

class MoveUpCommand : public Command {
public:
	MoveUpCommand(Entity* actor);
	~MoveUpCommand() override;
	void Execute() override;
private:
	Entity* m_pEntity_;
};

inline MoveUpCommand::MoveUpCommand(Entity* entity) : m_pEntity_(entity) {
}

inline MoveUpCommand::~MoveUpCommand() {
}

inline void MoveUpCommand::Execute() {
	m_pEntity_->MoveUp();
}
