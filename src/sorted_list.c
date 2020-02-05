/*
 * sorted_list.c
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
#include "sorted_list.h"


bool
slist_init (linked_list *c, list_compare_t compare)
{
	if (!c)
		return false;

	c->compare = compare;
	c->head = 0;
	c->tail = 0;
	return true;
}


void
_start_list_with(linked_list *c, element_t * new_element)
{
	c->head = new_element;
	c->tail = new_element;
	new_element->next = 0;
}

bool
_compare(linked_list *c, element_t * old_element, element_t * new_element)
{
	if (!c->compare)
		return false;

	if (c->compare( old_element->data, new_element->data))
		return true;
	else
		return false;
}

bool
_compare_with_head(linked_list *c, element_t * new_element)
{
	if (_compare(c, c->head, new_element))
	{
		new_element->next = c->head;
		c->head =new_element;
		return true;
	}

	return false;
}


bool
slist_add (linked_list *c, element_t * new_element)
{
	if (c->head == 0)
	{
		_start_list_with(c, new_element);
		return true;
	}

	if (_compare_with_head(c, new_element))
		return true;


	element_t * foo_ptr = c->head;

	while (foo_ptr->next){
		if (_compare(c, foo_ptr->next, new_element))
		{
			//Insert new element between foo and foo_next :  foo ->  new_element ->foo_next
			new_element->next = foo_ptr->next;
			foo_ptr->next = new_element;
			return true;
		}

		// Move next
		foo_ptr = foo_ptr->next;

	}

	// Insert to tail
	foo_ptr->next = new_element;
	new_element->next = 0;
	c->tail = new_element;

	return true;
}

bool
slist_delete (linked_list *c, element_t * element_to_delete)
{

	if (c->head == 0 )
		return false;

	if (c->head == element_to_delete)
	{
		//Check if it's the last element
		if (c->tail == c->head)
			c->tail = 0;

		c->head = element_to_delete->next;

		return true;
	}


	element_t * foo_ptr = c->head;

	while (foo_ptr->next){
		if (foo_ptr->next == element_to_delete)
		{
			foo_ptr->next = foo_ptr->next->next;
			if (foo_ptr->next == 0)
			{
				c->tail = foo_ptr;
			}
			return true;
		}

		// Move next
		foo_ptr = foo_ptr->next;
	}

	return false;
}

element_t*
slist_get_head (linked_list *c)
{

	return c->head;
}


