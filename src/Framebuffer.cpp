//
// Created by Tonz on 19.10.2023.
//

#include "Framebuffer.h"
#include "Application.h"

Framebuffer::Framebuffer() {
    glm::vec<2,int> screenDimensions = Application::getInstance().getWindow().getDimensions();
    this->target = std::make_unique<Texture>(screenDimensions);

    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target->getId(), 0);

    glGenRenderbuffers(1, &this->rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenDimensions.x, screenDimensions.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboId);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FBO created successfully" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Application::getInstance().getWindow().attach(this);
}

Framebuffer::~Framebuffer() {
    glDeleteRenderbuffers(1,&this->rboId);
    glDeleteFramebuffers(1,&this->id);
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void Framebuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const uint32_t &Framebuffer::getTargetId() const {
    return this->target->getId();
}

void Framebuffer::update(int width, int height) {
    glm::vec<2,int> screenDimensions = Application::getInstance().getWindow().getDimensions();
    auto newTexture = std::make_unique<Texture>(screenDimensions);
    std::swap(this->target,newTexture);

    this->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target->getId(), 0);

    glDeleteRenderbuffers(1,&this->rboId);
    glGenRenderbuffers(1, &this->rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenDimensions.x, screenDimensions.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboId);
    this->unbind();
}