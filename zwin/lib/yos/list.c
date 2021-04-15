/*
 * list.c
 *
 * linked list management
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 25.05.2012   tstih
 *
 */
#include "list.h"

/*
 * check if arg and pointer are equal
 */
byte_t list_match_eq(list_header_t *p, addr_t arg)
{
    return (((addr_t)p) == arg);
}

/*
 * find element using match function
 * this can be used for all sorts of tasks, for example if you want to find last element
 * you seek for element which has element->next==NULL
 */
list_header_t *list_find(
    list_header_t *first,
    list_header_t **prev,
    byte_t((*match)(list_header_t *p, addr_t arg)),
    addr_t the_arg)
{
    /* assume no previous */
    *prev = NULL;
    while (first && !match(first, the_arg))
    {
        *prev = first;
        first = first->next;
    }
    /* result is in first */
    return first;
}

/*
 * insert element into linked list at begining
 */
list_header_t *list_insert(list_header_t **first, list_header_t *el)
{
    el->next = *first;
    *first = el;
    return el;
}

/*
 * insert element into linked list at end
 */
list_header_t *list_append(list_header_t **first, list_header_t *el)
{

    list_header_t *current;

    el->next = NULL; /* it's always the last element */

    if (*first == NULL) /* empty list? */
        *first = el;
    else
    {
        current = *first;
        while (current->next)
            current = current->next;
        current->next = el;
    }
    return el;
}

/*
 * removes element from linked list
 */
list_header_t *list_remove(list_header_t **first, list_header_t *el)
{
    list_header_t *prev;
    if (el == *first)
    {
        *first = el->next;
    }
    else
    {
        if (!list_find(*first, &prev, list_match_eq, (addr_t)el))
            return NULL;
        else /* rewire */
            prev->next = el->next;
    }
    return el;
}

/*
 * remove first element from linked list
 */
list_header_t *list_remove_first(list_header_t **first)
{
    list_header_t *result;
    if (*first == NULL)
        return NULL; /* empty list */
    result = *first;
    *first = (list_header_t *)((*first)->next);
    return result;
}
