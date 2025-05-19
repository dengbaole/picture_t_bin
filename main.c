#include <stdio.h>
#include "tft_image.h"

uint32_t flash_address = 0x00000;
FILE* file = NULL;

void flash_write_bitmap_array_impl(const char* name, const void* array[], uint8_t count) {
	printf("FLASH_sBITMAP flash_%s[%d] = {\n", name, count);
	for (uint8_t i = 0; i < count; i++) {
		const sBITMAP* bmp = array[i];
		if (!bmp) continue;
		const uint32_t data_size = (uint32_t)(bmp->h) * bmp->w * 2;
		const uint32_t current_addr = flash_address;
		// W25Q128_WriteData(bmp->map, current_addr, data_size);
		fwrite(bmp->map, 1, data_size, file);
		flash_address += data_size;

		printf("%d, %d, 0x%x,\n", bmp->w, bmp->h, current_addr);
	}
	printf("};\n");
}


#define flash_write_bitmap_array(array) \
	flash_write_bitmap_array_impl(#array, array, sizeof(array)/sizeof(array[0]))

int main() {
	file = fopen("image_data.bin", "wb");
	if (!file) {
		perror("fopen error");
		return 1;
	}
	flash_write_bitmap_array(charge_array);
	flash_write_bitmap_array(timeout_array);
	flash_write_bitmap_array(lock_array);
	flash_write_bitmap_array(lowpower_array);
	flash_write_bitmap_array(nopod_array);
	flash_write_bitmap_array(power_on_array);
	flash_write_bitmap_array(smoke_array);
	flash_write_bitmap_array(letter_array);
	flash_write_bitmap_array(turbo_9_12_array);
	flash_write_bitmap_array(nos_9_12_array);
	fclose(file);
	printf("File write end!!\n");
	return 0;
}





