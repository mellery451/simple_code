#!/usr/bin/perl -w
# simple fibonacci impl with memoization
# author: Mike Ellery
use strict;
use Time::HiRes qw(gettimeofday tv_interval);
use feature 'say';

my $size = shift || 10;
my @memory = (0) x $size;

my $start = [gettimeofday];
say "FIB of $size is " . fib($size);
say "PHI at $size is " . $memory[-1]/$memory[-2];
say "TOOK " . tv_interval($start) . " seconds";

sub fib {
  my $n_val = shift;
  return $n_val if ($n_val <= 1);
  unless ($memory[$n_val]) {
      $memory[$n_val] = fib($n_val - 1) + fib($n_val - 2);
  }
  return $memory[$n_val];
}
