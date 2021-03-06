#ifndef TEXTURE_MODE
#define TEXTURE_MODE

enum TEXTURE_TYPE
{
	TEXTURE_1D = 0,
	TEXTURE_2D,
	TEXTURE_3D
};

enum TEXTURE_WRAP_MODE
{
	WRAP_REPEAT = 0,
	WRAP_CLAMP_EDGE,
	WRAP_CLAMP_BORDER
};

enum TEXTURE_FILTER_MODE
{
	FILTER_NEAREST = 0,
	FILTER_LINEAR,
	FILTER_NEAREST_MIPMAP_NEAREST,
	FILTER_LINEAR_MIPMAP_NEAREST,
	FILTER_NEAREST_MIPMAP_LINEAR,
	FILTER_LINEAR_MIPMAP_LINEAR
};

enum TEXTURE_SIZED_INTERNAL_FORMAT
{
	FORMAT_R8 = 0,
	FORMAT_R16,
	FORMAT_RG8,
	FORMAT_RG16F,
	FORMAT_RG32F,
	FORMAT_RGB8,
	FORMAT_RGB16,
	FORMAT_RGB32,
	FORMAT_RGBA8,
	FORMAT_RGBA16,
	FORMAT_RGBA32,
	FORMAT_DEPTH16,
	FORMAT_DEPTH32,
	FORMAT_DEPTH24_STENCIL8,
};

enum TEXTURE_INTERNAL_FORMAT
{
	FORMAT_RED = 0,
	FORMAT_RG,
	FORMAT_RGB,
	FORMAT_RGBA,
	FORMAT_DEPTH,
	FORMAT_DEPTH_STENCIL
};

enum TEXTURE_CHANNEL_TYPE
{
	CHANNEL_UNSIGNED_BYTE = 0,
	CHANNEL_FLOAT
};

enum TEXTURE_COMPRESSION_TYPE
{
	COMPRESS_NONE = 0,
	COMPRESS_BC1,        /* DXT1  */
	COMPRESS_BC2,        /* DXT3  */
	COMPRESS_BC3,        /* DXT5  */
	COMPRESS_BC3N,       /* DXT5n */
	COMPRESS_BC4,        /* ATI1  */
	COMPRESS_BC5,        /* ATI2  */
	COMPRESS_AEXP,       /* DXT5  */
	COMPRESS_YCOCG,      /* DXT5  */
	COMPRESS_YCOCGS,     /* DXT5  */
	COMPRESS_MAX
};

struct Size
{
	std::size_t width;
	std::size_t height;
	std::size_t depth;

	Size (std::size_t width, std::size_t height, std::size_t depth = 0) :
		width (width),
		height (height),
		depth (depth)
	{
	}
};

#endif