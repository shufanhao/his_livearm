/*
 * H264OnDemandServerMediaSubsession.h
 *
 *  Created on: 2014年1月4日
 *      Author: ny
 */

#ifndef H264ONDEMANDSERVERMEDIASUBSESSION_H_
#define H264ONDEMANDSERVERMEDIASUBSESSION_H_

#include <live/OnDemandServerMediaSubsession.hh>
//继承自OnDemandServerMediaSubsession
class H264OnDemandServerMediaSubsession: public OnDemandServerMediaSubsession {
public:
	H264OnDemandServerMediaSubsession(UsageEnvironment & env,
			FramedSource *source);
	virtual ~H264OnDemandServerMediaSubsession();
protected:
	virtual const char *getAuxSDPLine(RTPSink *sink, FramedSource *source);
	virtual RTPSink *createNewRTPSink(Groupsock *rtpsock, unsigned char type,
			FramedSource *source);
	virtual FramedSource *createNewStreamSource(unsigned sid,
			unsigned &bitrate);
	virtual char const* sdpLines();

private:
	static void afterPlayingDummy(void *ptr) {
		((H264OnDemandServerMediaSubsession *) ptr)->m_done = 0xff;
	}
	static void chkForAuxSDPLine(void *ptr) {
		((H264OnDemandServerMediaSubsession *) ptr)->chkForAuxSDPLine1();
	}
	void chkForAuxSDPLine1();

private:
	FramedSource *mp_source;    // 对应 V4L2FramedSource
	char *mp_sdp_line;
	RTPSink *mp_dummy_rtpsink;
	char m_done;
};

#endif /* H264ONDEMANDSERVERMEDIASUBSESSION_H_ */
