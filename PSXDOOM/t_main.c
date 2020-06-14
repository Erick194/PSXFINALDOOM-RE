/* t_main.c -- title intro */

#include "doomdef.h"
#include "p_spec.h"
#include "r_local.h"

int vframe1 = 0; //80077AB4 iGp000006a4
int vframe2 = 0; //80077AB8 iGp000006a8

int y_scroll;//80077FB8 uGp00000ba8
int last_ticon;//80077D38 iGp00000928

psxobj_t loadingpic;//0x80097870
psxobj_t marb01pic;//0x80097890
psxobj_t buttonspic;//0x800978B0
psxobj_t neterrpic; //0x800978d0
psxobj_t pausepic;//0x80097850
psxobj_t titlepic;//0x80097810

/*
=======================
=
= T_Start
=
=======================
*/

void T_Start(void)//L800353E4()
{
	int lump;

	Valloc_Init();
	//Z_FreeTags(mainzone,PU_CACHE);//test

	W_CacheLumpName("LOADING", PU_STATIC, 0);
	ImageToVram(&loadingpic, "LOADING", 0);
	P_LoadingPlaque(&loadingpic, 95, 109, palette[20]);
	S_Lcd_Load(0);

	W_CacheLumpName("TILE", PU_STATIC, 0);//MARB01
	W_CacheLumpName("BUTTONS", PU_STATIC, 0);
	W_CacheLumpName("NETERR", PU_STATIC, 0);
	W_CacheLumpName("PAUSE", PU_STATIC, 0);

	ImageToVram(&marb01pic, "TILE", 0);//MARB01
	ImageToVram(&buttonspic, "BUTTONS", 0);
	ImageToVram(&neterrpic, "NETERR", 0);
	ImageToVram(&pausepic, "PAUSE", 0);
	ImageToVram(&titlepic, "TITLE", 0);

	lump = R_TextureNumForName("SKY09");
	skytexturep = &textures[lump];
	skypalette = palette[15];

	W_CacheLumpNum(skytexturep->lump, PU_CACHE, true);

	TextureCache(skytexturep);

	y_scroll = 0;

	psxcd_play(CD_TRACK[cdmusic_title_screen], CDVolume);
	do {} while(psxcd_elapsed_sectors() == 0);
}

/*
=======================
=
= T_Stop
=
=======================
*/

void T_Stop(int exit)//L800355B0()
{
	S_StartSound(NULL, sfx_barexp);
	psxcd_stop();
}

/*
=======================
=
= T_Ticker
=
=======================
*/

int T_Ticker(void)//L800355DC()
{
    byte *cache, *cachetmp;
    int exit, pixel, cnt, i;

    exit = ga_nothing;

    if (ticbuttons[0] != 0)
    {
        exit = ga_exit;
    }
    else
    {
        vframe1 -= vblsinframe[consoleplayer];
        if ((vframe1 <= 0) && (y_scroll >= 128))
        {
            vframe1 = 2;
            P_FireSky(skytexturep);
        }

        if (y_scroll < 129)
            y_scroll += 4;

        if (y_scroll >= 128)
            exit = -((unsigned int)(ticon - last_ticon < 1800) ^ 1) & 7;
    }

    return exit;
}

/*
=======================
=
= T_Draw
=
=======================
*/

#if FIX_TITLE_FYRE_WITH == 1
#define SKY_W 64
#else
#define SKY_W 63
#endif // FIX_TITLE_FYRE_WITH

void T_Draw(void)//L800356B8()
{
	POLY_FT4 poly1;
	RECT rect;
	int i;
	byte *cache;

	NextTextureCacheIdx();

	// Draw 4 Fire Textures
	if (skytexturep->index == -1)
	{
		rect.x = (skytexturep->vramx >> 1) + ((skytexturep->vtpage & 15) << 6);
		rect.y = (skytexturep->vramy) + ((skytexturep->vtpage & 16) << 4);
		rect.w = 32;
		rect.h = 128;
		cache = (byte *)(lumpcache[skytexturep->lump].cache) + 8;
		LoadImage(&rect, (unsigned long *)(byte*)(cache));
		skytexturep->index = TextureCacheIdx;
	}

	setPolyFT4(&poly1);
	setRGB0(&poly1, 128, 128, 128);

	//setUV4(p,_u0,_v0,_u1,_v1,_u2,_v2,_u3,_v3)
	setUV4(&poly1,
		skytexturep->vramx     , skytexturep->vramy,
		skytexturep->vramx + SKY_W, skytexturep->vramy,
		skytexturep->vramx     , skytexturep->vramy + 127,
		skytexturep->vramx + SKY_W, skytexturep->vramy + 127);

	//setXY4(p,_x0,_y0,_x1,_y1,_x2,_y2,_x3,_y3)
	setXY4(&poly1,
		0, 112,
		SKY_W, 112,
		0, 239,
		SKY_W, 239);

	poly1.tpage = skytexturep->vtpage;
	poly1.clut = skypalette;

	for (i = 0; i < 4; i++)
	{
		W_AddPrim(&poly1);// add to order table
		poly1.x0 += SKY_W;
		poly1.x1 += SKY_W;
		poly1.x2 += SKY_W;
		poly1.x3 += SKY_W;
	}

	// Draw Title Textures
	setPolyFT4(&poly1);

	//setXY4(p,_x0,_y0,_x1,_y1,_x2,_y2,_x3,_y3)
	setXY4(&poly1,
		0  , 0,
		255, 0,
		0  , 239,
		255, 239);

	//setUV4(p,_u0,_v0,_u1,_v1,_u2,_v2,_u3,_v3)
	setUV4(&poly1,
		0  , 0  ,
		255, 0  ,
		0  , 239,
		255, 239);

    setRGB0(&poly1, y_scroll, y_scroll, y_scroll);

	poly1.tpage = titlepic.vtpage;
	poly1.clut = palette[17];

	W_AddPrim(&poly1);// add to order table

	UpdateDrawOTag();
	DrawRender();
}
