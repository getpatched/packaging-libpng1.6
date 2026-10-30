#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *read_rgb(const char *path, size_t *size)
{
   png_image image;
   unsigned char *pixels;
   memset(&image, 0, sizeof image);
   image.version = PNG_IMAGE_VERSION;
   if (!png_image_begin_read_from_file(&image, path))
      return NULL;
   image.format = PNG_FORMAT_RGB;
   *size = PNG_IMAGE_SIZE(image);
   pixels = (unsigned char *)malloc(*size);
   if (pixels == NULL || !png_image_finish_read(&image, NULL, pixels,
       (png_int_32)PNG_IMAGE_ROW_STRIDE(image), NULL))
   {
      free(pixels);
      png_image_free(&image);
      return NULL;
   }
   png_image_free(&image);
   return pixels;
}

int main(int argc, char **argv)
{
   size_t interlaced_size, flat_size, i;
   unsigned char *interlaced, *flat;
   size_t different = 0;
   if (argc != 3) return 2;
   interlaced = read_rgb(argv[1], &interlaced_size);
   flat = read_rgb(argv[2], &flat_size);
   if (interlaced == NULL || flat == NULL || interlaced_size != flat_size)
      return 2;
   for (i = 0; i < interlaced_size; ++i)
      if (interlaced[i] != flat[i]) ++different;
   printf("differing channels: %lu / %lu\n",
      (unsigned long)different, (unsigned long)interlaced_size);
   free(interlaced);
   free(flat);
   return different == 0 ? 0 : 1;
}
