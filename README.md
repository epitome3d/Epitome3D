##D3DLib
####Open Source Direct3D/2D Engine

This engine simplifies the use of DirectX with an easy-to-use graphics, sound, and memory management library.  This engine is built for all users from beginners to advanced 3D designers by allowing for as much, or as little, use of the library as desired.

###Current Features
- 3D Model Types: .fbx, .obj, or write your own!
- 2D Graphics and Sound
- Direct Shader Import
- Automated stack-based rasterizer and painter

###The Flow


###Writing your first 3D game in 30 minutes
{getting started page to example page}
{need to write content, including Visual Studio installation}


###Tasks


###Files
- [ ] Model Types
  - [x] model_FBX: Loads FBX models
  - [x] model_OBJ: Loads OBJ models
  - [ ] model_SIMP: Loads a customized, simplified model format
  - [x] Write your own!
- [ ] Shaders (change to HLSL coming soon!)
  - [ ] shader_SKYBOX: Creates a standard skybox
  - [ ] shader_MATERIAL: Fully-featured material shader
  - [x] shader_LIGHT: Lighting, texture, and color shader
  - [x] shader_TEXTURE: Texture and color shader
  - [x] shader_COLOR: Just a color shader
  - [ ] Supports customized shader import
- [x] Sounds
  - [x] sound_WAVEPCM: Loads and plays .wav sound
- [x] Bitmap: Bitmap base class
- [x] Camera: Controls camera and movement
- [x] CPU: Reads CPU state and render stats
- [x] Exception: Message and error handling
- [x] FPS: Reads render rate and contains timing functions
- [x] Frustum: Enables frustum culling, improving render rate
- [x] FrustumCull: Enables customized frustum culling
- [x] Globals: Global file structures
- [x] Input: Keyboard, mouse, and touchscreen reading
- [x] Math3D: General 3D math and unit conversions
- [x] Model: Base class for model types
- [x] Painter: Paints a scene based on a stack-based render structure
- [x] Shader: Shader base class
- [x] Sound: Sound base class
- [ ] SoundFX: Sound manipulation and effects pallate
- [x] Text: Text drawing class
- [x] Texture: Texture import and drawing class
- [x] Timer: Controls high-precision timers
- [x] Viewport: Allows rendering on multiple viewports
- [x] Window: Main method, starts window functions and dependencies

Note that not a single file is required for use in your application, but it is recommended that you at least include the window class.

###Contributing
Please **add bugs and features** to our issues page, **help with the wiki**, or **pull request** directly to this repository!

=========================================================
Licensed under **MIT License**
