package me.duncte123.lottieconverter;

public class LottieConverter {
    static {
        if (!LibraryLoader.load(LottieConverter.class, "lottieconverter")) {
            System.loadLibrary("lottieconverter");
        }
    }

    public native String getMessage();

    public native byte[] generateGif(String lottieJson, String cacheKey);
}
