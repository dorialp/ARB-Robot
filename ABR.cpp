#include "movementlibrary.h"
#include "pixy2library.h"
#include <chrono>
#include <thread>
#include "ABR.h"
using namespace std;

Pixy2 pixy;
bool run = true;

void turn(int dir, int centerDistance) {
    int angle = (centerDistance / pixy.uint16_t) * 90;
    backwheel.rotate(dir * angle);
    frontwheels.updateAcceleration(100 - (angle / 90) * 100);
}

int spin() {
    backwheel.rotate(45);
    frontwheels.updateAcceleration(30);
    chrono::seconds interval(0.1);
    for (int i = 0; i < 30; ++i) {
        if (pixy.ccc.getBlocks() > 0) {
            frontwheels.updateAcceleration(0);
            return 1;
        }
        this_thread::sleep_for(interval);
    }
    run = false;
    return 0;
}

void centerBlock(Block closest) {
    if (pixy.uint16_t / 2 < closest.uint16_t m_x) {
        turn(1, closest.uint16_t m_x - pixy.uint16_t / 2 );
    } else {
        turn(-1, pixy.uint16_t / 2 - closest.uint16_t m_x);
    }
}

int main() {
    if (pixy.init() < 0) {
        cout << "CONNECTION ERROR\n";
        return -1;
    }
    do {
        while (pixy.ccc.getBlocks() > 0) {
            centerBlock(pixy.ccc.blocks[0])
        }

        spin();
    } while (run);

    returnToStart();
    return 0;
}