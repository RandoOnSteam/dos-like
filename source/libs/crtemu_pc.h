#if 0
#include "crtemu_pcopenel.h"
#else
#ifndef crtemu_pc_h
#define crtemu_pc_h

#ifndef CRTEMU_PC_U32
#define CRTEMU_PC_U32 unsigned int
#endif
#ifndef CRTEMU_PC_U64
#define CRTEMU_PC_U64 unsigned long long
#endif

typedef struct crtemu_pc_t crtemu_pc_t;

typedef struct crtemu_pc_config_t {
	float curvature;
	float scanlines;
	float shadow_mask;
	float separation;
	float ghosting;
	float noise;
	float flicker;
	float vignette;
	float distortion;
	float aspect_lock;
	float hpos;
	float vpos;
	float hsize;
	float vsize;
	float contrast;
	float brightness;
	float saturation;
	float blur;
	float degauss;
} crtemu_pc_config_t;

crtemu_pc_t* crtemu_pc_create(void* memctx);
void crtemu_pc_destroy(crtemu_pc_t* crtemu_pc);
void crtemu_pc_config(crtemu_pc_t* crtemu_pc,crtemu_pc_config_t const* config);
void crtemu_pc_frame(crtemu_pc_t* crtemu_pc,CRTEMU_PC_U32* frame_abgr,int frame_width,int frame_height);
void crtemu_pc_present(crtemu_pc_t* crtemu_pc,CRTEMU_PC_U64 time_us,CRTEMU_PC_U32 const* pixels_xbgr,int width,int height,
	CRTEMU_PC_U32 mod_xbgr,CRTEMU_PC_U32 border_xbgr);
void crtemu_pc_coordinates_window_to_bitmap(crtemu_pc_t* crtemu_pc,int width,int height,int* x,int* y);
void crtemu_pc_coordinates_bitmap_to_window(crtemu_pc_t* crtemu_pc,int width,int height,int* x,int* y);

#endif /* crtemu_pc_h */

#ifdef CRTEMU_PC_IMPLEMENTATION
#undef CRTEMU_PC_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRTEMU_PC_MALLOC
#if defined(__cplusplus)
#define CRTEMU_PC_MALLOC(ctx, size) (::malloc(size))
#define CRTEMU_PC_FREE(ctx, ptr) (::free(ptr))
#else
#define CRTEMU_PC_MALLOC(ctx, size) (malloc(size))
#define CRTEMU_PC_FREE(ctx, ptr) (free(ptr))
#endif
#endif

#ifndef _WIN32
#define CRTEMU_PC_SDL
#endif

#ifdef __wasm__
#define CRTEMU_PC_WEBGL
#endif

#ifndef CRTEMU_PC_SDL

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
	__declspec(dllimport) struct HINSTANCE__* __stdcall LoadLibraryA(char const* lpLibFileName);
	__declspec(dllimport) int __stdcall FreeLibrary(struct HINSTANCE__* hModule);
#if defined(_WIN64)
	typedef __int64 (__stdcall* CRTEMU_PC_PROC)(void);
	__declspec(dllimport) CRTEMU_PC_PROC __stdcall GetProcAddress(struct HINSTANCE__* hModule,char const* lpLibFileName);
#else
	typedef __int32 (__stdcall* CRTEMU_PC_PROC)(void);
	__declspec(dllimport) CRTEMU_PC_PROC __stdcall GetProcAddress(struct HINSTANCE__* hModule,char const* lpLibFileName);
#endif
#if defined(_WIN64)
	__declspec(dllimport) void* __stdcall CreateThread(SECURITY_ATTRIBUTES* attributes,unsigned __int64 stack_size,unsigned long (__stdcall* start)(void*),void* param,unsigned long flags,unsigned long* id);
#else
	__declspec(dllimport) void* __stdcall CreateThread(struct _SECURITY_ATTRIBUTES* attributes,unsigned long stack_size,unsigned long (__stdcall* start)(void*),void* param,unsigned long flags,unsigned long* id);
#endif
	__declspec(dllimport) void* __stdcall CreateEventA(SECURITY_ATTRIBUTES* attributes,int manual_reset,int initial_state,char const* name);
	__declspec(dllimport) int __stdcall SetEvent(void* handle);
	__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* handle,unsigned long milliseconds);
	__declspec(dllimport) unsigned long __stdcall WaitForMultipleObjects(unsigned long count,void* const* handles,int wait_all,unsigned long milliseconds);
	__declspec(dllimport) int __stdcall CloseHandle(void* handle);
	__declspec(dllimport) int __stdcall SwitchToThread(void);
	__declspec(dllimport) unsigned long __stdcall GetActiveProcessorCount(unsigned short group_number);

#ifdef __cplusplus
}
#endif

#include <intrin.h>
#ifndef CRTEMU_PC_MAX_THREADS
#define CRTEMU_PC_MAX_THREADS 8
#endif

#define CRTEMU_PC_GLCALLTYPE __stdcall
typedef unsigned int CRTEMU_PC_GLuint;
typedef int CRTEMU_PC_GLsizei;
typedef unsigned int CRTEMU_PC_GLenum;
typedef int CRTEMU_PC_GLint;
typedef float CRTEMU_PC_GLfloat;
typedef unsigned int CRTEMU_PC_GLbitfield;

#define CRTEMU_PC_GL_TEXTURE_2D 0x0de1
#define CRTEMU_PC_GL_TEXTURE_MIN_FILTER 0x2801
#define CRTEMU_PC_GL_TEXTURE_MAG_FILTER 0x2800
#define CRTEMU_PC_GL_TEXTURE_WRAP_S 0x2802
#define CRTEMU_PC_GL_TEXTURE_WRAP_T 0x2803
#define CRTEMU_PC_GL_CLAMP 0x2900
#define CRTEMU_PC_GL_LINEAR 0x2601
#define CRTEMU_PC_GL_NEAREST 0x2600
#define CRTEMU_PC_GL_RGBA 0x1908
#define CRTEMU_PC_GL_LUMINANCE 0x1909
#define CRTEMU_PC_GL_UNSIGNED_BYTE 0x1401
#define CRTEMU_PC_GL_COLOR_BUFFER_BIT 0x00004000
#define CRTEMU_PC_GL_VIEWPORT 0x0ba2
#define CRTEMU_PC_GL_BLEND 0x0be2
#define CRTEMU_PC_GL_ZERO 0
#define CRTEMU_PC_GL_ONE 1
#define CRTEMU_PC_GL_SRC_ALPHA 0x0302
#define CRTEMU_PC_GL_ONE_MINUS_SRC_ALPHA 0x0303
#define CRTEMU_PC_GL_DST_COLOR 0x0306
#define CRTEMU_PC_GL_QUADS 0x0007
#define CRTEMU_PC_GL_PROJECTION 0x1701
#define CRTEMU_PC_GL_MODELVIEW 0x1700
#define CRTEMU_PC_GL_TEXTURE_ENV 0x2300
#define CRTEMU_PC_GL_TEXTURE_ENV_MODE 0x2200
#define CRTEMU_PC_GL_MODULATE 0x2100

#else

#ifndef CRTEMU_PC_WEBGL
#include <GL/glew.h>
#if !defined(APP_WS)
#include "SDL_opengl.h"
#endif
#else
#include <wajic_gl.h>
#endif

#define CRTEMU_PC_GLCALLTYPE GLAPIENTRY
typedef GLuint CRTEMU_PC_GLuint;
typedef GLsizei CRTEMU_PC_GLsizei;
typedef GLenum CRTEMU_PC_GLenum;
typedef GLint CRTEMU_PC_GLint;
typedef GLfloat CRTEMU_PC_GLfloat;
typedef GLbitfield CRTEMU_PC_GLbitfield;

#define CRTEMU_PC_GL_TEXTURE_2D GL_TEXTURE_2D
#define CRTEMU_PC_GL_TEXTURE_MIN_FILTER GL_TEXTURE_MIN_FILTER
#define CRTEMU_PC_GL_TEXTURE_MAG_FILTER GL_TEXTURE_MAG_FILTER
#define CRTEMU_PC_GL_TEXTURE_WRAP_S GL_TEXTURE_WRAP_S
#define CRTEMU_PC_GL_TEXTURE_WRAP_T GL_TEXTURE_WRAP_T
#ifndef CRTEMU_PC_WEBGL
#define CRTEMU_PC_GL_CLAMP GL_CLAMP
#else
#define CRTEMU_PC_GL_CLAMP GL_CLAMP_TO_EDGE
#endif
#define CRTEMU_PC_GL_LINEAR GL_LINEAR
#define CRTEMU_PC_GL_NEAREST GL_NEAREST
#define CRTEMU_PC_GL_RGBA GL_RGBA
#define CRTEMU_PC_GL_LUMINANCE GL_LUMINANCE
#define CRTEMU_PC_GL_UNSIGNED_BYTE GL_UNSIGNED_BYTE
#define CRTEMU_PC_GL_COLOR_BUFFER_BIT GL_COLOR_BUFFER_BIT
#define CRTEMU_PC_GL_VIEWPORT GL_VIEWPORT
#define CRTEMU_PC_GL_BLEND GL_BLEND
#define CRTEMU_PC_GL_ZERO GL_ZERO
#define CRTEMU_PC_GL_ONE GL_ONE
#define CRTEMU_PC_GL_SRC_ALPHA GL_SRC_ALPHA
#define CRTEMU_PC_GL_ONE_MINUS_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
#define CRTEMU_PC_GL_DST_COLOR GL_DST_COLOR
#define CRTEMU_PC_GL_QUADS GL_QUADS
#define CRTEMU_PC_GL_PROJECTION GL_PROJECTION
#define CRTEMU_PC_GL_MODELVIEW GL_MODELVIEW
#define CRTEMU_PC_GL_TEXTURE_ENV GL_TEXTURE_ENV
#define CRTEMU_PC_GL_TEXTURE_ENV_MODE GL_TEXTURE_ENV_MODE
#define CRTEMU_PC_GL_MODULATE GL_MODULATE

