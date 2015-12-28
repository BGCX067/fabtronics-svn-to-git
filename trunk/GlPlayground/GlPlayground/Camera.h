#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include "ssg.h"

class Camera
{
public:
	Camera( const SSG::SceneSpace& parent );

	SSG::SceneSpace& GetSpace();

	void SetPosition( const SSG::Coord3& position);
	void Translate( const glm::vec3& delta);


	glm::mat4 getWorldToViewMatrix() const;
	glm::mat4 GetViewProjection() const; 
	glm::mat4 getVP() const; 

	void SetProjection( const glm::mat4& value );

	void mouseUpdate( const glm::vec2& newMousePosition, bool start = false );
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void straveRight();
	void moveUp();
	void moveDown();

private:
	void operator=(const Camera& mesh);
	Camera(const Camera& mesh);

	SSG::SceneSpace _sceneSpace;
	glm::mat4 _projection;

	glm::vec3 _position;
	glm::vec3 _viewDirection;
	const glm::vec3 UP;
	glm::vec2 _oldMousePosition;
};



#endif