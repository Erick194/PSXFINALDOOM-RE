/* DoomDef.h */

/* Fixes and Version Update Here*/
// NEWS (PsyDoom) and ([GEC] Master Edition)
#define SHOWFPS 1
#define ENABLE_NIGHTMARE    1       // Originally Activated in the project [GEC] Master Edition
#define ENABLE_MOREMAPS		1       // Enable the increase of map limits, important note you need to change the #define LASTLEVEL to the desired value the limit is up to 255.
#define P_FNHF_UPDATE       1       // PsyDoom P_FindNextHighestFloor new code logic

//FIXES
#define FIX_LINEDEFS_DELETION   1   // Fixes for the 'linedef deletion' bug. From PsyDoom
#define RANGE_CHECKS    1           // Only if necessary to avoid alterations in the game
#define FIX_ML_DONTDRAW 1           // Automap: fix a PSX DOOM bug where lines flagged with ML_DONTDRAW would draw when the computer map powerup is obtained. From PsyDoom
#define FIX_PE_SKULL_LIMIT 1        // Fixes code error when limiting lost souls, converting Doom 2 pc function to PsxDoom (based on Jaguar Doom), code is incompatible, fixes based on repair done for Psx Final Doom.
#define FIX_FLATSPANS   1           // Precision fix for large open maps, to prevent cracks at the right of the screen. From PsyDoom.

//UPDATES
#define GH_UPDATES  1               // Psx Doom Greatest Hits Updates

#define	VINT	int

/* SONY LIBRARIES */
#include <sys/types.h>
#include <r3000.h>
#include <asm.h>
#include <kernel.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libsn.h>
#include <libgs.h>
#include <libapi.h>
#include <libcomb.h>
#include <libetc.h>
#include <sys/file.h> /* O_RDONLY|O_WRONLY|O_NOWAIT */

/* PSX CD INCLUDES */
#include "psxcd.h"
#include "psxcdabs.h"

/* WESS API INCLUDES */
#include "wessapi.h"
#include "wessarc.h"
#include "psxcd.h"
#include "psxspu.h"
#include "wessapi.h"
#include "seqload.h"
#include "lcdload.h"

/* NEW GEC */
#define setClutNum(p,num) \
	((p)->clut = num)

/*============================================================================= */

/* all external data is defined here */
#include "doomdata.h"

/* header generated by multigen utility */
#include "info.h"

#define MAXCHAR ((char)0x7f)
#define MAXSHORT ((short)0x7fff)
#define MAXINT	((int)0x7fffffff)	/* max pos 32-bit int */
#define MAXLONG ((long)0x7fffffff)

#define MINCHAR ((char)0x80)
#define MINSHORT ((short)0x8000)
#define MININT 	((int)0x80000000)	/* max negative 32-bit integer */
#define MINLONG ((long)0x80000000)

#ifndef NULL
#define	NULL	0
#endif

// PSX Doom

#define LASTLEVEL   31  // 60 is defined as it is the last level map entry, it does not contain a specific map, it is used to limit passwords, load sounds for credits.

/*
// Stores information about a texture, including it's dimensions, lump info and texture cache info
struct texture_t {
  0 0  2 int16_t                     offsetX;
    2  2 int16_t                     offsetY;
  1 4  2 int16_t                     width;                  // TODO: is this signed or unsigned?
    6  2 int16_t                     height;                 // TODO: is this signed or unsigned?
  2 8  1 uint8_t                     texPageCoordX;          // TODO: COMMENT
    9  1 uint8_t                     texPageCoordY;          // TODO: COMMENT
    10 2 uint16_t                    texPageId;              // TODO: COMMENT
  3 12 2 uint16_t                    widthIn16Blocks;        // Width in 16 pixel increments (rounded up)
    14 2 uint16_t                    heightIn16Blocks;       // Height in 16 pixel increments (rounded up)
  4 16 2 uint16_t                    lumpNum;
    18 2 uint16_t                    __padding;              // TODO: is this actually used?
  5 20 4 VmPtr<VmPtr<texture_t>>     ppTexCacheEntry;        // The texture cache entry for this texture
  6 24 4 uint32_t                    unknown1;               // TODO: what is this?
  7 28 4 uint32_t                    uploadFrameNum;         // What frame the texture was added to the texture cache, used to detect texture cache overflows
};
*/

