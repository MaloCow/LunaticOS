#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

// Basic color codes
namespace color {

    // Color codes
    enum Color {
        RESET = 0,
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,
        GRAY = 90,
        BRIGHT_RED = 91,
        BRIGHT_GREEN = 92,
        BRIGHT_YELLOW = 93,
        BRIGHT_BLUE = 94,
        BRIGHT_MAGENTA = 95,
        BRIGHT_CYAN = 96,
        BRIGHT_WHITE = 97
    };

    // Background color codes
    enum BackgroundColor {
        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
        BG_GRAY = 100,
        BG_BRIGHT_RED = 101,
        BG_BRIGHT_GREEN = 102,
        BG_BRIGHT_YELLOW = 103,
        BG_BRIGHT_BLUE = 104,
        BG_BRIGHT_MAGENTA = 105,
        BG_BRIGHT_CYAN = 106,
        BG_BRIGHT_WHITE = 107
    };

    // Formatting codes
    enum Format {
        BOLD = 1,
        UNDERLINE = 4,
        REVERSED = 7
    };

    // Function to set color
    std::ostream& setColor(std::ostream& os, Color color) {
        return os << "\033[" << color << "m";
    }

    // Function to set background color
    std::ostream& setBackgroundColor(std::ostream& os, BackgroundColor bgColor) {
        return os << "\033[" << bgColor << "m";
    }

    // Function to set formatting
    std::ostream& setFormat(std::ostream& os, Format format) {
        return os << "\033[" << format << "m";
    }

    // Function to reset color and formatting
    std::ostream& reset(std::ostream& os) {
        return os << "\033[0m";
    }

    // Function overloads for convenience
    inline std::ostream& operator<<(std::ostream& os, Color color) {
        return setColor(os, color);
    }

    inline std::ostream& operator<<(std::ostream& os, BackgroundColor bgColor) {
        return setBackgroundColor(os, bgColor);
    }

    inline std::ostream& operator<<(std::ostream& os, Format format) {
        return setFormat(os, format);
    }

    inline std::ostream& operator<<(std::ostream& os, std::ostream& (*func)(std::ostream&)) {
        return func(os);
    }

} // namespace color

#endif // COLOR_HPP
