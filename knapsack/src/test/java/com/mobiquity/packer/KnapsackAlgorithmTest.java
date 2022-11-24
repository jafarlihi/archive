package com.mobiquity.packer;

import com.mobiquity.KnapsackAlgorithm;
import com.mobiquity.model.Item;
import com.mobiquity.model.Package;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertIterableEquals;

public class KnapsackAlgorithmTest {

    @Test
    public void testAlgorithm() {
        List<Item> items = new ArrayList<>() {{
            add(new Item(53.38f, 45));
            add(new Item(88.62f, 98));
            add(new Item(78.48f, 3));
            add(new Item(72.30f, 76));
            add(new Item(30.18f, 9));
            add(new Item(46.34f, 48));
        }};
        Package pack = new Package(81, items);

        List<Integer> result = KnapsackAlgorithm.findOptimalItemIndices(pack);
        List<Integer> expectedResult = new ArrayList<>(){{add(4);}};

        assertIterableEquals(result, expectedResult);
    }
}
