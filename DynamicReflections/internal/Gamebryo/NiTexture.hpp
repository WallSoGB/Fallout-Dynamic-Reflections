#pragma once

#include "NiObjectNET.hpp"
#include "NiPixelFormat.hpp"

class NiDX9TextureData;

NiSmartPointer(NiTexture);

class NiTexture : public NiObjectNET {
public:
	NiTexture();
	~NiTexture();

	virtual void Unk_23();
	virtual void Unk_24();
	virtual UInt32 GetWidth();
	virtual UInt32 GetHeight();
	virtual NiFixedString* GetPath();
	virtual UInt32 GetSize();

	class FormatPrefs {
	public:
		FormatPrefs() : m_ePixelLayout(TRUE_COLOR_32), m_eAlphaFmt(SMOOTH), m_eMipMapped(YES) {};
		~FormatPrefs() {};
		enum PixelLayout
		{
			PALETTIZED_8 = 0x0,
			HIGH_COLOR_16 = 0x1,
			TRUE_COLOR_32 = 0x2,
			COMPRESSED = 0x3,
			BUMPMAP = 0x4,
			PALETTIZED_4 = 0x5,
			PIX_DEFAULT = 0x6,
			SINGLE_COLOR_8 = 0x7,
			SINGLE_COLOR_16 = 0x8,
			SINGLE_COLOR_32 = 0x9,
			DOUBLE_COLOR_32 = 0xA,
			DOUBLE_COLOR_64 = 0xB,
			FLOAT_COLOR_32 = 0xC,
			FLOAT_COLOR_64 = 0xD,
			FLOAT_COLOR_128 = 0xE,
		};

		enum AlphaFormat
		{
			BINARY = 0x1,
			SMOOTH = 0x2,
			ALPHA_DEFAULT = 0x3,
		};

		enum MipFlag
		{
			NO = 0x0,
			YES = 0x1,
			MIP_DEFAULT = 0x2,
		};

		FormatPrefs(const PixelLayout& m_ePixelLayout, const AlphaFormat& m_eAlphaFmt, const MipFlag& m_eMipMapped)
			: m_ePixelLayout(m_ePixelLayout), m_eAlphaFmt(m_eAlphaFmt), m_eMipMapped(m_eMipMapped)
		{
		}

		NiTexture::FormatPrefs::PixelLayout m_ePixelLayout;
		NiTexture::FormatPrefs::AlphaFormat m_eAlphaFmt;
		NiTexture::FormatPrefs::MipFlag m_eMipMapped;


	};

	class RendererData : public NiObject
	{
	public:
		virtual UInt32	GetWidth(void);
		virtual UInt32	GetHeight(void);
		virtual void	Unk_03(void);

		NiTexture* m_pkTexture;
		UInt32 m_uiWidth;
		UInt32 m_uiHeight;
		NiPixelFormat m_kPixelFormat;
		char unk58;
		char unk59;
		char unk5A;
		char bState;
		int unk5C;
	};

	FormatPrefs m_kFormatPrefs;
	RendererData* m_pkRendererData;
	NiTexture* m_pkPrev;
	NiTexture* m_pkNext;

	NiDX9TextureData* GetDX9RendererData() {
		return reinterpret_cast<NiDX9TextureData*>(m_pkRendererData);
	};
};