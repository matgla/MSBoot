docker run -it -e "TERM=xterm-256color" -v //d//repos//stm32-bootloader:/mnt/source docker_stm su - admin -s /bin/bash -c "cd /mnt/source && sh build.sh"