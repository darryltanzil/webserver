#pragma once

#include <string>
#include <netinet/in.h>

// Forward declaration of ThreadPool to avoid including its header.
class ThreadPool;

class WebServer {
public:
    /**
     * Start: Initializes the web server and starts listening for client connections.
     */
    [[noreturn]] void Start();

    /**
     *  Stop: Stops the web server.
     */
    void Stop();

    /**
     * ReadFileContent: Reads the content of a file and returns it as a string.
     * @param filename: The name of the file to be read.
     * @return The content of the file.
     */
    static std::string ReadFileContent(const std::string& filename);

private:
    /**
     * HandleRequest: Processes an incoming client request.
     * @param clientSocket: The socket descriptor for the client connection.
     */
    static void HandleRequest(int clientSocket);

    /**
     * ReadRequest: Reads the incoming HTTP request from the client socket.
     * @param clientSocket: The socket descriptor for the client connection.
     * @return The HTTP request as a string.
     */
    static std::string ReadRequest(int clientSocket);

    /**
     * ProcessRequest: Processes the request and prepares the response.
     * @param clientSocket: The socket descriptor for the client connection.
     * @param request: The HTTP request received from the client.
     */
    static void ProcessRequest(const std::string& request, int clientSocket);

    /**
     * GenerateResponse: Generates the HTTP response based on the request path.
     * @param path: The path extracted from the HTTP request.
     * @return The HTTP response as a string.
     */
    static std::string GenerateResponse(const std::string& path);

    /**
     * SendResponse: Sends the response to the client socket.
     * @param clientSocket: The socket descriptor for the client connection.
     * @return response: The HTTP response to be sent to the client.
     */
    static void SendResponse(int clientSocket, const std::string& response);


    /**
     * LoadFileContent: Loads the content of 'index.html' into memory.
     */
    static void LoadFileContent();

    int serverSocket;                 // Socket descriptor for the server.
    static std::string fileContent;   // Content of the file loaded into memory.
    struct sockaddr_in serverAddress; // Server address information.
    bool running = true;
};
