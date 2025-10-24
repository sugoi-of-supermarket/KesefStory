#include "game.h"
#include "raylib.h"

int main(int argc, char **argv)
{
    // Allow overriding asset directory from command line
    const char *asset_dir = (argc > 1) ? argv[1] : 0;

    // Initialize game
    if (!game_init(asset_dir)) {
        TraceLog(LOG_ERROR, "Failed to initialize game");
        game_cleanup();
        return 1;
    }

    // Main game loop
    while (game_should_run()) {
        const float dt = GetFrameTime();

        game_handle_input(dt);
        game_update(dt);
        game_render();
    }

    // Clean up and exit
    game_cleanup();
    return 0;
}
