#ifndef ASSETS_H
#define ASSETS_H

#include "types.h"
#include "config.h"
#include <stddef.h>

// Initialize asset system and resolve asset directory
void assets_init(const char *override_path);

// Get the current asset directory path
const char *assets_get_dir(void);

// Build a full path to an asset
void assets_build_path(char *out_path, size_t max_len, const char *relative_path);

// Font loading
bool assets_load_fonts(Fonts *fonts);
void assets_unload_fonts(Fonts *fonts);

// Texture loading
bool assets_load_texture(Texture2D *texture, const char *relative_path);
void assets_unload_texture(Texture2D *texture);

#endif // ASSETS_H_
