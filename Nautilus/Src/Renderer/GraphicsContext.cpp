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

#ifndef _RENDERER_GRAPHICS_CONTEXT_CPP_
    #define _RENDERER_GRAPHICS_CONTEXT_CPP_

#include "GraphicsContext.h"

namespace Nt
{
    GraphicsContext::GraphicsContext(Window* window, uint32 preset) :
        m_window(window), m_native((SDL_Window*)window->GetNativeWindow())
    {
    #ifdef NT_DEBUG
        m_device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB, true, nullptr);
    #else // (NOT) NT_DEBUG
        m_device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB, false, nullptr);
    #endif // NT_DEBUG
        if (!m_device)
        {
            NT_CORE_ERROR("SDL_CreateGPUDevice failed: %s!", SDL_GetError());
            return;
        }

        if (!SDL_ClaimWindowForGPUDevice(m_device, m_native))
        {
            NT_CORE_ERROR("SDL_ClaimWindowForGPUDevice failed: %s!", SDL_GetError());
            return;
        }

        /* SDL_GPUGraphicsPipelineCreateInfo pipelineInfo{};
        // ...

        m_pipeline = SDL_CreateGPUGraphicsPipeline(m_device, &pipelineInfo);
        if (!m_pipeline)
            NT_CORE_ERROR("SDL_CreateGPUGraphicsPipeline failed: %s!", SDL_GetError()); */
    }

    GraphicsContext::~GraphicsContext(void)
    {
        if (m_device)
        {
            SDL_ReleaseWindowFromGPUDevice(m_device, m_native);
            SDL_DestroyGPUDevice(m_device);
        }
    }

    void GraphicsContext::SwapBuffers(void) const
    {
        SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(m_device);
        if (!cmdbuf)
        {
            NT_CORE_ERROR("SDL_AcquireGPUCommandBuffer failed: %s!", SDL_GetError());
            return;
        }

        SDL_GPUTexture* swapchainTexture;
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, m_native, &swapchainTexture, nullptr, nullptr))
        {
            NT_CORE_ERROR("SDL_WaitAndAcquireGPUSwapchainTexture failed: %s!", SDL_GetError());
            return;
        }

        if (swapchainTexture)
        {
            SDL_GPUColorTargetInfo colorInfo{};
            colorInfo.texture     = swapchainTexture;
            colorInfo.clear_color = { 11 / 255.0f, 15 / 255.0f, 142 / 255.0f, 1.0f };
            colorInfo.load_op     = SDL_GPU_LOADOP_CLEAR;
            colorInfo.store_op    = SDL_GPU_STOREOP_STORE;

            SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorInfo, 1, nullptr);
            SDL_BindGPUGraphicsPipeline(renderPass, m_pipeline);

            SDL_GPUViewport viewport{ 0, 0, (float32)m_window->GetWidth(), (float32)m_window->GetHeight(), 0.01f, 1000.0f };
            SDL_Rect scissor{ 0, 0, (int32)m_window->GetWidth(), (int32)m_window->GetHeight() };

            SDL_SetGPUViewport(renderPass, &viewport);
            SDL_SetGPUScissor(renderPass, &scissor);

            SDL_EndGPURenderPass(renderPass);
        }

        SDL_SubmitGPUCommandBuffer(cmdbuf);
    }

    void GraphicsContext::SetVSync(bool enabled) const
    {
        SDL_SetGPUAllowedFramesInFlight(m_device, enabled ? 1 : 0);
    }
} // namespace Nt

#endif // _RENDERER_GRAPHICS_CONTEXT_CPP_
