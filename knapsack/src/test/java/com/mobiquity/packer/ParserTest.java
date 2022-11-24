package com.mobiquity.packer;

import com.mobiquity.Parser;
import com.mobiquity.exception.ParseException;
import com.mobiquity.model.Package;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class ParserTest {

    @Test
    public void testParsing() throws ParseException {
        List<String> content = new ArrayList<>(){{
            add("81 : (1,53.38,€45) (2,88.62,€98) (3,78.48,€3) (4,72.30,€76) (5,30.18,€9) (6,46.34,€48)");
        }};

        Parser parser = new Parser(content);
        List<Package> result = parser.parse();
        Package resultPackage = result.get(0);

        assertEquals(resultPackage.getMaxWeight(), 81);
        assertEquals(resultPackage.getItems().size(), 6);
        assertEquals(resultPackage.getItems().get(0).getPrice(), 45);
        assertEquals(resultPackage.getItems().get(0).getWeight(), 53.38f);
    }

    @Test
    public void testParsingWithInvalidMaxWeight() {
        List<String> content = new ArrayList<>(){{
            add("81.55 : (1,53.38,€45) (2,88.62,€98) (3,78.48,€3) (4,72.30,€76) (5,30.18,€9) (6,46.34,€48)");
        }};

        Parser parser = new Parser(content);
        assertThrows(ParseException.class, parser::parse);
    }

    @Test
    public void testParsingWithInvalidDelimiter() {
        List<String> content = new ArrayList<>(){{
            add("81 , (1,53.38,€45) (2,88.62,€98) (3,78.48,€3) (4,72.30,€76) (5,30.18,€9) (6,46.34,€48)");
        }};

        Parser parser = new Parser(content);
        assertThrows(ParseException.class, parser::parse);
    }

    @Test
    public void testParsingWithInvalidItemString() {
        List<String> content = new ArrayList<>(){{
            add("81 : (1,53.38,€45,55) (2,88.62,€98) (3,78.48,€3) (4,72.30,€76) (5,30.18,€9) (6,46.34,€48)");
        }};

        Parser parser = new Parser(content);
        assertThrows(ParseException.class, parser::parse);
    }
}
