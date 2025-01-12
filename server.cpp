#include <chrono>
#include <format>
#include <iostream>
#include <thread>
#include <zmq.hpp>

#include "tobii_gameintegration.h"

using namespace TobiiGameIntegration;
using namespace std::literals::chrono_literals;

static int PORT = 5556;

int main() {
    zmq::context_t ctx;
    zmq::socket_t sock(ctx, zmq::socket_type::pub);

    std::cout << "Connecting to " << "tcp://localhost:" + std::to_string(PORT) << '\n';

    sock.bind("tcp://localhost:" + std::to_string(PORT));

    ITobiiGameIntegrationApi* api = GetApi("Gaze Sample");

    IStreamsProvider* streamsProvider = api->GetStreamsProvider();

    api->GetTrackerController()->TrackRectangle({0, 0, 1000, 1000});

    while (true) {
        api->Update();

        GazePoint gazePoint;
        if (streamsProvider->GetLatestGazePoint(gazePoint)) {
            std::cout << "Gaze point: [" << gazePoint.X << ", " << gazePoint.Y << "]" << std::endl;
            std::string msg = std::format("{} {} {}", gazePoint.TimeStampMicroSeconds, gazePoint.X, gazePoint.Y);
            zmq::message_t message(msg.begin(), msg.end());
            sock.send(message);
        } else {
            std::cout << "Could not get gaze point.\n";
        }

        std::this_thread::sleep_for(50ms);
    }

    api->Shutdown();

    return 0;
}
