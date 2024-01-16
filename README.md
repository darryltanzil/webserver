# Simple Web Server with Thread Pool

As a side project, I wanted to learn about thread pooling in C++!

This is a simple implementation of a web server in C++ with a built-in thread pool for handling multiple client connections concurrently. The web server serves static HTML content from an "index.html" file and responds to incoming HTTP requests.

## Prerequisites

Before you can run the web server, ensure that you have the following prerequisites installed on your system:

- CMake
- C++ Compiler (e.g., g++ on Linux, Xcode on macOS, or Visual Studio on Windows)

## Building the Project

Follow these steps to build/run/test the project using CMake:

```bash
# Navigate to the project directory:
cd webserver

# Set project directory to current, and build directory to build folder
cmake -S . -B build

# Make or insert your index.html into the build directory.
# Build the project
cmake --build build

# Run the webserver
cd build && ./webserver

# Run tests for web server
cd build && ./webserver
```

The index.html page will be viewable!
