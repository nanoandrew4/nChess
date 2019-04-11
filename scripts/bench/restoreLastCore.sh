#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${SCRIPT_DIR}
echo "Restoring grub.old to its original location"
cp grub.old /etc/default/grub
update-grub