#include <stdio.h>
#include <stdlib.h>

struct list_head{
	struct list_head *next, *pre;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) struct list_head(name) = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do{ \
	(ptr)->next = (ptr); (ptr)->pre = (ptr);\
	}while( 0 )

#define list_entry(ptr, type, member)  ({  \
		const typeof( ((type *)0)->member)* _mptr = (ptr);  \
		(type *)( (int *)_mptr - offsetof(type,member) );})
#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define list_for_each(pos, head) \
		for( pos = (head)->next; pos != (head); \
		pos = pos->next )

int list_empty(const struct list_head *head)
{
	return head->next == head;
}

void list_add_tail(struct list_head *new, struct list_head *head)
{
	if( list_empty(head) ){
		head->pre = new;
		head->next = new;
		new->next = head;
		new->pre = head;
	}else{
		new->next = head;
		new->pre = head->pre;
		(head->pre)->next = new;
		head->pre = new;
	}
}

void list_add(struct list_head *new, struct list_head *head)
{
	if( list_empty(head) ){
		head->pre = new;
		head->next = new;
		new->next = head;
		new->pre = head;
	}else{
		new->next = head->next;
		new->pre = head;
		(head->next)->pre = new;
		head->next = new;
	}
}

void list_del(struct list_head *entry)
{
	(entry->pre)->next = entry->next;
	(entry->next)->pre = entry->pre;
	INIT_LIST_HEAD( entry );

}

void list_splice(struct list_head *list, struct list_head *head)
{
	(list->pre)->next = head->next;
	head->next = list->next;
	INIT_LIST_HEAD( list );
}

