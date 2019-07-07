#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

vector<ll> vectorMul(vector<ll> &vec1, vector<ll> &vec2, int mod) {
    int N = vec1.size();
    vector<ll> res(N, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[i] = (res[i] + vec1[j] * vec2[(i + N - j) % N]) % mod;
        }
    }
    return res;
}

vector<ll>& setCoefficients(int S, int mod, vector<ll> &firstIter, vector<ll> &midRes, vector<ll> &marker) {
    if (S == 1) {
        return firstIter;
    }
    if (S == 0) {
        int size = firstIter.size();
        midRes = vector<ll>(size, 0);
        midRes[0] = 1;
        return midRes;
    }

    midRes = setCoefficients(S / 2, mod, firstIter, midRes, marker);

    int size = firstIter.size();
    marker = vector<ll>(size, 0);
    marker[0] = 1;

    marker = vectorMul(midRes, midRes, mod);

    if (S % 2 == 1) { // Case we need to multiply again
        midRes = vectorMul(marker, firstIter, mod);
        return midRes;
    }

    return marker;
}

unsigned GetNumberOfDigits(ll x) {
    int digits = 1;
    for (int i = 0; i < x; i++) {
        digits *= 10;
    }
    return digits;
}

int main() {
    int TC;
    cin >> TC;
    while (TC--) {
        ll N, S, L, R, X;
        cin >> N >> S >> L >> R >> X;
        vector<ll> message(N), coeffs(N, 0);
        for (int i = 0; i < N; i++) {
            int enc;
            cin >> enc;
            message[i] = enc;
        }
            int mod = GetNumberOfDigits(X);

            vector<ll> firstIter(N, 0);
            firstIter[0] = 1;
            firstIter[N - 1] = L;
            firstIter[1] = R;
            vector<ll> midIter, marker;

            coeffs = setCoefficients(S, mod, firstIter, midIter, marker);
            vector<ll> output(N, 0);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    output[i] = (output[i] + message[j]*coeffs[(j+N-i)%N]) % mod;
                }
                cout << output[i];
                if (i<N-1) {
                    cout << " ";
                }
            }
            cout << endl;
    }
    return 0;
}