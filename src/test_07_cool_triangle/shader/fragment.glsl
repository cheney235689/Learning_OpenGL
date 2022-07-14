// #version 330 core
// out vec4 FragColor;
// in vec3 ourColor;

// void main(){
//     FragColor = vec4(ourColor, 1.0f);
// }
#version 330 core
out vec4 FracColor;
in vec3 ourColor;
uniform vec3 vcolor;
void main(){
  FracColor = vec4(ourColor + vcolor, 1.0f);
}

//Fragmet著色器