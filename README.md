![](https://www.holbertonschool.com/holberton-logo.png)

[![Stargazers][stars-shield]][stars-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
# Raise The Terrain
<h3>An isometric projection of a grid that rotates when pressing A (right) or D (left) </h3>

****
## About this project
Raise The Terrain is a voluntary project at Holberton School taking part of the "Low-level programming & Algorithm" projects.\
It is created using the **C programming Language** and **SDL2**.
## How it works
 - The program reads the file "demo_".
 - Gets the coordinate of each point.
 - Draws an isometric projection of a matrix(grid) (64 connected points). Each point has its x, y and z coordinates (z = altitude).
 - Rotates the grid to Right or Left, and UP or DOWN, all this when the user presses on WASD, key.
 - Zoom in , and zoom out , when the user press UP or DOWN arrow, to take some details, about the grid.
 - Quits when the user presses ESC key or when clicks on window Quit button.
## USAGE
You can run this program by following these steps:
> **Step 1:** Clone my repository using this command, (you need to have git, gcc and SDL2 installed on your machine first)
````
git clone
````
> **Step 2:** Change directory to Raise_the_terrain:
````
cd Raise_the_terrain
````
> **Step 3:** Compile the C files in this way:
````
gcc -Wall -Werror -Wextra -pedantic *.c -lm `sdl2-config --cflags` `sdl2-config --libs` -o Raise_terrain
````
> **Step 4:** Run the program
````
./Raise_terrain <file>
````
**Exiting the program**
When you want to exit the program, you can use one of the following methods:
> **1: Click on window close button**
````
exit
````
> **2: Press on ESC key**


<p align="center">
  
<img src="https://github.com/Rode1o/Raise_the_terrain/blob/main/final_60a0b43bac3fc500464588d8_860844.gif" width="250" height="250" />

</p>
 <h2> Authors</h2>

**Duvan Rodelo**
 - [ ] [@duvanrode1o](https://twitter.com/duvanrode1o)
 - [ ] [Github](https://github.com/Rode1o)

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/duvanrode1o/
[stars-shield]: https://img.shields.io/github/stars/Rode1o/Raise_the_terrain.svg?style=flat-square
[stars-url]: https://github.com/Rode1o/Raise_the_terrain/stargazers
