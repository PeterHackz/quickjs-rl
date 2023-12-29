#ifdef JS_RL_FUNCS
// Window-related functions
JS_RL_FUNC(InitWindow)
JS_RL_FUNC(CloseWindow)
JS_RL_FUNC(WindowShouldClose)
JS_RL_FUNC(IsWindowReady)
JS_RL_FUNC(IsWindowFullscreen)
JS_RL_FUNC(IsWindowHidden)
JS_RL_FUNC(IsWindowMinimized)
JS_RL_FUNC(IsWindowMaximized)
JS_RL_FUNC(IsWindowFocused)
JS_RL_FUNC(IsWindowResized)

JS_RL_FUNC(log)

JS_RL_FUNC(BeginDrawing)
JS_RL_FUNC(EndDrawing)
JS_RL_FUNC(ClearBackground)
#endif

#ifdef JS_RL_CLASSES
JS_RL_CLASS_CTOR(Color);
JS_RL_CLASS_FINALIZER(Color);
JS_RL_GETTER_MAGIC(Color, color);
JS_RL_SETTER_MAGIC(Color, color);
#endif

#ifdef JS_RL_CLASSES_INITS
JS_RL_CLASS_INIT(Color); // used by JS_AddRLBindings to register Color class
JS_RL_PREPARE(
    Color); // used to register Color static properties (ex: Color.RAYWHITE)
#endif