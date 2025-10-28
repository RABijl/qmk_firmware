/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// do not fallback to previous layer
#undef _______
#define _______ KC_NO

enum layers {
    _BASE = 0,
    _MEDIA,
    _NAVIGATION,
    _MOUSE,
    _NUMPAD,
    _SYMBOL,
    _FUNCTION,
    _BUTTON,
};

#define MEDIA MO(_MEDIA)
#define NAV MO(_NAVIGATION)
#define MOUSE MO(_MOUSE)
#define NUM MO(_NUMPAD)
#define SYM MO(_SYMBOL)
#define FUN MO(_FUNCTION)
#define BUT MO(_BUTTON)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_S MT(MOD_LALT, KC_S)
#define CTL_D MT(MOD_LCTL, KC_D)
#define SFT_F MT(MOD_LSFT, KC_F)
#define SFT_J MT(MOD_RSFT, KC_J)
#define CTL_K MT(MOD_RCTL, KC_K)
#define ALT_L MT(MOD_RALT, KC_L)
#define GUI_SCLN MT(MOD_RGUI, KC_SCLN)
#define BUT_Z LT(_BUTTON, KC_Z)
#define BUT_SLSH LT(_BUTTON, KC_SLSH)

// Click the top thumb buttons by smashing your entire thumb on two
// keys.
const uint16_t PROGMEM nav_combo[]   = {KC_SPC, NAV, COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {KC_TAB, MOUSE, COMBO_END};
const uint16_t PROGMEM sym_combo[]   = {KC_ENT, SYM, COMBO_END};
const uint16_t PROGMEM num_combo[]   = {KC_BSPC, NUM, COMBO_END};

combo_t key_combos[] = {
    COMBO(nav_combo, NAV),
    COMBO(mouse_combo, MOUSE),
    COMBO(sym_combo, SYM),
    COMBO(num_combo, NUM),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ~     |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | NAV  |MOUSE |  |SYM   |  NUM |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |NOP   | MEDIA| ESC  | Space| TAB  |  | ENTER| BACK-| DEL  | FUNC | APP  |
 *                        |      |      |      |      |      |  |      | SPACE|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
        KC_GRV  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P  ,  KC_BSPC,
        CTL_ESC , GUI_A,  ALT_S  ,  CTL_D ,  SFT_F ,   KC_G ,                                        KC_H,   SFT_J, CTL_K ,  ALT_L ,GUI_SCLN, CTL_QUOT,
        KC_LSFT , BUT_Z,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,  NAV   ,  MOUSE ,    SYM   ,  NUM  ,   KC_N,   KC_M ,KC_COMM, KC_DOT ,BUT_SLSH,  KC_RSFT,
                                   _______,  MEDIA , KC_ESC , KC_SPC , KC_TAB ,    KC_ENT,KC_BSPC, KC_DEL,   FUN  , KC_APP
    ),

/*
 * Layer: MEDIA
 * Legend:
 * - UG: Under Glow
 * - KC_M*: Key Code Media
 * - KC_VOL*: Key Code VOLume
 */
    [_MEDIA] = LAYOUT(
        UG_SPDU , UG_VALU, UG_SATU, UG_HUEU, UG_NEXT, UG_TOGG,                                             UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, UG_SPDU,
        _______ , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                             _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, 
        UG_SPDD , UG_VALD, UG_SATD, UG_HUED, UG_PREV, _______, _______, _______,         _______, _______, _______, UG_PREV, UG_HUED, UG_SATD, UG_VALD, UG_SPDD, 
                                    _______, _______, _______, _______, _______,         KC_MSTP, KC_MPLY, KC_MUTE, _______, _______
    ),


/*
 * Layer: Navigation
 * Legend:
 * - LCS: Left Control Shift
 * - LCTL: Left ConTroL
 */
    [_NAVIGATION] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                            LCS(KC_Z),LCTL(KC_V),LCTL(KC_C),LCTL(KC_X),LCTL(KC_Z), _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                             KC_CAPS , KC_LEFT  , KC_DOWN  ,  KC_UP   , KC_RGHT  , _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_INS  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______,
                                   _______, _______, _______, _______, _______,         KC_ENT , KC_BSPC, KC_DEL  , _______  , _______
    ),

