#!/usr/bin/perl
##############################################################
#                          SSBC 
# Simulator for SSBC.v4.r3
# Docs: ssbc261-v5.r1.artn and testPlan
# File: ssbc.pl
# Author: Peter Walsh csci 261 Feb 2010
#          Updated Nov 25 2015 (PW)
#          Updated Jan 19 2017 (PW)
##############################################################
        
use Bit::Vector;
use Switch;

sub resetSSBC { 

   open(MACHINECODE, "mac") || die "can't open mac file \n";

   $reset=0;

   my $vec = Bit::Vector->new(9);

   my $lc=0;
   while (<MACHINECODE>) {
      $instr=substr($_, 0, 8);
      $vec->from_Bin($instr);
      @mem[$lc] = $vec->to_Dec();
      $lc++;
   }

   close (MACHINECODE);

   $pc=0;
   $sp=0xfffa;
   $halt=0;
   $fault=0;

}

sub printMenu {
   print "+------------------------+ \n";
   print "|  R: RESET              | \n";
   print "|  b: BREAK              | \n";
   print "|  r: RUN                | \n";
   print "|  A: READ PORT A        | \n";
   print "|  B: WRITE PORT B       | \n";
   print "|  C: READ PORT C        | \n";
   print "|  D: WRITE PORT D       | \n";
   print "|  s: STATUS             | \n";
   print "|  t: TOP                | \n";
   print "|  p: PSW                | \n";
   print "|  q: QUIT               | \n";
   print "|                        | \n";
   print "|  Enter menu selection: | \n";
   print "+------------------------+ \n";
}

sub aluNor {
   my $ans, $xx, $yy;
   $xx=@_[0];
   $yy=@_[1];

   ($xx | $yy) ^ 0xff;

}


sub aluAdd {
   my $xx, $yy;
   $xx=@_[0];
   $yy=@_[1];

   ($xx+$yy) % 256;
}

sub aluSub {
   my $xx, $yy;
   $xx=@_[1];
   $yy=@_[0];

   if ($xx>=128) {
      $xx=($xx % 128);
      $xx=-$xx;
   }

   if ($yy>=128) {
      $yy=($yy % 128);
      $yy=-$yy;
   }


   if ($xx>=$yy) {
      ($xx-$yy) % 128 ;
   } else {
      ((($yy-$xx) + 128 ) % 256) ;
   }

}

sub adjustFlags {

   switch (@mem[0xfffb]) {
      case 0 {$Z=0; $N=0 }
      case 0x80 {$Z=1, $N=0 }
      case 0x40 {$Z=0, $N=1 }
   }
}

sub setFlags {
   my $xx;
   $xx=@_[0];

   @mem[0xfffb]=0;

   if ($xx==0) {
      $Z=1;
      @mem[0xfffb]=0x80;
   } else {
      $Z=0;
   }

   if ($xx>128) {
      $N=1;
      @mem[0xfffb]=0x40;
   } else {
      $N=0;
   }
}

sub insExe {
     
   switch ($ir) {
      case 0 {  }
      case 1 { $halt=1 }
      case 2 { @mem[$sp]=@mem[$pc]; $sp--; $pc++ }
      case 3 { $ext=((@mem[$pc]*256)+(@mem[$pc+1]));
               @mem[$sp]=@mem[$ext]; $sp--; $pc+=2 }
      case 4 { $sp++ }
      case 5 { $ext=((@mem[$pc]*256)+(@mem[$pc+1]));
               @mem[$ext]=@mem[$sp+1]; $sp++; $pc+=2;
	       adjustFlags() if ($ext==0xfffb) }
      case 6 { if (!$Z) {
                 $ext=((@mem[$pc]*256)+(@mem[$pc+1])); 
		 $pc=$ext;
               } else { $pc+=2 } }	
      case 7 { if (!$N) {
                 $ext=((@mem[$pc]*256)+(@mem[$pc+1])); 
		 $pc=$ext;
               } else { $pc+=2 } }	
      case 8 { @mem[$sp+2]=aluAdd(@mem[$sp+2], @mem[$sp+1]); $sp++; setFlags(@mem[$sp+1]) }
      case 9 { @mem[$sp+2]=aluSub(@mem[$sp+2], @mem[$sp+1]); $sp++; setFlags(@mem[$sp+1]) }
      case 10 { @mem[$sp+2]=aluNor(@mem[$sp+2], @mem[$sp+1]); $sp++ }

   }
}

sub execSSBC {

   if ((!$reset) && (!$fault)) {
      $ir=@mem[$pc];
      $pc++;
      if ($ir>$maxOpCode) {
         $fault=1;
      } else { insExe() }
   }
}

# main

my $portaVec=Bit::Vector->new(8);
my $portcVec=Bit::Vector->new(8);
my $portbVec=Bit::Vector->new(9);
my $portdVec=Bit::Vector->new(9);
my $topStackVec=Bit::Vector->new(8);
my $pswVec=Bit::Vector->new(8);
my $sel;

$maxOpCode=10;
$reset=1;

while (1) {
   printMenu();
   
   $sel=<>;
   chop($sel);
   switch($sel) {
      case "R" { resetSSBC() }
      case "b" { if ((!$halt) && (!$fault)) { execSSBC() } }
      case "r" { while ((!$halt) && (!$fault)) { execSSBC() } }
      case "B" { print "Enter Port B value in binary (8 bits) ";
                 $portbStr=<>; 
                 $portbStr=substr($portbStr, 0, 8);
                 $portbVec->from_Bin($portbStr);
                 @mem[0xfffd]=$portbVec->to_Dec() }
      case "A" { if (defined(@mem[0xfffc])) {
                    $portaVec->from_Dec(@mem[0xfffc]);
                    $portaStr=$portaVec->to_Bin();
       	         }
                 print "Port A value: $portaStr \n" }
      case "D" { print "Enter Port D value in binary (8 bits) ";
                 $portdStr=<>;
                 $portdStr=substr($portdStr, 0, 8);
                 $portdVec->from_Bin($portdStr);
                 @mem[0xffff]=$portdVec->to_Dec() } 
      case "C" { if (defined(@mem[0xfffe])) {
                    $portcVec->from_Dec(@mem[0xfffe]);
                    $portcStr=$portcVec->to_Bin();
                 }
                 print "Port C value: $portcStr \n" }
      case "s" { print "Fault: $fault \n Halt: $halt \n" }
      case "t" { if (defined(@mem[$sp+1])) {
                    $topStackVec->from_Dec(@mem[$sp+1]);
                    $topStackStr=$topStackVec->to_Bin();
                 }
                 print "Top of Stack: $topStackStr \n" }
      case "p" { if (defined(@mem[0xfffb])) {
                    $pswVec->from_Dec(@mem[0xfffb]);
                    $pswStr=$pswVec->to_Bin();
                 }
                 print "PSW: $pswStr \n" }
      case "q" { exit() }
   }
}
