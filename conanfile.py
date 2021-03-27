from conans import ConanFile, CMake


class ArgumentParser(ConanFile):
    name = "arg_parser"
    version = "0.0.0"
    license = "MIT"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "Simple argument parser for CLI in C++"
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "gtest/1.8.1@bincrafters/stable",  # package 1.10.0 have some issue with conanfile ... find package doesn't work with build_type=Debug
        "fmt/7.1.3"  # std::format implementation
    ]
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake", "cmake_paths"
    exports_sources = "*"

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["arg_parser"]
