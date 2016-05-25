#version 330 core

uniform vec3 ourColor;
uniform vec3 cameraPos;

in vec3 fragNormal;
in vec3 fragPos;


out vec4 color;

void main()
{
	float lightStrength = 0.5;
	vec3 ray = fragPos - cameraPos;
	float cos = -(dot(normalize(fragNormal), normalize(ray)));
    
	// Going for a somewhat plastic feeling with that. No specular light. Just diffused.
	float adjustedVal = atan((cos / length(ray))*lightStrength)*(0.5 + cos*0.7);

	color = vec4(adjustedVal*1.0, adjustedVal*0.5, adjustedVal*0.2, 1.0);
	//color = vec4(1.0, 0.8, 0.3, 1.0);
} 