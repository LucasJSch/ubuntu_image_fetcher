#include <string>
#include <stdexcept>
#include <sstream>

namespace canonical {

struct YearMonth {
    int year;
    int month;

    std::string toString() const {
        return std::to_string(year) + "." + (month < 10 ? "0" : "") + std::to_string(month);
    }

    std::string toStringShort() const {
        return std::to_string(year).substr(2) + "." + (month < 10 ? "0" : "") + std::to_string(month);
    }

    bool operator<(const YearMonth& other) const {
        return (year < other.year) || (year == other.year && month < other.month);
    }
};

YearMonth parseYearMonth(const std::string& versionStr) {
    YearMonth ym = {};
    char dot;

    std::istringstream ss(versionStr);
    if (!(ss >> ym.year >> dot >> ym.month) || dot != '.' || ym.month < 1 || ym.month > 12) {
        throw std::runtime_error("Invalid format: " + versionStr);
    }

    // Convert 2-digit year to 4-digit (assuming 20XX)
    ym.year += 2000;

    return ym;
}

} // namespace canonical