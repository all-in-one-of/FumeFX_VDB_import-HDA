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

if(detail(1, "FFXNSIMcountcheck", 0)){

    int nsimcount = detailattrib(0, "FFXNSIMcount", 0, 1);
    
    if(nsimcount>1){
        for(int i=0; i<detail(0, "FFXNSIMcount", 0); i++){
            adddetailattrib(0, concat("FFXNSIMVDBsubframe", itoa(i)), "");
            adddetailattrib(0, concat("FFXNSIMVDBintframe", itoa(i)), "");
        }
    }
}