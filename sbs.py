#!/usr/bin/python

from os import path
from subprocess import call
from colorama import init, Fore, Back, Style
from build_system.builder import CommandBuilder
from build_system.docker_builder import DockerBuilder
from build_system.runner import Runner
import argparse
import re

init()  # init colorama

default_target = "stm32f429-Discovery"

parser = argparse.ArgumentParser()
parser.add_argument('-n', '--native-builder', dest='native', action='store_true',
                    help='don\'t use Docker')
parser.add_argument('-b', '--build', dest='build', action='store_true',
                    help='build project')
parser.add_argument('-t', '--target', dest='target', nargs='?', type=str, default=default_target,
                    help='select target, default=' + default_target)
parser.add_argument('-g', '--generate', dest='generate', action='store_true',
                    help='generate project')
parser.add_argument('-a', '--test', dest='all_tests', action='store_true',
                    help='run all tests')
parser.add_argument('-c', '--generate_test', dest='generate_test', action='store_true',
                    help='generate sources for unit tests')
parser.add_argument('-r', '--rebuild', dest='rebuild', action='store_true',
                    help='rebuild project (generate & build)')
parser.add_argument('-u', '--ut', dest='ut', action='store_true',
                    help='run unit tests')
parser.add_argument('-s', '--st', dest='st', action='store_true',
                    help='run system tests')
args = parser.parse_args()

runner = Runner(args)

run_command = 'build'
commands_to_run = []


if args.generate:
    commands_to_run.append('generate')
    run_command = 'generate'

if args.build:
    commands_to_run.append('build')
    run_command = 'build'

if args.generate_test:
    commands_to_run.append('generate_test')
    run_command = 'generate_test'

if len(commands_to_run) == 0:
    commands_to_run.append('build')

use_docker = True
if args.native:
    use_docker = False

builder = None


class DockerBuildBuilder(DockerBuilder):

    def get_string(self):
        return "build target"

    def getShellCmd(self):
        return ' -c \'source ~/.bashrc && cd /mnt/source && sh build.sh\''


class DockerGenerateBuilder(DockerBuilder):

    def get_string(self):
        return "generate target"

    def getShellCmd(self):
        return ' -c \'source ~/.bashrc && cd /mnt/source && sh generate.sh\''


class DockerGenerateTestBuilder(DockerBuilder):

    def get_string(self):
        return "generate tests"

    def getShellCmd(self):
        return ' -c \'source ~/.bashrc && cd /mnt/source && sh generate_tests.sh\''


class DockerTestBuilder(DockerBuilder):

    def get_string(self):
        return "build & run tests"

    def getShellCmd(self):
        return ' -c \'source ~/.bashrc && cd /mnt/source && sh test.sh\''

if use_docker == False:
    builder = CommandBuilder()

print Fore.BLUE + '===================================\n' \
                + '=  STM32 BootLoader Build System  =\n' \
                + '===================================' + Style.RESET_ALL

runner.print_commands_to_be_executed()

# for command in commands_to_run:
# print Fore.GREEN + 'Selected command: ' + Fore.YELLOW + command +
# Style.RESET_ALL

# for command in commands_to_run:
#     if command == 'build':
#         builder = DockerBuildBuilder()
#     if command == 'test':
#         builder = DockerTestBuilder()
#     if command == 'generate':
#         builder = DockerGenerateBuilder()
#     if command == 'generate_test':
#         builder = DockerGenerateTestBuilder()

#     print Fore.CYAN + '\nCalling: ' + Style.RESET_ALL + builder.getCmd()
# call(builder.getCmd(), shell=True)