//
// Object Data Psx Doom
//
typedef struct psxobj_s
{
	short           x;		// pixels to the left of origin
	short           y;		// pixels below the origin
	short           w;		// width image
	short           h;		// height image

	unsigned char   vramx;	// vram position x
	unsigned char   vramy;	// vram position y

	unsigned short  vtpage;	// base tpage info
	unsigned short  vbasex;	// base x pos in vram
	unsigned short  vbasey;	// base y pos in vram
	unsigned short  lump;	// lump number
    unsigned short  pad1;	// lump number
	unsigned long   *vptr;	// ptr to an arry for the tpage??
	unsigned int    pad2;
	unsigned int    index;
} psxobj_t;

typedef struct
{
	short leftoffset;
	short topoffset;
	short width;
	short height;
} patchpsx_t;

#define FIRESKY_WIDTH	64
#define FIRESKY_HEIGHT	128
#define FIREPOS1 ((FIRESKY_WIDTH * FIRESKY_HEIGHT) - FIRESKY_WIDTH)
#define FIREPOS2 ((FIRESKY_WIDTH * FIRESKY_HEIGHT) - 1)


extern byte tempbuffer[0x10000];	//80098528 Psx Doom

int D_vsprintf(char *string, const char *format, int *argptr);

void D_printf (char *str, ...);

/*
===============================================================================

						GLOBAL TYPES

===============================================================================
*/

#define MAXPLAYERS	2
#define TICRATE		15			/* number of tics / second */

#define	FRACBITS		16
#define	FRACUNIT		(1<<FRACBITS)
#define	FRACMASK        (FRACUNIT-1)    //Named from PsyDoom (StationDoom)

typedef int fixed_t;

#define	ANG45	0x20000000
#define	ANG90	0x40000000
#define	ANG180	0x80000000
#define	ANG270	0xc0000000
typedef unsigned angle_t;

#define	FINEANGLES			8192
#define	FINEMASK			(FINEANGLES-1)
#define	ANGLETOFINESHIFT	19	/* 0x100000000 to 0x2000 */

extern	fixed_t		finesine[5*FINEANGLES/4];
extern	fixed_t		*finecosine;

typedef enum
{
	sk_baby,
	sk_easy,
	sk_medium,
	sk_hard,
	sk_nightmare
} skill_t;

typedef enum
{
	ga_nothing,
	ga_died,
	ga_completed,
	ga_secretexit,
	ga_warped,
	ga_exitdemo,
	//News
	ga_recorddemo,
	ga_timeout,
	ga_restart,
	ga_exit
} gameaction_t;


/* */
/* library replacements */
/* */

void D_memset (void *dest, int val, int count);
void D_memcpy (void *dest, void *src, int count);
void D_strncpy (char *dest, char *src, int maxcount);
int D_strncasecmp (char *s1, char *s2, int len);


/*
===============================================================================

							MAPOBJ DATA

===============================================================================
*/

struct mobj_s;

/* think_t is a function pointer to a routine to handle an actor */
typedef void (*think_t) ();

/* a latecall is a function that needs to be called after p_base is done */
typedef void (*latecall_t) (struct mobj_s *mo);

typedef struct thinker_s
{
	struct		thinker_s	*prev, *next;
	think_t		function;
} thinker_t;

struct player_s;

typedef struct mobj_s
{
/* info for drawing */
	fixed_t			x,y,z;
	struct subsector_s	*subsector;
	struct	mobj_s	*prev, *next;
	latecall_t		latecall;			/* set in p_base if more work needed */
	struct	mobj_s	*snext, *sprev;		/* links in sector (if needed) */
	angle_t			angle;
	VINT			sprite;				/* used to find patch_t and flip value */
	VINT			frame;				/* might be ord with FF_FULLBRIGHT */

/* interaction info */
	struct mobj_s	*bnext, *bprev;		/* links in blocks (if needed) */
	fixed_t			floorz, ceilingz;	/* closest together of contacted secs */
	fixed_t			radius, height;		/* for movement checking */
	fixed_t			momx, momy, momz;	/* momentums */

	mobjtype_t		type;
	mobjinfo_t		*info;				/* &mobjinfo[mobj->type] */
	VINT			tics;				/* state tic counter	 */
	state_t			*state;
	int				flags;
	VINT			health;
	VINT			movedir;		/* 0-7 */
	VINT			movecount;		/* when 0, select a new dir */
	struct mobj_s	*target;		/* thing being chased/attacked (or NULL) */
									/* also the originator for missiles */
	VINT			reactiontime;	/* if non 0, don't attack yet */
									/* used by player to freeze a bit after */
									/* teleporting */
	VINT			threshold;		/* if >0, the target will be chased */
									/* no matter what (even if shot) */
	struct player_s	*player;		/* only valid if type == MT_PLAYER */
	struct mobj_s   *extramobj;     /* for latecall functions */

	short			spawnx, spawny, spawntype,spawnangle;	/* for deathmatch respawning */

    struct mobj_s*	tracer;         /* Thing being chased/attacked for tracers. */
} mobj_t;

