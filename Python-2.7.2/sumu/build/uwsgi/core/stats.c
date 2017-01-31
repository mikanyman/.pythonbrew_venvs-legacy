#include "uwsgi.h"
/*
	utility functions for fast generating json output for the stats subsystem
*/

struct uwsgi_stats *uwsgi_stats_new(size_t chunk_size) {
	struct uwsgi_stats *us = uwsgi_malloc(sizeof(struct uwsgi_stats));
	us->base = uwsgi_malloc(chunk_size);
	us->base[0] = '{';
	us->base[1] = '\n';
	us->pos = 2;
	us->chunk = chunk_size;
	us->size = chunk_size;
	us->tabs = 1;
	return us;
}

int uwsgi_stats_symbol(struct uwsgi_stats *us, char sym) {
	char *ptr = us->base + us->pos;
	char *watermark = us->base + us->size;

	if (ptr+1 > watermark) {
		char *new_base = realloc(us->base, us->size + us->chunk);
		if (!new_base) return -1;
		us->base = new_base;
		us->size += us->chunk;
		ptr = us->base + us->pos;
	}

	*ptr = sym;
	us->pos++;
	return 0;
}

int uwsgi_stats_symbol_nl(struct uwsgi_stats *us, char sym) {
	if (uwsgi_stats_symbol(us, sym)) {
		return -1;
	}
	return uwsgi_stats_symbol(us, '\n');
}


int uwsgi_stats_comma(struct uwsgi_stats *us) {
	return uwsgi_stats_symbol_nl(us, ',');
}

int uwsgi_stats_apply_tabs(struct uwsgi_stats *us) {
	size_t i;
	for(i=0;i<us->tabs;i++) {
		if (uwsgi_stats_symbol(us, '\t')) return -1;
	};
	return 0;
}


int uwsgi_stats_object_open(struct uwsgi_stats *us) {
	if (uwsgi_stats_apply_tabs(us)) return -1;
	us->tabs++;
	return uwsgi_stats_symbol_nl(us, '{');
}

int uwsgi_stats_object_close(struct uwsgi_stats *us) {
	if (uwsgi_stats_symbol(us, '\n')) return -1;
	us->tabs--;
	if (uwsgi_stats_apply_tabs(us)) return -1;
	return uwsgi_stats_symbol(us, '}');
}

int uwsgi_stats_list_open(struct uwsgi_stats *us) {
	us->tabs++;
	return uwsgi_stats_symbol_nl(us, '[');
}

int uwsgi_stats_list_close(struct uwsgi_stats *us) {
	if (uwsgi_stats_symbol(us, '\n')) return -1;
	us->tabs--;
	if (uwsgi_stats_apply_tabs(us)) return -1;
	return uwsgi_stats_symbol(us, ']');
}

int uwsgi_stats_keyval(struct uwsgi_stats *us, char *key, char *value) {

	if (uwsgi_stats_apply_tabs(us)) return -1;

	char *ptr = us->base + us->pos;
	char *watermark = us->base + us->size;
	size_t available = watermark - ptr ;

	int ret = snprintf(ptr, available, "\"%s\":\"%s\"", key, value);
	if (ret < 0) return -1;
	while (ret >= (int) available) {
		char *new_base = realloc(us->base, us->size + us->chunk);
		if (!new_base) return -1;
		us->base = new_base;
		us->size += us->chunk;
		ptr = us->base + us->pos;
		watermark = us->base + us->size;
		available = watermark - ptr ;
		ret = snprintf(ptr, available, "\"%s\":\"%s\"", key, value);
		if (ret < 0) return -1;
	}

	us->pos += ret;
	return 0;
	
}

int uwsgi_stats_keyval_comma(struct uwsgi_stats *us, char *key, char *value) {
	int ret = uwsgi_stats_keyval(us, key, value);
	if (ret) return -1;
	return uwsgi_stats_comma(us);
}

int uwsgi_stats_keyvalnum(struct uwsgi_stats *us, char *key, char *value, unsigned long long num) {

	if (uwsgi_stats_apply_tabs(us)) return -1;

        char *ptr = us->base + us->pos;
        char *watermark = us->base + us->size;
        size_t available = watermark - ptr ;

        int ret = snprintf(ptr, available, "\"%s\":\"%s%llu\"", key, value, num);
        if (ret < 0) return -1;
        while (ret >= (int) available) {
                char *new_base = realloc(us->base, us->size + us->chunk);
                if (!new_base) return -1;
		us->base = new_base;
                us->size += us->chunk;
		ptr = us->base + us->pos;
                watermark = us->base + us->size;
                available = watermark - ptr ;
                ret = snprintf(ptr, available, "\"%s\":\"%s%llu\"", key, value, num);
                if (ret < 0) return -1;
        }

        us->pos += ret;
        return 0;
        
}

