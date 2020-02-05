# Static sorted list
This list was made for embedded systems with C/C++. 
It doesn't use th dynamic allocation. Look at tests (Google Test driven) for examples. 

 


# How to use 

* Create a container for your elements 
* Allocate them somehow
* Provide a method to compare them (you can set `0` if you don't need to sort them)


## Container for `element_t`

The element should contain a proper pointer to it's data (it's on your own)

```
typedef struct element_t{
	void * current;
	struct element_t* next;
}element_t;
```

This is an example. I set the data in the constructor. In this sample `delay` is a key value we want to sort. 
```
struct my_object_t{
	int delay = 0;
	element_t element;
	my_object_t()
	{
		element.data = this;
	}

};
```

## Alocate elements

You can use arrays or anything you want. Correct `element`s are stored in our containers
```
	my_object_t first;
	my_object_t second;
	my_object_t third;
	my_object_t fourth;
```

## Method to compare and list initialisation

As you see, you should provide the callback `list_compare_t` to compare your elemnts
```
typedef bool(*list_compare_t)(void * element_in_list, void * new_element);

bool
slist_init (linked_list *c,  list_compare_t compare);
```

Compare function example:
```
bool
compare_my_obj(void * element_in_list, void * new_element)
{
	my_object_t * first = static_cast<my_object_t*>(element_in_list);
	my_object_t * second = static_cast<my_object_t*>(new_element);

	return first->delay > second->delay;
}
```


If don't need to sort your list, just leave a zero value
```
linked_list unsorted_list;

slist_init(&unsorted_list, 0);
```



