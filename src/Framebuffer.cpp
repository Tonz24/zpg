//
// Created by Tonz on 19.10.2023.
//

#include "Framebuffer.h"
#include "Application.h"

Framebuffer::Framebuffer(int mipLevels) : mipLevels(mipLevels) {
    glm::vec<2,int> screenDimensions = Application::getInstance().getWindow().getDimensions();

    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);

    //generate mip 0
    this->target.push_back(std::make_unique<Texture>(screenDimensions));
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target[0]->getId(), 0);

    glGenRenderbuffers(1, &this->rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenDimensions.x, screenDimensions.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboId);

    //generate mip level textures
    for (int i = 1; i < mipLevels + 1; i++) {
        glm::vec<2,int> bufferDimensions = screenDimensions / static_cast<int>(pow(2,i));
        this->target.push_back(std::make_unique<Texture>(bufferDimensions));
    }

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FBO created successfully" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Application::getInstance().getWindow().attach(this);
}

Framebuffer::~Framebuffer() {
    glDeleteRenderbuffers(1,&this->rboId);
    glDeleteFramebuffers(1,&this->id);
}

void Framebuffer::bind(int mipLevel) const {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    if (mipLevel < this->target.size())
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target[mipLevel]->getId(), 0);
}

void Framebuffer::bindDepth(int mipLevel) const {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, this->target[mipLevel]->getId(), 0);
}

void Framebuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const uint32_t &Framebuffer::getTargetId(int mipLevel) const {
    return this->target[mipLevel]->getId();
}

void Framebuffer::update(int width, int height) {
    glm::vec<2,int> screenDimensions{width,height};

    //clear textures and renderbuffer
    this->target.clear();
    glDeleteRenderbuffers(1,&this->rboId);

    this->bind();
    //generate mip 0
    this->target.push_back(std::make_unique<Texture>(screenDimensions));
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target[0]->getId(), 0);

    glGenRenderbuffers(1, &this->rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenDimensions.x, screenDimensions.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboId);

    for (int i = 1; i < mipLevels + 1; i++){
        glm::vec<2,int> bufferDimensions = screenDimensions / static_cast<int>(pow(2,i));
        this->target.push_back(std::make_unique<Texture>(bufferDimensions));
    }
    this->unbind();
}

const glm::vec<2, int> &Framebuffer::getTargetDimensions(int mipLevel) const {
    return this->target[mipLevel]->getDimensions();
}

Framebuffer::Framebuffer(float h) : mipLevels(0) {

    glm::vec<2,int> screenDimensions = Application::getInstance().getWindow().getDimensions();

    this->target.push_back(std::make_unique<Texture>(screenDimensions,5));

    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->target[0]->getId(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "depth FBO created successfully" << std::endl;


    this->unbind();

    Application::getInstance().getWindow().attach(this);
}
