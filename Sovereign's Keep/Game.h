#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <random> //for distributions and number engine
#include <ctime> //for generating seeds for the number engines
#include "Renderable.h"
#include "stb_image.h"

class Renderable;
struct HitBox;

/*
This class holds all references to all entities in the game. The main class. Will hold all functions for the game as well
*/

const float SCREEN_Y_MOVE_MODIFIER = 1.7777f;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1080.0f;

const float MAX_WAVE_TIME = 30.0f;

enum class SPRITE_SHEETS
{
	no_texture,
	player_default, player_idle, player_walking, player_attacking, player_attacking_2, player_casting, player_casting_2, background, basic_attack,
	slime,
	fire_icon, water_icon, earth_icon, air_icon,
	health_bar, mana_bar,

	fire_soul_basic_attack,
	multishot_basic_attack,
	fireball, waterbolt,
	explosion1, steam_blast,
	flame_ring, bubble_shot,
	mud_pit, boulder_shot,
	air_spike, barrage, flash_freeze, geyser,

	meteor, fire_beam, earth_spike, tsunami, earth_mine, water_beam, water_spout, earth_impale, saturn_rock, whirlwind,

	fire_golem_walking, fire_golem_attacking, fire_golem_attacking_left,
	water_golem_walking, water_golem_attacking, water_golem_attacking_left,
	air_golem_walking, air_golem_attacking, air_golem_attacking_left,

	bat, crab, minotaur, skull,
	slime_death,bat_death, crab_death, minotaur_death, skull_death,

	player_death, main_menu, start_button, how_to_play_button, exit_button,

	how_to_play,

};

enum class ELEMENTS {
	NONE, FIRE, WATER, EARTH, AIR, ELEC, ICE, GRAV
};


class Game {

public:

	//this is the int value for the map of all textures, use the names included here to generate new textures in the loadAllTextures function.
	


	Game();
	
	//Set up window and everything the game needs to function
	bool initialize();


	//will render all Renderable objects
	void render();

	//updates all Renderables
	void update(double dt);

	//deletes everything to shut down the program
	void cleanup();

	void setupBuffers();


	void renderableToPendingAdd(Renderable* r);

	//this function will generate every single texture into the map of all textures
	void loadAllTextures();

	//this function generates one specified texture
	void generateTexture(GLuint &tex, int w, int h, int nrC, std::string path);
	//void generateBackgroundTexture(GLuint& tex, int w, int h, int nrC, std::string path);

	//input TOP-LEFT xy, TOP_RIGHT xy, BOTTOM_RIGHT xy texture coordinates
	void setTextureCoordinates(float TRx, float TRy, float BRx, float BRy, float BLx, float BLy, float TLx, float TLy);

	void resetTextureCoordinates();

	//getters and setters

	GLFWwindow* getWindow();

	GLuint getVBO() { return VBO; }
	GLuint getVAO() { return VAO; }

	GLuint getRenderablesProgID() { return renderables_programID; }

	bool isPaused() { return paused; }
	void setPaused(bool p) { paused = p; }



	bool getSpellComboMode() { return spellComboMode; }
	void setSpellComboMode(bool b) { spellComboMode = b; }
	Renderable* getPlayer() { return player; }

	//send in the enum name that corresponds to the spritesheet, should get a reference to that texture in the form of a GLuint
	GLuint& getTextureFromMap(int a);

	void updateCamera(glm::vec3 playerOrigin);

	std::multimap<int, Renderable*>& getRenderQueue() { return renderQueue; }

	//true, the following draw will be a GUI element
	//false, the following draw will be a regular renderable
	void setGUIFlag(int b){
		GLint gui = glGetUniformLocation(renderables_programID, "GUI");
		glUniform1i(gui, b); }

	//this sends the structs for the elementsGUI
	void sendElementsData();

	std::mt19937& getNumberEngine() { return numberEngine; }

	//Enemy Wave functions
	void GenerateNextWave();
	void SpawnEnemy(int randomNum);

	void setFullscreen();


	//send a 0 for main menu
	//send a 1 for level
	//use this function for destroying then spawning all renderables needed
	//and for starting the logic of that mode
	void setGameMode(int mode);

	int getGameMode() {
		if (IN_MAIN_MENU) {
			return 0;
		}

		if (IN_LEVEL) {
			return 1;
		}
	}

	//returns true of the given renderable is being hovered over
	bool checkButtonHitBox(Renderable* b);


	Renderable* getStartButton() { return startButton; }
	Renderable* getHowToPlayButton() { return howToPlayButton; }
	Renderable* getExitButton() { return exitButton; }

	void displayInstructions(bool b);

	void setHowToPlayButton(Renderable* r) { howToPlayButton = r; }

	bool getDisplayInstructions() { return DISPLAY_INSTRUCTIONS; }
	void setDisplayInstructions(bool b) { DISPLAY_INSTRUCTIONS = b; }

	glm::mat4& getView() { return View; }

private:

	bool FULLSCREEN;

	bool IN_LEVEL;
	bool IN_MAIN_MENU;
	bool DISPLAY_INSTRUCTIONS;
	
	//window that everything is rendered to
	GLFWwindow* window;

	glm::vec3 cameraPosition; //will start at (0.0, 0.0, 1.0), which is pointing down the z axis
	glm::mat4 View; //this is the view matrix, send to vertex shader

	//holds the program for the vertex and fragment shaders
	GLuint renderables_programID;

	//holds the program for the GUI vertex and fragment shaders
	GLuint gui_programID;


	//Vertex Array Object for the game
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;


	//holds ALL renderables and in the correct render order
	/*
	1 - background object
	2 - player object
	3 - enemies
	4 - spells, basic attacks, effects
	5 - GUI objects
	6 - MENU objects
	*/
	std::multimap<int, Renderable*> renderQueue;

	//will hold all sprite sheets for EVERYTHING IN THE GAME, use an ENUM for the int
	std::map<int, GLuint> allSpriteSheets;

	//used for generating textures
	unsigned char* data;
	GLuint generatedTexture;

	std::vector<Renderable*> pendingAdd;
	std::vector<Renderable*> pendingDestroy;

	//used for default buffer creation
	
	std::vector<GLfloat> vertices;

	GLuint indices[6];

	bool paused; //if the game is paused, render everything as normal, but only update the menus and track mouse activity

	//use this pointer for ease of referencing the player, be sure to also add/change this pointer to/and the renderQueue!
	Renderable* player;

	Renderable* startButton;
	Renderable* howToPlayButton;
	Renderable* exitButton;
	Renderable* howToPlay;

	//true if SHIFT is held
	bool spellComboMode;


	//number engine
	std::mt19937 numberEngine;

	//Enemy Wave
	int WaveNumber; //The current wave the game is on. Ex. Wave 1, Wave 2, etc...
	float WaveTimer; //How long a given wave lasts.
	float SpawnTickRate; //How often enemys of that wave spawn.

	std::vector<Renderable*> baseEnemies; //Initialized in the initialized() function
	std::uniform_int_distribution<int> waveDistribution;
	std::uniform_real_distribution<float> enemyPosition;

};