/* each sector has a degenmobj_t in it's center for sound origin purposes */
struct subsector_s;
typedef struct
{
	fixed_t			x,y,z;
    struct subsector_s	*subsec;	// Psx Doom New
} degenmobj_t;


/* */
/* frame flags */
/* */
#define	FF_FULLBRIGHT	0x8000		/* flag in thing->frame */
#define FF_FRAMEMASK	0x7fff

/* */
/* mobj flags */
/* */
#define	MF_SPECIAL		1			/* call P_SpecialThing when touched */
#define	MF_SOLID		2
#define	MF_SHOOTABLE	4
#define	MF_NOSECTOR		8			/* don't use the sector links */
									/* (invisible but touchable)  */
#define	MF_NOBLOCKMAP	16			/* don't use the blocklinks  */
									/* (inert but displayable) */
#define	MF_AMBUSH		32
#define	MF_JUSTHIT		64			/* try to attack right back */
#define	MF_JUSTATTACKED	128			/* take at least one step before attacking */
#define	MF_SPAWNCEILING	256			/* hang from ceiling instead of floor */
#define	MF_NOGRAVITY	512			/* don't apply gravity every tic */

/* movement flags */
#define	MF_DROPOFF		0x400		/* allow jumps from high places */
#define	MF_PICKUP		0x800		/* for players to pick up items */
#define	MF_NOCLIP		0x1000		/* player cheat */
#define	MF_SLIDE		0x2000		/* keep info about sliding along walls */
#define	MF_FLOAT		0x4000		/* allow moves to any height, no gravity */
#define	MF_TELEPORT		0x8000		/* don't cross lines or look at heights */
#define MF_MISSILE		0x10000		/* don't hit same species, explode on block */

#define	MF_DROPPED		0x20000		/* dropped by a demon, not level spawned */
#define	MF_SHADOW		0x40000		/* use fuzzy draw (shadow demons / invis) */
#define	MF_NOBLOOD		0x80000		/* don't bleed when shot (use puff) */
#define	MF_CORPSE		0x100000	/* don't stop moving halfway off a step */
#define	MF_INFLOAT		0x200000	/* floating to a height for a move, don't */
									/* auto float to target's height */

#define	MF_COUNTKILL	0x400000	/* count towards intermission kill total */
#define	MF_COUNTITEM	0x800000	/* count towards intermission item total */

#define	MF_SKULLFLY		0x1000000	/* skull in flight */
#define	MF_NOTDMATCH	0x2000000	/* don't spawn in death match (key cards) */

#define	MF_SEETARGET	0x4000000	/* is target visible? */

/* Exclusive Psx Doom Flags */
#define	MF_BLENDMASK1	0x10000000
#define	MF_BLENDMASK2	0x20000000
#define	MF_BLENDMASK3	0x40000000
#define	MF_ALL_BLEND_MASKS  (MF_BLENDMASK1 | MF_BLENDMASK2 | MF_BLENDMASK3)

/*============================================================================= */
typedef enum
{
	PST_LIVE,			/* playing */
	PST_DEAD,			/* dead on the ground */
	PST_REBORN			/* ready to restart */
} playerstate_t;


/* psprites are scaled shapes directly on the view screen */
/* coordinates are given for a 320*200 view screen */
typedef enum
{
	ps_weapon,
	ps_flash,
	NUMPSPRITES
} psprnum_t;

typedef struct
{
	state_t	*state;		/* a NULL state means not active */
	int		tics;
	fixed_t	sx, sy;
} pspdef_t;

typedef enum
{
	it_redcard,
	it_bluecard,
	it_yellowcard,
	it_redskull,
	it_blueskull,
	it_yellowskull,
	NUMCARDS
} card_t;

typedef enum
{
	wp_fist,
	wp_pistol,
	wp_shotgun,
	wp_supershotgun,//psx
	wp_chaingun,
	wp_missile,
	wp_plasma,
	wp_bfg,
	wp_chainsaw,
	NUMWEAPONS,
	wp_nochange
} weapontype_t;

typedef enum
{
	am_clip,		/* pistol / chaingun */
	am_shell,		/* shotgun */
	am_cell,		/* BFG */
	am_misl,		/* missile launcher */
	NUMAMMO,
	am_noammo		/* chainsaw / fist */
} ammotype_t;


