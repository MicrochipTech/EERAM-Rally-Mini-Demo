#ifndef _IMAGES_H
#define _IMAGES_H

typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; // 1: 323 or Indexed,  2:RGB 565, 3:RGB 888, 4:RGBA 8888 
  //uint8_t  pixel_data[160 * 120 * 2 +1]; // Largest Image size allowed!
  uint8_t  pixel_data[]; // Largest Image size allowed!
}IMAGE;   // This is for Function Calls only, please use the define based on your actual sprite size

typedef struct 
{
  uint8_t 	 width;
  uint8_t 	 height;
  uint8_t    frames;
  uint8_t 	 bytes_per_pixel; // 2:RGB16, 3:RGB, 4:RGBA 
  uint8_t	 pixel_data[16 * 26 * 2 + 1];
}IMAGE16X26;

typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[16 * 16 * 2 + 1];  // 513 Bytes
}IMAGE16;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[32 * 32 * 2 + 1]; // 2049 bytes
}IMAGE32;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[5 * 10 * 2 + 1]; // 2049 bytes
}IMAGE5x10;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[10 * 10 * 2 + 1]; // 2049 bytes
}IMAGE10x10;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[20 * 20 * 2 + 1]; // 2049 bytes
}IMAGE20x20;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[16 * 19 * 2 + 1];  // 513 Bytes
}IMAGE16x19;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[50 * 60 * 2 + 1]; // 6001 bytes
}IMAGE50x60;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  uint8_t  pixel_data[70 * 65 * 2 + 1]; // 9101 bytes
}IMAGE70x65;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; // 1: 323 or Indexed,  2:RGB 565, 3:RGB 888, 4:RGBA 8888  
  uint8_t  pixel_data[100 * 20 * 2 + 1]; // 4001 bytes
}IMAGE100x20;
typedef struct
{
  uint8_t  width;
  uint8_t  height;
  uint8_t  frames;
  uint8_t  bytes_per_pixel; // 1: 323 or Indexed,  2:RGB 565, 3:RGB 888, 4:RGBA 8888  
  uint8_t  pixel_data[120 * 160 * 2 + 1]; //38401 bytes
}IMAGE120x160;

extern const IMAGE16X26 car16;
extern const IMAGE16X26 blu16;
extern const IMAGE16X26 yel16;
extern const IMAGE16X26 org16;
extern const IMAGE16X26 vio16;
extern const IMAGE16X26 grn16;
extern const IMAGE16 bullet;
extern const IMAGE70x65 edgar;
extern const IMAGE32 enemy;
extern const IMAGE70x65 mchp_meatball;
extern const IMAGE100x20 microchip;
extern const IMAGE100x20 nintendo;
extern const IMAGE32 player;
#endif
