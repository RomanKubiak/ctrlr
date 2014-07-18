#!/usr/bin/perl
#
# dumprsrc.pl -- dump a mac resource fork in a pseudo-readable form
#
# dumprsrc [-s] <file>
#
# <file> is a file containing the contents of a Mac resource fork.
# This is NOT the same as an AppleDouble, AppleSingle, or MacBinary
# file.  Programs like the ones at:
#
#   <ftp://ftp.ibp.fr/pub/linux/sunsite/utils/compress/macutils.tar.gz>
#
# can produce this sort of file from that sort.  Or they could if the
# FTP server was still there (was it just down when I checked or is it
# really down?  Anyway the debian 'macutils' source package has all this
# stuff.
#
# Speaking of sorts, the '-s' option will cause the individual resources
# in the output dump to be ordered lexically (ascending) by resource
# type and numerically (also ascending) by resource ID within each type.
# Otherwise they will be output in the order they appear in the
# resource map (not the order the resource data physically appears in
# the file.
#
# dumprsrc doesn't work on pipes, sockets, named pipes or character
# devices since it seeks like a mother.
#

##### COPYRIGHT STATEMENT ###########################################
# This program may be considered part of the public domain.  That
# notwithstanding, it would be polite to give credit to James Deikun
# as the original author if you use it.
#

##### GENERAL COMMENTS ON THE FILE FORMAT ###########################
# The resource file format uses a lot of array structures that have
# a 'last' pointer (like $#foo) rather than a 'size'.  The 'last'
# pointer is unsigned and has no sentinel value so these arrays
# can't be empty.  That's OK since, given the rest of the format,
# if they'd be empty they just wouldn't be included at all.  It also
# uses a lot of offsets of various sizes relative to headers in the
# file, and the documentation can be a bit unclear--in one case I
# thought downright deceptive--about what exactly these offsets are
# relative to.  I've figured it out, though, and it's in the source
# if you're wondering.
#
# This format also uses a lot of 16-bit integers as offsets and
# sizes.  The limits this puts on the format aren't generally a
# problem in practice, although it does perhaps shed some light on
# why exactly That Company changed their stance and stopped the
# practice of putting all the program code in the resource fork.

##### GENERAL COMMENTS ON THE CODE ##################################
# As far as code goes, this really lives up to the name.  It follows
# the logical structure of the resource fork: file header -> map
# header -> type list -> resource reference lists -> resources.  It
# does this in a breadth-first manner.  It uses certain prefix and
# suffix conventions:
#
#  r*         - resource - useless, I know.
#  rdata*     - attributes of the resource data area
#  rmap*      - attributes of the resource map area
#  rtypelist* - attributes of the resource type list
#  rreflist*  - attributes of a resource reference list
#  rtl_*      - info from entries of the resource type list
#  rrl_*      - info from entries of a resource reference list
#  *start     - relative or absolute location of something in the file
#  *offset    - same thing (oops--make this meaningful in v2)
#  *len       - length, generally in bytes, of a structure in the file
#  *last      - index of last element in an array
#
# I apologize for the poor readability, especially given I'm posting
# this as example code.  It was originally designed for a more
# specific purpse.
#
# I also wish it had special handling for more resource types than
# 'STR#'...
#
# Now, let's get with the program, so to speak ...
#

use Getopt::Std;
use IO::Seekable;

getopts('s');

unless (1==@ARGV) {
  die "Usage: $0 [-s] <resource file>\n\nOptions:\n  -s  print resources in sorted order not map order\n"
}

# RESOURCE FILE:
#   16b  resource header
#   var  reserved
#   var  resource data
#   var  resource map

# RESOURCE HEADER:
#   4b   offset to resource data
#   4b   offset to resource map
#   4b   length of resource data
#   4b   length or resource map

open(RSRC, $ARGV[0]);
read(RSRC, $rhdr, 16);
($rdatastart, $rmapstart, $rdatalen, $rmaplen) = unpack("NNNN", $rhdr);

# RESOURCE MAP:
#   22b  reserved
#   2b   attributes
#   2b   offset of resource type list in map
#   2b   offset of resource name list in map
#   2b   # of last type in type map (starting from 0)
#        NOTE: zero types are represented by a 0-byte resource fork.
#   var  reserved for future expansion
#   var  resource type list
#   var  reference lists
#   var  resource name list

print "resource map found at $rmapstart\n";
seek(RSRC, $rmapstart+22, SEEK_SET);
read(RSRC, $rmaphdr, 6);
($rattr, $rtypeliststart, $rnameliststart) = unpack("a2nn", $rmaphdr);
$rtypeliststart += $rmapstart;
$rnameliststart += $rmapstart;
seek(RSRC, $rtypeliststart, SEEK_SET);
read(RSRC, $rtypelistlast, 2);
$rtypelistlast = unpack("n", $rtypelistlast);
$rtypelistlast += 65536 if $rtypelistlast  < 0;
print "$rtypelistlast different resource types\n";

