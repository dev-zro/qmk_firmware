// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include QMK_KEYBOARD_H

#include "modifiers.h"
#include "quantum_keycodes.h"
#include "process_key_override.h"
#include "action_util.h"
#include "os_detection.h"
#include "unicode.h"
#include "gpio.h"
#include "led.h"

#include "keymap_swiss_de.h"
#include "sendstring_swiss_de.h"

// #include "chibios/gpio.h"
// #include "chibios/vendors/RP/_pin_defs.h"

#ifndef gpio_set_pin_output_push_pull
#define gpio_set_pin_output_push_pull(pin)
#endif

#ifndef gpio_set_pin_input
#define gpio_set_pin_input(pin)
#endif

#ifndef gpio_write_pin
#define gpio_write_pin(pin, level)
#endif

#define ENT_L1 LT(1, KC_ENT)
#define TAB_L2 LT(2, KC_TAB)

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
const key_override_t backspace_shift_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &slash_shift_override,
    &backspace_shift_override
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │  Q     │  W     │  E     │  R     │ T      │   │  Z     │  U     │  I     │  O     │  P     │        │
           KC_LALT, CH_Q,    CH_W,    CH_E,    CH_R,    CH_T,        CH_Z,    CH_U,    CH_I,    CH_O,    CH_P,    KC_LALT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  A     │  S     │  D     │  F     │ G      │   │  H     │  J     │  K     │  L     │ / \    │        │
           KC_LSFT, CH_A,    CH_S,    CH_D,    CH_F,    CH_G,        CH_H,    CH_J,    CH_K,    CH_L,    CH_SLSH, KC_RSFT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  Y     │  X     │  C     │  V     │ B      │   │  N     │  M     │ , ;    │ . :    │ - _    │        │
           KC_LCTL, CH_Y,    CH_X,    CH_C,    CH_V,    CH_B,        CH_N,    CH_M,    CH_COMM, CH_DOT,  CH_MINS, KC_LCTL,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_ESC,  TAB_L2,  KC_SPC,      KC_ENT,  MO(1),   KC_BSPC
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
    [1] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │  ä     │  7     │  8     │  9     │ GUI    │   │ HOME   │ PGDN   │ PGUP   │ END    │ INSERT │        │
           KC_TRNS, CH_ADIA, CH_7,    CH_8,    CH_9,    KC_LGUI,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  ö     │  4     │  5     │  6     │  0     │   │ LEFT   │ DOWN   │ UP     │ RIGHT  │ BSPC   │        │
           KC_TRNS, CH_ODIA, CH_4,    CH_5,    CH_6,    CH_0,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  ü     │  1     │  2     │  3     │ LOCK   │   │        │        │        │        │        │        │
           KC_TRNS, CH_UDIA, CH_1,    CH_2,    CH_3,    KC_LOCK,     KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
    [2] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │  °     │  ?     │  {     │  }     │  ¿     │   │  ^     │  (     │  )     │  $     │        │        │
           KC_TRNS, CH_DEG,  CH_QUES, CH_LCBR, CH_RCBR, KC_INVQ,     CH_CIRC, CH_LPRN, CH_RPRN, CH_DLR,  KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  |     │  @     │  &     │  #     │  %     │   │  +     │  *     │  =     │  '     │  "     │        │
           KC_TRNS, CH_PIPE, CH_AT,   CH_AMPR, CH_HASH, CH_PERC,     CH_PLUS, CH_ASTR, CH_EQL,  CH_QUOT, CH_DQUO, KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  ¨     │  !     │  <     │  >     │  ¡     │   │  ~     │  [     │  ]     │  ´     │  `     │        │
           KC_TRNS, CH_DIAE, CH_EXLM, CH_LABK, CH_RABK, KC_INVE,     CH_TILD, CH_LBRC, CH_RBRC, CH_ACUT, CH_GRV,  KC_TRNS,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
    [3] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │        │ F7     │ F8     │ F9     │ F10    │   │        │ DARK   │ BRIGHT │        │        │        │
           KC_TRNS, UM(SNK), KC_F7,   KC_F8,   KC_F9,   KC_F10,      KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │ F4     │ F5     │ F6     │ F11    │   │ LEFT   │ DOWN   │ UP     │ RIGHT  │        │        │
           KC_TRNS, UM(TMB), KC_F4,   KC_F5,   KC_F6,   KC_F11,      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │ F1     │ F2     │ F3     │ F12    │   │        │ PAUSE  │        │        │        │        │
           KC_TRNS, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,      KC_NO,   KC_MPLY, KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, 1, 2, 3);
}

void keyboard_post_init_user(void) {
    os_variant_t os = detected_host_os();
    if (os == OS_LINUX) {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    } else if (os == OS_WINDOWS) {
        set_unicode_input_mode(UNICODE_MODE_WINDOWS);
    }
    gpio_set_pin_output_push_pull(GP25);
    gpio_set_pin_input(GP23);
}

bool led_update_user(led_t led_state) {
    if (!led_state.num_lock) {
        tap_code(KC_NUM_LOCK);
    }
    return true;
}

void caps_word_set_user(bool active) {
    gpio_write_pin(GP25, active);
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
