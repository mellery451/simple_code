use v6;

for $*IN.lines -> $line {
    my $score = 0;
    for $line.ords -> $ord {
        $score += $ord - 'a'.ord;
    }
    if ($score == 100) {
        say "$score: $line";
     }
}

