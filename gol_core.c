#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "gol_core.h"
#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>

/* NOP function */
static void nop_next_cycle(void){ return; }
static void nop_create(float _percent){ return; }
/* do it function */
static void do_next_cycle(void); 
static void do_create(float _percent);

/* interface */
void (*next_cycle)(void) = nop_next_cycle;
void (*create)(float) = nop_create;

/* working functions */ 
static void center(void* _params); // range_t casted 
static void left_and_right(void);
static void frame(void);
static void set_ranges(void);
static void* threaded_center(void* _params); 
static void single_counting(void);
static void multi_counting(void);
static bool do_allocate(index _cols, index _rows);

static index cols; //bits count  
static index rows;
static index ints_cols; //ints needed 

// for last column alive condition checking
static index last_col; 

static bits *bits_memory = NULL;

static bits **board = NULL; 
static bits **changes = NULL;

static void (*rest)(void); // frame's bit's states counting  
static void (*counting)(void) = single_counting; 

static void *threads_memory = NULL;
static pthread_t *threads = NULL;
static unsigned int threads_count = 0; //  counting threads
static index threads_cols = 0;
static index threads_rows = 0;

typedef struct 
{
  index first_col;
  index first_row;
  index last_col;
  index last_row;
  sem_t main_sem;
  sem_t thread_sem;
} threads_data_t; // range for center counting (with or without threads)

static threads_data_t *ranges = NULL;
static threads_data_t single_range; //for non-threaded and for set_ranges() with threads

static pthread_mutex_t cycle_mutex = PTHREAD_MUTEX_INITIALIZER;

static const unsigned int BITS_WIDTH = sizeof(bits) * CHAR_BIT;

static unsigned int last_bit;
static unsigned int pre_last_bit;

const bits* const init_board_cont(index _cols, index _rows)
{
 if(!do_allocate(_cols, _rows))
    return NULL;
  return (const bits* const)(bits_memory);
}

const bits** const init_board(index _cols, index _rows)
{
  if(!do_allocate(_cols, _rows))
    return NULL;
  return (const bits** const)(board + 1);
}  
  
static bool do_allocate(index _cols, index _rows)
{
  if (_cols == 0 || _rows == 0)
    return false;
  if (bits_memory)
    return true;
  ints_cols = ceil((double) _cols / BITS_WIDTH);
  cols = ints_cols * BITS_WIDTH; 
  rows = _rows;
  bits_memory =  calloc(2, rows * ints_cols * sizeof(bits) + sizeof(bits*) * (rows + 1));
  if (bits_memory == NULL)
    return false;
 
  board = (bits**)&bits_memory[2 * ints_cols * rows];
  changes = &board[rows + 2];
  for (index i = 1; i <= rows; i++)
  {
    board[i] = &bits_memory[(i - 1) * ints_cols];
    changes[i - 1] = &(bits_memory[ints_cols * rows + (i - 1) * ints_cols]);
  }
  board[0] = &bits_memory[(rows - 1) * ints_cols];
  board[rows + 1] = board[1];

  last_col = ints_cols - 1;
  
  single_range.first_col = 1;
  single_range.last_col = cols - 2;
  
  next_cycle = &do_next_cycle;
  create = &do_create;
  last_bit = (1 << (BITS_WIDTH - 1));
  pre_last_bit = (1 << (BITS_WIDTH - 2));
  set_torus(false);
  return true;
}

void do_create(float _percent)
{
  if (board == NULL)
    return;
  srand(time(NULL));
  if (_percent <= 0 || _percent >= 100)
    _percent = (float) (rand() / (RAND_MAX + 1.0) * 100);
  index alive_row = 0;
  index alive_col = 0;
  _percent /= 100;
  index_mtpl p = cols  * (rows * _percent);
  for (index_mtpl i = 0; i < p; i++)
  {    
    alive_col = (index) (rand() / (RAND_MAX + 1.0) * cols);
    alive_row = (index) (rand() / (RAND_MAX + 1.0) * rows);
    if ((board[alive_row + 1][alive_col / BITS_WIDTH]) & (1 << (alive_col % BITS_WIDTH)))  
      i--;
    else
      board[alive_row + 1][alive_col / BITS_WIDTH] |= (1 << (alive_col % BITS_WIDTH));	
  }
  create = &nop_create;
}

