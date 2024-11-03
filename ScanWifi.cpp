#include "ScanWifi.h"
#include "DisplayLib.h"

// Khởi tạo WebServer cho ESP32 hoặc ESP8266
#ifdef ESP32
  WebServer server(80);
#else
  ESP8266WebServer server(80);
#endif

const int maxClients = 10; // Giới hạn số lượng client
String clientIPs[maxClients]; // Danh sách lưu IP
int clientCount = 0; // Biến đếm số lượng client

void wifiHotspot(const char* ssidAP, const char* passAP) {
    #ifdef ESP32
        WiFi.mode(WIFI_AP_STA);
    #else
        WiFi.mode(WIFI_AP);
    #endif
    WiFi.softAP(ssidAP, passAP); // Tạo AP với SSID và mật khẩu
    displayWifiAP(ssidAP);
    Serial.println("\nAP started: " + String(ssidAP));
}

void setupServer() {
    // Đăng ký route cho trang chính
    server.on("/", []() {
        server.send(200, "text/html", index_html); // Gửi nội dung trang chính
    });

    // Đăng ký route để quét mạng WiFi
    server.on("/scan", []() {
        int n = WiFi.scanNetworks(); // Quét các mạng WiFi
        String jsonResponse = "[";
        for (int i = 0; i < n; ++i) {
            jsonResponse += "{\"ssid\":\"" + String(WiFi.SSID(i)) + "\"}"; // Thêm SSID vào JSON
            if (i < n - 1) jsonResponse += ",";
        }
        jsonResponse += "]"; // Kết thúc JSON
        server.send(200, "application/json", jsonResponse); // Gửi dữ liệu JSON
    });

    // Đăng ký route để xử lý yêu cầu kết nối WiFi
    server.on("/connect", []() {
        String ssidWeb = server.arg("ssid");
        String passWeb = server.arg("password");
        
        Serial.println("Received SSID: " + ssidWeb);
        Serial.println("Received Password: " + passWeb);

        connectWifi(ssidWeb.c_str(), passWeb.c_str());

        if (WiFi.status() == WL_CONNECTED) {
            server.send(200, "text/plain", "Connected to " + ssidWeb);
            Serial.println("\nConnected to " + String(ssidWeb));
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            displayConnectedWifi();
        } else {
            server.send(200, "text/plain", "Failed to connect to " + ssidWeb);
            Serial.println("\nFailed to connect to " + ssidWeb);
        }
    });

    // Route catch-all cho Captive Portal
    server.onNotFound([]() {
        server.sendHeader("Location", "/"); // Chuyển hướng đến trang chính
        server.send(302, "text/plain", ""); // Gửi phản hồi chuyển hướng
    });

    // Bắt đầu server
    server.begin();
    Serial.println("HTTP server started");
}

bool isIPInList(const String& ip) {
    // Kiểm tra xem IP đã tồn tại trong danh sách không
    for (int i = 0; i < clientCount; i++) {
        if (clientIPs[i] == ip) {
            return true; // IP đã tồn tại
        }
    }
    return false; // IP chưa tồn tại
}

void handleClient() {
    // Lấy địa chỉ IP của client
    IPAddress ip = server.client().remoteIP();
    
    // Kiểm tra nếu địa chỉ IP đã có trong danh sách
    if (!isIPInList(ip.toString()) && clientCount < maxClients) {
        clientIPs[clientCount] = ip.toString(); // Thêm địa chỉ IP mới vào danh sách
        Serial.println("Client " + String(clientCount + 1) + " connected: " + clientIPs[clientCount]);
        clientCount++; // Tăng biến đếm
    }
    server.handleClient(); // Xử lý các yêu cầu từ client
}
