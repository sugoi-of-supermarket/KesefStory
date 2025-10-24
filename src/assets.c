#include "assets.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Private state
static char asset_dir[MAX_PATH_LEN] = {0};

// Resolve asset directory by searching common locations
static void resolve_asset_path(char *out_path, size_t max_len)
{
    const char *search_paths[] = {
        "./assets",
        "../assets",
        "../../assets",
        "./c/assets",
        "/Users/ido/code/kesef-story/c/assets",  // Fallback absolute path
    };

    const size_t num_paths = sizeof(search_paths) / sizeof(search_paths[0]);

    for (size_t i = 0; i < num_paths; i++) {
        if (DirectoryExists(search_paths[i])) {
            strncpy(out_path, search_paths[i], max_len - 1);
            out_path[max_len - 1] = '\0';
            TraceLog(LOG_INFO, "ASSETS: Found assets at: %s", out_path);
            return;
        }
    }

    // Last resort: use current directory
    strncpy(out_path, ".", max_len - 1);
    TraceLog(LOG_WARNING, "ASSETS: Could not find assets directory, using current directory");
}

// Create Hebrew codepoint array for font loading
static int *create_hebrew_codepoints(size_t *out_count)
{
    const size_t ascii_count = 128 - 32;
    const size_t hebrew_count = 0x05ff - 0x0590 + 1;
    const size_t total_count = ascii_count + hebrew_count;

    int *codepoints = malloc(sizeof(int) * total_count);
    if (!codepoints) {
        TraceLog(LOG_ERROR, "ASSETS: Failed to allocate codepoints");
        *out_count = 0;
        return NULL;
    }

    size_t idx = 0;

    // ASCII printable characters (32-127)
    for (int c = 32; c < 128; c++) {
        codepoints[idx++] = c;
    }

    // Hebrew Unicode block (U+0590 to U+05FF)
    for (int c = 0x0590; c <= 0x05ff; c++) {
        codepoints[idx++] = c;
    }

    *out_count = total_count;
    return codepoints;
}

// Public API implementation

void assets_init(const char *override_path)
{
    if (override_path) {
        strncpy(asset_dir, override_path, MAX_PATH_LEN - 1);
        TraceLog(LOG_INFO, "ASSETS: Using override path: %s", asset_dir);
    } else {
        resolve_asset_path(asset_dir, MAX_PATH_LEN);
    }
}

const char *assets_get_dir(void)
{
    return asset_dir;
}

void assets_build_path(char *out_path, size_t max_len, const char *relative_path)
{
    snprintf(out_path, max_len, "%s/%s", asset_dir, relative_path);
}

bool assets_load_fonts(Fonts *fonts)
{
    size_t codepoint_count;
    int *codepoints = create_hebrew_codepoints(&codepoint_count);
    if (!codepoints) {
        return false;
    }

    char font_path[MAX_PATH_LEN];
    assets_build_path(font_path, MAX_PATH_LEN, "fonts/Heebo/Heebo-Regular.ttf");

    fonts->heebo = LoadFontEx(font_path, 32, codepoints, codepoint_count);
    free(codepoints);

    if (fonts->heebo.texture.id == 0) {
        TraceLog(LOG_ERROR, "ASSETS: Failed to load font: %s", font_path);
        return false;
    }

    TraceLog(LOG_INFO, "ASSETS: Loaded font: %s", font_path);
    return true;
}

void assets_unload_fonts(Fonts *fonts)
{
    UnloadFont(fonts->heebo);
}

bool assets_load_texture(Texture2D *texture, const char *relative_path)
{
    char full_path[MAX_PATH_LEN];
    assets_build_path(full_path, MAX_PATH_LEN, relative_path);

    *texture = LoadTexture(full_path);
    if (texture->id == 0) {
        TraceLog(LOG_ERROR, "ASSETS: Failed to load texture: %s", full_path);
        return false;
    }

    TraceLog(LOG_INFO, "ASSETS: Loaded texture: %s", full_path);
    return true;
}

void assets_unload_texture(Texture2D *texture)
{
    UnloadTexture(*texture);
}
