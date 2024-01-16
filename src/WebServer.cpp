#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ThreadPool.h"
#include "WebServer.h"

std::string WebServer::fileContent;

// Start: Initializes the web server and starts listening for client connections.
[[noreturn]] void WebServer::Start() {

    int clientSocket;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    LoadFileContent();

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 2000);
    std::cout << "Server started at address: 127.0.0.1, port: 8080" << std::endl;

    ThreadPool pool(2000);  // Thread pool for handling requests

    while (running) {
        clientAddressLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;  // Continue accepting other connections
        }

        // Handle each request in a separate thread
        std::thread requestThread([this, clientSocket]() {
            HandleRequest(clientSocket);
            close(clientSocket);  // Close the client socket after handling the request
        });
        requestThread.detach();  // Detach the thread to handle the connection independently
    }

    close(serverSocket);
}

void WebServer::HandleRequest(int clientSocket) {
    std::string request = ReadRequest(clientSocket);
    ProcessRequest(request, clientSocket);
}

std::string WebServer::ReadRequest(int clientSocket) {
    std::string request;
    char buffer[512];
    ssize_t bytesRead;
    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        request += buffer;
        if (request.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }
    return request;
}

void WebServer::ProcessRequest(const std::string& request, int clientSocket) {
    std::istringstream iss(request);
    std::string requestLine;
    std::getline(iss, requestLine);

    std::istringstream requestLineStream(requestLine);
    std::string method, path, protocol;
    requestLineStream >> method >> path >> protocol;

    std::string response = GenerateResponse(path);
    SendResponse(clientSocket, response);
}

std::string WebServer::GenerateResponse(const std::string& path) {
    std::string content;
    std::string response;
    std::ostringstream responseStream;

    if (path == "/") {
        content =  fileContent.empty() ? ReadFileContent("index.html") : fileContent;
    } else {
        content = ReadFileContent(path.substr(1));
    }

    if (!content.empty()) {
        responseStream << "HTTP/1.1 200 OK\r\n"
                       << "Content-Type: text/html\r\n"
                       << "Content-Length: " << content.length() << "\r\n"
                       << "Cache-Control: public, max-age=3600\r\n"
                       << "\r\n"
                       << content;
    } else {
        responseStream << "HTTP/1.1 404 Not Found\r\n"
                       << "Content-Type: text/plain\r\n"
                       << "Content-Length: 9\r\n"
                       << "\r\n"
                       << "Not Found";
    }

    return responseStream.str();
}

void WebServer::SendResponse(int clientSocket, const std::string& response) {
    write(clientSocket, response.c_str(), response.length());
    close(clientSocket);
}

std::string WebServer::ReadFileContent(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        std::ostringstream oss;
        oss << file.rdbuf();
        return oss.str();
    }
    return "";
}

void WebServer::LoadFileContent() {
    std::ifstream file("index.html", std::ios::binary);
    if (file) {
        std::ostringstream oss;
        oss << file.rdbuf();
        fileContent = oss.str();
    } else {
        std::cerr << "Failed to load file content." << std::endl;
    }
}

void WebServer::Stop() {
    running = false;
}


int main() {
    WebServer server;
    server.Start();

    return 0;
}
