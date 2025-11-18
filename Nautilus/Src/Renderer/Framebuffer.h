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

#ifndef _RENDERER_FRAMEBUFFER_H_
    #define _RENDERER_FRAMEBUFFER_H_

#include "PCH.h"

#define NT_MAX_FRAMEBUFFER_SIZE 8192

namespace Nt
{
    enum class FramebufferTextureFormat
    {
        None = 0,
        RGBA8,
        RedInt32,
        Depth24Stencil8,
    };

    enum class FramebufferFilterFormat
    {
        None = 0,
        Nearest,
        Linear,
    };

    enum class FramebufferWrapFormat
    {
        None = 0,
        Repeat,
        ClampToEdge,
        ClampToBorder,
        MirroredRepeat,
    };

    struct NT_API FramebufferTextureProps
    {
        FramebufferTextureFormat texture = FramebufferTextureFormat::None;
        FramebufferFilterFormat filter   = FramebufferFilterFormat::Linear;
        FramebufferWrapFormat wrap       = FramebufferWrapFormat::ClampToEdge;

        NT_STRUCT_DEFAULTS(FramebufferTextureProps)
        FramebufferTextureProps(void) = default;
    };

    struct NT_API FramebufferAttachmentProps
    {
        std::vector<FramebufferTextureProps> attachments;

        NT_STRUCT_DEFAULTS(FramebufferAttachmentProps)
        FramebufferAttachmentProps(void) = default;
        FramebufferAttachmentProps(std::initializer_list<FramebufferTextureProps> textures);

        inline void Push(FramebufferTextureProps texture)
        {
            attachments.push_back(texture);
        }
    };

    struct NT_API FramebufferProps
    {
        uint32 width         = 0,
               height        = 0;
        FramebufferAttachmentProps attachments;
        uint32 samples       = 1;
        bool swapChainTarget = false;

        NT_STRUCT_DEFAULTS(FramebufferProps)
        FramebufferProps(void) = default;
    };

    class NT_API Framebuffer
    {
    public:
        NT_CLASS_DEFAULTS(Framebuffer)
        Framebuffer(const FramebufferProps& props);
        ~Framebuffer(void);

        void Bind(void);
        void Unbind(void);

        void Resize(uint32 width, uint32 height);
        int32 ReadPixel(uint32 attachmentIndex, int32 x, int32 y);

        void ClearAttachment(uint32 attachmentIndex, int32 value);
        uint32 GetColorAttachmentRenderId(uint32 index=0) const;
        uint32 GetDepthAttachmentRenderId(void) const;

        const FramebufferProps& GetProps(void) const;

        uint32 GetRenderId(void) const;

    private:
        void Invalidate(void);

        inline static uint32 s_maxFramebufferSize = 8192;

        uint32 m_id;
        FramebufferProps m_props;
        std::vector<FramebufferTextureProps> m_colorAttachmentsProps;
        FramebufferTextureProps m_depthAttachmentProps;
        std::vector<uint32> m_colorAttachments;
        uint32 m_depthAttachment;
    };
} // namespace Nt

#endif // _RENDERER_FRAMEBUFFER_H_
