#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    btree* bt = btree_malloc();

    bt = btree_insert(bt, 825, 920);
    bt = btree_insert(bt, 330, 221);
    bt = btree_insert(bt, 582, 125);
    bt = btree_insert(bt, 26, 333);
    bt = btree_insert(bt, 612, 992);
    bt = btree_insert(bt, 904, 219);
    bt = btree_insert(bt, 94, 230);
    bt = btree_insert(bt, 231, 734);
    bt = btree_insert(bt, 959, 590);
    bt = btree_insert(bt, 767, 965);
    bt = btree_insert(bt, 322, 619);
    bt = btree_insert(bt, 601, 139);
    bt = btree_insert(bt, 867, 592);
    bt = btree_insert(bt, 153, 552);
    bt = btree_insert(bt, 389, 120);
    bt = btree_insert(bt, 273, 273);
    bt = btree_insert(bt, 152, 665);
    bt = btree_insert(bt, 726, 678);
    bt = btree_insert(bt, 592, 230);
    bt = btree_insert(bt, 124, 292);
    bt = btree_insert(bt, 98, 643);
    bt = btree_insert(bt, 841, 259);
    bt = btree_insert(bt, 924, 415);
    bt = btree_insert(bt, 21, 724);
    bt = btree_insert(bt, 444, 370);
    bt = btree_insert(bt, 17, 165);
    bt = btree_insert(bt, 754, 699);
    bt = btree_insert(bt, 626, 236);
    bt = btree_insert(bt, 72, 437);
    bt = btree_insert(bt, 197, 677);
    bt = btree_insert(bt, 258, 5);
    bt = btree_insert(bt, 733, 901);
    bt = btree_insert(bt, 783, 320);
    bt = btree_insert(bt, 362, 554);
    bt = btree_insert(bt, 535, 544);
    bt = btree_insert(bt, 338, 403);
    bt = btree_insert(bt, 323, 942);
    bt = btree_insert(bt, 636, 311);
    bt = btree_insert(bt, 117, 753);
    bt = btree_insert(bt, 342, 375);
    bt = btree_insert(bt, 730, 948);
    bt = btree_insert(bt, 916, 724);
    bt = btree_insert(bt, 509, 449);
    bt = btree_insert(bt, 125, 370);
    bt = btree_insert(bt, 813, 397);
    bt = btree_insert(bt, 368, 156);
    bt = btree_insert(bt, 791, 82);
    bt = btree_insert(bt, 196, 520);
    bt = btree_insert(bt, 27, 381);
    bt = btree_insert(bt, 29, 201);
    bt = btree_insert(bt, 68, 894);
    bt = btree_insert(bt, 943, 160);
    bt = btree_insert(bt, 518, 684);
    bt = btree_insert(bt, 602, 592);
    bt = btree_insert(bt, 199, 257);
    bt = btree_insert(bt, 719, 504);
    bt = btree_insert(bt, 287, 277);
    bt = btree_insert(bt, 44, 148);
    bt = btree_insert(bt, 198, 39);
    bt = btree_insert(bt, 902, 119);
    bt = btree_insert(bt, 705, 547);
    bt = btree_insert(bt, 183, 383);
    bt = btree_insert(bt, 76, 664);
    bt = btree_insert(bt, 790, 588);
    bt = btree_insert(bt, 30, 750);
    bt = btree_insert(bt, 740, 228);
    bt = btree_insert(bt, 74, 454);
    bt = btree_insert(bt, 810, 503);
    bt = btree_insert(bt, 598, 736);
    bt = btree_insert(bt, 443, 175);
    bt = btree_insert(bt, 895, 666);
    bt = btree_insert(bt, 738, 119);
    bt = btree_insert(bt, 772, 95);
    bt = btree_insert(bt, 248, 623);
    bt = btree_insert(bt, 530, 366);
    bt = btree_insert(bt, 713, 527);
    bt = btree_insert(bt, 353, 783);
    bt = btree_insert(bt, 670, 455);
    bt = btree_insert(bt, 19, 586);
    bt = btree_insert(bt, 224, 620);
    bt = btree_insert(bt, 209, 822);
    bt = btree_insert(bt, 638, 153);
    bt = btree_insert(bt, 56, 922);
    bt = btree_insert(bt, 420, 332);
    bt = btree_insert(bt, 208, 845);
    bt = btree_insert(bt, 365, 514);
    bt = btree_insert(bt, 425, 241);
    bt = btree_insert(bt, 693, 417);
    bt = btree_insert(bt, 888, 637);
    bt = btree_insert(bt, 890, 270);
    bt = btree_insert(bt, 678, 23);
    bt = btree_insert(bt, 275, 697);
    bt = btree_insert(bt, 516, 769);
    bt = btree_insert(bt, 533, 394);
    bt = btree_insert(bt, 341, 820);
    bt = btree_insert(bt, 336, 644);
    bt = btree_insert(bt, 520, 911);
    bt = btree_insert(bt, 923, 344);
    bt = btree_insert(bt, 174, 925);
    bt = btree_insert(bt, 421, 496);

    bt = btree_delete(bt, 825);
    bt = btree_delete(bt, 330);
    bt = btree_delete(bt, 582);
    bt = btree_delete(bt, 26);
    bt = btree_delete(bt, 612);
    bt = btree_delete(bt, 904);
    bt = btree_delete(bt, 94);
    bt = btree_delete(bt, 231);
    bt = btree_delete(bt, 959);
    bt = btree_delete(bt, 767);
    bt = btree_delete(bt, 322);
    bt = btree_delete(bt, 601);
    bt = btree_delete(bt, 867);
    bt = btree_delete(bt, 153);
    bt = btree_delete(bt, 389);
    bt = btree_delete(bt, 273);
    bt = btree_delete(bt, 152);
    bt = btree_delete(bt, 726);
    bt = btree_delete(bt, 592);
    bt = btree_delete(bt, 124);
    bt = btree_delete(bt, 98);
    bt = btree_delete(bt, 841);
    bt = btree_delete(bt, 924);
    bt = btree_delete(bt, 21);
    bt = btree_delete(bt, 444);
    bt = btree_delete(bt, 17);
    bt = btree_delete(bt, 754);
    bt = btree_delete(bt, 626);
    bt = btree_delete(bt, 72);
    bt = btree_delete(bt, 197);
    bt = btree_delete(bt, 258);
    bt = btree_delete(bt, 733);
    bt = btree_delete(bt, 783);
    bt = btree_delete(bt, 362);
    bt = btree_delete(bt, 535);
    bt = btree_delete(bt, 338);
    bt = btree_delete(bt, 323);
    bt = btree_delete(bt, 636);
    bt = btree_delete(bt, 117);
    bt = btree_delete(bt, 342);
    bt = btree_delete(bt, 730);
    bt = btree_delete(bt, 916);
    bt = btree_delete(bt, 509);
    bt = btree_delete(bt, 125);
    bt = btree_delete(bt, 813);
    bt = btree_delete(bt, 368);
    bt = btree_delete(bt, 791);
    bt = btree_delete(bt, 196);
    bt = btree_delete(bt, 27);
    bt = btree_delete(bt, 29);
    bt = btree_delete(bt, 68);
    
    // bt = btree_delete(bt, 943);

    /*bt = btree_delete(bt, 518);
    bt = btree_delete(bt, 602);
    bt = btree_delete(bt, 199);
    bt = btree_delete(bt, 719);
    bt = btree_delete(bt, 287);
    bt = btree_delete(bt, 44);
    bt = btree_delete(bt, 198);
    bt = btree_delete(bt, 902);
    bt = btree_delete(bt, 705);
    bt = btree_delete(bt, 183);
    bt = btree_delete(bt, 76);
    bt = btree_delete(bt, 790);
    bt = btree_delete(bt, 30);
    bt = btree_delete(bt, 740);
    bt = btree_delete(bt, 74);
    bt = btree_delete(bt, 810);
    bt = btree_delete(bt, 598);
    bt = btree_delete(bt, 443);
    bt = btree_delete(bt, 895);
    bt = btree_delete(bt, 738);
    bt = btree_delete(bt, 772);
    bt = btree_delete(bt, 248);
    bt = btree_delete(bt, 530);
    bt = btree_delete(bt, 713);
    bt = btree_delete(bt, 353);
    bt = btree_delete(bt, 670);
    bt = btree_delete(bt, 19);
    bt = btree_delete(bt, 224);
    bt = btree_delete(bt, 209);
    bt = btree_delete(bt, 638);
    bt = btree_delete(bt, 56);
    bt = btree_delete(bt, 420);
    bt = btree_delete(bt, 208);
    bt = btree_delete(bt, 365);
    bt = btree_delete(bt, 425);
    bt = btree_delete(bt, 693);
    bt = btree_delete(bt, 888);
    bt = btree_delete(bt, 890);
    bt = btree_delete(bt, 678);
    bt = btree_delete(bt, 275);
    bt = btree_delete(bt, 516);
    bt = btree_delete(bt, 533);
    bt = btree_delete(bt, 341);
    bt = btree_delete(bt, 336);
    bt = btree_delete(bt, 520);
    bt = btree_delete(bt, 923);
    bt = btree_delete(bt, 174);
    bt = btree_delete(bt, 421);*/

    btree_print(bt);

    btree_free(bt);

    return 0;
}
