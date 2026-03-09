*This project has been created as part of the 42 curriculum by jonnavar, igenez-y.*

## Description

miniRT is a minimal ray tracing engine implemented in C, developed as part of the 42 curriculum. This project introduces the fundamentals of computer-generated imagery through the ray tracing technique, demonstrating how mathematical formulas can be transformed into visual representations.

The program reads a scene description file (.rt format) and renders a 3D scene using ray tracing, featuring:


- Three primitive objects: spheres, planes, and cylinders

- Camera system with configurable position, orientation, and field of view

- Lighting model: ambient and diffuse illumination with hard shadows

- Interactive controls: real-time camera movement and object manipulation

- Scene parsing: robust validation of .rt scene files

Unlike rasterization (used in real-time graphics), ray tracing simulates the physical behavior of light by casting rays from the camera through each pixel and calculating their interactions with objects in the scene. This approach produces more photorealistic results at the cost of computational intensity.

## Instructions

Ensure you have the required dependencies:

```bash
# On Ubuntu/Debian
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

Compile the project:

```bash
make
```

Additional Makefile rules:

- make clean - Remove object files

- make fclean - Remove object files and executable

- make re - Recompile from scratch

- make bonus - Compile with bonus features (if implemented)

## Resources

Here's a list of references consulted for this project:

- CommonMark specification version 0.31.2 (2024-01-28): https://spec[.]commonmark[.]org/


- My notes in Notion

- My diagrams in draw.io

AI was not used for any task or any part of the project.
