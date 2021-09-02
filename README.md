
# Ray-Tracer
[![GitHub license](https://img.shields.io/github/license/KirilAngelov/Ray-Tracer)](https://github.com/KirilAngelov/Ray-Tracer/blob/main/LICENSE)
<br />
This raytracer was made with C/C++ and the framework [SDL](https://www.libsdl.org).
# Video Showcase
![Animation](https://user-images.githubusercontent.com/44143480/129457790-f3d0cec6-8f9e-45d6-a5d5-42285100deaa.gif)

# Image Showcase
<br />
<p align="center">
  This image here show what happens when we have a constant for one axis. All of them appear grounded.
  <img src= "https://user-images.githubusercontent.com/44143480/131137885-7982fd07-d154-4794-838e-315701ddd5fb.jpeg">
</p>
<br />

<br />
<p align="center">
   Here we have a bunch of them scattered around using random values for X, Y, Z.
  <br />
  <img src= "https://user-images.githubusercontent.com/44143480/131137976-44de6840-e11a-497f-9e2b-fdd6a4b16025.jpeg">
</p>
<br />

<br />
<p align="center">
  And finally, this one shows what happens when we use some kind of interval for the X axis while keeping Y and Z free.
  <br />
  <img src= "https://user-images.githubusercontent.com/44143480/131138050-d1352e66-de19-4640-b66d-c15ce5aa937e.jpeg">
</p>
<br />


# How it works
It definitely looks like magic, but it isn't. Maths gives us a helping hand here, let's dive in and see how.
First we have a camera that acts like a position from which we "see". A class is used for simulating a ray which comes from the camera position. We have our image dimensions and objects on the scene specified through code. Upon starting we iterate through all of the pixels and our ray goes through every one of them, also when entering a pixel which is occupied by and object we specify RGBA values and send them to a SDL Texture. This texture gives us the ability to set the color of a single pixel using the calculated RGBA values before that. I wanted to see how the image is drawn, because it is more exciting than just waiting for a result. Computation time varies on every machine and on specified image dimensions, objects on the scene and other settings.
<br />

<br />
<p align="center">
  This image helps visualise what is happening.
  <br />
 <img width="358" alt="Explanation" src="https://user-images.githubusercontent.com/44143480/131818378-1d5ae507-72c7-4bc3-b632-0b1a86ae8ab8.PNG">
</p>
<br />



# Techologies used
1. C++ 17
2. SDL version 2.0.16 stable
<br />
The major programming concepts used are classes, polymorphism, reading and writing to files and smart pointers.
C++ is used for computation on the CPU and SDL for displaying the result in a separate window.

# Dependencies
The vclib folder contains everything you need to run the project. No setup is required.

# Building and running
All you need to do is clone the repository and build and run the solution. Enjoy!


