#pragma once
#include "mixin/Updatable.h"

class GameObject: public Updatable {
public:
	virtual ~GameObject() = default;
	static int GenerateObjectId();

private:
	static unsigned int m_nextId_;

public:
	explicit GameObject(int id = GenerateObjectId());

	int GetId() const;
	bool IsActive() const;
	void SetActive(bool active);

	void Update(float dt) override;

private:
	unsigned int m_id_;
	bool m_isActive_;

	
};