static void do_next_cycle(void) 
{ 
  pthread_mutex_lock(&cycle_mutex);
  for (index i = 0; i < rows; i++)
    for (index j = 0; j < ints_cols; j++)    
      changes[i][j] = 0;
  counting(); 
  for (index i = 1; i <= rows; i++)
    for (index j = 0; j < ints_cols; j++)
      board[i][j] ^= changes[i - 1][j];
  pthread_mutex_unlock(&cycle_mutex);
}

void set_torus(bool _on)
{
  pthread_mutex_lock(&cycle_mutex);
  if (_on)
  { 
    single_range.first_row = 1;
    single_range.last_row = rows;
    rest = &left_and_right;
  }
  else
  {
    single_range.first_row = 2;
    single_range.last_row = rows - 1;
    rest = &frame;
  } 
  set_ranges();
  pthread_mutex_unlock(&cycle_mutex);
}

void destroy(void)
{
  set_threads_count(0);
  if (bits_memory != NULL)
    free(bits_memory);
  bits_memory = NULL;
  next_cycle = &nop_next_cycle;
  create = &do_create;
}

unsigned int set_threads_count(unsigned int _count)
{
  if (_count == threads_count)
    return threads_count;
  if(threads_count)
  {
    pthread_mutex_lock(&cycle_mutex);
    for (unsigned int i = 0; i < threads_count; i++)
    {
      pthread_cancel(threads[i]); 
      sem_destroy(&ranges[i].thread_sem);	
      sem_destroy(&ranges[i].main_sem);
    }
    threads_count = 0;
    threads_cols = 0;
    threads_rows = 0;
    free(threads_memory);
    threads_memory = NULL;
    threads = NULL;
    ranges = NULL;
    counting = &single_counting;
    pthread_mutex_unlock(&cycle_mutex);
  }
  if(_count == 0)
    return 0; 

  pthread_mutex_lock(&cycle_mutex);
  threads_cols = sqrt(_count);
  threads_rows = _count / threads_cols;
  threads_count = threads_cols * threads_rows;
  threads_memory = calloc(threads_count, sizeof(threads_data_t) + sizeof(pthread_t));
  if (threads_memory == NULL)
  {
    threads_cols = 0;
    threads_rows = 0;
    return 0;
  }
  threads = (pthread_t*)threads_memory; 
  ranges = (threads_data_t*)&threads[threads_count]; 

  for (unsigned int i = 0; i < threads_count; i++)
  {
    sem_init(&ranges[i].main_sem,0,0);
    sem_init(&ranges[i].thread_sem,0,0);
    if(pthread_create(&threads[i], NULL, &threaded_center, &ranges[i]))
    {
      sem_destroy(&ranges[i].thread_sem);	
      sem_destroy(&ranges[i].main_sem);
      i--;
      threads_cols = sqrt(i);
      threads_rows = i / threads_cols;
      threads_count = threads_cols * threads_rows;
      for (unsigned int ii = i; ii >= threads_count; ii--)
      {
        pthread_cancel(threads[ii]); 
        sem_destroy(&ranges[ii].thread_sem);	
        sem_destroy(&ranges[ii].main_sem);
      }
      break;
    }
  }

  set_ranges();
  counting = multi_counting;
  pthread_mutex_unlock(&cycle_mutex);
  return threads_count; 
}

index get_cols(void) { return cols;}

