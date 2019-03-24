#!/bin/bash

echo "Overwriting default grub file at /etc/default/grub"
echo "Only the target line will be overwriten, the rest will be kept. The target line contains: GRUB_CMDLINE_LINUX=..."
echo "A copy of the current file will be made to the current directory, in case anything were to go awry..."
echo

cp /etc/default/grub grub.old

{ grep -c proc /proc/cpuinfo && cat /etc/default/grub; } | awk -f capCPUs.awk  | awk 'NR > 1' > tmpGrub.txt

cp tmpGrub.txt /etc/default/grub
rm tmpGrub.txt

echo "Updating grub, so the changes take effect"

update-grub

echo "Reboot your computer, and the last core should be invisible to system processes!"
