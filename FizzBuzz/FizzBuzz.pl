
use strict;
use warnings;

foreach (1..100) {
  my $msg;
  $msg = "Fizz" if ($_ % 3 == 0);
  $msg .= "Buzz" if ($_ % 5 == 0);
  print "$_: $msg\n" if $msg;
}