typedef struct
{
	ammotype_t	ammo;
	int			upstate;
	int			downstate;
	int			readystate;
	int			atkstate;
	int			flashstate;
} weaponinfo_t;

extern	weaponinfo_t	weaponinfo[NUMWEAPONS];//80066f24

typedef enum
{
	pw_invulnerability,
	pw_strength,
	pw_invisibility,
	pw_ironfeet,
	pw_allmap,
	pw_infrared,
	NUMPOWERS
} powertype_t;

#define	INVULNTICS		(30*15)
#define	INVISTICS		(60*15)
#define	INFRATICS		(120*15)
#define	IRONTICS		(60*15)

/*
================
=
= player_t
=
================
*/

typedef struct player_s
{
	mobj_t		*mo;
	playerstate_t	playerstate;

	fixed_t		forwardmove, sidemove;	/* built from ticbuttons */
	angle_t		angleturn;				/* built from ticbuttons */

	fixed_t		viewz;					/* focal origin above r.z */
	fixed_t		viewheight;				/* base height above floor for viewz */
	fixed_t		deltaviewheight;		/* squat speed */
	fixed_t		bob;					/* bounded/scaled total momentum */

	int			health;					/* only used between levels, mo->health */
										/* is used during levels	 */
	int			armorpoints, armortype;	/* armor type is 0-2 */

	int			powers[NUMPOWERS];		/* invinc and invis are tic counters	 */
	boolean		cards[NUMCARDS];
	boolean		backpack;
	int			frags;					/* kills of other player */
	int			fragpad;	/* don't mess up offsets for asm code... */
	weapontype_t	readyweapon;
	weapontype_t	pendingweapon;		/* wp_nochange if not changing */
	boolean		weaponowned[NUMWEAPONS];
	int			ammo[NUMAMMO];
	int			maxammo[NUMAMMO];
	int			attackdown, usedown;	/* true if button down last tic */
	int			cheats;					/* bit flags */

	int			refire;					/* refired shots are less accurate */

	int			killcount, itemcount, secretcount;		/* for intermission */
	char		*message;				/* hint messages */
	int			damagecount, bonuscount;/* for screen flashing */
	mobj_t		*attacker;				/* who did damage (NULL for floors) */
	int			extralight;				/* so gun flashes light up areas */
	//int		fixedcolormap;			/* can be set to REDCOLORMAP, etc */
	//int		colormap;				/* 0-3 for which color to draw player */
	pspdef_t	psprites[NUMPSPRITES];	/* view sprites (gun, etc) */
	boolean		didsecret;				/* true if secret level has been done */
	void		*lastsoundsector;		/* don't flood noise every time */

	int			automapx, automapy, automapscale, automapflags;


	int         mousereactionuse;
	boolean     mouseuse;

	int			turnheld;				/* for accelerative turning */
} player_t;

#define CF_NOCLIP		1 // no use
#define CF_GODMODE		2
#define CF_ALLLINES		4
#define CF_ALLTHINGS	8
#define CF_VRAMVIEWER	16
#define CF_WARPLEVEL	32
#define CF_NONE			64
#define CF_X_RAY		128
#define CF_PAUSE		256

#define	AF_ACTIVE		1				/* automap active */
#define	AF_FOLLOW		2
#define	AF_ALLLINES		4
#define	AF_ALLMOBJ		8

#define	AF_OPTIONSACTIVE	128			/* options screen running */

/*
===============================================================================

					GLOBAL VARIABLES

===============================================================================
*/

/*================================== */

extern	int		ticsinframe;	/* how many tics since last drawer */
extern	int		ticon;
extern	int		frameon;
extern	int		ticbuttons[MAXPLAYERS];
extern	int		oldticbuttons[MAXPLAYERS];

int MiniLoop ( void (*start)(void),  void (*stop)(int)
		,  int (*ticker)(void), void (*drawer)(void) );

int	G_Ticker (void);
void G_Drawer (void);
void G_RunGame (void);

/*================================== */


extern	gameaction_t	gameaction;

#define	SBARHEIGHT	32			/* status bar height at bottom of screen */

typedef enum
{
	gt_single,
	gt_coop,
	gt_deathmatch
} gametype_t;

extern	gametype_t	netgame;

extern	boolean		playeringame[MAXPLAYERS];
extern	int			consoleplayer;		/* player taking events and displaying */
extern	int			displayplayer;
extern	player_t	players[MAXPLAYERS];

extern	boolean     rendersky;//8007801C


