/* Author: Rafael Cavalcanti <https://rafaelc.org/dev>
 * Based on dwm original configuration. */

/* See LICENSE file for copyright and license details. */

/* For multimedia keys */
#include <X11/XF86keysym.h>

/* For extra mouse buttons */
#define Button6 6
#define Button7 7
#define Button8 8
#define Button9 9

/* general appearance */
static unsigned int borderpx = 1;  /* border pixel of windows */
static unsigned int snap = 32;  /* snap pixel */
static char font[] = "Ubuntu Nerd Font:size=10";
static char dmenufont[] = "Ubuntu Nerd Font:size=10";
static const char *fonts[] = { font };

/* bar */
static int showbar = 1;   /* 0 means no bar */
static int topbar = 1;   /* 0 means bottom bar */
static const int user_bh = 20;  /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

/* systray */
static const unsigned int systraypinning = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray = 1;  /* 0 means no systray */
static const unsigned int systrayiconsize = 16; /* systray icon size in px */

/* gaps */
static const unsigned int gappih = 9;  /* horiz inner gap between windows */
static const unsigned int gappiv = 9;  /* vert inner gap between windows */
static const unsigned int gappoh = 9;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 9;  /* vert outer gap between windows and screen edge */
static int smartgaps = 0;  /* 1 means no outer gap when there is only one window */
#if !PERTAG_PATCH
static int enablegaps = 1;
#endif // PERTAG_PATCH

