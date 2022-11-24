package com.mobiquity.packer.packer;

import com.mobiquity.exception.APIException;
import com.mobiquity.packer.Packer;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class PackerTest {

    @Test
    public void testPacking() throws APIException, IOException {
        Path inputFilePath = Paths.get("src", "test", "resources", "example_input");
        Path outputFilePath = Paths.get("src", "test", "resources", "example_output");

        String result = Packer.pack(inputFilePath.toFile().getAbsolutePath());
        String expectedResult = String.join("\n", Files.readAllLines(outputFilePath));

        assertEquals(result, expectedResult);
    }
}
