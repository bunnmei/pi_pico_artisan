

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/rand.h"    
#include "class/cdc/cdc_device.h"

int indexOf(char *str, char *pattern) {
  int i, j;
  int len_str = strlen(str);
  int len_pattern = strlen(pattern);

  for (i = 0; i < len_str - len_pattern + 1; i++) {
    for (j = 0; j < len_pattern; j++) {
      if (str[i + j] != pattern[j]) {
        break;
      }
    }
    if (j == len_pattern) {
      return i;
    }
  }
  return -1;
}

char* substring(char * str, uint8_t start, uint8_t end){
    if (start < 0 || end < 0 || start > end || strlen(str) < end) {
        return NULL;
    }

    char *sub_str = (char *)malloc(end - start + 1);

    if (sub_str == NULL) {
        return NULL;
    }
    for (int i = start; i < end; i++) {
        sub_str[i - start] = str[i];
    }
    sub_str[end - start] = '\0';

    return sub_str;
}

int main() {
    stdio_init_all();

    unsigned short cmd_buff_index_ = 0;
    char cmd_buff[256] = {0};
    char tmp_input;
    
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    while (true) {
         // RxBuffにデータが存在する
        if(tud_cdc_available() > 0){
            while(tud_cdc_available() > 0){
                tmp_input = tud_cdc_read_char();
                cmd_buff[cmd_buff_index_] = tmp_input;
                cmd_buff_index_++;
            }

            // Artisan 
            if(indexOf(cmd_buff, "CHAN;") == 0){
                printf("#OK");
            } else if (indexOf(cmd_buff, "UNITS;") == 0) {
                
                char *sub_str = substring(cmd_buff, 7, 11);
                if(sub_str == "F"){
                    printf("#OK Farenheit\n");
                } else if(sub_str == "C") {
                    printf("#OK Celsius\n");
                }
                free(sub_str);

            } else if (indexOf(cmd_buff, "READ") == 0) {

                            //ET BT
                printf("0.00,%d,0.00,0.00,0.00\n", (uint8_t)get_rand_32());
            }

            if(indexOf(cmd_buff, "toglesy") == 0) {
                printf("%s", cmd_buff);
                char *sub_str = substring(cmd_buff, 2, 3);
                printf("Substr: %s\n", sub_str);
            }

            cmd_buff_index_ = 0;
            memset(cmd_buff, 0, sizeof(cmd_buff));
            
        }

        // sleep_ms(1000);
        sleep_ms(1);
    }
}
