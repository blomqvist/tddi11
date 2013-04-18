#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "rims.h"

#define IMGPATH "given_files/img/"

volatile byte READY = 0;
volatile byte B = 0;
volatile byte A = 0;
volatile bool g_exit_request = false;

int g_timer_period;
int g_timer_elapsed;
bool g_timer_running;

void TimerSet(int msec)
{
   g_timer_period = msec;
}

void TimerOn()
{
   g_timer_running = true;
}

/* Increase compatibility to RIMS and avoid extensive CPU usage :-) */
bool true_test(int loop, const char* test)
{
  if ( g_exit_request )
    return false; // break any loop !
  
  if ( strstr(test, "Clk") != 0 )
    return SDL_Delay(BASE_TICK), loop;
  else if ( strstr(test, "READY") != 0 )
    return SDL_Delay(BASE_TICK), loop;
  else if ( strstr(test, "period") != 0 )
    return SDL_Delay(BASE_TICK), loop;
  else if ( strcmp(test, "1") == 0 || strcmp(test, "true") == 0 )
    return !g_exit_request;
  else
    return loop;
}

void ShowImage(SDL_Surface* image, SDL_Surface *screen, int x, int y)
{
    SDL_Rect dest;
    
    /* Blit onto the screen surface.
       The surfaces should not be locked at this point.
     */
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;
    SDL_BlitSurface(image, NULL, screen, &dest);

    /* Update the changed portion of the screen */
//    SDL_UpdateRects(screen, 1, &dest);
}

const byte segments_on[16] = {
  0x77, /* 01110111 => 0 */
  0x44, /* 01000100 => 1 */
  0x3E, /* 00111110 => 2 */
  0x6E, /* 01101110 => 3 */
  0x4D, /* 01001101 => 4 */
  0x6B, /* 01101011 => 5 */
  0x7B, /* 01111011 => 6 */
  0x46, /* 01000110 => 7 */
  0x7F, /* 01111111 => 8 */
  0x6F, /* 01101111 => 9 */  
  0x5F, /* 01011111 => A */
  0x7F, /* 01111111 => B */
  0x33, /* 00110011 => C */
  0x77, /* 01110111 => D */
  0x3B, /* 00111011 => E */
  0x1B  /* 00011011 => F */
};

void update_segment(byte display[], SDL_Surface* img[], SDL_Surface* screen)
{
  int i, j;
  for ( i = 0; i < 4; ++i)
  {
    ShowImage(img[ 7 ], screen, 464 + 40*i, 85);
    for ( j = 0; j < 10; ++j)
    {
      if ( display[ i ] & (1 << j) )
        ShowImage(img[ j ], screen, 464 + 40*i, 85);
    }
  }
  ShowImage(img[ 8 ], screen, 464 + 40*1, 85);
}

int display(void* data)
{
   SDL_Surface* screen = data;
   char *segment[] = {
     IMGPATH "7segment_xcf-Segment_0.png",
     IMGPATH "7segment_xcf-Segment_1.png",
     IMGPATH "7segment_xcf-Segment_2.png",
     IMGPATH "7segment_xcf-Segment_3.png",
     IMGPATH "7segment_xcf-Segment_4.png",
     IMGPATH "7segment_xcf-Segment_5.png",
     IMGPATH "7segment_xcf-Segment_6.png",
     IMGPATH "7segment_xcf-Background.png",
     IMGPATH "7segment_xcf-Colon.png",
     IMGPATH "7segment_xcf-Segment_7.png",
     NULL
   };
   char *microwave[] = {
     IMGPATH "microwave_xcf-Background.png",
     IMGPATH "microwave_xcf-Frame.png",
     IMGPATH "microwave_xcf-Beep.png",     
     IMGPATH "microwave_xcf-Tray.png",
     IMGPATH "microwave_xcf-Microwaves.png",
     IMGPATH "microwave_xcf-Buttons.png",
     IMGPATH "microwave_xcf-Door.png",     
     NULL
   };
   SDL_Surface *image_s[10];
   SDL_Surface *image_m[8];
   int i;
   SDL_Rect dest_all = {0, 0, 640, 400};
   SDL_Rect dest_seg = {464, 85, 160, 60};
   
   for ( i = 0; microwave[ i ]; ++i )
   {
      image_m[i] = IMG_Load( microwave[i] );
      
      if ( image_m[i] == NULL )
      {
	 fprintf(stderr, "Couldn't load %s: %s\n",
                 microwave[i], SDL_GetError());
         g_exit_request = true;
	 return 1;
      }
   }
   
   for ( i = 0; segment[ i ]; ++i )
   {
      image_s[i] = IMG_Load( segment[i] );
      
      if ( image_s[i] == NULL )
      {
	 fprintf(stderr, "Couldn't load %s: %s\n",
                 segment[i], SDL_GetError());
         g_exit_request = true;
	 return 1;
      }
   }
   
   while ( ! g_exit_request )
   {
     static byte previous = 0xFF;
     static byte display[4] = {0,0,0,0};
     static bool prev_door = 0;
     int pos, dig;
     bool beep_on, tray_on, wave_on;
     bool door_open = (A & 0x08) != 0;
     byte current;

     current = B & 0xFF;
     
     dig = current & 0x0F;
     pos = (current >> 4) & 0x03;
     display[pos] = segments_on[ dig ];
     
     if ( ((current ^ previous) & 0xE0) || prev_door != door_open)
     {
       beep_on = (current & 0x80) != 0;
       tray_on = (current & 0x40) != 0;
       wave_on = (current & 0x40) != 0;

       ShowImage(image_m[ 0 ], screen, 0, 0);
       ShowImage(image_m[ 1 ], screen, 0, 0);
       if ( beep_on )
         ShowImage(image_m[ 2 ], screen, 0, 0);
       if ( tray_on )
         ShowImage(image_m[ 3 ], screen, 0, 0);
       if ( wave_on )
         ShowImage(image_m[ 4 ], screen, 0, 0);

       ShowImage(image_m[ 5 ], screen, 0, 0);
       
       if ( ! door_open )
         ShowImage(image_m[ 6 ], screen, 0, 0);
       
       update_segment(display, image_s, screen);
       SDL_UpdateRects(screen, 1, &dest_all);
     }
     else
     {
       update_segment(display, image_s, screen);
       SDL_UpdateRects(screen, 1, &dest_seg);
     }
     previous = current;
     prev_door = door_open;
     READY = true;
     
     SDL_Delay(BASE_TICK);
   }
   return 0;
}

