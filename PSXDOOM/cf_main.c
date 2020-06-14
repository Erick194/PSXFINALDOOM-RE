/* cf_main.c -- configuration menu */

#include "doomdef.h"
#include "p_local.h"
#include "st_main.h"
#include "r_local.h"

char fuctionsnames[][16] =//80073B9C
{
	"Attack",
	"Use",
	"Strafe On",
	"Speed",
	"Strafe Left",
	"Strafe Right",
	"Weapon Backward",
	"Weapon Forward",
	///New Final Doom
	"Move Backward",
	"Move Forward"
};

// Mouse Variables
int m_sensitivity   = 50;   //80077FB4|iGp00000664
int m_leftbutton    = 0;    //80077FB8|iGp00000668
int m_rightbutton   = 2;    //80077FBC|iGp0000066c

/*
=================
=
= CF_Start
=
=================
*/

void CF_Start(void)//L80037Cf8()
{
	S_StartSound(NULL, sfx_pistol);
	cursorframe = 0;
	cursorpos[0] = 0;
	ImageToVram(&buttonspic, "BUTTONS", 0);
}

/*
=================
=
= CF_Stop
=
=================
*/

#define Control_Pad 4

void CF_Stop(int exit)//L80037D3C()
{
	S_StartSound(NULL, sfx_pistol);
	cursorpos[0] = Control_Pad;
}

/*
=================
=
= CF_Ticker
=
=================
*/

int CF_Ticker(void)//L80037D68()
{
	unsigned int *tmpcfg;
	int cnt, buttons;

    if ((gamevbls < (int)gametic) && ((gametic & 3) == 0))
        cursorframe ^= 1;

	buttons = Get_PadButtons(&ticbuttons[0]);//ticbuttons[0];

	if (buttons & PAD_ARROWS)
	{
        m_vframe1[0] -= vblsinframe[0];
        if (m_vframe1[0] <= 0)
        {
            m_vframe1[0] = TICRATE;

            if (buttons & PAD_DOWN)
			{
				cursorpos[0]++;
				if (cursorpos[0] > 9)
					cursorpos[0] = 0;

				S_StartSound(NULL, sfx_pstop);
			}
			else if (buttons & PAD_UP)
			{
				cursorpos[0]--;
				if (cursorpos[0] < 0)
					cursorpos[0] = 9;

				S_StartSound(NULL, sfx_pstop);
			}
        }
	}
	else
	{
		m_vframe1[0] = 0;
	}

	if (buttons & (PAD_START | PAD_SELECT))
		return ga_exit;

	if (buttons != (unsigned short)oldticbuttons[0])
	{
        if (cursorpos[0] == 8) // Default
        {
            if (buttons & PAD_ACTION)
            {
                D_memcpy(&ActualConfiguration, &DefaultConfiguration, sizeof(int) * 8);

                // Apply Mouse Flag Binds
                ActualConfiguration[m_leftbutton] |= MOUSE_LEFT;
                ActualConfiguration[m_rightbutton] |= MOUSE_RIGHT;

                S_StartSound(NULL, sfx_swtchx);
            }
        }
        else
        {
            if (cursorpos[0] < 8) // Set New Flag Bind
            {
                tmpcfg = TempConfiguration;
                for (cnt = 0; cnt < 8; cnt++, tmpcfg++)
                {
                    if ((buttons & *tmpcfg) && !(buttons & (MOUSE_LEFT|MOUSE_RIGHT)))
                    {
                        ActualConfiguration[cursorpos[0]] = *tmpcfg;
                        S_StartSound(NULL, sfx_swtchx);
                        break;
                    }
                }
            }
            else if ((cursorpos[0] == 9) && (buttons & PAD_ACTION)) // Exit
            {
                return ga_exit;
            }
        }
	}

	return ga_nothing;
}

/*
=================
=
= CF_Drawer
=
=================
*/

