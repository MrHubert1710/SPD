#ifndef __DEBUG_HPP
#define __DEBUG_HPP

#include <stdint.h>
#define OSTREAM_LISTA_DEBUG 0
#define SCHRAGE_DEBUG 0
#define SCHRAGE_PMTN_DEBUG 0

typedef struct {
uint16_t ID;
int16_t r;
int16_t p;
int16_t q;
} zadanie;

typedef struct node{
	zadanie data;
	struct node *link;
}node;


#endif // __DEBUG_HPP

