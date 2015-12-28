#version 420

in layout(location = 0) vec3 vertexPositionModel;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normalModel;
in layout(location = 3) vec3 vertexColor;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat3 normalsToWorldMatrix;

out vec2 theTexCoord;
out vec3 normalWorld;
out vec3 theColor;
out vec3 vertexPositionWorld;


uniform vec3 lightPositionWorld;

void main()
{
	vec4 v = vec4(vertexPositionModel, 1.0);
	gl_Position = modelToProjectionMatrix * v ;
	//normalWorld =  vec3( modelToProjectionMatrix * vec4( normalModel, 0.0 ));

	vertexPositionWorld = vec3(modelToWorldMatrix * v );

	theColor = vertexColor;
	theTexCoord = texCoord;



	//vec3 lightColor = normalize( lightPositionWorld - vertexPositionModel);
	//float brightness =  dot (lightColor , normalModel );
	//theColor = vec3(brightness,brightness,brightness);

	normalWorld =  normalModel;
}
