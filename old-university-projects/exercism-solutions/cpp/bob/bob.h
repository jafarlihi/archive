#include <string>

namespace bob {

bool containsAlpha(std::string input) {
    for (char& c : input) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    
    return false;
}

bool isAllCaps(std::string input) {
    if (!containsAlpha(input)) { return false; }

    for (char& c : input) {
        if (std::isalpha(c) && std::islower(c)) {
            return false;
        }
    }
    
    return true;
}

std::string hey(std::string input) {
    if (isAllCaps(input)) {
        return "Whoa, chill out!";
    } else if (input.back() == '?' || (input.back() == ' ' && input[input.length() - 2] == '?')) {
        return "Sure.";
    } else if (input.find_first_not_of(' ') == std::string::npos) {
        return "Fine. Be that way!";
    } else { return "Whatever."; }
}

}
