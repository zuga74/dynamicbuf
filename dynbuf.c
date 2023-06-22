#include "dynbuf.h"
#include <string.h>



void dynamic_buf_init(dynamic_buf_t * dynamic_buf)
{
  dynamic_buf->first = NULL;
  dynamic_buf->busy = FALSE;
}

BOOL dynamic_buf_put(dynamic_buf_t * dynamic_buf, void * data, size_t data_len)
{
  struct dynamic_buf_item  * item;


  if (dynamic_buf->first) {
     item = dynamic_buf->first;
     while (item->next) {
       item = item->next;
     }
     item->next = (struct dynamic_buf_item  *)malloc(sizeof(struct dynamic_buf_item) + data_len);
     item = item->next;
  }
  else {
     dynamic_buf->first = (struct dynamic_buf_item  *)malloc(sizeof(struct dynamic_buf_item) + data_len);
     item = dynamic_buf->first;
  }

  if (!item) {
       return FALSE;
  }

  memcpy(item->data, data, data_len);
  item->data_len = data_len;
  item->next = NULL;
  return TRUE;
}

BOOL dynamic_buf_get(dynamic_buf_t * dynamic_buf, void * buf, size_t buf_size, size_t * data_len)
{
  struct dynamic_buf_item  * item;

  *data_len = 0;

  if (!dynamic_buf->first) return FALSE;

  *data_len = dynamic_buf->first->data_len > buf_size ? buf_size : dynamic_buf->first->data_len;
  memcpy(buf, dynamic_buf->first->data, *data_len);
  item = dynamic_buf->first->next;
  free(dynamic_buf->first);
  dynamic_buf->first = item;
  return TRUE;
}


BOOL dynamic_buf_get_no_copy(dynamic_buf_t * dynamic_buf, dynamic_buf_proc_t proc)
{
  struct dynamic_buf_item  * item;

  if (!dynamic_buf->first || !proc) return FALSE;


  proc(dynamic_buf->first->data, dynamic_buf->first->data_len);

  item = dynamic_buf->first->next;
  free(dynamic_buf->first);
  dynamic_buf->first = item;
  return TRUE;
}



void dynamic_buf_clear(dynamic_buf_t * dynamic_buf)
{
  struct dynamic_buf_item  * item, * next;

  if (!dynamic_buf->first) return;

  item = dynamic_buf->first;
  while (item) {
     next = item->next;
     free(item);
     item = next;
  }
  dynamic_buf->first = NULL;
}



BOOL dynamic_buf_enum(dynamic_buf_t * dynamic_buf, dynamic_buf_proc_t proc)
{
  struct dynamic_buf_item  * item;

  if (!dynamic_buf->first || !proc) return FALSE;

  item = dynamic_buf->first;
  while (item) {
     proc(item->data, item->data_len);
     item = item->next;
  }

  return TRUE;
}

BOOL dynamic_buf_is_empty(dynamic_buf_t * dynamic_buf)
{
   return dynamic_buf->first == NULL;
}

BOOL dynamic_buf_get_busy(dynamic_buf_t * dynamic_buf)
{
   return dynamic_buf->busy;
}

void dynamic_buf_set_busy(dynamic_buf_t * dynamic_buf, BOOL value)
{
	dynamic_buf->busy = value;
}
