#include <iostream>
#include <csignal>
#include <jetson-utils/logging.h>
#include <algorithm>

#include "Camera.h"
#include "Image.h"
#include "FaceDetect.h"
#include "TRetina.h"

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

    FaceDetect FaceDetect;

//    TRetina FaceRec(1280, 720);

    LogVerbose("finished starting\n");

    while (!SignalReceived)
    {
        Image Image;
        Camera.Capture(Image);

        FaceDetect.Detect(Image);

//        TRetina FaceRec(Image.GetWidth(), Image.GetHeight());
    }

    return 0;
}
