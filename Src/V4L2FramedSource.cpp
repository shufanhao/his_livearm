/*
 * V4L2FramedSource.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: frank
 */

#include <V4L2FramedSource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fifo.h>
extern "C" {
//sample_venc.h是包含sample_venc.c程序的头文件
#include "sample_venc.h"
}
unsigned char fifo_data [1024*100] ;
int V4L2FramedSource::nalIndex = 0;

V4L2FramedSource::V4L2FramedSource(UsageEnvironment & env) :
		FramedSource(env) {
	mp_token = NULL;
	printf("creater\n");
	s32Ret = SAMPLE_VENC_720P_CLASSIC(); //相当于进行初始化  当用new class 的时候 构造函数会自动运行
	if (HI_SUCCESS == s32Ret)
		printf("init is success \n");
	else
		printf("init is not success\n");

}

V4L2FramedSource::~V4L2FramedSource() {
}

unsigned V4L2FramedSource::maxFrameSize() const {
	return 40 * 1024;//live555提供的Buffer的大小
}
void V4L2FramedSource::doGetNextFrame() {
	//HI_S32 s32ChnTotal = 3;
	VENC_CHN_ATTR_S stVencChnAttr; //获得编码通道属性
	HI_S32 maxfd = 0;
	struct timeval TimeoutVal;
	fd_set read_fds; //fd_set是一种数据结构,实际上是一long类型的数组,每一个数组元素都能与一打开的
	                 //文件句柄建立联系.
	HI_S32 VencFd[VENC_MAX_CHN_NUM];
	VENC_CHN_STAT_S stStat;	   //定义编码通道的状态结构体
	VENC_STREAM_S stStream;	   //码流结构体
	HI_S32 s32Ret;
	PAYLOAD_TYPE_E enPayLoadType[VENC_MAX_CHN_NUM];
	/**step 1:  check & prepare save-file & venc-fd
	******************************************/
	int i = 1 ; // only set 0(720p) , 1(vga)-640*480, 2(qvga) 320*240
	s32Ret = HI_MPI_VENC_GetChnAttr(i, &stVencChnAttr);
	if (s32Ret != HI_SUCCESS) {
		SAMPLE_PRT("HI_MPI_VENC_GetChnAttr chn[%d] failed with %#x!\n", i,
				s32Ret);
		// return NULL;
	}
	enPayLoadType[i] = stVencChnAttr.stVeAttr.enType;
	VencFd[i] = HI_MPI_VENC_GetFd(i);//将编码通道映射为一个文件句柄,获得这个句柄
	if (VencFd[i] < 0) {
		SAMPLE_PRT("HI_MPI_VENC_GetFd failed with %#x!\n", VencFd[i]);
		// return NULL;
	}
	if (maxfd <= VencFd[i]) {
		maxfd = VencFd[i];
	}
	/******************************************
	   step 2:  Start to get streams of each channel
	   应该是在这里循环这step 2 的代码
	 ******************************************/
	FD_ZERO(&read_fds);//将read_fd初始化为空集NULL
	FD_SET(VencFd[i], &read_fds);//向集合 read_fds添加描述字VencFd[i]，VencFd[i]就是获得的文件句柄
	//FD_SET结构来表示一组等待检查的套接口
	TimeoutVal.tv_sec = 2;
	TimeoutVal.tv_usec = 0;
	//select返回值 >0 就绪描述字的数目 -1出错 0 超时 http://blog.chinaunix.net/uid-21411227-id-1826874.html
	s32Ret = select(maxfd + 1, &read_fds, NULL, NULL, &TimeoutVal);
	if (s32Ret < 0) {
		SAMPLE_PRT("select failed!\n");
		//break;
	} else if (s32Ret == 0) {
		SAMPLE_PRT("get venc stream time out, exit thread 1\n");
		//continue;
	} else {
		   //测试VencFd[i]是否可读
		if (FD_ISSET(VencFd[i], &read_fds)) { //判断VencFd[0]是否在给定的描述符集read_fds中
			memset(&stStream, i, sizeof(stStream));	        //先赋值0
			/*
			 * step 2.1: 查询包的个数
			*/
			s32Ret = HI_MPI_VENC_Query(i, &stStat);	//stStat.u32CurPacks就是一个帧中pack的数量;
			//printf(" step2.1中包的数量是stStat.u32CurPacks=%d\n",stStat.u32CurPacks);	//输出包的数量 打印出来是4，那是不是一个帧中有四个nal单元呢
			if (HI_SUCCESS != s32Ret) {
				SAMPLE_PRT("HI_MPI_VENC_Query chn[%d] failed with %#x!\n", i,
						s32Ret);
				//break;
			}
			/*****************************************************
			 step 2.2 : malloc corresponding number of pack nodes.
			 *****************************************************/
			//pstPack是码流包信息指针，指向一组 VENC_PACK_S 的内存空间,该空间由调用者分配。如果是按包获
			//取,则此空间不小于 sizeof(VENC_PACK_S)的大小;如果按帧获取,则此
			//空间不小于 N × sizeof(VENC_PACK_S)的大小,其中 N 代表当前帧之中的
			//包的个数,可以在 select 之后通过查询接口获得。
			stStream.pstPack = (VENC_PACK_S*) malloc(
					sizeof(VENC_PACK_S) * stStat.u32CurPacks);//按帧获取
			if (NULL == stStream.pstPack) {
				SAMPLE_PRT("malloc stream pack failed!\n");
				//break;
			}

			/*****************************************************
			 step 2.3 : call mpi to get one-frame stream 获取一帧码流
			 *****************************************************/
			stStream.u32PackCount = stStat.u32CurPacks;	//将当前帧的码流包个数赋值给u32PackCount
			s32Ret = HI_MPI_VENC_GetStream(i, &stStream, HI_TRUE);
			if (HI_SUCCESS != s32Ret) {
				free(stStream.pstPack);
				stStream.pstPack = NULL;
				SAMPLE_PRT("HI_MPI_VENC_GetStream failed with %#x!\n", s32Ret);
				//break;
			}
			/*//这部分内容是通过一个fifo实现的。
			pFifoType priv = new FifoType;
			fFrameSize = 0;
			for(unsigned int j =0;j< stStream.u32PackCount;j++)
			{
				printf("len=%d",stStream.pstPack[j].u32Len[0]);
				for (int i = 0; i < 10; i++) {
					printf(" %02x", *(stStream.pstPack[j].pu8Addr[0]+ i));
				}
				printf("\n");
				printf("flag run");
				fifoctl(priv,stStream.pstPack[j].pu8Addr[0],stStream.pstPack[j].u32Len[0],WR);
				printf("step01\n");
				unsigned char *fifo_p;
				fifo_p = fifoctl(priv,fifo_data,stStream.pstPack[j].u32Len[0],RD);
				printf("step02\n");
				memmove(fTo + fFrameSize, fifo_p,stStream.pstPack[j].u32Len[0]);
				printf("step03\n");//
				fFrameSize += stStream.pstPack[j].u32Len[0];
			}
			delete priv;*/
			/*****************************************************
			 step 2.4 : 将获得的一帧码流去发送
			 *****************************************************/
			HI_U32 j;
			fFrameSize = 0;
			for (j = 0; j < stStream.u32PackCount; j++) {

				//printf("for1 stStream.pstPack[0].pu8Addr= %s\n",stStream.pstPack[i].pu8Addr[0]);
				memmove(fTo + fFrameSize, stStream.pstPack[j].pu8Addr[0],
						stStream.pstPack[j].u32Len[0]);  //
				fFrameSize += stStream.pstPack[j].u32Len[0]; //因为一开始有四个包。这个地方就循环四次。之前写成一个包了
				printf("for0 fFrameSize= %d\n", stStream.pstPack[j].u32Len[0]);
				//printf("for1 stStream->u32PackCount= %d\n",stStream.u32PackCount);
				for (int i = 0; i < 10; i++) {
					printf("%02x", *(stStream.pstPack[j].pu8Addr[0] + i));
				}
				if (stStream.pstPack[j].u32Len[1] > 0) {
					//printf("stStream->pstPack[i].pu8Addr1= %d\n",stStream.pstPack[j].u32Len[1]);
					memmove(fTo, stStream.pstPack[j].pu8Addr[1],
							stStream.pstPack[j].u32Len[1]);
					fFrameSize = stStream.pstPack[j].u32Len[1];
				}

			}
			//以上注释部分是在没有用fifo的时候
			//现在改用mkfifo
           /* unsigned char sendbuffer[2048*40];
            int fd;
            unlink("fifo");
            mkfifo("fifo",0777);
            pid_t fpid;
            fpid = fork();
            if(fpid > 0) //写
            {
            	for (int j = 0; j < stStream.u32PackCount; j++)
            	{
            		 fd = open("fifo", O_WRONLY);
            		 write(fd, stStream.pstPack[j].pu8Addr[0], stStream.pstPack[j].u32Len[0]);
            		 fFrameSize += stStream.pstPack[j].u32Len[0];

            	}
            	printf("frameSize=%d",fFrameSize);
            	::close(fd);

            }
            else if(fpid == 0)//读
            {
            	fd = open("fifo", O_RDONLY);
            	read(fd, sendbuffer,fFrameSize);
            	memmove(fTo, sendbuffer,fFrameSize);
            	for (int i = 0; i < 5; i++) {
            			printf(" %02x", sendbuffer);
            	}

            	::close(fd);
            }
			gettimeofday(&fPresentationTime, NULL);
			printf("time_sec: %ld",fPresentationTime.tv_sec);
			printf("time_usec: %ld\n",fPresentationTime.tv_usec);
			if (HI_SUCCESS != s32Ret) {
				free(stStream.pstPack);
				stStream.pstPack = NULL;
				SAMPLE_PRT("save stream failed!\n");
				//break;
			}*/
			/*****************************************************
			 step 2.5 : release stream
			 *****************************************************/
			s32Ret = HI_MPI_VENC_ReleaseStream(i, &stStream);
			if (HI_SUCCESS != s32Ret) {
				free(stStream.pstPack);
				stStream.pstPack = NULL;
				//break;
			}
			/*****************************************************
			 step 2.6 : free pack nodes
			 *****************************************************/
			free(stStream.pstPack);
			stStream.pstPack = NULL;
		}
	}
/*	gettimeofday(&fPresentationTime, NULL);//24个循环然后一秒，40.774ms，两个I帧之间的间距
	printf("over_time_sec: %ld",fPresentationTime.tv_sec);
	printf("over_time_usec: %ld\n",fPresentationTime.tv_usec);*/
	afterGetting(this);
}