extern	skill_t		gameskill;
extern	int			gamemap;
extern	int			nextmap;
extern	int			totalkills, totalitems, totalsecret;	/* for intermission *///80077d4c,80077d58,80077E18

extern 	int 		gametic;

extern	mapthing_t	deathmatchstarts[10], *deathmatch_p;    //80097e4c,80077e8c
extern	mapthing_t	playerstarts[MAXPLAYERS];//800a8c60

/*
===============================================================================

					GLOBAL FUNCTIONS

===============================================================================
*/

fixed_t	FixedMul (fixed_t a, fixed_t b);
fixed_t	FixedDiv (fixed_t a, fixed_t b);

#ifndef __BIG_ENDIAN__
#define __BIG_ENDIAN__
#endif

#ifdef __BIG_ENDIAN__

#define	BIGSHORT(x) (x)
#define	BIGLONG(x) (x)
/*define	LITTLESHORT(x) ShortSwap(x) */
//#define	LITTLESHORT(x) (short)((((x)&255)<<8)+(((x)>>8)&255))
//#define	LITTLELONG(x) LongSwap(x)

#define	LITTLESHORT(x) (x)
#define	LITTLELONG(x) (x)

#else

short ShortSwap(short dat)
{
   return (((unsigned short)dat<<8) + ((unsigned short)dat>>8))&0xffff;
}

long LongSwap(long dat)
{
   unsigned    a,b,c,d;

   a = (dat>>24)&0xff;
   b = (dat>>16)&0xff;
   c = (dat>>8)&0xff;
   d = dat&0xff;
   return (d<<24)+(c<<16)+(b<<8)+a;
}

#define	BIGSHORT(x) ShortSwap(x)
#define	BIGLONG(x) LongSwap(x)
#define	LITTLESHORT(x) (x)
#define	LITTLELONG(x) (x)

#endif

/*----------- */
/*MEMORY ZONE */
/*----------- */
/* tags < 16 are not overwritten until freed */
#define	PU_STATIC		1			/* static entire execution time */
#define	PU_LEVEL		2			/* static until level exited */
#define	PU_LEVSPEC		4			/* a special thinker in a level */
#define	PU_ANIMATION	8			/* psx doom */
/* tags >= 16 are purgable whenever needed */
#define	PU_PURGELEVEL	16
#define	PU_CACHE		32

#define	ZONEID	0x1d4a

typedef struct memblock_s
{
	int		size;           /* including the header and possibly tiny fragments */
	void    **user;         /* NULL if a free block */
	short   tag;            /* purgelevel */
	short   id;             /* should be ZONEID */
	int		lockframe;		/* don't purge on the same frame */
	struct memblock_s   *next;
	struct memblock_s	*prev;
} memblock_t;

typedef struct
{
	int		size;				/* total bytes malloced, including header */
	memblock_t	*rover;
	memblock_t	blocklist;		/* start / end cap for linked list */
} memzone_t;

//extern int framecount;

extern	memzone_t	*mainzone;
//extern	memzone_t	*refzone;

void	Z_Init (void);
memzone_t *Z_InitZone (byte *base, int size);

void 	*Z_Malloc2 (memzone_t *mainzone, int size, int tag, void *ptr);
void	*Z_Alloc2(memzone_t *mainzone, int size, int tag, void *user);//psxdoom
inline void Z_Free2 (memzone_t *mainzone,void *ptr);

#define Z_Malloc(x,y,z) Z_Malloc2(mainzone,x,y,z)
#define Z_Alloc(x,y,z) Z_Alloc2(mainzone,x,y,z)
#define Z_Free(x) Z_Free2(mainzone,x)

void	Z_FreeTags(memzone_t *mainzone, int tag);
void	Z_CheckHeap (memzone_t *mainzone);
void	Z_ChangeTag (void *ptr, int tag);
int 	Z_FreeMemory (memzone_t *mainzone);
void    Z_DumpHeap(memzone_t *mainzone);

/*------- */
/*WADFILE */
/*------- */
typedef struct
{
	int			filepos;					/* also texture_t * for comp lumps */
	int			size;
	char		name[8];
} lumpinfo_t;

typedef struct {
    void       *cache;
} lumpcache_t;

extern	int			wadfilenum;

extern	lumpinfo_t	*lumpinfo;		/* points directly to rom image */
extern	int			numlumps;
extern	lumpcache_t	*lumpcache;
extern	byte		*lumpencode;	// psxdoom
extern	boolean		disableload;	// psxdoom
extern	byte		*mapfileptr;	// psxdoom
extern	int			mapnumlumps;	// psxdoom
extern	lumpinfo_t  *maplump;		// psxdoom

