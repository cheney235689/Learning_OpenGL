# Learning OpenGL 

C++ OpenGL setup wiht VSCode + minGW (glad +glfw)

---

### 創建window

首先是引用GLAD與GLFW

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

其中GLFW定義了一些最基本的視窗參數、context、渲染物件等基本接口

而GLAD是用來管理OpenGL的函數指標

首先是創建一個簡單的main function:

```cpp
int main()
{
glfwInit(); //初始化GLFW
//glfwWindowHint(選項,參數)
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//設置主要版本
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//設置次要版本
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式

return 0 ;
}
  
```

透過glfwWindowHint來調整視窗的許多設定

而在這裡我們調整了主版本、次版本與開發模式


建立window:

```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);
```

glfwCreateWindow前三個參數分別是長、寬、視窗名稱

該返回一個GLFWwindow類型的物件

之後對視窗的所有操作都會調用到它

而glfwMakeContextCurrent(window)

則是將window設置為當前視窗

前面提到GLAD是用來管理OpenGL函數的指針，而要使用前須先把GLAD初始化:

```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}
```

---

### 渲染

在對視窗內的空間渲染前

我們需要先設定Viewport的位置與大小

前兩個是窗口左下的位置

```cpp
glViewport(0, 0, 800, 600);
```

Viewport可以簡單理解成使用者看到的畫面

在複雜的3D場景中其實會牽涉到投影的運算

但在這個簡單的範例中可以理解成"渲染的區域"

另外宣告兩個function

```cpp
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
```

第一個callback function則是確保視窗變換大小時，渲染程序也持續進行，而第二個processInput則是定義使用者輸入，這邊設計是按下ESC就關閉視窗。

接著是後面的一個回調函數與渲染迴圈:

```cpp
int main()
{
.
.
.
.
//接續前面的code
.
.
.
.
.
.
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    // 渲染指令
    // ...
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
```

while迴圈使程式不停渲染視窗

而while迴圈前的glfwSetFramebufferSizeCallback()，意思是當window大小改變，會呼叫指定函數 framebuffer_size_callback。

大體而言整個程式就是包含兩部分:定義渲染所需要的資訊(while迴圈外)以及渲染流程本身(while迴圈內)。
