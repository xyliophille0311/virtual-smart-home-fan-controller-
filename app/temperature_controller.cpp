#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>

enum class FanState {
    OFF,
    LOW,
    HIGH
};

class FanController {
private:
    int temperature;
    FanState state;

    // Mutex protects shared fan data
    std::mutex fanMutex;

public:
    FanController(int temp) {
        temperature = temp;
        state = FanState::OFF;
    }

    void controlFan() {

        // Lock the critical section
        std::lock_guard<std::mutex> lock(fanMutex);

        // Decide fan state based on temperature
        if (temperature < 25) {
            state = FanState::OFF;
        }
        else if (temperature < 35) {
            state = FanState::LOW;
        }
        else {
            state = FanState::HIGH;
        }

        // Display temperature
        std::cout << "Temperature: "
                  << temperature
                  << " C"
                  << std::endl;

        // Display fan state
        std::cout << "Fan: ";

        switch (state) {

            case FanState::OFF:
                std::cout << "OFF";
                break;

            case FanState::LOW:
                std::cout << "LOW";
                break;

            case FanState::HIGH:
                std::cout << "HIGH";
                break;
        }

        std::cout << std::endl;

        // Save status to log file
        logStatus();

        // Send temperature to TCP server
        sendTemperature();
    }

private:

    void sendTemperature() {

        // Create TCP socket
        int clientSocket = socket(
            AF_INET,
            SOCK_STREAM,
            0
        );

        if (clientSocket < 0) {
            std::cout
                << "Network error: Socket creation failed."
                << std::endl;
            return;
        }

        // Configure server address
        sockaddr_in serverAddress{};

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);

        if (inet_pton(
                AF_INET,
                "127.0.0.1",
                &serverAddress.sin_addr
            ) <= 0) {

            std::cout
                << "Network error: Invalid server address."
                << std::endl;

            close(clientSocket);
            return;
        }

        // Connect to server
        if (connect(
                clientSocket,
                (struct sockaddr*)&serverAddress,
                sizeof(serverAddress)
            ) < 0) {

            std::cout
                << "Network error: Could not connect to server."
                << std::endl;

            close(clientSocket);
            return;
        }

        // Convert temperature to string
        std::string message =
            std::to_string(temperature);

        // Send temperature
        ssize_t bytesSent = send(
            clientSocket,
            message.c_str(),
            message.length(),
            0
        );

        if (bytesSent < 0) {
            std::cout
                << "Network error: Failed to send temperature."
                << std::endl;
        }
        else {
            std::cout
                << "Temperature sent to server."
                << std::endl;
        }

        // Close socket
        close(clientSocket);
    }

    void logStatus() {

        std::ofstream logFile(
            "logs/fan_log.txt",
            std::ios::app
        );

        if (!logFile) {
            std::cout
                << "Error: Could not open log file."
                << std::endl;
            return;
        }

        logFile
            << "Temperature: "
            << temperature
            << " C, Fan: ";

        switch (state) {

            case FanState::OFF:
                logFile << "OFF";
                break;

            case FanState::LOW:
                logFile << "LOW";
                break;

            case FanState::HIGH:
                logFile << "HIGH";
                break;
        }

        logFile << std::endl;

        logFile.close();
    }
};

int main(int argc, char* argv[]) {

    int temperature = 30;

    // Take temperature from command line
    if (argc > 1) {

        try {
            size_t position = 0;

            temperature = std::stoi(
                argv[1],
                &position
            );

            // Make sure the complete input is a number
            if (position != std::string(argv[1]).length()) {
                std::cout
                    << "Error: Invalid temperature input."
                    << std::endl;
                return 1;
            }

        }
        catch (const std::exception&) {

            std::cout
                << "Error: Invalid temperature input."
                << std::endl;

            return 1;
        }
    }

    // Create FanController object
    FanController fan(temperature);

    // Create a separate thread for fan control
    std::thread fanThread(
        &FanController::controlFan,
        &fan
    );

    // Wait for the thread to finish
    fanThread.join();

    return 0;
}