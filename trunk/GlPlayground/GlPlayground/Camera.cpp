
#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"

#include "Camera.h"


Camera::Camera( const SSG::SceneSpace& parent )
	:_sceneSpace(parent)
	,_position(0.2019f, 3.63f, 4.53f )
	,_viewDirection(-0.0672f, -0.636f, -0.76f )
	,UP(0.0f, 1.0f, 0.0f )
{
}

SSG::SceneSpace& Camera::GetSpace()
{
	return _sceneSpace;
}

void Camera::Translate( const glm::vec3& delta)
{
	_sceneSpace.Translate(delta);
}

void Camera::SetProjection( const glm::mat4& value ) 
{ 
	_projection = value;
} 

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return _sceneSpace.GetTransformationToRoot().GetMatrixInverse();
}

glm::mat4 Camera::GetViewProjection() const 
{
	return _projection * _sceneSpace.GetTransformationToRoot().GetMatrixInverse();
}



glm::mat4 Camera::getVP() const
{
	return _projection * glm::lookAt(_position, _position + _viewDirection, UP );
}

const float MOVEMENTSPEED = 0.1f;


void Camera::moveForward()
{
	_position += MOVEMENTSPEED * _viewDirection;
}

void Camera::moveBackward()
{
	_position += -MOVEMENTSPEED * _viewDirection;
}

void Camera::strafeLeft()
{
	auto strafeDirection = glm::cross(_viewDirection, UP );
	_position += -MOVEMENTSPEED * strafeDirection;	}

void Camera::straveRight()
{
	auto strafeDirection = glm::cross(_viewDirection, UP );
	_position += MOVEMENTSPEED * strafeDirection;
}
void Camera::moveUp()
{
	_position += MOVEMENTSPEED * UP;
}
void Camera::moveDown()
{
	_position += -MOVEMENTSPEED * UP;
}

void Camera::mouseUpdate( const glm::vec2& newMousePosition, bool start  )
{
	if ( !start ) 
	{
		const float ROTATIONAL_SPEED = 0.1f;

		auto mouseDelta = newMousePosition - _oldMousePosition;
		_viewDirection =glm::mat3( glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, UP ) ) * _viewDirection;

		glm::vec3 toRotateAround = glm::cross(_viewDirection, UP );

		_viewDirection =glm::mat3( glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, toRotateAround ) ) * _viewDirection;
	}
	_oldMousePosition = newMousePosition;

}