void	W_Init (void);

int		W_CheckNumForName (char *name);
int		W_GetNumForName (char *name);

int		W_LumpLength (int lump);
void	W_ReadLump (int lump, void *dest, boolean decodelump);//psxdoom

void	*W_CacheLumpNum (int lump, int tag, boolean decodelump);//psxdoom
void	*W_CacheLumpName (char *name, int tag, boolean decodelump);//psxdoom

byte	*W_OpenMapWad(char *mapname);//psxdoom
int		W_MapLumpLength(int lump);//psxdoom
int		W_MapGetNumForName(char *name);//psxdoom
void	W_ReadMapLump(int lump, void *dest, int decodelump);//psxdoom

void	decode(unsigned char *input, unsigned char *output);//psxdoom
int		decodedsize(unsigned char *input);//psxdoom

/*------- */
/*PSX FILE */
/*------- */
void	ClearFiles(void);//psxdoom
int		OpenFile(char *filename);//psxdoom
void	CloseFile(int file_num);//psxdoom
int     SeekFile(int file_num, int seekpos, int seekmode);//psxdoom
void	ReadFile(int file_num, void *destptr, unsigned int readbytes);//psxdoom

#define W_POINTLUMPNUM(x) (void*)(wadfileptr+BIGLONG(lumpinfo[x].filepos));

/*---------- */
/*BASE LEVEL */
/*---------- */
void D_DoomMain (void);
void D_DoomLoop (void);

extern	boolean	demoplayback, demorecording;
extern	int		*demo_p, *demobuffer;

extern	skill_t		startskill;
extern	int			startmap;
extern	gametype_t	starttype;

/*--------- */
/*SYSTEM IO */
/*--------- */
#define	SCREENWIDTH		256
#define	SCREENHEIGHT	240

/*---- */
/*GAME */
/*---- */

void G_DeathMatchSpawnPlayer (int playernum);
void G_InitNew (skill_t skill, int map, gametype_t gametype);
void G_CompleteLevel (void);
void G_RecordDemo (void);
int G_PlayDemoPtr (void);//(int *demo);

/*----- */
/*PLAY */
/*----- */

void P_SetupLevel (int map, skill_t skill);
void P_Init (void);

void P_Start (void);
void P_Stop (int exit);
int P_Ticker (void);
void P_Drawer (void);

void IN_Start (void);
void IN_Stop (int exit);
int IN_Ticker (void);
void IN_Drawer (void);


//m_main.c
typedef enum
{
	gamemode,
	level,
	difficulty,
	options,
	NUMMENUITEMS
} menu_t;

//Skull Graphic On StatusPic
#define	M_SKULL_W  16
#define	M_SKULL_H  18
#define	M_SKULL_VX  132
#define	M_SKULL_VY  192

extern int cursorframe;//80078000 00000bf0
extern int cursorpos[MAXPLAYERS];//80077E2C uGp00000a1c,
extern int m_vframe1[MAXPLAYERS]; //80077D24 uGp00000914
extern psxobj_t backpic;//0x800977f0
extern psxobj_t doompic;//0x80097830
extern psxobj_t connectpic;//0x800978F0

int RunMenu(void);
void M_Start (void);
void M_Stop (int exit);
int M_Ticker (void);
void M_Drawer (void);
void M_CrossFadeWipe(void);

//f_main.c
void END1_Start (void);
void END1_Stop(int exit);
int END1_Ticker(void);
void END1_Drawer(void);

void Cast_Start(void);
void Cast_Stop(int exit);
int Cast_Ticker(void);
void Cast_Drawer(void);
/*void F_Start (void);
void F_Stop (void);
int F_Ticker (void);
void F_Drawer (void);*/

void AM_Control (player_t *player);
void AM_Drawer (void);
void AM_Start (void);

/*----- */
/*OPTIONS */
/*----- */

void O_Start (void);
void O_Stop (int exit);
int O_Ticker (void);
void O_Drawer (void);

/*----- */
/*PASSWORD */
/*----- */

void PW_Start(void);
void PW_Stop(int exit);
int PW_Ticker(void);
void PW_Drawer(void);
void Encode_Password(byte *buff);
int Decode_Password(byte *inbuff, int *levelnum, int *skill, player_t *player);

/*----- */
/*CONFIGURATION */
/*----- */

void CF_Start (void);
void CF_Stop (int exit);
int CF_Ticker (void);
void CF_Drawer (void);

