from subprocess import call
from colorama import init, Fore, Back, Style
from build_system.builders.docker_builder import DockerBuilder, DockerGenerateBuilder
from build_system.builders.native_builder import NativeBuilder


class Runner:

    def __init__(self, args):
        self.args = args
        self.__parse_args()

    def print_commands_to_be_executed(self):
        for command in self.commands_to_run:
            print Fore.GREEN + 'Selected command: ' + Fore.YELLOW + \
                command.get_string() + Style.RESET_ALL

    def execute_commands(self):
        for command in self.commands_to_run:
            print Fore.CYAN + '\nCalling: ' + Style.RESET_ALL + command.getCmd()
            call(command.getCmd(), shell=True)

    def __parse_args(self):
        self.commands_to_run = []
        if self.args.native:
            self.builder = NativeBuilder()
        else:
            self.builder = DockerBuilder()

        if self.args.generate or (self.args.rebuild and self.args.build):
            self.commands_to_run.append(self.builder.generate_target())
        if self.args.build or (self.args.rebuild and self.args.generate):
            self.commands_to_run.append(self.builder.build_target())
        if self.args.generate_test or (self.args.rebuild and self.args.ut) \
                or (self.args.all_tests and self.args.rebuild):
            self.commands_to_run.append(self.builder.generate_tests())
        if self.args.ut or (self.args.rebuild and self.args.generate_test) or self.args.all_tests:
            self.commands_to_run.append(self.builder.build_unit_tests())
        if self.args.st or self.args.all_tests:
            self.commands_to_run.append(self.builder.run_system_tests())
