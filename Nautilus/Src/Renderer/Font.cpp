#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _RENDERER_FONT_CPP_
    #define _RENDERER_FONT_CPP_

#include "Font.h"

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8

namespace Nt
{
    template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
    static Ref<Texture2D> CreateAndCacheAtlas(const String& fontName, float32 fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs, const msdf_atlas::FontGeometry& fontGeometry, uint32 width, uint32 height)
    {
        msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass          = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
		generator.setAttributes(attributes);
		generator.setThreadCount(8);
		generator.generate(glyphs.data(), (int)glyphs.size());

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();

        TextureProps props{};
        props.width        = bitmap.width;
        props.height       = bitmap.height;
        props.format       = ImageFormat::RGBA8;
        props.generateMips = false;

        Ref<Texture2D> texture = CreateRef<Texture2D>(props);
        texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
        return texture;
    }

    Font::Font(const String& path) :
        m_data(new MSDFData{})
    {
        msdfgen::FreetypeHandle* ftHandle = msdfgen::initializeFreetype();
        msdfgen::FontHandle* font         = msdfgen::loadFont(ftHandle, (const char*)path);
        if (!font)
        {
            NT_CORE_ERROR("Failed to load font: %s", path);
            return;
        }

        struct CharsetRange
        {
            uint32 begin, end;
        };

        static const CharsetRange charsetRanges[] =
        {
            { 0x0020, 0x00ff },
        };

        msdf_atlas::Charset charset;
        for (CharsetRange range : charsetRanges)
            for (uint32 c = range.begin; c <= range.end; ++c)
                charset.add(c);

        float64 fontScale    = 1.0;
        m_data->fontGeometry = msdf_atlas::FontGeometry(&m_data->glyphs);
        int32 glyphsLoaded   = m_data->fontGeometry.loadCharset(font, fontScale, charset);
        NT_CORE_INFO("Loaded %d glyphs from font (out of %d)", glyphsLoaded, charset.size());

        float64 emSize = 40.0;
        msdf_atlas::TightAtlasPacker atlasPacker;
        atlasPacker.setPixelRange(2.0);
		atlasPacker.setMiterLimit(1.0);
        atlasPacker.setOuterPixelPadding(msdf_atlas::Padding());
		atlasPacker.setScale(emSize);

        int32 remaining = atlasPacker.pack(m_data->glyphs.data(), (int32)m_data->glyphs.size());
        NT_ASSERT(remaining == 0, "Failed to pack glyphs into atlas");

        int32 width, height;
        atlasPacker.getDimensions(width, height);
        emSize = atlasPacker.getScale();

        uint64 coloringSeed    = 0;
        bool expensiveColoring = false;
        if (expensiveColoring)
        {
            msdf_atlas::Workload([&glyphs = m_data->glyphs, &coloringSeed](int i, int threadNo) -> bool
            {
				uint64 glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
				glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
				return true;
			}, m_data->glyphs.size()).finish(THREAD_COUNT);
        }
        else
        {
            uint64 glyphSeed = coloringSeed;
			for (msdf_atlas::GlyphGeometry& glyph : m_data->glyphs)
			{
				glyphSeed *= LCG_MULTIPLIER;
				glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
			}
        }

        m_atlasTexture = CreateAndCacheAtlas<uint8, float32, 3, msdf_atlas::msdfGenerator>("Test", (float32)emSize, m_data->glyphs, m_data->fontGeometry, width, height);

        msdfgen::destroyFont(font);
        msdfgen::deinitializeFreetype(ftHandle);
    }

    Font::~Font(void)
    {
        delete m_data;
    }

    const MSDFData* Font::GetMSDFData(void) const
    {
        return m_data;
    }

    Ref<Texture2D> Font::GetAtlasTexture(void) const
    {
        return m_atlasTexture;
    }

    Ref<Texture2D> Font::GetDefault(void)
    {
        static Ref<Texture2D> defaultFont;
        if (!defaultFont)
            defaultFont = CreateRef<Texture2D>("Assets/Fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf");
        return defaultFont;
    }
} // namespace Nt

#endif // _RENDERER_FONT_CPP_
