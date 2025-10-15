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
	flash_write_bitmap_array(boot_array);
	flash_write_bitmap_array(charge_bg_array);
	flash_write_bitmap_array(charge_num_array);
	flash_write_bitmap_array(err_p_array);
	flash_write_bitmap_array(main_dowm_array);
	flash_write_bitmap_array(main_up_array);
	flash_write_bitmap_array(mian_a_array);
    flash_write_bitmap_array(mian_b_array);
	flash_write_bitmap_array(mian_num_array);
	flash_write_bitmap_array(oil_array);
	flash_write_bitmap_array(power_off_array);
	flash_write_bitmap_array(smoke_array);
	fclose(file);
	printf("File write end!!\n");
	return 0;
}




