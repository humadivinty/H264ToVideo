#include "H264ToMp4.h"
#include "Tool_function.h"
using namespace video_saver_ffmpeg;

bool H264ToMp4::m_bInitFFmpeg = false;

H264ToMp4::H264ToMp4()
{
	m_data = NULL;
	m_len = 0;

	m_fctx = NULL;
	m_StreamIndex = -1;
	m_iGetFirstIFrame = 0;

    m_iVideWidth = 1920;
    m_iVideoHeight = 1080;
    m_iFrameRate = 25;

	if (!m_bInitFFmpeg)
	{
#ifndef FFMPEG_VERSION_4
        OUT_LOG("av_register_all");
        av_register_all();
#endif
		m_bInitFFmpeg = true;
	}
}

H264ToMp4::~H264ToMp4()
{

}

int H264ToMp4::create_videoFile(const char* fileName, int width, int height, int frameRate)
{
	if (NULL == fileName)
	{
		OUT_LOG("NULL == fileName");
		return -1;
	}
	int ret;
	AVOutputFormat* pAvoutputFmt = NULL;
	AVCodec* video_codec = NULL;
	AVStream* pAvStream_video = NULL;

    m_iTimeBase = 0;
    m_iVideWidth = width;
    m_iVideoHeight = height;
    m_iFrameRate = frameRate;

	avformat_alloc_output_context2(&m_fctx, NULL, NULL, fileName);
	if (NULL == m_fctx)
	{
		avformat_alloc_output_context2(&m_fctx, NULL, NULL, fileName);
	}
 	if (NULL == m_fctx)
	{
		OUT_LOG("avformat_alloc_output_context2 failed.");
		return -1;
	}
    else
    {
        OUT_LOG("avformat_alloc_output_context2 success.");
    }
	pAvoutputFmt = m_fctx->oformat;
	if (pAvoutputFmt->video_codec != AV_CODEC_ID_NONE)
	{
		pAvStream_video = AddStream(m_fctx, &video_codec, pAvoutputFmt->video_codec);
	}
	if (pAvStream_video)
	{
        ret = avcodec_open2(pAvStream_video->codec, video_codec, NULL);
        OUT_LOG("add stream success, avcodec_open2(%d) = %d", pAvStream_video->codec, ret);
	}
	else
	{
		OUT_LOG("create avStream failed.");
	}
    av_dump_format(m_fctx, 0, fileName, 1);

	if (!(pAvoutputFmt->flags & AVFMT_NOFILE))
	{
        OUT_LOG("avio_open begin.");
		ret = avio_open(&m_fctx->pb, fileName, AVIO_FLAG_WRITE);
		if (ret < 0)
		{
			OUT_LOG("avio_open failed.");
			return -1;
		}
        OUT_LOG("avio_open = %d.", ret);
	}
    OUT_LOG("avio_open begin.");
	ret = avformat_write_header(m_fctx, NULL);
	if (ret < 0)
	{
        OUT_LOG("avformat_write_header failed, ret = %d.", ret);
		return -1;
	}

	return 0;
}

