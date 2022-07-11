#pragma once

#include <OGL.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

std::string ReadFile(const char *fileName);

static void Link(GLuint ShaderProgram);

static void AddShader(GLuint ShaderProgram, const char *pShaderText,
                      GLenum ShaderType);

void CompileShaders();