/*----- */
/*MOUSE CONFIGURATION */
/*----- */
void CFM_Start (void);
void CFM_Stop (int exit);
int CFM_Ticker (void);
void CFM_Drawer (void);
int Get_PadButtons(int *buttons);

/*----- */
/*STATUS */
/*----- */

extern psxobj_t statuspic;

void ST_Init (void);
void ST_Ticker (void);
void ST_Drawer (void);
void ST_InitEveryLevel(void);

/*------- */
/*REFRESH */
/*------- */

void R_RenderPlayerView (void);
void R_Init (void);
int	R_FlatNumForName (char *name);
int	R_TextureNumForName (char *name);
int	R_CheckTextureNumForName (char *name);
angle_t R_PointToAngle2 (fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2);
struct subsector_s *R_PointInSubsector (fixed_t x, fixed_t y);

/*---- */
/*MISC */
/*---- */
extern unsigned char rndtable[256];
int M_Random (void);
int P_Random (void);
void M_ClearRandom (void);
void M_ClearBox (fixed_t *box);
void M_AddToBox (fixed_t *box, fixed_t x, fixed_t y);


/* header generated by Dave's sound utility */
#include "sounds.h"

extern	boolean		gamepaused;

extern	int		maxlevel;			/* highest level selectable in menu (1-25) */

extern	int		gamevbls;			/* may not really be vbls in multiplayer */
extern	int		vblsinframe[MAXPLAYERS];		/* range from 4 to 8 */

/*----- */
/*PSX Doom */
/*----- */

/* CONTROL PAD */
#define PAD_UP			4096    //(1<<12)
#define PAD_DOWN		16384   //(1<<14)
#define PAD_LEFT		32768   //(1<<15)
#define PAD_RIGHT		8192    //(1<<13)
#define PAD_TRIANGLE	16      //(1<< 4)
#define PAD_CROSS		64      //(1<< 6)
#define PAD_SQUARE		128     //(1<< 7)
#define PAD_CIRCLE		32      //(1<< 5)
#define PAD_L1			4       //(1<< 2)
#define PAD_L2			1       //(1<< 0)
#define PAD_R1			8       //(1<< 3)
#define PAD_R2			2       //(1<< 1)
#define PAD_START		2048    //(1<<11)
#define PAD_SELECT		256     //(1<< 8)
#define PAD_LR			(PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2)//15
#define PAD_ARROWS		(PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)//61440
#define PAD_ACTION		(PAD_TRIANGLE | PAD_CIRCLE | PAD_CROSS | PAD_SQUARE)//240
#define PAD_ALL			(PAD_ARROWS | PAD_START | PAD_SELECT | PAD_ACTION | PAD_LR)//63999

//MOUSE PAD
//#define MOUSE_LEFT		(1<<3)//8
//#define MOUSE_RIGHT		(1<<2)//4
#define MOUSE_LEFT		1024    //(1<<10)
#define MOUSE_RIGHT		512     //(1<< 9)

typedef struct
{
	unsigned int BT_ATTACK;			//*
	unsigned int BT_USE;			//*4
	unsigned int BT_STRAFE;			//*8
	unsigned int BT_SPEED;			//*12
	unsigned int BT_STRAFELEFT;		//*16
	unsigned int BT_STRAFERIGHT;	//*20
	unsigned int BT_WEAPONBACKWARD;	//*24
	unsigned int BT_WEAPONFORWARD;	//*28

	unsigned int BT_MOUSELEFT;	    //*32
	unsigned int BT_MOUSERIGHT;	    //*36
} buttons_t;

extern buttons_t *BT_DATA[MAXPLAYERS];//80077DF4, 80077DF8

//NEW FINAL DOOM
extern int M_SENSITIVITY[MAXPLAYERS];   //80078358, 8007835c
extern int m_sensitivity;               //80077FB4|iGp00000664
extern int m_leftbutton;                //80077FB8|iGp00000668
extern int m_rightbutton;               //80077FBC|iGp0000066c

/* psxmain.c */
#define MAX_VRAMMEM				256     // # of entries in manager cache
#define MAX_DYNAMIC_TPAGE		11      // max # of tpages supported for dynamic memory
#define MIN_VRAM_ALLOC_SIZE		16		// each tpage is divided into this many number of squares
#define MIN_VRAM_ALLOC_SHIFT	4		// shift to simulate the divide of (MIN_VRAM_ALLOC_SIZE)
#define VRAMSIZE (sizeof(int) * MAX_DYNAMIC_TPAGE * MAX_VRAMMEM)

