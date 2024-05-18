
const byte numChars = 20;
char receivedChars[numChars]; // an array to store the received data

String inString = "";  // inString.toInt()

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Read Characters   //////
//////////////////////////////////////////////////////////////////////////////////////////////
void recvWithEndMarker() 
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
 
  while (Serial.available() > 0 && newConsoleData == false) 
  {
    rc = Serial.read();
    
    if (rc != endMarker) 
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) 
      {
        ndx = numChars - 1;
      }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      inString = receivedChars;
      ndx = 0;
      newConsoleData = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Handle Inputs     //////
//////////////////////////////////////////////////////////////////////////////////////////////
void handleConsoleInput() // running in main-loop !!
{
  recvWithEndMarker();
  if (newConsoleData == true) 
  {
    Serial << "received String: '" << inString << "'" << endl;
    pinNumber = inString.toInt();
    newConsoleData = false;
  }
}

/*

Additional BoardManager URLs: http://arduino.esp8266.com/stable/package_esp8266com_index.json, https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json,https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/MHEtLive/arduino-boards-index/master/package_mhetlive_index.json

Board: "ESP32S3 Dev Module"
Upload Speed: "921600"
USB Mode: "Hardware CDC and JTAG"
USB CDC On Boot: "Disabled"
USB Firmware MSC On Boot: "Disabled"
USB DFU On Boot: "Disabled"
Upload Mode: "UART0 / Hardware CDC"
CPU Frequency: "240MHz (WiFi)"
Flash Mode: "QIO 80MHz"
Flash Size: "16MB (128Mb)"
Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
Core Debug Level: "None"
PSRAM: "QSPI PSRAM"
Arduino Runs On: "Core 1"
Events Run On: "Core 1"
Erase All Flash Before Sketch Upload: "Disabled"
JTAG Adapter: "Disabled"
Zigbee Mode: "Disabled"

---> 3.0.0-rc1
Linking everything together...
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\xtensa-esp32s3-elf-gcc\\esp-12.2.0_20230208/bin/xtensa-esp32s3-elf-g++" "@C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/flags/ld_flags" "@C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/flags/ld_scripts" "-Wl,--Map=C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.map" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/lib" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/ld" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/qio_qspi" -Wl,--wrap=esp_panic_handler -Wl,--start-group "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\sketch\\S3_Blink_Console.ino.cpp.o" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\core\\core.a" "@C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3/flags/ld_libs" -Wl,--end-group -Wl,-EL -o "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esptool_py\\4.6/esptool.exe" --chip esp32s3 elf2image --flash_mode dio --flash_freq 80m --flash_size 16MB --elf-sha256-offset 0xb0 -o "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.bin" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
esptool.py v4.6
Creating esp32s3 image...
Merged 2 ELF sections
Successfully created esp32s3 image.
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\3.0.0-rc1\\tools\\gen_esp32part.exe" -q "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/partitions.csv" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.partitions.bin"
cmd /c if exist "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\libraries\\Insights" "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\3.0.0-rc1\\tools\\gen_insights_package.exe" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569" S3_Blink_Console.ino "D:\\UserData\\iCloudDrive\\_Fritzing_Projects\\20230108_ESP32-S3\\S3_Blink_Console"
cmd /c if exist "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\libraries\\ESP_SR" if exist "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3\\esp_sr\\srmodels.bin" COPY /y "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esp32-arduino-libs\\idf-release_v5.1-3662303f312/esp32s3\\esp_sr\\srmodels.bin" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\srmodels.bin"
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\xtensa-esp32s3-elf-gcc\\esp-12.2.0_20230208/bin/xtensa-esp32s3-elf-size" -A "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
Sketch uses 292169 bytes (9%) of program storage space. Maximum is 3145728 bytes.
Global variables use 14728 bytes (4%) of dynamic memory, leaving 312952 bytes for local variables. Maximum is 327680 bytes.

---> 2.0.14
Linking everything together...
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\xtensa-esp32s3-elf-gcc\\esp-2021r2-patch5-8.4.0/bin/xtensa-esp32s3-elf-g++" "-Wl,--Map=C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.map" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14/tools/sdk/esp32s3/lib" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14/tools/sdk/esp32s3/ld" "-LC:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14/tools/sdk/esp32s3/qio_qspi" -T memory.ld -T sections.ld -T esp32s3.rom.ld -T esp32s3.rom.api.ld -T esp32s3.rom.libgcc.ld -T esp32s3.rom.newlib.ld -T esp32s3.rom.version.ld -T esp32s3.rom.newlib-time.ld -T esp32s3.peripherals.ld -mlongcalls -Wl,--cref -Wl,--gc-sections -fno-rtti -fno-lto -Wl,--wrap=esp_log_write -Wl,--wrap=esp_log_writev -Wl,--wrap=log_printf -u _Z5setupv -u _Z4loopv -u esp_app_desc -u pthread_include_pthread_impl -u pthread_include_pthread_cond_impl -u pthread_include_pthread_local_storage_impl -u pthread_include_pthread_rwlock_impl -u include_esp_phy_override -u ld_include_highint_hdl -u start_app -u start_app_other_cores -u __ubsan_include -Wl,--wrap=longjmp -u __assert_func -u vfs_include_syscalls_impl -Wl,--undefined=uxTopUsedPriority -u app_main -u newlib_include_heap_impl -u newlib_include_syscalls_impl -u newlib_include_pthread_impl -u newlib_include_assert_impl -u __cxa_guard_dummy -DESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=0 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=1 -Wl,--start-group "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\sketch\\S3_Blink_Console.ino.cpp.o" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_cache_219070\\core\\core_fe199e1fb77936a8e17d49ceda400d16.a" -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lasio -lbt -lcbor -lunity -lcmock -lcoap -lnghttp -lesp-tls -lesp_adc_cal -lesp_hid -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lesp_https_server -lesp_lcd -lprotobuf-c -lprotocomm -lmdns -lesp_local_ctrl -lsdmmc -lesp_serial_slave_link -lesp_websocket_client -lexpat -lwear_levelling -lfatfs -lfreemodbus -ljsmn -ljson -llibsodium -lmqtt -lopenssl -lperfmon -lspiffs -lusb -lulp -lwifi_provisioning -lrmaker_common -lesp_diagnostics -lrtc_store -lesp_insights -ljson_parser -ljson_generator -lesp_schedule -lespressif__esp_secure_cert_mgr -lesp_rainmaker -lgpio_button -lqrcode -lws2812_led -lesp32-camera -lesp_littlefs -lespressif__esp-dsp -lfb_gfx -lasio -lcmock -lunity -lcoap -lesp_lcd -lesp_websocket_client -lexpat -lfreemodbus -ljsmn -llibsodium -lperfmon -lusb -lesp_adc_cal -lesp_hid -lfatfs -lwear_levelling -lopenssl -lspiffs -lesp_insights -lcbor -lesp_diagnostics -lrtc_store -lesp_rainmaker -lesp_local_ctrl -lesp_https_server -lwifi_provisioning -lprotocomm -lbt -lbtdm_app -lprotobuf-c -lmdns -ljson -ljson_parser -ljson_generator -lesp_schedule -lespressif__esp_secure_cert_mgr -lqrcode -lrmaker_common -lmqtt -larduino_tinyusb -lcat_face_detect -lhuman_face_detect -lcolor_detect -lmfn -ldl -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lphy -lbtbb -lesp_phy -lphy -lbtbb -lesp_phy -lphy -lbtbb -lxt_hal -lc -lm -lnewlib -lstdc++ -lpthread -lgcc -lcxx -Wl,--end-group -Wl,-EL -o "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\esptool_py\\4.5.1/esptool.exe" --chip esp32s3 elf2image --flash_mode dio --flash_freq 80m --flash_size 16MB --elf-sha256-offset 0xb0 -o "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.bin" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
esptool.py v4.5.1
Creating esp32s3 image...
Merged 2 ELF sections
Successfully created esp32s3 image.
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14/tools/gen_esp32part.exe" -q "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/partitions.csv" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.partitions.bin"
cmd /c if exist "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569\\libraries\\Insights" "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14/tools/gen_insights_package.exe" "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569" S3_Blink_Console.ino "D:\\UserData\\iCloudDrive\\_Fritzing_Projects\\20230108_ESP32-S3\\S3_Blink_Console"
cmd /c IF 0==1 COPY /y "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\openocd-esp32\\v0.12.0-esp32-20230419\\share\\openocd\\scripts\\board\\esp32s3-builtin.cfg" "D:\\UserData\\iCloudDrive\\_Fritzing_Projects\\20230108_ESP32-S3\\S3_Blink_Console\\debug.cfg"
cmd /c IF 0==1 COPY /y "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14\\tools\\ide-debug\\esp32s3.json" "D:\\UserData\\iCloudDrive\\_Fritzing_Projects\\20230108_ESP32-S3\\S3_Blink_Console\\debug_custom.json"
cmd /c IF 0==1 COPY /y "C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.14\\tools\\ide-debug\\svd\\esp32s3.svd" "D:\\UserData\\iCloudDrive\\_Fritzing_Projects\\20230108_ESP32-S3\\S3_Blink_Console\\debug.svd"
"C:\\Users\\ABCDEF\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\xtensa-esp32s3-elf-gcc\\esp-2021r2-patch5-8.4.0/bin/xtensa-esp32s3-elf-size" -A "C:\\Users\\ABCDEF\\AppData\\Local\\Temp\\arduino_build_343569/S3_Blink_Console.ino.elf"
Sketch uses 271473 bytes (8%) of program storage space. Maximum is 3145728 bytes.
Global variables use 18992 bytes (5%) of dynamic memory, leaving 308688 bytes for local variables. Maximum is 327680 bytes.
C:\Users\ABCDEF\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.5.1/esptool.exe --chip esp32s3 --port COM3 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 16MB 0x0 C:\Users\ABCDEF\AppData\Local\Temp\arduino_build_343569/S3_Blink_Console.ino.bootloader.bin 0x8000 C:\Users\ABCDEF\AppData\Local\Temp\arduino_build_343569/S3_Blink_Console.ino.partitions.bin 0xe000 C:\Users\ABCDEF\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.14/tools/partitions/boot_app0.bin 0x10000 C:\Users\ABCDEF\AppData\Local\Temp\arduino_build_343569/S3_Blink_Console.ino.bin 
esptool.py v4.5.1

*/
