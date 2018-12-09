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

vector bboxmax = getbbox_max(0);
vector bboxmin = getbbox_min(0);
v@file_bbox_max = set(bboxmax.x, bboxmax.y, bboxmax.z);
v@file_bbox_min = set(bboxmin.x, bboxmin.y, bboxmin.z);

@file_mem_bytes = primintrinsic(0, "memoryusage", @primnum);

setprimintrinsic(0, "vdb_creator", @primnum, "FumeFX", "set");
setprimintrinsic(0, "vdb_is_local_space", @primnum, 1, "set");
setprimintrinsic(0, "vdb_is_saved_as_half_float", @primnum, 1, "set");
