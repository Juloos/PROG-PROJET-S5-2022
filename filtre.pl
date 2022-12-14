#!/usr/bin/perl -w
use strict;
use Getopt::Long;

my @begin_directive = (qr/^\s*#ifdef\s+(\w+)\s*$/,
                       qr/^\s*\/\*\s+BEGIN\s+(\w+)\s+\*\/\s*$/);
my @else_directive = (qr/^\s*#else\s+\/\*\s+(\w+)\s+\*\/\s*$/,
                       qr/^\s*\/\*\s+ALTERNATIVE(?:\s+(\w+)\s+\*\/)\s*$/);
my @end_directive = (qr/^\s*#endif\s+\/\*\s+(\w+)\s+\*\/\s*$/,
                     qr/^\s*\/\*\s+END(?:\s+(\w+)\s+\*\/)\s*$/);

sub usage() {
print <<END;
Utilisation:
filtre.pl [ --help ] [ --herite ] [ --supprime NOM ] [ --conserve-autres ]
          [ --type num ] [ --inverse ] [ fichier ]

Affiche le contenu du (des) fichier(s) donne(s) en supprimant toutes les
directives de la forme "begin_directive NOM", "else_directive" ou
"end_directive" et en supprimant les parties de texte après la "begin_directive
NOM" et après la "else_directive" respectivement lorsque NOM est donné en
argument à --supprime ou non.
Les directives peuvent être de la forme :
0 - #ifdef NOM
    #else /* NOM */
    #endif /* NOM */
1 - /* BEGIN NOM */
    /* ALTERNATIVE NOM */
    /* END NOM */
Par défaut, le forme utilisée est la 0, elle peut être changée à l'aide de
l'option --type. Lorsque l'option --conserve-autres est donnée, les directives
ainsi que les parties entre une "else_directive" et une "end_directive"
d'une partie dont le nom n'est pas donné à --supprime sont conservées.
Si l'option --herite est donnee, les trous imbriques dans un trou supprime sont
egalement supprimes (autrement il faut les supprimer explicitement avec
--supprime).
Si l'option --inverse est donnée, le texte (hors directives) qui devrait
normalement être affiché ne le sera pas et, inversement, celui qui devrait ne
pas être affiché le sera.
END
exit 0;
}

my %cut;
my %keep;
my @supprime;
my @conserve;
my $herite=0;
my $type=0;
my $autres=0;
my $reverse=0;

GetOptions("supprime=s"=>\@supprime, "conserve=s"=>\@conserve,
           "help"=>\&usage, "herite"=>\$herite, "type=i"=>\$type,
           "conserve-autres"=>\$autres, "inverse"=>\$reverse);

foreach my $name (@supprime) {
    $cut{lc($name)} = 1;
}

foreach my $name (@conserve) {
    $keep{lc($name)} = 1;
}

my $mode=1;
my @names_stack;
my @modes_stack;
my $line_number = 0;

while (my $line=<>) {
    $line_number++;
# Debut de directive
    if ($line =~ $begin_directive[$type]) {
        my $name = lc($1);
        push @modes_stack, $mode;
        push @names_stack, $name;
        $mode = ($mode <= 0) ? ($herite ? -1 : 0) : ($cut{$name} ? 0 : 1);
        print $line if ($mode > 0) and ($keep{$name} ? 0 : $autres);
# Fin de directive
    } elsif ($line =~ $end_directive[$type]) {
        my $name = lc($1);
        $name = defined($name) ? $name : "";
        print $line if ($mode == 1) and ($keep{$name} ? 0 : $autres);
		my $former_mode;
        my $expected_name;
		if (scalar(@modes_stack)) {
			$former_mode = $mode;
        	$mode = pop @modes_stack;
        	$expected_name = pop @names_stack;
		} else {
			$expected_name = undef;
		}
        if (length($name) and defined($expected_name) and ($name ne $expected_name)) {
        	print STDERR "Name mismatch at line $line_number, ignoring\n";
        	push @modes_stack, $mode;
        	push @names_stack, $expected_name;
			$mode = $former_mode;
		}
# Alternative
    } elsif ($line =~ $else_directive[$type]) {
        my $name = lc($1);
        $name = defined($name) ? $name : "";
        print $line if ($mode > 0) and ($keep{$name} ? 0 : $autres);
        my $expected_name;
        $expected_name = $names_stack[$#names_stack];
        print STDERR "Name mismatch at line $line_number\n"
            unless not length($name) or $name eq $expected_name;
        $mode = ($mode > 0) ? ($keep{$name} ? 0 : $autres)
                            : (($mode < 0) ? $mode : 2);
# Reste du texte
    } else {
        print $line if ((($mode > 0) and not $reverse)
                    or (($mode <= 0) and $reverse));
    }
}