#endif

typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glGenTexturesProc)(CRTEMU_PC_GLsizei n,CRTEMU_PC_GLuint* textures);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glBindTextureProc)(CRTEMU_PC_GLenum target,CRTEMU_PC_GLuint texture);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glTexImage2DProc)(CRTEMU_PC_GLenum target,CRTEMU_PC_GLint level,CRTEMU_PC_GLint internalformat,CRTEMU_PC_GLsizei width,CRTEMU_PC_GLsizei height,CRTEMU_PC_GLint border,CRTEMU_PC_GLenum format,CRTEMU_PC_GLenum type,void const* pixels);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glTexParameteriProc)(CRTEMU_PC_GLenum target,CRTEMU_PC_GLenum pname,CRTEMU_PC_GLint param);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glClearColorProc)(CRTEMU_PC_GLfloat red,CRTEMU_PC_GLfloat green,CRTEMU_PC_GLfloat blue,CRTEMU_PC_GLfloat alpha);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glClearProc)(CRTEMU_PC_GLbitfield mask);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glEnableProc)(CRTEMU_PC_GLenum cap);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glDisableProc)(CRTEMU_PC_GLenum cap);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glBlendFuncProc)(CRTEMU_PC_GLenum sfactor,CRTEMU_PC_GLenum dfactor);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glBeginProc)(CRTEMU_PC_GLenum mode);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glEndProc)(void);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glTexCoord2fProc)(CRTEMU_PC_GLfloat s,CRTEMU_PC_GLfloat t);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glVertex2fProc)(CRTEMU_PC_GLfloat x,CRTEMU_PC_GLfloat y);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glViewportProc)(CRTEMU_PC_GLint x,CRTEMU_PC_GLint y,CRTEMU_PC_GLsizei width,CRTEMU_PC_GLsizei height);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glGetIntegervProc)(CRTEMU_PC_GLenum pname,CRTEMU_PC_GLint* data);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glDeleteTexturesProc)(CRTEMU_PC_GLsizei n,CRTEMU_PC_GLuint const* textures);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glMatrixModeProc)(CRTEMU_PC_GLenum mode);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glLoadIdentityProc)(void);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glColor3fProc)(CRTEMU_PC_GLfloat red,CRTEMU_PC_GLfloat green,CRTEMU_PC_GLfloat blue);
typedef void (CRTEMU_PC_GLCALLTYPE* crtemu_pc_glTexEnviProc)(CRTEMU_PC_GLenum target,CRTEMU_PC_GLenum pname,CRTEMU_PC_GLint param);

typedef struct crtemu_pc_rect_t
{
	int x;
	int y;
	int w;
	int h;
} crtemu_pc_rect_t;

typedef struct crtemu_pc_shade_params_t
{
	int width;
	int height;
	int frame_index;
	float t;
	float mod_r, mod_g, mod_b;
	float curve_mix;
	float sep_scale;
	float ghs;
	float noise_amt;
	float flicker_amt;
	float vig_scale;
	float wobble_amp;
	float frame_x_off;
	float v_min;
	float v_max;
	int apply_cbs;
	float cbs_contrast;
	float cbs_brightness;
	float cbs_saturation;
	int rebuild_geometry;
} crtemu_pc_shade_params_t;

typedef struct crtemu_pc_barrier_t
{
	volatile long count;
	volatile long generation;
	long total;
} crtemu_pc_barrier_t;

typedef struct crtemu_pc_work_t
{
	crtemu_pc_t* crtemu_pc;
	CRTEMU_PC_U32 const* pixels_xbgr;
	crtemu_pc_shade_params_t const* params;
	crtemu_pc_barrier_t* barrier;
	int index;
	int count;
} crtemu_pc_work_t;

#ifndef CRTEMU_PC_SDL
typedef struct crtemu_pc_pool_slot_t
{
	crtemu_pc_t* crtemu_pc;
	int index;
} crtemu_pc_pool_slot_t;
#endif

struct crtemu_pc_t
{
	void* memctx;
	crtemu_pc_config_t config;
	CRTEMU_PC_GLuint backbuffer;
	CRTEMU_PC_GLuint diffbuffer;
	CRTEMU_PC_GLuint frame_texture;
	CRTEMU_PC_GLuint overlay_texture;
	int frame_width;
	int frame_height;
	float use_frame;
	unsigned char* source_pixels;
	unsigned char* history_pixels;
	unsigned char* display_pixels;
	unsigned char* blur_pixels;
	unsigned char* temp_pixels;
	unsigned char* processed_pixels;
	unsigned char* diff_pixels;
	int buffer_width;
	int buffer_height;
	float* geometry;
	int geometry_valid;
	float geometry_curve_mix;
	float geometry_vig_scale;
	float geometry_frame_x_off;
	int overlay_width;
	int overlay_height;
	float overlay_scanlines;
	float overlay_shadow_mask;
	int last_present_width;
	int last_present_height;
	float time;
	int thread_count;
	float gamma_lut[1024];
	crtemu_pc_glGenTexturesProc GenTextures;
	crtemu_pc_glBindTextureProc BindTexture;
	crtemu_pc_glTexImage2DProc TexImage2D;
	crtemu_pc_glTexParameteriProc TexParameteri;
	crtemu_pc_glClearColorProc ClearColor;
	crtemu_pc_glClearProc Clear;
	crtemu_pc_glEnableProc Enable;
	crtemu_pc_glDisableProc Disable;
	crtemu_pc_glBlendFuncProc BlendFunc;
	crtemu_pc_glBeginProc Begin;
	crtemu_pc_glEndProc End;
	crtemu_pc_glTexCoord2fProc TexCoord2f;
	crtemu_pc_glVertex2fProc Vertex2f;
	crtemu_pc_glViewportProc Viewport;
	crtemu_pc_glGetIntegervProc GetIntegerv;
	crtemu_pc_glDeleteTexturesProc DeleteTextures;
	crtemu_pc_glMatrixModeProc MatrixMode;
	crtemu_pc_glLoadIdentityProc LoadIdentity;
	crtemu_pc_glColor3fProc Color3f;
	crtemu_pc_glTexEnviProc TexEnvi;
#ifndef CRTEMU_PC_SDL
	struct HINSTANCE__* gl_dll;
	CRTEMU_PC_PROC(CRTEMU_PC_GLCALLTYPE* wglGetProcAddress)(char const*);
	void* pool_threads[CRTEMU_PC_MAX_THREADS - 1];
	void* pool_work_events[CRTEMU_PC_MAX_THREADS - 1];
	void* pool_done_events[CRTEMU_PC_MAX_THREADS - 1];
	crtemu_pc_pool_slot_t pool_slots[CRTEMU_PC_MAX_THREADS - 1];
	crtemu_pc_work_t pool_work[CRTEMU_PC_MAX_THREADS];
	volatile int pool_shutdown;
	int pool_size;
#endif
};

static float crtemu_pc_internal_clampf(float v, float minv, float maxv)
{
	return v < minv ? minv : (v > maxv ? maxv : v);
}

static int crtemu_pc_internal_clampi(int v, int minv, int maxv)
{
	return v < minv ? minv : (v > maxv ? maxv : v);
}

static unsigned char crtemu_pc_internal_tobyte(float v)
{
	int iv = (int)(crtemu_pc_internal_clampf(v, 0.0f, 1.0f) * 255.0f + 0.5f);
	return (unsigned char)crtemu_pc_internal_clampi(iv, 0, 255);
}

static void crtemu_pc_internal_xbgr_to_rgb(CRTEMU_PC_U32 xbgr, float* r, float* g, float* b)
{
	*r = ((xbgr) & 0xff) / 255.0f;
	*g = ((xbgr >> 8) & 0xff) / 255.0f;
	*b = ((xbgr >> 16) & 0xff) / 255.0f;
}

static float crtemu_pc_internal_rand(int x, int y, int frame)
{
	unsigned int n = (unsigned int)x * 1973u + (unsigned int)y * 9277u + (unsigned int)frame * 26699u + 0x68bc21ebu;
	n = (n ^ (n >> 13)) * 1274126177u;
	n ^= n >> 16;
	return (n & 0xffffu) / 65535.0f;
}

static float crtemu_pc_internal_filmic(float x)
{
	x = x - 0.004f;
	if (x < 0.0f)
	{
		x = 0.0f;
	}
	return (x * (6.2f * x + 0.5f)) / (x * (6.2f * x + 1.7f) + 0.06f);
}

static float crtemu_pc_internal_decode(crtemu_pc_t* crtemu_pc, float x)
{
	return crtemu_pc->gamma_lut[(int)(x * 1023.0f + 0.5f)];
}

static void crtemu_pc_internal_display_rect(crtemu_pc_t* crtemu_pc, int const viewport[4], int width, int height, crtemu_pc_rect_t* rect)
{
	int window_width = viewport[2] > 1 ? viewport[2] : 1;
	int window_height = viewport[3] > 1 ? viewport[3] : 1;
	float source_aspect = height > 0 ? (float)width / (float)height : 4.0f / 3.0f;
	float target_aspect = crtemu_pc->config.aspect_lock < -0.5f ? source_aspect : 4.25f / 3.0f;
	float hsize_scale = crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.hsize * 0.15f, 0.25f, 2.0f);
	float vsize_scale = crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.vsize * 0.15f, 0.25f, 2.0f);
	int target_width = window_width;
	int target_height = (int)((float)window_width / target_aspect + 0.5f);

	if (target_height > window_height)
	{
		target_height = window_height;
		target_width = (int)((float)window_height * target_aspect + 0.5f);
	}

	target_width = (int)((float)target_width * hsize_scale);
	target_height = (int)((float)target_height * vsize_scale);
	target_width = crtemu_pc_internal_clampi(target_width, 1, window_width * 2);
	target_height = crtemu_pc_internal_clampi(target_height, 1, window_height * 2);

	rect->w = target_width;
	rect->h = target_height;
	rect->x = viewport[0] + (window_width - target_width) / 2 + (int)(crtemu_pc->config.hpos * (float)window_width * 0.10f);
	rect->y = viewport[1] + (window_height - target_height) / 2 + (int)(crtemu_pc->config.vpos * (float)window_height * 0.10f);
}

