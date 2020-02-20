#pragma once
#include <map>
#include <string>
#include <memory>
#include "../se_sdk3/mp_sdk_gui2.h"
#include "../shared/ImageMetadata.h"
/* 
#include "../shared/FontCache.h"
*/

struct TypefaceData
{
	TypefaceData(GmpiDrawing_API::IMpFactory* pfactory, std::string pskinId, std::string pstyle, GmpiDrawing::TextFormat ptextFormat, const FontMetadata* pmetadata) :
		factory(pfactory)
		, style(pstyle)
		, skinId(pskinId)
		, textFormat(ptextFormat)
	{
		legacy_metadata = std::make_unique<FontMetadata>(*pmetadata); // takes a copy.
	}

  	GmpiDrawing_API::IMpFactory* factory; // differentiates between GDI and D2D bitmaps.
	std::string skinId;
	std::string style;
	GmpiDrawing::TextFormat textFormat;

	std::unique_ptr<FontMetadata> legacy_metadata; // held by pointer so not invalidated when this object copied/moved by vector.
};

class FontCache
{
	friend class FontCacheClient;
	FontCache();

	std::vector<TypefaceData> fonts_;
	std::vector<SkinMetadata> skins_;

	int clientCount_;
protected:
	
	// Need to keep track of clients so imagecache can be cleared BEFORE program exit (else WPF crashes).
	void AddClient() {
		++clientCount_;
	}
	void RemoveClient();

public:
	static FontCache* instance();

	bool TextFormatExists(gmpi::IMpUserInterfaceHost2* host, gmpi_gui::IMpGraphicsHost* guiHost, std::string style);

	GmpiDrawing::TextFormat_readonly GetTextFormat(gmpi::IMpUserInterfaceHost2* host, gmpi_gui::IMpGraphicsHost* guiHost, std::string style, FontMetadata** metadata = 0);
	GmpiDrawing::TextFormat AddCustomTextFormat(gmpi::IMpUserInterfaceHost2* host, gmpi_gui::IMpGraphicsHost* guiHost, std::string style, const FontMetadata* fontmetadata);
};


class FontCacheClient
{
public:
	FontCacheClient()
	{
		FontCache::instance()->AddClient();
	}
	virtual ~FontCacheClient()
	{
		FontCache::instance()->RemoveClient();
	}

	bool TextFormatExists(gmpi::IMpUserInterfaceHost2 * host, gmpi_gui::IMpGraphicsHost * guiHost, std::string style)
	{
		return FontCache::instance()->TextFormatExists(host, guiHost, style);
	}

	GmpiDrawing::TextFormat_readonly GetTextFormat(gmpi::IMpUserInterfaceHost2* host, gmpi_gui::IMpGraphicsHost* guiHost, std::string style, FontMetadata** metadata = 0)
	{
		return FontCache::instance()->GetTextFormat(host, guiHost, style, metadata);
	}

	GmpiDrawing::TextFormat AddCustomTextFormat(gmpi::IMpUserInterfaceHost2* host, gmpi_gui::IMpGraphicsHost* guiHost, std::string style, const FontMetadata* fontmetadata)
	{
		return FontCache::instance()->AddCustomTextFormat(host, guiHost, style, fontmetadata);
	}

	GmpiDrawing::TextFormat_readonly GetTextFormat(std::string style);
	const FontMetadata* GetFontMetatdata(std::string style);
};
