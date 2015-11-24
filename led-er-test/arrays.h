/* min = 0, max = 65535, steps = 400 */
uint16_t smooth65535_400[400] = { 0,1,4,11,19,30,43,59,77,98,120,145,173,203,235,269,306,345,386,429,475,
522,572,625,679,735,794,855,918,983,1050,1119,1191,1264,1339,1417,1496,1578,1661,1747,1834,
1924,2015,2109,2204,2301,2400,2501,2604,2709,2815,2924,3034,3146,3260,3376,3493,3613,3734,3856,3981,
4107,4235,4364,4496,4629,4763,4900,5037,5177,5318,5461,5605,5751,5898,6047,6198,6350,6504,6659,6815,
6973,7133,7294,7456,7620,7785,7952,8120,8289,8460,8632,8805,8980,9156,9333,9512,9692,9873,10056,10239,
10424,10610,10798,10986,11176,11367,11559,11752,11946,12142,12338,12536,12735,12935,13135,13337,13540,13744,13949,14155,
14362,14570,14779,14989,15199,15411,15623,15837,16051,16267,16483,16700,16917,17136,17355,17575,17796,18018,18241,18464,
18688,18913,19138,19364,19591,19819,20047,20276,20505,20735,20966,21197,21429,21662,21895,22128,22362,22597,22832,23068,
23304,23541,23778,24015,24253,24492,24731,24970,25210,25450,25690,25931,26172,26413,26655,26897,27140,27382,27625,27868,
28112,28355,28599,28843,29088,29332,29577,29821,30066,30311,30557,30802,31047,31293,31538,31784,32030,32276,32521,32767,
33013,33258,33504,33750,33996,34241,34487,34732,34977,35223,35468,35713,35957,36202,36446,36691,36935,37179,37422,37666,
37909,38152,38394,38637,38879,39121,39362,39603,39844,40084,40324,40564,40803,41042,41281,41519,41756,41993,42230,42466,
42702,42937,43172,43406,43639,43872,44105,44337,44568,44799,45029,45258,45487,45715,45943,46170,46396,46621,46846,47070,
47293,47516,47738,47959,48179,48398,48617,48834,49051,49267,49483,49697,49911,50123,50335,50545,50755,50964,51172,51379,
51585,51790,51994,52197,52399,52599,52799,52998,53196,53392,53588,53782,53975,54167,54358,54548,54736,54924,55110,55295,
55478,55661,55842,56022,56201,56378,56554,56729,56902,57074,57245,57414,57582,57749,57914,58078,58240,58401,58561,58719,
58875,59030,59184,59336,59487,59636,59783,59929,60073,60216,60357,60497,60634,60771,60905,61038,61170,61299,61427,61553,
61678,61800,61921,62041,62158,62274,62388,62500,62610,62719,62825,62930,63033,63134,63233,63330,63425,63519,63610,63700,
63787,63873,63956,64038,64117,64195,64270,64343,64415,64484,64551,64616,64679,64740,64799,64855,64909,64962,65012,65059,
65105,65148,65189,65228,65265,65299,65331,65361,65389,65414,65436,65457,65475,65491,65504,65515,65523,65530,65533 };

/* min = 0, max = 65535, steps = 200 */
uint16_t smooth65535_200[200] = { 0,4,19,43,77,120,173,235,306,386,475,572,679,794,918,1050,1191,1339,1496,1661,1834,
2015,2204,2400,2604,2815,3034,3260,3493,3734,3981,4235,4496,4763,5037,5318,5605,5898,6198,6504,6815,
7133,7456,7785,8120,8460,8805,9156,9512,9873,10239,10610,10986,11367,11752,12142,12536,12935,13337,13744,14155,
14570,14989,15411,15837,16267,16700,17136,17575,18018,18464,18913,19364,19819,20276,20735,21197,21662,22128,22597,23068,
23541,24015,24492,24970,25450,25931,26413,26897,27382,27868,28355,28843,29332,29821,30311,30802,31293,31784,32276,32767,
33258,33750,34241,34732,35223,35713,36202,36691,37179,37666,38152,38637,39121,39603,40084,40564,41042,41519,41993,42466,
42937,43406,43872,44337,44799,45258,45715,46170,46621,47070,47516,47959,48398,48834,49267,49697,50123,50545,50964,51379,
51790,52197,52599,52998,53392,53782,54167,54548,54924,55295,55661,56022,56378,56729,57074,57414,57749,58078,58401,58719,
59030,59336,59636,59929,60216,60497,60771,61038,61299,61553,61800,62041,62274,62500,62719,62930,63134,63330,63519,63700,
63873,64038,64195,64343,64484,64616,64740,64855,64962,65059,65148,65228,65299,65361,65414,65457,65491,65515,65530 };

/* min = 0, max = 65535, steps = 100 */
uint16_t smooth65535_100[100] = { 0,19,77,173,306,475,679,918,1191,1496,1834,2204,2604,3034,3493,3981,4496,5037,5605,6198,6815,
7456,8120,8805,9512,10239,10986,11752,12536,13337,14155,14989,15837,16700,17575,18464,19364,20276,21197,22128,23068,
24015,24970,25931,26897,27868,28843,29821,30802,31784,32767,33750,34732,35713,36691,37666,38637,39603,40564,41519,42466,
43406,44337,45258,46170,47070,47959,48834,49697,50545,51379,52197,52998,53782,54548,55295,56022,56729,57414,58078,58719,
59336,59929,60497,61038,61553,62041,62500,62930,63330,63700,64038,64343,64616,64855,65059,65228,65361,65457,65515 };

