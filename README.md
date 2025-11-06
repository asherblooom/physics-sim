# Physics Sim

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)

A simple Rigid Body Physics Simulator written in C++ with OpenGL
Uses broad- and narrow-phase collision detection, and two methods of rendering the balls (texture/triangle fan)

## Controls

* Right-click to create a ball at cursor position
* Left-click and drag to move a ball
* Press N to create a ball at the top of the screen
* Press M to create a ball at the bottom right with forces acting on it

## Setup instructions

### Linux (x11)

<details>
<summary>Prerequisites</summary>
  
* Ensure the glfw, openGL, x11, xInput and xrandr development libraries are installed
  
  * _on ubuntu you can run_

    ```
    sudo apt install libgl-dev libx11-dev libxi-dev libxrandr-dev libglfw3-dev libfreetype6-dev
    ```

  * _on fedora you can run_

    ```
    sudo dnf install libglvnd-devel mesa-libGL-devel libXi-devel libX11-devel libXrandr-devel glfw-devel freetype-devel
    ```

</details>

<details>
<summary>Building and running your game</summary>

* Clone the repository
* Run `make` in the root directory
* Run the resulting `phys-sim` file (located in the root directory)

</details>
