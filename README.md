# dynamicbuf
dynamic fifo buffer

Example 1

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

  //get "aaa", data_len will be 3
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "bbbb", data_len will be 4
  dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); 

  //get "ccccc" without copying (fast) in on_get_no_copy function
  dynamic_buf_get_no_copy(&dynamic_buf, on_get_no_copy);

  //clear
  dynamic_buf_clear(&dynamic_buf);  
}
```

Example 2

```
#include "dynbuf.h"


static dynamic_buf_t dynamic_buf;

thread_write()
{
  int rc;
  socket s; 
  unsigned char buf[1600];
  dynamic_buf_t tmp_buf;
  size_t data_len;

  dynamic_buf_init(&tmp_buf);  //init tmp_buf

  ....

  while(true) {
    rc = read(s, buf, sizeof(buf)); //read data from socket
    if (rc < 1) {
      sleep(1);
      continue; //if no data -> wait
    }	
    if (dynamic_buf_get_busy(&dynamic_buf)) { //if dynamic_buf busy
       dynamic_buf_put(&tmp_buf, buf, rc); //write data to tmp_buf  
    } else {
       dynamic_buf_set_busy(&dynamic_buf, TRUE); //set busy flag
       while (dynamic_buf_get(&tmp_buf, buf, sizeof(buf), &data_len)) { //read data from tmp_buf
           dynamic_buf_put(&dynamic_buf, buf, data_len); //write data to dynamic_buf  	
       }	
       dynamic_buf_put(&dynamic_buf, buf, rc); //write data to dynamic_buf  
       dynamic_buf_set_busy(&dynamic_buf, FLASE); //unset busy flag
    }
  }

}

thread_read()
{
  size_t data_len;
  unsigned char buf[1600];

  ....

  while(true) {
    if (dynamic_buf_get_busy(&dynamic_buf)) {
       sleep(1);
       continue; //if dynamic_buf busy -> wait
    }
    dynamic_buf_set_busy(&dynamic_buf, TRUE); //set busy flag
    dynamic_buf_get(&dynamic_buf, buf, sizeof(buf), &data_len); //read data from dynamic_buf
    dynamic_buf_set_busy(&dynamic_buf, FLASE); //unset busy flag
    .....
  }

}

main()
{  
  dynamic_buf_init(&dynamic_buf);  //init dynamic_buf
  
  create_thread(thread_write);
  create_thread(thread_read);

  while(true) sleep(1000);
}
```