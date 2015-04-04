/*
 * fifo.h
 *
 *  Created on: 2015年2月2日
 *      Author: frank
 */

#ifndef HEAD_FIFO_H_
#define HEAD_FIFO_H_
#define BUFSIZE 102400
#define WR 1 //写数据标志
#define RD 0 //读数据标志
typedef struct FifoType{
  unsigned char fifo_buffer[BUFSIZE];        /* Circular buffer */
  unsigned int w_idx;            /* Index of write */
  unsigned int r_idx;         /* Index of read */
 }*pFifoType;

unsigned char *fifoctl(pFifoType priv , unsigned char data[] ,int fifo_len,const unsigned char flag);


#endif /* HEAD_FIFO_H_ */
