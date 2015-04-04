/*
 * Application.cpp
 *
 *  Created on: 2014年12月
 *      Author: fanhao
 *      说明：
 *      http://ebaina.com/bbs/forum.php?mod=viewthread&tid=1646
 *   1 编写FrameSource的子类，封装来自cmos sensor的264数据。重写virtual void doGetNextFrame(),
 *   覆盖父类的virtual void doGetNextFrame(),父类的doGetNextFram()会被父类自动调用。子类要实现这个虚函数
 *   获得帧数据
 *   2 编写OnDemandServerMediaSubsession的子类，获得输入源。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "H264OnDemandServerMediaSubsession.h"
#include "V4L2FramedSource.h"

#include <live/liveMedia.hh>
#include <live/BasicUsageEnvironment.hh>
#include <live/UsageEnvironment.hh>
//主程序参照testOnDemandRTSPServer.h
UsageEnvironment* env;
static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
		char const* streamName, char const* inputFileName = "live"); // fwd
int main() {
	// 设置使用环境。Begin by setting up our usage environment:
	//1 创建任务调度器
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	//2 创建交互环境
	env = BasicUsageEnvironment::createNew(*scheduler);
	//3 控制权限代码，设置后无权限的客户端无法进行连接
	UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
	authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("frank","1202");	//这个鉴权要和客户端配合才能
#endif
	//4 创建RTSPServer 并且一直处于监听状态
	RTSPServer* rtspServer = RTSPServer::createNew(*env, 8557, authDB);
	if (rtspServer == NULL) {
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}
	char const* descriptionString =
			"Session streamed by \"testOnDemandRTSPServer\"";
	// 5 创建媒体会话
	char const* streamName = "live"; //流名字
	//媒体会话对会话描述、会话持续时间、流名字等与会话有关的信息进行管理
	ServerMediaSession* sms = ServerMediaSession::createNew(*env, streamName,
			streamName, descriptionString);
	//6 增加264子会话，这个地方和testOndemandRTSPServer不同。此处是将点播改为直播修改地方..
	sms->addSubsession(
			new H264OnDemandServerMediaSubsession(*env,
					new V4L2FramedSource(*env))); //new 一个类对象作用，获得一块内存空间，调用构造函数，返回正确的指针
	rtspServer->addServerMediaSession(sms);
	announceStream(rtspServer, sms, streamName);
	env->taskScheduler().doEventLoop(); // does not return

	return 0;
}
static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
		char const* streamName, char const* inputFileName) {
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env << "\n\"" << streamName << "\" stream, from the file \""
			<< inputFileName << "\"\n";
	env << "Play this stream using the URL \"" << url << "\"\n";
	delete[] url;
}
