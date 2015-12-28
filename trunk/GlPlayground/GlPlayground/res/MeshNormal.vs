#version 420


in layout(location = 0) vec3 vertexPositionModel;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normalModel;
in layout(location = 3) vec3 vertexColor;

uniform mat4 ModelToProjectionMatrix;
uniform mat3 NormalsToWorldTransform;

out vec3 color0;

void main()
{
	gl_Position = ModelToProjectionMatrix * vec4(vertexPositionModel, 1.0);
	color0 = normalModel;
}
