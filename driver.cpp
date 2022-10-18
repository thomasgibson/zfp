#include <cstdio>
#include <cstdlib>
#include <string>
#include "zfp.h"

int main(int argc, char* argv[])
{
  // read input field
  const size_t nx = 384;
  const size_t ny = 384;
  const size_t nz = 256;
  const size_t n = nx * ny * nz;
  double* array = new double[n];
  if (fread(array, sizeof(*array), n, stdin) != n) {
    fprintf(stderr, "error reading stdin\n");
    return EXIT_FAILURE;
  }

  // describe field layout
  zfp_type type = zfp_type_double;
  zfp_field* field = zfp_field_3d(array, type, nx, ny, nz);

  // create zfp stream
  zfp_stream* zfp = zfp_stream_open(NULL);

  // set compression mode and parameters
  zfp_stream_set_rate(zfp, 64.0, type, zfp_field_dimensionality(field), zfp_false);

  // set execution policy
  if (argc == 2) {
    if (argv[1] == std::string("serial"))
      zfp_stream_set_execution(zfp, zfp_exec_serial);
    else if (argv[1] == std::string("cuda"))
      zfp_stream_set_execution(zfp, zfp_exec_cuda);
    else if (argv[1] == std::string("hip"))
      zfp_stream_set_execution(zfp, zfp_exec_hip);
    else {
      fprintf(stderr, "execution policy must be one of {serial, cuda, hip}\n");
      return EXIT_FAILURE;
    }
  }

  // allocate buffer for compressed data
  size_t bufsize = zfp_stream_maximum_size(zfp, field);
  void* buffer = malloc(bufsize);

  // associate bit stream with allocated buffer
  bitstream* stream = stream_open(buffer, bufsize);
  zfp_stream_set_bit_stream(zfp, stream);

  // loop over rates {1, 4, 16, 64}
  for (double rate = 1.0; rate <= 64.0; rate *= 4) {
    printf("rate = %g\n", rate);
    zfp_stream_set_rate(zfp, rate, type, zfp_field_dimensionality(field), zfp_false);

    const size_t runs = 9;
    size_t csize, dsize;

    // compress data
    printf("--- compress\n");
    for (size_t k = 0; k < runs; k++) {
      zfp_stream_rewind(zfp);
      csize = zfp_compress(zfp, field);
      if (!csize) {
        fprintf(stderr, "compression failed\n");
        return EXIT_FAILURE;
      }
    }

    // decompress data
    printf("--- decompress\n");
    for (size_t k = 0; k < runs; k++) {
      zfp_stream_rewind(zfp);
      dsize = zfp_decompress(zfp, field);
      if (dsize != csize) {
        fprintf(stderr, "decompression failed\n");
        return EXIT_FAILURE;
      }
    }

    printf("\n\n");
  }

  return 0;
}
