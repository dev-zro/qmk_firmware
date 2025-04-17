// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "modifiers.h"
#include "quantum_keycodes.h"
#include "process_key_override.h"
#include "action_util.h"
#include "os_detection.h"
#include "unicode.h"

#include "keymap_swiss_de.h"
#include "sendstring_swiss_de.h"


#define ENT_L1 LT(1, KC_ENT)
#define TAB_L2 LT(2, KC_TAB)

#define KC_LOCK LGUI(CH_L)

#define KC_ENYA 0x00E8
#define KC_INVQ 0x00E9
#define KC_INVE 0x00EA


const key_override_t slash_shift_override = ko_make_basic(MOD_MASK_SHIFT, CH_SLSH, CH_BSLS);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &slash_shift_override,
    NULL // Null terminate the array of overrides!
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
                                      KC_ESC,  TAB_L2,  KC_SPC,      KC_BSPC, ENT_L1,  KC_DEL
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
    [1] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │        │  7     │  8     │  9     │ GUI    │   │ HOME   │ PGDN   │ PGUP   │ END    │ INSERT │        │
           KC_TRNS, KC_NO,   CH_7,    CH_8,    CH_9,    KC_LGUI,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  0     │  4     │  5     │  6     │        │   │ LEFT   │ DOWN   │ UP     │ RIGHT  │ DELETE │        │
           KC_TRNS, CH_0,    CH_4,    CH_5,    CH_6,    KC_NO,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │  1     │  2     │  3     │ LOCK   │   │        │  ä     │  ö     │  ü     │  ñ     │        │
           KC_TRNS, KC_NO,   CH_1,    CH_2,    CH_3,    KC_LOCK,     KC_NO,   CH_ADIA, CH_ODIA, CH_UDIA, KC_ENYA, KC_TRNS,
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
           KC_TRNS, KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,      KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │ F4     │ F5     │ F6     │ F11    │   │ LEFT   │ DOWN   │ UP     │ RIGHT  │        │        │
           KC_TRNS, KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F11,      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │ F1     │ F2     │ F3     │ F12    │   │        │ PAUSE  │        │        │        │        │
           KC_TRNS, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,      KC_NO,   KC_MPLY, KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
};

void keyboard_post_init_user(void) {
    os_variant_t os = detected_host_os();
    if (os == OS_LINUX) {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    } else if (os == OS_WINDOWS) {
        set_unicode_input_mode(UNICODE_MODE_WINDOWS);
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
                    SEND_STRING(SS_ALGR(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P9) SS_TAP(X_P1)));
                } else {
                    process_normal = false;
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
                    SEND_STRING(SS_ALGR(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P6) SS_TAP(X_P1)));
                } else {
                    process_normal = false;
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
