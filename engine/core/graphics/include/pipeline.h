#pragma once

#include <string>
#include <vector>

#include <file_system.h>
#include <iostream>

namespace dfe {
class Pipeline {
 public:
  Pipeline(const std::string& vertShaderFilePath,
           const std::string& fragShaderFilePath) {
    CreateGraphicPipeline(vertShaderFilePath, fragShaderFilePath);
  }
  ~Pipeline() = default;

 private:
  void CreateGraphicPipeline(const std::string& vertShaderFilePath,
                             const std::string& fragShaderFilePath) {
    auto vertCode = FileSystem::ReadFileToVectorChar(vertShaderFilePath);
    auto fragCode = FileSystem::ReadFileToVectorChar(fragShaderFilePath);
  }
};
}  // namespace dfe