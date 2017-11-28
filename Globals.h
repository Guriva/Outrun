#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "MemLeaks.h"
#include "SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FULLSCREEN false
#define VSYNC true
#define TITLE "OutRun Tribute"
#define TICK_FPS 60

// Road parameters ---------
#define FOV 100
#define CAMERA_HEIGHT 1000	//200 or higher
#define ROAD_WIDTH 2000
#define ROAD_LENGTH 1500	//Track length
#define DRAW_DISTANCE 300
#define SEGMENT_LENGTH 200
#define RUMBLE_LENGTH 3
#define ROAD_LANES 3
#define LANEMARKER_WIDTH 4
#define RUMBLE_WIDTH 1.08
#define SCREEN_Y_OFFSET 100

#endif //__GLOBALS_H__