from conans import ConanFile, CMake


class BraceChecker(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "gtest/1.8.1@bincrafters/stable",  # package 1.10.0 have some issue with conanfile ... find package dosn't work with build_type=Debug
        "fmt/7.1.3"  # std::format implementation
    ]
    generators = "cmake", "cmake_paths"

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        cmake.configure()
        cmake.build()
