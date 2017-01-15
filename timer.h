#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

class Timer
{
    public:
        using Clock = std::chrono::steady_clock;

        Timer():
            start_(Clock::now())
        {}

        Clock::time_point::duration raw() const { return Clock::now() - start_; }
        const Clock::time_point& start() const { return start_; }

        template<class ReprT>
        ReprT as() const
        {
            using PrecisionT = typename std::conditional<std::is_integral<ReprT>::value, std::chrono::microseconds, std::chrono::seconds>::type;
            using DiffT = std::chrono::duration<ReprT, typename PrecisionT::period>;

            return std::chrono::duration_cast<DiffT>(raw()).count();
        }

    private:
        Clock::time_point start_;
};

template<>
std::string Timer::as<std::string>() const
{
    std::stringstream ss;
    ss << std::setprecision(6) << std::fixed << as<double>() << "s";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Timer& t)
{
    return os << t.as<std::string>();
}

