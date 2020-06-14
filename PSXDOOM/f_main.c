/* f_main.c -- finale */

#include "doomdef.h"
#include "p_local.h"
#include "st_main.h"
#include "r_local.h"


#define C_END1_TXT01	"you have assaulted and"
#define C_END1_TXT02	"triumphed over the most"
#define C_END1_TXT03	"vicious realms that the"
#define C_END1_TXT04	"demented minds of our"
#define C_END1_TXT05	"designers could devise."
#define C_END1_TXT06	"the havoc you left"
#define C_END1_TXT07	"behind you as you"
#define C_END1_TXT08	"smashed your way"
#define C_END1_TXT09	"through the master"
#define C_END1_TXT10	"levels is mute tribute"
#define C_END1_TXT11	"to your prowess."
#define C_END1_TXT12	"you have earned the"
#define C_END1_TXT13	"title of"
#define C_END1_TXT14	"Master of Destruction."

#define C_END2_TXT01	"suddenly all is silent"
#define C_END2_TXT02	"from one horizon to the"
#define C_END2_TXT03	"other."
#define C_END2_TXT04	"the agonizing echo of"
#define C_END2_TXT05	"hell fades away."
#define C_END2_TXT06	"the nightmare sky"
#define C_END2_TXT07	"turns blue."
#define C_END2_TXT08	"the heaps of monster"
#define C_END2_TXT09	"corpses begin to dissolve"
#define C_END2_TXT10	"along with the evil stench"
#define C_END2_TXT11	"that filled the air."
#define C_END2_TXT12	"maybe you_have done it."
#define C_END2_TXT13	"Have you really won..."

#define C_END3_TXT01	"you_gloat_over_the"
#define C_END3_TXT02	"carcass_of_the_guardian."
#define C_END3_TXT03	"with_its_death_you_have"
#define C_END3_TXT04	"wrested_the_accelerator"
#define C_END3_TXT05	"from_the_stinking_claws"
#define C_END3_TXT06	"of_hell._you_are_done."
#define C_END3_TXT07	"hell_has_returned_to"
#define C_END3_TXT08	"pounding_dead_folks"
#define C_END3_TXT09	"instead_of_good_live_ones."
#define C_END3_TXT10	"remember_to_tell_your"
#define C_END3_TXT11	"grandkids_to_put_a_rocket"
#define C_END3_TXT12	"launcher_in_your_coffin."
#define C_END3_TXT13	"If_you_go_to_hell_when"
#define C_END3_TXT14	"you_die_you_will_need_it"
#define C_END3_TXT15	"for_some_cleaning_up."

char *endcluster1[] =   //8007517C
{
    C_END1_TXT01,
	C_END1_TXT02,
	C_END1_TXT03,
	C_END1_TXT04,
	C_END1_TXT05,
	C_END1_TXT06,
	C_END1_TXT07,
	C_END1_TXT08,
	C_END1_TXT09,
	C_END1_TXT10,
	C_END1_TXT11,
	C_END1_TXT12,
	C_END1_TXT13,
	C_END1_TXT14,
	NULL
};

char *endcluster2[] =   //800751B8
{
    C_END2_TXT01,
	C_END2_TXT02,
	C_END2_TXT03,
	C_END2_TXT04,
	C_END2_TXT05,
	C_END2_TXT06,
	C_END2_TXT07,
	C_END2_TXT08,
	C_END2_TXT09,
	C_END2_TXT10,
	C_END2_TXT11,
	C_END2_TXT12,
	C_END2_TXT13,
	NULL
};

char *endcluster3[] =   //800751F0
{
    C_END3_TXT01,
	C_END3_TXT02,
	C_END3_TXT03,
	C_END3_TXT04,
	C_END3_TXT05,
	C_END3_TXT06,
	C_END3_TXT07,
	C_END3_TXT08,
	C_END3_TXT09,
	C_END3_TXT10,
	C_END3_TXT11,
	C_END3_TXT12,
	C_END3_TXT13,
	C_END3_TXT14,
	C_END3_TXT15,
	NULL
};

