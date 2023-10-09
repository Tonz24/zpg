# zpg
intro to computer graphics project

# To do:

## General
* fix input stutter and delay
* make input independent of framerate (delta time is currently fucked)
* General observer pattern (possibly with variadic payload data)
* Implement resource caches for meshes and textures (trying to load the same resource for the second time should result in getting a reference)
* Assimp for model loading
* Light material
* UBO for light data

## Window
* resize handling
* fullscreen toggle
* vsync toggle

## Camera
* on window resize change aspect ratio

### Done
* Application should handle the creation of matrix UBO
* Make the camera class upload its matrices
