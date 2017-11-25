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
#define SCREEN_SIZE 3
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define FULLSCREEN false
#define VSYNC true
#define TITLE "OutRun Tribute"

// Road parameters ---------
#define FOV 120
#define CAMERA_HEIGHT 800	//200 or higher
#define ROAD_WIDTH 600
#define ROAD_LENGTH 30000	//Track length
#define DRAW_DISTANCE 5000
#define RUMBLE_LENGTH 40
#define ROAD_LANES 3
#define LANEMARKER_WIDTH 4

#endif //__GLOBALS_H__