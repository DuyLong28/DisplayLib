# Hướng dẫn sử dụng thư viện Display_Lib.h cho OLED 128x64 trên ESP32 và ESP8266

## Giới thiệu
Thư viện `Display_Lib.h` hỗ trợ hiển thị trên màn hình OLED 128x64, sử dụng cho các dòng vi điều khiển ESP32 và ESP8266. Thư viện tích hợp sẵn các thư viện cần thiết và cung cấp nhiều hàm hỗ trợ để kết nối WiFi, NTP Server, và hiển thị thông tin lên màn hình OLED.

## Hướng dẫn sử dụng
Chỉ cần thêm dòng sau vào file `.ino` để sử dụng thư viện:
#include "Display_Lib.h"

## Các thư viện tích hợp
File `Display_Lib.h` đã tự động tích hợp các thư viện sau:
- `<wire.h>`: Thư viện cho màn OLED sử dụng giao tiếp I2C.
- `<time.h>`: Lấy dữ liệu thời gian thực qua NTP server.
- `<Adafruit_GFX.h>`: Thư viện hỗ trợ giao diện hiển thị cho OLED.
- `<Wifi.h>` hoặc `<ESP8266WiFi.h>`: Tự động thêm thư viện phù hợp với loại board mạch.
- `<Adafruit_SSD1306.h>` hoặc `<Adafruit_SH110X.h>`: Tự động chọn thư viện hiển thị OLED phù hợp với driver màn hình OLED.

### Sơ đồ đấu nối OLED
- **ESP32**: SCL-22, SDA-21
- **ESP8266**: SCL-5(D1), SDA-4(D2)

## Tổng hợp hàm sử dụng:
- void checkOLED();
- void drawBitmap(const uint8_t* bitmap, int16_t x, int16_t y, int16_t width, int16_t height);
- void displayConnectWifi(const char* ssid);
- void displayConnectedWifi();
- void connectWifi(const char* ssid, const char* pass);
- void checkWifi(const char* ssid, const char* pass);
- void displayConnectingNTP();
- void displayConnectedNTP();
- void displayTime();
- void displayTimeSerial();
- void updateTime();
- bool connectNTP();

## Các hàm hỗ trợ
### **void checkOLED();**
Kiểm tra kết nối với màn hình OLED có thành công hay không, nếu không sẽ dừng toàn bộ chương trình.

### **void drawBitmap(const uint8_t* bitmap, int16_t x, int16_t y, int16_t width, int16_t height);**
Vẽ hình ảnh bitmap lên màn OLED với tọa độ `x`, `y`, chiều rộng `width`, chiều cao `height`.
Ví dụ: void drawBitmap(bitmap, 0, 0, 128, 64);

### **void displayConnectWifi(const char* ssid);**
Hiển thị trên màn hình OLED quá trình chờ kết nối tới WiFi với tên `ssid`.

### **void displayConnectedWifi();**
Hiển thị thông báo đã kết nối thành công tới WiFi và hiển thị IP của ESP lên màn hình OLED.

### **void connectWifi(const char* ssid, const char* pass);**
Kết nối tới WiFi có tên `ssid` và mật khẩu là `pass`. Nếu kết nối thành công sẽ hiển thị trạng thái kết nối.

### **void checkWifi(const char* ssid, const char* pass);**
Kiểm tra trạng thái kết nối WiFi, nếu bị ngắt kết nối sẽ tự động kết nối lại tới WiFi cũ.

### **void displayConnectingNTP();**
Hiển thị trạng thái đang kết nối tới NTP Server để lấy thời gian thực.

### **void displayConnectedNTP();**
Hiển thị thông báo đã kết nối thành công tới NTP Server.

### **void displayTime();**
Hiển thị thời gian thực lên phần header của màn hình OLED.

### **void displayTimeSerial();**
Hiển thị thời gian trên Serial Monitor để kiểm tra.

### **void updateTime();**
Cập nhật thời gian thực từ NTP Server.

### **bool connectNTP();**
Kiểm tra và kết nối tới NTP Server để lấy thời gian thực.

## Sử dụng trong các dự án
Bạn có thể sử dụng thư viện này để phát triển các dự án IoT, theo dõi thời gian thực và hiển thị thông tin lên màn OLED một cách dễ dàng với các hàm đã cung cấp.
