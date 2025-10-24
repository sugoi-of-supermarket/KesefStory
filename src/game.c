#include "game.h"
#include "config.h"
#include "assets.h"
#include "entity.h"
#include "inventory.h"
#include "npc.h"

// Core game state
typedef struct {
    GameState       state;
    bool            running;
    Entity          player;
    NPC             orwell;
    InventoryWindow inventory;
    Fonts           fonts;
} Game;

static Game game = {0};

bool game_init(const char *asset_dir_override)
{
    // Initialize asset system
    assets_init(asset_dir_override);

    // Initialize window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    // Load fonts
    if (!assets_load_fonts(&game.fonts)) {
        TraceLog(LOG_ERROR, "GAME: Failed to load fonts");
        return false;
    }

    // Initialize inventory
    inventory_init(&game.inventory);

    // Initialize and load player entity
    entity_init(&game.player);
    if (!entity_load_texture(&game.player, "sprites/kesef-hatufim.png")) {
        TraceLog(LOG_ERROR, "GAME: Failed to load player texture");
        return false;
    }

    // Set up player
    entity_set_position(&game.player, 100, 300);
    entity_set_size(&game.player,
                    game.player.texture.width / 6.0f,
                    game.player.texture.height / 6.0f);

    // Initialize and set up Orwell NPC
    npc_init(&game.orwell);
    if (!npc_setup(&game.orwell, "sprites/orwell.png", "אורוול",
                   "אתה חטיף בסבתא מיזולדה, כלב כן כלב", true)) {
        TraceLog(LOG_ERROR, "GAME: Failed to load Orwell NPC");
        return false;
    }
    npc_set_position(&game.orwell, 650, 290);
    npc_set_size(&game.orwell,
                 game.orwell.entity.texture.width / 2.0f,
                 game.orwell.entity.texture.height / 2.0f);

    // Set initial game state
    game.state = STATE_PLAYING;
    game.running = true;

    TraceLog(LOG_INFO, "GAME: Initialized successfully");
    return true;
}

void game_cleanup(void)
{
    entity_cleanup(&game.player);
    npc_cleanup(&game.orwell);
    assets_unload_fonts(&game.fonts);
    CloseWindow();
    TraceLog(LOG_INFO, "GAME: Cleaned up");
}

void game_handle_input(float dt)
{
    // Global input
    if (IsKeyPressed(KEY_Q)) {
        game.running = false;
        return;
    }

    // Toggle inventory
    if (IsKeyPressed(KEY_I)) {
        if (game.state == STATE_PLAYING) {
            game.state = STATE_INVENTORY;
        } else if (game.state == STATE_INVENTORY) {
            game.state = STATE_PLAYING;
        }
    }

    // State-specific input
    if (game.state != STATE_PAUSED) {
        // Reset velocity each frame
        game.player.velocity = (Vector2){0, 0};

        // Movement input
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            game.player.velocity.x = -PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            game.player.velocity.x = PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            game.player.velocity.y = -PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            game.player.velocity.y = PLAYER_SPEED;
        }
    }

    (void)dt;  // Unused for now
}

void game_update(float dt)
{
    if (game.state != STATE_PAUSED) {
        // Update player
        entity_update(&game.player, dt);

        // Keep player on screen
        if (game.player.hitbox.x < 0) {
            game.player.hitbox.x = 0;
        }
        if (game.player.hitbox.x > WINDOW_WIDTH) {
            game.player.hitbox.x = WINDOW_WIDTH;
        }
        if (game.player.hitbox.y < 0) {
            game.player.hitbox.y = 0;
        }
        if (game.player.hitbox.y > WINDOW_HEIGHT) {
            game.player.hitbox.y = WINDOW_HEIGHT;
        }
    } else if (game.state == STATE_INVENTORY) {
        inventory_update(&game.inventory, dt);
    }
}

void game_render(void)
{
    BeginDrawing();
    ClearBackground(BLACK);

    // Always draw the game world
    entity_draw(&game.player);
    npc_draw(&game.orwell, &game.fonts, WINDOW_WIDTH);

    // Draw UI overlays based on state
    if (game.state == STATE_INVENTORY) {
        inventory_draw(&game.inventory, &game.fonts);
    }

    // Debug info
    DrawFPS(10, 10);

    EndDrawing();
}

bool game_should_run(void)
{
    return game.running && !WindowShouldClose();
}
