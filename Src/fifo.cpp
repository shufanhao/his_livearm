#include <iostream>
#include <string.h>
#include "fifo.h"
#include <stdio.h>
using namespace std;
 unsigned char *fifoctl(pFifoType priv , unsigned char data[] ,int fifo_len,const unsigned char flag)
 {
    unsigned char temp[BUFSIZE];
    //unsigned int widx = 0;
    //widx = priv->w_idx;
   // int len;/* Save the old index before proceeding */
    if (flag == WR) //write data

        {
    	/*for (int i = 0; i < 10; i++) {
    		printf("%02x", *(data+ i));//z这个地方打印出来的数据是000000016742001e95a8
    	}*/
        memcpy(priv->fifo_buffer,data,fifo_len);
        printf("fifo_len= %d",fifo_len);
        }
    else //read data

        {
        	unsigned char *p;
        	p = priv->fifo_buffer;
        	memcpy(temp,priv->fifo_buffer,fifo_len);
        	printf("read len = %d",fifo_len);
            priv->r_idx = (priv->r_idx + 1);
        }
     return temp;
 }
