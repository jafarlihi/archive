package com.mobiquity;

import com.mobiquity.model.Item;
import com.mobiquity.model.Package;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/* Implements dynamic programming approach to solving the knapsack problem.
 * Time complexity is O(N*C) where N is number of available items and C is the capacity of the knapsack.
 * Space complexity is O(N*C) as well.
 */
public class KnapsackAlgorithm {

    private KnapsackAlgorithm() {
    }

    public static List<Integer> findOptimalItemIndices(Package pack) {
        List<Integer> result = new ArrayList<>();
        // Weights are multiplied by 100 to lose the fractional part of the number
        Integer[][] table = new Integer[pack.getItems().size() + 1][pack.getMaxWeight() * 100 + 1];
        Integer[] weights = pack.getItems().stream().map(i -> Math.round(i.getWeight() * 100)).toArray(Integer[]::new);
        Integer[] prices = pack.getItems().stream().map(Item::getPrice).toArray(Integer[]::new);

        // Construct the table
        for (int i = 0; i <= pack.getItems().size(); i++) {
            for (int j = 0; j <= pack.getMaxWeight() * 100; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (weights[i - 1] <= j)
                    table[i][j] = Math.max(prices[i - 1] + table[i - 1][j - weights[i - 1]], table[i - 1][j]);
                else
                    table[i][j] = table[i - 1][j];
            }
        }

        int totalPrice = table[pack.getItems().size()][pack.getMaxWeight() * 100];
        int j = pack.getMaxWeight() * 100;

        // Backtrack on table and pick items
        for (int i = pack.getItems().size(); i > 0 && totalPrice > 0; i--) {
            for (int x = 0; x < j; x++)
                if (table[i][x].equals(table[i][j]))
                    j = x; // This allows us to get the solution that weights the least instead of just any solution
            if (totalPrice != table[i - 1][j]) {
                result.add(i);
                totalPrice -= prices[i - 1];
                j = j - weights[i - 1];
            }
        }

        Collections.sort(result);
        return result;
    }
}
