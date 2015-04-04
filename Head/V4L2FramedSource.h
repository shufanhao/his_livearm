/*
 * V4L2FramedSource.h
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */

#ifndef V4L2FRAMEDSOURCE_H_
#define V4L2FRAMEDSOURCE_H_

#include <live/FramedSource.hh>
#include <live/UsageEnvironment.hh>
extern "C" {
#include <hi_include/sample_comm.h>
#include "sample_venc.h"
}
class V4L2FramedSource: public FramedSource {
public:
	V4L2FramedSource(UsageEnvironment & env);
	virtual ~V4L2FramedSource();
protected:
	virtual void doGetNextFrame();
	virtual unsigned maxFrameSize() const; //const型只允许引用。不允许修改
	//void getenSizeStream(int i);
private:
	/*static void getNextFrame(void *ptr)
	 {
	 ((V4L2FramedSource *) ptr)->getNextFrame1();
	 }
	 void getNextFrame1();*/

private:
	//V4L2 * v4l2;
	//H264Encode *pEncode;
	//AVPicture Picture;
	void * mp_token;
	HI_S32 s32Ret;
	static int nalIndex;

};

#endif /* V4L2FRAMEDSOURCE_H_ */
