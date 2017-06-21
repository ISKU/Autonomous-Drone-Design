#ifndef __AMAZON2_GRAPHIC_H__
#define __AMAZON2_GRAPHIC_H__

#define HW_2D_ENGINE


#if defined(BOOL)
#else 
typedef int BOOL;
#endif

typedef signed char		S8;
typedef signed short	S16;
typedef signed int		S32;

typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;
typedef unsigned long long	U64;

typedef volatile unsigned char	vU8;
typedef volatile unsigned short	vU16;
typedef volatile unsigned int	vU32;
typedef volatile unsigned long long	vU64;


#ifdef TRUE	
#undef TRUE 
#endif
#define TRUE 1

#ifdef FALSE 
#undef FALSE
#endif
#define FALSE 0

#ifdef false
#undef false
#endif
#define false 0



typedef unsigned int EGL_COLOR;

#define ALPHA_BLEND(sR, sG, sB, A, dR, dG, dB)	\
    do {						\
        dR = (((sR-dR)*(A))>>8)+dR;		\
        dG = (((sG-dG)*(A))>>8)+dG;		\
        dB = (((sB-dB)*(A))>>8)+dB;		\
				    } while(0)



typedef struct _tagPOINT
{
	int  x;
	int y;
} EGL_POINT;


typedef struct _tag_RECT
{
	int x;
	int y;
	int w;
	int h;
} EGL_RECT;


typedef struct _tagARGB
{
	U8 b;
	U8 g;
	U8 r;
	U8 a;
} sARGB;
typedef struct _tagABGR
{
	U8 r;
	U8 g;
	U8 b;
	U8 a;
} sABGR;

typedef struct _tagrRGB
{
	U8 b;
	U8 g;
	U8 r;
	U8 resv; //reserved
} srRGB;

typedef struct _tagRGB565
{
	int b : 5;
	int g : 6;
	int r : 5;
} RGB565;

typedef union
{
	U32 data32;
	sARGB argb;
} ARGB;

typedef union
{
	U32 data32;
	sABGR abgr;
} ABGR;

typedef union
{
	U32 data32;
	srRGB rrgb;
} rRGB;

typedef enum
{
	PIX_FMT_RGB565 = 0,
	PIX_FMT_A1RGB555,
	PIX_FMT_PALETTE,
	PIX_FMT_RGB888,
	PIX_FMT_ARGB,//8888
	PIX_FMT_ABGR,//8888
	PIX_FMT_A1RGB,//1888
	PIX_FMT_A4RGB,//4888
	PIX_FMT_A000,//special 8bit mode, only alpha channel, palette 0  is color
	PIX_FMT_A1PALETTE,//A1 + 8 or4 BPP
} PIXFMT;

#ifdef HW_2D_ENGINE
typedef struct _tag_tmemmanager
{
	int offset;
	int size;

	struct _tag_tmemmanager	*prev;
	struct _tag_tmemmanager	*next;
} TMemManager;

#endif //HW_2D_ENGINE

typedef struct
{
	int bpp; //
	int nColors;
	int colorkey;
	EGL_COLOR* colors;

#ifdef HW_2D_ENGINE
	TMemManager tm;
	U8 LUT4Bank;///< only for 4bpp Texel mode
#endif //HW_2D_ENGINE
} PALETTE;

typedef struct _tagcliprect
{
	int x;
	int y;
	int endx;
	int endy;
} CLIP_RECT;
typedef struct
{
	int	w; ///< width of surface
	int	h; ///< height of surface
	int bpp; ///< Bits Per Pixel
	void*	pixels; ///< pointer to th actual pixel data
	int pitch; ///< Length of a surface scanline in U8s
	PIXFMT pixtype;
	PALETTE* pal;
	CLIP_RECT clip;
	void* reserv; //for extend
#ifdef HW_2D_ENGINE
	TMemManager tm;
	int drawmode;//for H/W Graphic engine
	int flipmode; //Vertical or horizontal
	sARGB ShadeColor;
	sARGB transColor;
	sARGB alphaConstColor;//for alphablend
	int sblendmode;
	int dblendmode;
	int TileXSize;///< real width of surface = 1<<(TileXSize+3)
	int TileYSize;///< real height of surface = 1<<(TileYSize+3)
#endif //HW_2D_ENGINE
} SURFACE;



typedef struct _tag_DrawRectFillArg
{
	EGL_RECT rect;
	EGL_COLOR clr;
} DrawRectFillArg;


