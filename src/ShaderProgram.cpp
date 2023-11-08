#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath){

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
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string ShaderProgram::loadShader(const std::string& path) {

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
                std::string wordAfter = line.substr(start, line.size() - start);
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

void ShaderProgram::bind() const{
    glUseProgram(this->id);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

void ShaderProgram::setVar(const std::string& name, bool value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void ShaderProgram::setVar(const std::string& name, int value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setVar(const std::string& name, float value) const{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setVar(const std::string& name, const glm::vec2& vec) const{
    glUniform2f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y);
}

void ShaderProgram::setVar(const std::string& name, const glm::vec<2,int>& vec) const{
    glUniform2i(glGetUniformLocation(id, name.c_str()), vec.x, vec.y);
}

void ShaderProgram::setVar(const std::string& name, const glm::vec3& vec) const{
    glUniform3f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z);
}

void ShaderProgram::setVar(const std::string& name, const glm::vec4& vec) const {
    glUniform4f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setVar(const std::string& name, const glm::mat4x4& mat) const{
    int loc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE,glm::value_ptr(mat));
}

void ShaderProgram::checkCompileErrors(unsigned int shader, const std::string& type){
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

void ShaderProgram::compileShaders() {
    shaderCache["shader_constant"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\constant.frag)"));
    shaderCache["shader_phong"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\phong.frag)"));
    shaderCache["shader_lambert"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\lambert.frag)"));
    shaderCache["shader_blinn"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\blinn.frag)"));

    shaderCache["shader_texture"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\texture.frag)"));
    shaderCache["shader_fur"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\fur.vert)",R"(..\Shaders\fur.geom)", R"(..\Shaders\fur.frag)"));
    shaderCache["shader_shadowMap"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\shadowMap.vert)", R"(..\Shaders\shadowMap.frag)"));
    shaderCache["shader_skybox"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\skybox.vert)", R"(..\Shaders\skybox.frag)"));
    shaderCache["shader_occlusion"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\default.vert)", R"(..\Shaders\occlusion.frag)"));

    shaderCache["effect_empty"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\empty.frag)"));
    shaderCache["effect_filter"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\colorFilter.frag)"));
    shaderCache["effect_box_blur_horizontal"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\boxBlurHorizontal.frag)"));
    shaderCache["effect_radial_blur"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\radialBlur.frag)"));
    shaderCache["effect_box_blur_vertical"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\boxBlurVertical.frag)"));
    shaderCache["effect_gaussian_blur_horizontal"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\gaussBlurHorizontal.frag)"));
    shaderCache["effect_gaussian_blur_vertical"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\gaussBlurVertical.frag)"));
    shaderCache["effect_tonemap"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\tonemap.frag)"));
    shaderCache["effect_downsample"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\downsample.frag)"));
    shaderCache["effect_upsample"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\upsample.frag)"));
    shaderCache["effect_add"] = std::unique_ptr<ShaderProgram>(new ShaderProgram(R"(..\Shaders\ImageEffects\default.vert)", R"(..\Shaders\ImageEffects\add.frag)"));
}

const ShaderProgram* ShaderProgram::getShaderProgram(const std::string& name) {
    return ShaderProgram::shaderCache[name].get();
}

ShaderProgram::ShaderProgram(const char *vertexPath, const char *geometryPath, const char *fragmentPath) {
    const char *vShaderCode;
    const char *fShaderCode;
    const char *gShaderCode;

    std::string vertexCode =  loadShader(vertexPath);
    std::string geometryCode = loadShader(geometryPath);
    std::string fragmentCode = loadShader(fragmentPath);

    vShaderCode = vertexCode.c_str();
    fShaderCode = fragmentCode.c_str();
    gShaderCode = geometryCode.c_str();

    // 2. compile shaders
    unsigned int vertex,geometry, fragment;

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

    // geometry Shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    checkCompileErrors(geometry, "GEOMETRY");

    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, geometry);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



