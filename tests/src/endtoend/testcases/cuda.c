// requires #include "utils/testMacros.h", do outside of main()

_cmocka_unit_test(when_seededRandomSmoothDataGenerated_expect_ChecksumMatches),

/* fixed-rate */
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, Array_when_ZfpCompressDecompressFixedRate_expect_BitstreamAndArrayChecksumsMatch), setupDefaultStride, teardown),

/* fixed-rate strided */
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, ReversedArray_when_ZfpCompressDecompressFixedRate_expect_BitstreamAndArrayChecksumsMatch), setupReversed, teardown),
#if DIMS >= 2
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, PermutedArray_when_ZfpCompressDecompressFixedRate_expect_BitstreamAndArrayChecksumsMatch), setupPermuted, teardown),
#endif

/* variable-rate */
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, Array_when_ZfpCompressDecompressFixedPrecision_expect_BitstreamAndArrayChecksumsMatch), setupDefaultIndexed, teardown),
#ifdef FL_PT_DATA
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, Array_when_ZfpCompressDecompressFixedAccuracy_expect_BitstreamAndArrayChecksumsMatch), setupDefaultIndexed, teardown),
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, Array_when_ZfpCompressFixedAccuracy_expect_CompressedValuesWithinAccuracy), setupDefaultIndexed, teardown),
#endif

/* variable-rate strided */
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, ReversedArray_when_ZfpCompressDecompressFixedPrecision_expect_BitstreamAndArrayChecksumsMatch), setupReversedIndexed, teardown),
#ifdef FL_PT_DATA
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, ReversedArray_when_ZfpCompressDecompressFixedAccuracy_expect_BitstreamAndArrayChecksumsMatch), setupReversedIndexed, teardown),
#endif

#if DIMS >= 2
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, PermutedArray_when_ZfpCompressDecompressFixedPrecision_expect_BitstreamAndArrayChecksumsMatch), setupPermutedIndexed, teardown),
  #ifdef FL_PT_DATA
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, PermutedArray_when_ZfpCompressDecompressFixedAccuracy_expect_BitstreamAndArrayChecksumsMatch), setupPermutedIndexed, teardown),
  #endif
#endif

/* CUDA expects contiguous storage */
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, InterleavedArray_when_ZfpCompressDecompressFixedRate_expect_BitstreamUntouchedAndReturnsZero), setupInterleaved, teardown),
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, InterleavedArray_when_ZfpCompressDecompressFixedPrecision_expect_BitstreamUntouchedAndReturnsZero), setupInterleaved, teardown),
#ifdef FL_PT_DATA
_cmocka_unit_test_setup_teardown(_catFunc3(given_Cuda_, DIM_INT_STR, InterleavedArray_when_ZfpCompressDecompressFixedAccuracy_expect_BitstreamUntouchedAndReturnsZero), setupInterleaved, teardown),
#endif
