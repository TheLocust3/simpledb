#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(613, 542);
    engine_insert(537, 139);
    engine_insert(323, 634);
    engine_insert(298, 103);
    engine_insert(41, 719);
    engine_insert(533, 630);
    engine_insert(688, 344);
    engine_insert(413, 896);
    engine_insert(550, 808);
    engine_insert(760, 396);
    engine_insert(244, 379);
    engine_insert(282, 415);
    engine_insert(595, 23);
    engine_insert(544, 3);
    engine_insert(459, 109);
    engine_insert(66, 347);
    engine_insert(947, 483);
    engine_insert(381, 554);
    engine_insert(966, 134);
    engine_insert(109, 413);
    engine_insert(1, 609);
    engine_insert(766, 30);
    engine_insert(681, 413);
    engine_insert(268, 930);
    engine_insert(438, 996);
    engine_insert(331, 324);
    engine_insert(733, 241);
    engine_insert(555, 381);
    engine_insert(911, 703);
    engine_insert(943, 343);
    engine_insert(639, 147);
    engine_insert(113, 625);
    engine_insert(585, 583);
    engine_insert(705, 935);
    engine_insert(27, 724);
    engine_insert(674, 838);
    engine_insert(390, 870);
    engine_insert(782, 631);
    engine_insert(299, 546);
    engine_insert(924, 505);
    engine_insert(24, 699);
    engine_insert(987, 65);
    engine_insert(355, 689);
    engine_insert(407, 15);
    engine_insert(84, 162);
    engine_insert(163, 345);
    engine_insert(738, 737);
    engine_insert(661, 120);
    engine_insert(732, 247);
    engine_insert(448, 382);
    engine_insert(792, 504);
    engine_insert(16, 320);
    engine_insert(687, 919);
    engine_insert(360, 898);
    engine_insert(573, 853);
    engine_insert(270, 217);
    engine_insert(129, 479);
    engine_insert(980, 518);
    engine_insert(917, 518);
    engine_insert(256, 290);
    engine_insert(353, 51);
    engine_insert(154, 635);
    engine_insert(428, 347);
    engine_insert(398, 332);
    engine_insert(105, 267);
    engine_insert(883, 931);
    engine_insert(867, 432);
    engine_insert(588, 89);
    engine_insert(852, 143);
    engine_insert(208, 642);
    engine_insert(221, 690);
    engine_insert(272, 518);
    engine_insert(986, 242);
    engine_insert(636, 81);
    engine_insert(86, 677);
    engine_insert(263, 920);
    engine_insert(475, 247);
    engine_insert(258, 418);
    engine_insert(691, 693);
    engine_insert(251, 762);
    engine_insert(466, 230);
    engine_insert(553, 195);
    engine_insert(32, 527);
    engine_insert(194, 739);
    engine_insert(556, 504);
    engine_insert(873, 463);
    engine_insert(648, 550);
    engine_insert(316, 944);
    engine_insert(813, 489);
    engine_insert(394, 727);
    engine_insert(346, 132);
    engine_insert(601, 549);
    engine_insert(231, 415);
    engine_insert(122, 362);
    engine_insert(63, 523);
    engine_insert(10, 275);
    engine_insert(425, 159);
    engine_insert(845, 992);
    engine_insert(65, 867);
    engine_insert(896, 459);

    engine_delete(613);
    engine_delete(537);
    engine_delete(323);
    engine_delete(298);
    engine_delete(41);
    engine_delete(533);
    engine_delete(688);
    engine_delete(413);
    engine_delete(550);
    engine_delete(760);
    engine_delete(244);
    engine_delete(282);
    engine_delete(595);
    engine_delete(544);

    engine_delete(459);
    engine_delete(66);
    engine_delete(947);
    
    engine_dump();

    engine_stop();

    return 0;
}
