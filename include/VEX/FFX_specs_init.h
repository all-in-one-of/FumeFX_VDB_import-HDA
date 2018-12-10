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

float voxel = detail(2, "Spacing", 0);
vector tmp_N0 = volumeindexorigin(0, 0);
vector tmp_Nmax = volumeres(1, 0);
vector tmp_N = volumeres(0, 0);

v@N0 = set(tmp_N0.x, tmp_N0.z, tmp_N0.y);
v@tmp_N = set(tmp_N.x, tmp_N.z, tmp_N.y);
v@Nmax = set(tmp_Nmax.x, tmp_Nmax.z, tmp_Nmax.y);

v@L = set(voxel * tmp_N.x, voxel * tmp_N.z, voxel * tmp_N.y);
v@Lmax = set(voxel * tmp_Nmax.x, voxel * tmp_Nmax.z, voxel * tmp_Nmax.y);

i@Step = (int)@Frame;
i@NSimCount = 0;
i@NumSubFramesForCache = 1;

int file_voxel_count = (int)(v@tmp_N.x * v@tmp_N.z * v@tmp_N.y);
setattrib(0, "prim", "file_voxel_count", 0, 0, file_voxel_count, "set");
