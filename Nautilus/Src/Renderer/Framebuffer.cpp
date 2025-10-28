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

    static void AttachColorTexture(uint32 id, int32 samples, GLenum internalFormat, GLenum format, uint32 width, uint32 height, int32 index, GLenum filter, GLenum wrap)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
    }

    static void AttachDepthTexture(uint32 id, int32 samples, GLenum format, GLenum attachmentType, uint32 width, uint32 height, GLenum filter, GLenum wrap)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
        else
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
    }

    static GLenum FramebufferTextureFormatToGL(FramebufferTextureFormat texture)
    {
        switch (texture)
        {
            case FramebufferTextureFormat::RGBA8:           return GL_RGBA8;
            case FramebufferTextureFormat::RedInt32:        return GL_RED_INTEGER;
            case FramebufferTextureFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
            default:                                        return 0;
        }
    }

    static GLenum FramebufferFilterFormatToGL(FramebufferFilterFormat filter)
    {
        switch (filter)
        {
            case FramebufferFilterFormat::Nearest: return GL_NEAREST;
            case FramebufferFilterFormat::Linear:  return GL_LINEAR;
            default:                                return 0;
        }
    }

    static GLenum FramebufferWrapFormatToGL(FramebufferWrapFormat wrap)
    {
        switch (wrap)
        {
            case FramebufferWrapFormat::Repeat:         return GL_REPEAT;
            case FramebufferWrapFormat::ClampToEdge:    return GL_CLAMP_TO_EDGE;
            case FramebufferWrapFormat::ClampToBorder:  return GL_CLAMP_TO_BORDER;
            case FramebufferWrapFormat::MirroredRepeat: return GL_MIRRORED_REPEAT;
            default:                                     return 0;
        }
    }

    Framebuffer::Framebuffer(const FramebufferProps& props) :
        m_props(props)
    {
        for (auto p : m_props.attachments.attachments)
        {
            if (p.texture == FramebufferTextureFormat::Depth24Stencil8)
                m_colorAttachmentsProps.emplace_back(p);
            else
                m_depthAttachmentProps = p;
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
        if (width == 0 || height == 0 || m_props.width == width || m_props.height == height)
            return;

        m_props.width  = width;
        m_props.height = height;
        Invalidate();
    }

    int32 Framebuffer::ReadPixel(uint32 attachmentIndex, int32 x, int32 y)
    {
        NT_ASSERT(attachmentIndex < m_colorAttachments.size(), "Index out of range");
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int32 pixelData;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        return pixelData;
    }

    void Framebuffer::ClearAttachment(uint32 attachmentIndex, int32 value)
    {
        NT_ASSERT(attachmentIndex < m_colorAttachments.size(), "Index out of range");
        auto& spec = m_colorAttachmentsProps[attachmentIndex];
        glClearTexImage(m_colorAttachments[attachmentIndex], 0, FramebufferTextureFormatToGL(spec.texture), GL_INT, &value);
    }

    uint32 Framebuffer::GetColorAttachmentRenderId(uint32 index) const
    {
        NT_ASSERT(index < m_colorAttachments.size(), "Index out of range");
        return m_colorAttachments[index];
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
        }

        glCreateFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        bool multisampled = m_props.samples > 1;

        if (m_colorAttachmentsProps.size() > 0)
        {
            m_colorAttachments.resize(m_colorAttachmentsProps.size());
            CreateTextures(multisampled, m_colorAttachments.data(), m_colorAttachments.size());

            for (uint32 i = 0; i < m_colorAttachments.size(); ++i)
            {
                BindTexture(multisampled, m_colorAttachments[i]);
                switch (m_colorAttachmentsProps[i].texture)
                {
                    case FramebufferTextureFormat::RGBA8:
                        AttachColorTexture(m_colorAttachments[i], m_props.samples, GL_RGBA8, GL_RGBA, m_props.width, m_props.height, i, FramebufferFilterFormatToGL(m_colorAttachmentsProps[i].filter), FramebufferWrapFormatToGL(m_colorAttachmentsProps[i].wrap));
                        break;
                    case FramebufferTextureFormat::RedInt32:
                        AttachColorTexture(m_colorAttachments[i], m_props.samples, GL_R32I, GL_RED_INTEGER, m_props.width, m_props.height, i, FramebufferFilterFormatToGL(m_colorAttachmentsProps[i].filter), FramebufferWrapFormatToGL(m_colorAttachmentsProps[i].wrap));
                        break;
                    default:
                        break;
                }
            }
        }

        if (m_depthAttachmentProps.texture != FramebufferTextureFormat::None)
        {
            CreateTextures(multisampled, &m_depthAttachment, 1);
            BindTexture(multisampled, m_depthAttachment);
            switch (m_depthAttachmentProps.texture)
            {
                case FramebufferTextureFormat::Depth24Stencil8:
                    AttachDepthTexture(m_depthAttachment, m_props.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_props.width, m_props.height, FramebufferFilterFormatToGL(m_depthAttachmentProps.filter), FramebufferWrapFormatToGL(m_depthAttachmentProps.wrap));
                    break;
                default:
                    break;
            }
        }

        if (m_colorAttachments.size() > 1)
        {
            NT_ASSERT(m_colorAttachments.size() <= 32, "Too many color attachments");
            GLenum buffers[32] =
            {
                GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
                GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7,
                GL_COLOR_ATTACHMENT8, GL_COLOR_ATTACHMENT9, GL_COLOR_ATTACHMENT10, GL_COLOR_ATTACHMENT11,
                GL_COLOR_ATTACHMENT12, GL_COLOR_ATTACHMENT13, GL_COLOR_ATTACHMENT14, GL_COLOR_ATTACHMENT15,
                GL_COLOR_ATTACHMENT16, GL_COLOR_ATTACHMENT17, GL_COLOR_ATTACHMENT18, GL_COLOR_ATTACHMENT19,
                GL_COLOR_ATTACHMENT20, GL_COLOR_ATTACHMENT21, GL_COLOR_ATTACHMENT22, GL_COLOR_ATTACHMENT23,
                GL_COLOR_ATTACHMENT24, GL_COLOR_ATTACHMENT25, GL_COLOR_ATTACHMENT26, GL_COLOR_ATTACHMENT27,
                GL_COLOR_ATTACHMENT28, GL_COLOR_ATTACHMENT29, GL_COLOR_ATTACHMENT30, GL_COLOR_ATTACHMENT31,
            };
            glDrawBuffers(m_colorAttachments.size(), buffers);
        }
        else if (m_colorAttachments.empty())
            glDrawBuffer(GL_NONE);

        NT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
} // namespace Nt

#endif // _RENDERER_FRAMEBUFFER_CPP_
