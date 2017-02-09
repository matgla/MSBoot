from builder import CommandBuilder


class NativeBuilder(CommandBuilder):

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

    def getCmd(self):
        return "docker " + self.getDockerCommand() + self.getMountCommand() + self.getImageName() + self.getLoginCmd() + self.getShellCmd()

    def getLoginCmd(self):
        return " su - admin -s /bin/bash"

    def getShellCmd(self):
        return " -c \"\""

    def get_string(self):
        return "build target"
