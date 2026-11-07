/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 6);
    return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

void keyboard_post_init_user(void)
{
    // EEPROM に保存された CPI・スクロール設定を無視して config.h の値に固定する
    // (設定は USB を挿した側の EEPROM から読まれるため、左右で挙動が変わらないようにする)
    keyball_set_cpi(0);        // 0 は KEYBALL_CPI_DEFAULT
    keyball_set_scroll_div(0); // 0 は KEYBALL_SCROLL_DIV_DEFAULT
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_FREE); // 斜めスクロール可
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void)
{
    set_auto_mouse_enable(true);
}
#endif

// ここから追加
#include "keyball44.h"
#include <stdio.h>

static const char PROGMEM my_logo[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xf3, 0xff, 0xfe, 0x7f, 0xf3, 0xff, 0xff, 0xff, 0xff,
    0xe0, 0x8e, 0x64, 0x73, 0xe0, 0x06, 0x60, 0x33, 0xe6, 0x66, 0x67, 0x33, 0xe6, 0x66, 0x67, 0x33,
    0xe6, 0x66, 0x67, 0x33, 0xe6, 0x66, 0x67, 0x33, 0xe6, 0x66, 0x67, 0x33, 0xe6, 0x66, 0x67, 0x33,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xbf, 0xbf, 0xff, 0xff,
    0xbf, 0xbf, 0xff, 0xff, 0x83, 0x3f, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xf6, 0xff, 0xff, 0xff,
    0xee, 0xf1, 0xc8, 0xf3, 0xed, 0xe0, 0xc0, 0x61, 0xdd, 0xce, 0x4e, 0x4c, 0xdb, 0xce, 0x4e, 0x40,
    0xbb, 0xce, 0x4e, 0x40, 0x30, 0x4e, 0x4e, 0x4f, 0x7f, 0xa0, 0xce, 0x61, 0x7f, 0xb1, 0xce, 0x70,
    0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    // メイン側は手元から読めるよう時計回りに90度回転 (縦長: 5文字x16行)
    // サブ側のロゴは oledkit の既定どおり180度回転
    return is_keyboard_master() ? OLED_ROTATION_90 : OLED_ROTATION_180;
}

// 指定行に書く。1行5文字ちょうどで書くと自動改行されるため、
// oled_write_ln は使わず毎回カーソル位置を指定する
static void write_row(uint8_t row, const char *str)
{
    oled_set_cursor(0, row);
    oled_write(str, false);
}

bool oled_task_user(void)
{
    if (is_keyboard_master())
    {
        uint8_t mods = get_mods();

        // レイヤ番号・名前 (名前は5文字まで)
        static const char *layer_names[] = {"Base ", "Symbl", "FnNum", "Mouse"};
        uint8_t layer = get_highest_layer(layer_state);
        char layer_str[] = "L0   ";
        layer_str[1] = '0' + layer;
        write_row(0, layer_str);
        write_row(1, layer < ARRAY_SIZE(layer_names) ? layer_names[layer] : "     ");

        // スクロールモード
        write_row(3, "Scrl ");
        write_row(4, keyball_get_scroll_mode() ? " ON  " : " OFF ");

        // 修飾キー (Caps Lock 中も Shift 扱い)
        bool is_shift = host_keyboard_led_state().caps_lock || (mods & MOD_MASK_SHIFT);
        write_row(6, is_shift ? "Shift" : "     ");
        write_row(7, (mods & MOD_MASK_CTRL) ? "Ctrl " : "     ");
        write_row(8, (mods & MOD_MASK_ALT) ? "Alt  " : "     ");
        write_row(9, (mods & MOD_MASK_GUI) ? "Win  " : "     ");

        // CPI・スクロール除数
        write_row(11, "CPI  ");
        write_row(12, get_u16_str((uint16_t)keyball_get_cpi() * 100, ' '));
        char div_str[] = "Div:0";
        div_str[4] = '0' + keyball_get_scroll_div();
        write_row(14, div_str);
    }
    else
    {
        oledkit_render_logo_user();
    }
    return false;
}
