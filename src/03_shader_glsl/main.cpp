#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
//using shaders + uniforms



void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
// //vertex shader source code
// const char *vertexShaderSource =  "#version 330 core\n" 
//                                   "layout (location = 0) in vec3 aPos;\n"
//                                   "out vec4 vColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
//                                   "vColor = vec4(0.0f, 0.5f, 0.1f, 1.0f);\n"
//                                   "gl_PointSize = 2.0f;\n"
//                                   "}\n";
// //fragment shader source code
// const char *fragmentShaderSource1 =  "#version 330 core\n"
//                                     "out vec4 FragColor;\n"
//                                     "in vec4 vColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     // "vec4 color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                     "FragColor = vColor;\n"
//                                     "}\n"; 

// const char *fragmentShaderSource2 =  "#version 330 core\n"
//                                     "out vec4 FragColor;"
//                                     "uniform vec4 ourColor;\n"
//                                     "void main()\n"                      
//                                     "{\n"
//                                     "FragColor = ourColor;\n"
//                                     // "FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
//                                     "}\n";




//vertex shader source code
const char *vertexShaderSource =  "#version 330 core\n" 
                                  "layout (location = 0) in vec3 aPos;\n"                                  
                                  "void main()\n"
                                  "{\n"
                                  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"                              
                                  "gl_PointSize = 2.0f;\n"
                                  "}\n";
//fragment shader source code
const char *fragmentShaderSource1 =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec4 vColor;\n"
                                    "uniform vec4 ourColor1;\n"
                                    "void main()\n"
                                    "{\n"
                                    // "vec4 color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "FragColor = ourColor1;\n"
                                    "}\n"; 

const char *fragmentShaderSource2 =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec4 vColor;\n"
                                    "uniform vec4 ourColor2;\n"
                                    "void main()\n"
                                    "{\n"
                                    // "vec4 color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "FragColor = ourColor2;\n"
                                    "}\n"; 


int main()
{
  glfwInit();
  // 設置主要與次要版本
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);






  // 創建視窗對象
  GLFWwindow *window = glfwCreateWindow(800, 600, "triangle with 2 shaders + uniform", NULL, NULL);
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
  glViewport(0, 0, 500, 500);

  // 監聽視窗變化
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



  ///////目前硬體支援Shader支援頂點數///////
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;



  //vertex(頂點)輸入
  //Normalized coor.(-1,1)
  float vertices[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    
    -1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
  };
 


/////////////////////////兩個VAO、VBO/////////////////

  //生成VBO,VAO
  //生成兩個:數組大小為2,生成buffer時參數也是2
  unsigned int VBOS[2],VAOS[2];
  glGenBuffers(2, VBOS);  
  glGenVertexArrays(2,VAOS);
  

///第一個VAO、VBO///
  //綁定第一個VAO:VAOS[0]
  glBindVertexArray(VAOS[0]);
  //綁定第一個VBO:VBOS[0]
  glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
  

  //填充資料 (目標,資料大小,資料,希望GPU如何管理數據)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //設置vertex屬性指標
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  //(屬性位置,屬性大小,數據類型,是否Normalized,步長,起始點偏移量)
  //啟用
  glEnableVertexAttribArray(0);
  //綁定
  glBindVertexArray(0);

