from builder_factory import BuilderFactory
import native_builders

class NativeBuilderFactory(BuilderFactory):

    def build_target(self):
        return native_builders.NativeTargetBuilder()
    
    def generate_target(self):
        return native_builders.NativeGenerateTargetBuilder()
        
    def generate_tests(self):
        return native_builders.NativeDefaultBuilder()
        
    def build_unit_tests(self):
        return native_builders.NativeDefaultBuilder()
        
    def run_system_tests(self):
        return native_builders.NativeDefaultBuilder()