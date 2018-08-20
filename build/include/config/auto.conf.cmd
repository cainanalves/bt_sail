deps_config := \
	/home/cainan/esp/esp-idf/components/app_trace/Kconfig \
	/home/cainan/esp/esp-idf/components/aws_iot/Kconfig \
	/home/cainan/esp/esp-idf/components/bt/Kconfig \
	/home/cainan/esp/esp-idf/components/driver/Kconfig \
	/home/cainan/esp/esp-idf/components/esp32/Kconfig \
	/home/cainan/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/cainan/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/cainan/esp/esp-idf/components/ethernet/Kconfig \
	/home/cainan/esp/esp-idf/components/fatfs/Kconfig \
	/home/cainan/esp/esp-idf/components/freertos/Kconfig \
	/home/cainan/esp/esp-idf/components/heap/Kconfig \
	/home/cainan/esp/esp-idf/components/http_server/Kconfig \
	/home/cainan/esp/esp-idf/components/libsodium/Kconfig \
	/home/cainan/esp/esp-idf/components/log/Kconfig \
	/home/cainan/esp/esp-idf/components/lwip/Kconfig \
	/home/cainan/esp/esp-idf/components/mbedtls/Kconfig \
	/home/cainan/esp/esp-idf/components/mdns/Kconfig \
	/home/cainan/esp/esp-idf/components/openssl/Kconfig \
	/home/cainan/esp/esp-idf/components/pthread/Kconfig \
	/home/cainan/esp/esp-idf/components/spi_flash/Kconfig \
	/home/cainan/esp/esp-idf/components/spiffs/Kconfig \
	/home/cainan/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/cainan/esp/esp-idf/components/vfs/Kconfig \
	/home/cainan/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/cainan/esp/esp-idf/Kconfig.compiler \
	/home/cainan/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/cainan/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/cainan/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/cainan/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
