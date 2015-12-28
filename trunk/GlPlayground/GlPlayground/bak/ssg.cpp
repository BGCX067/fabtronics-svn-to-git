#include "ssg.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


const glm::vec3 AxisX= glm::vec3(1.0f, 0.0f, 0.0f );
const glm::vec3 AxisY= glm::vec3(0.0f, 1.0f, 0.0f );
const glm::vec3 AxisZ= glm::vec3(0.0f, 0.0f, 1.0f );


//SsgTransformation::SsgTransformation()
//{
//}
//
//SsgTransformation::SsgTransformation(const glm::mat4& matrix)
//{
//	_matrix = matrix; 
//	_matrix = glm::inverse(matrix);
//}
//
//SsgTransformation::SsgTransformation(const SsgTransformation& rhs )
//{
//	_matrix = rhs._matrix;
//	_matrixInverse = rhs._matrixInverse;
//}
//
//glm::vec3 SsgTransformation::GetTranslationVector() const 
//{
//	return (glm::vec3)glm::row(_matrix,0);
//}
//
//glm::vec3 SsgTransformation::GetScaleVector() const 
//{
//	
//	return glm::vec3(	glm::column(_matrix,0).length(),
//						glm::column(_matrix,1).length(),
//						glm::column(_matrix,2).length() );
//}
//
//glm::mat4 SsgTransformation::GetRotationMatrix() const 
//{
//	auto scaleVector = GetScaleVector();
//	glm::mat4 rotationMatrix;
//
//    rotationMatrix[0, 0] = _matrix[0, 0] / scaleVector.x;
//    rotationMatrix[0, 1] = _matrix[0, 1] / scaleVector.y;
//    rotationMatrix[0, 2] = _matrix[0, 2] / scaleVector.z;
//
//    rotationMatrix[1, 0] = _matrix[1, 0] / scaleVector.x;
//    rotationMatrix[1, 1] = _matrix[1, 1] / scaleVector.y;
//    rotationMatrix[1, 2] = _matrix[1, 2] / scaleVector.z;
//
//    rotationMatrix[2, 0] = _matrix[2, 0] / scaleVector.x;
//    rotationMatrix[2, 1] = _matrix[2, 1] / scaleVector.y;
//    rotationMatrix[2, 2] = _matrix[2, 2] / scaleVector.z;
//
//	return rotationMatrix;
//}
//
//glm::vec3 SsgTransformation::Transform(const glm::vec3& vector)
//{
//    return glm::mat3( _matrix ) * vector;
//}
//
//glm::vec3 SsgTransformation::TransformInverse(const glm::vec3& vector)
//{
//    return glm::mat3( _matrixInverse ) * vector;
//}
//
//void SsgTransformation::Multiply(const SsgTransformation& transformation)
//{
//	_matrix = _matrix * transformation._matrix;
//	_matrixInverse = _matrixInverse * transformation._matrixInverse;
//}
//
//void SsgTransformation::RotateAxis(float angle, const glm::vec3& axis)
//{
//	_matrix = glm::rotate(_matrix, angle * 180.0f / 3.1415926f, axis);
//	_matrixInverse = glm::rotate(_matrixInverse, -angle * 180.0f / 3.1415926f, axis);
//}
//
//void SsgTransformation::Translate(const glm::vec3& deltaTranslation)
//{
//	auto tm = glm::mat4();
//	tm[3] = glm::vec4(deltaTranslation, 1.0f);
//	_matrix = tm * _matrix;
//	tm[3] = glm::vec4(-deltaTranslation, 1.0f);
//	_matrixInverse = _matrixInverse * tm;
//}
//
//void SsgTransformation::Scale(const glm::vec3& scaling)
//{
//	_matrix = glm::scale(_matrix, scaling);
//	_matrixInverse = _matrixInverse * glm::scale( 1.0f/scaling);
//}
//
//SsgSpace::SsgSpace()
//{
//}
//
//
//
//
//SsgSpace::SsgSpace(const std::string& name)
//{
//	_name = name; 
//}
//
//ssg::ssg(void)
//{
//}
//
//
//ssg::~ssg(void)
//{
//}
