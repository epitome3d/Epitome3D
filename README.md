##D3DLib
####Open Source Direct3D/2D Engine

This engine simplifies the use of DirectX with an easy-to-use graphics, sound, and memory management library.  This engine is built for all users from beginners to advanced 3D designers by allowing for as much, or as little, use of the library as you wish.

###Features
- 3D Model Types: .fbx, .obj
- 2D Graphics and Sound
- Direct Shader Import
- Automated stack-based rasterizer and painter

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
- 
- Bitmap: Bitmap base class
- Camera: Controls camera and movement
- CPU: Reads CPU state and render stats
- Exception: Message and error handling
- FPS: Reads render rate and contains timing functions
- Frustum: Enables frustum culling, improving render rate
- FrustumCull: Enables customized frustum culling
