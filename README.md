# Simple Web Server with Thread Pool

As a side project, I wanted to learn about thread pooling in C++!

This is a simple implementation of a web server in C++ with a built-in thread pool for handling multiple client connections concurrently. The web server serves static HTML content from an "index.html" file and responds to incoming HTTP requests.

## Prerequisites

Before you can run the web server, ensure that you have the following prerequisites installed on your system:

- CMake
- C++ Compiler (e.g., g++ on Linux, Xcode on macOS, or Visual Studio on Windows)

## Building the Project

Follow these steps to build the project using CMake:

```
# Navigate to the project directory:
cd webserver

# Create a build directory:
mkdir build

# Enter the build directory:
cd build

# Run CMake to configure the project:
cmake ..

# Build the project using your C++ compiler (e.g., g++, Xcode, Visual Studio):
cmake --build .
```

To run:
```
# From the build directory, navigate to the "bin" directory:
cd bin

# Start the web server by running the executable:
./webserver
```
The index.html page will be viewable!
