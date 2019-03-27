#!/bin/bash

echo "Restoring grub.old to its original location"
cp grub.old /etc/default/grub
update-grub