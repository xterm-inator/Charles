#include <iostream>
#include <csignal>
#include <jetson-utils/logging.h>

#include "Camera.h"
#include "Image.h"

bool SignalReceived = false;

void sig_handler(int Signo)
{
    if (Signo == SIGINT)
    {
        LogVerbose("received SIGINT\n");
        SignalReceived = true;
    }
}

int main() {
    LogVerbose("starting\n");

    Camera Camera;
    Camera.Setup();

    while (!SignalReceived)
    {
        Image Image;
        int result = Camera.Capture(Image);
        LogVerbose("capture status: %i\n", result);
    }

    std::cout << "this is a test" << std::endl;
    return 0;
}
