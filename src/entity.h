#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

// Initialize an entity (zeros it out)
void entity_init(Entity *entity);

// Load texture for an entity and set up source rectangle
bool entity_load_texture(Entity *entity, const char *texture_path);

// Set entity position in world coordinates
void entity_set_position(Entity *entity, float x, float y);

// Set entity size and recalculate origin
void entity_set_size(Entity *entity, float width, float height);

// Update entity physics (apply velocity)
void entity_update(Entity *entity, float dt);

// Draw entity to screen
void entity_draw(const Entity *entity);

// Clean up entity resources
void entity_cleanup(Entity *entity);

#endif // ENTITY_H_
