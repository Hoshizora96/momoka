#pragma once
#include "commands/Command.h"
#include "objects/Entity.h"

class MoveDownCommand : public Command {
public:
	MoveDownCommand(Entity* entity);
	~MoveDownCommand() override;
	void Execute() override;
private:
	Entity* m_pEntity_;
};

inline MoveDownCommand::MoveDownCommand(Entity* entity) : m_pEntity_(entity) {
}

inline MoveDownCommand::~MoveDownCommand() {
}

inline void MoveDownCommand::Execute() {
	m_pEntity_->MoveDown();
}
