#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to convert a string representation of a number in a given base to decimal
unsigned long long base_to_decimal(const char *value, int base) {
    unsigned long long result = 0;
    unsigned long long multiplier = 1;
    int len = strlen(value);

    for (int i = len - 1; i >= 0; i--) {
        char digit = value[i];
        unsigned long long digit_value;

        if (digit >= '0' && digit <= '9') {
            digit_value = digit - '0';
        } else if (digit >= 'a' && digit <= 'f') {
            digit_value = digit - 'a' + 10;
        } else if (digit >= 'A' && digit <= 'F') {
            digit_value = digit - 'A' + 10;
        } else {
            fprintf(stderr, "Invalid character in number: %c\n", digit);
            exit(EXIT_FAILURE);
        }

        if (digit_value >= base) {
            fprintf(stderr, "Digit %llu is not valid for base %d\n", digit_value, base);
            exit(EXIT_FAILURE);
        }

        result += digit_value * multiplier;
        multiplier *= base;
    }

    return result;
}

// Function to calculate the constant term (c) of the polynomial given the roots
unsigned long long find_constant_term(unsigned long long *roots, int k) {
    unsigned long long c = 1;
    for (int i = 0; i < k; i++) {
        c *= -roots[i]; // c = (-1)^k * (r1 * r2 * ... * rk)
    }
    return c;
}

int main() {
    // Sample JSON input (for simplicity, hardcoded)
    const char *json_input = "{"
        "\"keys\": {"
        "\"n\": 4,"
        "\"k\": 3"
        "},"
        "\"1\": {\"base\": \"10\", \"value\": \"4\"},"
        "\"2\": {\"base\": \"2\", \"value\": \"111\"},"
        "\"3\": {\"base\": \"10\", \"value\": \"12\"},"
        "\"4\": {\"base\": \"4\", \"value\": \"213\"}"
        "}";

    // Extracting values (simulated for demonstration)
    unsigned long long roots[4]; // Up to n roots
    int k = 3; // Minimum number of roots required

    // Manually extracting and converting values from the JSON input
    roots[0] = base_to_decimal("4", 10); // from key "1"
    roots[1] = base_to_decimal("111", 2); // from key "2"
    roots[2] = base_to_decimal("12", 10); // from key "3"
    roots[3] = base_to_decimal("213", 4); // from key "4"

    // Calculate the constant term (c)
    unsigned long long constant_term = find_constant_term(roots, k);
    
    // Output the result
    printf("Constant term (c) of the polynomial: %llu\n", constant_term);
    
    return 0;
}
