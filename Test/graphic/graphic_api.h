#ifndef __AMAZON2_GRAPHIC_API_H__
#define __AMAZON2_GRAPHIC_API_H__


#include "amazon2_sdk.h"

void draw_rectfill(int x, int y, int w, int h, EGL_COLOR clr);
void clear_screen(void);
void flip(void);
void flipwait(void);
SURFACE* create_surface(int w, int h, int bpp);
void release_surface(SURFACE* surf);
void draw_surface(SURFACE* src_surf, int dx, int dy);
void draw_surfacerect(SURFACE* src_surf, int dx, int dy, EGL_RECT* pRect);
void draw_surface_scalerectrect(SURFACE* src_surf, EGL_RECT* pDestRect, EGL_RECT* pSrcRect);
void read_fpga_video_data(U16* buf);
void draw_fpga_video_data(U16* buf, int dx, int dy);
void draw_fpga_video_data_full(U16* buf);
void draw_img_from_buffer(U16* buf, int cdx, int cdy, int ctx, int cty, float zoom, int angle);
void direct_camera_display_on(void);
void direct_camera_display_off(void);
int direct_camera_display_stat(void);
SURFACE* loadbmp(char* fname);

int open_graphic(void); 
void close_graphic(void);
#endif //__AMAZON2_GRAPHIC_API_H__
