#include "inventory.h"
#include "config.h"
#include <stdio.h>

void inventory_init(InventoryWindow *inv)
{
    const int width = WINDOW_WIDTH / INVENTORY_WIDTH_RATIO;
    const int height = WINDOW_HEIGHT / INVENTORY_HEIGHT_RATIO;
    const int x = WINDOW_WIDTH / 2;
    const int y = WINDOW_HEIGHT / 2;

    inv->dimensions = (Rectangle){x, y, width, height};
    inv->bg_color = WHITE;
    inv->text_color = BLACK;
    inv->kesef_count = 69;
}

void inventory_update(InventoryWindow *inv, float dt)
{
    // For future animations or state updates
    (void)inv;
    (void)dt;
}

void inventory_draw(const InventoryWindow *inv, const Fonts *fonts)
{
    // Center the window on screen
    const int x = inv->dimensions.x - (inv->dimensions.width / 2);
    const int y = inv->dimensions.y - (inv->dimensions.height / 2);

    // Draw background
    DrawRectangle(
        x, y,
        inv->dimensions.width,
        inv->dimensions.height,
        inv->bg_color
    );

    // Draw kesef label (Hebrew: כסף - "kesef" means money)
    // Hebrew reads right-to-left, so we position from the right
    const int label_x = x + inv->dimensions.width - 50;
    const int label_y = y + inv->dimensions.height - 30;

    DrawTextEx(
        fonts->heebo,
        ":פסכ",  // ":kesef" in Hebrew (reversed for RTL display)
        (Vector2){label_x, label_y},
        20, 1.0f,
        inv->text_color
    );

    // Draw kesef amount
    char amount_text[32];
    snprintf(amount_text, sizeof(amount_text), "%d", inv->kesef_count);

    const int amount_x = label_x - 40;
    DrawTextEx(
        fonts->heebo,
        amount_text,
        (Vector2){amount_x, label_y},
        20, 1.0f,
        inv->text_color
    );
}

void inventory_add_kesef(InventoryWindow *inv, int amount)
{
    inv->kesef_count += amount;
}

void inventory_remove_kesef(InventoryWindow *inv, int amount)
{
    inv->kesef_count -= amount;
    if (inv->kesef_count < 0) {
        inv->kesef_count = 0;
    }
}
