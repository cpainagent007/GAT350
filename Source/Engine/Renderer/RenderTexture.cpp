#include "RenderTexture.h"

namespace neu {
    RenderTexture::~RenderTexture() {
        if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
        if (m_depthBuffer) glDeleteRenderbuffers(1, &m_depthBuffer);
    }

    bool RenderTexture::Load(const std::string& filename) {
        LOG_WARNING("RenderTexture cannot load from file: {}", filename);
        return false;
    }

    bool RenderTexture::Create(int width, int height, bool depth) {
        m_size = glm::ivec2{ width, height };

        // framebuffer

        // color texture
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // depth (optional)
        if (depth) {
            //
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            LOG_WARNING("Error creating framebuffer");
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return true;
    }

    void RenderTexture::BindFramebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void RenderTexture::UnbindFramebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}