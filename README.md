# Simple Web Server with Thread Pool

As a side project, I wanted to learn about thread pooling in C++!

This is a simple implementation of a web server in C++ with a built-in thread pool for handling multiple client connections concurrently. The web server serves static HTML content from an "index.html" file and responds to incoming HTTP requests.

### Core Components

#### WebServer Class

**Network Communication:** Uses TCP/IP sockets for stable and reliable data exchange.
**Concurrency Handling**: Leverages a ThreadPool for managing simultaneous client requests.
**Request Processing:** Each client connection is handled in a dedicated thread from the pool.
**Content Serving:** Preloads "index.html" into memory to minimize I/O operations.
**HTTP Protocol Management:** Parses HTTP requests and constructs appropriate responses, setting standard headers.
**Scalability and Responsiveness:** Maintains the main thread's availability for incoming connections.

#### Threadpool Class
**Thread Management:** Initializes with a fixed number of threads to handle incoming tasks.
**Task Queuing and Execution:** Allows enqueuing of tasks (jobs) which are then executed by available worker threads.
**Resource Utilization:** Reduces the overhead of continuous thread creation and deletion.
**Optimization and Performance**
**Memory Management**: Uses string streams for file reading and a fixed-size buffer for network data, saving memory
**Load Optimization:** Preloads frequently accessed content, reducing repetitive index.html access.

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
cd build && ctest
```

The index.html page will be viewable!
