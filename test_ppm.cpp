
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
  photo_bw.image = new u_char[3 * photo_bw.width * photo_bw.height];
  memcpy(photo_bw.image, photo.image, 3 * photo_bw.width * photo_bw.height * sizeof(*photo_bw.image));

  // Desaturate image_bw
  ppm_desaturate(photo_bw.image, photo_bw.width, photo_bw.height);

  char file_bw_name[18] = "gargouille_bw.ppm";
  ppm_write_to_file(photo_bw.width, photo_bw.height, photo_bw.image,file_bw_name);

  // Free the desaturated image
  delete photo_bw.image;


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  
  structure photo_small;
  
  // Copy image into image_small
  photo_small.width  = photo.width;
  photo_small.height = photo.height;
  photo_small.image = new u_char[3 * photo_small.width * photo_small.height];
  memcpy(photo_small.image, photo.image, 3 * photo_small.width * photo_small.height * sizeof(*photo_small.image));

  // Shrink image_small size 2-fold
  ppm_shrink(&photo_small.image, &photo_small.width, &photo_small.height, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  char file_small_name[21]= "gargouille_small.ppm";
  ppm_write_to_file(photo_small.width, photo_small.height, photo_small.image, file_small_name);
      

  // Free the not yet freed images
  delete(photo.image);
  delete(photo_small.image);

  return 0;
}