static int crtemu_pc_internal_source_uv(crtemu_pc_t* crtemu_pc, float u, float v, float* su, float* sv, float* curved_u, float* curved_v)
{
	float curve_mix = crtemu_pc_internal_clampf(0.2f + crtemu_pc->config.curvature * 0.2f, 0.0f, 1.0f);
	float gy = 1.0f - v;
	float cx = (u - 0.5f) * 2.0f * 1.1f;
	float cy = (gy - 0.5f) * 2.0f * 1.1f;
	float ax, ay, cu, cgy, scu, scv_gl;

	ay = (cy >= 0.0f ? cy : -cy) / 5.0f;
	cx *= 1.0f + ay * ay;
	ax = (cx >= 0.0f ? cx : -cx) / 4.0f;
	cy *= 1.0f + ax * ax;
	cx = (cx * 0.5f + 0.5f) * 0.92f + 0.04f;
	cy = (cy * 0.5f + 0.5f) * 0.92f + 0.04f;

	cu = u * (1.0f - curve_mix) + cx * curve_mix;
	cgy = gy * (1.0f - curve_mix) + cy * curve_mix;
	*curved_u = cu;
	*curved_v = 1.0f - cgy;

	scu = cu * 0.96f + 0.02f + 0.003f;
	scv_gl = cgy * 0.96f + 0.02f - 0.001f;

	*su = (scu * 1.035f + (crtemu_pc->use_frame != 0.0f ? -0.009375f : -0.018f)) * 1.2f - 0.1f;
	*sv = 1.076f - scv_gl * 1.152f;

	return cu >= 0.0f && cu <= 1.0f && cgy >= 0.0f && cgy <= 1.0f;
}

static float crtemu_pc_internal_sample_channel(unsigned char const* pixels, int width, int height, float u, float v, int channel)
{
	int x0, y0, x1, y1;
	float x, y, tx, ty;
	float c00, c10, c01, c11, c0, c1;

	if (!pixels)
	{
		return 0.0f;
	}
	x = u * (float)width - 0.5f;
	y = v * (float)height - 0.5f;
	if (x <= -1.0f || y <= -1.0f || x >= (float)width || y >= (float)height)
	{
		return 0.0f;
	}
	x0 = (int)(x + 1.0f) - 1;
	y0 = (int)(y + 1.0f) - 1;
	x1 = x0 + 1;
	y1 = y0 + 1;
	tx = x - (float)x0;
	ty = y - (float)y0;

	if (x0 >= 0 && y0 >= 0 && x1 < width && y1 < height)
	{
		unsigned char const* row0 = pixels + (y0 * width + x0) * 4 + channel;
		unsigned char const* row1 = row0 + width * 4;
		c0 = row0[0] + (row0[4] - row0[0]) * tx;
		c1 = row1[0] + (row1[4] - row1[0]) * tx;
		return (c0 + (c1 - c0) * ty) / 255.0f;
	}

	c00 = (x0 >= 0 && y0 >= 0) ? pixels[(y0 * width + x0) * 4 + channel] / 255.0f : 0.0f;
	c10 = (x1 < width && y0 >= 0) ? pixels[(y0 * width + x1) * 4 + channel] / 255.0f : 0.0f;
	c01 = (x0 >= 0 && y1 < height) ? pixels[(y1 * width + x0) * 4 + channel] / 255.0f : 0.0f;
	c11 = (x1 < width && y1 < height) ? pixels[(y1 * width + x1) * 4 + channel] / 255.0f : 0.0f;
	c0 = c00 + (c10 - c00) * tx;
	c1 = c01 + (c11 - c01) * tx;
	return c0 + (c1 - c0) * ty;
}

static int crtemu_pc_internal_sample_rgb(unsigned char const* pixels, int width, int height, float u, float v, float* out_r, float* out_g, float* out_b)
{
	static const unsigned char zero[4] = { 0,0,0,0 };
	int x0, y0, x1, y1, c;
	float x, y, tx, ty;
	unsigned char const* p00;
	unsigned char const* p10;
	unsigned char const* p01;
	unsigned char const* p11;
	int maxbyte = 0;
	float out[3];

	*out_r = *out_g = *out_b = 0.0f;
	if (!pixels)
	{
		return 0;
	}
	x = u * (float)width - 0.5f;
	y = v * (float)height - 0.5f;
	if (x <= -1.0f || y <= -1.0f || x >= (float)width || y >= (float)height)
	{
		return 0;
	}
	x0 = (int)(x + 1.0f) - 1;
	y0 = (int)(y + 1.0f) - 1;
	x1 = x0 + 1;
	y1 = y0 + 1;
	tx = x - (float)x0;
	ty = y - (float)y0;

	if (x0 >= 0 && y0 >= 0 && x1 < width && y1 < height)
	{
		p00 = pixels + (y0 * width + x0) * 4;
		p10 = p00 + 4;
		p01 = p00 + width * 4;
		p11 = p01 + 4;
	}
	else
	{
		p00 = (x0 >= 0 && y0 >= 0) ? pixels + (y0 * width + x0) * 4 : zero;
		p10 = (x1 < width && y0 >= 0) ? pixels + (y0 * width + x1) * 4 : zero;
		p01 = (x0 >= 0 && y1 < height) ? pixels + (y1 * width + x0) * 4 : zero;
		p11 = (x1 < width && y1 < height) ? pixels + (y1 * width + x1) * 4 : zero;
	}

	for (c = 0; c < 3; ++c)
	{
		float c0 = p00[c] + (p10[c] - p00[c]) * tx;
		float c1 = p01[c] + (p11[c] - p01[c]) * tx;
		if (p00[c] > maxbyte) maxbyte = p00[c];
		if (p10[c] > maxbyte) maxbyte = p10[c];
		if (p01[c] > maxbyte) maxbyte = p01[c];
		if (p11[c] > maxbyte) maxbyte = p11[c];
		out[c] = (c0 + (c1 - c0) * ty) / 255.0f;
	}
	*out_r = out[0];
	*out_g = out[1];
	*out_b = out[2];
	return maxbyte;
}

static void crtemu_pc_internal_blur_pass(unsigned char* dst, unsigned char const* src, int width, int height, int horizontal, int y_index, int y_stride)
{
	static const int weights[5] = { 14879,12754,7971,3543,1063 };
	int x, y, o, c, v;

	if (horizontal)
	{
		int x0 = width > 9 ? 4 : width;
		int x1 = width > 9 ? width - 4 : width;
		for (y = y_index; y < height; y += y_stride)
		{
			unsigned char const* row = src + (size_t)y * (size_t)width * 4u;
			unsigned char* drow = dst + (size_t)y * (size_t)width * 4u;
			for (x = 0; x < width; x = (x + 1 == x0 ? x1 : x + 1))
			{
				for (c = 0; c < 3; ++c)
				{
					int acc = 0;
					for (o = -4; o <= 4; ++o)
					{
						acc += row[crtemu_pc_internal_clampi(x + o, 0, width - 1) * 4 + c] * weights[o < 0 ? -o : o];
					}
					v = acc >> 16;
					drow[x * 4 + c] = (unsigned char)(v > 255 ? 255 : v);
				}
				drow[x * 4 + 3] = 255;
			}
			for (x = x0; x < x1; ++x)
			{
				unsigned char const* p = row + x * 4;
				for (c = 0; c < 3; ++c)
				{
					int acc = p[c] * 14879 + (p[c - 4] + p[c + 4]) * 12754 + (p[c - 8] + p[c + 8]) * 7971
						+ (p[c - 12] + p[c + 12]) * 3543 + (p[c - 16] + p[c + 16]) * 1063;
					v = acc >> 16;
					drow[x * 4 + c] = (unsigned char)(v > 255 ? 255 : v);
				}
				drow[x * 4 + 3] = 255;
			}
		}
	}
	else
	{
		for (y = y_index; y < height; y += y_stride)
		{
			unsigned char const* rows[9];
			unsigned char* drow = dst + (size_t)y * (size_t)width * 4u;
			for (o = -4; o <= 4; ++o)
			{
				rows[o + 4] = src + (size_t)crtemu_pc_internal_clampi(y + o, 0, height - 1) * (size_t)width * 4u;
			}
			for (x = 0; x < width; ++x)
			{
				int i4 = x * 4;
				for (c = 0; c < 3; ++c)
				{
					int acc = rows[4][i4 + c] * 14879 + (rows[3][i4 + c] + rows[5][i4 + c]) * 12754
						+ (rows[2][i4 + c] + rows[6][i4 + c]) * 7971 + (rows[1][i4 + c] + rows[7][i4 + c]) * 3543
						+ (rows[0][i4 + c] + rows[8][i4 + c]) * 1063;
					v = acc >> 16;
					drow[i4 + c] = (unsigned char)(v > 255 ? 255 : v);
				}
				drow[i4 + 3] = 255;
			}
		}
	}
}