//
// Character cast strings F_FINALE.C
//
#define CC_ZOMBIE	"Zombieman"
#define CC_SHOTGUN	"Shotgun Guy"
#define CC_HEAVY	"Heavy Weapon Dude"
#define CC_IMP		"Imp"
#define CC_DEMON	"Demon"
#define CC_LOST		"Lost Soul"
#define CC_CACO		"Cacodemon"
#define CC_HELL		"Hell Knight"
#define CC_BARON	"Baron Of Hell"
#define CC_ARACH	"Arachnotron"
#define CC_PAIN		"Pain Elemental"
#define CC_REVEN	"Revenant"
#define CC_MANCU	"Mancubus"
//#define CC_ARCH		"Arch-Vile"
#define CC_SPIDER	"The Spider Mastermind"
#define CC_CYBER	"The Cyberdemon"
#define CC_HERO		"Our Hero"

//
// Final DOOM 2 animation
// Casting by id Software.
// in order of appearance
//
typedef struct
{
	char		*name;
	mobjtype_t	type;
} castinfo_t;

static castinfo_t	castorder[] = //80074898
{
	{ CC_ZOMBIE, MT_POSSESSED },
	{ CC_SHOTGUN, MT_SHOTGUY },
	{ CC_HEAVY, MT_CHAINGUY },
	{ CC_IMP, MT_TROOP },
	{ CC_DEMON, MT_SERGEANT },
	{ CC_LOST, MT_SKULL },
	{ CC_CACO, MT_HEAD },
	{ CC_HELL, MT_KNIGHT },
	{ CC_BARON, MT_BRUISER },
	{ CC_ARACH, MT_BABY },
	{ CC_PAIN, MT_PAIN },
	{ CC_REVEN, MT_UNDEAD },
	{ CC_MANCU, MT_FATSO },
	//{ CC_ARCH, MT_VILE },
	{ CC_SPIDER, MT_SPIDER },
	{ CC_CYBER, MT_CYBORG },
	{ CC_HERO, MT_PLAYER },
	{ NULL,0 }
};

typedef enum
{
	F_STAGE_TEXT,
	F_STAGE_SCROLLTEXT,
	F_STAGE_CAST,
} finalestage_t;


static int textline;			//80077F38 uGp00000b28
static int textcount;			//80077D84 uGp00000974
static byte text_array[28];	    //L800A8E2C

static int textypos;			//uGp00000950
static char **text;			    //ppuGp00000b5c

/*
=================
=
= END1_Start
=
=================
*/

void END1_Start(void)//L8003E238()
{
	P_LoadingPlaque(&loadingpic, 95, 109, palette[20]);
	Valloc_Init();

	TextureCache(&backpic);

    if (nextmap == 14)
    {
        textypos = 22;
        text = endcluster1;
    }
    else
    {
        textypos = 29;
        text = endcluster2;
    }

	textline = 0;
	textcount = 0;
	text_array[0] = '\0';

	psxcd_play_at_andloop(CD_TRACK[cdmusic_finale_final_doom],CDVolume,0,0,CD_TRACK[cdmusic_credits_demo],CDVolume,0,0);
	do { } while (psxcd_elapsed_sectors() == 0);
}

/*
=================
=
= END1_Stop
=
=================
*/

void END1_Stop(int exit)//L8003E318()
{
	gamepaused = false;
	psxcd_stop();
}

/*
=================
=
= END1_Ticker
=
=================
*/

