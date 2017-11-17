#pragma once
class GameState {
public:
	virtual ~GameState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
};
