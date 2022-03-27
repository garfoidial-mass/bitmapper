//stolen from SDL headers + a CTRL-F replace

typedef enum _keys{
    BM_KEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    BM_KEY_A = 4,
    BM_KEY_B = 5,
    BM_KEY_C = 6,
    BM_KEY_D = 7,
    BM_KEY_E = 8,
    BM_KEY_F = 9,
    BM_KEY_G = 10,
    BM_KEY_H = 11,
    BM_KEY_I = 12,
    BM_KEY_J = 13,
    BM_KEY_K = 14,
    BM_KEY_L = 15,
    BM_KEY_M = 16,
    BM_KEY_N = 17,
    BM_KEY_O = 18,
    BM_KEY_P = 19,
    BM_KEY_Q = 20,
    BM_KEY_R = 21,
    BM_KEY_S = 22,
    BM_KEY_T = 23,
    BM_KEY_U = 24,
    BM_KEY_V = 25,
    BM_KEY_W = 26,
    BM_KEY_X = 27,
    BM_KEY_Y = 28,
    BM_KEY_Z = 29,

    BM_KEY_1 = 30,
    BM_KEY_2 = 31,
    BM_KEY_3 = 32,
    BM_KEY_4 = 33,
    BM_KEY_5 = 34,
    BM_KEY_6 = 35,
    BM_KEY_7 = 36,
    BM_KEY_8 = 37,
    BM_KEY_9 = 38,
    BM_KEY_0 = 39,

    BM_KEY_RETURN = 40,
    BM_KEY_ESCAPE = 41,
    BM_KEY_BACKSPACE = 42,
    BM_KEY_TAB = 43,
    BM_KEY_SPACE = 44,

    BM_KEY_MINUS = 45,
    BM_KEY_EQUALS = 46,
    BM_KEY_LEFTBRACKET = 47,
    BM_KEY_RIGHTBRACKET = 48,
    BM_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    BM_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate BM_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    BM_KEY_SEMICOLON = 51,
    BM_KEY_APOSTROPHE = 52,
    BM_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    BM_KEY_COMMA = 54,
    BM_KEY_PERIOD = 55,
    BM_KEY_SLASH = 56,

    BM_KEY_CAPSLOCK = 57,

    BM_KEY_F1 = 58,
    BM_KEY_F2 = 59,
    BM_KEY_F3 = 60,
    BM_KEY_F4 = 61,
    BM_KEY_F5 = 62,
    BM_KEY_F6 = 63,
    BM_KEY_F7 = 64,
    BM_KEY_F8 = 65,
    BM_KEY_F9 = 66,
    BM_KEY_F10 = 67,
    BM_KEY_F11 = 68,
    BM_KEY_F12 = 69,

    BM_KEY_PRINTSCREEN = 70,
    BM_KEY_SCROLLLOCK = 71,
    BM_KEY_PAUSE = 72,
    BM_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    BM_KEY_HOME = 74,
    BM_KEY_PAGEUP = 75,
    BM_KEY_DELETE = 76,
    BM_KEY_END = 77,
    BM_KEY_PAGEDOWN = 78,
    BM_KEY_RIGHT = 79,
    BM_KEY_LEFT = 80,
    BM_KEY_DOWN = 81,
    BM_KEY_UP = 82,

    BM_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    BM_KEY_KP_DIVIDE = 84,
    BM_KEY_KP_MULTIPLY = 85,
    BM_KEY_KP_MINUS = 86,
    BM_KEY_KP_PLUS = 87,
    BM_KEY_KP_ENTER = 88,
    BM_KEY_KP_1 = 89,
    BM_KEY_KP_2 = 90,
    BM_KEY_KP_3 = 91,
    BM_KEY_KP_4 = 92,
    BM_KEY_KP_5 = 93,
    BM_KEY_KP_6 = 94,
    BM_KEY_KP_7 = 95,
    BM_KEY_KP_8 = 96,
    BM_KEY_KP_9 = 97,
    BM_KEY_KP_0 = 98,
    BM_KEY_KP_PERIOD = 99,

    BM_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    BM_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
    BM_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    BM_KEY_KP_EQUALS = 103,
    BM_KEY_F13 = 104,
    BM_KEY_F14 = 105,
    BM_KEY_F15 = 106,
    BM_KEY_F16 = 107,
    BM_KEY_F17 = 108,
    BM_KEY_F18 = 109,
    BM_KEY_F19 = 110,
    BM_KEY_F20 = 111,
    BM_KEY_F21 = 112,
    BM_KEY_F22 = 113,
    BM_KEY_F23 = 114,
    BM_KEY_F24 = 115,
    BM_KEY_EXECUTE = 116,
    BM_KEY_HELP = 117,
    BM_KEY_MENU = 118,
    BM_KEY_SELECT = 119,
    BM_KEY_STOP = 120,
    BM_KEY_AGAIN = 121,   /**< redo */
    BM_KEY_UNDO = 122,
    BM_KEY_CUT = 123,
    BM_KEY_COPY = 124,
    BM_KEY_PASTE = 125,
    BM_KEY_FIND = 126,
    BM_KEY_MUTE = 127,
    BM_KEY_VOLUMEUP = 128,
    BM_KEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     BM_KEY_LOCKINGCAPSLOCK = 130,  */
/*     BM_KEY_LOCKINGNUMLOCK = 131, */
/*     BM_KEY_LOCKINGSCROLLLOCK = 132, */
    BM_KEY_KP_COMMA = 133,
    BM_KEY_KP_EQUALSAS400 = 134,

    BM_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    BM_KEY_INTERNATIONAL2 = 136,
    BM_KEY_INTERNATIONAL3 = 137, /**< Yen */
    BM_KEY_INTERNATIONAL4 = 138,
    BM_KEY_INTERNATIONAL5 = 139,
    BM_KEY_INTERNATIONAL6 = 140,
    BM_KEY_INTERNATIONAL7 = 141,
    BM_KEY_INTERNATIONAL8 = 142,
    BM_KEY_INTERNATIONAL9 = 143,
    BM_KEY_LANG1 = 144, /**< Hangul/English toggle */
    BM_KEY_LANG2 = 145, /**< Hanja conversion */
    BM_KEY_LANG3 = 146, /**< Katakana */
    BM_KEY_LANG4 = 147, /**< Hiragana */
    BM_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    BM_KEY_LANG6 = 149, /**< reserved */
    BM_KEY_LANG7 = 150, /**< reserved */
    BM_KEY_LANG8 = 151, /**< reserved */
    BM_KEY_LANG9 = 152, /**< reserved */

    BM_KEY_ALTERASE = 153, /**< Erase-Eaze */
    BM_KEY_SYSREQ = 154,
    BM_KEY_CANCEL = 155,
    BM_KEY_CLEAR = 156,
    BM_KEY_PRIOR = 157,
    BM_KEY_RETURN2 = 158,
    BM_KEY_SEPARATOR = 159,
    BM_KEY_OUT = 160,
    BM_KEY_OPER = 161,
    BM_KEY_CLEARAGAIN = 162,
    BM_KEY_CRSEL = 163,
    BM_KEY_EXSEL = 164,

    BM_KEY_KP_00 = 176,
    BM_KEY_KP_000 = 177,
    BM_KEY_THOUSANDSSEPARATOR = 178,
    BM_KEY_DECIMALSEPARATOR = 179,
    BM_KEY_CURRENCYUNIT = 180,
    BM_KEY_CURRENCYSUBUNIT = 181,
    BM_KEY_KP_LEFTPAREN = 182,
    BM_KEY_KP_RIGHTPAREN = 183,
    BM_KEY_KP_LEFTBRACE = 184,
    BM_KEY_KP_RIGHTBRACE = 185,
    BM_KEY_KP_TAB = 186,
    BM_KEY_KP_BACKSPACE = 187,
    BM_KEY_KP_A = 188,
    BM_KEY_KP_B = 189,
    BM_KEY_KP_C = 190,
    BM_KEY_KP_D = 191,
    BM_KEY_KP_E = 192,
    BM_KEY_KP_F = 193,
    BM_KEY_KP_XOR = 194,
    BM_KEY_KP_POWER = 195,
    BM_KEY_KP_PERCENT = 196,
    BM_KEY_KP_LESS = 197,
    BM_KEY_KP_GREATER = 198,
    BM_KEY_KP_AMPERSAND = 199,
    BM_KEY_KP_DBLAMPERSAND = 200,
    BM_KEY_KP_VERTICALBAR = 201,
    BM_KEY_KP_DBLVERTICALBAR = 202,
    BM_KEY_KP_COLON = 203,
    BM_KEY_KP_HASH = 204,
    BM_KEY_KP_SPACE = 205,
    BM_KEY_KP_AT = 206,
    BM_KEY_KP_EXCLAM = 207,
    BM_KEY_KP_MEMSTORE = 208,
    BM_KEY_KP_MEMRECALL = 209,
    BM_KEY_KP_MEMCLEAR = 210,
    BM_KEY_KP_MEMADD = 211,
    BM_KEY_KP_MEMSUBTRACT = 212,
    BM_KEY_KP_MEMMULTIPLY = 213,
    BM_KEY_KP_MEMDIVIDE = 214,
    BM_KEY_KP_PLUSMINUS = 215,
    BM_KEY_KP_CLEAR = 216,
    BM_KEY_KP_CLEARENTRY = 217,
    BM_KEY_KP_BINARY = 218,
    BM_KEY_KP_OCTAL = 219,
    BM_KEY_KP_DECIMAL = 220,
    BM_KEY_KP_HEXADECIMAL = 221,

    BM_KEY_LCTRL = 224,
    BM_KEY_LSHIFT = 225,
    BM_KEY_LALT = 226, /**< alt, option */
    BM_KEY_LGUI = 227, /**< windows, command (apple), meta */
    BM_KEY_RCTRL = 228,
    BM_KEY_RSHIFT = 229,
    BM_KEY_RALT = 230, /**< alt gr, option */
    BM_KEY_RGUI = 231, /**< windows, command (apple), meta */

    BM_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    BM_KEY_AUDIONEXT = 258,
    BM_KEY_AUDIOPREV = 259,
    BM_KEY_AUDIOSTOP = 260,
    BM_KEY_AUDIOPLAY = 261,
    BM_KEY_AUDIOMUTE = 262,
    BM_KEY_MEDIASELECT = 263,
    BM_KEY_WWW = 264,
    BM_KEY_MAIL = 265,
    BM_KEY_CALCULATOR = 266,
    BM_KEY_COMPUTER = 267,
    BM_KEY_AC_SEARCH = 268,
    BM_KEY_AC_HOME = 269,
    BM_KEY_AC_BACK = 270,
    BM_KEY_AC_FORWARD = 271,
    BM_KEY_AC_STOP = 272,
    BM_KEY_AC_REFRESH = 273,
    BM_KEY_AC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    BM_KEY_BRIGHTNESSDOWN = 275,
    BM_KEY_BRIGHTNESSUP = 276,
    BM_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    BM_KEY_KBDILLUMTOGGLE = 278,
    BM_KEY_KBDILLUMDOWN = 279,
    BM_KEY_KBDILLUMUP = 280,
    BM_KEY_EJECT = 281,
    BM_KEY_SLEEP = 282,

    BM_KEY_APP1 = 283,
    BM_KEY_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    BM_KEY_AUDIOREWIND = 285,
    BM_KEY_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /* Add any other keys here. */

    BM_NUM_KEYS = 512 /**< not a key, just marks the number of KEYs
                                 for array bounds */
} KEY;

