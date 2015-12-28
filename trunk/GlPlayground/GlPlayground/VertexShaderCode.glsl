#version 420
in layout(location=0) vec3  position;
in layout(location=1) vec3  vertexColor;
in layout(location=2) vec3  normal;


uniform mat4 fullTransformMatrix;
uniform vec3 dominatingColor;

out vec3  theColor;

void main()
{
	vec4 v = vec4(position, 1.0);
	gl_Position = fullTransformMatrix * v ;
	theColor = vertexColor;
	//theColor = normal;
	//theColor = vec3(1.0f,1.0f, 0.0f);
}

