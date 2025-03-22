#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>

#define CLIENT_ID "" // CLIENT_ID for your application https://discord.com/developers/applications
#define PIPE_NAME L"\\\\.\\pipe\\discord-ipc-0"  

std::string serializeJSON(const std::string& key, const std::string& value) {
    return "\"" + key + "\": \"" + value + "\"";
}

std::string serializeJSON(int value) {
    return std::to_string(value);
}

std::string createHandshakePayload() {
    return "{ " + serializeJSON("v", "1") + ", " + serializeJSON("client_id", CLIENT_ID) + " }";
}

std::string createActivityPayload() {
    int startTime = static_cast<int>(std::time(nullptr));  

    std::ostringstream payload;
    // DOCS at = https://discord.com/developers/docs/rich-presence/overview
    payload << "{ "
        << "\"cmd\": \"SET_ACTIVITY\", "
        << "\"args\": { "
        << "\"pid\": " << GetCurrentProcessId() << ", "
        << "\"activity\": { "
        << "\"state\": \"Giocando una partita epica!\", "
        << "\"details\": \"Livello 7 - Foresta Incantata\", "
        << "\"timestamps\": { \"start\": " << startTime << " }, "
        << "\"assets\": { "
        << "\"large_image\": \"game_logo\", "
        << "\"large_text\": \"Gioco Fantastico\", "
        << "\"small_image\": \"hero_icon\", "
        << "\"small_text\": \"Eroe Leggendario\" "
        << "}, "
        << "\"buttons\": [ "
        << "{ \"label\": \"Gioca Ora\", \"url\": \"https://example.com\" }, "
        << "{ \"label\": \"Unisciti a noi!\", \"url\": \"https://discord.gg/example\" } "
        << "] "
        << "} "
        << "}, "
        << "\"nonce\": \"" << std::to_string(startTime) << "\" "
        << "}";

    return payload.str();
}

void sendPacket(HANDLE hPipe, uint32_t op, const std::string& payload) {
    uint32_t length = payload.size();
    char header[8];

    memcpy(header, &op, sizeof(op));
    memcpy(header + 4, &length, sizeof(length));

    DWORD bytesWritten;
    WriteFile(hPipe, header, sizeof(header), &bytesWritten, NULL);
    WriteFile(hPipe, payload.c_str(), length, &bytesWritten, NULL);
}

int main() {
    HANDLE hPipe = CreateFile(
        PIPE_NAME,           
        GENERIC_READ | GENERIC_WRITE,  
        0,                     
        NULL,                 
        OPEN_EXISTING,         
        0,                   
        NULL);                 

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Impossibile connettersi al pipe Discord." << std::endl;
        return 1;
    }

    std::cout << "Connesso a Discord!" << std::endl;
    std::string handshakePayload = createHandshakePayload();
    sendPacket(hPipe, 0, handshakePayload);
    std::cout << "Handshake completato!" << std::endl;

    std::string activityPayload = createActivityPayload();
    sendPacket(hPipe, 1, activityPayload);
    std::cout << "Rich Presence aggiornata!" << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(15));  
        sendPacket(hPipe, 1, activityPayload);
        std::cout << "Rich Presence aggiornata di nuovo!" << std::endl;
    }

    CloseHandle(hPipe);
    std::cout << "Connessione chiusa." << std::endl;

    return 0;
}
