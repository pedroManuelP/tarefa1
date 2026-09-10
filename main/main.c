#include <stdio.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_rom_sys.h>

#define BUTTON1_PIN 18
#define BUTTON2_PIN 19
#define LED1_PIN 21
#define LED2_PIN 22
#define LED3_PIN 23

static const char* TAG1 = "LED1";
static const char* TAG2 = "LED2";
static const char* TAG3 = "LED3";

void app_main(void)
{
    bool button1_level, button2_level;
    bool button1_pressed=false, button2_pressed=false;
    bool led1_level=false, led2_level=false, led3_level=false;
    int led3_timer=0;

    //  Reseta os pinos e os configura como saíd
    gpio_reset_pin(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED1_PIN, 0);

    gpio_reset_pin(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED2_PIN, 0);

    gpio_reset_pin(LED3_PIN);
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED3_PIN, 0);

    //  Reseta os pinos e os configura como entrada
    gpio_reset_pin(BUTTON1_PIN);
    gpio_set_direction(BUTTON1_PIN, GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON1_PIN);

    gpio_reset_pin(BUTTON2_PIN);
    gpio_set_direction(BUTTON2_PIN, GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON2_PIN);

    while(1){
        button1_level = gpio_get_level(BUTTON1_PIN);
        button2_level = gpio_get_level(BUTTON2_PIN);

        // LED1
        if(button1_level && !button1_pressed)
        {
            button1_pressed = true;
            led1_level = !led1_level;
            gpio_set_level(LED1_PIN, led1_level);
            
            if(!led1_level)
            {
                ESP_LOGI(TAG1, "Desligado");
            }else
            {
                ESP_LOGI(TAG1, "Ligado");
            }
        }
        else if(!button1_level)
        {
            button1_pressed = false;
        }

        //  LED2
        if(button2_level && !button2_pressed)
        {
            button2_pressed = true;
            led2_level = !led2_level;
            gpio_set_level(LED2_PIN, led2_level);

            if(!led2_level)
            {
                ESP_LOGI(TAG2, "Desligado");
            }else
            {
                ESP_LOGI(TAG2, "Ligado");
            }
        }
        else if(!button2_level)
        {
            button2_pressed = false;
        }

        //  LED3
        if(led3_timer == 1000000){
            led3_level = !led3_level;
            gpio_set_level(LED3_PIN, led3_level);
            if(!led3_level)
            {
                ESP_LOGI(TAG3, "Desligado"); 
            }
            else
            {
                ESP_LOGI(TAG3, "Ligado"); 
            }

            led3_timer=0;
        }
        led3_timer++;
    }
}

