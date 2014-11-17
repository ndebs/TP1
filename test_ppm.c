
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"




//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //Call the structure
  structure photo;


  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  photo.image = NULL;
  //photo.width;
  //photo.height;
 
  ppm_read_from_file(&photo.width, &photo.height, &photo.image);
  
  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  
  structure photo_bw;
  // Copy image into image_bw
  photo_bw.width  = photo.width;
  photo_bw.height = photo.height;
  photo_bw.image = (u_char*) malloc(3 * photo.width * photo.height * sizeof(*photo_bw.image));
  memcpy(photo_bw.image, photo.image, 3 * photo_bw.width * photo_bw.height * sizeof(*photo_bw.image));

  // Desaturate image_bw
  ppm_desaturate(photo_bw.image, photo_bw.width, photo_bw.height);

  char file_bw_name[18] = "gargouille_bw.ppm";
  ppm_write_to_file(photo_bw.width, photo_bw.height, photo_bw.image,file_bw_name);

  // Free the desaturated image
  free(photo_bw.image);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  
  structure photo_small;
  
  // Copy image into image_small
  photo_small.width  = photo.width;
  photo_small.height = photo.height;
  photo_small.image = (u_char*) malloc(3 * photo_small.width * photo_small.height * sizeof(*photo_small.image));
  memcpy(photo_small.image, photo.image, 3 * photo_small.width * photo_small.height * sizeof(*photo_small.image));
  printf("Hello \n");
  // Shrink image_small size 2-fold
  ppm_shrink(&photo_small.image, &photo_small.width, &photo_small.height, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  char file_small_name[21]= "gargouille_small.ppm";
  ppm_write_to_file(photo_small.width, photo_small.height, photo_small.image, file_small_name);
      

  // Free the not yet freed images
  free(photo.image);
  free(photo_small.image);

  return 0;
}