static int crtemu_pc_internal_ensure_buffers(crtemu_pc_t* crtemu_pc, int width, int height)
{
	size_t size;
	unsigned char** buffers[7];
	int i;

	buffers[0] = &crtemu_pc->source_pixels;
	buffers[1] = &crtemu_pc->history_pixels;
	buffers[2] = &crtemu_pc->display_pixels;
	buffers[3] = &crtemu_pc->blur_pixels;
	buffers[4] = &crtemu_pc->temp_pixels;
	buffers[5] = &crtemu_pc->processed_pixels;
	buffers[6] = &crtemu_pc->diff_pixels;

	if (crtemu_pc->buffer_width == width && crtemu_pc->buffer_height == height && crtemu_pc->source_pixels)
	{
		return 1;
	}

	for (i = 0; i < 7; ++i)
	{
		if (*buffers[i])
		{
			CRTEMU_PC_FREE(crtemu_pc->memctx, *buffers[i]);
			*buffers[i] = NULL;
		}
	}

	size = (size_t)width * (size_t)height * 4u;
	for (i = 0; i < 7; ++i)
	{
		*buffers[i] = (unsigned char*)CRTEMU_PC_MALLOC(crtemu_pc->memctx, size);
		if (!*buffers[i])
		{
			while (--i >= 0)
			{
				CRTEMU_PC_FREE(crtemu_pc->memctx, *buffers[i]);
				*buffers[i] = NULL;
			}
			crtemu_pc->buffer_width = 0;
			crtemu_pc->buffer_height = 0;
			return 0;
		}
	}

	if (crtemu_pc->geometry)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->geometry);
	}
	crtemu_pc->geometry = (float*)CRTEMU_PC_MALLOC(crtemu_pc->memctx, (size_t)width * (size_t)height * 4u * sizeof(float));
	crtemu_pc->geometry_valid = 0;
	if (!crtemu_pc->geometry)
	{
		for (i = 0; i < 7; ++i)
		{
			CRTEMU_PC_FREE(crtemu_pc->memctx, *buffers[i]);
			*buffers[i] = NULL;
		}
		crtemu_pc->buffer_width = 0;
		crtemu_pc->buffer_height = 0;
		return 0;
	}

	memset(crtemu_pc->history_pixels, 0, size);
	crtemu_pc->buffer_width = width;
	crtemu_pc->buffer_height = height;
	return 1;
}

static void crtemu_pc_internal_convert_slice(crtemu_pc_t* crtemu_pc, CRTEMU_PC_U32 const* pixels_xbgr, int width, int height, int y_index, int y_stride)
{
	int y;
	size_t i, end;
	for (y = y_index; y < height; y += y_stride)
	{
		i = (size_t)y * (size_t)width;
		end = i + (size_t)width;
		for (; i < end; ++i)
		{
			CRTEMU_PC_U32 c = pixels_xbgr[i];
			crtemu_pc->source_pixels[i * 4 + 0] = (unsigned char)((c) & 0xff);
			crtemu_pc->source_pixels[i * 4 + 1] = (unsigned char)((c >> 8) & 0xff);
			crtemu_pc->source_pixels[i * 4 + 2] = (unsigned char)((c >> 16) & 0xff);
			crtemu_pc->source_pixels[i * 4 + 3] = 255;
		}
	}
}

static void crtemu_pc_internal_accum_slice(crtemu_pc_t* crtemu_pc, int width, int height, int y_index, int y_stride)
{
	int y;
	size_t i, end;
	for (y = y_index; y < height; y += y_stride)
	{
		i = (size_t)y * (size_t)width * 4u;
		end = i + (size_t)width * 4u;
		for (; i < end; ++i)
		{
			int decayed = (crtemu_pc->display_pixels[i] * 245) >> 8;
			int src = crtemu_pc->source_pixels[i];
			int hist = src > decayed ? src : decayed;
			int trail = (hist * 61) >> 8;
			crtemu_pc->history_pixels[i] = (unsigned char)hist;
			crtemu_pc->display_pixels[i] = (unsigned char)(src > trail ? src : trail);
		}
	}
}

static void crtemu_pc_internal_geometry_slice(crtemu_pc_t* crtemu_pc, crtemu_pc_shade_params_t const* p, int y_index, int y_stride)
{
	int x, y;
	int width = p->width, height = p->height;
	float curve_mix = p->curve_mix;
	float vig_scale = p->vig_scale;
	float frame_x_off = p->frame_x_off;

	for (y = y_index; y < height; y += y_stride)
	{
		float v = ((float)y + 0.5f) / (float)height;
		float gy = 1.0f - v;
		float* geom = crtemu_pc->geometry + (size_t)y * (size_t)width * 4u;

		for (x = 0; x < width; ++x, geom += 4)
		{
			float u = ((float)x + 0.5f) / (float)width;
			float cx, cyy, ax, ay, cu, cgy, vig, fvig;

			cx = (u - 0.5f) * 2.0f * 1.1f;
			cyy = (gy - 0.5f) * 2.0f * 1.1f;
			ay = (cyy >= 0.0f ? cyy : -cyy) / 5.0f;
			cx *= 1.0f + ay * ay;
			ax = (cx >= 0.0f ? cx : -cx) / 4.0f;
			cyy *= 1.0f + ax * ax;
			cx = (cx * 0.5f + 0.5f) * 0.92f + 0.04f;
			cyy = (cyy * 0.5f + 0.5f) * 0.92f + 0.04f;
			cu = u * (1.0f - curve_mix) + cx * curve_mix;
			cgy = gy * (1.0f - curve_mix) + cyy * curve_mix;

			if (cu < 0.0f || cu > 1.0f || cgy < 0.0f || cgy > 1.0f)
			{
				geom[0] = 0.0f;
				geom[1] = 0.0f;
				geom[2] = -1.0f;
				geom[3] = 0.0f;
				continue;
			}

			geom[0] = ((cu * 0.96f + 0.023f) * 1.035f + frame_x_off) * 1.2f - 0.1f;
			geom[1] = 1.076f - (cgy * 0.96f + 0.019f) * 1.152f;

			vig = 0.1f + 16.0f * cu * cgy * (1.0f - cu) * (1.0f - cgy);
			vig = 1.3f * sqrtf(vig);
			vig = 1.0f + (vig - 1.0f) * vig_scale;
			geom[2] = vig;

			fvig = crtemu_pc_internal_clampf(512.0f * u * gy * (1.0f - u) * (1.0f - gy), 0.2f, 0.85f);
			geom[3] = fvig;
		}
	}
}

