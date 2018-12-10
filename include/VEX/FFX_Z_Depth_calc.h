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

vector nearp = point(1, "P", 0);
vector farp = point(1, "P", 1);
vector camp = point(2, "P", 0);
float fard = distance(farp, camp);
float neard = distance(nearp, camp);

float d = distance(@P, camp);
d = clamp(d, neard, fard);
float ndist = fit(d, neard, fard, 0, 1);

// Lets output the Normalized distance.
@density = ndist;