/*
 * H264OnDemandServerMediaSubsession.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */

#include <H264OnDemandServerMediaSubsession.h>
#include <live/H264VideoRTPSink.hh>
#include <live/H264VideoStreamFramer.hh>
#include <live/Media.hh>
#include <live/UsageEnvironment.hh>
#include <cstring>

//本部分代码类似live555的OnDemandServerMediaSubsession.cpp
//H264OnDemandServerMediaSubsession类主要是继承了OnDemandServerMediaSubsession类。
//主要是为了设置SDP 描述
H264OnDemandServerMediaSubsession::H264OnDemandServerMediaSubsession(
		UsageEnvironment& env, FramedSource * source) :
		OnDemandServerMediaSubsession(env, true) {
	mp_source = source;
	mp_sdp_line = NULL;
	mp_dummy_rtpsink = NULL;
	m_done = 0;
}

H264OnDemandServerMediaSubsession::~H264OnDemandServerMediaSubsession() {
}

void H264OnDemandServerMediaSubsession::chkForAuxSDPLine1() {
	if (mp_dummy_rtpsink->auxSDPLine())
		m_done = 0xff;
	else {
		int delay = 100 * 1000;   // 100ms
		nextTask() = envir().taskScheduler().scheduleDelayedTask(delay,
				chkForAuxSDPLine, this);
	}
}

const char * H264OnDemandServerMediaSubsession::getAuxSDPLine(RTPSink *sink,
		FramedSource *source) {
	if (mp_sdp_line)
		return mp_sdp_line;

	mp_dummy_rtpsink = sink;
	mp_dummy_rtpsink->startPlaying(*source, 0, 0);
	//mp_dummy_rtpsink->startPlaying(*source, afterPlayingDummy, this);
	chkForAuxSDPLine(this);
	m_done = 0;
	envir().taskScheduler().doEventLoop(&m_done);
	mp_sdp_line = strdup(mp_dummy_rtpsink->auxSDPLine());
	mp_dummy_rtpsink->stopPlaying();

	return mp_sdp_line;
}

RTPSink * H264OnDemandServerMediaSubsession::createNewRTPSink(
		Groupsock *rtpsock, unsigned char type, FramedSource *source) {
	return H264VideoRTPSink::createNew(envir(), rtpsock, type);
}

FramedSource * H264OnDemandServerMediaSubsession::createNewStreamSource(
		unsigned sid, unsigned &bitrate) {
	bitrate = 500;
	return H264VideoStreamFramer::createNew(envir(), mp_source);
}
char const* H264OnDemandServerMediaSubsession::sdpLines() {	//http://blog.csdn.net/zhangjikuan/article/details/27367437
//http://blog.csdn.net/zhangjikuan/article/details/27378237
//以下是对sdplines方法进行了重写，会话级描述已经写完，下面写的是媒体级描述
//1.m=是媒体级会话的开始处，video：媒体类型 ； o端口号    ；RTP/AVP：传输协议   ；96：rtp头中的payload格式
//a=rtpmap：证明是动态绑定的进一步说明    ；96：rtp头中的payload格式；H264：编码名 ；缺省了时钟速率，应该为90000,这里的90000是指1s采集90000个字节
//c=：媒体链接信息；IN：网络类型一般为IN；IP4：地址类型一般为IP4；后面是IP地址（注意是VLC所在的IP地址，不是发送方的IP）
	return fSDPLines =
			(char *) "m=video 0 RTP/AVP 96\r\n"
					"c=IN IP4 0.0.0.0\r\n"
					"b=AS:96\r\n"
					"a=rtpmap:96 H264/90000\r\n"
					"a=fmtp:96 packetization-mode=1;profile-level-id=000000;sprop-parameter-sets=H264\r\n"
					"a=control:track1\r\n";
}
