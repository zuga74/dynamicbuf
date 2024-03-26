# dynamicbuf
dynamic fifo buffer

Example

```
#include "dynbuf.h"



main()
{
  dynamic_buf_t dynamic_buf;
  char buf[128];
  size_t data_len, i;
  void * data;

  //init
  dynamic_buf_init(&dynamic_buf);

  //put "aaa"
  dynamic_buf_push(&dynamic_buf, "aaa", 3);

  //put "bbbb"
  dynamic_buf_push(&dynamic_buf, "bbbb", 4);

  //put "ccccc"
  dynamic_buf_push(&dynamic_buf, "ccccc", 5);

  //put "dddddd"
  dynamic_buf_push(&dynamic_buf, "dddddd", 6);

  //get "aaa", data_len will be 3
  dynamic_buf_pop(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "bbbb", data_len will be 4
  dynamic_buf_pop(&dynamic_buf, buf, sizeof(buf), &data_len); 


  for (i = 0; i < dynamic_buf_get_count(&dynamic_buf); ++i) {
	//get "ccccc", get "dddddd"	
  	data = dynamic_buf_get_at(&dynamic_buf, i, &data_len);
  }

  //clear
  dynamic_buf_clear(&dynamic_buf);  
}
```