/* min = 0, max = 32767, steps = 400 */
uint16_t smooth32767_400[400] = { 0,0,2,5,9,15,21,29,38,49,60,72,86,101,117,134,153,172,193,214,237,
261,286,312,339,367,397,427,459,491,525,559,595,632,669,708,748,789,830,873,917,
962,1007,1054,1102,1150,1200,1250,1302,1354,1407,1462,1517,1573,1630,1688,1746,1806,1866,1928,1990,
2053,2117,2182,2248,2314,2381,2449,2518,2588,2659,2730,2802,2875,2949,3023,3099,3175,3251,3329,3407,
3486,3566,3646,3728,3810,3892,3975,4059,4144,4230,4316,4402,4490,4578,4666,4756,4846,4936,5027,5119,
5212,5305,5399,5493,5588,5683,5779,5876,5973,6071,6169,6268,6367,6467,6567,6668,6770,6872,6974,7077,
7181,7285,7389,7494,7599,7705,7811,7918,8025,8133,8241,8349,8458,8568,8677,8787,8898,9009,9120,9232,
9344,9456,9569,9682,9795,9909,10023,10137,10252,10367,10483,10598,10714,10830,10947,11064,11181,11298,11416,11533,
11652,11770,11888,12007,12126,12245,12365,12485,12604,12724,12845,12965,13085,13206,13327,13448,13569,13691,13812,13934,
14055,14177,14299,14421,14543,14666,14788,14910,15033,15155,15278,15401,15523,15646,15769,15892,16014,16137,16260,16383,
16506,16629,16752,16874,16997,17120,17243,17365,17488,17611,17733,17856,17978,18100,18223,18345,18467,18589,18711,18832,
18954,19075,19197,19318,19439,19560,19681,19801,19921,20042,20162,20281,20401,20521,20640,20759,20878,20996,21114,21233,
21350,21468,21585,21702,21819,21936,22052,22168,22283,22399,22514,22629,22743,22857,22971,23084,23197,23310,23422,23534,
23646,23757,23868,23979,24089,24198,24308,24417,24525,24633,24741,24848,24955,25061,25167,25272,25377,25481,25585,25689,
25792,25894,25996,26098,26199,26299,26399,26498,26597,26695,26793,26890,26987,27083,27178,27273,27367,27461,27554,27647,
27739,27830,27920,28010,28100,28188,28276,28364,28450,28536,28622,28707,28791,28874,28956,29038,29120,29200,29280,29359,
29437,29515,29591,29667,29743,29817,29891,29964,30036,30107,30178,30248,30317,30385,30452,30518,30584,30649,30713,30776,
30838,30900,30960,31020,31078,31136,31193,31249,31304,31359,31412,31464,31516,31566,31616,31664,31712,31759,31804,31849,
31893,31936,31977,32018,32058,32097,32134,32171,32207,32241,32275,32307,32339,32369,32399,32427,32454,32480,32505,32529,
32552,32573,32594,32613,32632,32649,32665,32680,32694,32706,32717,32728,32737,32745,32751,32757,32761,32764,32766 };

/* min = 0, max = 32767, steps = 200 */
uint16_t smooth32767_200[200] = { 0,2,9,21,38,60,86,117,153,193,237,286,339,397,459,525,595,669,748,830,917,
1007,1102,1200,1302,1407,1517,1630,1746,1866,1990,2117,2248,2381,2518,2659,2802,2949,3099,3251,3407,
3566,3728,3892,4059,4230,4402,4578,4756,4936,5119,5305,5493,5683,5876,6071,6268,6467,6668,6872,7077,
7285,7494,7705,7918,8133,8349,8568,8787,9009,9232,9456,9682,9909,10137,10367,10598,10830,11064,11298,11533,
11770,12007,12245,12485,12724,12965,13206,13448,13691,13934,14177,14421,14666,14910,15155,15401,15646,15892,16137,16383,
16629,16874,17120,17365,17611,17856,18100,18345,18589,18832,19075,19318,19560,19801,20042,20281,20521,20759,20996,21233,
21468,21702,21936,22168,22399,22629,22857,23084,23310,23534,23757,23979,24198,24417,24633,24848,25061,25272,25481,25689,
25894,26098,26299,26498,26695,26890,27083,27273,27461,27647,27830,28010,28188,28364,28536,28707,28874,29038,29200,29359,
29515,29667,29817,29964,30107,30248,30385,30518,30649,30776,30900,31020,31136,31249,31359,31464,31566,31664,31759,31849,
31936,32018,32097,32171,32241,32307,32369,32427,32480,32529,32573,32613,32649,32680,32706,32728,32745,32757,32764 };

/* min = 0, max = 32767, steps = 100 */
uint16_t smooth32767_100[100] = { 0,9,38,86,153,237,339,459,595,748,917,1102,1302,1517,1746,1990,2248,2518,2802,3099,3407,
3728,4059,4402,4756,5119,5493,5876,6268,6668,7077,7494,7918,8349,8787,9232,9682,10137,10598,11064,11533,
12007,12485,12965,13448,13934,14421,14910,15401,15892,16383,16874,17365,17856,18345,18832,19318,19801,20281,20759,21233,
21702,22168,22629,23084,23534,23979,24417,24848,25272,25689,26098,26498,26890,27273,27647,28010,28364,28707,29038,29359,
29667,29964,30248,30518,30776,31020,31249,31464,31664,31849,32018,32171,32307,32427,32529,32613,32680,32728,32757 };
