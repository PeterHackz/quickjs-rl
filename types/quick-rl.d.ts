declare namespace rl {
    /**
     * outputs a message to the console
     * @param args - list of javascript objects to output
     */
    function log(...args: string[]): void;

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

    const LIGHTGRAY: Color;
    const GRAY: Color;
    const DARKGRAY: Color;
    const YELLOW: Color;
    const GOLD: Color;
    const ORANGE: Color;
    const PINK: Color;
    const RED: Color;
    const MAROON: Color;
    const GREEN: Color;
    const LIME: Color;
    const DARKGREEN: Color;
    const SKYBLUE: Color;
    const BLUE: Color;
    const DARKBLUE: Color;
    const PURPLE: Color;
    const VIOLET: Color;
    const DARKPURPLE: Color;
    const BEIGE: Color;
    const BROWN: Color;
    const DARKBROWN: Color;
    const WHITE: Color;
    const BLACK: Color;
    const BLANK: Color;
    const MAGENTA: Color;
    const RAYWHITE: Color;
}
