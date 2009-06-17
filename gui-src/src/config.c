/*
 * config.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 */

#include <gtk/gtk.h>
#include <gnome.h>
#include "support.h"
#include "interface.h"

#include "common.h"



void config_read(void) {

	char fname[1024], buf[1024];
	char name[200], val[200];
	FILE *fd;
	CONFIG *ptr = config;


	sprintf(fname, "%s/.slimrc", getenv("HOME"));
	if((fd = fopen(fname, "rt")) == NULL) {
		/* Try to save default values */
		if(config_save(1) == 0)
			config_read();

		return;
	}


	config_free();

	do {
		memset(buf, 0, sizeof(buf));
		if(fgets(buf, 1024, fd) == NULL)
			break;

		if(strchr(buf, '\r'))
			*strchr(buf, '\r') = 0;

		if(strchr(buf, '\n'))
			*strchr(buf, '\n') = 0;

		if(sscanf(buf, "%[^=]=%[^=]", name, val) != 2)
			break;

		if(!ptr)
			config = ptr = (CONFIG *)calloc(1,  sizeof(CONFIG));
		else {
			ptr->next = (CONFIG *)calloc(1, sizeof(CONFIG));
			ptr = ptr->next;
		}

		ptr->name = strdup(name);
		ptr->val = strdup(val);
	} while(1);

	fclose(fd);
}


int config_save(int save_defaults) {
	CONFIG *defaults, *ptr;
	char name[4096];
	FILE *fd;

	if(save_defaults) {
		defaults = ptr = (CONFIG *)calloc(1, sizeof(CONFIG));
		ptr->name = strdup("shoot_diff");
		ptr->val = strdup("10");

		ptr->next = (CONFIG *)calloc(1, sizeof(CONFIG));
		ptr = ptr->next;
		ptr->name = strdup("mainwin_title");
		ptr->val = strdup("Snogeholmskastaren");

		ptr->next = (CONFIG *)calloc(1, sizeof(CONFIG));
		ptr = ptr->next;
		ptr->name = strdup("init_rounds");
		ptr->val = strdup("2");

		ptr->next = (CONFIG *)calloc(1, sizeof(CONFIG));
		ptr = ptr->next;
		ptr->name = strdup("reload_time");
		ptr->val = strdup("1500");

		ptr->next = (CONFIG *)calloc(1, sizeof(CONFIG));
		ptr = ptr->next;
		ptr->name = strdup("dual_execute");
		ptr->val = strdup("0");

		ptr = defaults;
	}
	else
		ptr = config;

	
	sprintf(name, "%s/.slimrc", getenv("HOME"));
	if((fd = fopen(name, "wt")) == NULL) {
		g_print("-- config_save(): unable to save config!\n");
		return -1;
	}


	while(ptr) {
		fprintf(fd, "%s=%s\n", ptr->name, ptr->val);
		ptr = ptr->next;
	}

	fclose(fd);

	g_print("-- config_save(): Configuration successfully saved!\n");
	return 0;
}


void config_free(void) {
	CONFIG *ptr = config, *tmp;


	while(ptr) {
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->name);
		free(tmp->val);
		free(tmp);
	}

	config = NULL;
}


char *config_get(char *name) {
	CONFIG *ptr = config;

	while(ptr) {
		if(!strcmp(name, ptr->name))
			return ptr->val;

		ptr = ptr->next;
	}

	return NULL;
}


void config_load_to_clist(GtkWidget *clist) {
	gchar *values[2];
	char fname[1024], buf[1024];
	/* XXX - bufferstorlek! */
	char name[1024], val[1024];
	FILE *fd;

	sprintf(fname, "%s/.slimrc", getenv("HOME"));
	if((fd = fopen(fname, "rt")) == NULL) {
		return;
	}


	gtk_clist_clear(GTK_CLIST(clist));
	do {
		memset(name, 0, sizeof(name));
		memset(val, 0, sizeof(val));
		memset(buf, 0, sizeof(buf));
		if(fgets(buf, 1024, fd) == NULL)
			break;

		if(strchr(buf, '\r'))
			*strchr(buf, '\r') = 0;

		if(strchr(buf, '\n'))
			*strchr(buf, '\n') = 0;

		if(sscanf(buf, "%[^=]=%[^=]", name, val) != 2)
			break;

		values[0] = strdup(name);
		values[1] = strdup(val);
		printf("config_read(): %s=%s\n", name, val);

		free(values[0]);
		free(values[1]);
		gtk_clist_append(GTK_CLIST(clist), values);

	} while(1);

	fclose(fd);
}


void config_save_from_clist(GtkWidget *clist) {
	gchar *name[1], *val[1];
	int i;
	CONFIG *p = config;



	for(i = 0; i < 100; i++) {
		if(!gtk_clist_get_text(GTK_CLIST(clist), i, 0, name)
		   || !gtk_clist_get_text(GTK_CLIST(clist), i, 1, val))
			break;

		p = config;
		while(p) {
			if(!strcmp(name[0], p->name)) {
				free(p->val);
				p->val = strdup(val[0]);
				break;
			}


			p = p->next;
		}
		
	}

	


}


void config_use(void) {
	if(config_get("mainwin_title"))
		gtk_window_set_title(GTK_WINDOW(mainwin), config_get("mainwin_title"));


	if(config_get("init_rounds"))
		run->init_rounds = atoi(config_get("init_rounds"));
	else
		run->init_rounds = 2;


	if(config_get("reload_time"))
		run->reload_time = atoi(config_get("reload_time"));
	else
		run->reload_time = 2000;

	if(config_get("dual_execute"))
		run->dual_execute = atoi(config_get("dual_execute"));
	else
		run->dual_execute = 0;
}
