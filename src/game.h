#ifndef GAME_H
#define GAME_H

#include "types.h"
#include <stdbool.h>

// Initialize game systems and load resources
bool game_init(const char *asset_dir_override);

// Clean up all game resources
void game_cleanup(void);

// Handle input for current frame
void game_handle_input(float dt);

// Update game state
void game_update(float dt);

// Render current frame
void game_render(void);

// Check if game should continue running
bool game_should_run(void);

#endif // GAME_H
