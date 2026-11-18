# IjzerEngineDocs

## here I will be documenting my design choices

### Engine choices

The engine is used as a lib, it is never the entry point of the application and it can't initialize more than it is told to by the application that is using it.

The engine will provide a abstraction of rendering, window management, input handling, sound management, complex maths, debug UI and thread group management.


### Game choices

I haven't decided on any specific game yet, though I do have a general direction I want to go with testing tech, thus I will design the engine for this and let the game only handle "game" things, such as the actual implementation of shaders, the game loop and mesh acquisition