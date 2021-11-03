#pragma once

#include <string>
#include <filesystem>

using std::filesystem::path;
using std::filesystem::weakly_canonical;
using std::string;

class ResourceManager {
 private:
  const string resourcesDir = "/resources/";
  std::string execPath;

  string resourcesPath;

  void generateResourcesPath();

 public:
  ResourceManager(std::string _execPath);
};
