// #version 330 core
// out vec4 FracColor;
// in vec3 ourColor;
// in vec2 ourTex;
// //sample fro texture
// uniform sampler2D texture_o;
// void main(){
//   // FracColor = vec4(ourColor, 1.0f);
//   FracColor = texture(texture_o , ourTex);
// }
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// uniform vec3 vcolor;
// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// FragColor = texture(texture1, TexCoord) * vec4(ourColor + vcolor, 1.0f);
	// FragColor = texture(texture1, TexCoord);
	FragColor = mix(texture(texture2, TexCoord), texture(texture1, TexCoord), 0.2	);
}