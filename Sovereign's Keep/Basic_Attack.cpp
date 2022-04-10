#include "Basic_Attack.h"

Basic_Attack::Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet)
	:Renderable(g, rOrder, defaultSpriteSheet) {

	resize(BULLET_WIDTH, BULLET_HEIGHT);


	damage = BASE_DAMAGE;
	speed = BULLET_BASE_SPEED;
	angle = 0.0f;
	direction = glm::vec3(1.0f, 0.0f, 0.0f); //points down x axis
}


void Basic_Attack::update(double dt) {

	getHitBox().updateHitBox(getOrigin(), 0.0f, 0.01f, 0.005f, 0.05f);

	
	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * dt * BULLET_BASE_SPEED, direction.y * dt * BULLET_BASE_SPEED, 0.0f));
	
	updatePosition(move);

}

void Basic_Attack::render() {

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}