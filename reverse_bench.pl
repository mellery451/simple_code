
# investigate whether there are more peformant options
# for reversing a domain. Will want to investigate 
# something similar for splitting a domain into parts
use strict;
use warnings;
use Benchmark qw(:all :hireswallclock);

my $domain = "server1.l.google.com.";

my $count = 1000000;

sub naive {
    my $temp = $domain;
    $temp =~ s/\.$//;
    my $reversed = join('.', reverse(split(/\./, $temp)));
    return $reversed;
}

my $timing = timethese($count, {
    'NAIVE' => \&naive,
    'INLINE'  => sub{ 
        inline_code($domain);
     },
});

cmpthese($timing);

use Inline C => <<'END_OF_C_CODE';

#include <string.h>

SV* inline_code(char* domain) {
    char copy[256];    
    char new[256];
    strcpy(copy, domain);
    memset(new, 0, 256);
    char* piter = copy + strlen(copy) - 1;
    char* pdest = new; 
    /* eliminate the root dot, if present */
    if (*piter == '.') {
      *piter = '\0';
      piter--;
    }
    while (piter != copy) {
        if (*piter == '.') {
            strcpy(pdest, piter + 1);
            *piter = '\0';
            pdest += strlen(piter + 1);
            *pdest = '.';
            pdest++;
        }
        piter--;
    }
    strcpy(pdest, piter);
    return newSVpv(new, strlen(new));
}

END_OF_C_CODE
