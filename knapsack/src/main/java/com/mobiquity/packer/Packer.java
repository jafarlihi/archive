package com.mobiquity.packer;

import com.mobiquity.Parser;
import com.mobiquity.KnapsackAlgorithm;
import com.mobiquity.exception.ParseException;
import com.mobiquity.model.Item;
import com.mobiquity.model.Package;
import com.mobiquity.exception.APIException;

import javax.validation.ConstraintViolation;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class Packer {

    private Packer() {
    }

    public static String pack(String filePath) throws APIException {
        // Initialize parser with input file content
        Parser parser;
        try {
            parser = new Parser(Files.readAllLines(Paths.get(filePath)));
        } catch (IOException e) {
            throw new APIException("File could not be read", e);
        }

        // Parse the input file content
        List<Package> packages;
        try {
            packages = parser.parse();
        } catch (ParseException e) {
            throw new APIException("Input content is malformed", e);
        }

        // Execute Bean Validation on parsed objects
        ValidatorFactory factory = Validation.buildDefaultValidatorFactory();
        Validator validator = factory.getValidator();
        Set<ConstraintViolation> violations = new HashSet<>();

        for (Package pack : packages) {
            violations.addAll(validator.validate(pack));
            for (Item item : pack.getItems())
                violations.addAll(validator.validate(item));
        }

        if (!violations.isEmpty()) {
            String violationMessage = violations
                    .stream()
                    .map(ConstraintViolation::getMessage)
                    .collect(Collectors.joining("; "));
            throw new APIException("Input constraint violation(s) found: " + violationMessage);
        }

        // Run the Knapsack algorithm over each parsed Package object
        List<String> result = new ArrayList<>();
        for (Package pack : packages) {
            String singleResult = KnapsackAlgorithm.findOptimalItemIndices(pack)
                    .stream()
                    .map(String::valueOf)
                    .collect(Collectors.joining(","));
            if (singleResult.isBlank())
                result.add("-");
            else
                result.add(singleResult);
        }

        // Join result strings and return a single string
        return String.join("\n", result);
    }
}
