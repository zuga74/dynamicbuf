# dynamicbuf
dynamic fifo buffer

```
#include "dynbuf.h"


void on_get_no_copy(unsigned char * data, size_t data_len)
{
  //get data without copy
}

main()
{
  dynamic_buf_t dynamic_buf;
  char buf[128];
  size_t data_len;

  //init
  dynamic_buf_init(&dynamic_buf);

  //put "aaa"
  dynamic_buf_put(&dynamic_buf, "aaa", 3);

  //put "bbbb"
  dynamic_buf_put(&dynamic_buf, "bbbb", 4);

  //put "ccccc"
  dynamic_buf_put(&dynamic_buf, "ccccc", 5);

  //put "dddddd"
  dynamic_buf_put(&dynamic_buf, "dddddd", 6);

  //get "aaa"
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "bbbb"
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "cccc" without copying (fast) in on_get_no_copy function
  dynamic_buf_get_no_copy(&dynamic_buf, on_get_no_copy);

  //clear
  dynamic_buf_clear(&dynamic_buf);  
}
```