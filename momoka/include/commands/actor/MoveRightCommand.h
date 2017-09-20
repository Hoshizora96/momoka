#pragma once
#include "commands/Command.h"
#include "objects/Entity.h"

class MoveRightCommand : public Command {
public:
	MoveRightCommand(Entity* actor);
	~MoveRightCommand() override;
	void Execute() override;
private:
	Entity* m_pEntity_;
};

inline MoveRightCommand::MoveRightCommand(Entity* entity) : m_pEntity_(entity) {
}

inline MoveRightCommand::~MoveRightCommand() {
}

inline void MoveRightCommand::Execute() {
	m_pEntity_->MoveRight();
}
