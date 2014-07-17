#ifndef __READ_STREAM_H__
#define __READ_STREAM_H__

// includes
#include "common.h"

// int parsing macros
#define PARSE_LE32(p) (*(uint32_t*)(p))
#define PARSE_BE16(p) ( ((uint16_t) (p)[0] << 8) |  ((p)[1]) )
#define PARSE_BE32(p) ( ((uint32_t) (p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | ((p)[3]) )
#define PARSE_BE64(p) ((((uint64_t)PARSE_BE32(p)) << 32) | PARSE_BE32((p) + 4))

// int reading macros
#define READ_LE32(p, v) { v = PARSE_LE32(p); p += sizeof(uint32_t); }
#define READ_BE16(p, v) { v = PARSE_BE16(p); p += sizeof(uint16_t); }
#define READ_BE32(p, v) { v = PARSE_BE32(p); p += sizeof(uint32_t); }
#define READ_BE64(p, v) { v = PARSE_BE64(p); p += sizeof(uint64_t); }

// typedefs
typedef struct {
	const u_char* cur_pos;
	const u_char* end_pos;
	bool_t eof_reached;
} simple_read_stream_t;

// functions
static vod_inline u_char 
stream_get8(simple_read_stream_t* stream)
{
	if (stream->cur_pos >= stream->end_pos)
	{
		stream->eof_reached = TRUE;
		return 0;
	}
	return *stream->cur_pos++;
}

static vod_inline void 
stream_skip(simple_read_stream_t* stream, int bytes)
{
	if (stream->cur_pos + bytes > stream->end_pos)
	{
		stream->eof_reached = TRUE;
		stream->cur_pos = stream->end_pos;
	}
	else
	{
		stream->cur_pos += bytes;
	}
}

#endif // __READ_STREAM_H__