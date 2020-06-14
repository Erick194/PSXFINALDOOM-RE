#include "doomdef.h"

/*
=================
=
= Get_PadButtons
= PS1 Mouse or PS1 Control
=
=================
*/

int Get_PadButtons(int *buttons)//L80038FDC()
{
    int mouse_x, mouse_y;
    int b_code, b_code1, b_code2;

    /* Apply current buttons */
    b_code1 = *buttons;

    /* Reads the X / Y movement of the mouse, the left / right buttons, */
    /* and converts them into flag codes like a normal control */

    mouse_x = ((m_sensitivity + 5) * (signed char)(b_code1 >> 16)) / 100;
    mouse_y = ((m_sensitivity + 5) * (signed char)(b_code1 >> 24)) / 100;

    if (mouse_y >= 2)
    {
        b_code1 |= PAD_DOWN;
    }
    else if (mouse_y < -1)
    {
        b_code1 |= PAD_UP;
    }

    if (mouse_x >= 2)
    {
        b_code1 |= PAD_RIGHT;
    }
    else if (mouse_x < -1)
    {
        b_code1 |= PAD_LEFT;
    }

    b_code2 = b_code1;
    if (b_code1 & MOUSE_RIGHT)
    {
        b_code2 = b_code1 | PAD_TRIANGLE;
        *buttons = *buttons | PAD_TRIANGLE;
    }

    b_code = b_code2 & 0xffff;
    if (b_code1 & MOUSE_LEFT)
    {
        *buttons = *buttons | PAD_CROSS;
        b_code = b_code2 & 0xffff | PAD_CROSS;
    }

    return b_code;
}

