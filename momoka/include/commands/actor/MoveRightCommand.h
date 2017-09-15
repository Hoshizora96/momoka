#pragma once
#include "commands/Command.h"
#include "objects/Actor.h"

class MoveRightCommand : public Command {
public:
	MoveRightCommand(Actor* actor);
	~MoveRightCommand() override;
	void Execute() override;
private:
	Actor* m_pActor_;
};

inline MoveRightCommand::MoveRightCommand(Actor* actor) : m_pActor_(actor) {
}

inline MoveRightCommand::~MoveRightCommand() {
}

inline void MoveRightCommand::Execute() {
	m_pActor_->MoveRight();
}
