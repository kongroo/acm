#ifndef DS_MATH_MOD_INT
#define DS_MATH_MOD_INT

template<int Mod, typename T = int> struct ModInt {
    T val;
    ModInt(T val): val((val + Mod) % Mod) {}
    static T rev(T x) { return x == 1 ? 1 : rev(Mod % x) * 1LL * (Mod - Mod / x) % Mod; }
    ModInt<Mod, T> operator+(const ModInt<Mod, T>& rhs) { return (0LL + val + rhs.val) % Mod; }
    ModInt<Mod, T> operator-(const ModInt<Mod, T>& rhs) { return (0LL + val - rhs.val + Mod) % Mod; }
    ModInt<Mod, T> operator*(const ModInt<Mod, T>& rhs) { return (1LL * val * rhs.val) % Mod; }
    ModInt<Mod, T> operator/(const ModInt<Mod, T>& rhs) { return (1LL * val * ModInt<Mod>::rev(rhs.val)) % Mod; }
    ModInt<Mod, T> pow(int k) {
        auto ret = ModInt<Mod, T>(1);
        auto x = *this;
        while(k) {
            if (k&1) ret = ret * x;
            x = x * x;
            k >>= 1;
        }
        return ret;
    }
};

#endif /* ifndef DS_MATH_MOD_INT */
