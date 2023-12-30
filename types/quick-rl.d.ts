declare namespace rl {
    /**
     * outputs a message to the console
     * @param args - list of javascript objects to output
     */
    function log(...args: any[]): void;

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