int END1_Ticker(void)//L8003E340()
{
	unsigned int buttons, oldbuttons, exit;
	char *textdata;

	gameaction = ga_nothing;

	buttons = ticbuttons[consoleplayer];
	oldbuttons = (unsigned short)oldticbuttons[consoleplayer];

	P_CheckCheats();

	exit = gameaction;

	if (gamepaused == false)
	{
	    exit = ga_nothing;

        textdata = text[textline];
        if(textdata)
        {
            if ((gamevbls < (int)gametic) && !(gametic & 1))
            {
                if (textdata[textcount] == '\0')
                {
                    textcount = 0;
                    textline++;
                }
                else
                {
                    D_strncpy(text_array, textdata, textcount);
                }

                text_array[textcount] = '\0';
                textcount++;
            }
        }
        else if (((buttons & 0xffff) != oldbuttons) && (buttons & (PAD_ACTION|MOUSE_LEFT|MOUSE_RIGHT)))
        {
            exit = ga_exit;
        }
	}

	return exit;
}

/*
=================
=
= END1_Drawer
=
=================
*/

void END1_Drawer(void)//L8003E490()
{
	int i, ypos;

	NextTextureCacheIdx();

	DrawStaticImage(&backpic, 0, 0, palette[17]);

	ypos = textypos;
	for (i = 0; i < textline; i++)
	{
		ST_DrawText(-1, ypos, text[i]);
		ypos += 14;
	}

	ST_DrawText(-1, ypos, text_array);

	if (gamepaused)
		ST_CheatDraw();

	UpdateDrawOTag();
	DrawRender();
}


static psxobj_t demonpic;//0x80097990

//int             castrotation = 0;//test

static int				castnum;		//800780AC uGp00000c9c
static int				casttics;		//80077CFC uGp000008ec
static state_t         *caststate;		//80077DD4 puGp000009c4
static boolean			castdeath;		//80077DA4 uGp00000994
static int				castframes;		//80077EB4 uGp00000aa4
static int				castonmelee;	//80077F90 uGp00000b80
static finalestage_t	finalestage;	//80077F94 uGp00000b84

/*
=================
=
= Cast_Start
=
=================
*/

void Cast_Start(void)//L8003E558()
{
	P_LoadingPlaque(&loadingpic, 95, 109, palette[20]);
	Valloc_Init();

	ImageToVram(&demonpic, "DEMON", 0);

	P_LoadBlocks((char *)_MAPSPR31_IMG);

	text_array[0] = '\0';

	finalestage = F_STAGE_TEXT;
	textline = 0;
	textcount = 0;
	castnum = 0;
	castdeath = false;
	castframes = 0;
	castonmelee = 0;
	caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	casttics = states[mobjinfo[castorder[castnum].type].seestate].tics;
	textypos = 15;

	S_Lcd_Load(LASTLEVEL);
	psxcd_play_at_andloop(CD_TRACK[cdmusic_finale_final_doom],CDVolume,0,0,CD_TRACK[cdmusic_credits_demo],CDVolume,0,0);
	do {} while (psxcd_elapsed_sectors() == 0);
}

/*
=================
=
= Cast_Stop
=
=================
*/

void Cast_Stop(int exit)//L8003E684()
{
	gamepaused = false;
	psxcd_stop();
}

/*
=================
=
= Cast_Ticker
=
=================
*/

