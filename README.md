# Hướng dẫn sử dụng thư viện DisplayLib.h cho OLED 128x64 trên ESP32 và ESP8266

## Giới thiệu
Thư viện `DisplayLib.h` hỗ trợ hiển thị trên màn hình OLED 128x64, sử dụng cho các dòng vi điều khiển ESP32 và ESP8266. Thư viện tích hợp sẵn các thư viện cần thiết và cung cấp nhiều hàm hỗ trợ để kết nối WiFi, NTP Server, và hiển thị thông tin lên màn hình OLED.
Version 2.0.0 đã thêm tính năng Scan Wifi và hiển thị lên web server.

## Hướng dẫn sử dụng
Tải file nén DisplayLib.zip về và thêm vào thư viện Arduino của bạn `Mở Arduino IDE, chọn Sketch -> Include Library -> Add .ZIP Library...`
Sau khi thêm thành công chỉ cần thêm dòng sau vào file `.ino` để sử dụng thư viện:
`#include "DisplayLib.h"`

## Các thư viện tích hợp
File `DisplayLib.h` đã tự động tích hợp các thư viện sau:
- [`<wire.h>`](https://github.com/codebendercc/arduino-library-files/blob/master/libraries/Wire/Wire.h): Thư viện cho màn OLED sử dụng giao tiếp I2C.
- [`<time.h>`](https://github.com/ebrevdo/arduino/blob/master/libraries/Time/Time.h): Lấy dữ liệu thời gian thực qua NTP server.
- [`<Adafruit_GFX.h>`](https://github.com/adafruit/Adafruit-GFX-Library): Thư viện hỗ trợ giao diện hiển thị cho OLED.
- [`<Wifi.h>`](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h) hoặc [`<ESP8266WiFi.h>`](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h): Tự động thêm thư viện phù hợp với loại board mạch.
- [`<Adafruit_SSD1306.h>`](https://github.com/adafruit/Adafruit_SSD1306) hoặc [`<Adafruit_SH110X.h>`](https://github.com/adafruit/Adafruit_SH110x): Tự động chọn thư viện hiển thị OLED phù hợp với driver màn hình OLED.
- [`WebServer.h`](https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/src/WebServer.h) và [`ESP8266WebServer.h`](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h): Thư viện cấu hình webserver cho ESP.


### Sơ đồ đấu nối OLED
- **ESP32**: SCL-22, SDA-21
- **ESP8266**: SCL-5(D1), SDA-4(D2)

## Tổng hợp hàm sử dụng:
- void checkOLED();
- void drawBitmap(const uint8_t* bitmap, int16_t x, int16_t y, int16_t width, int16_t height);
- void displayConnectWifi(const char* ssid);
- void displayConnectedWifi();
- void connectWifi(const char* ssid, const char* pass);
- void connectedWifi(const char* ssid);
- void checkWifi(const char* ssid, const char* pass);
- void displayConnectingNTP();
- void displayConnectedNTP();
- void displayTime();
- void displayTimeSerial();
- void updateTime();
- bool connectNTP();
- void wifiHotspot(const char* ssidAP, const char* passAP);
- void setupServer();
- void handleClient();

## Tính năng các hàm
### void checkOLED();
Kiểm tra kết nối với màn hình OLED có thành công hay không, nếu không sẽ dừng toàn bộ chương trình.

### void drawBitmap(const uint8_t* bitmap, int16_t x, int16_t y, int16_t width, int16_t height);
Vẽ hình ảnh bitmap lên màn OLED với tọa độ `x`, `y`, chiều rộng `width`, chiều cao `height`.
Ví dụ: `void drawBitmap(bitmap, 0, 0, 128, 64);`

### void displayConnectWifi(const char* ssid);
Hiển thị trên màn hình OLED quá trình chờ kết nối tới WiFi với tên `ssid`.

### void displayConnectedWifi();
Hiển thị thông báo đã kết nối thành công tới WiFi và hiển thị IP của ESP lên màn hình OLED.

### void connectWifi(const char* ssid, const char* pass);
Kết nối tới WiFi có tên `ssid` và mật khẩu là `pass`.

### void connectedWifi();
Thông báo đã kết nối Wifi thành công.

### void checkWifi(const char* ssid, const char* pass);
Kiểm tra trạng thái kết nối WiFi, nếu bị ngắt kết nối sẽ tự động kết nối lại tới WiFi cũ.

### void displayConnectingNTP();
Hiển thị trạng thái đang kết nối tới NTP Server để lấy thời gian thực.

### void displayConnectedNTP();
Hiển thị thông báo đã kết nối thành công tới NTP Server.

### void displayTime();
Hiển thị thời gian thực lên phần header của màn hình OLED.

### void displayTimeSerial();
Hiển thị thời gian trên Serial Monitor để kiểm tra.

### void updateTime();
Cập nhật thời gian thực từ NTP Server.

### bool connectNTP();
Kiểm tra và kết nối tới NTP Server để lấy thời gian thực.

### void wifiHotspot(const char* ssidAP, const char* passAP);
Chuyển chế độ ESP sang AP để phát 1 wifi có tên `ssidAP` với mật khẩu `passAP` để Client có thể kết nối tới Webserver.

### void setupServer();
Cấu hình thiết lập Webserver.

### void handleClient();
Kiểm tra các yêu cầu từ Client

## Ảnh Bitmap được khai báo
### Header disconnect wifi
<img src="Bitmap Picture/Header NoWifi 128x12.bmp?raw=true" width="300px"><br/>
### Header connected wifi
<img src="Bitmap Picture/Header 128x12.bmp?raw=true" width="300px"><br/>
### Robot face
| Normal | Funny | NoFeel | NoEye | Sad | Angry |
|--------|-------|--------|-------|-----|-------|
| <img src="Bitmap Picture/Robot Face/Normal.bmp?raw=true" width="200px"> | <img src="Bitmap Picture/Robot Face/Funny.bmp?raw=true" width="200px"> | <img src="Bitmap Picture/Robot Face/NoFeel.bmp?raw=true" width="200px"> | <img src="Bitmap Picture/Robot Face/NoEye.bmp?raw=true" width="200px"> | <img src="Bitmap Picture/Robot Face/Sad.bmp?raw=true" width="200px"> | <img src="Bitmap Picture/Robot Face/Angry.bmp?raw=true" width="200px"> |
