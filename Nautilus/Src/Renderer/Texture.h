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

#pragma once

#ifndef _RENDERER_TEXTURE_H_
    #define _RENDERER_TEXTURE_H_

#include "Core/String.h"
#include "Framebuffer.h"
#include "Math/Vector.h"

namespace Nt
{
    using TextureFilter = FramebufferFilterFormat;
    using TextureWrap   = FramebufferWrapFormat;

    enum class ImageFormat
    {
        None = 0,
        R8,
        RG8,
        RGB8,
        RGBA8,
        RGBA32F,
    };

    struct NT_API TextureSampler
    {
        TextureFilter filter = TextureFilter::Linear;
        TextureWrap wrap     = TextureWrap::Repeat;

        NT_STRUCT_DEFAULTS(TextureSampler)
        TextureSampler(void) = default;
    };

    struct NT_API TextureProps
    {
        uint32 width           = 1,
               height          = 1;
        ImageFormat format     = ImageFormat::RGBA8;
        bool generateMips      = true;
        TextureSampler sampler = {};

        NT_STRUCT_DEFAULTS(TextureProps)
        TextureProps(void) = default;
    };

    class NT_API Texture2D
    {
    public:
        NT_CLASS_DEFAULTS(Texture2D)
        Texture2D(const TextureProps& props);
        Texture2D(const String& path, const TextureSampler& sampler={});
        ~Texture2D(void);

        void Bind(uint32 slot=0);

        void SetData(void* data, uint32 size);

        bool IsLoaded(void) const;
        String GetPath(void) const;
        uint32 GetWidth(void) const;
        uint32 GetHeight(void) const;

        uint32 GetRenderId(void) const;

    private:
        uint32 m_id;
        String m_path;
        bool m_isLoaded;
        uint32 m_width, m_height;
        GLenum m_internalFormat, m_dataFormat;
    };

    class NT_API SubTexture2D
    {
    public:
        NT_CLASS_DEFAULTS(SubTexture2D)
        SubTexture2D(const Ref<Texture2D>& texture, const Vector2& min=Vector2(0.0f), const Vector2& max=Vector2(1.0f));

        Ref<Texture2D> GetTexture(void) const;
        Vector2* GetTexCoords(void);

    private:
        Ref<Texture2D> m_texture;
        Vector2 m_texCoords[4];
    };

    using TileSet = std::vector<Ref<SubTexture2D>>;

    Ref<SubTexture2D> CreateSubTexture(const Ref<Texture2D>& texture, const Vector2& coords, const Vector2& size=Vector2(1.0f));
    TileSet CreateTileSet(const Ref<Texture2D>& texture, uint32 cols, uint32 rows);
} // namespace Nt

#endif // _RENDERER_TEXTURE_H_
