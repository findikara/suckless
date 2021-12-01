/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 6;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:style=Regular" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=9:style=Regular";
static const char col_bg[]          = "#282C34";
static const char col_fg[]          = "#ABB2BF";
static const char col_acc[]         = "#E5C07B";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_acc,col_acc },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"kitty", "--name", "spt1", NULL};
const char *spcmd2[] = {"kitty", "--name", "spt2", NULL};
const char *spcmd3[] = {"kitty", "--name", "rang", "-e", "ranger", NULL};
const char *spcmd4[] = {"pavucontrol",     NULL};
static Sp scratchpads[] = {
    /* name                cmd  */
    {"spt1",               spcmd1},
    {"spt2",               spcmd2},
    {"rang",               spcmd3},
    {"pavucontrol",        spcmd4},
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,				1,			 -1 },
    { "mpv",         NULL,           NULL,      0,            1,           -1 },
    { NULL,          "spt1",         NULL,      SPTAG(0),     1,           -1 },
    { NULL,          "spt2",         NULL,      SPTAG(1),     1,           -1 },
    { NULL,          "rang",         NULL,      SPTAG(2),     1,           -1 },
    { "Pavucontrol", "pavucontrol",  NULL,      SPTAG(3),     1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "H[]",      deck },
	{ ">M>",      centeredfloatingmaster },
	{ ":::",      gaplessgrid },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ "|M|",      centeredmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define CMD(cmd)   { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TRM(cmd)   { .v = (const char*[]){ "kitty", "-e", cmd, NULL } }/* spawn in terminal */

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "kitty", NULL };


static Key keys[] = {
	/* modifier                     key                  function        argument */
    /* Progs */
	{ MODKEY,                       XK_p,                spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,           spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,                spawn,          SHCMD("brave ") },
	{ MODKEY|ShiftMask,             XK_w,                spawn,          CMD("qutebrowser") },
	{ Mod1Mask,                     XK_w,                spawn,          CMD("dmn_websearch") },
	{ MODKEY,                       XK_e,                spawn,          TRM("ranger") },
	{ MODKEY|ShiftMask,             XK_e,                spawn,          CMD("pcmanfm") },
	{ MODKEY,                       XK_d,                spawn,          CMD("emacsclient -c -a 'emacs'") },
	{ MODKEY|ShiftMask,             XK_d,                spawn,          CMD("libreoffice") },
	{ MODKEY,                       XK_x,                spawn,          CMD("telegram-desktop") },
	{ Mod1Mask,                     XK_space,            spawn,          CMD("dmn_text") },
	{ Mod1Mask|ShiftMask,           XK_space,            spawn,          CMD("dmn_text_add") },
	{ MODKEY,                       XK_F1,               spawn,          CMD("dmn_wifi") },
	{ MODKEY,                       XK_F2,               spawn,          CMD("dmn_confedit") },
	{ MODKEY,                       XK_F3,               spawn,          CMD("dmn_monitors") },

    /* Windows client controls */
	{ MODKEY,                       XK_j,                focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_bracketright,     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Return,           zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_h,                setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,                setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,                setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_k,                setcfact,       {.f = -0.25} },
	{ MODKEY|ControlMask,           XK_space,            setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_space,            togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_j,                incrgaps,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_k,                incrgaps,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_space,            defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,              view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                killclient,     {0} },

    /* Layouts */
	{ MODKEY,                       XK_space,            setlayout,      {0} },
	{ MODKEY,                       XK_z,                setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,                setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,                setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_z,                setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,                setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_g,                setlayout,      {.v = &layouts[5]} },

    /* Monitors */
	{ MODKEY,                       XK_i,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_o,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_o,                tagmon,         {.i = +1 } },
    
    /* Tags */
	TAGKEYS(                        XK_1,                                0)
	TAGKEYS(                        XK_2,                                1)
	TAGKEYS(                        XK_3,                                2)
	TAGKEYS(                        XK_4,                                3)

    /* Scratchpads */
	{ MODKEY,            			XK_grave,            togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_7,	             togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_8,	             togglescratch,  {.ui = 2 } },
	{ MODKEY,            			XK_9,	             togglescratch,  {.ui = 3 } },

    /* DWM Controls */
	{ MODKEY|ShiftMask,             XK_q,                quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,                quit,           {1} }, 

    /* Misc */
	{ MODKEY,                       XK_equal,            togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_f,                togglebar,      {0} },

    /* Layouts
    */

    /* Gap management
	{ MODKEY|Mod1Mask,              XK_i,                incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,                incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,                incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,                incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,                incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,                incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,                incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,                incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,                incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,                incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,                incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,                incrovgaps,     {.i = -1 } },
    */

    /* Misc
	{ MODKEY|ShiftMask,             XK_0,                tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_0,                view,           {.ui = ~0 } },
    */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

    /* click on window */
    { ClkClientWin,     MODKEY,             Button1,        movemouse,      {0} },
    { ClkClientWin,     MODKEY,             Button3,        resizemouse,    {0} },
    { ClkClientWin,     MODKEY|ShiftMask,   Button1,        togglefloating, {0} },

};
