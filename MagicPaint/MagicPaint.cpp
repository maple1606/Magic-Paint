#include "MainControl.h"

int main() {
    MainControl* mainControl = new MainControl();
    if (mainControl->init()) {
        mainControl->setMode();
    }
    mainControl->close();
    return 0;
}