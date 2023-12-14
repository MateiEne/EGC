#pragma once

class State {
public:
	State() {}
	virtual ~State() {}

	virtual void Start() = 0;

	virtual void Update(float dt) = 0;

	virtual bool HasFinished() = 0;
};