#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"

// Initialize inventory window
void inventory_init(InventoryWindow *inv);

// Update inventory state (if needed for animations, etc.)
void inventory_update(InventoryWindow *inv, float dt);

// Draw inventory window
void inventory_draw(const InventoryWindow *inv, const Fonts *fonts);

// Add/remove kesef
void inventory_add_kesef(InventoryWindow *inv, int amount);
void inventory_remove_kesef(InventoryWindow *inv, int amount);

#endif // INVENTORY_H_
