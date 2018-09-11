#include<stdio.h>
#include<stdlib.h>
#include"huffman.h"

void destroy_fn(void* destroy)
{
	return;
}
static int int_cmp(const void* p1, const void* p2)
{
	return *(const int*)p1 - *(const int*)p2;
}
static void print_fn(const void* ptr)
{
	printf("%d",*(const int*)ptr);
}

int main(int argc, char** argv)
{
	int a = 2;
	int b = 4;
	int c = 6;
	int d = 8;
	int e = 10;
	int f = 7;

	int (*cmp)(const void*, const void*) = int_cmp;
	void(*print)(const void*) = print_fn;
	void(*dest)(void*) = destroy_fn;

	Node* start = malloc(sizeof(*start));
	(*start).ptr = &a;
	Node* curr = start;

	(*curr).next = malloc(sizeof(Node));
	curr = (*curr).next;
	(*curr).ptr = &b;

	(*curr).next = malloc(sizeof(Node));
	curr = (*curr).next;
	(*curr).ptr = &c;

	(*curr).next = malloc(sizeof(Node));
	curr = (*curr).next;
	(*curr).ptr = &d;

	(*curr).next = malloc(sizeof(Node));
	curr = (*curr).next;
	(*curr).ptr = &e;

	(*curr).next = NULL;

	print_node(start,print);
	start = pq_enqueue(&start,&d,cmp);
	print_node(start,print_fn);
	Node* test_push = stack_push(&start,&f);
	print_node(test_push,print_fn);
	Node* remove = remove_last_node(&test_push);
	print_node(remove,print_fn);
	destroy_node(start,dest);
	//free(start);
	destroy_node(remove,dest);
	free(start);

	return EXIT_SUCCESS;
}
