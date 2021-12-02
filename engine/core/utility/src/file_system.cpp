#include <file_system.h>

#include <filesystem>
#include <fstream>

namespace dfe {
bool FileSystem::CheckFileExists(std::string_view filePath) {
  const std::filesystem::path path = filePath.data();
  return std::filesystem::exists(path);
}

std::string FileSystem::ReadFileToString(std::string_view filePath) {
  std::ifstream file(filePath.data(),
                     std::ios::in | std::ios::binary | std::ios::ate);

  std::string result;
  if (file.is_open()) {
    const size_t fileSize = static_cast<size_t>(file.tellg());
    result.reserve(fileSize);
    file.seekg(0, std::ios::beg);
    result.assign((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  } else {
    // TODO Indicate error
  }

  file.close();
  return result;
}

std::vector<char> FileSystem::ReadFileToVectorChar(std::string_view filePath) {
  std::ifstream file(filePath.data(),
                     std::ios::in | std::ios::binary | std::ios::ate);

  std::vector<char> result;
  if (file.is_open()) {
    const size_t fileSize = static_cast<size_t>(file.tellg());
    result.resize(fileSize);
    file.seekg(0, std::ios::beg);
    file.read(result.data(), fileSize);
  } else {
    // TODO Indicate error
  }

  file.close();
  return result;
}
}  // namespace dfe