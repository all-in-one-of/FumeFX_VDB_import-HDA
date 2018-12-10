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

vector center_from_NDC = set(0.5, 0.5, -1);
vector cam_center = fromNDC(chs("cam"), center_from_NDC);
vector cam_pos = point(1, "P", 0);
vector cam_dir = normalize(cam_pos - cam_center);

vector px = fromNDC(chs("cam"), set(1, 0.5, -1));
vector py = fromNDC(chs("cam"), set(0.5, 1, -1));
vector pz = cam_center + cam_dir;
vector x = normalize(px - cam_center);
vector y = normalize(py - cam_center);
vector z = normalize(pz - cam_center);
matrix3 m3 = set(x, y, z);
@orient = quaternion(m3);

vector near_pos = cam_pos - (cam_dir * chf("near"));
vector far_pos = cam_pos - (cam_dir * chf("far"));
int near = addpoint(0, near_pos);
int far = addpoint(0, far_pos);

float n_pscale = distance(cam_pos, near_pos);
float f_pscale = distance(cam_pos, far_pos);
setpointattrib(0, "orient", near, @orient, "set");
setpointattrib(0, "Cd", near, {1,0,0}, "set");
setpointattrib(0, "pscale", near, (float)0.19 * n_pscale, "set");
setpointattrib(0, "orient", far, @orient, "set");
setpointattrib(0, "Cd", far, {0,1,1}, "set");
setpointattrib(0, "pscale", far, (float)0.22 * f_pscale, "set");