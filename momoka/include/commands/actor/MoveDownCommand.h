#pragma once
#include "commands/Command.h"
#include "objects/Actor.h"

class MoveDownCommand : public Command {
public:
	MoveDownCommand(Actor* actor);
	~MoveDownCommand() override;
private:
	void Execute() override;
	Actor* m_pActor_;
};

inline MoveDownCommand::MoveDownCommand(Actor* actor) : m_pActor_(actor) {
}

inline MoveDownCommand::~MoveDownCommand() {
}

inline void MoveDownCommand::Execute() {
	m_pActor_->MoveDown();
}
