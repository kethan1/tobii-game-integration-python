# Tobii Game Integration SDK in Python

## Rationale

Tobii's non-research oriented eyetracking models are solely compatible with their Game Integration API, which they only provide C++ and C# bindings for. While a wrapper could be written about the C++ API (using a tool like pybind11 or Swig) for Python, this can be difficult to get reliably working (I attempted to use Swig to wrap the C++ API, and while it compiled and functions could be used, it never detected the Tobii hardware).

For this reason, using a message passing protocol like ZeroMQ and a publisher (in C++) and subscriber (in the target language, in this case Python) model can be easier to implement. This repository aims to be an example for this usage.

## Prerequisites

I have tested this on Windows 11 with [Visual Studio 2022](https://visualstudio.microsoft.com/vs). Your millage on other platforms may vary. Please file an issue if you have any problems.

### Pull the Repository

Pull the repository and its submodules with theis command:
```
git clone --recurse-submodules --depth=1 https://github.com/kethan1/tobii-game-integration-python.git
```

### Configure Vcpkg

Vcpkg is used to download the cppzmq library. To configure it, ensure that you have pulled the submodules and run these commands from the root of the repo:
```
cd libs/vcpkg
./bootstrap-vcpkg.bat
cd ../
```

### Tobii Game Integration Library

Due to the license agreement for the Tobii Game Integration API, its file cannot be distributed. For this reason, you must obtain the library from https://developer.tobii.com/pc-gaming/downloads (it should take roughly <48 hours for them to send the library). Ensure that the directory follows this structure (`tobii_gameintegration_<version here>`). This code has been tested with version 9.0.4.26 of the library.

### C++ Toolchain

Make sure that you have [CMake](https://cmake.org) installed and a working C++ compile. If you are on Windows 11, you can install these with [Visual Studio](https://visualstudio.microsoft.com/vs). You may be able to use [MSYS2](https://www.msys2.org]), but I have not tested this myself.

## Building + Running

Ensure that you have configure Vcpkg. Then run these commands:
```
mkdir build
cd build
cmake ../ && cmake --build .
```

Then, to run these C++ publisher (publishes Gaze Data), run the following command:
```
./Debug/eyetracker-server.exe
```

To run the Python subscriber, install the requirements:
```
pip install -r requirements.txt
```

Then run the `recv.py` script:
```
python recv.py
```
