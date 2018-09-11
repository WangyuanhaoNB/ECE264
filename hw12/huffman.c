#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


//static int int_cmp(const void* p1, const void* p2)
//{
//	return (*const int *p1) - *(const int*)p2;
//}

//static int string_cmp(const void* p1,const void* p2)
//{
//	return strcmp((const char*)p1, (const int*)p2);
//			}

Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))
{
	if (new_object == NULL)
	{
		return NULL;
	}
	Node* current = malloc(sizeof(Node));
	if ((*pq) == NULL)
	{
		current->next = (*pq);
		(*pq) = current;
	}
	current -> ptr = (void*)new_object;
	if (cmp_fn((*pq)->ptr,current->ptr) >= 0)
	{
		current->next = (*pq);
		(*pq) = current;
	}
	else if (cmp_fn((*pq)->ptr,current->ptr) >= 0)
	{
		current->next = (*pq);
		(*pq) = current;
	}
	Node* one = *pq;
	Node* two = (*pq)->next;
	while (two != NULL && (cmp_fn(two->ptr,current->ptr) < 0))
	{
		one = one ->next;
		two = one -> next;
	}
	one->next = current;
	current->next = two;
	return current;
}
       
Node *pq_dequeue(Node **pq)
{
	Node* go = *pq;
	*pq = (*pq)->next;
	go->next = NULL;
	return go;
}


Node *stack_push(Node **stack, const void *new_object)
{
	if (new_object == NULL)
	{
		return NULL;
	}
	Node* new_stack = malloc(sizeof(Node));
	new_stack -> ptr =(void*) new_object;
	new_stack -> next = *stack;
	*stack = new_stack;
	return new_stack;
}


                       
Node *stack_pop(Node **stack)
{
	Node* go = *stack;
	*stack = (*stack)->next;
	go -> next = NULL;
	return go;
}


Node *remove_last_node(Node **list)
{
	Node* first = *list;
	Node* before;
	if (first == NULL)
	{
		return NULL;
	}
	while (first -> next != NULL)
	{
		before = first;
		first = first -> next;
	}
	before -> next = NULL;
	free(list);

   return first;
}


void destroy_node(Node *list, void (*destroy_fn)(void *))
{
	if(list == NULL)
	{
		return;
	}
	while (list != NULL) 
	{
		Node* current = list->next;
		destroy_fn(list->ptr);
	//    free(list);
		list = current;
    }
}

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}

