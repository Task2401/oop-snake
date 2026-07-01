#ifndef INTERFACE_H
#define INTERFACE_H

class State;

class Interface {
    public:
        Interface();
        ~Interface();

        void init();
        void close();
        void draw_frame(const State& state);
};

#endif