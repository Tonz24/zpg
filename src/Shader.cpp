#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // 1. retrieve the vertex/fragment source code from filePath

    const char *vShaderCode;
    const char *fShaderCode;

    std::string vertexCode =  loadShader(vertexPath);
    std::string fragmentCode = loadShader(fragmentPath);

    vShaderCode = vertexCode.c_str();
    fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::loadShader(const std::string& path) {

    std::string delimiter = "\\";

    std::string pathPath = path;
    std::string pathPathPath;

    //throw away filename
    size_t pos = 0;
    std::string token;
    while ((pos = pathPath.find(delimiter)) != std::string::npos) {
        token = pathPath.substr(0, pos);
        std::cout << token << std::endl;
        pathPathPath += pathPath.substr(0,pos + delimiter.length());
        pathPath.erase(0, pos + delimiter.length());
    }
    std::cout << pathPath << std::endl;
    std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


    try {
        // open files
        shaderFile.open(path);

        std::stringstream shaderStream;

        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();

        std::string line;

        while (std::getline(shaderStream, line)) {

            std::string search{"#include"};

            size_t found = line.find(search);

            if (found != std::string::npos) {
                size_t start = found + search.length();
                size_t end = line.find(' ', start);
                std::string wordAfter = line.substr(start, end + start);
                auto h = wordAfter.substr(2, wordAfter.size() - 3);

                line = loadShader(pathPathPath +  h); //recursively relpace #include with file contents
            }
            code += line + "\n";
        }

        // close file handlers
        shaderFile.close();
    }

    catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    return code;
}


void Shader::use() const{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string& name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),(int)value);
}

void Shader::setInt(const std::string& name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2f(const std::string& name,glm::vec2 vec) const{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), vec.x,vec.y);
}

void Shader::setVec2i(const std::string& name,glm::vec<2,int> vec) const{
    glUniform2i(glGetUniformLocation(ID, name.c_str()), vec.x,vec.y);
}

void Shader::setVec3f(const std::string& name, glm::vec3 vec) const{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x,vec.y,vec.z);
}

void Shader::setVec4f(const std::string& name, glm::vec4 vec) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat4f(const std::string& name, glm::mat4x4 mat) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,glm::value_ptr(mat));
}

void Shader::checkCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if (type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::compileShaders() {
    shaderCache["shader_default"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\default.frag)");
    shaderCache["shader_constant"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\constant.frag)");
    shaderCache["shader_texture"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\texture.frag)");
    shaderCache["shader_lambert"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\lambert.frag)");
    shaderCache["shader_phong"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\phong.frag)");
    shaderCache["shader_blinn"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\blinn.frag)");
    shaderCache["shader_light"] = std::make_unique<Shader>(R"(..\Shaders\default.vert)",R"(..\Shaders\light.frag)");

    shaderCache["effect_empty"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\empty.frag)");
    shaderCache["effect_filter"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\colorFilter.frag)");
    shaderCache["effect_box_blur_horizontal"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\boxBlurHorizontal.frag)");
    shaderCache["effect_box_blur_vertical"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\boxBlurVertical.frag)");
    shaderCache["effect_gaussian_blur_horizontal"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\gaussBlurHorizontal.frag)");
    shaderCache["effect_gaussian_blur_vertical"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\gaussBlurVertical.frag)");
    shaderCache["effect_tonemap"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\tonemap.frag)");
    shaderCache["effect_downsample"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\downsample.frag)");
    shaderCache["effect_upsample"] = std::make_unique<Shader>(R"(..\Shaders\ImageEffects\default.vert)",R"(..\Shaders\ImageEffects\upsample.frag)");
}

const Shader* Shader::getShaderProgram(const std::string& name) {
    return Shader::shaderCache[name].get();
}

