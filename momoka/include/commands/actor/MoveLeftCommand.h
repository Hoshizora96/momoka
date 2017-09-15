#pragma once
#include "commands/Command.h"
#include "objects/Actor.h"

class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(Actor* actor);
	~MoveLeftCommand() override;
	void Execute() override;
private:
	Actor* m_pActor_;
};

inline MoveLeftCommand::MoveLeftCommand(Actor* actor) : m_pActor_(actor) {
}

inline MoveLeftCommand::~MoveLeftCommand() {
}

inline void MoveLeftCommand::Execute() {
	m_pActor_->MoveLeft();
}
