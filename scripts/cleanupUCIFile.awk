# To be used on the output file of pgn-extract, having used the following flags: -Wuci -s --noresults --nocomments --nobadresults
# Eliminates all lines that are not UCI moves and all matches where white does not start, and potentially very short
# matches or lines that only contain a score (pgn-extract does not remove all of them...)
{
    if (length($0) > 20 && substr($0, 0, 1) != "[" && substr($0, 2, 1) != "7" && substr($0, 2, 1) != "8")
        print $0;
}
