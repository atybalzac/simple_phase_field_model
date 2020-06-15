#include <iostream>
#include "simple_model.hpp"
#include "EasyBMP.h"
#include <linux/limits.h>


int main(int argc, char **argv){
    register int i, j;

    double endtime = 63;
    double time;

//Generate a blank image that can be updated and output as an image as the program runs
    BMP* img = new BMP();
    img -> SetSize(XSIZE,YSIZE);
//Declare a path length for naming the image files
    char imgpath[PATH_MAX];

//initialize Gphi 
    for(i = 0; i < XSIZE; i++){
        for (j = 0; j < YSIZE; j++){
            if (((XSIZE/2 -2) <= i && i <= (XSIZE/2 + 2)) && ((YSIZE/2 -2) <= j  && j <= (YSIZE/2 + 2))){
                Gphi[i][j] = 0.1;
            }
            else{
                Gphi[i][j] = 0.99;
            }
        }

    }

//Advance through time
    for (time = 0; time <= endtime; time += Gdt){
        for (i = 0; i < XSIZE; i++){
            for(j = 0; j < YSIZE; j++){
                double newphi = Gphi[i][j] - (GM * Gdt * (dfdphi(i,j) - (Geps2 * laplac(i,j))));
                //set pixel colors in grayscale
                img -> SetPixel(i, j, (RGBApixel){
                    .Blue = 176, //(ebmpBYTE)(255*Gphi[i][j]),
                    .Green = 138, //(ebmpBYTE)(255*Gphi[i][j]),
                    .Red = (ebmpBYTE)(255*Gphi[i][j]),
                    .Alpha = 0,
                });
                Gphi[i][j] = newphi;
            }
        }
       
        //write image to file iterating name based on timestep
    
        if (argc > 1){
            if (time < (10 - Gdt/2)){
                snprintf(imgpath, sizeof(imgpath), "%s_t=0%f.bmp", argv[1], time);
                img -> WriteToFile(imgpath);
            }
            else{
                snprintf(imgpath, sizeof(imgpath), "%s_t=%f.bmp", argv[1], time);
                img -> WriteToFile(imgpath);
            }
        }
    }




    delete img;
}