///第二個VAO,VBO///
  //綁定第二個VAO:VAOS[1]
  glBindVertexArray(VAOS[1]);
  //綁定第二個VBO:VBOS[1]
  glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
  

  //填充資料 (目標,資料大小,資料,希望GPU如何管理數據)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //設置vertex屬性指標
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)(9 * sizeof(float)));
  //最後偏移三個頂點,資料長度為九個浮點數
  //啟用
  glEnableVertexAttribArray(0);
  //綁定
  glBindVertexArray(0);



  




  //創建Vertex shader與Fragment Shader
  unsigned int vertexShader,fragmentShader1,fragmentShader2; 
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

  //附加shader代碼 
  //glShaderSource(編譯對象,傳遞數量,shadr代碼,NULL)
  
  //vertex
  glShaderSource(vertexShader, 1 , &vertexShaderSource , NULL);
  glCompileShader(vertexShader);  //編譯shader
  
  //fragment
  glShaderSource(fragmentShader1, 1 , &fragmentShaderSource1 , NULL);
  glShaderSource(fragmentShader2, 1 , &fragmentShaderSource2 , NULL);
  glCompileShader(fragmentShader1);  //編譯shader
  glCompileShader(fragmentShader2);  //編譯shader
 
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
  
  
  glGetShaderiv(fragmentShader1,GL_COMPILE_STATUS,&success);
  //判斷fragmentShader是否編譯成功
  //FRAGMENT_1
  if (!success){
 
    glGetShaderInfoLog(fragmentShader1,512,NULL,infoLog);
    std::cout<<"ERROR:SHADOW::FRAGMENT_1::FAILED\n"<< infoLog<<std::endl;
  
  }
  else
  {
    std::cout<<"fragment_1::success\n"<<std::endl;
  }
  //FRAGMENT_2
  glGetShaderiv(fragmentShader2,GL_COMPILE_STATUS,&success);
   if (!success){
 
    glGetShaderInfoLog(fragmentShader2,512,NULL,infoLog);
    std::cout<<"ERROR:SHADOW::FRAGMENT_2::FAILED\n"<< infoLog<<std::endl;
  
  }
  else
  {
    std::cout<<"fragment_2::success\n"<<std::endl;
  }


 

  // 創建著色器程序物件(SPO,shader program object)
  unsigned int shaderPorgram1,shaderPorgram2;
  shaderPorgram1 = glCreateProgram();
  shaderPorgram2 = glCreateProgram();
  // 將shader附加至SPO
  glAttachShader(shaderPorgram1,vertexShader);
  glAttachShader(shaderPorgram1,fragmentShader1);
  glAttachShader(shaderPorgram2,fragmentShader2);

  //link shader
  glLinkProgram(shaderPorgram1);
  glLinkProgram(shaderPorgram2); 

  //檢測link成功與否
  //檢測shaderPorgram1
  glGetProgramiv(shaderPorgram1,GL_LINK_STATUS,&success);
  if (!success)
  {
    glGetProgramInfoLog(shaderPorgram1,512,NULL,infoLog); 
    std::cout<<"PROGEME::LINK_1::FAILED\n"<< infoLog<<std::endl;
  }
  else
  {
    std::cout<<"link_1::success"<<std::endl;
  }
  //檢測shaderPorgram2
  glGetProgramiv(shaderPorgram2,GL_LINK_STATUS,&success);
  if (!success)
  {
    glGetProgramInfoLog(shaderPorgram2,512,NULL,infoLog); 
    std::cout<<"PROGEME::LINK_2::FAILED\n"<< infoLog<<std::endl;
  }
  else
  {
    std::cout<<"link_2::success"<<std::endl;
  }
  

  // //使用SPO
  // glUseProgram(shaderPorgram);
  
  
  //LINK完刪除著色器
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  glDeleteShader(fragmentShader2);
  

  int ourColorLocation1 = glGetUniformLocation(shaderPorgram1,"ourColor1");
  int ourColorLocation2 = glGetUniformLocation(shaderPorgram2,"ourColor2");

 


  
  ////渲染迴圈////
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    // 渲染指令
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;

    //第一個三角形  前三個頂點
    //使用第一個著色器
    glUseProgram(shaderPorgram1);
    glBindVertexArray(VAOS[0]);
    glDrawArrays(GL_POINTS,0,3);   //第一個三角形 使用前三個點
    glDrawArrays(GL_TRIANGLES,0,3);
    
    

    std::cout<<"shaderPorgram1_BV:"<<greenValue<<std::endl;
    glUniform4f(ourColorLocation1, 0.3f, 0.7f, greenValue, 0.0f);







    //第二個三角形
    //使用第二個著色器
    glUseProgram(shaderPorgram2);
    glBindVertexArray(VAOS[1]);
    glDrawArrays(GL_POINTS,0,3); 
    glDrawArrays(GL_TRIANGLES,0,3);


    std::cout<<"shaderPorgram2_GV:"<<greenValue<<std::endl;
    glUniform4f(ourColorLocation2, (1-greenValue), greenValue, 0.5f, 0.9f);




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
  glViewport(0, 0, 500, 500); 
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}