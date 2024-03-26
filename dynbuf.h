#ifndef dynbufH
#define dynbufH

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>


#ifndef BOOL
#define BOOL	unsigned char
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef NULL
#define NULL	0
#endif


struct dynamic_buf_item {

  struct dynamic_buf_item * next;

  size_t data_len;

  unsigned char data[];
};


typedef struct _dynamic_buf {
  struct dynamic_buf_item  * first;
  BOOL busy;
  size_t max_alloc_size;
  size_t alloc_size;
  size_t data_size;
  size_t count;
} dynamic_buf_t;

//init dynamic buffer
void dynamic_buf_init(dynamic_buf_t * dynamic_buf, size_t max_alloc_size);

//push data with size data_len
BOOL dynamic_buf_push(dynamic_buf_t * dynamic_buf, void * data, size_t data_len);

//pop data into buffer buff with buffer size buf_size, data_len - size of read data (FIFO)
BOOL dynamic_buf_pop(dynamic_buf_t * dynamic_buf, void * buf, size_t buf_size, size_t * data_len);

//clear dynamic buffer
void dynamic_buf_clear(dynamic_buf_t * dynamic_buf);

//is dynamic buffer empty
BOOL dynamic_buf_is_empty(dynamic_buf_t * dynamic_buf);

//get dynamic buffer count datas
size_t dynamic_buf_get_count(dynamic_buf_t * dynamic_buf);

//get dynamic buffer pointer to data from index
void * dynamic_buf_get_at(dynamic_buf_t * dynamic_buf, size_t index, size_t * data_len);

//delete dynamic buffer data from index
BOOL dynamic_buf_delete_at(dynamic_buf_t * dynamic_buf, size_t index);

//is dynamic buffer busy
BOOL dynamic_buf_get_busy(dynamic_buf_t * dynamic_buf);

//set dynamic buffer busy
void dynamic_buf_set_busy(dynamic_buf_t * dynamic_buf, BOOL value);

//get dynamic buffer data size
size_t dynamic_buf_get_data_size(dynamic_buf_t * dynamic_buf);

#ifdef __cplusplus
}
#endif

#endif
