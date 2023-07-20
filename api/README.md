# Installing 
```bash
sudo apt install libiomp-dev
sudo apt-get install libsqlite3-dev
```

PATH=/usr/local/cuda/bin:$PATH

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../toolchains/jetson.toolchain.cmake -DNCNN_VULKAN=ON -DNCNN_BUILD_EXAMPLES=ON -DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc ..

https://github.com/AastaNV/JEP/blob/master/script/install_opencv4.6.0_Jetson.sh
https://qengineering.eu/overclocking-the-jetson-nano.html
https://qengineering.eu/install-opencv-4.5-on-jetson-nano.html
https://qengineering.eu/install-ncnn-on-jetson-nano.html

## Drogon
https://github.com/drogonframework/drogon/wiki/ENG-02-Installation

## glslang
https://chromium.googlesource.com/external/github.com/KhronosGroup/glslang/+/refs/tags/7.12.3352/README.md
https://github.com/KhronosGroup/SPIRV-Tools
https://github.com/KhronosGroup/Vulkan-Loader/blob/main/BUILD.md

## NCNN
https://qengineering.eu/install-ncnn-on-jetson-nano.html
```bash
sudo cp -r install/lib/*.a /usr/local/lib/
# sudo cp -r install/lib/cmake/ncnn /usr/local/lib/cmake/ncnn
```


If you get this error
```
CMake Error at /usr/local/share/cmake-3.26/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
  Could NOT find CUDA (missing: CUDA_TOOLKIT_ROOT_DIR CUDA_INCLUDE_DIRS
  CUDA_CUDART_LIBRARY) (found suitable exact version "10.2")
Call Stack (most recent call first):
  /usr/local/share/cmake-3.26/Modules/FindPackageHandleStandardArgs.cmake:600 (_FPHSA_FAILURE_MESSAGE)
  /usr/local/share/cmake-3.26/Modules/FindCUDA.cmake:1268 (find_package_handle_standard_args)
  glslang/CMakeLists.txt:252 (find_package)
  /usr/local/lib/cmake/opencv4/OpenCVConfig.cmake:108 (find_host_package)
  examples/CMakeLists.txt:17 (find_package)

```
run
```bash
sudo rm -rf /usr/local/lib/cmake/opencv4/
```


## GStreamer
```bash
sudo apt-get install -y gstreamer1.0-tools gstreamer1.0-nice gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-plugins-good libgstreamer1.0-dev git libglib2.0-dev libgstreamer-plugins-bad1.0-dev libsoup2.4-dev libjson-glib-dev
```


# Errors
## nvargus daemon frozen
```
Error generated. /dvs/git/dirty/git-master_linux/multimedia/nvgstreamer/gst-nvarguscamera/gstnvarguscamerasrc.cpp, execute:751 Failed to create CaptureSession
```
Run
```bash
sudo service nvargus-daemon restart
```


# References
https://github.com/Qengineering/Face-Recognition-with-Mask-Jetson-Nano/blob/main/src/TRetina.cpp

