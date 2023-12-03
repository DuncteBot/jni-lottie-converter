package me.duncte123.fuck_me;

import me.duncte123.lottieconverter.LottieConverter;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class LottieTest {
    @Test
    public void test_lib() {
        final var converter = new LottieConverter();

        System.out.println("Message from JNI: " + converter.getMessage());

        assertEquals(converter.getMessage(), "This is a test from C++");
    }

    @Test
    public void test_generate_gif() throws IOException {
        final var jsonData = new String(Files.readAllBytes(Paths.get("./test_lottie_discord.json")));
        final var converter = new LottieConverter();

//        converter.generateGif(jsonData, "idkWhatThisIsFor");

        System.out.println("Message from JNI: " + converter.getMessage());

        assertEquals(converter.getMessage(), "This is a test from C++");
    }
}
