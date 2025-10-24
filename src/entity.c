#include "entity.h"
#include "assets.h"
#include <string.h>

void entity_init(Entity *entity)
{
    memset(entity, 0, sizeof(Entity));
}

bool entity_load_texture(Entity *entity, const char *texture_path)
{
    if (!assets_load_texture(&entity->texture, texture_path)) {
        return false;
    }

    // Set up source rectangle to cover entire texture
    entity->source = (Rectangle){
        0, 0,
        (float)entity->texture.width,
        (float)entity->texture.height
    };

    return true;
}

void entity_set_position(Entity *entity, float x, float y)
{
    entity->hitbox.x = x;
    entity->hitbox.y = y;
}

void entity_set_size(Entity *entity, float width, float height)
{
    entity->hitbox.width = width;
    entity->hitbox.height = height;

    // Center the origin
    entity->origin = (Vector2){
        width / 2.0f,
        height / 2.0f
    };
}

void entity_update(Entity *entity, float dt)
{
    entity->hitbox.x += entity->velocity.x * dt;
    entity->hitbox.y += entity->velocity.y * dt;
}

void entity_draw(const Entity *entity)
{
    DrawTexturePro(
        entity->texture,
        entity->source,
        entity->hitbox,
        entity->origin,
        0.0f,  // rotation
        WHITE
    );
}

void entity_cleanup(Entity *entity)
{
    assets_unload_texture(&entity->texture);
}