void CF_Drawer(void)//L80037FB8()
{
	int		picid, cnt, cnt2, xpos, ypos;
	unsigned int *tmpcfg;
	unsigned int *actcfg;

	NextTextureCacheIdx();

	//Draw Backround MARB01 Pic
	for (ypos = 0; ypos < 4; ypos++)
	{
		for (xpos = 0; xpos < 4; xpos++)
		{
			DrawStaticImage(&marb01pic, xpos << 6, ypos << 6, palette[20]);
		}
	}

	ST_DrawText(-1, 15, "Control Pad");//Draw Text

	//Draw Skull Selector
	DrawImage(statuspic.vtpage, palette[16], 10, (cursorpos[0] * 20) + 38, (cursorframe * M_SKULL_W) + M_SKULL_VX, M_SKULL_VY, M_SKULL_W, M_SKULL_H);

	//Draw Psx Buttons Graphics
	ypos = 40;
	actcfg = ActualConfiguration;
	for (cnt = 0; cnt < 8; cnt++, actcfg++)
	{
		picid = 0;

		tmpcfg = TempConfiguration;
		for (cnt2 = 0; cnt2 < 8; cnt2++, tmpcfg++)
		{
			if(*actcfg & *tmpcfg)
				break;

			picid++;
		}
		//Draw Buttons PSX
        if (cursorpos[0] != cnt || !(ticon & 8))
            DrawImage(buttonspic.vtpage, palette[20], 38, ypos, buttonspic.vramx + (picid * 16), buttonspic.vramy, 16, 16);

		ypos += 20;
	}

	//Draw Options names
	ypos = 40;
	for (cnt = 0; cnt < 8; cnt++)
	{
		ST_DrawText(65, ypos, fuctionsnames[cnt]);
		ypos += 20;
	}

	//Draw Default Text
    ST_DrawText(65, 200, "Default");

    //Draw Exit Text
    ST_DrawText(65, 220, "Exit"); /* FIXME */

	UpdateDrawOTag();
	DrawRender();
}

/*
==================================
=
=   Mouse Configuration from Final Doom
=
==================================
*/

/*
=================
=
= CFM_Start
=
=================
*/

void CFM_Start(void)//L800381D8()
{
	S_StartSound(NULL, sfx_pistol);
    cursorframe = 0;
	cursorpos[0] = 0;
	ImageToVram(&buttonspic, "BUTTONS", 0);

    ActualConfiguration[m_leftbutton ] &= ~MOUSE_LEFT;
    ActualConfiguration[m_rightbutton] &= ~MOUSE_RIGHT;
}

/*
=================
=
= CFM_Stop
=
=================
*/

#define Mouse 3

void CFM_Stop(int exit)//L8003825C()
{
	S_StartSound(NULL, sfx_pistol);

    ActualConfiguration[m_leftbutton ] |= MOUSE_LEFT;
    ActualConfiguration[m_rightbutton] |= MOUSE_RIGHT;
    M_SENSITIVITY[0] = (m_sensitivity * (100*FRACUNIT)) / 92;

	cursorpos[0] = Mouse;
}

/*
=================
=
= CFM_Ticker
=
=================
*/

