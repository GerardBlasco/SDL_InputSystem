# SDL_InputSystem
This simple extension of the SDL library, aims to simplify and centralize keyboard and mouse input management.

## Classes:
### Input System

**Methods:**
  - `static void CreateMap(std::string name)`: This function creates an Input Map that automatically registers itself into the Input System as a `string` as an identifier.
```c++
InputSystem::CreateMap("FooMap");
```
  - `static void CreateMap(std::string name, SDL_Keycode key, bool inverted)`: An override of the function `CreateMap()`. This function, besides creating an Input Map, it also adds a binding to the new map.
```c++
InputSystem::CreateMap("FooMap", SDLK_SPACE); // Inverted value is false by default
InputSystem::CreateMap("FooMap2", SDL_BUTTON_LEFT, true);
```
  - `static void DeleteMap(std::string name)`: Deletes an Input Map with the specified identifier.
```c++
InputSystem::CreateMap("FooMap", SDLK_W);
InputSystem::DeleteMap("FooMap"); // Deletes FooMap and all it's bindings
```
  - `static InputMap* Map(std::string name)`: Returns a pointer the Input Map with the specified name.
```c++
InputSystem::CreateMap("FooMap", SDLK_W);
InputSystem::Map("FooMap"); // Pointer to FooMap
```
  - `static void Update()`: The essential function so this extension can work. This function updates all Input Event status and all Input Maps registered. It needs to be called from a loop being this the FIRST method called.
```c++
void Game::Loop()
{
	while(!game_end){
      InputSystem::Update();
      Update();
    }
}
```
  - `static void Delta(float& x, float& y)`: Returns the value x / y from the mouse delta relative to the project window.
```c++
float posX;
float posY;

InputSystem::Delta(posX, posY); // Now posX equals the mouse delta x, and posY equals the mouse delta y
```
  - `static float DeltaX()`: Returns the x value from the mouse delta relative to the project window.
```c++
float posX;

posX = InputSystem::DeltaX(); // Now posX equals the mouse delta x
```
  - `static float DeltaY()`: Returns the y value from the mouse delta relative to the project window.
```c++
float posY;

posY = InputSystem::DeltaY(); // Now posY equals the mouse delta y
```
  - `static bool EventQuit()`: Returns true if any SDL_EVENT_QUIT is performed.
```c++
void Game::Loop()
{
	while(!game_end){
      InputSystem::Update();

      if(InputSystem::EventQuit()){
          game_end = true; // Ends the game loop in case any SDL_EVENT_QUIT is performed
      }
      
      Update();
    }
}
```

### Input Map

**Parameters:**
  - `triggered`: It's value will be true the only frame a registered binding is pressed. It won't be true again until it's key is up and pressed again.
  - `performed`: It's value will be true while it's registered binding is pressed.

**Methods:**
  - `InputMap()`: Empty class constructor method. It is called via the `InputSystem::CreateMap()` method.
  - `InputMap(SDL_Keycode key, bool inverted)`: Class constructor method that adds a binding on creation to the map. The "inverted" parameter specifies if the float value of the binding should be 1 or -1, and it's false by default. This constructor is called via the `InputSystem::CreateMap()`.
```c++
InputMap map1 = new InputMap(SDLK_W); // Registers the W key with value 1
InputMap map2 = new InputMap(SDLK_SPACE, true); // Registers the SPACE key with value -1
```
  - `void AddBinding(SDL_Keycode key, bool inverted)`: Registers a key that will be added to the Input Map. The "inverted" parameter specifies if the float value of the binding should be 1 or -1, and it's false by default.
```c++
InputMap map = new InputMap();
map.AddBinding(SDLK_D); // Registers the D key with value 1
map.AddBinding(SDLK_SPACE, true); // Registers the SPACE key with value -1
```
  - `void RemoveBinding(SDL_Keycode key)`: Unregisters a key from the Input Map.
```c++
InputMap map = new InputMap();
map.AddBinding(SDLK_D);
map.AddBinding(SDLK_SPACE, true);

map.RemoveBinding(SDLK_D); // D key no longer registered to the map
```
  - `void AddListener(T* object, void (T::* function)())`: Registers a function pointer into the map. This way, every time a registered binding is performed, all functions will be executed.
```c++
class Foo
{
  Foo()
  {
    InputMap map = new InputMap();
    map.AddBinding(SDLK_D);
    map.AddListener(this, &Foo::FooMethod);
  }

  void FooMethod()
  {
  }
}
```
  - `float ReadFloat()`: Returns the float value from the bindings registered into the map if performed. If the binding was added normally, it will return 1, but if it was added inverted, it will return -1. If none is performed, it will return 0.
```c++
float value;
InputMap map = new InputMap();

map.AddBinding(SDLK_D);
map.AddBinding(SDLK_SPACE, true);

// SDLK_D is performed, value = 1 | SDLK_SPACE is performed, value = -1 | No binding performed, value = 0
value = map.ReadFloat();
```

## InputMap creation & binding example:
```c++
class Foo
{
  Foo()
  {
    InputSystem::CreateMap("HorizontalMovement");
    InputSystem::Map("HorizontalMovement")->AddBinding(SDLK_D);
    InputSystem::Map("HorizontalMovement")->AddBinding(SDLK_A, true);

    InputSystem::CreateMap("Shoot");
    InputSystem::Map("Shoot")->AddBinding(SDL_BUTTON_LEFT);

    InputSystem::CreateMap("Sprint");
    InputSystem::Map("Sprint")->AddBinding(SDLK_LSHIFT);
    InputSystem::Map("Sprint")->AddListener(this, &Foo::Sprint); // Everytime Left Shift is pressed, Sprint() will be called
  }

  void UpadateFoo()
  {
    // If Shoot is triggered the function Shoot will be called one frame
    if(InputSystem::Map("Shoot")->triggered){
      Shoot();
    }

    // Moves based on the binding float value. If D is pressed, it will move right. If A is pressed, it will move left
    transform.position.x += InputSystem::Map("HorizontalMovement")->ReadFloat() * 0.1f;
  }

  void Sprint(){ ... }
  void Shoot(){ ... }
}
```


