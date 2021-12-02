#pragma once

#include <string_view>
#include <vector>

namespace dfe {
class FileSystem {
 public:
  static bool CheckFileExists(std::string_view filePath);

  static std::string ReadFileToString(std::string_view filePath);

  static std::vector<char> ReadFileToVectorChar(std::string_view filePath);
};
}  // namespace dfe