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
#include "keycodes.h"
#include QMK_KEYBOARD_H

#include "process_key_override.h"
#include "quantum_keycodes.h"
#include "os_detection.h"
#include "action_util.h"
#include "unicode.h"
#include "host.h"
#include "gpio.h"
#include "led.h"

#include "keymap_swiss_de.h"
#include "sendstring_swiss_de.h"

#include "../../../../../drivers/oled/oled_driver.h"

#ifndef LAYOUT
#define LAYOUT(...) {__VA_ARGS__}
#endif

#ifndef gpio_set_pin_output
#define gpio_set_pin_output(pin)
#endif

#ifndef gpio_write_pin_high
#define gpio_write_pin_high(pin)
#endif

#ifndef OLED_ENABLE
#define OLED_ENABLE
#endif

#define L1 MO(1)
#define L2 MO(2)

#define KC_LOCK LGUI(CH_L)

#define KC_ENYA 0x00E8
#define KC_INVQ 0x00E9
#define KC_INVE 0x00EA


enum unicode_names {
    SNK,
    TMB
};

const uint32_t PROGMEM unicode_map[] = {
    [SNK]  = 0x1F40D, // 🐍
    [TMB]  = 0x1F44D, // 👍
};

const key_override_t slash_shift_override = ko_make_basic(MOD_MASK_SHIFT, CH_SLSH, CH_BSLS);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &slash_shift_override,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
     KC_LALT,    CH_Q,    CH_W,    CH_E,    CH_R,    CH_T,                                        CH_Z,    CH_U,    CH_I,    CH_O,    CH_P, KC_LALT,
     KC_LSFT,    CH_A,    CH_S,    CH_D,    CH_F,    CH_G,                                        CH_H,    CH_J,    CH_K,    CH_L, CH_SLSH, KC_RSFT,
     KC_LCTL,    CH_Y,    CH_X,    CH_C,    CH_V,    CH_B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    CH_N,    CH_M, CH_COMM,  CH_DOT, CH_MINS, KC_LCTL,
                                KC_LGUI,  KC_ESC,      L2,  KC_SPC,  KC_TAB, KC_BSPC,  KC_ENT,      L1,  KC_DEL, KC_LGUI
    ),
    [1] = LAYOUT(
     _______, CH_ADIA,    CH_7,    CH_8,    CH_9, XXXXXXX,                                     KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, _______,
     _______, CH_ODIA,    CH_4,    CH_5,    CH_6,    CH_0,                                     KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSPC, _______,
     _______, CH_UDIA,    CH_1,    CH_2,    CH_3, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
     _______,  CH_DEG, CH_QUES, CH_LCBR, CH_RCBR, KC_INVQ,                                     CH_CIRC, CH_LPRN, CH_RPRN,  CH_DLR, XXXXXXX, _______,
     _______, CH_PIPE,   CH_AT, CH_AMPR, CH_HASH, CH_PERC,                                     CH_PLUS, CH_ASTR,  CH_EQL, CH_QUOT, CH_DQUO, _______,
     _______, CH_DIAE, CH_EXLM, CH_LABK, CH_RABK, KC_INVE, _______, _______, _______, _______, CH_TILD, CH_LBRC, CH_RBRC, CH_ACUT,  CH_GRV, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
     _______, UM(SNK),   KC_F7,   KC_F8,   KC_F9,  KC_F10,                                     XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, _______,
     _______, UM(TMB),   KC_F4,   KC_F5,   KC_F6,  KC_F11,                                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, _______,
     _______, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F12, _______, _______, _______, _______, XXXXXXX, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, 1, 2, 3);
}

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void keyboard_post_init_user(void) {
    os_variant_t os = detected_host_os();
    if (os == OS_LINUX) {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    } else if (os == OS_WINDOWS) {
        set_unicode_input_mode(UNICODE_MODE_WINDOWS);
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case CH_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case CH_1 ... CH_0:
        case KC_BSPC:
        case KC_DEL:
        case CH_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool process_normal = true;
    switch (keycode) {
        case CH_ADIA:  // ä Ä
        case CH_ODIA:  // ö Ö
        case CH_UDIA:  // ü Ü
            if (record->event.pressed) {
                const uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    switch (keycode) {
                        case CH_ADIA:
                            SEND_STRING(SS_TAP(X_RBRC) SS_LSFT(SS_TAP(X_A)));
                            break;
                        case CH_ODIA:
                            SEND_STRING(SS_TAP(X_RBRC) SS_LSFT(SS_TAP(X_O)));
                            break;
                        case CH_UDIA:
                            SEND_STRING(SS_TAP(X_RBRC) SS_LSFT(SS_TAP(X_U)));
                            break;
                    }
                    set_mods(mods);
                    process_normal = false;
                }
            }
            break;
        case KC_ENYA:  // ñ Ñ
            if (record->event.pressed) {
                const uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING(SS_RALT(SS_TAP(X_EQL)) SS_LSFT(SS_TAP(X_N)));
                    set_mods(mods);
                } else {
                    SEND_STRING(SS_RALT(SS_TAP(X_EQL)) SS_TAP(X_N));
                }
                process_normal = false;
            }
            break;
        case KC_INVQ:  // ¿
            if (record->event.pressed) {
                process_normal = false;
                os_variant_t os = detected_host_os();
                if (os == OS_LINUX) {
                    register_unicode(0x00BF);
                } else if (os == OS_WINDOWS) {
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_1)));
                } else {
                    process_normal = true;
                }
            }
            break;
        case KC_INVE:  // ¡
            if (record->event.pressed) {
                process_normal = false;
                os_variant_t os = detected_host_os();
                if (os == OS_LINUX) {
                    register_unicode(0x00A1);
                } else if (os == OS_WINDOWS) {
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_1)));
                } else {
                    process_normal = true;
                }
            }
            break;
        case CH_CIRC:  // ^
        case CH_DIAE:  // ¨
        case CH_TILD:  // ~
        case CH_ACUT:  // ´
        case CH_GRV:   // `
            if (record->event.pressed) {
                process_normal = false;
                os_variant_t os = detected_host_os();
                if (os == OS_LINUX) {
                    switch (keycode) {
                        case CH_CIRC:
                            SEND_STRING(SS_TAP(X_EQL) SS_TAP(X_EQL));
                            break;
                        case CH_DIAE:
                            SEND_STRING(SS_TAP(X_RBRC) SS_TAP(X_RBRC));
                            break;
                        case CH_TILD:
                            SEND_STRING(SS_ALGR(SS_TAP(X_EQL) SS_TAP(X_EQL)));
                            break;
                        case CH_ACUT:
                            SEND_STRING(SS_ALGR(SS_TAP(X_MINS) SS_TAP(X_MINS)));
                            break;
                        case CH_GRV:
                            SEND_STRING(SS_LSFT(SS_TAP(X_EQL) SS_TAP(X_EQL)));
                            break;
                    }
                } else if (os == OS_WINDOWS) {
                    switch (keycode) {
                        case CH_CIRC:
                            SEND_STRING(SS_TAP(X_EQL) SS_TAP(X_SPC));
                            break;
                        case CH_DIAE:
                            SEND_STRING(SS_TAP(X_RBRC) SS_TAP(X_SPC));
                            break;
                        case CH_TILD:
                            SEND_STRING(SS_ALGR(SS_TAP(X_EQL)) SS_TAP(X_SPC));
                            break;
                        case CH_ACUT:
                            SEND_STRING(SS_ALGR(SS_TAP(X_MINS)) SS_TAP(X_SPC));
                            break;
                        case CH_GRV:
                            SEND_STRING(SS_LSFT(SS_TAP(X_EQL)) SS_TAP(X_SPC));
                            break;
                    }
                } else {
                    process_normal = true;
                }
            }
            break;
    }
    return process_normal;
}

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
            case 0:
                oled_write_P(PSTR("Zero\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Uno\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Due\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Tres\n"), false);
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
