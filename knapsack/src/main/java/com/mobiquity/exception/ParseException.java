package com.mobiquity.exception;

public class ParseException extends Exception {

    public ParseException(String message, Exception e) {
        super(message, e);
    }

    public ParseException(String message) {
        super(message);
    }
}