extern int PageCount;
extern int TextureCacheIdx;
extern int xycount;
extern int xcount;
extern int ycount;
extern int V_PagFlags;

extern DRAWENV	draw[2];				/* draw environment */      //800A8E90, 800A8EEC
extern DISPENV disp[2];					/* display environment*/    //800a8f48, 800A8F5C
extern long drawside;
extern int	drawsync1;//80077FE4
extern int	drawsync2;//80077F3C

#define MAX_PAD 34
extern char    buff_1[MAX_PAD], buff_2[MAX_PAD];   //80099050, 80099074
extern signed char   *PAD_Rbuf1, *PAD_Rbuf2;       //puGp00000c40, puGp00000c44

void I_Error(char *error, ...);
unsigned int I_PadRead(void);// New Final Doom
void ImageToVram(psxobj_t *pic, char *name, int lump);
void DrawStaticImage(psxobj_t *psxobj, int xpos, int ypos, int pal);
void DrawImage(int vtpage, int pal, int xpos, int ypos,  char vramx, char vramy, int width, int height);
void P_LoadingPlaque(psxobj_t *psxobj, int xpos, int ypos, int pal);
void NextTextureCacheIdx(void);
void DrawRender(void);
void Add_vsync(void);
void Init_Vram_Cache(void);
void TextureCache (psxobj_t *psxobj);
void V_ClearBlock(psxobj_t *psxobj);
void Valloc_Init(void);
void Vram_Viewer(int page);

extern boolean cancel_link;
extern unsigned int TempConfiguration[8];
extern unsigned int DefaultConfiguration[8];
extern unsigned int ActualConfiguration[10];
extern unsigned int NewConfiguration[10];

void Link_Conection(void);
boolean Update_Conection(void);
void Sync_Data_Transmission(void);
void Sync_Read_Write (void);
void UpdateDrawOTag(void);
unsigned int Get_CfgCode(unsigned int *cfgdata);
unsigned int *Get_CfgByCode(unsigned int cfgcode);

/* extras */
//void W_AddPrim (void* prim, unsigned long* addr0, unsigned long* addr1);//OLD VERSION
void W_AddPrim (void* prim);
void TestRender(void);

int RunLegal(void);
int RunTitle(void);
int RunDemo(char *demoname);
int RunCredits(void);

/* l_main.c */
extern int y_scroll;//80077FB8 uGp00000ba8
extern int last_ticon;//80077D38 iGp00000928
extern psxobj_t legalspic;

void L_Start(void);
void L_Stop(int exit);
int L_Ticker(void);
void L_Draw(void);

/* c_main.c */
void C_Start(void);
void C_Stop(int exit);
int C_Ticker(void);
void C_Draw(void);

/* t_main.c */
extern psxobj_t loadingpic;//0x80097870
extern psxobj_t marb01pic;//0x80097890
extern psxobj_t buttonspic;//0x800978B0
extern psxobj_t neterrpic; //0x800978d0
extern psxobj_t pausepic;//0x80097850
extern psxobj_t titlepic;//0x80097810

void T_Start(void);
void T_Stop(int exit);
int T_Ticker(void);
void T_Draw(void);

/* Enum for a CD music piece and also an index into the 'CD_Track' array to get an actual track number */
enum cdmusic_t {
    cdmusic_title_screen,
    cdmusic_main_menu,
    cdmusic_credits_demo,
    cdmusic_intermission,
    cdmusic_club_doom,
    cdmusic_finale_final_doom,
    NUM_CD_MUSIC_TRACKS
};

extern int CD_TRACK[NUM_CD_MUSIC_TRACKS];//80073C7C

void S_SetSoundVolume (int volume);
void S_SetMusicVolume(int volume);
void S_StopMusic(void);
void S_StartMusic(void);
void S_InitBlock(SampleBlock *sampblk);
void S_DoBlockClear(SampleBlock *sampblk);
void S_Lcd_Load(int map_indx);
void S_Pause(void);
void S_Resume(void);
void S_StopSound(unsigned long sequence_type);
void S_StopAll(void);
void S_AdjustSoundParams(mobj_t *origin, int sound_id, TriggerPlayAttr *attr);
void S_StartSound(mobj_t *origin, int sound_id);
void S_UpdateSounds(void);
void PsxSoundInit(int sfx_volume, int mus_volume, void *data);
void PsxSoundExit(void);

extern int SfxVolume;   /* range from 0 to 100 */       //80077420
extern int MusVolume;	/* range from 0 to 100 */       //80077424
extern int CDVolume;	/* range from 0 to 0x3CFF */    //80077428