int uwsgi_stats_keyvalnum_comma(struct uwsgi_stats *us, char *key, char *value, unsigned long long num) {
        int ret = uwsgi_stats_keyvalnum(us, key, value, num);
        if (ret) return -1;
        return uwsgi_stats_comma(us);
}


int uwsgi_stats_keyvaln(struct uwsgi_stats *us, char *key, char *value, int vallen) {

	if (uwsgi_stats_apply_tabs(us)) return -1;

        char *ptr = us->base + us->pos;
        char *watermark = us->base + us->size;
        size_t available = watermark - ptr ;

        int ret = snprintf(ptr, available, "\"%s\":\"%.*s\"", key, vallen, value);
        if (ret < 0) return -1;
        while (ret >= (int) available) {
                char *new_base = realloc(us->base, us->size + us->chunk);
                if (!new_base) return -1;
		us->base = new_base;
                us->size += us->chunk;
		ptr = us->base + us->pos;
                watermark = us->base + us->size;
                available = watermark - ptr ;
                ret = snprintf(ptr, available, "\"%s\":\"%.*s\"", key, vallen, value);
                if (ret < 0) return -1;
        }

        us->pos += ret;
        return 0;
        
}

int uwsgi_stats_keyvaln_comma(struct uwsgi_stats *us, char *key, char *value, int vallen) {
        int ret = uwsgi_stats_keyvaln(us, key, value, vallen);
        if (ret) return -1;
        return uwsgi_stats_comma(us);
}


int uwsgi_stats_key(struct uwsgi_stats *us, char *key) {

	if (uwsgi_stats_apply_tabs(us)) return -1;

        char *ptr = us->base + us->pos;
        char *watermark = us->base + us->size;
        size_t available = watermark - ptr ;

        int ret = snprintf(ptr, available, "\"%s\":", key);
        if (ret < 0) return -1;
        while (ret >= (int) available) {
                char *new_base = realloc(us->base, us->size + us->chunk);
                if (!new_base) return -1;
		us->base = new_base;
                us->size += us->chunk;
		ptr = us->base + us->pos;
                watermark = us->base + us->size;
                available = watermark - ptr ;
                ret = snprintf(ptr, available, "\"%s\":", key);
                if (ret < 0) return -1;
        }

        us->pos += ret;
        return 0;
}

int uwsgi_stats_str(struct uwsgi_stats *us, char *str) {

        char *ptr = us->base + us->pos;
        char *watermark = us->base + us->size;
        size_t available = watermark - ptr ;

        int ret = snprintf(ptr, available, "\"%s\"", str);
        if (ret < 0) return -1;
        while (ret >= (int) available) {
                char *new_base = realloc(us->base, us->size + us->chunk);
                if (!new_base) return -1;
		us->base = new_base;
                us->size += us->chunk;
		ptr = us->base + us->pos;
                watermark = us->base + us->size;
                available = watermark - ptr ;
                ret = snprintf(ptr, available, "\"%s\"", str);
                if (ret < 0) return -1;
        }

        us->pos += ret;
        return 0;
}




int uwsgi_stats_keylong(struct uwsgi_stats *us, char *key, unsigned long long num) {

	if (uwsgi_stats_apply_tabs(us)) return -1;

        char *ptr = us->base + us->pos;
        char *watermark = us->base + us->size;
        size_t available = watermark - ptr ;

        int ret = snprintf(ptr, available, "\"%s\":%llu", key, num);
        if (ret < 0) return -1;
        while (ret >= (int) available) {
                char *new_base = realloc(us->base, us->size + us->chunk);
                if (!new_base) return -1;
		us->base = new_base;
                us->size += us->chunk;
		ptr = us->base + us->pos;
                watermark = us->base + us->size;
                available = watermark - ptr ;
                ret = snprintf(ptr, available, "\"%s\":%llu", key, num);
                if (ret < 0) return -1;
        }

        us->pos += ret;
        return 0;
}


int uwsgi_stats_keylong_comma(struct uwsgi_stats *us, char *key, unsigned long long num) {
	int ret = uwsgi_stats_keylong(us, key, num);
	if (ret) return -1;
	return uwsgi_stats_comma(us);
}