static void crtemu_pc_internal_shade_slice(crtemu_pc_t* crtemu_pc, crtemu_pc_shade_params_t const* p, int y_index, int y_stride)
{
	int x, y;
	int width = p->width, height = p->height;
	int frame_index = p->frame_index;
	float t = p->t;
	float mod_r = p->mod_r, mod_g = p->mod_g, mod_b = p->mod_b;
	float sep_scale = p->sep_scale;
	float ghs = p->ghs;
	float noise_amt = p->noise_amt;
	float flicker_amt = p->flicker_amt;
	float wobble_amp = p->wobble_amp;
	float v_min = p->v_min;
	float v_max = p->v_max;
	int apply_cbs = p->apply_cbs;
	float cbs_contrast = p->cbs_contrast;
	float cbs_brightness = p->cbs_brightness;
	float cbs_saturation = p->cbs_saturation;
	unsigned char const* display = crtemu_pc->display_pixels;
	unsigned char const* blurbuf = crtemu_pc->blur_pixels;
	float sep_r_du = 0.000225f * sep_scale * 1.242f;
	float sep_r_dv = -0.000225f * sep_scale * 1.152f;
	float sep_g_dv = 0.000275f * sep_scale * 1.152f;
	float sep_b_du = -0.000375f * sep_scale * 1.242f;

	for (y = y_index; y < height; y += y_stride)
	{
		float gy = 1.0f - ((float)y + 0.5f) / (float)height;
		float x_w = sinf(0.1f * t + gy * 13.0f) * sinf(0.23f * t + gy * 19.0f) * sinf(0.3f + 0.11f * t + gy * 23.0f) * wobble_amp * 0.2f;
		float wob_du = x_w * 1.242f;
		float gh_r_du = (0.45f * x_w - 0.0053f + 0.007f * 0.35f * sinf(1.0f / 7.0f + 15.0f * gy + 0.9f * t)) * 1.242f;
		float gh_r_dv = -(-0.01115f + 0.007f * 0.35f * sinf(2.0f / 7.0f + 10.0f * gy + 1.37f * t)) * 1.152f;
		float gh_g_du = (0.45f * x_w - 0.00855f + 0.007f * 0.35f * cosf(1.0f / 9.0f + 15.0f * gy + 0.5f * t)) * 1.242f;
		float gh_g_dv = -(-0.011f + 0.007f * 0.35f * sinf(2.0f / 9.0f + 10.0f * gy + 1.5f * t)) * 1.152f;
		float gh_b_du = (0.35f * x_w - 0.00795f + 0.007f * 0.35f * sinf(2.0f / 3.0f + 15.0f * gy + 0.7f * t)) * 1.242f;
		float gh_b_dv = -(-0.00105f + 0.007f * 0.35f * cosf(2.0f / 3.0f + 10.0f * gy + 1.63f * t)) * 1.152f;
		float flicker_row = 1.0f - flicker_amt * (sinf(50.0f * t + gy * 2.0f) * 0.5f + 0.5f);
		float const* geom = crtemu_pc->geometry + (size_t)y * (size_t)width * 4u;

		for (x = 0; x < width; ++x, geom += 4)
		{
			float r, g, b, lum, iv, vig, fvig, su, sv;
			float br, bg, bb;
			float grain_r, grain_g, grain_b;
			int pos = (y * width + x) * 4;

			vig = geom[2];
			if (vig < 0.0f)
			{
				crtemu_pc->processed_pixels[pos + 0] = 0;
				crtemu_pc->processed_pixels[pos + 1] = 0;
				crtemu_pc->processed_pixels[pos + 2] = 0;
				crtemu_pc->processed_pixels[pos + 3] = 255;
				crtemu_pc->diff_pixels[pos + 0] = 0;
				crtemu_pc->diff_pixels[pos + 1] = 0;
				crtemu_pc->diff_pixels[pos + 2] = 0;
				crtemu_pc->diff_pixels[pos + 3] = 255;
				continue;
			}
			su = geom[0] + wob_du;
			sv = geom[1];
			fvig = geom[3];

			/* main color with per-channel separation */
			r = crtemu_pc_internal_decode(crtemu_pc, crtemu_pc_internal_sample_channel(display, width, height, su + sep_r_du, sv + sep_r_dv, 0)) + 0.02f;
			g = crtemu_pc_internal_decode(crtemu_pc, crtemu_pc_internal_sample_channel(display, width, height, su, sv + sep_g_dv, 1)) + 0.02f;
			b = crtemu_pc_internal_decode(crtemu_pc, crtemu_pc_internal_sample_channel(display, width, height, su + sep_b_du, sv, 2)) + 0.02f;

			/* intensity factor */
			iv = crtemu_pc_internal_clampf(r * 0.299f + g * 0.587f + b * 0.114f, 0.0f, 1.0f);
			iv = iv * iv * 0.85f + 0.15f;

			/* ghosting from the blurred display buffer */
			if (ghs > 0.0f)
			{
				float gsu = su - wob_du;
				if (crtemu_pc_internal_sample_rgb(blurbuf, width, height, gsu + gh_r_du, sv + gh_r_dv, &br, &bg, &bb) > 8)
				{
					float w = ghs * (1.0f - 0.299f) * iv;
					float cr = crtemu_pc_internal_clampf(3.0f * 0.5f * crtemu_pc_internal_decode(crtemu_pc, br), 0.0f, 1.0f);
					float cg = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, bg), 0.0f, 1.0f);
					float cb = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, bb), 0.0f, 1.0f);
					r += w * cr * cr; g += w * cg * cg; b += w * cb * cb;
				}
				if (crtemu_pc_internal_sample_rgb(blurbuf, width, height, gsu + gh_g_du, sv + gh_g_dv, &br, &bg, &bb) > 8)
				{
					float w = ghs * (1.0f - 0.587f) * iv;
					float cr = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, br), 0.0f, 1.0f);
					float cg = crtemu_pc_internal_clampf(3.0f * 0.5f * crtemu_pc_internal_decode(crtemu_pc, bg), 0.0f, 1.0f);
					float cb = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, bb), 0.0f, 1.0f);
					r += w * cr * cr; g += w * cg * cg; b += w * cb * cb;
				}
				if (crtemu_pc_internal_sample_rgb(blurbuf, width, height, gsu + gh_b_du, sv + gh_b_dv, &br, &bg, &bb) > 8)
				{
					float w = ghs * (1.0f - 0.114f) * iv;
					float cr = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, br), 0.0f, 1.0f);
					float cg = crtemu_pc_internal_clampf(3.0f * 0.25f * crtemu_pc_internal_decode(crtemu_pc, bg), 0.0f, 1.0f);
					float cb = crtemu_pc_internal_clampf(3.0f * 0.5f * crtemu_pc_internal_decode(crtemu_pc, bb), 0.0f, 1.0f);
					r += w * cr * cr; g += w * cg * cg; b += w * cb * cb;
				}
			}

			/* level adjustment (curves) */
			g *= 1.1f;
			r = crtemu_pc_internal_clampf(r * 1.3f + 0.75f * r * r + 1.25f * r * r * r * r * r, 0.0f, 10.0f);
			g = crtemu_pc_internal_clampf(g * 1.3f + 0.75f * g * g + 1.25f * g * g * g * g * g, 0.0f, 10.0f);
			b = crtemu_pc_internal_clampf(b * 1.3f + 0.75f * b * b + 1.25f * b * b * b * b * b, 0.0f, 10.0f);

			/* vignette */
			r *= vig;
			g *= vig;
			b *= vig;

			grain_r = crtemu_pc_internal_rand(x, y, frame_index);
			grain_g = crtemu_pc_internal_rand(x + 17, y, frame_index);
			grain_b = crtemu_pc_internal_rand(x, y + 31, frame_index);

			{
				/* tone map at scanline/mask minimum and maximum, then noise,
				   flicker, modulate, frame vignette on both */
				float kr = flicker_row * mod_r * fvig;
				float kg = flicker_row * mod_g * fvig;
				float kb = flicker_row * mod_b * fvig;
				float dr = crtemu_pc_internal_filmic(r * v_min) * kr - noise_amt * grain_r * sqrtf(grain_r);
				float dg = crtemu_pc_internal_filmic(g * v_min) * kg - noise_amt * grain_g * sqrtf(grain_g);
				float db = crtemu_pc_internal_filmic(b * v_min) * kb - noise_amt * grain_b * sqrtf(grain_b);
				float xr = crtemu_pc_internal_filmic(r * v_max) * kr - noise_amt * grain_r * sqrtf(grain_r);
				float xg = crtemu_pc_internal_filmic(g * v_max) * kg - noise_amt * grain_g * sqrtf(grain_g);
				float xb = crtemu_pc_internal_filmic(b * v_max) * kb - noise_amt * grain_b * sqrtf(grain_b);

				if (apply_cbs)
				{
					dr = (dr - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					dg = (dg - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					db = (db - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					xr = (xr - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					xg = (xg - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					xb = (xb - 0.5f) * cbs_contrast + 0.5f + cbs_brightness;
					lum = dr * 0.299f + dg * 0.587f + db * 0.114f;
					dr = lum + (dr - lum) * cbs_saturation;
					dg = lum + (dg - lum) * cbs_saturation;
					db = lum + (db - lum) * cbs_saturation;
					lum = xr * 0.299f + xg * 0.587f + xb * 0.114f;
					xr = lum + (xr - lum) * cbs_saturation;
					xg = lum + (xg - lum) * cbs_saturation;
					xb = lum + (xb - lum) * cbs_saturation;
				}

				crtemu_pc->processed_pixels[pos + 0] = crtemu_pc_internal_tobyte(dr);
				crtemu_pc->processed_pixels[pos + 1] = crtemu_pc_internal_tobyte(dg);
				crtemu_pc->processed_pixels[pos + 2] = crtemu_pc_internal_tobyte(db);
				crtemu_pc->processed_pixels[pos + 3] = 255;
				crtemu_pc->diff_pixels[pos + 0] = crtemu_pc_internal_tobyte(xr - crtemu_pc_internal_clampf(dr, 0.0f, 1.0f));
				crtemu_pc->diff_pixels[pos + 1] = crtemu_pc_internal_tobyte(xg - crtemu_pc_internal_clampf(dg, 0.0f, 1.0f));
				crtemu_pc->diff_pixels[pos + 2] = crtemu_pc_internal_tobyte(xb - crtemu_pc_internal_clampf(db, 0.0f, 1.0f));
				crtemu_pc->diff_pixels[pos + 3] = 255;
			}
		}
	}
}

static void crtemu_pc_internal_barrier_wait(crtemu_pc_barrier_t* barrier)
{
#ifndef CRTEMU_PC_SDL
	long generation = barrier->generation;
	if (_InterlockedIncrement(&barrier->count) == barrier->total)
	{
		barrier->count = 0;
		_InterlockedIncrement(&barrier->generation);
	}
	else
	{
		int spins = 0;
		while (barrier->generation == generation)
		{
			if (++spins < 2048)
			{
			#if defined(_M_X64) || defined(_M_IX86)
				_mm_pause();
			#endif
			}
			else
			{
				SwitchToThread();
			}
		}
	}
#else
	(void)barrier;
#endif
}

static void crtemu_pc_internal_process_slices(crtemu_pc_work_t* work)
{
	crtemu_pc_t* crtemu_pc = work->crtemu_pc;
	int width = work->params->width;
	int height = work->params->height;
	int index = work->index;
	int stride = work->count;

	crtemu_pc_internal_convert_slice(crtemu_pc, work->pixels_xbgr, width, height, index, stride);
	crtemu_pc_internal_blur_pass(crtemu_pc->temp_pixels, crtemu_pc->history_pixels, width, height, 1, index, stride);
	if (work->params->rebuild_geometry)
	{
		crtemu_pc_internal_geometry_slice(crtemu_pc, work->params, index, stride);
	}
	crtemu_pc_internal_barrier_wait(work->barrier);
	crtemu_pc_internal_blur_pass(crtemu_pc->display_pixels, crtemu_pc->temp_pixels, width, height, 0, index, stride);
	crtemu_pc_internal_accum_slice(crtemu_pc, width, height, index, stride);
	crtemu_pc_internal_barrier_wait(work->barrier);
	crtemu_pc_internal_blur_pass(crtemu_pc->temp_pixels, crtemu_pc->display_pixels, width, height, 1, index, stride);
	crtemu_pc_internal_barrier_wait(work->barrier);
	crtemu_pc_internal_blur_pass(crtemu_pc->blur_pixels, crtemu_pc->temp_pixels, width, height, 0, index, stride);
	crtemu_pc_internal_barrier_wait(work->barrier);
	crtemu_pc_internal_shade_slice(crtemu_pc, work->params, index, stride);
}

#ifndef CRTEMU_PC_SDL
static unsigned long __stdcall crtemu_pc_internal_pool_worker(void* param)
{
	crtemu_pc_pool_slot_t* slot = (crtemu_pc_pool_slot_t*)param;
	crtemu_pc_t* crtemu_pc = slot->crtemu_pc;
	int index = slot->index;
	for (;;)
	{
		WaitForSingleObject(crtemu_pc->pool_work_events[index], 0xFFFFFFFF /* INFINITE */);
		if (crtemu_pc->pool_shutdown)
		{
			break;
		}
		crtemu_pc_internal_process_slices(&crtemu_pc->pool_work[index + 1]);
		SetEvent(crtemu_pc->pool_done_events[index]);
	}
	return 0;
}

static void crtemu_pc_internal_pool_start(crtemu_pc_t* crtemu_pc)
{
	int i;
	crtemu_pc->pool_size = 0;
	crtemu_pc->pool_shutdown = 0;
	for (i = 0; i < crtemu_pc->thread_count - 1; ++i)
	{
		void* work_event = CreateEventA(NULL, 0, 0, NULL);
		void* done_event = CreateEventA(NULL, 0, 0, NULL);
		void* thread;
		if (!work_event || !done_event)
		{
			if (work_event)
			{
				CloseHandle(work_event);
			}
			if (done_event)
			{
				CloseHandle(done_event);
			}
			break;
		}
		crtemu_pc->pool_work_events[i] = work_event;
		crtemu_pc->pool_done_events[i] = done_event;
		crtemu_pc->pool_slots[i].crtemu_pc = crtemu_pc;
		crtemu_pc->pool_slots[i].index = i;
		thread = CreateThread(NULL, 0, crtemu_pc_internal_pool_worker, &crtemu_pc->pool_slots[i], 0, NULL);
		if (!thread)
		{
			CloseHandle(work_event);
			CloseHandle(done_event);
			break;
		}
		crtemu_pc->pool_threads[i] = thread;
		++crtemu_pc->pool_size;
	}
}

static void crtemu_pc_internal_pool_stop(crtemu_pc_t* crtemu_pc)
{
	int i;
	if (crtemu_pc->pool_size <= 0)
	{
		return;
	}
	crtemu_pc->pool_shutdown = 1;
	for (i = 0; i < crtemu_pc->pool_size; ++i)
	{
		SetEvent(crtemu_pc->pool_work_events[i]);
	}
	WaitForMultipleObjects((unsigned long)crtemu_pc->pool_size, crtemu_pc->pool_threads, 1, 0xFFFFFFFFul);
	for (i = 0; i < crtemu_pc->pool_size; ++i)
	{
		CloseHandle(crtemu_pc->pool_threads[i]);
		CloseHandle(crtemu_pc->pool_work_events[i]);
		CloseHandle(crtemu_pc->pool_done_events[i]);
	}
	crtemu_pc->pool_size = 0;
}
#endif

static void crtemu_pc_internal_process(crtemu_pc_t* crtemu_pc, CRTEMU_PC_U32 const* pixels_xbgr, int width, int height, CRTEMU_PC_U32 mod_xbgr)
{
	crtemu_pc_shade_params_t params;
	crtemu_pc_barrier_t barrier;
#ifdef CRTEMU_PC_SDL
	crtemu_pc_work_t work;
#endif
	float scan_amp = crtemu_pc_internal_clampf(0.2f + crtemu_pc->config.scanlines * 0.2f, 0.0f, 0.45f);
	float mask_amp = crtemu_pc_internal_clampf(0.23f + crtemu_pc->config.shadow_mask * 0.23f, 0.0f, 0.9f);

	params.width = width;
	params.height = height;
	params.frame_index = (int)(crtemu_pc->time * 60.0f);
	params.t = crtemu_pc->time;
	crtemu_pc_internal_xbgr_to_rgb(mod_xbgr, &params.mod_r, &params.mod_g, &params.mod_b);
	params.curve_mix = crtemu_pc_internal_clampf(0.2f + crtemu_pc->config.curvature * 0.2f, 0.0f, 1.0f);
	params.sep_scale = crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.separation * 8.0f, 0.0f, 16.0f);
	params.ghs = 0.05f * crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.ghosting * 2.0f, 0.0f, 3.0f);
	params.noise_amt = 0.015f * crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.noise * 2.0f, 0.0f, 3.0f);
	params.flicker_amt = 0.004f * crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.flicker * 2.0f, 0.0f, 3.0f);
	params.vig_scale = crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.vignette * 1.5f, 0.0f, 3.0f);
	params.wobble_amp = 0.0012f * crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.distortion * 2.0f, 0.0f, 4.0f);
	params.frame_x_off = crtemu_pc->use_frame != 0.0f ? -0.009375f : -0.018f;
	params.v_min = crtemu_pc_internal_clampf(powf(0.5f - scan_amp, 0.9f), 0.0f, 1.0f) * (1.0f - mask_amp);
	params.v_max = powf(0.5f + scan_amp, 0.9f) * (1.0f - 0.25f * mask_amp);
	params.apply_cbs = crtemu_pc->config.contrast != 0.0f || crtemu_pc->config.brightness != 0.0f || crtemu_pc->config.saturation != 0.0f;
	params.cbs_contrast = 1.0f + crtemu_pc->config.contrast * 0.5f;
	params.cbs_brightness = crtemu_pc->config.brightness * 0.25f;
	params.cbs_saturation = crtemu_pc_internal_clampf(1.0f + crtemu_pc->config.saturation, 0.0f, 2.5f);

	params.rebuild_geometry = !crtemu_pc->geometry_valid ||
		crtemu_pc->geometry_curve_mix != params.curve_mix ||
		crtemu_pc->geometry_vig_scale != params.vig_scale ||
		crtemu_pc->geometry_frame_x_off != params.frame_x_off;
	if (params.rebuild_geometry)
	{
		crtemu_pc->geometry_valid = 1;
		crtemu_pc->geometry_curve_mix = params.curve_mix;
		crtemu_pc->geometry_vig_scale = params.vig_scale;
		crtemu_pc->geometry_frame_x_off = params.frame_x_off;
	}

	barrier.count = 0;
	barrier.generation = 0;
	barrier.total = 1;

