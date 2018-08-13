#include <kernel/keyboard.h>

typedef struct {
    unsigned int SHIFT_LEFT: 1;
    unsigned int CAPS_LOCK: 1;
    unsigned int NUM_LOCK: 1;
    unsigned int EXTENDED: 1;
} KeyboardState;

static KeyboardState kState = { 0 };

static char scancode_set1[256] = {
    // Presses
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    's', 0, /*'ß', '´',*/ 0, 0, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i',
    'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h',
    'j', 'k', 'l', 0, 0, /*'ö', 'ä',*/ '#', 0, 0,
    'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, '*',
    0, ' ', 0 /*CAPS*/,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/* F1 - F10 */
    0, 0, //NUM, SCROLL
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', //KEYPAD
    0, 0, 0, 0, 0, 0 /*,,,,F11 F12*/
};

static char caps_row_set[11] = {
    '!', '"', '#', /* ,'§' */ '$', '%', '&', '/', '(', ')', '=', '?'
};

uint8_t getScancode() {

    uint8_t c = 0;

    while(!(inb(KB_CONTROL_PORT) & 1)) {}; // Wait for new input
        c = inb(KB_DATA_PORT); // read input

    return c;   
}

void processScancode(uint8_t c) {
    
    switch(c) {

        case 0xE0:
            kState.EXTENDED = 1;
            break;

        case 0x2A:
            kState.SHIFT_LEFT = 1;
            break;

        case 0xAA:
            kState.SHIFT_LEFT = 0;
            break;

        case 0x45:
            kState.NUM_LOCK = 1 - kState.NUM_LOCK;
            break;

        case 0x3A:
            kState.CAPS_LOCK = 1 - kState.CAPS_LOCK;
            break;

        case 0x0E:
            terminal_backspace();
            break;

        default:
            break;
    }

    // F Buttons
    /*if (c >= 0x3B && c <= 0x44) {
        uint8_t f = c - 0x3B + 1;
        // do whatever
    }*/
}

char getChar() {
    uint8_t scancode = getScancode();
    processScancode(scancode);
    char c  = scancode_set1[scancode];

    // Numpad check
    if (scancode >= 0x47 && scancode <= 0x53) {
        if (kState.NUM_LOCK == 0) {
            return 0;
        }
    }

    // Caps check
    if (kState.CAPS_LOCK | kState.SHIFT_LEFT) {
        if (c >= 'a' && c <= 'z') {
            return c - ('a'-'A');
        }
        if (scancode >= 0x02  && scancode <= 0x0D) {
            // Number row caps
            return caps_row_set[scancode-0x02];
        }
    }

    return c;
}