/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Mononoki:size=12" };
static const char dmenufont[]       = "Mononoki:size=12";
static const char col_gray1[]       = "#21242B";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#BBC2CF";
static const char col_gray4[]       = "#1B2229";
static const char col_cyan[]        = "#51AFEF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "", "", "", "" , "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
	{ "Brave-browser",  NULL,       NULL,       1 << 4,       0,           -1,        50,50,800,500,        0 },
	{ "Spotify",  NULL,       NULL,       1 << 5,       0,           0,        50,50,800,500,        0 },
	{ "Emacs",  NULL,       NULL,       1 << 6,       0,           -1,        50,50,800,500,        0 },
	{ "Mumble",  NULL,       NULL,       1 << 7,       0,           0,        50,50,800,500,        0 },
	{ "Signal",  NULL,       NULL,       1 << 7,       0,           0,        50,50,800,500,        0 },
	{ "Element",  NULL,       NULL,       1 << 7,       0,           0,        50,50,800,500,        0 },
	{ "discord",  NULL,       NULL,       1 << 7,       0,           0,        50,50,800,500,        0 },
	{ "thunderbird",  NULL,       NULL,       1 << 7,       0,           -1,        50,50,800,500,        0 },
	{ NULL,  NULL,       "Spectr",       1 << 8,       1,           0,        50,50,800,500,        0 },
	{ NULL,  NULL,       "Phase/Frequency Wheel",       1 << 8,       1,           0,      885,50,500,500,        0 },
	{ NULL,  NULL,       "EBU R128 Meter",       1 << 8,       1,           0,        1450,50,500,500,        0 },
	{ NULL,  NULL,       "DR-14 - Crest Factor Loudness Range Meter",       1 << 8,       1,           0,        50,600,215,396,        0 },
	{ "Hdspmixer",  NULL,       NULL,       1 << 8,       1,           -1,        600,1600,1000,1000,        0 },
	{ "org.remmina.Remmina",  NULL,       NULL,       1 << 9,       0,           -1,        50,50,800,500,        0 },
	{ "obs",  NULL,       NULL,       1 << 9,       0,           0,        50,50,800,500,        0 },
};
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *vifmcmd[]    = { "st", "-e", "vifm", NULL };
static const char *screenshotcmd[]    = { "/usr/bin/flameshot", "gui", NULL };
static const char *colorpickercmd[]	= { "/home/niklas/.local/bin/colorpicker.sh", NULL };
static const char *emoji_dmenucmd[]	= { "/home/niklas/.local/bin/emojenu", NULL };
/* static const char *vimcmd[]	= { "st", "-e", "nvim", NULL }; 
static const char *scimcmd[]	= { "st", "-e", "sc-im", NULL }; wie gesagt -> quicklauncher */

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = colorpickercmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emoji_dmenucmd } },
	/* { MODKEY,                       XK_v,      spawn,          {.v = vimcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = scimcmd } },  stattdessen lieber quicklauncher dmenu script und automatisches enter im dmenu :D */
	{ MODKEY,	             XK_t, spawn,          {.v = termcmd } },
	{ MODKEY,       	      XK_x, spawn,          {.v = vifmcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
/*	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, ebenso useless :D*/
	{ MODKEY,	                XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
/*	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, ruf zurück, wenn ich jemals layouts durchcyclen will :D*/
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	/*{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, scary :D */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	/* { MODKEY|ShiftMask,             XK_q,      quit,           {0} }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

