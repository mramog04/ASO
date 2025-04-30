savedcmd_/home/osboxes/ASO/assoofs.mod := printf '%s\n'   assoofs.o | awk '!x[$$0]++ { print("/home/osboxes/ASO/"$$0) }' > /home/osboxes/ASO/assoofs.mod
