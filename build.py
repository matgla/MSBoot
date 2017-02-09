#!/usr/bin/python

from os import path
from subprocess import call
from colorama import init, Fore, Back, Style
import argparse
import re

init()
parser = argparse.ArgumentParser()
parser.add_argument('-n', '--no-docker', dest='nodocker', action='store_true')
parser.add_argument('-b', '--build', dest='build', action='store_true')
parser.add_argument('-g', '--generate', dest='generate', action='store_true')
parser.add_argument('-t', '--test', dest='test', action='store_true')
parser.add_argument('-c', '--generate_test',
                    dest='generate_test', action='store_true')
args = parser.parse_args()

run_command = "build"
commands_to_run = []

if args.generate:
    commands_to_run.append("generate")
    run_command = "generate"

if args.build:
    commands_to_run.append("build")
    run_command = "build"

if args.generate_test:
    commands_to_run.append("generate_test")
    run_command = "generate_test"

if args.test:
    commands_to_run.append("test")
    run_command = "test"

if len(commands_to_run) == 0:
    commands_to_run.append("build")

use_docker = True
if args.nodocker:
    use_docker = False

builder = None


class CommandBuilder:

    def getCmd(self):
        return "Default"


class DOCKER_COMMAND:
    RUN = 1


class DockerBuilder(CommandBuilder):

    def __init__(self):
        self.command = DOCKER_COMMAND.RUN

    def getDockerCommand(self):
        if DOCKER_COMMAND.RUN == self.command:
            return "run"

    def getImageName(self):
        return " matgla/docker_stm"

    def getMountCommand(self):
        path_to_working_dir = path.dirname(
            path.abspath(__file__))

        if path_to_working_dir.find(":") != -1:
            path_to_working_dir = "//" + path_to_working_dir
            path_to_working_dir = path_to_working_dir.replace("\\", "//")
            path_to_working_dir = path_to_working_dir.replace(":", "")
        return " -v " + path_to_working_dir + ":/mnt/source"

    def getCmd(self):
        return "docker " + self.getDockerCommand() + self.getMountCommand() + self.getImageName() + self.getLoginCmd() + self.getShellCmd()

    def getLoginCmd(self):
        return " su - admin -s /bin/bash"

    def getShellCmd(self):
        return " -c \"\""


class DockerBuildBuilder(DockerBuilder):

    def getShellCmd(self):
        return " -c \"source ~/.bashrc && cd /mnt/source && sh build.sh\""


class DockerGenerateBuilder(DockerBuilder):

    def getShellCmd(self):
        return " -c \"source ~/.bashrc && cd /mnt/source && sh generate.sh\""


class DockerGenerateTestBuilder(DockerBuilder):

    def getShellCmd(self):
        return " -c \"source ~/.bashrc && cd /mnt/source && sh generate_tests.sh\""


class DockerTestBuilder(DockerBuilder):

    def getShellCmd(self):
        return " -c \"source ~/.bashrc && cd /mnt/source && sh test.sh\""

if use_docker == False:
    builder = CommandBuilder()

print Fore.BLUE + "===================================\n" \
                + "=  STM32 BootLoader Build System  =\n" \
                + "===================================" + Style.RESET_ALL

for command in commands_to_run:
    print Fore.GREEN + "Selected command: " + Fore.YELLOW + command + Style.RESET_ALL

for command in commands_to_run:
    if command == "build":
        builder = DockerBuildBuilder()
    if command == "test":
        builder = DockerTestBuilder()
    if command == "generate":
        builder = DockerGenerateBuilder()
    if command == "generate_test":
        builder = DockerGenerateTestBuilder()

    print Fore.CYAN + "\nCalling: " + Style.RESET_ALL + builder.getCmd()
    call(builder.getCmd(), shell=True)
