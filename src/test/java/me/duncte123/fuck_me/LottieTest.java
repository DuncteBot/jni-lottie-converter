package me.duncte123.fuck_me;

import me.duncte123.lottieconverter.LottieConverter;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class LottieTest {
    @Test
    public void test_lib() {
        final var converter = new LottieConverter();

        System.out.println("Message from JNI: " + converter.getMessage());

        assertEquals(converter.getMessage(), "This is a test from C++");
    }
}
