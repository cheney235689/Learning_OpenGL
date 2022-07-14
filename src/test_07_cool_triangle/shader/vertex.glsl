// #version 330 core
// layout (location = 0 )in vec3 aPos;
// layout (location = 1 )in vec3 aColor;
// out vec3 ourColor;
// void main(){
//     gl_Position =  vec4(aPos.x, aPos.y, aPos.z, 1.0f);
//     ourColor = aColor;
// }

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float x_offset;
uniform float y_offset;
void main(){
  // gl_Position = vec4(aPos.x , aPos.y , aPos.z , 1.0f);
  gl_Position = vec4(aPos.x + x_offset , -aPos.y + y_offset , aPos.z , 1.0f);
  //x_offset+upside down
  ourColor = aColor;
}
//測試7頂點著色器