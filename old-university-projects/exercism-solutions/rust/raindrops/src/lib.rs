pub fn raindrops(input: u32) -> String {
    let mut result = "".to_string();

    if input % 3 == 0 { result.push_str("Pling") }
    if input % 5 == 0 { result.push_str("Plang") }
    if input % 7 == 0 { result.push_str("Plong") }

    if result != "" { return result }
    return input.to_string()
}
