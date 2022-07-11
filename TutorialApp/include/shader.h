#pragma once

#include <stdio.h>
#include <string.h>
#include <OGL.h>
#include <iostream>


std::string ReadFile(const char* fileName);

static void Link(GLuint ShaderProgram);

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

void CompileShaders();


