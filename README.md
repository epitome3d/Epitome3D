##D3DLib
####Open Source Direct3D/2D Engine

This engine simplifies the use of DirectX with an easy-to-use graphics, sound, and memory management library.  This engine is built for all users from beginners to advanced 3D designers by allowing for as much, or as little, use of the library as desired.

###Features
- 3D Model Types: .fbx, .obj
- 2D Graphics and Sound
- Direct Shader Import
- Automated stack-based rasterizer and painter

###The Flow


###Example: Writing your first 3D game in 30 minutes


###Files
- Model Types
  - model_FBX: Loads FBX models
  - model_OBJ: Loads OBJ models
  - model_SIMP: Loads a customized, simplified model format
  - Write your own!
- Shaders (change to HLSL coming soon!)
  - shader_SKYBOX: Creates a standard skybox
  - shader_MATERIAL: Fully-featured material shader
  - shader_LIGHT: Lighting, texture, and color shader
  - shader_TEXTURE: Texture and color shader
  - shader_COLOR: Just a color shader
  - Supports customized shader import
- Sounds
  - sound_WAVEPCM: Loads and plays .wav sound
- Bitmap: Bitmap base class
- Camera: Controls camera and movement
- CPU: Reads CPU state and render stats
- Exception: Message and error handling
- FPS: Reads render rate and contains timing functions
- Frustum: Enables frustum culling, improving render rate
- FrustumCull: Enables customized frustum culling
- Globals: Global file structures
- Input: Keyboard, mouse, and touchscreen reading
- Math3D: General 3D math and unit conversions
- Model: Base class for model types
- Painter: Paints a scene based on a stack-based render structure
- Shader: Shader base class
- Sound: Sound base class
- Text: Text drawing class
- Texture: Texture import and drawing class
- Timer: Controls high-precision timers
- Viewport: Allows rendering on multiple viewports
- Window: Main method, starts window functions and dependencies
Note that not a single file is required for use in your application, but it is recommended that you at least include the window class.

###Contributing
Please **add issues** and bugs to our issues page, **help with the wiki**, or **pull request** directly to this repository!


=========================================================
Licensed under **MIT License**
