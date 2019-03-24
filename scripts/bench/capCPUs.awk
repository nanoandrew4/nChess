BEGIN {
    numCPUs = ""
}

{
    if (numCPUs == "")
        numCPUs = $0 - 2; # Assumes HT enabled CPU
    split($0, a, "="); 
    if (a[1] == "GRUB_CMDLINE_LINUX") {
        print a[1] "=\"isolcpus=" numCPUs "," numCPUs + 1 "\"";
    } else { // Line 0 will be output from command to determine CPU count
        print $0;
    }
}
