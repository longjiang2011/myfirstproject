#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node{
	float  data;
	struct list_head list;
};

void create_node(struct node* node_ptr, float data)
{
	node_ptr->data = data;

}

int main( )
{
	struct list_head  *i, *list_ptr;
	struct node 	*node_ptr;

	//declear list head;    
	LIST_HEAD(head);
	//insert from head
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 1 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add( &(node_ptr->list), &(head) );
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 1 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add( &(node_ptr->list), &(head) );

	//inser from tail
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 2 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add_tail( &(node_ptr->list), &(head) );
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 2 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add_tail( &(node_ptr->list), &(head) );

	list_for_each( i, &head ){
		node_ptr = list_entry( i, struct node, list);
		printf("%f\n", node_ptr->data);
	}
	//delete a node
	list_del( &(node_ptr->list) );
	list_for_each( i, &head ){
		node_ptr = list_entry( i, struct node, list);
		printf("%f\n", node_ptr->data);
	}

	//splice 
	LIST_HEAD(another_head);
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 3 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add( &(node_ptr->list), &(another_head) );
	node_ptr = (struct node*)malloc(sizeof(struct node));
	create_node( node_ptr, 3 );
	INIT_LIST_HEAD( &(node_ptr->list) );
	list_add( &(node_ptr->list), &(another_head) );
	list_splice(&another_head, &head);

	list_for_each( i, &head ){
		node_ptr = list_entry( i, struct node, list);
		printf("%f\n", node_ptr->data);
	}

	return 0;
}

