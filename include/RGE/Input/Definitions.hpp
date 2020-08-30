#pragma once

// =============================================================================
// Keycodes
// =============================================================================

/* The unknown key */
#define RGE_KEY_UNKNOWN            -1

/* Printable keys */
#define RGE_KEY_SPACE              32
#define RGE_KEY_APOSTROPHE         39  /* ' */
#define RGE_KEY_COMMA              44  /* , */
#define RGE_KEY_MINUS              45  /* - */
#define RGE_KEY_PERIOD             46  /* . */
#define RGE_KEY_SLASH              47  /* / */
#define RGE_KEY_0                  48
#define RGE_KEY_1                  49
#define RGE_KEY_2                  50
#define RGE_KEY_3                  51
#define RGE_KEY_4                  52
#define RGE_KEY_5                  53
#define RGE_KEY_6                  54
#define RGE_KEY_7                  55
#define RGE_KEY_8                  56
#define RGE_KEY_9                  57
#define RGE_KEY_SEMICOLON          59  /* ; */
#define RGE_KEY_EQUAL              61  /* = */
#define RGE_KEY_A                  65
#define RGE_KEY_B                  66
#define RGE_KEY_C                  67
#define RGE_KEY_D                  68
#define RGE_KEY_E                  69
#define RGE_KEY_F                  70
#define RGE_KEY_G                  71
#define RGE_KEY_H                  72
#define RGE_KEY_I                  73
#define RGE_KEY_J                  74
#define RGE_KEY_K                  75
#define RGE_KEY_L                  76
#define RGE_KEY_M                  77
#define RGE_KEY_N                  78
#define RGE_KEY_O                  79
#define RGE_KEY_P                  80
#define RGE_KEY_Q                  81
#define RGE_KEY_R                  82
#define RGE_KEY_S                  83
#define RGE_KEY_T                  84
#define RGE_KEY_U                  85
#define RGE_KEY_V                  86
#define RGE_KEY_W                  87
#define RGE_KEY_X                  88
#define RGE_KEY_Y                  89
#define RGE_KEY_Z                  90
#define RGE_KEY_LEFT_BRACKET       91  /* [ */
#define RGE_KEY_BACKSLASH          92  /* \ */
#define RGE_KEY_RIGHT_BRACKET      93  /* ] */
#define RGE_KEY_GRAVE_ACCENT       96  /* ` */
#define RGE_KEY_WORLD_1            161 /* non-US #1 */
#define RGE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define RGE_KEY_ESCAPE             256
#define RGE_KEY_ENTER              257
#define RGE_KEY_TAB                258
#define RGE_KEY_BACKSPACE          259
#define RGE_KEY_INSERT             260
#define RGE_KEY_DELETE             261
#define RGE_KEY_RIGHT              262
#define RGE_KEY_LEFT               263
#define RGE_KEY_DOWN               264
#define RGE_KEY_UP                 265
#define RGE_KEY_PAGE_UP            266
#define RGE_KEY_PAGE_DOWN          267
#define RGE_KEY_HOME               268
#define RGE_KEY_END                269
#define RGE_KEY_CAPS_LOCK          280
#define RGE_KEY_SCROLL_LOCK        281
#define RGE_KEY_NUM_LOCK           282
#define RGE_KEY_PRINT_SCREEN       283
#define RGE_KEY_PAUSE              284
#define RGE_KEY_F1                 290
#define RGE_KEY_F2                 291
#define RGE_KEY_F3                 292
#define RGE_KEY_F4                 293
#define RGE_KEY_F5                 294
#define RGE_KEY_F6                 295
#define RGE_KEY_F7                 296
#define RGE_KEY_F8                 297
#define RGE_KEY_F9                 298
#define RGE_KEY_F10                299
#define RGE_KEY_F11                300
#define RGE_KEY_F12                301
#define RGE_KEY_F13                302
#define RGE_KEY_F14                303
#define RGE_KEY_F15                304
#define RGE_KEY_F16                305
#define RGE_KEY_F17                306
#define RGE_KEY_F18                307
#define RGE_KEY_F19                308
#define RGE_KEY_F20                309
#define RGE_KEY_F21                310
#define RGE_KEY_F22                311
#define RGE_KEY_F23                312
#define RGE_KEY_F24                313
#define RGE_KEY_F25                314
#define RGE_KEY_KP_0               320
#define RGE_KEY_KP_1               321
#define RGE_KEY_KP_2               322
#define RGE_KEY_KP_3               323
#define RGE_KEY_KP_4               324
#define RGE_KEY_KP_5               325
#define RGE_KEY_KP_6               326
#define RGE_KEY_KP_7               327
#define RGE_KEY_KP_8               328
#define RGE_KEY_KP_9               329
#define RGE_KEY_KP_DECIMAL         330
#define RGE_KEY_KP_DIVIDE          331
#define RGE_KEY_KP_MULTIPLY        332
#define RGE_KEY_KP_SUBTRACT        333
#define RGE_KEY_KP_ADD             334
#define RGE_KEY_KP_ENTER           335
#define RGE_KEY_KP_EQUAL           336
#define RGE_KEY_LEFT_SHIFT         340
#define RGE_KEY_LEFT_CONTROL       341
#define RGE_KEY_LEFT_ALT           342
#define RGE_KEY_LEFT_SUPER         343
#define RGE_KEY_RIGHT_SHIFT        344
#define RGE_KEY_RIGHT_CONTROL      345
#define RGE_KEY_RIGHT_ALT          346
#define RGE_KEY_RIGHT_SUPER        347
#define RGE_KEY_MENU               348

#define RGE_KEY_LAST               RGE_KEY_MENU

// =============================================================================
// MouseButton codes
// =============================================================================

#define RGE_MOUSE_BUTTON_1         0
#define RGE_MOUSE_BUTTON_2         1
#define RGE_MOUSE_BUTTON_3         2
#define RGE_MOUSE_BUTTON_4         3
#define RGE_MOUSE_BUTTON_5         4
#define RGE_MOUSE_BUTTON_6         5
#define RGE_MOUSE_BUTTON_7         6
#define RGE_MOUSE_BUTTON_8         7
#define RGE_MOUSE_BUTTON_LAST      RGE_MOUSE_BUTTON_8
#define RGE_MOUSE_BUTTON_LEFT      RGE_MOUSE_BUTTON_1
#define RGE_MOUSE_BUTTON_RIGHT     RGE_MOUSE_BUTTON_2
#define RGE_MOUSE_BUTTON_MIDDLE    RGE_MOUSE_BUTTON_3
