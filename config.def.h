// jgr //
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx       = 4;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 10;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 15;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 15;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 0;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const char ptagf[] = "[%s %s]";          /* format of a tag label */
static const char etagf[] = "[%s]";             /* format of an empty tag */
static const int lcaselbl = 1;                  /* 1 means make tag label lowercase */



/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const int quit_empty_window_count = 0;   /* only allow dwm to quit if no (<= count) windows are open */
static const char *fonts[]               = { "JetBrainsMono Nerd Font:size=14" };
static const char dmenufont[]            = "JetBrainsMono:size=16";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#181926";
static char normbgcolor[]                = "#363a4f";
static char normbordercolor[]            = "#8aadf4";
static char normfloatcolor[]             = "#8aadf4";

static char selfgcolor[]                 = "#181926";
static char selbgcolor[]                 = "#363a4f";
static char selbordercolor[]             = "#ee99a0";
static char selfloatcolor[]              = "#ee99a0";

static char titlenormfgcolor[]           = "#cad3f5";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#8aadf4";
static char titlenormfloatcolor[]        = "#8aadf4";

static char titleselfgcolor[]            = "#181926";
static char titleselbgcolor[]            = "#363a4f";
static char titleselbordercolor[]        = "#ee99a0";
static char titleselfloatcolor[]         = "#ee99a0";

static char tagsnormfgcolor[]            = "#cad3f5";
static char tagsnormbgcolor[]            = "#363a4f";
static char tagsnormbordercolor[]        = "#8aadf4";
static char tagsnormfloatcolor[]         = "#8aadf4";

static char tagsselfgcolor[]             = "#181926";
static char tagsselbgcolor[]             = "#222222";
static char tagsselbordercolor[]         = "#ee99a0";
static char tagsselfloatcolor[]          = "#ee99a0";

static char hidnormfgcolor[]             = "#cad3f5";
static char hidselfgcolor[]              = "#181926";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#363a4f";

static char urgfgcolor[]                 = "#181926";
static char urgbgcolor[]                 = "#363a4f";
static char urgbordercolor[]             = "#ee99a0";
static char urgfloatcolor[]              = "#ee99a0";



static const unsigned int baralpha = 0x00;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};





/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "1  ", "2  ", "3  ", "4 󰢚 ", "5 󰄛 ", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "scpad", .isfloating = 1)
//	RULE(.class = "Gimp", .tags = 1 << 4)
//	RULE(.class = "Firefox", .tags = 1 << 7)
};



/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_taglabels,          draw_taglabels,         click_taglabels,         NULL,                    "taglabels" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,            click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
    { ":::",      gaplessgrid },
    { "===",      bstackhoriz },
    { "[D]",      deck },
    { "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};


/* key definitions */
#define MODKEY Mod1Mask
#define ALTMOD Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
//	"-nb", normbgcolor,
//	"-nf", normfgcolor,
//	"-sb", selbgcolor,
//	"-sf", selfgcolor,
	NULL
};
static const char *termcmd[]  = { "kitty", NULL };



