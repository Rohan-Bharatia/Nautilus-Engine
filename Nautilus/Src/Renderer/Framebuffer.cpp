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

#ifndef _RENDERER_FRAMEBUFFER_CPP_
    #define _RENDERER_FRAMEBUFFER_CPP_

#include "Framebuffer.h"

namespace Nt
{
    static GLenum TextureTarget(bool multisampled)
    {
        return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    static void CreateTextures(bool multisampled, uint32* ids, uint32 count)
    {
        glCreateTextures(TextureTarget(multisampled), count, ids);
    }

    static void BindTexture(bool multisampled, uint32 id)
    {
        glBindTexture(TextureTarget(multisampled), id);
    }

    static void AttachColorTexture(uint32 id, int32 samples, GLenum internalFormat, GLenum format, uint32 width, uint32 height, uint32 index, GLenum filter, GLenum wrap)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else
        {
            GLenum pixelType = GL_UNSIGNED_BYTE;
            if (internalFormat == GL_R32I)
                pixelType = GL_INT;
            else if (internalFormat == GL_R32UI)
                pixelType = GL_UNSIGNED_INT;
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, pixelType, nullptr);

            GLenum minFilter = filter;
            GLenum magFilter = filter;

            if (format == GL_RED_INTEGER || format == GL_RGBA_INTEGER || format == GL_RGB_INTEGER)
                minFilter = magFilter = GL_NEAREST;

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
    }

