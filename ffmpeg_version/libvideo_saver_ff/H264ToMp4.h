#ifndef H264_TO_MP4_H
#define H264_TO_MP4_H

#include <string>

extern "C"
{
#include <libavformat/avformat.h>
};

class H264ToMp4
{
public:
	H264ToMp4();
	~H264ToMp4();

    int create_videoFile(const char* fileName, int width, int height, int frameRate);
	void add_frame(unsigned char* data, size_t dataLength);
	int finish_save_video();

private:
	AVStream* AddStream(AVFormatContext* formatCtx, AVCodec** codec, enum AVCodecID codec_id);
	bool isIdrFrame2(uint8_t* buf, int len);
	bool checkIfIFrame(uint8_t* buf, int size);


private:
	std::string m_strFileName;

	void* m_data;
	long m_len;

	AVFormatContext* m_fctx;
	int m_StreamIndex;
	int m_iGetFirstIFrame;

    int m_iTimeBase;

    int m_iVideWidth;
    int m_iVideoHeight;
    int m_iFrameRate;

	static bool m_bInitFFmpeg;
};


#endif // h264_to_mp4_h