#ifndef CRTEMU_PC_SDL
	{
		int i;
		int participants = crtemu_pc->pool_size + 1;
		barrier.total = participants;
		for (i = 0; i < participants; ++i)
		{
			crtemu_pc->pool_work[i].crtemu_pc = crtemu_pc;
			crtemu_pc->pool_work[i].pixels_xbgr = pixels_xbgr;
			crtemu_pc->pool_work[i].params = &params;
			crtemu_pc->pool_work[i].barrier = &barrier;
			crtemu_pc->pool_work[i].index = i;
			crtemu_pc->pool_work[i].count = participants;
		}
		for (i = 0; i < crtemu_pc->pool_size; ++i)
		{
			SetEvent(crtemu_pc->pool_work_events[i]);
		}
		crtemu_pc_internal_process_slices(&crtemu_pc->pool_work[0]);
		if (crtemu_pc->pool_size > 0)
		{
			WaitForMultipleObjects((unsigned long)crtemu_pc->pool_size, crtemu_pc->pool_done_events, 1, 0xFFFFFFFF /* INFINITE */);
		}
	}
#else
	work.crtemu_pc = crtemu_pc;
	work.pixels_xbgr = pixels_xbgr;
	work.params = &params;
	work.barrier = &barrier;
	work.index = 0;
	work.count = 1;
	crtemu_pc_internal_process_slices(&work);
#endif
}

static void crtemu_pc_internal_update_overlay(crtemu_pc_t* crtemu_pc, int width, int height)
{
	float scan_amp = crtemu_pc_internal_clampf(0.2f + crtemu_pc->config.scanlines * 0.2f, 0.0f, 0.45f);
	float mask_amp = crtemu_pc_internal_clampf(0.23f + crtemu_pc->config.shadow_mask * 0.23f, 0.0f, 0.9f);
	float v_min = crtemu_pc_internal_clampf(powf(0.5f - scan_amp, 0.9f), 0.0f, 1.0f) * (1.0f - mask_amp);
	float v_max = powf(0.5f + scan_amp, 0.9f) * (1.0f - 0.25f * mask_amp);
	float v_range = v_max - v_min > 0.000001f ? v_max - v_min : 0.000001f;
	float m[3];
	unsigned char* pixels;
	unsigned char row_bytes[3];
	int x, y, k;

	if (crtemu_pc->overlay_width == width && crtemu_pc->overlay_height == height &&
		crtemu_pc->overlay_scanlines == scan_amp && crtemu_pc->overlay_shadow_mask == mask_amp)
	{
		return;
	}

	pixels = (unsigned char*)CRTEMU_PC_MALLOC(crtemu_pc->memctx, (size_t)width * (size_t)height);
	if (!pixels)
	{
		return;
	}

	for (k = 0; k < 3; ++k)
	{
		m[k] = 1.0f - mask_amp * crtemu_pc_internal_clampf(((float)k + 0.5f) / 2.0f, 0.0f, 1.0f);
	}

	for (y = 0; y < height; ++y)
	{
		int j = height - 1 - y;
		float s = crtemu_pc_internal_clampf(0.5f + scan_amp * sinf(((float)j + 0.5f) * 1.75f), 0.0f, 1.0f);
		s = powf(s, 0.9f);
		for (k = 0; k < 3; ++k)
		{
			row_bytes[k] = crtemu_pc_internal_tobyte(powf(crtemu_pc_internal_clampf((s * m[k] - v_min) / v_range, 0.0f, 1.0f), 0.9f));
		}
		for (x = 0; x < width; ++x)
		{
			pixels[y * width + x] = row_bytes[x % 3];
		}
	}

	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->overlay_texture);
	crtemu_pc->TexImage2D(CRTEMU_PC_GL_TEXTURE_2D, 0, CRTEMU_PC_GL_LUMINANCE, width, height, 0, CRTEMU_PC_GL_LUMINANCE, CRTEMU_PC_GL_UNSIGNED_BYTE, pixels);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_NEAREST);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_NEAREST);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_S, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_T, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, 0);
	CRTEMU_PC_FREE(crtemu_pc->memctx, pixels);

	crtemu_pc->overlay_width = width;
	crtemu_pc->overlay_height = height;
	crtemu_pc->overlay_scanlines = scan_amp;
	crtemu_pc->overlay_shadow_mask = mask_amp;
}

