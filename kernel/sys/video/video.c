#include <sys/video/internal.h>
#include <sys/video/init.h>
#include <sys/video/video.h>


void init_video(stiletto_video_t stiletto_video) {
    video.pFrame_buffer_base = stiletto_video.pFrame_buffer_base;
    video.frame_buffer_sz    = stiletto_video.frame_buffer_sz;

    video.horiz              = stiletto_video.horiz;
    video.vert               = stiletto_video.vert;
    
    video.ppsl               = stiletto_video.ppsl;
}


/*  Operating routines  */

VOID putpixel_routine(UINT32 x, UINT32 y, UINT32 color) {
    video.pFrame_buffer_base[y * video.ppsl + x] = color;
}

VOID clr_scr(VOID) {
    // draw vertically for the vsync
    for(UINT32 __y__ = 0; __y__ < video.vert; ++__y__) {
        for(UINT32 __x__ = 0; __x__ < video.horiz; ++__x__) {
            putpixel_routine(__x__, __y__, 0x080C0E);
        }
    }
}

VOID fill_scr(UINT32 hex_rgb_color) {
    // draw vertically for the vsync
    for(UINT32 __y__ = 0; __y__ < video.vert; ++__y__) {
        for(UINT32 __x__ = 0; __x__ < video.horiz; ++__x__) {
            putpixel_routine(__x__, __y__, hex_rgb_color);
        }
    }
}
