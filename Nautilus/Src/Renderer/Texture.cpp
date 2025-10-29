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

#ifndef _RENDERER_TEXTURE_CPP_
    #define _RENDERER_TEXTURE_CPP_

#include "Texture.h"

namespace Nt
{
    static GLenum ImageFormatToGLDataFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::R8:      return GL_RED;
            case ImageFormat::RG8:     return GL_RG;
            case ImageFormat::RGB8:    return GL_RGB;
            case ImageFormat::RGBA8:   return GL_RGBA;
            case ImageFormat::RGBA32F: return GL_RGBA;
            default:                   return 0;
        }
    }

    static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::R8:      return GL_R8;
            case ImageFormat::RG8:     return GL_RG8;
            case ImageFormat::RGB8:    return GL_RGB8;
            case ImageFormat::RGBA8:   return GL_RGBA8;
            case ImageFormat::RGBA32F: return GL_RGBA32F;
            default:                   return 0;
        }
    }

    static GLenum TextureFilterFormatToGL(TextureFilter filter)
    {
        switch (filter)
        {
            case TextureFilter::Nearest: return GL_NEAREST;
            case TextureFilter::Linear:  return GL_LINEAR;
            default:                     return 0;
        }
    }

    static GLenum TextureWrapFormatToGL(TextureWrap wrap)
    {
        switch (wrap)
        {
            case TextureWrap::Repeat:         return GL_REPEAT;
            case TextureWrap::ClampToEdge:    return GL_CLAMP_TO_EDGE;
            case TextureWrap::ClampToBorder:  return GL_CLAMP_TO_BORDER;
            case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
            default:                          return 0;
        }
    }

    Texture2D::Texture2D(const TextureProps& props) :
        m_isLoaded(false), m_width(props.width), m_height(props.height)
    {
        m_internalFormat = ImageFormatToGLInternalFormat(props.format);
        m_dataFormat     = ImageFormatToGLDataFormat(props.format);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, TextureFilterFormatToGL(props.sampler.filter));
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, TextureFilterFormatToGL(props.sampler.filter));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, TextureWrapFormatToGL(props.sampler.wrap));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, TextureWrapFormatToGL(props.sampler.wrap));
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, TextureWrapFormatToGL(props.sampler.wrap));
    }

    Texture2D::Texture2D(const String& path, const TextureSampler& sampler) :
        m_path(path), m_isLoaded(false)
    {
        int32 width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load((const char*)path, &width, &height, &channels, 0);

        if (data)
        {
            m_isLoaded = true;
            m_width    = width;
            m_height   = height;

            switch (channels)
            {
                case 4:
                    m_internalFormat = GL_RGBA8;
                    m_dataFormat     = GL_RGBA;
                    break;
                case 3:
                    m_internalFormat = GL_RGB8;
                    m_dataFormat     = GL_RGB;
                    break;
                case 2:
                    m_internalFormat = GL_RG8;
                    m_dataFormat     = GL_RG;
                    break;
                case 1:
                    m_internalFormat = GL_R8;
                    m_dataFormat     = GL_RED;
                    break;
                default:
                    break;
            }

            glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
            glTextureStorage2D(m_id, 1, m_internalFormat, m_width, m_height);

            glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, TextureFilterFormatToGL(sampler.filter));
            glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, TextureWrapFormatToGL(sampler.wrap));
            glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, TextureWrapFormatToGL(sampler.wrap));
            glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, TextureWrapFormatToGL(sampler.wrap));

            glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }

    Texture2D::~Texture2D(void)
    {
        glDeleteTextures(1, &m_id);
    }

    void Texture2D::Bind(uint32 slot)
    {
        glBindTextureUnit(slot, m_id);
    }

    void Texture2D::SetData(void* data, uint32 size)
    {
        uint32 bpp = m_dataFormat == GL_RGBA ? 4 : 3;
        NT_ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    }

    bool Texture2D::IsLoaded(void) const
    {
        return m_isLoaded;
    }

    String Texture2D::GetPath(void) const
    {
        return m_path;
    }

    uint32 Texture2D::GetWidth(void) const
    {
        return m_width;
    }

    uint32 Texture2D::GetHeight(void) const
    {
        return m_height;
    }

    uint32 Texture2D::GetRenderId(void) const
    {
        return m_id;
    }
} // namespace Nt

#endif // _RENDERER_TEXTURE_CPP_
