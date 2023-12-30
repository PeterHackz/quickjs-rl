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
JS_RL_FUNC(IsWindowState)
JS_RL_FUNC(SetWindowState)
JS_RL_FUNC(ClearWindowState)
JS_RL_FUNC(ToggleFullscreen)
JS_RL_FUNC(ToggleBorderlessWindowed)
JS_RL_FUNC(MaximizeWindow)
JS_RL_FUNC(MinimizeWindow)
JS_RL_FUNC(RestoreWindow)
JS_RL_FUNC(SetWindowIcon)

JS_RL_FUNC(log)

JS_RL_FUNC(BeginDrawing)
JS_RL_FUNC(EndDrawing)
JS_RL_FUNC(ClearBackground)

JS_RL_FUNC(LoadImage)
JS_RL_FUNC(LoadImageRaw)
JS_RL_FUNC(LoadImageSvg)
JS_RL_FUNC(LoadImageAnim)
JS_RL_FUNC(LoadImageFromMemory)
JS_RL_FUNC(LoadImageFromTexture)
JS_RL_FUNC(LoadImageFromScreen)
JS_RL_FUNC(IsImageReady)
JS_RL_FUNC(UnloadImage)
JS_RL_FUNC(ExportImage)
JS_RL_FUNC(ExportImageToMemory)
JS_RL_FUNC(ExportImageAsCode)
#endif

#ifdef JS_RL_CLASSES
JS_RL_CLASS_CTOR(Color);
JS_RL_CLASS_FINALIZER(Color);
JS_RL_GETTER_MAGIC(Color, color);
JS_RL_SETTER_MAGIC(Color, color);

JS_RL_CLASS_CTOR(Image);
JS_RL_CLASS_FINALIZER(Image);
JS_RL_GETTER_MAGIC(Image, img_props);
JS_RL_SETTER_MAGIC(Image, img_props);
#endif

#ifdef JS_RL_CLASSES_INITS
JS_RL_PREPARE(
    Window); // used to register Window static properties (ex: ConfigFlags)

JS_RL_CLASS_INIT(Color); // used by JS_AddRLBindings to register Color class
JS_RL_PREPARE(Color); // used to register Color static properties (ex: RAYWHITE)

JS_RL_CLASS_INIT(Image);
#endif