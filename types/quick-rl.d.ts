declare namespace rl {
    /**
        outputs a message to the console
        @param args - list of javascript objects to output
    */
    function log(args: string[]): void;

    /**
        Initialize window and OpenGL context
        @param width - width of the window
        @param height - height of the window
        @param title - title of the window
    */
    function InitWindow(width: number, height: number, title: string): void;

    /**
        Close window and unload OpenGL context
    */
    function CloseWindow(): void;

    /**
        Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
        @ret true if window should close, false otherwise
    */
    function WindowShouldClose(): boolean;

    /**
        Setup canvas (framebuffer) to start drawing
     */
    function BeginDrawing(): void;

    /**
        End canvas drawing and swap buffers (double buffering)
    */
    function EndDrawing(): void;
}
