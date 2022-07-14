#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//using more vertices to draw more triangles



void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
//vertex shader source code
const char *vertexShaderSource =  "#version 330 core\n" 
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                  "}\n";
//fragment shader source code
const char *fragmentShaderSource =  "#version 330 core\n"
                                    "out vec4 FragColor;"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(0.5f, 0.1f, 0.1f, 1.0f);\n"
                                    "}\n";

int main()
{
  glfwInit();
  // 設置主要與次要版本
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 創建視窗對象
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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


  //vertex(頂點)輸入
  //Normalized coor.(-1,1)
  float vertices[] = {
    0.3f, 0.0f, 0.0f,
    0.9f, 0.0f, 0.0f,
    0.6f,  0.5f, 0.0f,
    
    -0.3f, 0.0f, 0.0f,
    -0.9f, 0.0f, 0.0f,
    -0.6f,  0.5f, 0.0f,
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
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  //(屬性位置,屬性大小,數據類型,是否Normalized,步長,起始點偏移量)
   
  //啟用
  glEnableVertexAttribArray(0);
  //綁定
  glBindVertexArray(0);

  
  //創建Vertex shader與Fragment Shader
  unsigned int vertexShader,fragmentShader; 
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  //附加shader代碼 
  //glShaderSource(編譯對象,傳遞數量,shadr代碼,NULL)
  
  //vertex
  glShaderSource(vertexShader, 1 , &vertexShaderSource , NULL);
  glCompileShader(vertexShader);  //編譯shader
  
  //fragment
  glShaderSource(fragmentShader, 1 , &fragmentShaderSource , NULL);
  glCompileShader(fragmentShader);  //編譯shader


  //檢測是否編譯成功
  int  success;
  char infoLog[512];
  //獲取訊息
  
  
  
  //glGetShaderiv(檢測對象,傳遞編譯狀態-GL_COMPILE_STATUS,回傳)
  glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
  //判斷vertexShader是否編譯成功
  if (!success){

    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    std::cout<<"ERROR:SHADOW::VERTEX::FAILED"<< infoLog<<std::endl;
  
  }
  else
  {
    std::cout<<"vertex::success\n"<<std::endl;
  }
  
  
  glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
  //判斷fragmentShader是否編譯成功
  if (!success){
 
    glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cout<<"ERROR:SHADOW::FRAGMENT::FAILED\n"<< infoLog<<std::endl;
  
  }
  else
  {
    std::cout<<"fragment::success\n"<<std::endl;
  }

  // 創建著色器程序物件(SPO,shader program object)
  unsigned int shaderPorgram;
  shaderPorgram = glCreateProgram();
  // 將shader附加至SPO
  glAttachShader(shaderPorgram,vertexShader);
  glAttachShader(shaderPorgram,fragmentShader);
  //link shader
  glLinkProgram(shaderPorgram); 
  //檢測link成功與否
  glGetProgramiv(shaderPorgram,GL_LINK_STATUS,&success);
  if (!success)
  {
    glGetProgramInfoLog(shaderPorgram,512,NULL,infoLog); 
    std::cout<<"PROGEME::LINK::FAILED\n"<< infoLog<<std::endl;
  }
  else
  {
    std::cout<<"link::success"<<std::endl;
  }
  
  //使用SPO
  glUseProgram(shaderPorgram);
  //繪製完刪除著色器
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  

  
  
  ////渲染迴圈////
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    // 渲染指令
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //使用SPO
    glUseProgram(shaderPorgram);
    
    //綁定VAO
    glBindVertexArray(VAO);
    
    //繪製(模式,起點,點數)
    glDrawArrays(GL_TRIANGLES,0,6);
    
    // glDrawArrays(GL_POINTS,0,3);  //三點
    // glDrawArrays(GL_LINE_LOOP,0,3); //三線

    //解綁VAO
    glBindVertexArray(0);



    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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