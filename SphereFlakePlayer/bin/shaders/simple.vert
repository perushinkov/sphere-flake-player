#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos4 = vec4(position, 1.0f);

    gl_Position = projection * view * translation * pos4;
	
	
	fragNormal = normal;
	fragPos = position;
}