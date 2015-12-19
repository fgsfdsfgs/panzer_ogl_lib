#pragma once

#include "panzer_ogl_lib.hpp"

class r_Texture final
{
	friend class r_Framebuffer;

public:
	enum class PixelFormat
	{
		Unknown= 0,

		//one component formats:
		R8   , R8S , R8UI , R8I ,
		R16  , R16S, R16UI, R16I, R16F,
		R32UI, R32I, R32F ,

		//two component formats:
		RG8  , RG8S  , RG8UI , RG8I ,
		RG16 , RG16S , RG16UI, RG16I, RG16F,
		RG32UI, RG32I, RG32F ,

		//four component formats:
		RGBA8   , RGBA8S , RGBA8UI , RGBA8I ,
		RGBA16  , RGBA16S, RGBA16UI, RGBA16I, RGBA16F,
		RGBA32UI, RGBA32I, RGBA32F ,

		//depth formats:
		Depth16, Depth32, Depth32F, Depth24Stencil8
	};

	enum class WrapMode
	{
		Unknown= 0,
		Clamp,
		Repeat
	};

	enum class Filtration
	{
		Unknown= 0,
		Nearest,
		Linear,
		NearestMipmapNearest,
		NearestMipmapLinear,
		LinearMipmapNearest,
		LinearMipmapLinear,
	};

	r_Texture();
	r_Texture( r_Texture&& other );
	~r_Texture();

	r_Texture& operator=( const r_Texture& )= delete;
	r_Texture& operator=( r_Texture&& other );

	//create and bind texture
	void Create( PixelFormat format, unsigned int width, unsigned int height );
	void Create( PixelFormat format, unsigned int width, unsigned int height, const unsigned char* data );
	void Create( PixelFormat format, unsigned int width, unsigned int height, const float* data );
	void Destroy();

	//load texture data into GPU. Texture must be created and binded before.
	void SetData( decltype(nullptr) );
	void SetData( const float* data );
	void SetData( const unsigned char* data );

	//texture params modification methods. Texture must be created and binded before it.
	void SetWrapMode( WrapMode mode );
	void SetFiltration( Filtration filter_min, Filtration filter_mag );
	void BuildMips();

	//bind texture and set active texture unit.
	void Bind( unsigned int unit= 0 ) const;

	bool Created() const;
	unsigned int Width () const;
	unsigned int Height() const;
	bool IsDepthTexture() const;

private:
	static GLenum FormatToInternalFormat( PixelFormat format );
	static GLenum FormatToBaseFormat( PixelFormat format );
	static GLenum FiltrationToGLFiltration( Filtration filtration );
	static GLenum WrapModeToGLWrapMode( WrapMode mode );

private:
	GLuint tex_id_;

	PixelFormat format_;
	WrapMode wrap_mode_;
	Filtration filter_min_, filter_mag_;

	unsigned int size_x_, size_y_;

	static const GLuint c_texture_not_created_;
};