/*
 * Layer: MOUSE
 * Legend:
 * - LCS: Left Control Shift
 * - LCTL: Left ConTroL
 * - MS: MouSe
 */
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                            LCS(KC_Z),LCTL(KC_V),LCTL(KC_C),LCTL(KC_X),LCTL(KC_Z), _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                             KC_CAPS , MS_LEFT  , MS_DOWN  ,  MS_UP   , MS_RGHT  , _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_INS  , MS_WHLL  , MS_WHLD  , MS_WHLU  , MS_WHLR  , _______,
                                   _______, _______, _______, _______, _______,         MS_BTN2, MS_BTN1, MS_BTN3 , _______  , _______ 
    ),


/*
 * Layer: NUMPAD
 * Legend:
 * - BRC: BRaCket
 * - COLN: COLoN
 * - GRV: GRaVe
 * - BSLS: Back SLaSh
 */
    [_NUMPAD] = LAYOUT(
        _______, KC_LBRC,  KC_7  ,  KC_8  ,  KC_9  , KC_RBRC,                                             _______, _______, _______, _______, _______, _______,
        _______, KC_COLN,  KC_4  ,  KC_5  ,  KC_6  , KC_EQL ,                                             _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  , KC_BSLS, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, KC_DOT ,  KC_0  , KC_MINS,         _______, _______, _______, _______, _______
    ),

/*
 * Layer: SUMBOL
 * Legend:
 * - CBR: Curly BRacket
 * - PRN: PaReNthesis
 * - UNDS: UNDerScore
 */
    [_SYMBOL] = LAYOUT(
        _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                             _______, _______, _______, _______, _______, _______,
        _______, KC_SCLN, KC_DLR , KC_PERC, KC_CIRC, KC_PLUS,                                             _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_TILD, KC_EXLM,  KC_AT , KC_HASH, KC_PIPE, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, KC_LPRN, KC_RPRN, KC_UNDS,         _______, _______, _______, _______, _______
    ),

/* 
 * Layer: FUNCTION
 */
    [_FUNCTION] = LAYOUT(
        _______, KC_F12 ,  KC_F7 ,  KC_F8 ,  KC_F9 , _______,                                             _______, _______, _______, _______, _______, _______,
        _______, KC_F11 ,  KC_F4 ,  KC_F5 ,  KC_F6 , _______,                                             _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, KC_F10 ,  KC_F1 ,  KC_F2 ,  KC_F3 , _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______
    ),

/* 
 * Layer: BUTTON
 */
    [_BUTTON] = LAYOUT(
        _______, KC_UNDO, KC_CUT , KC_COPY, KC_PSTE, KC_AGIN,                                    KC_AGIN, KC_PSTE, KC_COPY, KC_CUT , KC_UNDO, _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                    _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______, 
        _______, KC_UNDO, KC_CUT , KC_COPY, KC_PSTE, KC_AGIN, _______, _______,         _______, _______, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT , KC_UNDO, _______, 
                                   _______, _______, MS_BTN3, MS_BTN1, MS_BTN2,         MS_BTN2, MS_BTN1, MS_BTN3, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev3.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case _MEDIA:
                oled_write_P(PSTR("Media\n"), false);
                break;
            case _NAVIGATION:
                oled_write_P(PSTR("Navigation"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("Mouse\n"), false);
                break;
            case _NUMPAD:
                oled_write_P(PSTR("Numpad\n"), false);
                break;
            case _SYMBOL:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _BUTTON:
                oled_write_P(PSTR("Button\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
