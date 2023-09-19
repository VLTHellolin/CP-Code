#ifndef HELLOLIN_IO_HPP
#define HELLOLIN_IO_HPP 1
#include <fstream>
#include <iostream>
#include <vector>

namespace hellolin {

constexpr static size_t IO_MAX_SIZE = (1 << 20) + 1;
constexpr static size_t PRINTER_STACK_SIZE = (1 << 8) + 1;

class scanner {
private:
    std::streambuf *fi;
    size_t sz;
    bool fail;
    char *buf, *buf_head, *buf_tail;

    template <class T>
    void _read(T &x) {
        bool s = 0;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = (x << 1) + (x << 3) + (c ^ '0');
            c = get();
        }
        if (s) x = ~x + 1;
    }
    void _read(long double &x) {
        bool s = false;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = x * 10 + (c ^ '0');
            c = get();
        }
        if (c == '.') {
            c = get();
            long double t = 1;
            while (isdigit(c)) {
                t /= 10;
                x += t * (c ^ '0');
                c = get();
            }
        }
        if (s) x = -x;
    }
    void _read(double &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(float &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(char &x) {
        do {
            x = get();
        } while (isspace(x));
    }
    void _read(char *x) {
        char c = get();
        while (isspace(c)) {
            c = get();
        }
        while (!isspace(c) && c) {
            *x++ = c;
            c = get();
        }
        *x = '\0';
    }
    void _read(std::string &x) {
        char c = get();
        while (isspace(c)) {
            c = get();
        }
        while (!isspace(c) && c) {
            x += c;
            c = get();
        }
    }
    template <class T, class U>
    void _read(std::pair<T, U> &x) {
        T a;
        U b;
        _read(a);
        _read(b);
        x = {a, b};
    }
    template <class T>
    void _read(std::vector<T> &x) {
        for (T &i : x)
            _read(i);
    }

public:
    explicit scanner(std::streambuf *_fi = std::cin.rdbuf(), size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    explicit scanner(const char *_fi, size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    void reopen(std::streambuf *_fi, size_t _sz = IO_MAX_SIZE) {
        fail = 0;
        fi = _fi;
        sz = _sz;
        buf = buf_head = buf_tail = new char[sz];
    }
    void reopen(const char *_fi, size_t _sz = IO_MAX_SIZE) {
        fail = 0;
        static std::ifstream tp(_fi);
        fi = tp.rdbuf();
        sz = _sz;
        buf = buf_head = buf_tail = new char[sz];
    }
    std::streambuf *rdbuf() { return fi; }

    operator bool() { return !fail; }
    void flush() {
        if (buf_head == buf_tail) {
            buf_head = buf;
            buf_tail = buf + fi->sgetn(buf, sz);
        }
    }
    char get() {
        flush();
        char c = -1;
        if (buf_head == buf_tail)
            fail = 1;
        else
            c = *buf_head++;
        return c;
    }
    char peek() {
        flush();
        char c = -1;
        if (buf_head == buf_tail)
            fail = 1;
        else
            c = *buf_head;
        return c;
    }
    template <class T>
    scanner &operator>>(T &x) {
        _read(x);
        return *this;
    }
    template <class T>
    void operator()(T &x) { _read(x); }
    template <class T, class... Args>
    void operator()(T &x, Args &...args) {
        _read(x);
        operator()(args...);
    }
};

class printer {
private:
    std::streambuf *fi;
    std::string buf;
    int cbuf[PRINTER_STACK_SIZE];
    int ctop = 0;
    int prec = 6;

    template <class T>
    void _write(T x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = ~x + 1;
        }
        while (x) {
            cbuf[++ctop] = x % 10;
            x /= 10;
        }
        if (!ctop)
            put('0');
        while (ctop)
            put(cbuf[ctop--] ^ '0');
    }
    bool _round(int x) { return x > 4; }
    void _write(long double x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = -x;
        }
        int t = x;
        x -= t;
        ctop = 0;
        if (x) {
            do {
                cbuf[ctop++] = x * 10;
                x = x * 10 - cbuf[ctop - 1];
            } while (ctop < prec - 1);
            cbuf[ctop++] = (int) (x * 10 + _round((int) ((x * 10 - ((int) (x * 10))) * 10)));
            if (cbuf[ctop - 1] == 10) {
                int nt = ctop - 1;
                while (cbuf[nt] == 10 && nt) {
                    cbuf[nt] = 0;
                    cbuf[--nt] += 1;
                }
                if (!nt && cbuf[nt] == 10) {
                    cbuf[nt] = 0;
                    t += 1;
                }
            }
        }
        _write(t);
        put('.');
        for (int i = 0; i < ctop; i++)
            put(cbuf[i] ^ '0');
        for (int i = ctop; i < prec; i++)
            put('0');
    }
    void _write(double x) { _write((long double) x); }
    void _write(float x) { _write((long double) x); }
    void _write(const char x) { put(x); }
    void _write(char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(const char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(std::string x) {
        for (char i : x)
            put(i);
    }
    void _write(bool x) {
        if (x)
            _write(1);
        else
            _write(0);
    }
    template <class T>
    void _write(std::vector<T> x) {
        for (T i : x)
            _write(i);
    }

public:
    explicit printer(std::streambuf *_fi = std::cout.rdbuf(), size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    explicit printer(const char *_fi, size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    void reopen(std::streambuf *_fi, size_t _sz = IO_MAX_SIZE) {
        fi = _fi;
        buf.reserve(_sz);
    }
    void reopen(const char *_fi, size_t _sz = IO_MAX_SIZE) {
        static std::ofstream tp(_fi);
        fi = tp.rdbuf();
        buf.reserve(_sz);
    }
    std::streambuf *rdbuf() { return fi; }

    ~printer() { flush(); }
    void flush() {
        fi->sputn(buf.c_str(), buf.size());
        buf.clear();
    }
    void put(char x) { buf += x; }
    template <class T>
    printer &operator<<(T x) {
        _write(x);
        return *this;
    }
    template <class T>
    void operator()(T x) { _write(x); }
    template <class T, class... Args>
    void operator()(T x, Args &...args) {
        _write(x);
        operator()(args...);
    }
};

} // namespace hellolin

#endif