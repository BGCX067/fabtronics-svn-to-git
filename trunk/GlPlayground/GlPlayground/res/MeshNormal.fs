#version 420

in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

out vec4  daColor;


void main()
{
	daColor = vec4( color0, 1.0f) ;
}
