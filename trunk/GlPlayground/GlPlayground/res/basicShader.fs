#version 420

in vec2 texCoord0;
in vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

out vec4  daColor;


void main()
{
	daColor = texture2D(sampler, texCoord0) * 
		clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}
