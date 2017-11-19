#pragma once

class game_object_interface {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool if_dead() = 0;
	virtual ~game_object_interface(){}
};

