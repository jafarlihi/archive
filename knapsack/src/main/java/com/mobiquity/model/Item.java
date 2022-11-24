package com.mobiquity.model;

import lombok.AllArgsConstructor;
import lombok.Getter;

import javax.validation.constraints.Max;

@AllArgsConstructor
@Getter
public class Item {

    @Max(value = 100, message = "Weight must be less than 100")
    private Float weight;
    @Max(value = 100, message = "Price must be less than 100")
    private Integer price;
}
