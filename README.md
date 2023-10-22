# zpg
intro to computer graphics project

# To do:
## General
* Implement resource caches for meshes and textures (trying to load the same resource for the second time should result in getting a reference)
* Assimp for model loading

## Window
* resize handling
* fullscreen toggle
* vsync toggle

# Done

## General
* Application should handle the creation of matrix UBO
* Make the camera class upload its matrices
* fix input stutter and delay
* make input independent of framerate (delta time is currently fucked)
* General observer pattern (possibly with variadic payload data)
* Light material
* UBO for light data
* Shader parsing handles #include

## Camera
* on window resize change aspect ratio