/* colorscheme */
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1:www", "2:ter", "3:not", "4:etc", "5:etc", "6:etc", "7:vir", "8:sur", "9:mus" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title                    tags mask  isfloating  issticky  monitor */

	/* Tags */
	{ "Brave-browser",         "brave-browser", NULL,              1 << 0,    0,          0,        -1 },
	{ "st-256color",           "st-256color", NULL,                1 << 1,    0,          0,        -1 },
	{ "st-256color",           "tmux",    NULL,                    1 << 1,    0,          0,        -1 },
	{ "Code",                  NULL,      NULL,                    1 << 1,    0,          0,        -1 },
	{ "obsidian",              NULL,      NULL,                    1 << 2,    0,          0,        -1 },
	{ "Soffice",               NULL,      NULL,                    1 << 3,    0,          0,        -1 },
	{ "thunderbird",           NULL,      NULL,                    1 << 5,    0,          0,        -1 },
	{ "Virt-manager",          NULL,      NULL,                    1 << 6,    0,          0,        -1 },
	{ "Virt-viewer",           NULL,      NULL,                    1 << 6,    0,          0,        -1 },
	{ "firefox",               NULL,      NULL,                    1 << 7,    0,          0,        -1 },
	{ "Chromium",              "chromium", NULL,                   1 << 7,    0,          0,        -1 },
	{ "Microsoft-edge",        NULL,      NULL,                    1 << 7,    0,          0,        -1 },
	{ NULL,                    "cmus",    NULL,                    1 << 8,    0,          0,        -1 },
	{ "feishin",               "feishin",    NULL,                    1 << 8,    0,          0,        -1 },
	{ "Spotify",               NULL,      NULL,                    1 << 8,    0,          0,        -1 },

	/* Floating */
	{ "gnome-calculator",      NULL,      NULL,                    0,         1,          0,        -1 },
	{ "org.gnome.clocks",      NULL,      NULL,                    0,         1,          0,        -1 },
	{ "Pavucontrol",           NULL,      NULL,                    0,         1,          0,        -1 },
	{ "Blueman-manager",       NULL,      NULL,                    0,         1,          0,        -1 },
	{ "Nm-connection-editor",  NULL,      NULL,                    0,         1,          0,        -1 },
	{ "flameshot",             NULL,      NULL,                    0,         1,          0,        -1 },
	{ "Nemo",                  NULL,      NULL,                    0,         1,          0,        -1 },

	/* Floating and sticky */
	/* Float works oob. We set as sticky so it is placed on bottom right. */
	{ "Galendae",              NULL,      NULL,                    0,         1,          1,        -1 },
	{ "mpv",                   NULL,      NULL,                    0,         1,          1,        -1 },
	{ NULL,                    NULL,      "Picture in picture",    0,         1,          1,        -1 },
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;  /* number of clients in master area */
static int resizehints = 1;  /* 1 means respect size hints in tiled resizals */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* first entry is default */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",        tile },
	{ "M",        monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D",        deck },
	{ "B",        bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "f",        NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,   ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,   ACTION##stack, {.i = INC(-1) } }, \
	//{ MOD, XK_g,     ACTION##stack, {.i = 0 } }, \
	//{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	//{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	//{ MOD, XK_x,     ACTION##stack, {.i = -1 } },
	//{ MOD, XK_q,     ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* [> component of dmenucmd, manipulated in spawn() <] */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };

/* multimedia commands */
static const char *vol_up[] =       { "volume", "up", NULL };
static const char *vol_down[] =     { "volume", "down", NULL };
static const char *vol_mute[] =     { "volume", "mute", NULL };
static const char *player_prev[] =  { "/bin/sh", "-c", "playerctl previous && sleep 0.5 && dwm-status", NULL };
static const char *player_next[] =  { "/bin/sh", "-c", "playerctl next && sleep 0.5 && dwm-status", NULL };
static const char *player_pause[] = { "/bin/sh", "-c", "playerctl play-pause && sleep 0.5 && dwm-status", NULL };
static const char *player_stop[] =  { "/bin/sh", "-c", "playerctl stop && sleep 0.5 && dwm-status", NULL };
static const char *player_ff[] =    { "/bin/sh", "-c", "playerctl position 10+", NULL };
static const char *player_rw[] =    { "/bin/sh", "-c", "playerctl position 10-", NULL };
static const char *player_shift[] = { "/bin/sh", "-c", "playerctld shift && dwm-status", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "font",               STRING,  &font },
	{ "dmenufont",          STRING,  &dmenufont },
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",           INTEGER, &borderpx },
	{ "snap",               INTEGER, &snap },
	{ "showbar",            INTEGER, &showbar },
	{ "topbar",             INTEGER, &topbar },
	{ "nmaster",            INTEGER, &nmaster },
	{ "resizehints",        INTEGER, &resizehints },
	{ "enablegaps",         INTEGER, &enablegaps },
	{ "smartgaps",          INTEGER, &smartgaps },
	{ "mfact",              FLOAT,   &mfact },
	{ "showsystray",        INTEGER, &showsystray },
};

static Key keys[] = {
	/* modifier                     key                      function        argument */
	STACKKEYS(MODKEY,                                        focus)
	STACKKEYS(MODKEY|ShiftMask,                              push)
	{ MODKEY|ShiftMask,             XK_b,                    togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_c,                    spawn,          SHCMD("galendae") },
	{ MODKEY,                       XK_bracketright,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_z,                    zoom,           {0} },
	{ MODKEY,                       XK_z,                    view,           {0} },
	{ MODKEY,                       XK_q,                    killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_l,                    cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_x,                    togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_y,                    togglesystray,  {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,                  viewnext,       {0} },
	{ MODKEY|ShiftMask,             XK_Tab,                  viewprev,       {0} },
	//{ MODKEY|ShiftMask,             XK_Right,                tagtonext,      {0} },
	//{ MODKEY|ShiftMask,             XK_Left,                 tagtoprev,      {0} },

	/* Layouts */
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} }, // tiling
	{ MODKEY|ShiftMask,             XK_t,                    setlayout,      {.v = &layouts[5]} }, // bstack
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY|ShiftMask,             XK_m,                    setlayout,      {.v = &layouts[4]} }, // deck

	/* Gaps */
	{ MODKEY,                       XK_equal,                incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,                incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,                defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_minus,                togglegaps,     {0} },
	//{ MODKEY|Mod4Mask,              XK_i,                    incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_i,                    incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_o,                    incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_o,                    incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,                    incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,                    incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,                    incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,                    incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,                    incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,                    incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,                    incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,                    incrovgaps,     {.i = -1 } },

	/* multimedia */
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = vol_mute } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = vol_down } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = vol_up } },
	{ 0,                            XF86XK_AudioPrev,        spawn,          {.v = player_prev } },
	{ 0,                            XF86XK_AudioNext,        spawn,          {.v = player_next } },
	{ 0,                            XF86XK_AudioPlay,        spawn,          {.v = player_pause } },
	/* AudioPause is sent by headset buttons besides AudioPlay. */
	{ 0,                            XF86XK_AudioPause,       spawn,          {.v = player_pause } },
	{ 0,                            XF86XK_AudioStop,        spawn,          {.v = player_stop } },
	{ MODKEY,                       XK_comma,                spawn,          {.v = player_prev } },
	{ MODKEY,                       XK_period,               spawn,          {.v = player_next } },
	{ MODKEY,                       XK_semicolon,            spawn,          {.v = player_pause } },
	{ MODKEY|ShiftMask,             XK_comma,                spawn,          {.v = player_rw } },
	{ MODKEY|ShiftMask,             XK_period,               spawn,          {.v = player_ff } },
	{ MODKEY|ShiftMask,             XK_semicolon,            spawn,          {.v = player_shift } },

	/* For x220. */
	/* Brightness: Needed after bios update. */
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,         SHCMD("brightness -time 0 -inc 7") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,         SHCMD("brightness -time 0 -dec 7") },
	{ 0,                            XF86XK_AudioMicMute,      spawn,         SHCMD("pactl -- set-source-mute 1 toggle") },
	{ 0,                            XF86XK_Display,           spawn,         SHCMD("hotplug-monitor cycle") },

	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function           argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,         {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,         {.v = &layouts[1]} },
	//{ ClkWinTitle,          0,              Button1,        zoom,              {0} },
	//{ ClkWinTitle,          0,              Button2,        killclient,        {0} },
	//{ ClkWinTitle,          0,              Button4,        focusstack,        {.i = INC(-1) } },
	//{ ClkWinTitle,          0,              Button5,        focusstack,        {.i = INC(+1) } },
	{ ClkStatusText,        0,              Button1,        spawn,             SHCMD("galendae") },
	{ ClkStatusText,        0,              Button2,        spawn,             {.v = player_shift } },
	{ ClkStatusText,        0,              Button9,        spawn,             {.v = player_next } },
	{ ClkStatusText,        0,              Button8,        spawn,             {.v = player_prev } },
	{ ClkStatusText,        0,              Button3,        spawn,             {.v = player_pause } },
	{ ClkStatusText,        0,              Button4,        spawn,             {.v = vol_up } },
	{ ClkStatusText,        0,              Button5,        spawn,             {.v = vol_down } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,         {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,       {0} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,              {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,        {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,               {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,         {0} },
};