int Cast_Ticker(void)//L8003E6AC()
{
    unsigned int buttons, oldbuttons;
	int	st, sfx;
	char *textdata;

	gameaction = ga_nothing;

	buttons = ticbuttons[consoleplayer];
	oldbuttons = (unsigned short)oldticbuttons[consoleplayer];

	P_CheckCheats();

	if (gamepaused != 0)
	{
		return gameaction;
	}
	else
	{
		if (finalestage == F_STAGE_TEXT)
		{
			if ((gamevbls < (int)gametic) && !(gametic & 1))
            {
                textdata = endcluster3[textline];
                if(textdata)
                {
                    if (textdata[textcount] == '\0')
                    {
                        textcount = 0;
                        textline++;
                    }
                    else
                    {
                        D_strncpy(text_array, textdata, textcount);
                    }
                    text_array[textcount] = '\0';
                    textcount++;
                }
                else
                {
                    finalestage = F_STAGE_SCROLLTEXT;
                }
            }
		}
		else if(finalestage == F_STAGE_SCROLLTEXT)
		{
			textypos--;

			if (textypos < -200)
				finalestage = F_STAGE_CAST;
		}
		else if (finalestage == F_STAGE_CAST)
		{
			if (castdeath == false)
			{
                if (((buttons & 0xffff) != oldbuttons) && (buttons & (PAD_ACTION|MOUSE_LEFT|MOUSE_RIGHT)))
				{
					S_StartSound(NULL, sfx_shotgn);

					// go into death frame
					if (mobjinfo[castorder[castnum].type].deathsound)
						S_StartSound(NULL, mobjinfo[castorder[castnum].type].deathsound);

					castdeath = true;
					castframes = 0;
					caststate = &states[mobjinfo[castorder[castnum].type].deathstate];
					casttics = caststate->tics;
				}

				//test
				/*if ((buttons != oldbuttons))
				{
				    if(buttons & PAD_LEFT)
                        castrotation = castrotation+1 & 7;
                    else if(buttons & PAD_RIGHT)
                        castrotation = castrotation-1 & 7;
				}*/
			}

			if (gametic > gamevbls)
			{
				if (castdeath && caststate->nextstate == S_NULL)
				{
					/* switch from deathstate to next monster */
					castnum++;
					castdeath = false;

					if (castorder[castnum].name == NULL)
						castnum = 0;

					if (mobjinfo[castorder[castnum].type].seesound)
						S_StartSound(NULL, mobjinfo[castorder[castnum].type].seesound);

					caststate = &states[mobjinfo[castorder[castnum].type].seestate];
					castframes = 0;
				}
				else
				{
				    /* advance state*/
                    if (--casttics > 0)
                        return ga_nothing;  /* not time to change state yet */

                    /* sound hacks.... */
                    switch (caststate->nextstate)
                    {
                        case S_PLAY_ATK2:	sfx = sfx_dshtgn; break;
                        case S_POSS_ATK2:	sfx = sfx_pistol; break;
                        case S_SPOS_ATK2:	sfx = sfx_shotgn; break;
                        //case S_VILE_ATK2:	sfx = sfx_vilatk; break;
                        case S_SKEL_FIST2:	sfx = sfx_skeswg; break;
                        case S_SKEL_FIST4:	sfx = sfx_skepch; break;
                        case S_SKEL_MISS2:	sfx = sfx_skeatk; break;
                        case S_FATT_ATK8:
                        case S_FATT_ATK5:
                        case S_FATT_ATK2:	sfx = sfx_firsht; break;
                        case S_CPOS_ATK2:
                        case S_CPOS_ATK3:
                        case S_CPOS_ATK4:	sfx = sfx_pistol; break;
                        case S_TROO_ATK3:	sfx = sfx_claw; break;
                        case S_SARG_ATK2:	sfx = sfx_sgtatk; break;
                        case S_BOSS_ATK2:
                        case S_BOS2_ATK2:
                        case S_HEAD_ATK2:	sfx = sfx_firsht; break;
                        case S_SKULL_ATK2:	sfx = sfx_sklatk; break;
                        case S_SPID_ATK2:
                        case S_SPID_ATK3:	sfx = sfx_pistol; break;
                        case S_BSPI_ATK2:	sfx = sfx_plasma; break;
                        case S_CYBER_ATK2:
                        case S_CYBER_ATK4:
                        case S_CYBER_ATK6:	sfx = sfx_rlaunc; break;
                        case S_PAIN_ATK3:	sfx = sfx_sklatk; break;
                        default: sfx = 0; break;
                    }

                    if (sfx)
                        S_StartSound(NULL, sfx);
				}

				st = caststate->nextstate;
				caststate = &states[st];
				castframes++;

				if (castframes == 12)
				{   /* go into attack frame */
					if (castonmelee)
						caststate = &states[mobjinfo[castorder[castnum].type].meleestate];
					else
						caststate = &states[mobjinfo[castorder[castnum].type].missilestate];

					castonmelee ^= 1;

					if (caststate == &states[S_NULL])
					{
						if (castonmelee)
							caststate = &states[mobjinfo[castorder[castnum].type].meleestate];
						else
							caststate = &states[mobjinfo[castorder[castnum].type].missilestate];
					}
				}

				if (castframes == 24 || caststate == &states[S_PLAY])
				{
					caststate = &states[mobjinfo[castorder[castnum].type].seestate];
					castframes = 0;
				}

				casttics = caststate->tics;
				if (casttics == -1)
					casttics = TICRATE;
			}
		}
	}
	return ga_nothing;
}

