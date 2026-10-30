/* Regression for the CVE-2026-22695 follow-up to the CVE-2025-65018 backport. */
#include <png.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
   png_image image;
   png_bytep output;
   size_t row_bytes;
   size_t stride;
   size_t size;
   int ok;

   if (argc != 2)
      return 2;
   memset(&image, 0, sizeof image);
   image.version = PNG_IMAGE_VERSION;
   if (!png_image_begin_read_from_file(&image, argv[1]))
      return 3;
   image.format = PNG_FORMAT_RGBA;
   row_bytes = PNG_IMAGE_ROW_STRIDE(image);
   stride = row_bytes + 16;
   size = stride * image.height;
   output = (png_bytep)malloc(size);
   if (output == NULL)
   {
      png_image_free(&image);
      return 4;
   }
   memset(output, 0xA5, size);
   ok = png_image_finish_read(&image, NULL, output, (png_int_32)stride, NULL);
   png_image_free(&image);
   free(output);
   return ok ? 0 : 5;
}
