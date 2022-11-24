package com.mobiquity;

import com.mobiquity.exception.ParseException;
import com.mobiquity.model.Item;
import com.mobiquity.model.Package;

import java.util.ArrayList;
import java.util.List;

public class Parser {

    private List<String> content;

    public Parser(List<String> content) {
        this.content = content;
    }

    public List<Package> parse() throws ParseException {
        List<Package> packages = new ArrayList<>();

        for (String taskString : content) {
            int maxWeight;
            try {
                maxWeight = Integer.parseInt(taskString.split(":", 2)[0].trim());
            } catch (NumberFormatException e) {
                throw new ParseException("Max weight is not a number", e);
            }

            List<Item> items = new ArrayList<>();
            int itemStringStart = -1;
            for (int i = 0; i < taskString.length(); i++) {
                if (taskString.charAt(i) == '(') {
                    itemStringStart = i;
                } else if (taskString.charAt(i) == ')' && itemStringStart != -1) {
                    items.add(parseItemString(taskString.substring(itemStringStart, i)));
                    itemStringStart = -1;
                }
            }

            packages.add(new Package(maxWeight, items));
        }

        return packages;
    }

    private Item parseItemString(String itemString) throws ParseException {
        String[] itemStringSplit = itemString.split(",", 3);

        if (itemStringSplit.length != 3)
            throw new ParseException("Item string is malformed");

        try {
            Float weight = Float.parseFloat(itemStringSplit[1]);
            Integer price = Integer.parseInt(itemStringSplit[2].replace('€', ' ').trim());
            return new Item(weight, price);
        } catch (NumberFormatException e) {
            throw new ParseException("Item string values are not numbers", e);
        }
    }
}
