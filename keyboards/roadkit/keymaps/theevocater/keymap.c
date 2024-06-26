#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _L0 0
#define _L1 1
#define _NP 2

enum custom_keycodes {
  NFOCUS = SAFE_RANGE,
};

#define LAYER1 MO(_L1)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*[_NP] = LAYOUT_ortho_4x4( [> Numpad <]*/
    /*KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_PLUS, \*/
    /*KC_KP_4, KC_KP_5,   KC_KP_6, KC_KP_MINUS, \*/
    /*KC_KP_1, KC_KP_2,   KC_KP_3, KC_KP_ENTER, \*/
    /*KC_KP_0, KC_KP_DOT, TG(_L1), KC_BSPC*/
  /*),*/
  [_L0] = LAYOUT_ortho_4x4( /* LAYER 0 */
    NFOCUS, _______, _______,  _______, \
    KC_LEFT, KC_DOWN, KC_UP,   _______, \
    KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, \
    KC_VOLD, KC_MUTE, KC_VOLU, LAYER1
  ),
  [_L1] = LAYOUT_ortho_4x4( /* LAYER 1 */
    RESET,   _______, _______,  _______, \
    _______, _______, _______,  _______, \
    _______, _______, _______,  _______, \
    KC_SLEP, _______, _______,  _______
  )
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _L1:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_L1);
          }
          break;
        case _NP:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_NP);
          }
          break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case NFOCUS:
			if (record->event.pressed) {
				SEND_STRING(SS_LGUI("`")); // send the ⌘-` for window switching
			} else {
				// don't need to do anything
			}
			return false;
			break;
	}
	return true;
}
