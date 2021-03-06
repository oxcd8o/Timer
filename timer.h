#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

class Timer
{
    public:
        using Clock = std::chrono::steady_clock;
        template<class ReprT>
            using DefaultPrecision = typename std::conditional<std::is_integral<ReprT>::value, std::chrono::microseconds, std::chrono::seconds>::type;

        Timer():
            start_(Clock::now())
        {}

        Clock::time_point::duration raw() const { return Clock::now() - start_; }
        const Clock::time_point& start() const { return start_; }

        template<class ReprT, class PrecisionT = DefaultPrecision<ReprT>>
        ReprT as() const
        {
            static_assert(std::is_arithmetic<ReprT>() || std::is_same<ReprT, std::string>(),
                          "Timer: Only arithmetic types or std::string should be used as ReprT");
            static_assert(!std::is_same<ReprT, std::string>() || std::is_same<PrecisionT, std::chrono::seconds>(),
                          "Timer: Only std::chrono::seconds could be used as PrecisionT when ReprT is std::string");

            using DiffT = std::chrono::duration<ReprT, typename PrecisionT::period>;
            return std::chrono::duration_cast<DiffT>(raw()).count();
        }

    private:
        Clock::time_point start_;
};

template<>
std::string Timer::as<std::string, std::chrono::seconds>() const
{
    std::stringstream ss;
    ss << std::setprecision(6) << std::fixed << as<double>() << "s";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Timer& t)
{
    return os << t.as<std::string>();
}