int CFM_Ticker(void)//L80038300()
{
	unsigned int *tmpcfg;
	int cnt, buttons, oldbuttons;

    buttons = Get_PadButtons(&ticbuttons[0]);
    oldbuttons = (unsigned short)oldticbuttons[0];

    if ((gamevbls < (int)gametic) && !(gametic & 3))
        cursorframe ^= 1;

    if ((buttons != oldbuttons) && (buttons & (PAD_START | PAD_SELECT)))
    {
        return ga_exit;
    }

    if (!(buttons & (PAD_ARROWS | PAD_ACTION)))
    {
        m_vframe1[0] = 0;
        return ga_nothing;
    }

    m_vframe1[0] -= vblsinframe[0];
    if (m_vframe1[0] <= 0)
    {
        m_vframe1[0] = TICRATE;

        if (buttons & PAD_DOWN)
        {
            cursorpos[0]++;
            if (cursorpos[0] > 4)
                cursorpos[0] = 0;

            S_StartSound(NULL, sfx_pstop);
        }
        else if (buttons & PAD_UP)
        {
            cursorpos[0]--;
            if (cursorpos[0] < 0)
                cursorpos[0] = 4;

            S_StartSound(NULL, sfx_pstop);
        }

        if(cursorpos[0] == 1)
        {
            if (buttons & PAD_RIGHT)
			{
				m_leftbutton++;
				if (m_leftbutton > 9)
					m_leftbutton = 9;
                else
                    S_StartSound(NULL, sfx_swtchx);
			}
			else if (buttons & PAD_LEFT)
			{
				m_leftbutton--;
				if (m_leftbutton < 0)
					m_leftbutton = 0;
                else
                    S_StartSound(NULL, sfx_swtchx);
			}
        }
        else if(cursorpos[0] == 2)
        {
            if (buttons & PAD_RIGHT)
			{
				m_rightbutton++;
				if (m_rightbutton > 9)
					m_rightbutton = 9;
                else
                    S_StartSound(NULL, sfx_swtchx);
			}
			else if (buttons & PAD_LEFT)
			{
				m_rightbutton--;
				if (m_rightbutton < 0)
					m_rightbutton = 0;
                else
                    S_StartSound(NULL, sfx_swtchx);
			}
        }
    }

    if(cursorpos[0] == 3)//default
    {
        if ((buttons != oldbuttons) && (buttons & PAD_ACTION))
        {
            m_sensitivity = 50;
            m_leftbutton = 0;
            m_rightbutton = 2;
            S_StartSound(NULL, sfx_swtchx);
            return ga_nothing;
        }
    }
    else
    {
        if (cursorpos[0] < 4)
        {
            if (cursorpos[0] == 0)//sensitivity
            {
                if (buttons & PAD_RIGHT)
                {
                    m_sensitivity++;
                    if (m_sensitivity > 92)
                    {
                        m_sensitivity = 92;
                        return ga_nothing;
                    }
                }
                else if (buttons & PAD_LEFT)
                {
                    m_sensitivity--;
                    if (m_sensitivity < 8)
                    {
                        m_sensitivity = 8;
                        return ga_nothing;
                    }
                }

                if ((m_sensitivity & 1) != 0)
                {
                    S_StartSound(NULL, sfx_stnmov);
                    return ga_nothing;
                }
            }
        }
        else
        {
            if (cursorpos[0] == 4)//exit
            {
                if ((buttons != oldbuttons) && (buttons & PAD_ACTION))
                {
                    return ga_exit;
                }
            }
        }
    }

	return ga_nothing;
}

/*
=================
=
= CFM_Drawer
=
=================
*/

void CFM_Drawer(void)//L80038628()
{
	int		picid, cnt, cnt2, xpos, ypos;
	unsigned int *tmpcfg;
	unsigned int *actcfg;

	NextTextureCacheIdx();

	//Draw Backround MARB01 Pic
	for (ypos = 0; ypos < 4; ypos++)
	{
		for (xpos = 0; xpos < 4; xpos++)
		{
			DrawStaticImage(&marb01pic, xpos << 6, ypos << 6, palette[20]);
		}
	}

	ST_DrawText(-1, 20, "Mouse");
	ST_DrawText(64, 50, "Sensitivity");

	//Draw Bar Dial
	DrawImage(statuspic.vtpage, palette[16], 65, 70, 0, 184, 108, 11);
	DrawImage(statuspic.vtpage, palette[16], m_sensitivity + 66, 70, 108, 184, 6, 11);

	ST_DrawText(64, 95, "Left Button");
	ST_DrawText(74, 115, fuctionsnames[m_leftbutton]);

	ST_DrawText(64, 140, "Right_Button");
	ST_DrawText(74, 160, fuctionsnames[m_rightbutton]);

	ST_DrawText(64, 185, "Default");
	ST_DrawText(64, 210, "Exit");

	//Draw Skull Selector
	if(cursorpos[0] == 4)
        ypos = (cursorpos[0] * 45) + 30;
    else
        ypos = (cursorpos[0] * 45) + 48;

	DrawImage(statuspic.vtpage, palette[16], 40, ypos, (cursorframe * M_SKULL_W) + M_SKULL_VX, M_SKULL_VY, M_SKULL_W, M_SKULL_H);

	UpdateDrawOTag();
	DrawRender();
}
