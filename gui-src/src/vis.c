/*
 * vis.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "common.h"

#include <math.h>

#define CUR_SH_COL	"green"
#define NEXT_SH_COL	"orange"

#define SKYTT_PIXMAP	"edwin3.xpm"
#define PIX_H		111
#define PIX_W		111
#define EDGE_OFFSET	20
#define ARC_SIZE	20

/*
#define SKYTT_PIXMAP	"/tmp/skytt1.xpm"
#define PIX_H		75
#define PIX_W		60
#define EDGE_OFFSET	20
#define ARC_SIZE	10
*/
/*
#define SKYTT_PIXMAP	"/tmp/skytt2.xpm"
#define PIX_H		96
#define PIX_W		67
#define EDGE_OFFSET	20
#define ARC_SIZE	10
*/



static struct {
	double x;
	double y;
} pts[] = {
#if 0
	/* Skytt 1 - 8 */
	{ -0.00000, -1.00000 },
	{  0.70711, -0.70711 },
	{  1.00000,  0.00000 },
	{  0.70711,  0.70711 },
	{  0.00000,  1.00000 },
	{ -0.70711,  0.70711 },
	{ -1.00000,  0.00000 },
	{ -0.70711, -0.70711 },	/* Rakt framför bilen */
	/* Skytt A - H */
	{  0.38268, -0.92388 },
	{  0.92388, -0.38268 },
	{  0.92388,  0.38268 },
	{  0.38268,  0.92388 },
	{ -0.38268,  0.92388 },
	{ -0.92388,  0.38268 },
	{ -0.92388, -0.38268 },
	{ -0.38268, -0.92388 }
#endif
{ 0.00000, -1.00000 },  /* 1 */
{ 0.70711, -0.70711 },  /* 2 */
{ 1.00000, 0.00000 },   /* 3 */
{ 0.70711, 0.70711 },   /* 4 */
{ 0.00000, 1.00000 },   /* 5 */
{ -0.70711, 0.70711 },  /* 6 */
{ -1.00000, 0.00000 },  /* 7 */
{ -0.70711, -0.70711 }, /* 8 */
{ 0.38268, -0.92388 },  /* A */
{ 0.92388, -0.38268 },  /* B */
{ 0.92388, 0.38268 },   /* C */
{ 0.38268, 0.92388 },   /* D */
{ -0.38268, 0.92388 },  /* E */
{ -0.92388, 0.38268 },  /* F */
{ -0.92388, -0.38268 }, /* G */
{ -0.38268, -0.92388 }, /* H */

};


static GdkPoint r_pts[16];
static GdkPixmap *pix;
static GdkGC *gc = NULL;
static GdkColor gcl;
static GdkFont *font;


void vis_init(void) {
	int i;

	for(i = 0; i < 16; i++) {
		pts[i].x *= PIX_W/2 + EDGE_OFFSET/2;
		pts[i].y *= PIX_H/2 + EDGE_OFFSET/2;

		pts[i].x += PIX_W/2 + EDGE_OFFSET/2;
		pts[i].y += PIX_H/2 + EDGE_OFFSET/2;

		r_pts[i].x = (gint16) pts[i].x;
		r_pts[i].y = (gint16) pts[i].y;
	}

	font = gdk_font_load("-adobe-courier-*-*-normal-*-10-*-*-*-*-*-iso8859-1");
}


void vis_update(void) {
	gchar skytt_txt[10];
	int i;
	int skytt = 0;

	if(!gc)
		return;

	gdk_color_parse("rgb:d6/d6/d6", &gcl);		// GTK grey :)
	gdk_color_parse("rgb:12/34/56", &gcl);		// GTK grey :)
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);

	for(i = 0; i < 16; i++)
		gdk_draw_arc(imgMain->window, gc, 1, r_pts[i].x, r_pts[i].y, 
				ARC_SIZE, ARC_SIZE, 0, 64*360);

	if(!run->running)
		return;

	if(!run->running || !run->program 
	   || run->instruction >= run->tot_instructions 
	   || !run->program[run->instruction].id)
		return;


	/* Draw the red arc for the current shooter */
	gdk_color_parse(CUR_SH_COL, &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);

	skytt = run->program[run->instruction].id;

	gdk_draw_arc(imgMain->window, gc, 1, r_pts[skytt].x, r_pts[skytt].y,
			ARC_SIZE, ARC_SIZE, 0, 64*360);

	gdk_colormap_free_colors(gdk_rgb_get_cmap(), &gcl, 1);



	/* Draw number of shooter on the arc */
	gdk_color_parse("black", &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);
	sprintf(skytt_txt, "%c", run->program[run->instruction].id <= 8?
		run->program[run->instruction].id + '0':
		run->program[run->instruction].id + 'A' - 8);

	if(font)
		gdk_draw_string(imgMain->window, font, gc, r_pts[skytt].x-8+ARC_SIZE/2,
				r_pts[skytt].y+4+ARC_SIZE/2, skytt_txt);

	gdk_colormap_free_colors(gdk_rgb_get_cmap(), &gcl, 1);




	if(run->program[run->instruction].value != 1 ||
	   run->instruction+1 >= run->tot_instructions)
		return;

	if(run->program[run->instruction].id ==
	   run->program[run->instruction+1].id)
		return;		/* Same shooter */



	gdk_color_parse(NEXT_SH_COL, &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);

	skytt = run->program[run->instruction+1].id;
	gdk_draw_arc(imgMain->window, gc, 1, r_pts[skytt].x, r_pts[skytt].y,
			ARC_SIZE, ARC_SIZE, 0, 64*360);
	gdk_colormap_free_colors(gdk_rgb_get_cmap(), &gcl, 1);


	gdk_color_parse("black", &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);
	sprintf(skytt_txt, "%c", run->program[run->instruction+1].id <= 8?
		run->program[run->instruction+1].id + '0':
		run->program[run->instruction+1].id + 'A' - 8);

	if(font)
		gdk_draw_string(imgMain->window, font, gc, r_pts[skytt].x-8+ARC_SIZE/2,
				r_pts[skytt].y+4+ARC_SIZE/2, skytt_txt);

	gdk_colormap_free_colors(gdk_rgb_get_cmap(), &gcl, 1);

}



gboolean on_imgMain_expose_event(GtkWidget *widget, GdkEventExpose *event,
				 gpointer user_data) {

	if(!gc)
		gc = gdk_gc_new(widget->window);

	pix = gdk_pixmap_create_from_xpm(widget->window, NULL, NULL, 
					 SKYTT_PIXMAP);
	if(!pix)
		return FALSE;


	gdk_color_parse("white", &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_foreground(gc, &gcl);
	gdk_colormap_free_colors(gdk_rgb_get_cmap(), &gcl, 1);

#if 0
	gdk_color_parse("black", &gcl);
	gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &gcl, FALSE, TRUE);
	gdk_gc_set_background(gc, &gcl);
#endif

	gdk_draw_pixmap(imgMain->window, gc, pix, 0, 0, 
			EDGE_OFFSET, EDGE_OFFSET, -1, -1);
	gdk_pixmap_unref(pix);

	vis_update();

	return FALSE;
}

