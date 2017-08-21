install(FILES
    nghttp2/nghttp2.h
	nghttp2/nghttp2_common.h
    "${CMAKE_CURRENT_BINARY_DIR}/nghttp2/nghttp2ver.h"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/nghttp2")
