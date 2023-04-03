#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

void show_help_message(void);

void show_image(char imagename[255], char separator[15]);

int main(int args, char *argv[])
{
    char imagepath[255];
    char separator[15] = "  ";
    
    if (args == 1 || !strcmp(argv[args - 1], "--help")){
      show_help_message();
    }

    for(int argi = 1; argi < args - 1; argi++){
      
      if (!strcmp(argv[argi], "--separator")){
        strcpy(separator, argv[argi + 1]);
      }
    }

    show_image(argv[args - 1], separator);
    
    return 0;
}

void show_image(char imagepath[255], char separator[15]){

  int width, height, channels;
  unsigned char *img = stbi_load(imagepath, &width, &height, &channels, 0);

  int new_width, new_height;

  initscr();
  getmaxyx(stdscr, new_height, new_width);
  endwin();

  unsigned char *resized_image = (unsigned char*)malloc(new_width * new_height * channels);

  stbir_resize_uint8(img, width, height, 0, resized_image, new_width, new_height, 0, channels);

  for(int line=0; line<new_height;line += 2){
    for(int chr=0; chr<new_width; chr += 2){

      printf("\x1b[48;2");
      for(int chan=0; chan<channels;chan++){
        printf(";%d", resized_image[line*new_width*channels + chr*channels + chan]);
      }
      printf("m");
      printf(separator);
      printf("\x1b[0m");
    }
    printf("\n");
  }

  stbi_image_free(img);
  free(resized_image);
}

void show_help_message(void){
  printf("Usage: ctimage [imagepath]\n\n");
  printf("Options:\n\t--separator specifies the string that will be outputed, default is \"  \"");
  printf("\n");
  exit(0);
}
