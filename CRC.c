#include "settings.h"
#include "CRC.h"


uint8_t crc8_cdma2000(uint8_t *data, uint8_t len){
    uint8_t crc = 0xFF;

    for (uint8_t i = 0; i < len; i++)
        crc = crc8_table[crc ^ data[i]];

    return crc;
}