static const Key keys[] = {
    /* modifier                     key        function        argument */
    // basic functions
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_q,      killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,                   {0} },
    // mediakeys and print
    {0,               XF86XK_AudioRaiseVolume, spawn,          SHCMD("volset up") },
    {0,               XF86XK_AudioLowerVolume, spawn,          SHCMD("volset down") },
    {0,               XF86XK_AudioMute,        spawn,          SHCMD("volset mute") },
	{ MODKEY|ALTMOD, XK_F1,          spawn,          SHCMD("volset max") },
    {0,               XK_Print,                spawn,          SHCMD("maimer cropped") },
    { ShiftMask,      XK_Print,                spawn,          SHCMD("maimer window") },
    //
    // personal shellscrips
    //
	{ MODKEY|ShiftMask, XK_Return, spawn,        SHCMD("scratch scratchpad") },
	{ MODKEY|ALTMOD, XK_b, spawn,        SHCMD("bookmarkmake") },
    //
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_o,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_p,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_Left,       focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_Right,      focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_Up,         focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_Down,       focusdir,               {.i = 3 } }, // down
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_k,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ControlMask,                       XK_Return,       zoom,                   {0} },
	{ MODKEY,                       XK_Page_Up,    togglefloating,         {0} },
	{ MODKEY,                       XK_f,  togglefakefullscreen,   {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
//	{ MODKEY|ALTMOD|ShiftMask|ControlMask,         XK_F1,         focusmon,               {.i = +1 } },
//	{ MODKEY|ALTMOD|ShiftMask,      XK_F2,         tagmon,                 {.i = +1 } },
	{ MODKEY,                       XK_c,        cyclelayout,            {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
    ////// useless
	{ 0, 0,          incrgaps,               {.i = +1 } },
	{ 0, 0,          incrgaps,               {.i = -1 } },
	{ 0, 0,          incrigaps,              {.i = +1 } },
	{ 0, 0,          incrigaps,              {.i = -1 } },
	{ 0, 0,          incrogaps,              {.i = +1 } },
	{ 0, 0,          incrogaps,              {.i = -1 } },
	{ 0, 0,          incrihgaps,             {.i = +1 } },
	{ 0, 0,          incrihgaps,             {.i = -1 } },
	{ 0, 0,          incrivgaps,             {.i = +1 } },
	{ 0, 0,          incrivgaps,             {.i = -1 } },
	{ 0, 0,          incrohgaps,             {.i = +1 } },
	{ 0, 0,          incrohgaps,             {.i = -1 } },
	{ 0, 0,          incrovgaps,             {.i = +1 } },
	{ 0, 0,          incrovgaps,             {.i = -1 } },
	{ 0, 0,          togglegaps,             {0} },
	{ 0, 0,          defaultgaps,            {0} },
	{ 0, 0,          view,                   {0} },
	{ 0, 0,          setlayout,              {.v = &layouts[0]} },
	{ 0, 0,          setlayout,              {.v = &layouts[1]} },
	{ 0, 0,          setlayout,              {.v = &layouts[2]} },
	{ 0, 0,          setlayout,              {0} },
	{ 0, 0,          cyclelayout,            {.i = -1 } },
	{ 0, 0,          tagmon,                 {.i = -1 } },
	{ 0, 0,          focusmon,               {.i = -1 } },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static const Signal signals[] = {
	/* signum                    function */
	{ "focusstack",              focusstack },
	{ "setmfact",                setmfact },
	{ "togglebar",               togglebar },
	{ "incnmaster",              incnmaster },
	{ "togglefloating",          togglefloating },
	{ "focusmon",                focusmon },
	{ "tagmon",                  tagmon },
	{ "zoom",                    zoom },
	{ "incrgaps",                incrgaps },
	{ "incrigaps",               incrigaps },
	{ "incrogaps",               incrogaps },
	{ "incrihgaps",              incrihgaps },
	{ "incrivgaps",              incrivgaps },
	{ "incrohgaps",              incrohgaps },
	{ "incrovgaps",              incrovgaps },
	{ "togglegaps",              togglegaps },
	{ "defaultgaps",             defaultgaps },
	{ "setgaps",                 setgapsex },
	{ "view",                    view },
	{ "viewall",                 viewallex },
	{ "viewex",                  viewex },
	{ "toggleview",              toggleview },
	{ "togglesticky",            togglesticky },
	{ "cyclelayout",             cyclelayout },
	{ "toggleviewex",            toggleviewex },
	{ "tag",                     tag },
	{ "tagall",                  tagallex },
	{ "tagex",                   tagex },
	{ "toggletag",               toggletag },
	{ "toggletagex",             toggletagex },
	{ "togglefakefullscreen",    togglefakefullscreen },
	{ "killclient",              killclient },
	{ "quit",                    quit },
	{ "setlayout",               setlayout },
	{ "setlayoutex",             setlayoutex },
};

