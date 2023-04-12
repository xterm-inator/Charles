//
// Created by charles on 2/04/23.
//

#ifndef API_CAMERA_H
#define API_CAMERA_H

#define WIDTH 1280
#define HEIGHT 720

class videoSource;
class Image;

class Camera {
    public:
        Camera();
        bool Setup();
        int Capture(Image& NewImage);
        unsigned int GetImageSize();
    private:
        videoSource* Source;

};


#endif //API_CAMERA_H
