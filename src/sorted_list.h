/*
 * linked_list.c
 *
 *  Created on: 4 feb. 2020 ã.
 *      Author: Natalenko Mikhail
 *
 *       This file is part of Static Sorted List.
 *
 *       Static Sorted List is free software: you can redistribute it and/or modify
 *       it under the terms of the GNU General Public License as published by
 *       the Free Software Foundation, either version 3 of the License, or
 *       (at your option) any later version.
 *
 *       Static Sorted List is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public License
 *       along with Static Sorted List.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SORTED_LIST_H_
#define SORTED_LIST_H_


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
  {
#endif

typedef struct element_t{
	void * data;
	struct element_t* next;
}element_t;

typedef bool(*list_compare_t)(void * element_in_list, void * new_element);

typedef struct
{
  element_t * head;
  element_t * tail;
  list_compare_t compare;
} linked_list;

bool
slist_init (linked_list *c,  list_compare_t compare);

bool
slist_add (linked_list *c, element_t *);

bool
slist_delete (linked_list *c, element_t *);

element_t*
slist_get_head (linked_list *c);

#ifdef __cplusplus
}
#endif
#endif /* SORTED_LIST_H_ */
