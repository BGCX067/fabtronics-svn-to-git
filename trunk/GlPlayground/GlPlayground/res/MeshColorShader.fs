#version 420

in vec2 theTexCoord;
in vec3 normalWorld;
in vec3 theColor;
in vec3 vertexPositionWorld;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform vec3 lightPositionWorld;
uniform vec4 ambientLight;

out vec4  daColor;


void main()
{
    //vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	//float brightness = dot(lightVectorWorld, normalize(normalWorld));
    //vec4 diffuseLight = clamp( vec4( brightness,brightness,brightness, 1.0f),0,1);
    
    //daColor = diffuseLight + ambientLight;
    //daColor = vec4(theColor,1.0);


   vec3 lightColor = normalize( lightPositionWorld - vertexPositionWorld);
	float brightness =  dot (lightColor , normalWorld );
	daColor = vec4(brightness,brightness,brightness, 1.0f);


}
