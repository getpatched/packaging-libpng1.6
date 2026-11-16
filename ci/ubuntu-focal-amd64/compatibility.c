#include <assert.h>
#include <png.h>
#include <string.h>

int main(void) {
    const unsigned char pixels[] = {255, 0, 0, 255, 0, 128, 0, 64};
    unsigned char decoded[sizeof(pixels)] = {0};
    png_image encoder = {0};
    png_image decoder = {0};

    encoder.version = PNG_IMAGE_VERSION;
    encoder.width = 2;
    encoder.height = 1;
    encoder.format = PNG_FORMAT_RGBA;
    assert(png_image_write_to_file(&encoder, "sample.png", 0, pixels, 0, NULL));

    decoder.version = PNG_IMAGE_VERSION;
    assert(png_image_begin_read_from_file(&decoder, "sample.png"));
    assert(decoder.width == 2 && decoder.height == 1);
    decoder.format = PNG_FORMAT_RGBA;
    assert(png_image_finish_read(&decoder, NULL, decoded, 0, NULL));
    assert(memcmp(pixels, decoded, sizeof(pixels)) == 0);
    png_image_free(&decoder);
    return 0;
}
