//
// Created by Tonz on 19.10.2023.
//

#include "Framebuffer.h"
#include "Application.h"

Framebuffer::Framebuffer() {
    this->target = std::make_unique<Texture>(Application::getInstance().getWindow().getDimensions());

    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target->getId(), 0);

    glGenRenderbuffers(1, &this->rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboId);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FBO created successfully" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteRenderbuffers(1,&this->rboId);
    glDeleteFramebuffers(1,&this->id);
}