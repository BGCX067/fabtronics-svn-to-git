#version 420


in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normal;

uniform mat4 MVP;
uniform mat4 Normal;

out vec2 texCoord0;
out vec3 normal0;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (Normal * vec4(normal, 0.0)).xyz;
}