# RESOURCE TYPE LIST ENTRY:
#  4b   resource type
#  2b   # of last resource of this type (starting at 0)
#       NOTE: a type with 0 resources gets no type list entry;
#  2b   offset from beginning of resource type list to this type's
#       reference sublist.

$rleftoff = $rtypeliststart + 8*($rtypelistlast+1) + 2;
for $i (0..$rtypelistlast) {
  read(RSRC, $rtypelistent, 8);
  ($rtype, $rlast, $roffset) = unpack("a4nn", $rtypelistent);
  $roffset += $rtypeliststart;
  warn "resource reference list for type '$rtype' not contiguous (at $roffset, expected $rleftoff)\n" if $roffset != $rleftoff;
  $rleftoff = $roffset + 12*($rlast+1);
  push @rtl_rtype, $rtype;
  push @rtl_reflast, $rlast;
  push @rtl_refstart, $roffset;
  print "$i '$rtype' $roffset $rlast\n";
}
$bitmask24 = (1 << 24) - 1;

# RESOURCE REFERENCE LIST ENTRY
#
#  2b   resource id
#  2b   offset of resource name in resource name list (-1 if nameless);
#  1b   resource attributes
#  3b   offset of this resource's data in resource data
#  4b   reserved

for $i (0..$rtypelistlast) {
  seek(RSRC, $rtl_refstart[$i], SEEK_SET);
  for $j (0..$rtl_reflast[$i]) {
    read(RSRC, $rreflistent, 12);
    ($rid, $rnameoffset, $rlocalattr, $roffset_coded) = unpack("nnCa3", $rreflistent);
    $roffset = unpack("N", "\0" . $roffset_coded);
    if ($rnameoffset == 65535) {
      undef $rnameoffset;
    } else {
      $rnameoffset += $rnameliststart;
    }
    $rid -= 65536 if $rid > 32767;
    $roffset += $rdatastart;
    push @rrl_rtype, $rtl_rtype[$i];
    push @rrl_rid, $rid;
    push @rrl_rdatastart, $roffset;
    push @rrl_rnamestart, $rnameoffset;
    push @rrl_rattr, $rlocalattr;
    print "found '$rtl_rtype[$i]'$rid at $roffset (name at $rnameoffset) with attributes $rlocalattr\n";
  }
}
print "\n";	# debugging/illustrative stuff over, down to the meat

for $i (0..$#rrl_rid) {
  if (defined($rrl_rnamestart[$i])) {
    seek(RSRC, $rrl_rnamestart[$i], SEEK_SET);
    read(RSRC, $rlen, 1);
    $rlen = ord($rlen);
    read(RSRC, $rname, $rlen);
    push @rrl_rname, $rname;
  } else {
    push @rrl_rname, undef;
  }
}

@order = (0..$#rrl_rid);
if ($opt_s) {
  @order = sort { $rrl_rtype[$a] cmp $rrl_rtype[$b] or $rrl_rid[$a] <=> $rrl_rid[$b] } @order;
}

for $i (@order) {
  print "'$rrl_rtype[$i]'$rrl_rid[$i]";
  print " named '$rrl_rname[$i]'" if defined($rrl_rname[$i]);
  print ":\n";
  seek(RSRC, $rrl_rdatastart[$i], SEEK_SET);
  read(RSRC, $rlen, 4);
  $rlen = unpack("N", $rlen);
  if ($rrl_rtype[$i] eq 'STR#') {
    # STR# resource - 16-bit integer indicating the number of strings
    #                 followed by that many closely packed pascal
    #                 strings.
    #
    read(RSRC, $strs, 2);
    $nstrs = unpack("n", $strs);
    print "  $nstrs strings\n";
    for $j (1..$nstrs) {
      read(RSRC, $slen, 1);
      $slen = ord($slen);
      read(RSRC, $str, $slen);
      @lines = split "\r", $str;
      printf "    %05d %s\n", $j, shift @lines;
      printf "          %s\n", shift @lines while @lines;
    }
    print "\n";
  } else {
    # anything else -- dump as a 16-byte-per-line classic hexdump
    #
    read(RSRC, $data, $rlen);
    $offs = 0;					# offset of this line in $data
    while (length($data) > 15) {
      $piece = substr($data, 0, 16, '');
      @bytesfrompiece = unpack("C16", $piece);
      $piece =~ y/\000-\037\177-\377/./;
      printf "  %8x  %2x %2x %2x %2x %2x %2x %2x %2x-%2x %2x %2x %2x %2x %2x %2x %2x  %16s\n", $offs, @bytesfrompiece, $piece;
      $offs += 16;
    }
    @bytesfrompiece = unpack("C*", $data);
    $data =~ y/\000-\037\177-\377/./;
    if (length($data) >= 8) {
      $form = "  %8x  %2x %2x %2x %2x %2x %2x %2x %2x-" . ("%2x " x (length($data)-8)) . ("   " x (16-length($data))) . " %s\n";
    } else {
      $form = "  %8x " . (" %2x" x length($data)) . ("   " x (8-length($data))) . "-" . ("   " x 8) . " %s\n";
    }
    printf $form, $offs, @bytesfrompiece, $data;
    print "\n";
  }
}

