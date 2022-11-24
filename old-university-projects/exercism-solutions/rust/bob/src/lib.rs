pub fn reply(input: &str) -> String {
    if input.chars().any(char::is_lowercase) == false && input.chars().any(char::is_alphabetic) == true {
        return "Whoa, chill out!".to_string()
    }

    if is_last_char_question_mark(&mut input.to_string()) == true {
        return "Sure.".to_string()
    }

    if input.chars().any(char::is_alphanumeric) == false {
        return "Fine. Be that way!".to_string()
    }

    return "Whatever.".to_string()
}

fn is_last_char_question_mark(input: &mut String) -> bool {
    let popped = input.pop();

    match popped {
        None => return false,
        Some(' ') => is_last_char_question_mark(input),
        Some('?') => return true,
        _ => return false,
    }
}
