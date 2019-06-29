#include <iostream>
#include <typeinfo>
#include "regex"

using namespace std;

class Parking;

class I_transport {
public:
    int time;
    string name;

    I_transport() { time = -1; };

    ~I_transport() {};

    virtual int pay(int a) = 0;
};

class Moto_transport : public I_transport {
public:
    Moto_transport() {
        time = 0;
    };

    Moto_transport(int a, string n) {
        time = a;
        name = n;
    }

    int pay(int a) override {
        return a * time;
    };

};

class Avto_transporrt : public I_transport {
public:
    unsigned int weight;
};

class Cargo_transport : public Avto_transporrt {
public:
    Cargo_transport() {
        time = 0;
    };

    Cargo_transport(int a, string n) {
        name = n;
        time = a;
    }

    int pay(int a) override {
        return a * time;
    };
};

class NonCargo_transport : public Avto_transporrt {
public:
    NonCargo_transport() {
        time = 0;
    };

    NonCargo_transport(int a, string n) {
        time = a;
        name = n;
    }

    int pay(int a) override {
        return a * time;
    };
};


class Parking {
    unsigned int count_of_tiers;
    unsigned int count_of_lots;
    I_transport ***Parking_lots;
    unsigned int moto_cost = 70;
    unsigned int cargo_cost = 100;
    unsigned int noncargo_cost = 90;
public:
    Parking(int a, int b) {
        count_of_tiers = a;
        count_of_lots = b;
        Parking_lots = new I_transport **[count_of_tiers];
        for (int i = 0; i < count_of_tiers; i++) {
            Parking_lots[i] = new I_transport *[count_of_lots];
        }
    }

    bool search_parking_lot(int i, int j) {
        return Parking_lots[i][j] == nullptr;
    }

    void park_a_transport(I_transport *a) {
        for (int i = 0; i < count_of_tiers; ++i) {
            for (int j = 0; j < count_of_lots; ++j) {
                if (search_parking_lot(i, j)) {
                    Parking_lots[i][j] = a;
                    return;
                }
            }
        }
    }

    void show_all_lots() {
        for (int i = 0; i < count_of_tiers; ++i) {
            for (int j = 0; j < count_of_lots; j++) {
                if (Parking_lots[i][j] != nullptr) {
                    cout << Parking_lots[i][j]->name << "    ";
                }
            }
            cout << endl;
        }
    }

    void get_from_park(/*I_transport *iTransport*/) {
        int min = 100000;
        int minI;
        int minJ;
        for (int i = 0; i < count_of_tiers; ++i) {
            for (int j = 0; j < count_of_lots; ++j) {
                if ((Parking_lots[i][j] != nullptr) && (Parking_lots[i][j]->time < min)) {
                    min = Parking_lots[i][j]->time;
                    minI = i;
                    minJ = j;
                }
            }
        }
        Parking_lots[minI][minJ] = nullptr;
    }

    void change_moto_cost(int a) {
        moto_cost = a;
    }

    void change_cargo_cost(int a) {
        cargo_cost = a;
    }

    void change_noncargo_cost(int a) {
        noncargo_cost = a;
    }

    int get_cost(Moto_transport &motoTransport) {
        return moto_cost;
    }

    int get_cost(Cargo_transport &cargoTransport) {
        return cargo_cost;
    }

    int get_cost(NonCargo_transport &motoTransport) {
        return noncargo_cost;
    }


};

int main() {
    Moto_transport *moto = new Moto_transport(10, "moto");
    Cargo_transport *cargo = new Cargo_transport(12, "Cargo");
    NonCargo_transport *noncargo = new NonCargo_transport(43, "noncargo");
    Parking Park(5, 20);
    Park.park_a_transport(moto);
    Park.park_a_transport(cargo);
    Park.park_a_transport(noncargo);
    Park.show_all_lots();
    Park.get_from_park();
    Park.show_all_lots();
    cout << moto->pay(Park.get_cost(*moto)) << endl;
    cout << cargo->pay(Park.get_cost(*cargo)) << endl;
    cout << noncargo->pay(Park.get_cost(*noncargo)) << endl;
    return 0;
}