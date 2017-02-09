#!/usr/bin/python

from os import path
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-n', '--no-docker', dest='nodocker', action='store_true')
args = parser.parse_args()

use_docker = True
if args.nodocker:
    use_docker = False

builder = None

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    
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
            
    def getMountCommand(self):
        return " -v " + path.dirname(path.abspath(__file__)) + ":/mnt/source"
        
    def getCmd(self):
        return "docker " + self.getDockerCommand() + self.getMountCommand() + self.getLoginCmd() + self.getShellCmd()
        
    def getLoginCmd(self):
        return " su - admin -s /bin/bash"
    
    def getShellCmd(self):
        return " -c \"\""
    
class DockerBuildBuilder(DockerBuilder):
    def getShellCmd(self):
        return " \"cd /mnt/source && sh build.sh\""

if use_docker == False:
    builder = CommandBuilder()
else:
    builder = DockerBuildBuilder()


print bcolors.HEADER + "Welcome to pyhon build system\n" + bcolors.ENDC + bcolors.OKGREEN + " -> " + bcolors.ENDC + "\n"

print bcolors.OKBLUE + builder.getCmd()