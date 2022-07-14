#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 transform;


// uniform float x_offset;
// uniform float y_offset;
void main()
{
	// gl_Position = vec4(aPos.x + x_offset , -aPos.y + y_offset , aPos.z , 1.0f);
	gl_Position = transform * vec4(aPos.x  , aPos.y  , aPos.z , 1.0f);
	ourColor = aColor;
	// TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	TexCoord = aTexCoord ;
}