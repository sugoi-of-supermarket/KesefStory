#ifndef NPC_H
#define NPC_H

#include "types.h"
#include <stdbool.h>

// Maximum length for NPC names and dialogue
#define MAX_NPC_NAME_LENGTH 64
#define MAX_NPC_DIALOGUE_LENGTH 256

// NPC represents a non-player character with dialogue capabilities
typedef struct {
    Entity      entity;                              // Base entity (sprite, position, etc.)
    char        name[MAX_NPC_NAME_LENGTH];          // Display name (original)
    char        dialogue[MAX_NPC_DIALOGUE_LENGTH];   // Current dialogue text (original)
    char        *display_name;                      // Rendered name (may be reversed for Hebrew)
    char        *display_dialogue;                  // Rendered dialogue (may be reversed for Hebrew)
    float       name_font_size;                     // Font size for name
    float       dialogue_font_size;                 // Font size for dialogue
    bool        is_hebrew;                          // Whether text is in Hebrew
} NPC;

// Initialize an NPC (zeros it out)
void npc_init(NPC *npc);

// Set up NPC with basic properties
bool npc_setup(NPC *npc, const char *texture_path, const char *name,
               const char *dialogue, bool is_hebrew);

// Set NPC position in world coordinates
void npc_set_position(NPC *npc, float x, float y);

// Set NPC size and recalculate origin
void npc_set_size(NPC *npc, float width, float height);

// Set NPC dialogue text
void npc_set_dialogue(NPC *npc, const char *dialogue);

// Update NPC (currently just updates the base entity)
void npc_update(NPC *npc, float dt);

// Draw NPC sprite and text
void npc_draw(const NPC *npc, const Fonts *fonts, int screen_width);

// Clean up NPC resources
void npc_cleanup(NPC *npc);

#endif // NPC_H