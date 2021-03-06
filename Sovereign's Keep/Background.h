#pragma once
#include "Renderable.h"
/*
	This will be the class that holds all the functions for adding backgrounds, such as the ground
	To add obstacles for the player, derive another class from this class?
*/

const float BACKGROUND_WIDTH = 4.0f;
const float BACKGROUND_HEIGHT = 3.0f;

const float MAIN_MENU_WIDTH = 1.0f;

class Background : public Renderable {

public:

	Background(Game* g, int rOrder, int defaultSpriteSheet);

	void render() ;

	void update(double dt) ;

private:


};