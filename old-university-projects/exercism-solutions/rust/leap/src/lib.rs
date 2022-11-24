pub fn is_leap_year(input: u16) -> bool {
    if input % 4 == 0 && (input % 100 != 0 || input % 400 == 0) { return true }

    return false
}
