/*
 * test_alarm.cpp
 *
 *  Created on: Jan 2, 2020
 *      Author: misha
 */
#include <gtest/gtest.h>
#include "../sorted_list.h"




struct my_object_t{
	int delay = 0;
	element_t element;
	my_object_t()
	{
		element.data = this;
	}

};

bool
compare_my_obj(void * element_in_list, void * new_element)
{
	my_object_t * first = static_cast<my_object_t*>(element_in_list);
	my_object_t * second = static_cast<my_object_t*>(new_element);

	return first->delay > second->delay;
}

class CommonTests : public ::testing::Test
{
protected:

	linked_list list;
	my_object_t first;
	my_object_t second;
	my_object_t third;
	my_object_t fourth;

	linked_list unsorted_list;
	void SetUp()
	{
		slist_init(&list, compare_my_obj);
		slist_init(&unsorted_list, 0);
	}
	void TearDown()
	{
	}
};

TEST_F(CommonTests, add_equal)
{
	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &third);
	ASSERT_EQ(start->next->next->next->data, &fourth);
}


TEST_F(CommonTests, add_increment)
{

	first.delay = 50;
	second.delay = 1000;
	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &third);
	ASSERT_EQ(start->next->data, &fourth);
	ASSERT_EQ(start->next->next->data, &first);
	ASSERT_EQ(start->next->next->next->data, &second);
}

TEST_F(CommonTests, remove_tasks)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	ASSERT_EQ(true, slist_delete(&list, &third.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &fourth);
}

TEST_F(CommonTests, remove_last_task)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	ASSERT_EQ(true, slist_delete(&list, &fourth.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &third);
	ASSERT_EQ(start->next->next->next, nullptr);
}

TEST_F(CommonTests, remove_first_task)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	ASSERT_EQ(true, slist_delete(&list, &first.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &second);
	ASSERT_EQ(start->next->data, &third);
	ASSERT_EQ(start->next->next->data, &fourth);
	ASSERT_EQ(start->next->next->next, nullptr);
}

TEST_F(CommonTests, remove_all_tasks_from_head)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	ASSERT_EQ(true, slist_delete(&list, &first.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &second);
	ASSERT_EQ(start->next->data, &third);
	ASSERT_EQ(start->next->next->data, &fourth);
	ASSERT_EQ(start->next->next->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &second.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start->data, &third);
	ASSERT_EQ(start->next->data, &fourth);
	ASSERT_EQ(start->next->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &third.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start->data, &fourth);
	ASSERT_EQ(start->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &fourth.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start, nullptr);

	ASSERT_EQ(false, slist_delete(&list, &fourth.element));
}


TEST_F(CommonTests, remove_all_tasks_from_tail)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &second.element));
	ASSERT_EQ(true, slist_add(&list, &third.element));
	ASSERT_EQ(true, slist_add(&list, &fourth.element));

	ASSERT_EQ(true, slist_delete(&list, &fourth.element));

	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &third);
	ASSERT_EQ(start->next->next->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &third.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &second.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next, nullptr);

	ASSERT_EQ(true, slist_delete(&list, &first.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start, nullptr);

	ASSERT_EQ(false, slist_delete(&list, &first.element));
}

TEST_F(CommonTests, add_one_and_remove)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(true, slist_delete(&list, &first.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start, nullptr);
}

TEST_F(CommonTests, add_dublicats)
{

	ASSERT_EQ(true, slist_add(&list, &first.element));
	ASSERT_EQ(true, slist_add(&list, &first.element));
	element_t * start = slist_get_head(&list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(true, slist_delete(&list, &first.element));
	start = slist_get_head(&list);
	ASSERT_EQ(start, nullptr);
}

TEST_F(CommonTests, add_to_unsorted_equal)
{

	ASSERT_EQ(true, slist_add(&unsorted_list, &first.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &second.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &third.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &fourth.element));

	element_t * start = slist_get_head(&unsorted_list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &third);
	ASSERT_EQ(start->next->next->next->data, &fourth);
}

TEST_F(CommonTests, add_to_unsorted_unequal)
{
	first.delay = 50;
	second.delay = 1000;
	ASSERT_EQ(true, slist_add(&unsorted_list, &first.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &second.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &third.element));
	ASSERT_EQ(true, slist_add(&unsorted_list, &fourth.element));

	element_t * start = slist_get_head(&unsorted_list);
	ASSERT_EQ(start->data, &first);
	ASSERT_EQ(start->next->data, &second);
	ASSERT_EQ(start->next->next->data, &third);
	ASSERT_EQ(start->next->next->next->data, &fourth);
}
