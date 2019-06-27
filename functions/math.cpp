#include <cmath>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

// compute (a^q) mod n. should be used with q >= 0 and n >= 1
ll powmodn(ll a, ll q, ll n) {
    ll res = 1;
    while (q) {
        if (q % 2)
            res = (res * a) % n;
        a = (a * a) % n;
        q >>= 1;
    }
    return res;
}

// compute gcd(a, b) aka greatest common divisor
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// compute lcm(a, b) aka least common multiple
ll lcm(ll a, ll b) {
    return a * (b / gcd(a, b)); // order: divide before multiplying!
}

// compute the value of (n choose k)
ull n_choose_k(ull n, ull k) {
    if (k > n)
        return 0;
    if (k * 2 > n)
        k = n - k;
    if (k == 0)
        return 1;

    ull result = n;
    for (ull i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

// return true if n is a prime number, better for (n > 2^20) / (n > 10^6) values
bool MillerRabin(ull n, ll k = 5) {
    if (n == 2 or n == 3) {
        return true;
    }
    if (n < 5) {
        return false;
    }
    ull m = n - 1;
    ull r = 0;
    while (m % 2 == 0) {
        m >>= 1;
        r += 1;
    }
    // !!! Deterministic version for n<2^64 !!!
    ull dtrm_set[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ull a : dtrm_set) {
        if (a >= n)
            break;
        // !!! End of deterministic version !!! */

        /* // !!! Probabilistic version !!!
        while (k--) {
            ull a = rand() % (n - 4) + 2;
            // !!! end of probabilistic version !!! */
        a = powmodn(a, m, n);
        if (a == 1)
            continue;
        ll i = r;
        while (i-- and a != n - 1) {
            a = (a * a) % n;
            if (a == 1)
                return false;
        }
        if (i == -1)
            return false;
    }
    return true;
}

// return true if n is a prime number, better for (n < 2^20) / (n < 10^6) values
bool is_prime(ull n) {
    if (n < 2)
        return false;
    ull sqrtn = (ull)sqrt(n);
    for (ull i = 2; i <= sqrtn; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// return bool array where (ps[n] == true) iff n is a prime number, until n inclusive
vector<bool> sieve(ull n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    ull sqrtn = (ull)sqrt(n);
    for (ull i = 0; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (ull j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

// return an array of primes that are less or equal to n
vector<ull> sieve_primes(ull n) {
    vector<ull> primes;
    auto pbools = sieve(n);
    for (ull i = 0; i < pbools.size(); ++i) {
        if (pbools[i])
            primes.push_back(i);
    }
    return primes;
}

// return array of fibonacci numbers smaller or equal to n
// fib[0..15] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610}
vector<ull> fibonacci_numbers(ull n) {
    ull f0 = 0, f1 = 1;

    vector<ull> fibs;
    fibs.push_back(0);

    if (n < 1)
        return fibs;

    while (f1 <= n and fibs.size() < 94) { // prevent inf loop from overflow
        fibs.push_back(f1);
        ull next = f0 + f1;
        f0 = f1;
        f1 = next;
    }
    return fibs;
}

// compute the factors of a number, good if used a few amount of times (1..1000)
vector<ull> factorizationA(ull n) {
    vector<ull> facs;
    for (ull d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            facs.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        facs.push_back(n);
    return facs;
}

// compute the factors of a number, good if used a lot of times (>100)
template <ull N> // the highest number that is going to be factorized
vector<ull> factorizationB(ull n) {
    static const auto primes = sieve_primes((ull)sqrt(N));
    vector<ull> facs;
    for (auto p : primes) {
        if (p * p > n)
            break;
        while (n % p == 0) {
            facs.push_back(p);
            n /= p;
        }
    }
    if (n > 1)
        facs.push_back(n);
    return facs;
}
