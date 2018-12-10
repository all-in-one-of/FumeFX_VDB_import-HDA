// FFX_IMPORT v1.5
// SideFX Houdini OTL
//
// Author/Copyrights: Alessandro Nardini
// Email: alexnardini@gmail.com
// Creation date: 09th October 2018
//
// "FFX_import" is a little houdini OTL to work
// with FumeFX caches inside Houdini in an easy way.
// It works like "DOP import fields" node does for Pyro
// but instead of referencing a live DOP
// it will operate on simulation VDB caches
// done with FumeFX v5 and up.
//

//  it will generate incorrect values
//  if Too big. This should be good for all cases.
vector N0_maxmin = 1000000000;

// FLAGS
vector L_1 = detail(1, "L", 0);
vector N_1 = detail(1, "N", 0);

int i1pt = npoints(1);
int i1 = chi("flags");
vector N0_1 = N0_maxmin;
if(i1 && i1pt>0)
    N0_1 = detail(1, "N0", 0);

// SMOKE
vector L_2 = detail(2, "L", 0);
vector N_2 = detail(2, "N", 0);

int i2pt = npoints(2);
int i2 = chi("smoke");
vector N0_2 = N0_maxmin;
if(i2 && i2pt>0)
    N0_2 = detail(2, "N0", 0);

// VEL
vector L_3 = detail(3, "L", 0);
vector N_3 = detail(3, "N", 0);

int i3pt = npoints(3);
int i3 = chi("vel");
vector N0_3 = N0_maxmin;
if(i3 && i3pt>0)
    N0_3 = detail(3, "N0", 0);

// TMP
vector L_4 = detail(-1, "L", 0);
vector N_4 = detail(-1, "N", 0);

int i4pt = npoints(-1);
int i4 = chi("temp");
vector N0_4 = N0_maxmin;
if(i4 && i4pt>0)
    N0_4 = detail(-1, "N0", 0);

// FIRE
vector L_5 = detail(-2, "L", 0);
vector N_5 = detail(-2, "N", 0);

int i5pt = npoints(-2);
int i5 = chi("fire");
vector N0_5 = N0_maxmin;
if(i5 && i5pt>0)
    N0_5 = detail(-2, "N0", 0);

// OXY
vector L_6 = detail(-3, "L", 0);
vector N_6 = detail(-3, "N", 0);

int i6pt = npoints(-3);
int i6 = chi("oxy");
vector N0_6 = N0_maxmin;
if(i6 && i6pt>0)
    N0_6 = detail(-3, "N0", 0);

// COL
vector L_7 = detail(-4, "L", 0);
vector N_7 = detail(-4, "N", 0);

int i7pt = npoints(-4);
int i7 = chi("col");
vector N0_7 = N0_maxmin;
if(i7 && i7pt>0)
    N0_7 = detail(-4, "N0", 0);

// WTP
vector L_8 = detail(-5, "L", 0);
vector N_8 = detail(-5, "N", 0);

int i8pt = npoints(-5);
int i8 = chi("wtp");
vector N0_8 = N0_maxmin;
if(i8 && i8pt>0)
    N0_8 = detail(-5, "N0", 0);

// FM
vector L_9 = detail(-6, "L", 0);
vector N_9 = detail(-6, "N", 0);

int i9pt = npoints(-6);
int i9 = chi("fm");
vector N0_9 = N0_maxmin;
if(i9 && i9pt>0)
    N0_9 = detail(-6, "N0", 0);

// HFE
vector L_10 = detail(-7, "L", 0);
vector N_10 = detail(-7, "N", 0);

int i10pt = npoints(-7);
int i10 = chi("hfe");
vector N0_10 = N0_maxmin;
if(i10 && i10pt>0)
    N0_10 = detail(-7, "N0", 0);

// Calculate final ffx bounding grids values
vector L_max = max(L_1, L_2, L_3, L_4, L_5, L_6, L_7, L_8, L_9, L_10);
vector N_max = max(N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9, N_10);
vector N0_min = min(N0_1, N0_2, N0_3, N0_4, N0_5, N0_6, N0_7, N0_8, N0_9, N0_10);

// Lets output the new values
v@L = L_max;
v@N = N_max;
v@N0 = N0_min;
