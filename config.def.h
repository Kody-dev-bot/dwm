/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=18" };
static const char col_bg[]       = "#121212";    // 极暗的背景色
static const char col_fg[]       = "#b3b3b3";    // 柔和的前景色
static const char col_sel_fg[]   = "#121212";    // 选中项前景色（与背景色对比）
static const char col_sel_bg[]   = "#e6b800";    // 暖黄色作为强调色
static const char col_hid_fg[]   = "#595959";    // 隐藏窗口的前景色
static const char col_hid_bg[]   = "#0d0d0d";    // 隐藏窗口的背景色
static const char col_urg_fg[]   = "#ff4d4d";    // 紧急提示色
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_fg, col_bg, col_hid_fg },
    [SchemeSel]  = { col_sel_fg, col_sel_bg, col_sel_bg },
    [SchemeHid]  = { col_hid_fg, col_hid_bg, col_hid_fg },
    [SchemeStatus]  = { col_fg, col_bg,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { col_sel_fg, col_sel_bg,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_fg, col_bg,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_sel_fg, col_sel_bg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_fg, col_bg,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
  "fcitx5", NULL,
  "picom", NULL,
  "/usr/local/bin/slstatus", NULL,
  "/usr/local/bin/wallpaper", "loop", NULL,
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *screenshotcmd[] = { "flameshot", "gui", NULL };

static const char *setupwallpaper[] = { "wallpaper", "setup", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                     XK_p,                    spawn,            {.v = dmenucmd } },
  { MODKEY,                     XK_Return,               spawn,            {.v = termcmd } },
  { MODKEY,                     XK_a,                    spawn,            {.v = screenshotcmd} },
  { MODKEY,                     XK_r,                    spawn,            {.v = setupwallpaper} },
  { MODKEY,                     XK_apostrophe,           togglescratch,    {.v = scratchpadcmd } },
  { MODKEY,                     XK_j,                    focusstackvis,    {.i = +1 } },
  { MODKEY,                     XK_k,                    focusstackvis,    {.i = -1 } },
  { MODKEY,                     XK_i,                    incnmaster,       {.i = +1 } },
  { MODKEY,                     XK_d,                    incnmaster,       {.i = -1 } },
  { MODKEY,                     XK_t,                    setlayout,        {.v = &layouts[0]} },
  { MODKEY,                     XK_f,                    setlayout,        {.v = &layouts[1]} },
  { MODKEY,                     XK_m,                    setlayout,        {.v = &layouts[2]} },
  { MODKEY,                     XK_0,                    view,             {.ui = ~0 } },
  { MODKEY,                     XK_comma,                focusmon,         {.i = -1 } },
  { MODKEY,                     XK_period,               focusmon,         {.i = +1 } },
  { MODKEY,                     XK_minus,                setgaps,          {.i = -1 } },
  { MODKEY,                     XK_equal,                setgaps,          {.i = +1 } },
  { MODKEY,                     XK_Tab,                  view,             {0} },
  { MODKEY,                     XK_b,                    togglebar,        {0} },
  { MODKEY,                     XK_s,                    show,             {0} },
  { MODKEY,                     XK_h,                    hide,             {0} },
  { MODKEY,                     XK_Tab,                  view,             {0} },
  { MODKEY,                     XK_space,                setlayout,        {0} },

  { MODKEY|ShiftMask,           XK_0,                    tag,              {.ui = ~0 } },
  { MODKEY|ShiftMask,           XK_comma,                tagmon,           {.i = -1 } },
  { MODKEY|ShiftMask,           XK_period,               tagmon,           {.i = +1 } },
  { MODKEY|ShiftMask,           XK_equal,                setgaps,          {.i = 0  } },
  { MODKEY|ShiftMask,           XK_j,                    focusstackhid,    {.i = +1 } },
  { MODKEY|ShiftMask,           XK_k,                    focusstackhid,    {.i = -1 } },
  { MODKEY|ShiftMask,           XK_h,                    setmfact,         {.f = -0.05} },
  { MODKEY|ShiftMask,           XK_l,                    setmfact,         {.f = +0.05} },
  { MODKEY|ShiftMask,           XK_Return,               zoom,             {0} },
  { MODKEY|ShiftMask,           XK_q,                    killclient,       {0} },
  { MODKEY|ShiftMask,           XK_space,                togglefloating,   {0} },
  { MODKEY|ShiftMask,           XK_c,                    quit,             {0} },
  { MODKEY|ShiftMask,           XK_f,                    fullscreen,       {0} },
  { MODKEY|ShiftMask,           XK_s,                    showall,          {0} },

  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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
