#include "sensorReaderModule.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>



/*
    This is an example file showcasing how one module inside a generated project might look:
*/

// =========================
// Don't touch this!
sensorReaderModule::sensorReaderModule() : moduleIntermediary(requests::moduleIds::sensorReaderModule), moduleId(getDerivedModuleId())
{

}

sensorReaderModule::~sensorReaderModule()
{
}
// =========================

void    sensorReaderModule::onModuleStart()
{
    setModuleState(moduleStates::ACTIVE);

    std::cout << "sensorReaderModule started\n";
    
    // Initialize random seed for sensor simulation
    srand(static_cast<unsigned int>(time(nullptr)));

    // Demonstrate inter-module communication capabilities
    demonstrateInterModuleCommunication();
    
    // Example: Simulate sensor reading and data processing workflow
    simulateSensorReading();
}

void    sensorReaderModule::simulateSensorReading()
{
    std::cout << "Starting sensor reading simulation...\n";
    
    // Simulate reading temperature sensor data
    for (int i = 0; i < 5; i++) {
        double temperature = 20.0 + (rand() % 100) / 10.0; // Random temp between 20-30°C
        std::cout << "Read temperature: " << temperature << "°C\n";
        
        // Send data to dataProcessor module
        sendSensorDataToProcessor(temperature);
        
        // Wait before next reading
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void    sensorReaderModule::sendSensorDataToProcessor(double sensorValue)
{
    std::cout << "Sending sensor data (" << sensorValue << ") to dataProcessor...\n";
    
    // Create a test request to send data to dataProcessor
    requests::requests::testRequest request(
        requests::moduleIds::sensorReaderModule,  // sender
        requests::moduleIds::dataProcessorModule  // receiver
    );
    
    // Pack the sensor value into payload
    requests::payload payload;
    payload.d = sensorValue;
    
    // Send the request
    request.send(payload);
    
    std::cout << "Sensor data sent to dataProcessor\n";
}

void    sensorReaderModule::requestNetworkStatus()
{
    std::cout << "Requesting network status from networkManager...\n";
    
    // Create request to networkManager
    requests::requests::testRequest request(
        requests::moduleIds::sensorReaderModule,
        requests::moduleIds::networkManagerModule
    );
    
    // Send empty payload for status request
    requests::payload payload;
    payload.i = 1; // Use integer to indicate status request type
    
    // Send and wait for reply
    requests::payload reply = request.sendAndGetReply(payload);
    
    std::cout << "Network status received: " << reply.i << "\n";
}

void    sensorReaderModule::demonstrateInterModuleCommunication()
{
    std::cout << "\n=== Demonstrating inter-module communication ===\n";
    
    // Example 1: Send test request to dataProcessor
    std::cout << "1. Sending test request to dataProcessor...\n";
    requests::requests::testRequest testReq1(
        requests::moduleIds::sensorReaderModule,
        requests::moduleIds::dataProcessorModule
    );
    
    requests::payload testPayload;
    testPayload.i = 42;
    testReq1.send(testPayload);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Example 2: Send test request to networkManager  
    std::cout << "2. Sending test request to networkManager...\n";
    requests::requests::testRequest testReq2(
        requests::moduleIds::sensorReaderModule,
        requests::moduleIds::networkManagerModule
    );
    
    testPayload.c = 'A';
    testReq2.send(testPayload);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Example 3: Request status from network manager
    requestNetworkStatus();
    
    std::cout << "=== Inter-module communication demo complete ===\n\n";
}


void   sensorReaderModule::testRequest_Handler(const requests::payload &p, requests::requests::incomingRequestInfo &info)
{
    (void)p;
    std::cout << "sensorReaderModule caught testRequest request, handling...\n";

    // Simulated work
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "sensorReaderModule Handled testRequest request\n";
}