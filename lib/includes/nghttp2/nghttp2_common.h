#ifndef NGHTTP2_EXTERN_H
#define NGHTTP2_EXTERN_H

/* Define WIN32 when build target is Win32 API (borrowed from libcurl) */
#if (defined(_WIN32) || defined(__WIN32__)) && !defined(WIN32)
#define WIN32
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#if defined(_MSC_VER) && (_MSC_VER < 1800)
	/* MSVC < 2013 does not have inttypes.h because it is not C99
	compliant.  See compiler macros and version number in
	https://sourceforge.net/p/predef/wiki/Compilers/ */
#include <stdint.h>
#else /* !defined(_MSC_VER) || (_MSC_VER >= 1800) */
#include <inttypes.h>
#endif /* !defined(_MSC_VER) || (_MSC_VER >= 1800) */
#include <sys/types.h>
#include <stdarg.h>

#ifdef NGHTTP2_STATICLIB
#define NGHTTP2_EXTERN
#elif defined(WIN32)
#ifdef BUILDING_NGHTTP2
#define NGHTTP2_EXTERN __declspec(dllexport)
#else /* !BUILDING_NGHTTP2 */
#define NGHTTP2_EXTERN __declspec(dllimport)
#endif /* !BUILDING_NGHTTP2 */
#else  /* !defined(WIN32) */
#ifdef BUILDING_NGHTTP2
#define NGHTTP2_EXTERN __attribute__((visibility("default")))
#else /* !BUILDING_NGHTTP2 */
#define NGHTTP2_EXTERN
#endif /* !BUILDING_NGHTTP2 */
#endif /* !defined(WIN32) */

/**
 * @enum
 *
 * Error codes used in this library.  The code range is [-999, -500],
 * inclusive. The following values are defined:
 */
typedef enum {
  /**
   * Invalid argument passed.
   */
  NGHTTP2_ERR_INVALID_ARGUMENT = -501,
  /**
   * Out of buffer space.
   */
  NGHTTP2_ERR_BUFFER_ERROR = -502,
  /**
   * The specified protocol version is not supported.
   */
  NGHTTP2_ERR_UNSUPPORTED_VERSION = -503,
  /**
   * Used as a return value from :type:`nghttp2_send_callback`,
   * :type:`nghttp2_recv_callback` and
   * :type:`nghttp2_send_data_callback` to indicate that the operation
   * would block.
   */
  NGHTTP2_ERR_WOULDBLOCK = -504,
  /**
   * General protocol error
   */
  NGHTTP2_ERR_PROTO = -505,
  /**
   * The frame is invalid.
   */
  NGHTTP2_ERR_INVALID_FRAME = -506,
  /**
   * The peer performed a shutdown on the connection.
   */
  NGHTTP2_ERR_EOF = -507,
  /**
   * Used as a return value from
   * :func:`nghttp2_data_source_read_callback` to indicate that data
   * transfer is postponed.  See
   * :func:`nghttp2_data_source_read_callback` for details.
   */
  NGHTTP2_ERR_DEFERRED = -508,
  /**
   * Stream ID has reached the maximum value.  Therefore no stream ID
   * is available.
   */
  NGHTTP2_ERR_STREAM_ID_NOT_AVAILABLE = -509,
  /**
   * The stream is already closed; or the stream ID is invalid.
   */
  NGHTTP2_ERR_STREAM_CLOSED = -510,
  /**
   * RST_STREAM has been added to the outbound queue.  The stream is
   * in closing state.
   */
  NGHTTP2_ERR_STREAM_CLOSING = -511,
  /**
   * The transmission is not allowed for this stream (e.g., a frame
   * with END_STREAM flag set has already sent).
   */
  NGHTTP2_ERR_STREAM_SHUT_WR = -512,
  /**
   * The stream ID is invalid.
   */
  NGHTTP2_ERR_INVALID_STREAM_ID = -513,
  /**
   * The state of the stream is not valid (e.g., DATA cannot be sent
   * to the stream if response HEADERS has not been sent).
   */
  NGHTTP2_ERR_INVALID_STREAM_STATE = -514,
  /**
   * Another DATA frame has already been deferred.
   */
  NGHTTP2_ERR_DEFERRED_DATA_EXIST = -515,
  /**
   * Starting new stream is not allowed (e.g., GOAWAY has been sent
   * and/or received).
   */
  NGHTTP2_ERR_START_STREAM_NOT_ALLOWED = -516,
  /**
   * GOAWAY has already been sent.
   */
  NGHTTP2_ERR_GOAWAY_ALREADY_SENT = -517,
  /**
   * The received frame contains the invalid header block (e.g., There
   * are duplicate header names; or the header names are not encoded
   * in US-ASCII character set and not lower cased; or the header name
   * is zero-length string; or the header value contains multiple
   * in-sequence NUL bytes).
   */
  NGHTTP2_ERR_INVALID_HEADER_BLOCK = -518,
  /**
   * Indicates that the context is not suitable to perform the
   * requested operation.
   */
  NGHTTP2_ERR_INVALID_STATE = -519,
  /**
   * The user callback function failed due to the temporal error.
   */
  NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE = -521,
  /**
   * The length of the frame is invalid, either too large or too small.
   */
  NGHTTP2_ERR_FRAME_SIZE_ERROR = -522,
  /**
   * Header block inflate/deflate error.
   */
  NGHTTP2_ERR_HEADER_COMP = -523,
  /**
   * Flow control error
   */
  NGHTTP2_ERR_FLOW_CONTROL = -524,
  /**
   * Insufficient buffer size given to function.
   */
  NGHTTP2_ERR_INSUFF_BUFSIZE = -525,
  /**
   * Callback was paused by the application
   */
  NGHTTP2_ERR_PAUSE = -526,
  /**
   * There are too many in-flight SETTING frame and no more
   * transmission of SETTINGS is allowed.
   */
  NGHTTP2_ERR_TOO_MANY_INFLIGHT_SETTINGS = -527,
  /**
   * The server push is disabled.
   */
  NGHTTP2_ERR_PUSH_DISABLED = -528,
  /**
   * DATA or HEADERS frame for a given stream has been already
   * submitted and has not been fully processed yet.  Application
   * should wait for the transmission of the previously submitted
   * frame before submitting another.
   */
  NGHTTP2_ERR_DATA_EXIST = -529,
  /**
   * The current session is closing due to a connection error or
   * `nghttp2_session_terminate_session()` is called.
   */
  NGHTTP2_ERR_SESSION_CLOSING = -530,
  /**
   * Invalid HTTP header field was received and stream is going to be
   * closed.
   */
  NGHTTP2_ERR_HTTP_HEADER = -531,
  /**
   * Violation in HTTP messaging rule.
   */
  NGHTTP2_ERR_HTTP_MESSAGING = -532,
  /**
   * Stream was refused.
   */
  NGHTTP2_ERR_REFUSED_STREAM = -533,
  /**
   * Unexpected internal error, but recovered.
   */
  NGHTTP2_ERR_INTERNAL = -534,
  /**
   * Indicates that a processing was canceled.
   */
  NGHTTP2_ERR_CANCEL = -535,
  /**
   * The errors < :enum:`NGHTTP2_ERR_FATAL` mean that the library is
   * under unexpected condition and processing was terminated (e.g.,
   * out of memory).  If application receives this error code, it must
   * stop using that :type:`nghttp2_session` object and only allowed
   * operation for that object is deallocate it using
   * `nghttp2_session_del()`.
   */
  NGHTTP2_ERR_FATAL = -900,
  /**
   * Out of memory.  This is a fatal error.
   */
  NGHTTP2_ERR_NOMEM = -901,
  /**
   * The user callback function failed.  This is a fatal error.
   */
  NGHTTP2_ERR_CALLBACK_FAILURE = -902,
  /**
   * Invalid client magic (see :macro:`NGHTTP2_CLIENT_MAGIC`) was
   * received and further processing is not possible.
   */
  NGHTTP2_ERR_BAD_CLIENT_MAGIC = -903,
  /**
   * Possible flooding by peer was detected in this HTTP/2 session.
   * Flooding is measured by how many PING and SETTINGS frames with
   * ACK flag set are queued for transmission.  These frames are
   * response for the peer initiated frames, and peer can cause memory
   * exhaustion on server side to send these frames forever and does
   * not read network.
   */
  NGHTTP2_ERR_FLOODED = -904
} nghttp2_error;