int timer(void* data UNUSED)
{
   while ( ! g_exit_request )
   {
      SDL_Delay(BASE_TICK);
      g_timer_elapsed += BASE_TICK;
      
      if ( g_timer_running && g_timer_elapsed >= g_timer_period )
      {
	 TimerISR();
	 g_timer_elapsed = 0;
      }
   }
   return 0;
}

bool inside_rect(const SDL_Rect *r, int x, int y)
{
  return ( x > r->x && x < (r->x + r->w) &&
           y > r->y && y < (r->y + r->h) );
}

/* rims.h substitute main to app_main, #undef avoids that here */
#undef main
int main(int argc UNUSED, char *argv[] UNUSED)
{
   if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
   {
      fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
      exit(1);
   }
   atexit( SDL_Quit );

   SDL_Surface *screen;
   screen = SDL_SetVideoMode(
     640, /* width */
     400, /* height */
     32, /* bits per pixel */
     SDL_SWSURFACE);
   
   if ( screen == NULL )
   {
      fprintf(stderr, "Unable to set 64*8x64 video: %s\n", SDL_GetError());
      exit(1);
   }
//   SDL_SetWindowTitle(screen, "Right Click to exit");
   
   SDL_Thread *display_thread;
   display_thread = SDL_CreateThread(display, screen);
   if ( display_thread == NULL )
   {
      fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
      g_exit_request = true;
   }

   SDL_Thread *time_thread;
   time_thread = SDL_CreateThread(timer, NULL);
   if ( time_thread == NULL )
   {
      fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
      g_exit_request = true;
   }
   
   SDL_Thread *app_thread;
   app_thread = SDL_CreateThread(app_main, NULL);
   if ( app_thread == NULL )
   {
      fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
      g_exit_request = true;
   }
      
   SDL_Rect button_plus;
   button_plus.x = 550;
   button_plus.y = 270;
   button_plus.w = 40;
   button_plus.h = 40;
   SDL_Rect button_minus;
   button_minus.x = 500;
   button_minus.y = 270;
   button_minus.w = 40;
   button_minus.h = 40;
   SDL_Rect button_start;
   button_start.x = 500;
   button_start.y = 315;
   button_start.w = 90;
   button_start.h = 40;
   SDL_Rect door_handle;
   door_handle.x = 20;
   door_handle.y = 20;
   door_handle.w = 420;
   door_handle.h = 360;
   
   while ( ! g_exit_request )
   {
      SDL_Event event;
      static byte a = 0;
      
      if ( SDL_WaitEvent(&event) )
      {
	 switch (event.type) {
           /*
            case SDL_MOUSEMOTION:
	       debug("Mouse moved by %d,%d to (%d,%d)\n", 
		      event.motion.xrel, event.motion.yrel,
		      event.motion.x, event.motion.y);
	       break;
           */
            case SDL_MOUSEBUTTONDOWN:
	       debug("Mouse button %d pressed at (%d,%d)\n",
		      event.button.button, event.button.x, event.button.y);
               
               if ( inside_rect( &button_plus,
                                 event.button.x,
                                 event.button.y) )
                 a |= 1;
               
               if ( inside_rect( &button_minus,
                                 event.button.x,
                                 event.button.y) )
                 a |= 2;
               
               if ( inside_rect( &button_start,
                                 event.button.x,
                                 event.button.y) )
                 a |= 4;

               if ( inside_rect( &door_handle,
                                 event.button.x,
                                 event.button.y) )
                 a ^= 8;

               if (event.button.button != 1)
                 g_exit_request = true;
               
	       break;
            case SDL_MOUSEBUTTONUP:
	       debug("Mouse button %d released at (%d,%d)\n",
		      event.button.button, event.button.x, event.button.y);
               
               if ( inside_rect( &button_plus,
                                 event.button.x,
                                 event.button.y) )
                 a &= ~1;
               
               if ( inside_rect( &button_minus,
                                 event.button.x,
                                 event.button.y) )
                 a &= ~2;
               
               if ( inside_rect( &button_start,
                                 event.button.x,
                                 event.button.y) )
                 a &= ~4;
               
	       break;
            case SDL_QUIT:
	       g_exit_request = true;
	 }
      }
      if ( A != a)
      {
        fprintf(stdout, "A is 0x%02x\n", a);
      }
      A = a & 0x0F;
   }

   int status = 0;
   SDL_WaitThread(display_thread, &status);
   SDL_WaitThread(time_thread, &status);
   TimerISR(); /* release anyone waiting */
   SDL_WaitThread(app_thread, &status);
   
   return status;
}
