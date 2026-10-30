/* Regression for CVE-2025-65018 using a valid RGB16 Adam7 image. */
#include <png.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
   png_image image;
   png_bytep output;
   size_t size;
   int ok;

   if (argc != 2)
      return 2;
   memset(&image, 0, sizeof image);
   image.version = PNG_IMAGE_VERSION;
   if (!png_image_begin_read_from_file(&image, argv[1]))
      return 3;
   image.format = PNG_FORMAT_RGBA;
   size = PNG_IMAGE_SIZE(image);
   output = (png_bytep)malloc(size);
   if (output == NULL)
   {
      png_image_free(&image);
      return 4;
   }
   memset(output, 0xA5, size);
   ok = png_image_finish_read(&image, NULL, output, 0, NULL);
   png_image_free(&image);
   free(output);
   return ok ? 0 : 5;
}
