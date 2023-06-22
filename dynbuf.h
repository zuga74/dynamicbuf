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
} dynamic_buf_t;

typedef void (* dynamic_buf_proc_t)(void * data, size_t data_len);

//init dynamic buffer
void dynamic_buf_init(dynamic_buf_t * dynamic_buf);

//put data with size date_len
BOOL dynamic_buf_put(dynamic_buf_t * dynamic_buf, void * data, size_t data_len);

//get data into buffer buff with buffer size buf_size, data_len - size of read data
BOOL dynamic_buf_get(dynamic_buf_t * dynamic_buf, void * buf, size_t buf_size, size_t * data_len);

//get data without copying into function proc
BOOL dynamic_buf_get_no_copy(dynamic_buf_t * dynamic_buf, dynamic_buf_proc_t proc);

//clear dynamic buffer
void dynamic_buf_clear(dynamic_buf_t * dynamic_buf);

//is dynamic buffer empty
BOOL dynamic_buf_is_empty(dynamic_buf_t * dynamic_buf);

//enumeration of a dynamic buffer into a function proc
BOOL dynamic_buf_enum(dynamic_buf_t * dynamic_buf, dynamic_buf_proc_t proc);

//is dynamic buffer busy
BOOL dynamic_buf_get_busy(dynamic_buf_t * dynamic_buf);

//set dynamic buffer busy
void dynamic_buf_set_busy(dynamic_buf_t * dynamic_buf, BOOL value);

#ifdef __cplusplus
}
#endif

#endif