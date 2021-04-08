/*
 *  yos.h
 *  the complete yos API
 *  include this to write code for yos
 *
 *  tomaz stih jul 26 2015
 *
 */
#ifndef _YOS_H
#define _YOS_H

/* yos definitions */
#define NULL    ( (word)0 )
#define TRUE    ( (byte)1 )
#define FALSE   ( (byte)0 )

/* yos types */
#ifdef _ZX_SPECTRUM
typedef signed char         byte;
typedef byte                boolean;
typedef byte                result;
typedef unsigned short int  word;
typedef word                handle;
typedef byte*               string;
#elif _SDL
typedef signed char         byte;
typedef byte                boolean;
typedef byte                result;
typedef void* 				word;
typedef word                handle;
typedef signed char*        string;
#endif

/* API */
typedef struct yos_s yos_t;
struct yos_s {

    /* system lists */
    void* (*lappend)(void **first, void *el);
    void* (*linsert)(void **first, void *el);
    void* (*lremove)(void **first, void *el);
    void* (*lremfirst)(void **first);

    /* memory management */
    void* (*allocate)(word size);
    void (*free)(void *p);
    void (*copy)(byte *src, byte *dst, word count);

    /* tasks, events */
    void (*sleep)(word _50);
};

/* call this to obtain the yos interface
 *   yos_t* api=(yos*)query_api("yo00"); // 2 letters + 2 dig. version
 *   void* mem_block=api->allocate(1024);
 * this function is defined in crt0.s for yos application
 */
extern void *query_api(char *api);

/* register your own api so that it can be accessed from yos api */
extern void register_api(char *api, void *name);


#endif /* _YOS_H */
