# perl additionally/errno_code.pl
use strict;
use warnings;

use Errno;

foreach my $err (sort keys (%!)) {
    $! = eval "Errno::$err";
    printf "%20s %4d   %s\n", $err, $! + 0, $!
}