/*
=================
=
= Cast_Drawer
=
=================
*/
void Cast_Drawer(void)//L8003EECC()
{
	spritedef_t*	sprdef;
	spriteframe_t*	sprframe;
	int			lump;
	boolean		flip;
	int i, xpos, ypos;
	psxobj_t *sprite;

    POLY_FT4 *spritepoly = (POLY_FT4*) getScratchAddr(128);//1F800200

	NextTextureCacheIdx();

	DrawStaticImage(&demonpic, 0, 0, palette[0]);

	if (finalestage <= (F_STAGE_TEXT + F_STAGE_SCROLLTEXT))
	{
		ypos = textypos;
		for (i = 0; i < textline; i++)
		{
			ST_DrawText(-1, ypos, endcluster3[i]);
			ypos += 14;
		}

		ST_DrawText(-1, ypos, text_array);
	}
	else if (finalestage == F_STAGE_CAST)
	{
		// draw the current frame in the middle of the screen
		sprdef = &sprites[caststate->sprite];
		sprframe = &sprdef->spriteframes[caststate->frame & FF_FRAMEMASK];
		lump = sprframe->lump[0];
		flip = (boolean)sprframe->flip[0];

		//lump = sprframe->lump[castrotation];
		//flip = (boolean)sprframe->flip[castrotation];

		sprite = &texsprites[lump - firstsprite];
		TextureCache(sprite);

		setPolyFT4(spritepoly);
		setShadeTex(spritepoly, 1);
		spritepoly->clut = palette[0];
		spritepoly->tpage = sprite->vtpage;

		ypos = 180 - sprite->y;

		if (!flip)
		{
			//setUV4(p,_u0,_v0,_u1,_v1,_u2,_v2,_u3,_v3)
            setUV4(spritepoly,
                   sprite->vramx,                   sprite->vramy,
                   sprite->vramx + sprite->w + -1,  sprite->vramy,
                   sprite->vramx,                   sprite->vramy + sprite->h + -1,
                   sprite->vramx + sprite->w + -1,  sprite->vramy + sprite->h + -1);

            xpos = 128 - sprite->x;
        }
		else
		{
			//setUV4(p,_u0,_v0,_u1,_v1,_u2,_v2,_u3,_v3)
            setUV4(spritepoly,
                   sprite->vramx + sprite->w + -1,  sprite->vramy,
                   sprite->vramx,                   sprite->vramy,
                   sprite->vramx + sprite->w + -1,  sprite->vramy + sprite->h + -1,
                   sprite->vramx,                   sprite->vramy + sprite->h + -1);

            xpos = sprite->x - (sprite->w - 128);
		}

		//setXY4(p,_x0,_y0,_x1,_y1,_x2,_y2,_x3,_y3)
        setXY4(spritepoly,
               xpos,                  ypos,
               xpos + sprite->w,      ypos,
               xpos,                  ypos + sprite->h,
               xpos + sprite->w,      ypos + sprite->h);

		W_AddPrim(spritepoly);// add to order table

		ST_DrawText(-1, 20, "Cast Of Characters");
		ST_DrawText(-1, 208, castorder[castnum].name);
	}

	if (gamepaused)
		ST_CheatDraw();

	UpdateDrawOTag();
	DrawRender();
}
