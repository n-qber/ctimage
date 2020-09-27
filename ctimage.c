#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int rgb_to_ansi(int rgb);

int main()
{

    int width, height, channels;
    unsigned char *img = stbi_load("potato.jpg", &width, &height, &channels, 0);

    for(int line=0; line<height;line += 2){
      for(int chr=0; chr<width; chr += 2){

        printf("\x1b[48;2");
        for(int chan=0; chan<channels;chan++){
          printf(";%d", img[line*width*channels + chr*channels + chan]);
        }
        printf("m");
        printf("  ");
        printf("\x1b[0m");
      }
      printf("\n");
    }

    stbi_image_free(img);
    return 0;
}
