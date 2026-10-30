/* Based on the upstream GHSA-vgjq-8cw5-ggw8 negative-stride reproducer. */
#include <png.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
   png_image image;
   png_bytep last_row;
   size_t row_bytes;
   size_t size;
   int ok;
   png_bytep input;

   memset(&image, 0, sizeof image);
   image.version = PNG_IMAGE_VERSION;
   image.width = 64;
   image.height = 64;
   image.format = PNG_FORMAT_RGBA;
   row_bytes = PNG_IMAGE_ROW_STRIDE(image);
   size = PNG_IMAGE_SIZE(image);
   input = (png_bytep)malloc(size);
   if (input == NULL)
   {
      return 2;
   }
   memset(input, 0x80, size);
   last_row = input + (image.height - 1) * row_bytes;
   /* PNG_SIMPLIFIED_WRITE_SUPPORTED allocates an opaque write control object. */
   ok = png_image_write_to_file(&image, "/dev/null", 0, last_row,
                                -(png_int_32)row_bytes, NULL);
   png_image_free(&image);
   free(input);
   return ok ? 0 : 5;
}