/**
 * @enum
 * The status codes for the RST_STREAM and GOAWAY frames.
 */
typedef enum {
  /**
   * No errors.
   */
  NGHTTP2_NO_ERROR = 0x00,
  /**
   * PROTOCOL_ERROR
   */
  NGHTTP2_PROTOCOL_ERROR = 0x01,
  /**
   * INTERNAL_ERROR
   */
  NGHTTP2_INTERNAL_ERROR = 0x02,
  /**
   * FLOW_CONTROL_ERROR
   */
  NGHTTP2_FLOW_CONTROL_ERROR = 0x03,
  /**
   * SETTINGS_TIMEOUT
   */
  NGHTTP2_SETTINGS_TIMEOUT = 0x04,
  /**
   * STREAM_CLOSED
   */
  NGHTTP2_STREAM_CLOSED = 0x05,
  /**
   * FRAME_SIZE_ERROR
   */
  NGHTTP2_FRAME_SIZE_ERROR = 0x06,
  /**
   * REFUSED_STREAM
   */
  NGHTTP2_REFUSED_STREAM = 0x07,
  /**
   * CANCEL
   */
  NGHTTP2_CANCEL = 0x08,
  /**
   * COMPRESSION_ERROR
   */
  NGHTTP2_COMPRESSION_ERROR = 0x09,
  /**
   * CONNECT_ERROR
   */
  NGHTTP2_CONNECT_ERROR = 0x0a,
  /**
   * ENHANCE_YOUR_CALM
   */
  NGHTTP2_ENHANCE_YOUR_CALM = 0x0b,
  /**
   * INADEQUATE_SECURITY
   */
  NGHTTP2_INADEQUATE_SECURITY = 0x0c,
  /**
   * HTTP_1_1_REQUIRED
   */
  NGHTTP2_HTTP_1_1_REQUIRED = 0x0d
} nghttp2_error_code;

/**
 * @struct
 *
 * The structure to specify stream dependency.
 */
typedef struct {
  /**
   * The stream ID of the stream to depend on.  Specifying 0 makes
   * stream not depend any other stream.
   */
  int32_t stream_id;
  /**
   * The weight of this dependency.
   */
  int32_t weight;
  /**
   * nonzero means exclusive dependency
   */
  uint8_t exclusive;
} nghttp2_priority_spec;

#ifdef __cplusplus
}
#endif


#endif /* NGHTTP2_EXTERN_H */