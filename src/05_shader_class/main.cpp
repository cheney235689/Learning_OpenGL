#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tool/shader.h>
//using more attribute to draw a colorful triangle

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
//vertex shader source code
std::string Shader::dirName;
int main()
{
  glfwInit();
  // 設置主要與次要版本
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 創建視窗對象
  GLFWwindow *window = glfwCreateWindow(800, 600, "05_shader_class", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  // 設置視窗
  glViewport(0, 0, 800, 600);

  // 監聽視窗變化
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Shader ourShader("D://OpenGL_proj//src//05_shader_class//shader//vertex.glsl", 
  "D://OpenGL_proj//src//05_shader_class//shader//fragment.glsl");
  //vertex(頂點)輸入
  //Normalized coor.(-1,1)
  float vertices[] = {
       0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
  };
  ///生成VBO,VAO
  unsigned int VBO,VAO;
  glGenBuffers(1, &VBO);  
  glGenVertexArrays(1,&VAO);
  
  //綁定(目標,VAO)
  glBindVertexArray(VAO);
  //綁定(目標,VBO)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  //填充資料 (目標,資料大小,資料,希望GPU如何管理數據)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //GL_STATIC_DRAW :數據不會 或者幾乎不會改變
  //GL_DYNAMIC_DRAW : 數據會更改很多
  //GL_STREAM_DRAW :數據每次繪製都會改變,需使顯卡將數據放在能高速寫入的記憶體部分
  

  //設置vertex屬性指標
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  //(屬性位置,屬性大小,數據類型,是否Normalized,步長,起始點偏移量)
  //啟用
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3* sizeof(float)) );
  glEnableVertexAttribArray(1);
  
  glBindVertexArray(0);
  

  
  ////渲染迴圈////
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    // 渲染指令
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();
    
    //綁定VAO
    glBindVertexArray(VAO);
    
    //繪製(模式,起點,點數)
    glDrawArrays(GL_TRIANGLES,0,3);
    
    // glDrawArrays(GL_POINTS,0,3);  //三點
    // glDrawArrays(GL_LINE_LOOP,0,3); //三線


     glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, 800, 600); 
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}