    static void AttachDepthTexture(uint32 id, int32 samples, GLenum internalFormat, GLenum attachmentType, uint32 width, uint32 height, GLenum filter, GLenum wrap)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
    }

    static GLenum TextureFormatToGLInternalFormat(FramebufferTextureFormat format)
    {
        switch (format)
        {
            case FramebufferTextureFormat::RGBA8:           return GL_RGBA8;
            case FramebufferTextureFormat::RedInt32:        return GL_R32I;
            case FramebufferTextureFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
            default:                                        return GL_RGBA8;
        }
    }

    static GLenum TextureFormatToGLPixelFormat(FramebufferTextureFormat format)
    {
        switch (format)
        {
            case FramebufferTextureFormat::RGBA8:           return GL_RGBA;
            case FramebufferTextureFormat::RedInt32:        return GL_RED_INTEGER;
            case FramebufferTextureFormat::Depth24Stencil8: return GL_DEPTH_STENCIL;
            default:                                        return GL_RGBA;
        }
    }

    static GLenum TextureFilterFormatToGL(FramebufferFilterFormat filter)
    {
        switch (filter)
        {
            case FramebufferFilterFormat::Nearest: return GL_NEAREST;
            case FramebufferFilterFormat::Linear:  return GL_LINEAR;
            default:                                return GL_NEAREST;
        }
    }

    static GLenum TextureWrapFormatToGL(FramebufferWrapFormat wrap)
    {
        switch (wrap)
        {
            case FramebufferWrapFormat::Repeat:         return GL_REPEAT;
            case FramebufferWrapFormat::ClampToEdge:    return GL_CLAMP_TO_EDGE;
            case FramebufferWrapFormat::ClampToBorder:  return GL_CLAMP_TO_BORDER;
            case FramebufferWrapFormat::MirroredRepeat: return GL_MIRRORED_REPEAT;
            default:                                     return GL_CLAMP_TO_EDGE;
        }
    }

    Framebuffer::Framebuffer(const FramebufferProps& props) :
        m_props(props)
    {
        for (auto prop : m_props.attachments.attachments)
        {
            if (prop.texture != FramebufferTextureFormat::None && prop.texture != FramebufferTextureFormat::Depth24Stencil8)
                m_colorAttachmentsProps.push_back(prop);
            else if (prop.texture == FramebufferTextureFormat::Depth24Stencil8)
                m_depthAttachmentProps = prop;
            else
                NT_ASSERT(false, "Framebuffer attachment type not supported!");
        }

        Invalidate();
    }

    Framebuffer::~Framebuffer(void)
    {
        glDeleteFramebuffers(1, &m_id);
        glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
        glDeleteTextures(1, &m_depthAttachment);
    }

    void Framebuffer::Bind(void)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glViewport(0, 0, m_props.width, m_props.height);
    }

    void Framebuffer::Unbind(void)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Resize(uint32 width, uint32 height)
    {
        if (m_props.width == width || m_props.height == height || width > NT_MAX_FRAMEBUFFER_SIZE || height > NT_MAX_FRAMEBUFFER_SIZE)
            return;

        m_props.width  = width;
        m_props.height = height;
        Invalidate();
    }

    int32 Framebuffer::ReadPixel(uint32 attachmentIndex, int32 x, int32 y)
    {
        NT_ASSERT(attachmentIndex < m_colorAttachmentsProps.size(), "Index out of range!");
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int32 pixelData = 0;
        GLenum pf       = TextureFormatToGLPixelFormat(m_colorAttachmentsProps[attachmentIndex].texture);
        if (pf == GL_RED_INTEGER)
            glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        else
            glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
        return pixelData;
    }

    void Framebuffer::ClearAttachment(uint32 attachmentIndex, int32 value)
    {
        NT_ASSERT(attachmentIndex < m_colorAttachmentsProps.size(), "Index out of range!");
        GLenum pf   = TextureFormatToGLPixelFormat(m_colorAttachmentsProps[attachmentIndex].texture);
        GLenum type = GL_UNSIGNED_BYTE;

        if (pf == GL_RED_INTEGER)
            type = GL_INT;
        else if (pf == GL_RGBA)
            type = GL_UNSIGNED_BYTE;
        else
        {
            pf   = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
        }

        glClearTexImage(m_colorAttachments[attachmentIndex], 0, pf, type, &value);
    }

    uint32 Framebuffer::GetColorAttachmentRenderId(uint32 index) const
    {
        NT_ASSERT(index < m_colorAttachments.size(), "Index out of range!");
        return m_colorAttachments[index];
    }

    uint32 Framebuffer::GetDepthAttachmentRenderId(void) const
    {
        return m_depthAttachment;
    }

    const FramebufferProps& Framebuffer::GetProps(void) const
    {
        return m_props;
    }

    uint32 Framebuffer::GetRenderId(void) const
    {
        return m_id;
    }

    void Framebuffer::Invalidate(void)
    {
        if (m_id)
        {
            glDeleteFramebuffers(1, &m_id);
            glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
            glDeleteTextures(1, &m_depthAttachment);

            m_colorAttachments.clear();
            m_depthAttachment = 0;
            m_id              = 0;
        }

        glCreateFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        bool multisampled = m_props.samples > 1;
        if (!m_colorAttachmentsProps.empty())
        {
            m_colorAttachments.resize(m_colorAttachmentsProps.size());
            CreateTextures(multisampled, m_colorAttachments.data(), m_colorAttachments.size());

            for (int32 i = 0; i < m_colorAttachments.size(); ++i)
            {
                BindTexture(multisampled, m_colorAttachments[i]);

                FramebufferTextureFormat format = m_colorAttachmentsProps[i].texture;
                GLenum internalFormat           = TextureFormatToGLInternalFormat(format);
                GLenum pixelFormat              = TextureFormatToGLPixelFormat(format);
                GLenum filter                   = TextureFilterFormatToGL(m_colorAttachmentsProps[i].filter);
                GLenum wrap                     = TextureWrapFormatToGL(m_colorAttachmentsProps[i].wrap);

                if (format == FramebufferTextureFormat::RGBA8 || format == FramebufferTextureFormat::RedInt32)
                    AttachColorTexture(m_colorAttachments[i], m_props.samples, internalFormat, pixelFormat, m_props.width, m_props.height, i, filter, wrap);
            }
        }

        if (m_depthAttachmentProps.texture == FramebufferTextureFormat::Depth24Stencil8)
        {
            CreateTextures(multisampled, &m_depthAttachment, 1);
            BindTexture(multisampled, m_depthAttachment);

            GLenum internalFormat = TextureFormatToGLInternalFormat(m_depthAttachmentProps.texture);
            GLenum filter         = TextureFilterFormatToGL(m_depthAttachmentProps.filter);
            GLenum wrap           = TextureWrapFormatToGL(m_depthAttachmentProps.wrap);

            AttachDepthTexture(m_depthAttachment, m_props.samples, internalFormat, GL_DEPTH_STENCIL_ATTACHMENT, m_props.width, m_props.height, filter, wrap);
        }

        if (m_colorAttachments.size() > 1)
        {
            NT_ASSERT(m_colorAttachments.size() <= 32, "Framebuffer: Maximum of 4 color attachments!");

            std::vector<GLenum> buffers(m_colorAttachments.size());
            for (uint32 i = 0; i < m_colorAttachments.size(); ++i)
                buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
            glDrawBuffers(buffers.size(), buffers.data());
        }
        else if (m_colorAttachments.size() == 1)
        {
            GLenum buffer = GL_COLOR_ATTACHMENT0;
            glDrawBuffers(1, &buffer);
        }
        else
            glDrawBuffer(GL_NONE);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        NT_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete (%d)!", status);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
} // namespace Nt

#endif // _RENDERER_FRAMEBUFFER_CPP_
