// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keymap_swiss_de.h"
#include "sendstring_swiss_de.h"


#define ENT_L1 LT(1, KC_ENT)
#define TAB_L2 LT(2, KC_TAB)

#define KC_LOCK LGUI(CH_L)

#define CONCAT(key) SEND_STRING(SS_TAP(key) SS_TAP(key))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │  Q     │  W     │  E     │  R     │ T      │   │  Z     │  U     │  I     │  O     │  P     │        │
           KC_LALT, CH_Q,    CH_W,    CH_E,    CH_R,    CH_T,        CH_Y,    CH_U,    CH_I,    CH_O,    CH_P,    KC_RALT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  A     │  S     │  D     │  F     │ G      │   │  H     │  J     │  K     │  L     │ / \    │        │
           KC_LSFT, CH_A,    CH_S,    CH_D,    CH_F,    CH_G,        CH_H,    CH_J,    CH_K,    CH_L,    CH_SLSH, KC_RSFT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  Y     │  X     │  C     │  V     │ B      │   │  N     │  M     │ , ;    │ . :    │ - _    │        │
           KC_LCTL, CH_Z,    CH_X,    CH_C,    CH_V,    CH_B,        CH_N,    CH_M,    CH_COMM, CH_DOT,  CH_MINS, KC_RCTL,
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
           KC_TRNS, CH_PIPE, CH_4,    CH_5,    CH_6,    KC_NO,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │        │  1     │  2     │  3     │ LOCK   │   │        │  ä     │  ö     │  ü     │  ñ     │        │
           KC_TRNS, KC_NO,   CH_1,    CH_2,    CH_3,    KC_LOCK,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //╰────────┴────────┴────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┴────────┴────────╯
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
        //                           ╰────────┴────────┴────────╯   ╰────────┴────────┴────────╯
    ),
    [2] = LAYOUT_split_3x6_3(
        //╭────────┬────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────┬────────╮
        //│        │  °     │  ?     │  {     │  }     │  ¿     │   │  ^     │  (     │  )     │  $     │        │        │
           KC_TRNS, CH_DEG,  CH_QUES, CH_LCBR, CH_RCBR, CH_QUES,     CH_CIRC, CH_LPRN, CH_RPRN, CH_DLR,  KC_NO,   KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  |     │  @     │  &     │  #     │  %     │   │  +     │  *     │  =     │  '     │  "     │        │
           KC_TRNS, CH_PIPE, CH_AT,   CH_AMPR, CH_HASH, CH_PERC,     CH_PLUS, CH_ASTR, CH_EQL,  CH_QUOT, CH_DQUO, KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┼────────┤
        //│        │  ¨     │  !     │  <     │  >     │  ¡     │   │  ~     │  [     │  ]     │  ´     │  `     │        │
           KC_TRNS, CH_DIAE, CH_EXLM, CH_LABK, CH_RABK, CH_EXLM,     CH_TILD, CH_LBRC, CH_RBRC, CH_ACUT, CH_GRV,  KC_TRNS,
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