typedef struct _tag_CreateSurfaceArg
{
	int w;
	int h;
	int bpp;//8,16,24,32
} CreateSurfaceArg;


typedef struct _tag_DrawSurfaceArg
{
	SURFACE* surf;
	int dx;//screen x
	int dy;// screen y;
} DrawSurfaceArg;

typedef struct _tag_DrawSurfaceRectArg
{
	SURFACE* surf;
	int dx;//screen x
	int dy;// screen y;
	EGL_RECT rect;//surface's
} DrawSurfaceRectArg;

typedef struct _tag_DrawSurfaceScaleRectArg
{
	SURFACE* surf;
	EGL_RECT dest_rect;//screen's
	EGL_RECT surf_rect;//surface's
} DrawSurfaceScaleRectArg;

typedef struct _tag_DrawFPGADataArg
{
	U16* buf;
	int dx;//screen x
	int dy;// screen y;
} DrawFPGADataArg;

typedef struct _tag_DrawRaw_value 
{
	int InitDX;
	int InitDY;
	int EndX;
	int EndY;
	int InitSX;
	int InitSY;
	int dxSx;
	int dxSy;
	int dySx;
	int dySy;
	int imgbuf_en;
	U16 *imgbuf;
} DrawRaw_value;


#define MAKE_COLORREF(r,g,b)	(0xff<<24 | (EGL_COLOR)((((r << 8) | g) << 8) | b))//ARGB
#define MAKE_RGB888(r,g,b)	((EGL_COLOR)((((r << 8) | g) << 8) | b))//RGB
#define MAKE_RGB565(r,g,b)	((U16)((((U16)r&0xf8)<<8)|(((U16)g&0xfc)<<3)|(((U16)b&0xf8)>>3)))  ///< make RGB565 from r,g,b
#define MAKE_COLORARGB(a,r,g,b)	((EGL_COLOR)((((((a<<8) | r) << 8) | g) << 8) | b))//ARGB
#define EXTRACT_ARGB(c,a,r,g,b)	do{a=(U8)(c>>24);r=(U8)(c>>16);g=(U8)(c>>8);b=(U8)(c>>0);}while(0);
#define EXTRACT_RGB(c,r,g,b)	do{r=(U8)(c>>16);g=(U8)(c>>8);b=(U8)(c);}while(0);
#define EXTRACT_RGB565(c,r,g,b)	do{r=(U8)(c>>11);g=(U8)((c>>5)&0x3f);b=(U8)(c & 0x1f);}while(0);
#define MAKE_RGB565FROM888(c)		((U16)((((U16)(c>>16)&0xf8)<<8)|(((U16)(c>>8)&0xfc)<<3)|(((U16)c&0xf8)>>3)))
#define GetRedValue(C)	((C>>16)&0xff)
#define GetGreenValue(C)	((C>>8)&0xff)
#define GetBlueValue(C)	(C&0xff)

/*#######################################################*/
typedef enum 
{
	AMAZON2_IOCTL_CLEAR_SCREEN=0,
	AMAZON2_IOCTL_FLIP,
	AMAZON2_IOCTL_FLIPWAIT,

	AMAZON2_IOCTL_CREATE_SURFACE,
	AMAZON2_IOCTL_RELEASE_SURFACE,
	AMAZON2_IOCTL_DRAW_SURFACE,
	AMAZON2_IOCTL_DRAW_SURFACE_RECT,
	AMAZON2_IOCTL_DRAW_SURFACE_SCALE_RECT,

	AMAZON2_IOCTL_DRAW_RECT_FILL,

	AMAZON2_IOCTL_GET_DIRECT_CAMERA_SURFACE, //surface's pixel data is updated by H/W 
	AMAZON2_IOCTL_READ_FPGA_VIDEO_DATA,
	AMAZON2_IOCTL_DRAW_FPGA_VIDEO_DATA,
	AMAZON2_IOCTL_DRAW_FPGA_VIDEO_DATA_FULL,
	AMAZON2_IOCTL_DRAW_IMG_FROM_BUFFER,

	AMAZON2_IOCTL_CAM_DISP_ON,
	AMAZON2_IOCTL_CAM_DISP_OFF,
	AMAZON2_IOCTL_CAM_DISP_STAT,

}AMAZON2_IOCTL;


/*#######################################################*/


#endif // __AMAZON2_GRAPHIC_H__