static void set_ranges(void)
{
  if(threads_count == 0) 
    return;
  index bits_per_col = (single_range.last_col - single_range.first_col) / threads_cols;
  index bits_per_row = (single_range.last_row - single_range.first_row) / threads_rows;
  index rest_cols = (single_range.last_col - single_range.first_col) % threads_cols;
  index rest_rows = (single_range.last_row - single_range.first_row) % threads_rows;
  
  for (index i = 0; i < rest_cols; i++)
  {
    ranges[i].first_col = single_range.first_col + i * (bits_per_col + 1);
    ranges[i].last_col = ranges[i].first_col + bits_per_col;
    for (index j = 0; j < rest_rows; j++)
    {
      ranges[j * threads_cols + i].first_col = ranges[i].first_col;
      ranges[j * threads_cols + i].last_col = ranges[i].last_col;
      ranges[j * threads_cols + i].first_row = single_range.first_row + j * (bits_per_row + 1);
      ranges[j * threads_cols + i].last_row = ranges[j * threads_cols + i].first_row + bits_per_row;
    }
    for (index j = rest_rows; j < threads_rows; j++)
    {
      ranges[j * threads_cols + i].first_col = ranges[i].first_col; 
      ranges[j * threads_cols + i].last_col = ranges[i].last_col;
      ranges[j * threads_cols + i].first_row = single_range.first_row + rest_rows * (bits_per_row + 1) + (j - rest_rows) * bits_per_row;
      ranges[j * threads_cols + i].last_row = ranges[j * threads_cols + i].first_row + bits_per_row - 1;
    }
  }	
  for (index i = rest_cols; i < threads_cols; i++)
  {
    ranges[i].first_col = single_range.first_col + rest_cols * (bits_per_col + 1) + (i - rest_cols) * bits_per_col;
    ranges[i].last_col = ranges[i].first_col + bits_per_col - 1;
    for (index j = 0; j < rest_rows; j++)
    {
      ranges[j * threads_cols + i].first_col = ranges[i].first_col;
      ranges[j * threads_cols + i].last_col =  ranges[i].last_col;
      ranges[j * threads_cols + i].first_row = single_range.first_row + j * (bits_per_row + 1);
      ranges[j * threads_cols + i].last_row = ranges[j * threads_cols + i].first_row + bits_per_row;
    }
    for (index j = rest_rows; j < threads_rows; j++)
    {
      ranges[j * threads_cols + i].first_col = ranges[i].first_col; 
      ranges[j * threads_cols + i].last_col = ranges[i].last_col;
      ranges[j * threads_cols + i].first_row = single_range.first_row + rest_rows * (bits_per_row + 1) + (j - rest_rows) * bits_per_row;
      ranges[j * threads_cols + i].last_row = ranges[j * threads_cols + i].first_row + bits_per_row - 1;
    }
  }
}

static void center(void *_params)
{
//center part
  threads_data_t *params = (threads_data_t*) _params;
  index act_col = params->first_col / BITS_WIDTH;
  index act_bit = params->first_col % BITS_WIDTH;
  index prev_col = (params->first_col - 1) / BITS_WIDTH;
  index prev_bit = (params->first_col - 1) % BITS_WIDTH;
  for (index i = params->first_col; i <= params->last_col; i++)
  {
    index next_col = (i + 1) / BITS_WIDTH;
    index next_bit = (i + 1) % BITS_WIDTH;
    for (index j = params->first_row; j <= params->last_row; j++)
    {
      unsigned int count = 0;
      count += 1 && (board[j - 1][act_col] & (1 << act_bit));  
      count += 1 && (board[j - 1][prev_col] & (1 << prev_bit));
      count += 1 && (board[j][prev_col] & (1 << prev_bit)); 
      count += 1 && (board[j + 1][prev_col] & (1 << prev_bit)); 
      count += 1 && (board[j + 1][act_col] & (1 << act_bit)); 
      count += 1 && (board[j + 1][next_col] & (1 << next_bit)); 
      count += 1 && (board[j][next_col] & (1 << next_bit));
      count += 1 && (board[j - 1][next_col] & (1 << next_bit));
         
      if ((board[j][act_col] & (1 << act_bit)) != 0)
      {
        if (count < 2 || count > 3)
	  changes[j - 1][act_col] |= (1 << act_bit);
      }
      else 
        if (count == 3) 
	    changes[j - 1][act_col] |= (1 << act_bit);
    }
    prev_bit = act_bit;
    prev_col = act_col;
    act_bit = next_bit;
    act_col = next_col;
  }
}

