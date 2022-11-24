package com.mobiquity.model;

import lombok.AllArgsConstructor;
import lombok.Getter;

import javax.validation.constraints.Max;
import javax.validation.constraints.Size;
import java.util.List;

@AllArgsConstructor
@Getter
public class Package {

    @Max(value = 100, message = "Max weight must be less than 100")
    private Integer maxWeight;
    @Size(max = 15, message = "Item count must be less than 15")
    private List<Item> items;
}
