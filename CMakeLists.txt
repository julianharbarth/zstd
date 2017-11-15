project(zstd)
cmake_minimum_required(VERSION 3.8)

set(src-files
  lib/common/entropy_common.c
  lib/common/fse_decompress.c
  lib/common/threading.c
  lib/common/pool.c
  lib/common/zstd_common.c
  lib/common/error_private.c
  lib/common/xxhash.c
  lib/compress/fse_compress.c
  lib/compress/huf_compress.c
  lib/compress/zstd_compress.c
  lib/compress/zstdmt_compress.c
  lib/compress/zstd_fast.c
  lib/compress/zstd_double_fast.c
  lib/compress/zstd_lazy.c
  lib/compress/zstd_opt.c
  lib/compress/zstd_ldm.c
  lib/decompress/huf_decompress.c
  lib/decompress/zstd_decompress.c
  lib/dictBuilder/cover.c
  lib/dictBuilder/divsufsort.c
  lib/dictBuilder/zdict.c
  lib/deprecated/zbuff_common.c
  lib/deprecated/zbuff_compress.c
  lib/deprecated/zbuff_decompress.c)
add_library(zstd STATIC ${src-files})
target_compile_definitions(zstd PUBLIC
    XXH_NAMESPACE=ZSTD_
    ZSTD_LEGACY_SUPPORT=0
)
target_include_directories(zstd SYSTEM PUBLIC lib lib/common)
if (MSVC)
  target_compile_definitions(zstd PRIVATE
    _CRT_SECURE_NO_WARNINGS
    _UNICODE
    UNICODE
    ZSTD_HEAPMODE=0
  )
endif()