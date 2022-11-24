# knapsack

Solves the knapsack problem using dynamic programming. Please see the included PDF file for requirements.

### Packer.java

`Packer` contains the main entry point to the library: `public static String pack(String filePath) throws APIException`.
`pack` method does the following operations:
1. Initialize the `Parser` with the provided input file content.
2. Parse the input file content to `Package` and `Item` POJOs.
3. Execute Bean Validation on parsed POJOs.
4. Call `KnapsackAlgorithm.findOptimalItemIndices` for each of the parsed `Package`.
5. Collect results of the algorithm calls and return a `String`.

### Parser.java

`Parser` is used for parsing the input file content. It takes in a list of strings `List<String>` where each line corresponds to one `Package` that will be parsed.
It returns `List<Package>`.

### KnapsackAlgorithm.java

`KnapsackAlgorithm` contains the implementation of solution for knapsack problem using dynamic programming. 
Time complexity is O(N\*C) where N is number of available items and C is the capacity of the knapsack. Space complexity is O(N\*C) as well.

It takes in a `Package` and returns `List<Integer>`. Returned list contains indices of the items that should be picked for optimal solution.
