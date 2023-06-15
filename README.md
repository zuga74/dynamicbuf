# dynamicbuf
dynamic fifo buffer

```
#include "dynbuf.h"

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


  //get "aaa"
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "bbbb"
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //clear
  dynamic_buf_clear(&dynamic_buf);  
}
```