static void frame(void)
{
 // (top left)  
  unsigned int count = 0;
  count += 1 && (board[2][0] & (1 << 0));
  count += 1 && (board[2][0] & (1 << 1));
  count += 1 && (board[1][0] & (1 << 1));
  if (board[1][0] & (1 << 0)) 
  {
    if(count < 2)
      changes[0][0] |= (1 << 0);
  }
  else
    if (count == 3)
      changes[0][0] |= (1 << 0);
  
  // first and last columns w/o first and last (corners)
  for (index i = 2; i <= rows - 1; i++)
  { 	
    count = 0;
    count += 1 && (board[i - 1][0] & (1 << 0));
    count += 1 && (board[i - 1][0] & (1 << 1));
    count += 1 && (board[i + 1][0] & (1 << 0));
    count += 1 && (board[i + 1][0] & (1 << 1));
    count += 1 && (board[i][0] & (1 << 1));
    if (board[i][0] & (1 << 0)) 
    {
      if(count < 2 || count > 3)
        changes[i - 1][0] |= (1 << 0);
    }
    else
      if (count == 3)
        changes[i - 1][0] |= (1 << 0);
    
    count = 0;
    count += 1 && board[i - 1][last_col] & last_bit;
    count += 1 && board[i - 1][last_col] & pre_last_bit;
    count += 1 && board[i + 1][last_col] & last_bit;
    count += 1 && board[i + 1][last_col] & pre_last_bit;
    count += 1 && board[i][last_col] & pre_last_bit;
    if ((board[i][last_col] & last_bit) != 0)
    {
      if (count < 2 || count > 3)
        changes[i - 1][last_col] |= last_bit;
    }
    else 
      if (count == 3)
        changes[i - 1][last_col] |= last_bit;
  }

// (bottom left)
  count = 0;
  count += 1 && (board[rows - 1][0] & (1 << 0));
  count += 1 && (board[rows - 1][0] & (1 << 1));
  count += 1 && (board[rows][0] & (1 << 1));
  if (board[rows][0] & (1 << 0))
  {
    if (count << 2)
      changes[rows - 1][0] |= (1 << 0);
  }		
  else 
    if (count == 3)
      changes[rows - 1][0] |= (1 << 0);

  // (top right)
  count = 0;
  count += 1 && (board[1][last_col] & pre_last_bit);
  count += 1 && (board[2][last_col] & last_bit);
  count += 1 && (board[2][last_col] & pre_last_bit);
  if (board[1][last_col] & last_bit)
  {
    if (count < 2)
       changes[0][last_col] |= last_bit;
  }
  else
    if (count == 3)
      changes[0][last_col] |= last_bit;

  //first and last lines
  index act_col = 0;
  index act_bit = 1;
  index prev_col = 0;
  index prev_bit = 0;
  index next_col;    
  index next_bit;
  
  for (index i = 1; i < cols; i++)
  { 	
    count = 0;
    next_col = (i + 1) / BITS_WIDTH;
    next_bit = (i + 1) % BITS_WIDTH;
    
    count += 1 && (board[1][prev_col] & (1 << prev_bit));
    count += 1 && (board[2][prev_col] & (1 << prev_bit));
    count += 1 && (board[2][act_col] & (1 << act_bit));
    count += 1 && (board[2][next_col] & (1 << next_bit));
    count += 1 && (board[1][next_col] & (1 << next_bit));
    if (board[1][act_col] & (1 << act_bit))
    {
      if (count < 2 || count > 3)
        changes[0][act_col] |= (1 << act_bit);
    }
    else
      if (count == 3)
        changes[0][act_col] |= (1 << act_bit); 
    
    count = 0;
    count += 1 && (board[rows][prev_col] & (1 << prev_bit));
    count += 1 && (board[rows - 1][prev_col] & (1 << prev_bit));
    count += 1 && (board[rows - 1][act_col] & (1 << act_bit));
    count += 1 && (board[rows - 1][next_col] & (1 << next_bit));
    count += 1 && (board[rows][next_col] & (1 << next_bit));
    if (board[rows][act_col] & (1 << act_bit)) 
    {
      if (count < 2 || count > 3)
        changes[rows - 1][act_col] |= (1 << act_bit);
    } 
    else
      if (count == 3)
          changes[rows - 1][act_col] |= (1 << act_bit);
    
    prev_bit = act_bit;
    prev_col = act_col;
    act_bit = next_bit;
    act_col = next_col;
  }

// (bottom right)
  count = 0;
  count += 1 && (board[rows][last_col] & pre_last_bit);
  count += 1 && (board[rows - 1][last_col] & pre_last_bit);
  count += 1 && (board[rows - 1][last_col] & last_bit);
  if(board[rows][last_col] & last_bit)
  {
    if(count < 2)
      changes[rows - 1][last_col] |= last_bit;
  }
  else
    if (count == 3)
      changes[rows - 1][last_col] |= last_bit;
}

