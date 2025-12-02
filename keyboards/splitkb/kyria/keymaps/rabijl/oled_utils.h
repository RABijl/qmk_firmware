
#ifdef OLED_ENABLE

#define OLED_ROTATION_WIDTH OLED_DISPLAY_WIDTH

void oled_write_offset_raw(const char *data, uint16_t width, uint16_t height, uint8_t offset_x, uint8_t offset_y) {
    uint16_t size = width * height;
    for(uint16_t i = 0; i < size; i += width){
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

static uint8_t pos = 0;
void oled_invert_line(){

}

void oled_draw_line_vertical(uint8_t x, uint8_t y, uint8_t w) {
    // divided by 8 since pixels are stored vertically
    uint16_t start_index = x + (y / 8) * OLED_DISPLAY_WIDTH ;
    oled_buffer_reader_t reader = oled_read_raw(start_index);
    uint8_t mask = (1 << (y % 8));
    for(int i = 0; i < w; i++){
        reader.current_element[i] |= mask;
    }
}

void oled_scanline_render(const int8_t speed) {

    if(pos - 1 >= 0) {
        oled_invert_line();
    }
    if(pos + 1 < OLED_DISPLAY_HEIGHT) {
        oled_invert_line();
    }
    uint8_t new_pos = pos + 1;
    pos = new_pos > OLED_DISPLAY_HEIGHT ? 0 : new_pos;
}
void oled_scanline_clear() {

}

#endif