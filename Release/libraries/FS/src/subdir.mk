################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Users\ylabr\git\arduino-esp32\libraries\FS\src\FS.cpp \
C:\Users\ylabr\git\arduino-esp32\libraries\FS\src\vfs_api.cpp 

LINK_OBJ += \
.\libraries\FS\src\FS.cpp.o \
.\libraries\FS\src\vfs_api.cpp.o 

CPP_DEPS += \
.\libraries\FS\src\FS.cpp.d \
.\libraries\FS\src\vfs_api.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\FS\src\FS.cpp.o: C:\Users\ylabr\git\arduino-esp32\libraries\FS\src\FS.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Users/ylabr/git/arduino-esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++" -DESP_PLATFORM -IMBEDTLS_CONFIG_FILE="mbedtls/esp_config.h" -DHAVE_CONFIG_H "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/config" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bluedroid" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bluedroid/api" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/app_trace" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/app_update" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bootloader_support" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bt" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/driver" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp32" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_adc_cal" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_http_client" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_https_ota" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp-mqtt" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp-tls" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/ethernet" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/fatfs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/freertos" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/heap" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/http_server" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/jsmn" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/log" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mdns" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mbedtls" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mbedtls_port" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/newlib" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/nvs_flash" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/openssl" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/spi_flash" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/sdmmc" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/smartconfig_ack" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/spiffs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/tcpip_adapter" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/tcp_transport" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/ulp" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/vfs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/wear_levelling" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/xtensa-debug-module" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/lwip" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/coap" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/console" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/expat" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/json" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/newlib" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/nghttp" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/soc" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/wpa_supplicant" -std=gnu++11 -fno-exceptions -Os -g3 -Wpointer-arith -fexceptions -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -w -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -fno-rtti -MMD -c -DF_CPU=240000000L -DARDUINO=10802 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ARDUINO-ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="doitESP32devkitV1"  -DESP32 -DCORE_DEBUG_LEVEL=0    -I"C:\Users\ylabr\git\arduino-esp32\cores\esp32" -I"D:\dev\workspace\esp32Test\libraries\ESP8266Spiram_ID5417\src" -I"D:\dev\workspace\esp32Test\libraries\ESP8266Audio-master\src" -I"D:\dev\workspace\esp32Test\MyLib\src" -I"C:\Users\ylabr\git\arduino-esp32\variants\doitESP32devkitV1" -I"C:\Users\ylabr\git\arduino-esp32\libraries\EEPROM" -I"C:\Users\ylabr\git\arduino-esp32\libraries\ESPmDNS\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\FS\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\HTTPClient\src" -I"C:\sloeber\arduinoPlugin\libraries\NtpClientLib\2.5.1\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SD\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SPI\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SPIFFS\src" -I"C:\sloeber\arduinoPlugin\libraries\ThingSpeak\1.3.3\src" -I"C:\sloeber\arduinoPlugin\libraries\Time\1.5.0" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WiFi\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\Wire\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WiFiClientSecure\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WebServer\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"  -DARDUINO_ARCH_ESP32 -DEEPROM_VERSION=1 -DLE_SPEAKER_VERSION=1.2 -DMCPOC_TEST=1 -DARDUINO_VARIANT=DoIT
	@echo 'Finished building: $<'
	@echo ' '

libraries\FS\src\vfs_api.cpp.o: C:\Users\ylabr\git\arduino-esp32\libraries\FS\src\vfs_api.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Users/ylabr/git/arduino-esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++" -DESP_PLATFORM -IMBEDTLS_CONFIG_FILE="mbedtls/esp_config.h" -DHAVE_CONFIG_H "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/config" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bluedroid" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bluedroid/api" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/app_trace" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/app_update" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bootloader_support" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/bt" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/driver" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp32" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_adc_cal" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_http_client" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp_https_ota" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp-mqtt" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/esp-tls" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/ethernet" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/fatfs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/freertos" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/heap" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/http_server" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/jsmn" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/log" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mdns" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mbedtls" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/mbedtls_port" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/newlib" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/nvs_flash" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/openssl" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/spi_flash" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/sdmmc" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/smartconfig_ack" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/spiffs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/tcpip_adapter" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/tcp_transport" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/ulp" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/vfs" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/wear_levelling" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/xtensa-debug-module" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/lwip" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/coap" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/console" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/expat" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/json" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/newlib" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/nghttp" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/soc" "-IC:/Users/ylabr/git/arduino-esp32/tools/sdk/include/wpa_supplicant" -std=gnu++11 -fno-exceptions -Os -g3 -Wpointer-arith -fexceptions -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -w -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -fno-rtti -MMD -c -DF_CPU=240000000L -DARDUINO=10802 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ARDUINO-ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="doitESP32devkitV1"  -DESP32 -DCORE_DEBUG_LEVEL=0    -I"C:\Users\ylabr\git\arduino-esp32\cores\esp32" -I"D:\dev\workspace\esp32Test\libraries\ESP8266Spiram_ID5417\src" -I"D:\dev\workspace\esp32Test\libraries\ESP8266Audio-master\src" -I"D:\dev\workspace\esp32Test\MyLib\src" -I"C:\Users\ylabr\git\arduino-esp32\variants\doitESP32devkitV1" -I"C:\Users\ylabr\git\arduino-esp32\libraries\EEPROM" -I"C:\Users\ylabr\git\arduino-esp32\libraries\ESPmDNS\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\FS\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\HTTPClient\src" -I"C:\sloeber\arduinoPlugin\libraries\NtpClientLib\2.5.1\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SD\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SPI\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\SPIFFS\src" -I"C:\sloeber\arduinoPlugin\libraries\ThingSpeak\1.3.3\src" -I"C:\sloeber\arduinoPlugin\libraries\Time\1.5.0" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WiFi\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\Wire\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WiFiClientSecure\src" -I"C:\Users\ylabr\git\arduino-esp32\libraries\WebServer\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"  -DARDUINO_ARCH_ESP32 -DEEPROM_VERSION=1 -DLE_SPEAKER_VERSION=1.2 -DMCPOC_TEST=1 -DARDUINO_VARIANT=DoIT
	@echo 'Finished building: $<'
	@echo ' '


