/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;
    /* gap pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *defaultfonts[]          = {
  "monospace:size=15", /* PP default start index */
};
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *defaultcolors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTabActive]  = { col_gray2, col_gray3,  col_gray2 },
	[SchemeTabInactive]  = { col_gray1, col_gray3,  col_gray1 }
};

/* 1 means attach after the currently active window */
static const int attachbelow = 1;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "st",       NULL,       NULL,       0,            0,           1,         1,        -1,  0},
	{ "svkbd",    NULL,       NULL,       TAGMASK,      1,           1,         0,        -1,  1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

/* Bartabgroups properties */
#define BARTAB_BORDERS 1       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 1  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 1 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 5        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 2      // # rows in tag grid (9 tags, e.g. 3x3)
static void (*bartabmonfns[])(Monitor *) = { monocle, bstack };
static void (*bartabfloatfns[])(Monitor *) = { NULL /* , customlayoutfn */ };

static const Layout ppcyclelayouts[] = {
	/* symbol     arrange function */
	{ "",      bstack },   /* first entry is default */
	{ "",      tile },
	{ "",      monocle },
};


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      bstack },   /* first entry is default */
	{ "",      tile },
	{ "F",        NULL },
	{ "",      monocle },
	{ "DD",       deckdouble},
	{ "D",        deck},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{0, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{0, MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{0, MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
  /* PP */
	{1,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_inputhandler.sh volup_one") },
	{2,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_inputhandler.sh volup_two") },
	{3,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_inputhandler.sh volup_three") },
	{1,  0,  XF86XK_AudioLowerVolume, spawn, SHCMD("sxmo_inputhandler.sh voldown_one") },
	{2,  0,  XF86XK_AudioLowerVolume, spawn, SHCMD("sxmo_inputhandler.sh voldown_two") },
	{3,  0,  XF86XK_AudioLowerVolume, spawn, SHCMD("sxmo_inputhandler.sh voldown_three") },
	//{3,  0,  XF86XK_AudioLowerVolume, killclient, {0} },

	{1,  0,  XF86XK_PowerOff, spawn, SHCMD("sxmo_inputhandler.sh powerbutton_one") },
	{2,  0,  XF86XK_PowerOff, spawn, SHCMD("sxmo_inputhandler.sh powerbutton_two") },
	{3,  0,  XF86XK_PowerOff, spawn, SHCMD("sxmo_inputhandler.sh powerbutton_three") },

	/* Used by scripts via xdotool */
	{0,  MODKEY|ShiftMask,  XK_e, shiftview, {.i = -1} },
	{0,  MODKEY|ShiftMask,  XK_r, shiftview, {.i = +1} },
	{0,  MODKEY,  XK_e, clienttagpush, {.i = -1} },
	{0,  MODKEY,  XK_r, clienttagpush, {.i = +1} },

	/* PBP */
	{ 0, MODKEY,                    XK_p,      spawn,          SHCMD("dmenu_run -c -fn Terminus-14 -l 20") },
	{ 0, MODKEY,                    XK_d,      spawn,          SHCMD("dmenu_run -c -fn Terminus-13 -l 20") },

	{ 0, MODKEY|ShiftMask,          XK_Return, spawn,          SHCMD("st") },
	{ 0, MODKEY,                    XK_b,      togglebar,      {0} },
	{ 0, MODKEY,                    XK_j,      focusstack,     {.i = +1 } },
	{ 0, MODKEY,                    XK_k,      focusstack,     {.i = -1 } },

	{ 0, MODKEY|ShiftMask,          XK_j,      pushdown,    {.i = +1 } },
	{ 0, MODKEY|ShiftMask,          XK_k,      pushup,    {.i = -1 } },

	{ 0, MODKEY,                    XK_x,      inplacerotate,    {.i = +2 } },

	{ 0, 0,                         XF86XK_MonBrightnessUp,  spawn, SHCMD("sxmo_brightness.sh up") },
	{ 0, 0,                         XF86XK_MonBrightnessDown,  spawn, SHCMD("sxmo_brightness.sh down") },
	{ 0, MODKEY|ShiftMask,          XK_Down,      spawn,    SHCMD("sxmo_vol.sh down") },
	{ 0, MODKEY|ShiftMask,          XK_Up,      spawn,    SHCMD("sxmo_vol.sh up") },

	{ 0, MODKEY,                    XK_i,      incnmaster,     {.i = +1 } },
	{ 0, MODKEY,                    XK_o,      incnmaster,     {.i = -1 } },
	{ 0, MODKEY,                    XK_h,      setmfact,       {.f = -0.05} },
	{ 0, MODKEY,                    XK_l,      setmfact,       {.f = +0.05} },
	{ 0, MODKEY,                    XK_Return, zoom,           {0} },
	{ 0, MODKEY,                    XK_Tab,    view,           {0} },
	{ 0, MODKEY|ShiftMask,          XK_c,      killclient,     {0} },
	{ 0, MODKEY|ShiftMask,          XK_q,      killclient,     {0} },

	{ 0, MODKEY|ShiftMask,          XK_q,      killclient,     {0} },

	{ 0, MODKEY,                       XK_semicolon, switchcol,    {0} },

	{ 1, MODKEY,                       XK_s, transfer,    {0} },
	{ 2, MODKEY,                       XK_s, transferall,    {0} },


	/* monocle */
	{ 0, MODKEY,                    XK_m,      setlayout,      {.v = &layouts[3]} },
	/* tile */
	{ 0, MODKEY,                    XK_slash,  setlayout,      {.v = &layouts[1]} },
	/* bstack */
	{ 0, MODKEY|ShiftMask,          XK_slash,  setlayout,      {.v = &layouts[0]} },

	{ 0, MODKEY,                       XK_f,  togglefloating, {0} },
	{ 0, MODKEY|ShiftMask,             XK_f,  unfloatvisible, {0} },

	/* cycle through the layouts in ppcyclelayouts */
	{ 0, MODKEY,                    XK_space,  cyclelayout,    {.i = +1} },

	{ 0, MODKEY|ShiftMask,          XK_space,  togglefloating, {0} },
	{ 0, MODKEY,                    XK_0,      view,           {.ui = ~0 } },
	{ 0, MODKEY|ShiftMask,          XK_0,      tag,            {.ui = ~0 } },

	{ 0, MODKEY,                    XK_comma,  focusmon,       {.i = -1 } },
	{ 0, MODKEY,                    XK_period, focusmon,       {.i = +1 } },
	{ 0, MODKEY|ShiftMask,          XK_comma,  tagmon,         {.i = -1 } },
	{ 0, MODKEY|ShiftMask,          XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

