#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <functional>

namespace DT {
class Scheduler;
}

// performs a given task with the given delay
class DT::Scheduler {
private:

    std:: function < void() > _task;
    int _counter;

public:

    Scheduler() {
        _task = []() {};
        _counter = 0;
    }

    Scheduler(int delay, std:: function < void() > task) {
        _task = task;
        _counter = delay;
    }

    void operator++(int) {
        if (on()) {
            _counter--;
            if (_counter == 0)
                _task();
        }
    }

    bool on() {
        return _counter > 0;
    }
};
#endif // SCHEDULER_H