static void left_and_right(void)
{  
  index count;	
// first and last columns 
  for (index i = 1; i <= rows; i++)
  { 	
    count = 0;
    count += 1 && (board[i - 1][0] & (1 << 0));
    count += 1 && (board[i - 1][0] & (1 << 1));
    count += 1 && (board[i - 1][last_col] & last_bit);
    count += 1 && (board[i + 1][0] & (1 << 0));
    count += 1 && (board[i + 1][0] & (1 << 1));
    count += 1 && (board[i + 1][last_col] & last_bit);
    count += 1 && (board[i][last_col] & last_bit);
    count += 1 && (board[i][0] & (1 << 1));
    if (board[i][0] & (1 << 0))
    {
      if (count < 2 || count > 3)
        changes[i - 1][0] |= (1 << 0);
    }
    else 
      if (count == 3)
        changes[i - 1][0] |= (1 << 0);
    
    count = 0;
    count += 1 && (board[i - 1][last_col] & last_bit);
    count += 1 && (board[i - 1][last_col] & pre_last_bit);
    count += 1 && (board[i - 1][0] & (1 << 0));
    count += 1 && (board[i + 1][last_col] & last_bit);
    count += 1 && (board[i + 1][last_col] & pre_last_bit);
    count += 1 && (board[i + 1][0] & (1 << 0));
    count += 1 && (board[i][last_col] & pre_last_bit);
    count += 1 && (board[i][0] & (1 << 0));
    if (board[i][last_col] & last_bit)
    {
      if (count < 2 || count > 3)
        changes[i - 1][last_col] |= last_bit; 
    }
    else
      if (count == 3)
        changes[i - 1][last_col] |= last_bit;	
  }  
}

static void* threaded_center(void *_param)
{
  threads_data_t *dane = (threads_data_t*) _param;
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  while(1)
  {
    sem_wait(&dane->thread_sem);
    center(dane);
    sem_post(&dane->main_sem);
  }
  return NULL;
}

static void single_counting(void)
{
  center(&single_range);
  rest();
}

static void multi_counting(void)
{
  for (unsigned int i = 0; i < threads_count; i++)
    sem_post(&ranges[i].thread_sem);
  rest();
  for (unsigned int i = 0; i < threads_count; i++)
    sem_wait(&ranges[i].main_sem); 
}

