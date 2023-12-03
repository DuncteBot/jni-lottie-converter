include(ExternalProject)

add_library(lottieconverter SHARED "" rlottie)
target_sources(lottieconverter PRIVATE me_duncte123_lottieconverter_LottieConverter.cpp)
