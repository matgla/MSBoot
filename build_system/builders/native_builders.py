from os import path

from builder import Builder

class NativeDefaultBuilder(Builder):
    def get_cmd(self):
        return "default"
    
    def get_cmd_name(self):
        return "oleole"
        
class NativeTargetBuilder(NativeDefaultBuilder):
    def get_cmd_name(self):
        return "build target"
    def get_cmd(self):
        return "cd scripts && ./build.sh"
        
class NativeGenerateTargetBuilder(NativeDefaultBuilder):
    def get_cmd_name(self):
        return "generate target"
    def get_cmd(self):
        return "cd scripts && ./generate.sh"
        
class NativeGenerateTestBuilder(NativeDefaultBuilder):
    def get_cmd_name(self):
        return "generate tests"
    def get_cmd(self):
        return "cd scripts && ./generate_tests.sh"
        
class NativeTestBuilder(NativeDefaultBuilder):
    def get_cmd_name(self):
        return "generate tests"
    def get_cmd(self):
        return "cd scripts && ./generate_tests.sh"