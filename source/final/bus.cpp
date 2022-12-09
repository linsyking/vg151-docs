class Ticket {
public:
    Ticket(int _n, int _s) : n(_n), s(_s) {
        if (s < 0 || s > 10) throw std::exception();
    }
    int  number() { return n; }
    int  size() { return s; }
    void print() { std::cout << "number:" << n << ",luggage:" << s; }

private:
    int n, s;
};

class Bus {
public:
    Bus(int _seats, int _capacity) : seats(_seats), capacity(_capacity) {}
    void getIn(std::vector<Passenger> &v);
    void travel();
    void getOut();

private:
    static bool           passengerCmp(Passenger const &a, Passenger const &b);
    std::stack<Passenger> stack;
    int                   seats, capacity;
};

class Passenger {
public:
    Passenger(Ticket _t) : t(_t) {}
    Ticket ticket() { return t; }

private:
    Ticket t;
};