void H264ToMp4::add_frame(unsigned char* data, size_t dataLength)
{
	if (-1 == m_StreamIndex)
	{
		OUT_LOG("can not find stream index.");
		return;
	}
	AVStream* pAvStream_video = m_fctx->streams[m_StreamIndex];
	AVPacket pkt;

	av_init_packet(&pkt);
	int isIFrame = checkIfIFrame(data, dataLength);

	pkt.flags |= isIFrame ? AV_PKT_FLAG_KEY : 0;
	pkt.stream_index = pAvStream_video->index;
	pkt.data = data;
	pkt.size = dataLength;

	if (!m_iGetFirstIFrame)
	{
		if (0 == (pkt.flags & AV_PKT_FLAG_KEY))
		{
			return;
		}
		else
		{
			m_iGetFirstIFrame = 1;
		}
	}

    //int ptsInc = 0;
	int STREAM_FRAME_RATE = 25;

    pkt.pts = (m_iTimeBase++) * (90000 / STREAM_FRAME_RATE);
    //pkt.pts = av_rescale_q((m_iTimeBase++) * 2, pAvStream_video->codec->time_base, pAvStream_video->time_base);
	pkt.dts = av_rescale_q_rnd(pkt.dts, pAvStream_video->time_base, pAvStream_video->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	pkt.duration = av_rescale_q(pkt.duration, pAvStream_video->time_base, pAvStream_video->time_base);
	pkt.pos = -1;

	av_interleaved_write_frame(m_fctx, &pkt);
	//av_write_frame(m_fctx, &pkt);
}

int H264ToMp4::finish_save_video()
{
    m_iTimeBase = 0;
	m_iGetFirstIFrame = 0;
	m_StreamIndex = -1;

	if (m_fctx)
	{
		av_write_trailer(m_fctx);
	}
		
	if (m_fctx && !(m_fctx->oformat->flags & AVFMT_NOFILE))
	{
		avio_close(m_fctx->pb);
	}

	if (m_fctx)
	{
		avformat_free_context(m_fctx);
		m_fctx = NULL;
	}
	return 0;
}

AVStream* H264ToMp4::AddStream(AVFormatContext* formatCtx, AVCodec** codec, enum AVCodecID codec_id)
{
    OUT_LOG("formatCtx = %p, codec_id = %d", formatCtx, codec_id);
	AVCodecContext* pAvCodecContex = NULL;
	AVStream* pAvStream = NULL;

	*codec = avcodec_find_encoder(codec_id);
	if (NULL == *codec)
	{
		OUT_LOG("input  *AVCodec == NULL.");
		return NULL;
	}

	pAvStream = avformat_new_stream(formatCtx, *codec);
	if (NULL == pAvStream)
	{
		OUT_LOG("avformat_new_stream failed.");
		return NULL;
	}

	pAvStream->id = formatCtx->nb_streams - 1;
	pAvCodecContex = pAvStream->codec;
	m_StreamIndex = pAvStream->index;

	switch ((*codec)->type)
	{
	case AVMEDIA_TYPE_AUDIO:
        OUT_LOG("case AVMEDIA_TYPE_AUDIO.");
		pAvCodecContex->sample_fmt = (*codec)->sample_fmts ? (*codec)->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
		pAvCodecContex->bit_rate = 64000;
		pAvCodecContex->sample_rate = 44100;
		pAvCodecContex->channels = 2;
		break;
	case AVMEDIA_TYPE_VIDEO:
        OUT_LOG("case AVMEDIA_TYPE_VIDEO.");
		pAvCodecContex->codec_id = AV_CODEC_ID_H264;
		pAvCodecContex->bit_rate = 0;
        pAvCodecContex->width = m_iVideWidth;
        pAvCodecContex->height = m_iVideoHeight;
        pAvCodecContex->time_base.den = m_iFrameRate;
		pAvCodecContex->time_base.num = 1;
		pAvCodecContex->gop_size = 1;
		pAvCodecContex->pix_fmt = AV_PIX_FMT_YUV420P;
		if (pAvCodecContex->codec_id == AV_CODEC_ID_MPEG2VIDEO)
		{
			pAvCodecContex->max_b_frames = 2;
		}
		if (pAvCodecContex->codec_id == AV_CODEC_ID_MPEG1VIDEO)
		{
			pAvCodecContex->mb_decision = 2;
		}
		break;
	default:
        OUT_LOG("case unknow type.");
		break;
	}

	if (formatCtx->oformat->flags & AVFMT_GLOBALHEADER)
	{
		pAvCodecContex->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}
	return pAvStream;
}

bool H264ToMp4::isIdrFrame2(uint8_t* buf, int len)
{
	switch (buf[0] & 0x1f) {
	case 7: // SPS
		return true;
	case 8: // PPS
		return true;
	case 5:
		return true;
	case 1:
		return false;

	default:
		return false;
		break;
	}

	return false;
}

bool H264ToMp4::checkIfIFrame(uint8_t* buf, int size)
{
	//主要是解析idr前面的sps pps
	int last = 0;
	for (int i = 2; i <= size; ++i)
	{
		if (i == size) {
			if (last) {
				bool ret = isIdrFrame2(buf + last, i - last);
				if (ret) {
					return true;
				}
			}
		}
		else if (buf[i - 2] == 0x00 && buf[i - 1] == 0x00 && buf[i] == 0x01) {
			if (last) {
				int size = i - last - 3;
				if (buf[i - 3]) ++size;
				bool ret = isIdrFrame2(buf + last, size);
				if (ret) {
					return true;
				}
			}
			last = i + 1;
		}
	}
	return false;
}
