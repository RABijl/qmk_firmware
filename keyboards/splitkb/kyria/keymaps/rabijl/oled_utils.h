// #define OLED_ENABLE
// #define DEBUG
#ifdef OLED_ENABLE

#ifdef DEBUG
#include "print.h"
#endif
// #include <cstdint>

#define MAX_W OLED_DISPLAY_WIDTH
#define MAX_H OLED_DISPLAY_HEIGHT

void oled_write_offset_raw(const char *data, uint16_t width, uint16_t height, uint8_t offset_x, uint8_t offset_y) {
    uint16_t size = width * height;
    for (uint16_t i = 0; i < size; i += width) {
        oled_set_cursor(offset_x, offset_y);
        offset_y++;
        oled_write_raw(&data[i], width);
    }
}

void oled_write_at(const char *data, bool invert, uint8_t row, uint8_t col) {
    oled_set_cursor(row, col);
    oled_write(data, invert);
}

// void oled_distort_image(const char *data, uin8_t width, uint8_t height, uint8_t row, uint8_t col) {

// }

void oled_invert_line(void) { 
    return; 
}

void oled_draw_line_vertical(uint8_t x, uint8_t y, uint8_t w) {

#ifdef DEBUG
    if (x + w >= MAX_W) {
        uprintf("Draw vertical line width: %u + %u >=%u \n", x, w, MAX_W);
        return;
    }
    if ( y >= MAX_H) {
        uprint("Draw vertical line height: %u >= %u \n", y, MAX_H);
        return;
    }
#endif

    // divided by 8 since pixels are stored vertically
    uint16_t             start_index = x + (y / 8) * MAX_W;
    oled_buffer_reader_t reader      = oled_read_raw(start_index);
    uint8_t              mask        = (1 << (y % 8));
    for (uint8_t i = 0; i < w; i++) {
        reader.current_element[i] |= mask;
    }
}

static uint8_t pos = 0;
// void oled_scanline_render(const int8_t speed) {

//     uint8_t line_mask = (1 << ( pos % 8));
//     uint8_t invert_mask = 0;
//     if (pos > 0) {
//         invert_mask |= (1 << ((pos - 1) % 8));
//     }
//     if (pos + 1 < MAX_H) {
//         invert_mask |= (1 << ((pos + 1) % 8));
//     }

//     // divided by 8 since pixels are stored vertically
//     uint16_t buffer_index = (pos / 8) * MAX_W;
//     oled_buffer_reader_t reader = oled_read_raw(buffer_index);
//     for (uint8_t i = 0; i < MAX_W; i++) {
//         reader.current_element[i] |= line_mask;
//         reader.current_element[i] ^= invert_mask;
//     }
//     uint8_t new_pos = pos + 1;
//     pos             = new_pos > OLED_DISPLAY_HEIGHT ? 0 : new_pos;

//     // TODO: mark blocks as dirty
    
// }
// void oled_scanline_clear() {}

void oled_scanline_render(const int8_t speed, const uint8_t x, const uint8_t w){
    uint8_t end = x + w > MAX_W ? MAX_W : x + w;

    if(pos > 0) {
        uint8_t j = pos - 1;
        for(uint8_t i = x; i < end; i++){
            oled_write_pixel(i, j, false);
        }
    }
    for (uint8_t i = x; i < end; i++) {
        oled_write_pixel(i, pos, true);
    }
    if(pos + 1 < MAX_W) {
        uint8_t j = pos + 1;
        for(uint8_t i = x; i < end; i++) {
            oled_write_pixel(i, j, false);
        }
    }
    uint8_t new_pos = pos + speed;
    pos             = new_pos > OLED_DISPLAY_HEIGHT ? 0 : new_pos;

}

#endif