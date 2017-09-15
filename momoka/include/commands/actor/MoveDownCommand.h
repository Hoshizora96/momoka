#pragma once
#include "commands/Command.h"
#include "objects/Actor.h"

class MoveDownCommand : public Command {
public:
	MoveDownCommand(Actor* actor);
	~MoveDownCommand() override;
	void Execute() override;
private:
	Actor* m_pActor_;
};

inline MoveDownCommand::MoveDownCommand(Actor* actor) : m_pActor_(actor) {
}

inline MoveDownCommand::~MoveDownCommand() {
}

inline void MoveDownCommand::Execute() {
	m_pActor_->MoveDown();
}
