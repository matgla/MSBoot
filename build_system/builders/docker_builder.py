from os import path
from builder import CommandBuilder


class DOCKER_COMMAND:
    RUN = 1


def get_common_command():
    return " -c \"source ~/.bashrc && cd /mnt/source/scripts && "


class DockerDefaultBuilder:

    def getDockerCommand(self):
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
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
        return " -v " + path_to_working_dir + ":/mnt/source"

    def getLoginCmd(self):
        return " su - admin -s /bin/bash"

    def getShellCmd(self):
        return " -c \"\""

    def getColors(self):
        return " -it -e \"TERM=xterm-256color\""

    def getCmd(self):
        return "docker " + self.getDockerCommand() + self.getColors() + \
            self.getMountCommand() + self.getImageName() + \
            self.getLoginCmd() + self.getShellCmd()


class DockerGenerateBuilder(DockerDefaultBuilder):

    def get_string(self):
        return "generate target"

    def getShellCmd(self):
        return get_common_command() + "sh generate.sh\""


class DockerTargetBuilder(DockerDefaultBuilder):

    def get_string(self):
        return "build target"

    def getShellCmd(self):
        return get_common_command() + "sh build.sh\""


class DockerGenerateTestsBuilder(DockerDefaultBuilder):

    def get_string(self):
        return "generate tests"

    def getShellCmd(self):
        return get_common_command() + "sh generate_tests.sh\""


class DockerUnitTestBuilder(DockerDefaultBuilder):

    def get_string(self):
        return "build & run UTs"

    def getShellCmd(self):
        return get_common_command() + "sh test_ut.sh\""


class DockerSystemTestRunner(DockerDefaultBuilder):

    def get_string(self):
        return "run STs"

    def getShellCmd(self):
        return get_common_command() + "sh test_st.sh\""


class DockerBuilder:

    def __init__(self):
        self.command = DOCKER_COMMAND.RUN

    def build_target(self):
        return DockerTargetBuilder()

    def build_unit_tests(self):
        return DockerUnitTestBuilder()

    def generate_target(self):
        return DockerGenerateBuilder()

    def generate_tests(self):
        return DockerGenerateTestsBuilder()

    def run_system_tests(self):
        return DockerSystemTestRunner()

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
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
        return " -v " + path_to_working_dir + ":/mnt/source"

    def getCmd(self):
        return "docker " + self.getDockerCommand() + self.getColors() + self.getMountCommand() + self.getImageName() + self.getLoginCmd() + self.getShellCmd()

    def getLoginCmd(self):
        return " su - admin -s /bin/bash"

    def getShellCmd(self):
        return " -c \"\""
