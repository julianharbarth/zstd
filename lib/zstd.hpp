#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"

#include <stdexcept>
#include <string>

namespace zstd {

inline void compress(char const* data, size_t size, std::string* dst) {
  auto const max_compressed_size = ZSTD_compressBound(size);
  dst->resize(max_compressed_size);
  auto const compressed_size =
      ZSTD_compress(&dst->operator[](0), dst->size(), data, size, 1);
  if (ZSTD_isError(compressed_size)) {
    throw std::runtime_error("zstd compression error");
  }
  dst->resize(compressed_size);
}

inline void uncompress(char const* data, size_t size, std::string* dst) {
  auto decompression_size = ZSTD_findDecompressedSize(data, size);
  if (decompression_size == ZSTD_CONTENTSIZE_ERROR ||
      decompression_size == ZSTD_CONTENTSIZE_UNKNOWN) {
    throw std::runtime_error("zstd decompression error (decompression size)");
  }
  dst->resize(decompression_size);
  if (auto const size_check =
          ZSTD_decompress(&dst->operator[](0), dst->size(), data, size);
      size_check != decompression_size) {
    throw std::runtime_error("zstd decompression error (decompress)");
  }
}

}  // namespace zstd