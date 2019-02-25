# To be used on the output file of pgn-extract, having used the following flags: -Wuci -noresults
{
    if (length($0) > 0 && substr($0, 0, 1) != "[")
        print $0;
}