static void crtemu_pc_internal_draw_textured_quad(crtemu_pc_t* crtemu_pc)
{
	crtemu_pc->Begin(CRTEMU_PC_GL_QUADS);
	crtemu_pc->TexCoord2f(0.0f, 1.0f); crtemu_pc->Vertex2f(-1.0f, -1.0f);
	crtemu_pc->TexCoord2f(1.0f, 1.0f); crtemu_pc->Vertex2f(1.0f, -1.0f);
	crtemu_pc->TexCoord2f(1.0f, 0.0f); crtemu_pc->Vertex2f(1.0f, 1.0f);
	crtemu_pc->TexCoord2f(0.0f, 0.0f); crtemu_pc->Vertex2f(-1.0f, 1.0f);
	crtemu_pc->End();
}

#ifndef CRTEMU_PC_SDL
#define CRTEMU_PC_LOAD_GL(name, type) crtemu_pc->name = (type)(uintptr_t)GetProcAddress(crtemu_pc->gl_dll, "gl" #name); \
		if (!crtemu_pc->name && crtemu_pc->wglGetProcAddress) crtemu_pc->name = (type)(uintptr_t)crtemu_pc->wglGetProcAddress("gl" #name)
#endif

crtemu_pc_t* crtemu_pc_create(void* memctx)
{
	int i;
	crtemu_pc_t* crtemu_pc = (crtemu_pc_t*)CRTEMU_PC_MALLOC(memctx, sizeof(crtemu_pc_t));
	if (!crtemu_pc)
	{
		return NULL;
	}
	memset(crtemu_pc, 0, sizeof(crtemu_pc_t));
	crtemu_pc->memctx = memctx;

	for (i = 0; i < 1024; ++i)
	{
		crtemu_pc->gamma_lut[i] = powf((float)i / 1023.0f, 2.2f) * 1.25f;
	}

	crtemu_pc->thread_count = 1;
#ifndef CRTEMU_PC_SDL
	{
		int processor_count = (int)GetActiveProcessorCount(0xffff /* ALL_PROCESSOR_GROUPS */);
		crtemu_pc->thread_count = crtemu_pc_internal_clampi(processor_count, 1, CRTEMU_PC_MAX_THREADS);
		crtemu_pc_internal_pool_start(crtemu_pc);
	}
#endif

#ifndef CRTEMU_PC_SDL
	crtemu_pc->gl_dll = LoadLibraryA("opengl32.dll");
	if (!crtemu_pc->gl_dll)
	{
		goto failed;
	}
	crtemu_pc->wglGetProcAddress = (CRTEMU_PC_PROC(CRTEMU_PC_GLCALLTYPE*)(char const*))(uintptr_t)GetProcAddress(crtemu_pc->gl_dll, "wglGetProcAddress");

	CRTEMU_PC_LOAD_GL(GenTextures, crtemu_pc_glGenTexturesProc);
	CRTEMU_PC_LOAD_GL(BindTexture, crtemu_pc_glBindTextureProc);
	CRTEMU_PC_LOAD_GL(TexImage2D, crtemu_pc_glTexImage2DProc);
	CRTEMU_PC_LOAD_GL(TexParameteri, crtemu_pc_glTexParameteriProc);
	CRTEMU_PC_LOAD_GL(ClearColor, crtemu_pc_glClearColorProc);
	CRTEMU_PC_LOAD_GL(Clear, crtemu_pc_glClearProc);
	CRTEMU_PC_LOAD_GL(Enable, crtemu_pc_glEnableProc);
	CRTEMU_PC_LOAD_GL(Disable, crtemu_pc_glDisableProc);
	CRTEMU_PC_LOAD_GL(BlendFunc, crtemu_pc_glBlendFuncProc);
	CRTEMU_PC_LOAD_GL(Begin, crtemu_pc_glBeginProc);
	CRTEMU_PC_LOAD_GL(End, crtemu_pc_glEndProc);
	CRTEMU_PC_LOAD_GL(TexCoord2f, crtemu_pc_glTexCoord2fProc);
	CRTEMU_PC_LOAD_GL(Vertex2f, crtemu_pc_glVertex2fProc);
	CRTEMU_PC_LOAD_GL(Viewport, crtemu_pc_glViewportProc);
	CRTEMU_PC_LOAD_GL(GetIntegerv, crtemu_pc_glGetIntegervProc);
	CRTEMU_PC_LOAD_GL(DeleteTextures, crtemu_pc_glDeleteTexturesProc);
	CRTEMU_PC_LOAD_GL(MatrixMode, crtemu_pc_glMatrixModeProc);
	CRTEMU_PC_LOAD_GL(LoadIdentity, crtemu_pc_glLoadIdentityProc);
	CRTEMU_PC_LOAD_GL(Color3f, crtemu_pc_glColor3fProc);
	CRTEMU_PC_LOAD_GL(TexEnvi, crtemu_pc_glTexEnviProc);
#else
	crtemu_pc->GenTextures = glGenTextures;
	crtemu_pc->BindTexture = glBindTexture;
	crtemu_pc->TexImage2D = glTexImage2D;
	crtemu_pc->TexParameteri = glTexParameteri;
	crtemu_pc->ClearColor = glClearColor;
	crtemu_pc->Clear = glClear;
	crtemu_pc->Enable = glEnable;
	crtemu_pc->Disable = glDisable;
	crtemu_pc->BlendFunc = glBlendFunc;
	crtemu_pc->Begin = glBegin;
	crtemu_pc->End = glEnd;
	crtemu_pc->TexCoord2f = glTexCoord2f;
	crtemu_pc->Vertex2f = glVertex2f;
	crtemu_pc->Viewport = glViewport;
	crtemu_pc->GetIntegerv = glGetIntegerv;
	crtemu_pc->DeleteTextures = glDeleteTextures;
	crtemu_pc->MatrixMode = glMatrixMode;
	crtemu_pc->LoadIdentity = glLoadIdentity;
	crtemu_pc->Color3f = glColor3f;
	crtemu_pc->TexEnvi = glTexEnvi;
#endif

	if (!crtemu_pc->GenTextures || !crtemu_pc->BindTexture || !crtemu_pc->TexImage2D || !crtemu_pc->TexParameteri ||
		!crtemu_pc->ClearColor || !crtemu_pc->Clear || !crtemu_pc->Enable || !crtemu_pc->Disable || !crtemu_pc->BlendFunc ||
		!crtemu_pc->Begin || !crtemu_pc->End || !crtemu_pc->TexCoord2f || !crtemu_pc->Vertex2f || !crtemu_pc->Viewport ||
		!crtemu_pc->GetIntegerv || !crtemu_pc->DeleteTextures || !crtemu_pc->MatrixMode || !crtemu_pc->LoadIdentity ||
		!crtemu_pc->Color3f || !crtemu_pc->TexEnvi)
	{
		goto failed;
	}

	crtemu_pc->GenTextures(1, &crtemu_pc->backbuffer);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->backbuffer);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_S, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_T, CRTEMU_PC_GL_CLAMP);

	crtemu_pc->GenTextures(1, &crtemu_pc->diffbuffer);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->diffbuffer);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_S, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_T, CRTEMU_PC_GL_CLAMP);

	crtemu_pc->GenTextures(1, &crtemu_pc->frame_texture);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->frame_texture);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_S, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_T, CRTEMU_PC_GL_CLAMP);

	crtemu_pc->GenTextures(1, &crtemu_pc->overlay_texture);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, 0);

	return crtemu_pc;

failed:
#ifndef CRTEMU_PC_SDL
	crtemu_pc_internal_pool_stop(crtemu_pc);
	if (crtemu_pc->gl_dll)
	{
		FreeLibrary(crtemu_pc->gl_dll);
	}
#endif
	CRTEMU_PC_FREE(memctx, crtemu_pc);
	return NULL;
}

void crtemu_pc_destroy(crtemu_pc_t* crtemu_pc)
{
#ifndef CRTEMU_PC_SDL
	crtemu_pc_internal_pool_stop(crtemu_pc);
#endif
	if (crtemu_pc->backbuffer)
	{
		crtemu_pc->DeleteTextures(1, &crtemu_pc->backbuffer);
	}
	if (crtemu_pc->diffbuffer)
	{
		crtemu_pc->DeleteTextures(1, &crtemu_pc->diffbuffer);
	}
	if (crtemu_pc->frame_texture)
	{
		crtemu_pc->DeleteTextures(1, &crtemu_pc->frame_texture);
	}
	if (crtemu_pc->overlay_texture)
	{
		crtemu_pc->DeleteTextures(1, &crtemu_pc->overlay_texture);
	}
	if (crtemu_pc->source_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->source_pixels);
	}
	if (crtemu_pc->history_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->history_pixels);
	}
	if (crtemu_pc->display_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->display_pixels);
	}
	if (crtemu_pc->blur_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->blur_pixels);
	}
	if (crtemu_pc->temp_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->temp_pixels);
	}
	if (crtemu_pc->processed_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->processed_pixels);
	}
	if (crtemu_pc->diff_pixels)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->diff_pixels);
	}
	if (crtemu_pc->geometry)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc->geometry);
	}
#ifndef CRTEMU_PC_SDL
	if (crtemu_pc->gl_dll)
	{
		FreeLibrary(crtemu_pc->gl_dll);
	}
#endif
	CRTEMU_PC_FREE(crtemu_pc->memctx, crtemu_pc);
}

void crtemu_pc_config(crtemu_pc_t* crtemu_pc, crtemu_pc_config_t const* config)
{
	if (crtemu_pc && config)
	{
		crtemu_pc->config = *config;
	}
}

