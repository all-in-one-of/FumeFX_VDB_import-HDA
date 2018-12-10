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
        
            // Time marks
            int startframe = detailattrib(0, concat("FFXNSIMSTARTframe", itoa(i)), 0, 1);
            int endframe = detailattrib(0, concat("FFXNSIMENDframe", itoa(i)), 0, 1);
            int endsubframe = detailattrib(0, concat("FFXNSIMENDsubframe", itoa(i)), 0, 1);
            
            // filenames
            string in_ss[] = detailattrib(0, concat("FFXNSIMVDBsubframeArray", itoa(i)), 0, 1);
            string in_int[] = detailattrib(0, concat("FFXNSIMVDBintframeArray", itoa(i)), 0, 1);
            
            // Lets do SS first
            if(chi("doss")){
                if(@Frame>=startframe && @Frame<=endsubframe)
                    setdetailattrib(0, concat("FFXNSIMVDBsubframe", itoa(i)), in_ss[int(@Frame)-startframe], "set");
                else
                    setdetailattrib(0, concat("FFXNSIMVDBsubframe", itoa(i)), "", "set");
                }
               
            // ..then int
            else if(chi("doss")==0){
                if(@Frame>=startframe && @Frame<=endframe)
                    setdetailattrib(0, concat("FFXNSIMVDBintframe", itoa(i)), in_int[int(@Frame)-startframe], "set");
                else
                    setdetailattrib(0, concat("FFXNSIMVDBintframe", itoa(i)), "", "set");
                }
                
            // ..then ref
            if(i==0){
                if(@Frame>=startframe && @Frame<=endframe)
                    setdetailattrib(0, concat("FFXNSIMVDBrefloadedint", itoa(i)), in_int[int(@Frame)-startframe], "set");
                else
                    setdetailattrib(0, concat("FFXNSIMVDBrefloadedint", itoa(i)), "", "set");
                }
            }
        }
    }