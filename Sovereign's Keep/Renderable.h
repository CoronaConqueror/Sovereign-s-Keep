#pragma once
#include "Game.h"
#include "GLM/gtc/type_ptr.hpp"

class Game;
/*
This class will be the parent of everything in that game that can be rendered, such as the player, enemies, menu system, and GUI entities
*/



class Renderable {

public:


	Renderable(Game* g, int rOrder, int w, int h, int c, std::string path);
	~Renderable() {}

	//these are overriden!
	virtual void update(double dt) ; //update the Renderable

	virtual void render() ; //draw Renderable to the screen

	

	
	int renderOrder; //from 1 - 6?

	/*
		CHECK IF THIS WORKS
	*/
	bool operator<(const Renderable& r2) {
		if (this->renderOrder < r2.renderOrder) {
			return true;
		}
		else
		{
			return false;
		}
	}


	void setTexture(int w, int h, int nrC, std::string path);


	/*
		GETTERS AND SETTERS
	*/

	Game* getGame() { return game; }

	void setO2W(glm::mat4 s) { objectToWorld = s; }
	glm::mat4& getO2W() { return objectToWorld; }

	GLuint getTexture() { return texture; }

	//std::vector<GLfloat>& getPosition() { return position; }
	//std::vector<GLfloat>& getColor() { return colors; }
	//std::vector<GLfloat>& getTexCoord() { return textureCoordinates; }


private:

	

	//origin?
	glm::vec3 origin;

	//texture for the renderable, need width, height, color channels, and the unsigned char* for the actual image
	int textureWidth;
	int textureHeight;
	int nrChannels;
	unsigned char* data;
	GLuint texture;


	//transformation matrix
	glm::mat4 objectToWorld;

	//this pointer allows every renderable object to be able to call game functions
	//such as creating new enemies.
	Game* game;

	


};




