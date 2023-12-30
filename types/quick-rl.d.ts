declare namespace rl {
    /**
     * outputs a message to the console
     * @param args - list of javascript objects to output
     */
    function log(...args: any[]): void;

    enum ConfigFlags {
        FLAG_VSYNC_HINT,
        FLAG_FULLSCREEN_MODE,
        FLAG_WINDOW_RESIZABLE,
        FLAG_WINDOW_UNDECORATED,
        FLAG_WINDOW_HIDDEN,
        FLAG_WINDOW_MINIMIZED,
        FLAG_WINDOW_MAXIMIZED,
        FLAG_WINDOW_UNFOCUSED,
        FLAG_WINDOW_TOPMOST,
        FLAG_WINDOW_ALWAYS_RUN,
        FLAG_WINDOW_TRANSPARENT,
        FLAG_WINDOW_HIGHDPI,
        FLAG_WINDOW_MOUSE_PASSTHROUGH,
        FLAG_BORDERLESS_WINDOWED_MODE,
        FLAG_MSAA_4X_HINT,
        FLAG_INTERLACED_HINT,
    }

    const FLAG_VSYNC_HINT = ConfigFlags.FLAG_VSYNC_HINT,
        FLAG_FULLSCREEN_MODE = ConfigFlags.FLAG_FULLSCREEN_MODE,
        FLAG_WINDOW_RESIZABLE = ConfigFlags.FLAG_WINDOW_RESIZABLE,
        FLAG_WINDOW_UNDECORATED = ConfigFlags.FLAG_WINDOW_UNDECORATED,
        FLAG_WINDOW_HIDDEN = ConfigFlags.FLAG_WINDOW_HIDDEN,
        FLAG_WINDOW_MINIMIZED = ConfigFlags.FLAG_WINDOW_MINIMIZED,
        FLAG_WINDOW_MAXIMIZED = ConfigFlags.FLAG_WINDOW_MAXIMIZED,
        FLAG_WINDOW_UNFOCUSED = ConfigFlags.FLAG_WINDOW_UNFOCUSED,
        FLAG_WINDOW_TOPMOST = ConfigFlags.FLAG_WINDOW_TOPMOST,
        FLAG_WINDOW_ALWAYS_RUN = ConfigFlags.FLAG_WINDOW_ALWAYS_RUN,
        FLAG_WINDOW_TRANSPARENT = ConfigFlags.FLAG_WINDOW_TRANSPARENT,
        FLAG_WINDOW_HIGHDPI = ConfigFlags.FLAG_WINDOW_HIGHDPI,
        FLAG_WINDOW_MOUSE_PASSTHROUGH = ConfigFlags.FLAG_WINDOW_MOUSE_PASSTHROUGH,
        FLAG_BORDERLESS_WINDOWED_MODE = ConfigFlags.FLAG_BORDERLESS_WINDOWED_MODE,
        FLAG_MSAA_4X_HINT = ConfigFlags.FLAG_MSAA_4X_HINT,
        FLAG_INTERLACED_HINT = ConfigFlags.FLAG_INTERLACED_HINT;

    /**
     * Initialize window and OpenGL context
     * @param width - width of the window
     * @param height - height of the window
     * @param title - title of the window
     */
    function InitWindow(width: number, height: number, title: string): void;

    /**
     * Close window and unload OpenGL context
     */
    function CloseWindow(): void;

    /**
     * Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
     */
    function WindowShouldClose(): boolean;

    /**
     * Check if window has been initialized successfully
     */
    function IsWindowReady(): boolean;

    /**
     * Check if window is currently fullscreen
     */
    function IsWindowFullscreen(): boolean;

    /**
     * Check if window is currently hidden (only PLATFORM_DESKTOP)
     */
    function IsWindowHidden(): boolean;

    /**
     * Check if window is currently minimized (only PLATFORM_DESKTOP)
     */
    function IsWindowMinimized(): boolean;

    /**
     * Check if window is currently maximized (only PLATFORM_DESKTOP)
     */
    function IsWindowMaximized(): boolean;

    /**
     * Check if window is currently focused (only PLATFORM_DESKTOP)
     */
    function IsWindowFocused(): boolean;

    /**
     * Check if window has been resized last frame
     */
    function IsWindowResized(): boolean;

    /**
     * Check if one specific window flag is enabled
     */
    function IsWindowState(flag: number): boolean;

    /**
     * Set window configuration state using flags (only PLATFORM_DESKTOP)
     * @param flags - flags to set (rl.FLAG_*)
     */
    function SetWindowState(flag: ConfigFlags): void;

    /**
     * Clear window configuration state flags (only PLATFORM_DESKTOP)
     */
    function ClearWindowState(flag: ConfigFlags): void;

    /**
     * Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
     */
    function ToggleFullscreen(): void;

    /**
     * Toggle window state: borderless/windowed (only PLATFORM_DESKTOP)
     */
    function ToggleBorderlessWindowed(): void;

    /**
     * Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
     */
    function MaximizeWindow(): void;

    /**
     * Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
     */
    function MinimizeWindow(): void;

    /**
     * Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
     */
    function RestoreWindow(): void;

    /**
     * Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
     */
    function SetWindowIcon(image: Image): void;

    /**
        Setup canvas (framebuffer) to start drawing
     */
    function BeginDrawing(): void;

    /**
        End canvas drawing and swap buffers (double buffering)
    */
    function EndDrawing(): void;

    /**
        Set background color (framebuffer clear color)
    */
    function ClearBackground(color: Color): void;

    /**
        Color, 4 components, R8G8B8A8 (32bit)
    */
    class Color {
        r: number;
        g: number;
        b: number;
        a: number;

        /**
         * Color, 4 components, R8G8B8A8 (32bit)
         */
        constructor(r?: number, g?: number, b?: number, a?: number);
    }

    /**
     * Image struct
     */
    class Image {
        private data: ArrayBuffer | Uint8Array;
        width: number;
        height: number;
        mipmaps: number;
        format: number;

        /**
         * rl.Image is not supposed to be initialized directly, use rl.LoadImage() or related function instead
         */
        private constructor();
    }

    /**
     * Load image from file into CPU memory (RAM)
     * if image fails to load, null is returned
     * but if an unexpected internal error occurs, exception is thrown
     */
    function LoadImage(fileName: string): Image;

    const LIGHTGRAY: Color,
        GRAY: Color,
        DARKGRAY: Color,
        YELLOW: Color,
        GOLD: Color,
        ORANGE: Color,
        PINK: Color,
        RED: Color,
        MAROON: Color,
        GREEN: Color,
        LIME: Color,
        DARKGREEN: Color,
        SKYBLUE: Color,
        BLUE: Color,
        DARKBLUE: Color,
        PURPLE: Color,
        VIOLET: Color,
        DARKPURPLE: Color,
        BEIGE: Color,
        BROWN: Color,
        DARKBROWN: Color,
        WHITE: Color,
        BLACK: Color,
        BLANK: Color,
        MAGENTA: Color,
        RAYWHITE: Color;
}
