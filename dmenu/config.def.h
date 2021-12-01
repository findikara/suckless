/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;/* -b  option; if 0, dmenu appears at bottom     */
static int fuzzy  = 1; /* -F  option; if 0, dmenu doesn't use fuzzy matching     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=9:style=Bold"};
static const char *prompt  = NULL;
static const char col_bg[]          = "#020202";
static const char col_fg[]          = "#dddddd";
static const char col_gr[]          = "#252525";
static const char col_acc[]         = "#478061";
static const char col_aac[]         = "#aa9943";
static const char *colors[SchemeLast][2] = {
	/*                          fg        bg     */
	[SchemeNorm]            = { col_fg  , col_bg  },
	[SchemeSel]             = { col_bg  , col_acc },
	[SchemeSelHighlight]    = { col_aac , col_acc },
	[SchemeNormHighlight]   = { col_acc , col_gr  },
	[SchemeOut]             = { col_fg  , col_bg  },
};
/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines      = 0;
static unsigned int columns    = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
