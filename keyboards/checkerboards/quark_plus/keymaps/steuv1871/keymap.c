/* Copyright 2023 Steuv1871
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

// Layers declaration
enum layers {
    _AZERTY,
    _LOWER,
    _RAISE,
    _FUNC,
};

enum my_keycodes {
    PTMED  = SAFE_RANGE, // Custom Keycode for Interpunct
    BSPCDEL, // Custom Keycode for BSPCDEL
    ALTAB, // ALT-TAB for encoder
    SALTAB // SHIFT-ALT-TAB for encoder
};

// Globale var for ALT+TAB
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Scan to reset ALT for ALT+TAB
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) { // Timer for multiple ALT+TAB is 1250ms
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

/* CUSTOM KEYCODE */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool bsdel_mods = false; // Declaration for BSPCDEL
  switch (keycode) {
   case PTMED:  // Types an Interpunct (·)
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P8) SS_TAP(X_P3)));//SS_LALT(X_P0 X_P1 X_P8 X_P3));
      }
      return false;
    case BSPCDEL: // KC_DELETE when holding KC_LSFT and pressed KC_BSPC
      if (record->event.pressed) {
        if (get_mods() & (MOD_BIT(KC_LSFT))) {
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
          bsdel_mods = true;
        } else {
          register_code(KC_BSPC);
        }
      } else {
        if (bsdel_mods) {
          unregister_code(KC_DEL);
          register_code(KC_LSFT);
          bsdel_mods = false;
        } else {
          unregister_code(KC_BSPC);
        }
      }
      return false;
      break;
    case ALTAB:  // ALT-TAB for encoder
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(KC_TAB);
      }
      return false;
      break;
    case SALTAB:  // SHIFT-ALT-TAB for encoder
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
      }
      return false;
      break;
    default:
      return true;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Azerty
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   A  |   Z  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | DEL  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |   Q  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   M  |BSPDEL|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   W  |   X  |   C  |   V  |   B  |   N  |   ,  |   ;  |   :  |   !  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl | Func | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */
    [_AZERTY] = LAYOUT_grid(
        KC_ESC,  KC_Q,      KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_DEL,
        KC_TAB,  KC_A,      KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, BSPCDEL,
        KC_LSFT, KC_Z,      KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, MO(_FUNC), KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC,  KC_SPC,  TT(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * |      |   &  |   é  |   "  |   '  |   (  |   -  |   è  |   _  |   ç  |   à  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  |   ~  |   @  |   #  |   {  |   [  |   \  |   ]  |   }  |   )  |   =  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   <  |   ²  |   €  |   ·  |      |  |   |   ^  |   $  |   ù  |   *  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             | RAlt | Home | PgDn | PgUp | End  |
    * `-----------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT_grid(
        _______, KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,          KC_8,          KC_9,    KC_0,    _______,
        KC_ESC,  ALGR(KC_2), ALGR(KC_0), ALGR(KC_3), ALGR(KC_4), ALGR(KC_5), ALGR(KC_8), ALGR(KC_MINS), ALGR(KC_EQL),  KC_MINS, KC_EQL,  _______,
        _______, KC_NUBS,    KC_GRV,     ALGR(KC_E), PTMED,      KC_NO,      ALGR(KC_6), KC_LBRC,       KC_RBRC,       KC_QUOT, KC_BSLS, _______,
        _______, _______,    _______,    _______,    _______,    _______,    _______,    KC_RALT,       KC_HOME,       KC_PGDN, KC_PGUP, KC_END
    ),

    /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |   +  |   -  |   7  |   8  |   9  |   -  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |   *  |   /  |   4  |   5  |   6  |   +  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |   1  |   2  |   3  |   *  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      | CALC |      |      |      |             |      |   0  |   .  |   /  |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_grid(
        _______, TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), KC_PPLS, KC_PMNS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
        _______, TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), KC_PAST, KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), TO(_AZERTY), XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PAST, _______,
        _______, KC_CALC,     _______,     _______,     TO(_AZERTY), _______, _______, _______, KC_P0,   KC_PDOT, KC_PSLS, _______
    ),

    /* Func
    * ,-----------------------------------------------------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |RGBTGL|RGBMD+|BRGTH+| HUE+ | SAT+ | SPD+ |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |RGBKNG|RGBMD+|BRGTH-| HUE- | SAT- | SPD- |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Ins  | PrScr|ScrLck| Pause|
    * `-----------------------------------------------------------------------------------'
    */
    [_FUNC] = LAYOUT_grid(
        KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        RGB_M_K, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______,   KC_INS,  KC_PSCR, KC_SCRL, KC_PAUS
    )
};

// Rotary Encoder action definition per layer
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_AZERTY] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_HOME, KC_END) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_DOWN, KC_UP), ENCODER_CCW_CW(SALTAB, ALTAB) },
    [_RAISE]  = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(C(KC_LEFT), C(KC_RGHT)) },
    [_FUNC]   = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif
