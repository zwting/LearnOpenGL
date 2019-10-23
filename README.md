# LearnOpenGL
我的OpenGL学习计划

### 项目介绍
不用现有引擎，从底层图形API开始制作一个3D游戏。为了方便游戏开发，过程会制作一些方便开发使用的工具，编辑器。这些构成以后的游戏开发工具包，可以称之为游戏引擎

### 制作优先级思路
1. 游戏本身优先级最高
2. 游戏开发中所用到的工具，编辑器
总结：为了做游戏，不为了做引擎

### 开发环境
1. windows
2. Visual studio 2019 社区版

### 参考资料
1. LearnOpenGL： [英文版](https://learnopengl.com/In-Practice/Debugging)  [中文版](https://learnopengl-cn.github.io/)
2. [OGRE渲染引擎源代码](https://www.ogre3d.org/) 
3. 一个用来“抄袭”的游戏，待定~~
4. OpenGL教程：http://ogldev.org/index.html ，这个里面有使用Assimp来实现骨骼动画的方法
5. 虚幻引擎源代码：https://github.com/EpicGames/UnrealEngine

### 引用
1. [glm](https://github.com/g-truc/glm.git)：一个开源数学库
2. [stb](https://github.com/nothings/stb.git)：开源图片加载库
3. [glad](https://glad.dav1d.de/)：提取opengl中的接口签名
4. [assimp](http://www.assimp.org/)：加载3D模型开源库
5. [glfw](https://www.glfw.org/)：OpenGL窗口，事件管理工具
6. [idea imgui](https://github.com/ocornut/imgui/tree/docking)：一个IMGUI库，打算用来实现引擎编辑器

### 大纲（以unity目标）
+ 引擎编辑器GUI（尚未开始）
  + scene view: 场景编辑视口
  + game view: 游戏运行视口
  + console: 输出运行日志
  + hierarchy: 层级面板，管理当前场景中的所有物体
  + project: 项目面板，管理当前项目的所有文件
  + inspector: 检视面板，显示当前选中的对象属性
  + setting: 设置面板
+ 引擎核心
  + 场景管理
  + 内存管理
  + 资源管理
  + 动画模块
    + 3D骨骼动画：
  + 日志系统
  + 渲染管线
  + AI模块
    + 行为树
  + UI引擎：游戏侧重玩法，不重UI。目前打算采用IMGUI方式，能满足需求即可
  + 物理引擎：[Phyics](https://github.com/NVIDIAGameWorks/PhysX-3.4)
 
