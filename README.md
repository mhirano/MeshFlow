This project contains a minimum set of files to work with OpenCV + CMake.

- Primarily designed for CLion and Mac, but should work with other IDEs and operating system.

- You should add paths before compile. For ease of use, here is excerpt from my .bash_profile
```
# OpenCV
export OpenCV_DIR=/Users/mhirano/opencv-3.2.0/build
export OpenCV_LIBS=/Users/mhirano/opencv-3.2.0/build/lib
export OpenCV_INCLUDE_DIRS=/Users/mhirano/opencv-3.2.0/include
```

- Use out-of-source build. Namely, run cmake within debug/release directory as `cmake ..`

- C++11 is activated by default if available.
