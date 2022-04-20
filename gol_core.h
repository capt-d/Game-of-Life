#ifndef GOL_H
#define GOL_H


#ifdef __cplusplus
extern "C" {
namespace NS_GoL {
#endif

#include <stddef.h>
#include <stdbool.h>

typedef unsigned int index;
typedef int bits;
typedef unsigned long long index_mtpl;

/* interface  -  call in this order*/ 
const bits** const init_board(index _cols, index _rows); // returns NULL on fail
const bits* const init_board_cont(index _cols, index _rows); // returns NULL on fail

unsigned int set_threads_count(index _count); // optional
void set_torus(bool); // optional 
index get_cols(void);

extern void (*next_cycle)(void);
extern void (*create)(float);
void destroy(void); // end of game, clean 

#ifdef __cplusplus
}// namespace NS_GoL
} 
#endif
#endif