void crtemu_pc_frame(crtemu_pc_t* crtemu_pc, CRTEMU_PC_U32* frame_abgr, int frame_width, int frame_height)
{
	unsigned char transfer[256];
	unsigned char* transformed;
	size_t i, count;

	if (!frame_abgr || frame_width <= 0 || frame_height <= 0)
	{
		crtemu_pc->use_frame = 0.0f;
		crtemu_pc->frame_width = 0;
		crtemu_pc->frame_height = 0;
		return;
	}

	for (i = 0; i < 256; ++i)
	{
		transfer[i] = crtemu_pc_internal_tobyte(powf((float)i / 255.0f * 0.5f + 0.25f, 1.4f));
	}

	count = (size_t)frame_width * (size_t)frame_height;
	transformed = (unsigned char*)CRTEMU_PC_MALLOC(crtemu_pc->memctx, count * 4);
	if (transformed)
	{
		unsigned char const* src = (unsigned char const*)frame_abgr;
		for (i = 0; i < count; ++i)
		{
			transformed[i * 4 + 0] = transfer[src[i * 4 + 0]];
			transformed[i * 4 + 1] = transfer[src[i * 4 + 1]];
			transformed[i * 4 + 2] = transfer[src[i * 4 + 2]];
			transformed[i * 4 + 3] = src[i * 4 + 3];
		}
	}

	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->frame_texture);
	crtemu_pc->TexImage2D(CRTEMU_PC_GL_TEXTURE_2D, 0, CRTEMU_PC_GL_RGBA, frame_width, frame_height, 0, CRTEMU_PC_GL_RGBA, CRTEMU_PC_GL_UNSIGNED_BYTE, transformed ? transformed : (unsigned char const*)frame_abgr);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_S, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_WRAP_T, CRTEMU_PC_GL_CLAMP);
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, 0);
	if (transformed)
	{
		CRTEMU_PC_FREE(crtemu_pc->memctx, transformed);
	}
	crtemu_pc->frame_width = frame_width;
	crtemu_pc->frame_height = frame_height;
	crtemu_pc->use_frame = 1.0f;
}

void crtemu_pc_present(crtemu_pc_t* crtemu_pc, CRTEMU_PC_U64 time_us, CRTEMU_PC_U32 const* pixels_xbgr, int width, int height,
	CRTEMU_PC_U32 mod_xbgr, CRTEMU_PC_U32 border_xbgr)
{
	CRTEMU_PC_GLint viewport_gl[4];
	int viewport[4];
	crtemu_pc_rect_t rect;
	float border_r, border_g, border_b;

	crtemu_pc->time = 1.5f * (float)((double)time_us / 1000000.0);
	crtemu_pc->last_present_width = width;
	crtemu_pc->last_present_height = height;

	if (!crtemu_pc_internal_ensure_buffers(crtemu_pc, width, height))
	{
		return;
	}

	crtemu_pc_internal_process(crtemu_pc, pixels_xbgr, width, height, mod_xbgr);

	crtemu_pc->GetIntegerv(CRTEMU_PC_GL_VIEWPORT, viewport_gl);
	viewport[0] = viewport_gl[0];
	viewport[1] = viewport_gl[1];
	viewport[2] = viewport_gl[2];
	viewport[3] = viewport_gl[3];
	crtemu_pc_internal_display_rect(crtemu_pc, viewport, width, height, &rect);
	crtemu_pc_internal_xbgr_to_rgb(border_xbgr, &border_r, &border_g, &border_b);

	crtemu_pc->Viewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	crtemu_pc->ClearColor(border_r, border_g, border_b, 1.0f);
	crtemu_pc->Clear(CRTEMU_PC_GL_COLOR_BUFFER_BIT);

	crtemu_pc->Viewport(rect.x, rect.y, rect.w, rect.h);
	crtemu_pc->MatrixMode(CRTEMU_PC_GL_PROJECTION);
	crtemu_pc->LoadIdentity();
	crtemu_pc->MatrixMode(CRTEMU_PC_GL_MODELVIEW);
	crtemu_pc->LoadIdentity();
	crtemu_pc->Color3f(1.0f, 1.0f, 1.0f);
	crtemu_pc->TexEnvi(CRTEMU_PC_GL_TEXTURE_ENV, CRTEMU_PC_GL_TEXTURE_ENV_MODE, CRTEMU_PC_GL_MODULATE);
	crtemu_pc->Enable(CRTEMU_PC_GL_TEXTURE_2D);

	crtemu_pc_internal_update_overlay(crtemu_pc, rect.w, rect.h);
	if (crtemu_pc->overlay_width == rect.w && crtemu_pc->overlay_height == rect.h)
	{
		crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->overlay_texture);
		crtemu_pc_internal_draw_textured_quad(crtemu_pc);

		crtemu_pc->Enable(CRTEMU_PC_GL_BLEND);
		crtemu_pc->BlendFunc(CRTEMU_PC_GL_DST_COLOR, CRTEMU_PC_GL_ZERO);
		crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->diffbuffer);
		crtemu_pc->TexImage2D(CRTEMU_PC_GL_TEXTURE_2D, 0, CRTEMU_PC_GL_RGBA, width, height, 0, CRTEMU_PC_GL_RGBA, CRTEMU_PC_GL_UNSIGNED_BYTE, crtemu_pc->diff_pixels);
		crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
		crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
		crtemu_pc_internal_draw_textured_quad(crtemu_pc);

		crtemu_pc->BlendFunc(CRTEMU_PC_GL_ONE, CRTEMU_PC_GL_ONE);
	}
	else
	{
		crtemu_pc->Enable(CRTEMU_PC_GL_BLEND);
		crtemu_pc->BlendFunc(CRTEMU_PC_GL_ONE, CRTEMU_PC_GL_ZERO);
	}
	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->backbuffer);
	crtemu_pc->TexImage2D(CRTEMU_PC_GL_TEXTURE_2D, 0, CRTEMU_PC_GL_RGBA, width, height, 0, CRTEMU_PC_GL_RGBA, CRTEMU_PC_GL_UNSIGNED_BYTE, crtemu_pc->processed_pixels);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MIN_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc->TexParameteri(CRTEMU_PC_GL_TEXTURE_2D, CRTEMU_PC_GL_TEXTURE_MAG_FILTER, CRTEMU_PC_GL_LINEAR);
	crtemu_pc_internal_draw_textured_quad(crtemu_pc);
	crtemu_pc->Disable(CRTEMU_PC_GL_BLEND);

	if (crtemu_pc->use_frame != 0.0f && crtemu_pc->frame_width > 0 && crtemu_pc->frame_height > 0)
	{
		int frame_x = rect.x + (int)((float)rect.w * -0.06695f);
		int frame_y = rect.y + (int)((float)rect.h * -0.15193f);
		int frame_w = (int)((float)rect.w * 1.12378f);
		int frame_h = (int)((float)rect.h * 1.28068f);
		crtemu_pc->Enable(CRTEMU_PC_GL_BLEND);
		crtemu_pc->BlendFunc(CRTEMU_PC_GL_SRC_ALPHA, CRTEMU_PC_GL_ONE_MINUS_SRC_ALPHA);
		crtemu_pc->Viewport(frame_x, frame_y, frame_w, frame_h);
		crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, crtemu_pc->frame_texture);
		crtemu_pc_internal_draw_textured_quad(crtemu_pc);
		crtemu_pc->Disable(CRTEMU_PC_GL_BLEND);
	}

	crtemu_pc->BindTexture(CRTEMU_PC_GL_TEXTURE_2D, 0);
	crtemu_pc->Disable(CRTEMU_PC_GL_TEXTURE_2D);
	crtemu_pc->Viewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void crtemu_pc_coordinates_window_to_bitmap(crtemu_pc_t* crtemu_pc, int width, int height, int* x, int* y)
{
	CRTEMU_PC_GLint viewport_gl[4];
	int viewport[4];
	crtemu_pc_rect_t rect;
	float u, v, su, sv, cu, cv;

	crtemu_pc->GetIntegerv(CRTEMU_PC_GL_VIEWPORT, viewport_gl);
	viewport[0] = viewport_gl[0];
	viewport[1] = viewport_gl[1];
	viewport[2] = viewport_gl[2];
	viewport[3] = viewport_gl[3];
	crtemu_pc_internal_display_rect(crtemu_pc, viewport, width, height, &rect);

	u = ((float)(*x - rect.x)) / (float)(rect.w > 0 ? rect.w : 1);
	v = ((float)(*y - rect.y)) / (float)(rect.h > 0 ? rect.h : 1);
	crtemu_pc_internal_source_uv(crtemu_pc, u, v, &su, &sv, &cu, &cv);
	*x = (int)(su * (float)width);
	*y = (int)(sv * (float)height);
}

void crtemu_pc_coordinates_bitmap_to_window(crtemu_pc_t* crtemu_pc, int width, int height, int* x, int* y)
{
	CRTEMU_PC_GLint viewport_gl[4];
	int viewport[4];
	crtemu_pc_rect_t rect;
	float u, v;

	crtemu_pc->GetIntegerv(CRTEMU_PC_GL_VIEWPORT, viewport_gl);
	viewport[0] = viewport_gl[0];
	viewport[1] = viewport_gl[1];
	viewport[2] = viewport_gl[2];
	viewport[3] = viewport_gl[3];
	crtemu_pc_internal_display_rect(crtemu_pc, viewport, width, height, &rect);

	u = ((float)*x + 0.5f) / (float)width;
	v = ((float)*y + 0.5f) / (float)height;
	*x = rect.x + (int)(u * (float)rect.w);
	*y = rect.y + (int)(v * (float)rect.h);
}

#ifndef CRTEMU_PC_SDL
#undef CRTEMU_PC_LOAD_GL
#endif

#endif /* CRTEMU_PC_IMPLEMENTATION */
#endif
