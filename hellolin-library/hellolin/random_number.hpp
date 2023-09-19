#ifndef HELLOLIN_RANDOM_NUMBER_HPP
#define HELLOLIN_RANDOM_NUMBER_HPP 1
#include <chrono>
#include <functional>
#include <random>

namespace hellolin {

class random_number {
private:
    std::mt19937_64 *gen;
    std::uniform_int_distribution<unsigned long long> dist;
    std::hash<unsigned long long> hs;
    unsigned long long get_time() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

public:
    explicit random_number(unsigned long long sd = 4731636727ll) {
        static std::mt19937_64 r(sd ^ get_time());
        gen = &r;
    }
    unsigned long long operator()() {
        return hs(1ll * (dist(*gen) ^ get_time()));
    }
    unsigned long long operator()(unsigned long long l, unsigned long long r) {
        return operator()() % r + l;
    }
};

} // namespace hellolin

#endif