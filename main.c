#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shtc3.h"
#include <string.h>

#define SENSOR_ADDR_SHT 0x70
#define SENSOR_ADDR_ALS 0x29

#define FLAG_TIME 0
#define FLAG_SHT_SENSOR 1
#define FLAG_ALS_SENSOR 2

static const char *TAG = "example";
uint8_t FLAG_NOW=1;
char SHT_DATA[10];
uint8_t ALS_DATA[10];

float temperature =0, humidity =0; 
float light=0;

static void temp_hum_measure(void *pvParameter)
{
 init_sensor(I2C_MODE_MASTER, 25, 26, I2C_MASTER_FREQ_100KHZ);

    while (1)
    {
        //get_ID_sensor(SENSOR_ADDR);

        wakeup_sensor(SENSOR_ADDR_SHT);
       
        read_out(SENSOR_ADDR_SHT, T_FIRST_N, &temperature, &humidity);
        sleep_sensor(SENSOR_ADDR_SHT);
        ESP_LOGI(TAG, "Temperature: %0.2f, Humidade: %0.2f", temperature, humidity);
      sprintf(SHT_DATA,"%0.2f:%0.2f",temperature,humidity);
        //printf("DATA_SHT: %s\n",SHT_DATA);
      //  printf()
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    
}

void app_main(void)
{

    //time_t now;
    //struct tm timeinfo;
    //char strftime_buf[64];
    //Initialize NVS
    //esp_err_t ret = nvs_flash_init();
    //if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
     // ESP_ERROR_CHECK(nvs_flash_erase());
     // ret = nvs_flash_init();
    //}
    //ESP_ERROR_CHECK(ret);

   // ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
   // wifi_init_sta();
    //time_init(); 
 


    //xTaskCreate(&matrixUpdate, "updateMatrix", 2096, NULL, 5, NULL);
    xTaskCreate(&temp_hum_measure, "temp_hum", 2096, NULL, 5, NULL);
    //xTaskCreate(&light_measure, "light", 4096, NULL, 5, NULL);
    //xTaskCreate(&http_post_task, "send_data_to_thingspeak", 8192, NULL, 6, NULL);
    
    while (true) {
        
        FLAG_NOW=! FLAG_NOW;
        vTaskDelay(10000/ portTICK_PERIOD_MS); 
               
 
    }
}
