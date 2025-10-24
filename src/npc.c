#include "npc.h"
#include "entity.h"
#include "assets.h"
#include "text_utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void npc_init(NPC *npc)
{
    entity_init(&npc->entity);
    memset(npc->name, 0, sizeof(npc->name));
    memset(npc->dialogue, 0, sizeof(npc->dialogue));
    npc->display_name = NULL;
    npc->display_dialogue = NULL;
    npc->name_font_size = 15.0f;
    npc->dialogue_font_size = 25.0f;
    npc->is_hebrew = false;
}

bool npc_setup(NPC *npc, const char *texture_path, const char *name,
               const char *dialogue, bool is_hebrew)
{
    // Load the entity texture
    if (!entity_load_texture(&npc->entity, texture_path)) {
        return false;
    }

    // Copy name and dialogue (with bounds checking)
    strncpy(npc->name, name, MAX_NPC_NAME_LENGTH - 1);
    npc->name[MAX_NPC_NAME_LENGTH - 1] = '\0';

    strncpy(npc->dialogue, dialogue, MAX_NPC_DIALOGUE_LENGTH - 1);
    npc->dialogue[MAX_NPC_DIALOGUE_LENGTH - 1] = '\0';

    npc->is_hebrew = is_hebrew;

    // Create display strings (reversed for Hebrew)
    if (is_hebrew) {
        npc->display_name = text_reverse_hebrew(name);
        npc->display_dialogue = text_reverse_hebrew(dialogue);
    } else {
        npc->display_name = strdup(name);
        npc->display_dialogue = strdup(dialogue);
    }

    // Check for allocation failure
    if (!npc->display_name || !npc->display_dialogue) {
        free(npc->display_name);
        free(npc->display_dialogue);
        npc->display_name = NULL;
        npc->display_dialogue = NULL;
        return false;
    }

    return true;
}

void npc_set_position(NPC *npc, float x, float y)
{
    entity_set_position(&npc->entity, x, y);
}

void npc_set_size(NPC *npc, float width, float height)
{
    entity_set_size(&npc->entity, width, height);
}

void npc_set_dialogue(NPC *npc, const char *dialogue)
{
    strncpy(npc->dialogue, dialogue, MAX_NPC_DIALOGUE_LENGTH - 1);
    npc->dialogue[MAX_NPC_DIALOGUE_LENGTH - 1] = '\0';

    // Update display dialogue
    free(npc->display_dialogue);
    if (npc->is_hebrew) {
        npc->display_dialogue = text_reverse_hebrew(dialogue);
    } else {
        npc->display_dialogue = strdup(dialogue);
    }
}

void npc_update(NPC *npc, float dt)
{
    entity_update(&npc->entity, dt);
}

void npc_draw(const NPC *npc, const Fonts *fonts, int screen_width)
{
    // Draw the base entity (sprite)
    entity_draw(&npc->entity);

    const int nickname_pad = (int)(npc->name_font_size * 1.1f);

    if (npc->is_hebrew) {
        // Draw Hebrew name (using pre-reversed display string)
        if (npc->display_name) {
            Vector2 name_size = MeasureTextEx(fonts->heebo, npc->display_name, npc->name_font_size, 1.0f);
            int name_x = (int)(npc->entity.hitbox.x - name_size.x / 2);
            int name_y = (int)(npc->entity.hitbox.y + npc->entity.hitbox.height / 2 + nickname_pad);
            DrawTextEx(fonts->heebo, npc->display_name, (Vector2){name_x, name_y}, npc->name_font_size, 1.0f, WHITE);
        }

        // Draw Hebrew dialogue (using pre-reversed display string)
        if (npc->display_dialogue && strlen(npc->display_dialogue) > 0) {
            float dialogue_font_size = npc->dialogue_font_size;
            Vector2 dialogue_size = MeasureTextEx(fonts->heebo, npc->display_dialogue, dialogue_font_size, 1.0f);

            // Scale dialogue to fit screen width (with 5% margin)
            if (dialogue_size.x > screen_width * 0.95f) {
                float scale = (screen_width * 0.95f) / dialogue_size.x;
                dialogue_font_size *= scale;
                dialogue_size = MeasureTextEx(fonts->heebo, npc->display_dialogue, dialogue_font_size, 1.0f);
            }

            int dialogue_x = (int)(npc->entity.hitbox.x - npc->entity.hitbox.width - dialogue_size.x / 2);
            int dialogue_y = (int)(npc->entity.hitbox.y - npc->entity.hitbox.height - (dialogue_size.y * 0.4f));
            DrawTextEx(fonts->heebo, npc->display_dialogue, (Vector2){dialogue_x, dialogue_y}, dialogue_font_size, 1.0f, WHITE);
        }
    } else {
        // Draw ASCII name
        if (npc->display_name) {
            int name_width = MeasureText(npc->display_name, (int)npc->name_font_size);
            int name_x = (int)(npc->entity.hitbox.x - name_width / 2);
            int name_y = (int)(npc->entity.hitbox.y + npc->entity.hitbox.height / 2 + nickname_pad);
            DrawText(npc->display_name, name_x, name_y, (int)npc->name_font_size, WHITE);
        }

        // Draw ASCII dialogue
        if (npc->display_dialogue && strlen(npc->display_dialogue) > 0) {
            int dialogue_width = MeasureText(npc->display_dialogue, (int)npc->dialogue_font_size);
            int dialogue_x = (int)(npc->entity.hitbox.x - dialogue_width / 2);
            int dialogue_y = (int)(npc->entity.hitbox.y - npc->entity.hitbox.height - 20);
            DrawText(npc->display_dialogue, dialogue_x, dialogue_y, (int)npc->dialogue_font_size, WHITE);
        }
    }
}

void npc_cleanup(NPC *npc)
{
    entity_cleanup(&npc->entity);
    free(npc->display_name);
    free(npc->display_dialogue);
    npc->display_name = NULL;
    npc->display_dialogue = NULL;
}