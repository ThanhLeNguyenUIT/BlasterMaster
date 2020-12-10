#pragma once
#include "GlobalConfig.h"
class PlayerState {
public:
	PlayerState() {};
	virtual void HandleKeyboard() = 0;
	virtual void Update() = 0;
	
	STATENAME StateName;
	STATEOBJECT StateObject;
};