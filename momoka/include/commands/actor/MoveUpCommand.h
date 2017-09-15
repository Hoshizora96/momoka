#pragma once
#include "commands/Command.h"
#include "objects/Actor.h"

class MoveUpCommand : public Command {
public:
	MoveUpCommand(Actor* actor);
	~MoveUpCommand() override;
private:
	void Execute() override;
	Actor* m_pActor_;
};

inline MoveUpCommand::MoveUpCommand(Actor* actor) : m_pActor_(actor) {
}

inline MoveUpCommand::~MoveUpCommand() {
}

inline void MoveUpCommand::Execute() {
	m_pActor_->MoveUp();
}
