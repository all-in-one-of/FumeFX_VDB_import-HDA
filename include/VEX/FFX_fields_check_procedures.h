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

#include <file.h>

// FFX VDB in
string ffxvdbin = chs("ffxvdbin");

if(strlen(ffxvdbin)>0)
{
    // Current HDA name
    string HDAname = chs("hdaname");
        
    // NSIM ON/OFF
    int nsim = chi("nsim");
    int nsimcount = chi("nsimcount");

    // Fields counters
    int flg = 0;
    int smk = 0;
    int vel = 0;
    int tmp = 0;
    int ful = 0;
    int oxy = 0;
    int col = 0;
    int extWTP = 0;     // WTP stand for "Wavelet Turbulence PostProcess"
    int extFM = 0;      // FM stand for "Fluid Mapping"
    int hfe = 0;
    
    // Are the Vectors fields missing any of their 3 components?
    // XYZ or RGB. Lets mark them if so.
    int vel_check = 0;
    int col_check = 0;
    int extWTP_check = 0;
    int extFM_check = 0;
    
    // Fields name in the UI
    string ssmk = "smoke";
    string svel = "vel";
    string svel_missing = "vel_?";
    string stmp = "temp";
    string sful = "fire";
    string soxy = "oxy";
    string scol = "col";
    string scol_missing = "col_?";
    string sextWTP = "texWTP";
    string sextWTP_missing = "texWTP_?";
    string sextFM = "texFM";
    string sextFM_missing = "texFM_?";
    string shfe = "hfe";
    
    // Lets keep track of the fields count.
    int count = -1;
    
    // Lets count those fields
    int npt = npoints(0);
    for(int i = 0; i<npt; i++){
        string fields_name = getattrib(0, "prim", "name", i, 1);
    
        // FLAGS
        if(fields_name=="Flags")
            flg++;
    
        // SMOKE
        else if(fields_name=="Smoke"){
            smk++;
            if(smk==1)
                count++;
            }
    
        // VELOCITIES XYZ ( also check if any components are missing )
        else if(fields_name == "VelocitiesX" || fields_name == "VelocitiesY" || fields_name == "VelocitiesZ"){
            vel++;
            if(vel==3){
                count++;
                vel_check = 0;
                }
            if(vel<3 && vel_check==0){
                count++;
                vel_check=1;
                }
            }
    
        // TEMPERATURE
        else if(fields_name=="Temperature"){
            tmp++;
            if(tmp==1)
                count++;
            }
    
        // FIREFUEL
        else if(fields_name=="FireFuel"){
            ful++;
            if(ful==1)
                count++;
            }
    
        // OXYGEN
        else if(fields_name=="Oxygen"){
            oxy++;
            if(oxy==1)
                count++;
            }
    
        // COLORS RGB ( also check if any components are missing )
        else if(fields_name == "ColorR" || fields_name == "ColorG" || fields_name == "ColorB"){
            col++;
            if(col==3){
                count++;
                col_check = 0;
                }
            if(col<3 && col_check==0){
                count++;
                col_check=1;
                }
            }
    
         // TEXTURES WTP ( also check if any components are missing )
         else if(fields_name == "TextureX" || fields_name == "TextureY" || fields_name == "TextureZ"){
            extWTP++;
            if(extWTP==3){
                count++;
                extWTP_check = 0;
                }
            if(extWTP<3 && extWTP_check==0){
                count++;
                extWTP_check=1;
                }
            }
    
         // TEXTURES FM ( also check if any components are missing )
         else if(fields_name == "TextureBX" || fields_name == "TextureBY" || fields_name == "TextureBZ"){
            extFM++;
            if(extFM==3){
                count++;
                extFM_check = 0;
                }
            if(extFM<3 && extFM_check==0){
                count++;
                extFM_check=1;
                }
            }
    
        // HF ENERGY
        else if(fields_name == "HFenergy"){
            hfe++;
            if(hfe==1)
                count++;
            }
        }
    
    // Are there any fields into the loaded cache?
    int FFXIMPORT_active = 0;
    int validity_check = flg + smk + vel + tmp + ful + oxy + col + extWTP + extFM + hfe;
    if(validity_check>0 && validity_check==npoints(0))
        FFXIMPORT_active = 1;
    
    // Is there anything to merge ?
    int FFXVDBmerge = 0;
    if(vel == 3 || col == 3 || extWTP == 3 || extFM == 3)
        FFXVDBmerge = 1;
    
    // About box in grey because I like it more...
    int about = 0;
    
    // Lets output so the UI can read those values.
    i[]@FFXFIELDScount = array(flg, smk, vel, tmp, ful, oxy, col, extWTP, extFM, hfe, FFXIMPORT_active, FFXVDBmerge, about);
    
    // Do we have all we need?
    //
    // This is only for UI query service.
    //
    // In short, we are building a dynamically changing array
    // based on the fields found in the input VDB cache.
    // The array get built using an ordered list of fields
    // as we check them in a precise order.
    // This way the UI "data: display" always rearrange the VDB cache fields names
    // the same way no matter how many and witch one are present in the VDB file.
    // So for example if only Smoke and Colors are found,
    // the "UI data display" visualize their names one after the other
    // without having an empthy slot between the two.
    // Perhaps with Python this can be solved in a more elegant way.
    //
    string field_order[] = {};
    if(count>=0){
        if(smk==1)
            push(field_order, ssmk);
    
        if(vel>=1)
            if(vel_check)       // Something is missing...
                push(field_order, svel_missing);
            else if(vel==3)
                push(field_order, svel);
    
        if(tmp==1)
            push(field_order, stmp);
    
        if(ful==1)
            push(field_order, sful);
    
        if(oxy==1)
            push(field_order, soxy);
    
        if(col>=1)
            if(col_check)       // Something is missing...
                push(field_order, scol_missing);
            else if(col==3)
                push(field_order, scol);
    
        if(extWTP>=1)
            if(extWTP_check)    // Something is missing...
                push(field_order, sextWTP_missing);
            else if(extWTP==3)
                push(field_order, sextWTP);
                
        if(extFM>=1)
            if(extFM_check)     // Something is missing...
                push(field_order, sextFM_missing);
            else if(extFM==3)
                push(field_order, sextFM);
    
        if(hfe==1)
            push(field_order, shfe);
    }
    
    for(int i = 0; i <= count; i++){
        setpointattrib(0, "fname", i, field_order[i], "set");
        }
    
    // VDB Merge cases down the line.
    //
    // CASES for VEL and COL
    if(vel==0 && col==0){
        i@FFXVDB_check_A = -1;
        i@FFXVDB_merge_check_A = 3;
        }
    else if(vel==3 && col==0){
        i@FFXVDB_check_A = -1;
        i@FFXVDB_merge_check_A = -1;
        }
    else if(vel==0 && col==3){
        i@FFXVDB_check_A = -1;
        i@FFXVDB_merge_check_A = -1;
        }
    else if(vel==3 && col==3){
        i@FFXVDB_check_A = -1;
        i@FFXVDB_merge_check_A = -1;
        }
    else if(vel==3 && col==3)
        i@FFXVDB_merge_check_A = 0;
    else if(vel==3 && col<3)
        i@FFXVDB_merge_check_A = 1;
    else if(vel<3 && col==3)
        i@FFXVDB_merge_check_A = 2;
    else if(vel<3 && col<3)
        i@FFXVDB_merge_check_A = 3;
    else if(vel<3 && col==0)
        i@FFXVDB_merge_check_A = 3;
    else if(vel==0 && col<3)
        i@FFXVDB_merge_check_A = 3;
    //
    // CASES for texWTP and texFM
    if(extWTP==0 && extFM==0){
        i@FFXVDB_check_B = -1;
        i@FFXVDB_merge_check_B = 3;
        }
    else if(extWTP==3 && extFM==0){
        i@FFXVDB_check_B = -1;
        i@FFXVDB_merge_check_B = -1;
        }
    else if(extWTP==0 && extFM==3){
        i@FFXVDB_check_B = -1;
        i@FFXVDB_merge_check_B = -1;
        }
    else if(extWTP==3 && extFM==3){
        i@FFXVDB_check_B = -1;
        i@FFXVDB_merge_check_B = -1;
        }
    else if(extWTP==3 && extFM==3)
        i@FFXVDB_merge_check_B = 0;
    else if(extWTP==3 && extFM<3)
        i@FFXVDB_merge_check_B = 1;
    else if(extWTP<3 && extFM==3)
        i@FFXVDB_merge_check_B = 2;
    else if(extWTP<3 && extFM<3)
        i@FFXVDB_merge_check_B = 3;
    else if(extWTP<3 && extFM==0)
        i@FFXVDB_merge_check_B = 3;
    else if(extWTP==0 && extFM<3)
        i@FFXVDB_merge_check_B = 3;
    
    // If they are all existent
    if(vel==3 && col==3 && extWTP==3 && extFM==3){
        i@FFXVDB_check_A = -1;
        i@FFXVDB_check_B = -1;
        }
        
    // Warning messages so the user is aware of things.
    int file_exists(string name){
        return cached_file_stat(name)->isValid();
        }
    // Check if the vdb file exist on disk
    int file_exist = file_exists(ffxvdbin);
    
    // Check if the filename is correct ( Follow the FumeFX naming convention)
    // I do this from this wrangle because python does not always show the warning upstream.
    // Most likely becasue me not knowing the HOU and python well enough.
    //
    // Collect data for warnings
    //
    int subf = chi("subf");
    int FFXXISVALIDfilename = detail(1, "FFXISVALIDfilename", 0);
    int FFXSUBSAMPLEScheck = detail(1, "FFXSUBSAMPLEScheck", 0);
    int FFXSTARTsubframe = detail(1, "FFXSTARTsubframe", 0);
    int FFXENDsubframe = detail(1, "FFXENDsubframe", 0);
    int FFXENDframe = detail(1, "FFXENDframe", 0);
    int nossFFXSTARTframe = detail(2, "FFXSTARTframe", 0);
    int nossFFXENDframe = detail(2, "FFXENDframe", 0);
    int fields_num = npoints(0);
    // Initialize warning message variables and strings
    //
    string warning_vel = "";
    string warning_col = "";
    string warning_extWTP = "";
    string warning_extFM = "";
    string warning_invalidVDBfilename = "";
    string warning_somefields = "INFO: Not all fields in the loaded vdb file follow the FumeFX naming convention, but some does.";
    string warning_invalidVDB = concat("\n", HDAname, "::WARNING::\nYou are trying to load an invalid FumeFX vdb cache or the loaded vdb field's name do not follow the FumeFX channel's naming convention.");
    string warning_invalidVDB_suggestion = "TIP: Try to load the desired vdb file with a standard Houdini file node.";
    string warning_filenoexistent = concat("\n", HDAname, "::WARNING::\nThe currently loaded vdb file does not exist.");
    string warning_filenoexistent_tip_start = "TIP: You are yet to reach the START Frame: ";
    string warning_filenoexistent_tip_end = "TIP: You are past the END Frame: ";
    
    // Warning's conditions
    //
    if(vel==1)
        warning_vel = concat(HDAname, "::WARNING::\nVelocities(XYZ) has only", " ", itoa(vel), " ", "field instead of 3. ");
    else
        warning_vel = concat(HDAname, "::WARNING::\nVelocities(XYZ) has only", " ", itoa(vel), " ", "fields instead of 3. ");
    //
    if(col==1)
        warning_col = concat(HDAname, "::WARNING::\nColors(RGB) has only", " ", itoa(col), " ", "field instead of 3. ");
    else
        warning_col = concat(HDAname, "::WARNING::\nColors(RGB) has only", " ", itoa(col), " ", "fields instead of 3. ");
    //
    if(extWTP==1)
        warning_extWTP = concat(HDAname, "::WARNING::\nExtraDetailsWTP has only", " ", itoa(extWTP), " ", "field instead of 3. ");
    else
        warning_extWTP = concat(HDAname, "::WARNING::\nExtraDetailsWTP has only", " ", itoa(extWTP), " ", "fields instead of 3. ");
    //   
    if(extFM==1)
        warning_extFM = concat(HDAname, "::WARNING::\nExtraDetailsFM has only", " ", itoa(extFM), " ", "field instead of 3. ");
    else
        warning_extFM = concat(HDAname, "::WARNING::\nExtraDetailsFM has only", " ", itoa(extFM), " ", "fields instead of 3. ");
    //
    if(FFXXISVALIDfilename==0)
        warning_invalidVDBfilename = concat("\n", HDAname, "::WARNING::\nThe filename does not conform to the FumeFX file naming convention. An underscore \"_\" must be inbetween the filename and the file number.\nex: \nmy.new.explosion_0123.vdb");
        
        
    // Execute warnings
    //
    
    // Missing Velocities components
    if(vel>0 && vel<3)
        warning(warning_vel);
    //
    // Missing Colors components
    if(col>0 && col<3)
        warning(warning_col);
    //
    // Missing Wavelet components
    if(extWTP>0 && extWTP<3)
        warning(warning_extWTP);
    //
    // Missing FluidMapping components
    if(extFM>0 && extFM<3)
        warning(warning_extFM);
    //
    // File non existent
    if(file_exist==0 && strlen(ffxvdbin)>0 && FFXIMPORT_active==0)
        warning(warning_filenoexistent);
    //
    // SS OutOfRange past END frame
    if(file_exist==0 && strlen(ffxvdbin)>0 && FFXIMPORT_active==0 && FFXSUBSAMPLEScheck && nossFFXENDframe>0){
        if(subf==0){
            if(@Frame>nossFFXENDframe)
                warning(concat("Frames: ", warning_filenoexistent_tip_end, itoa(nossFFXENDframe)));
            }
        if(subf==1){
            if(@Frame>FFXENDsubframe)
                warning(concat("SubFrames: ", warning_filenoexistent_tip_end, itoa(FFXENDsubframe)));
            }
        }
    //
    // SS OutOfRange before START frame
    if(file_exist==0 && strlen(ffxvdbin)>0 && FFXIMPORT_active==0 && FFXSUBSAMPLEScheck && nossFFXSTARTframe!=0){
        if(subf==0){
            if(@Frame<nossFFXSTARTframe)
                warning(concat("Frames: ", warning_filenoexistent_tip_start, itoa(nossFFXSTARTframe)));
            }
        if(subf==1){
            if(@Frame<FFXSTARTsubframe)
                warning(concat("SubFrames: ", warning_filenoexistent_tip_start, itoa(FFXSTARTsubframe)));
            }
        }
    //
    // noSS OutOfRange past END frame
    if(file_exist==0 && strlen(ffxvdbin)>0 && FFXIMPORT_active==0 && FFXSUBSAMPLEScheck==0 && nossFFXENDframe>0){
        if(@Frame>nossFFXENDframe)
            warning(concat("Frames: ", warning_filenoexistent_tip_end, itoa(nossFFXENDframe)));
    }
    //
    // noSS OutOfRange before START frame
    if(file_exist==0 && strlen(ffxvdbin)>0 && FFXIMPORT_active==0 && FFXSUBSAMPLEScheck==0 && nossFFXSTARTframe!=0){
        if(@Frame<nossFFXSTARTframe)
            warning(concat("Frames: ", warning_filenoexistent_tip_start, itoa(nossFFXSTARTframe)));
    }
    
    // Invalid VDB ( no FumeFX naming convention or no valid vdb)
    if(file_exist && strlen(ffxvdbin)>0 && FFXIMPORT_active==0){
        warning(warning_invalidVDB);
        warning(warning_invalidVDB_suggestion);
        }
    // Some fields does follow the FumeFX naming convention
    // But some do not...
    if(file_exist && strlen(ffxvdbin)>0 && validity_check>0 && validity_check!=npoints(0)){
        warning(warning_somefields);
        }
    // Invalid VDB filename ( most likely no "_" underscore inbetween the filename and the filenumber)
    if(file_exist && strlen(ffxvdbin)>0 && FFXIMPORT_active==1 && FFXXISVALIDfilename==0)
        warning(warning_invalidVDBfilename);


    // is it part of an NSim?
    // Lets check and inform the user of the outcome
    int NSIMcount = detail(-1, "FFXNSIMcountcheck", 0);
    
    int isNSim = detail(0, "NSimCount", 0);
    int isNSim2 = detail(3, "NSimCount", 0);
    if(isNSim && NSIMcount==1)
        i@FFXNSIMcheck = 1;
    else if(npoints(0)==0){
        if(isNSim2 && NSIMcount==1)
            i@FFXNSIMcheck = 1;
        if(isNSim2 && NSIMcount==0)
            warning(HDAname+"::WARNING::\nYou loaded a FumeFX VDB cache that is part of an NSim but was not able to find the other NSim caches in the folder.");
        }
    else if(isNSim && NSIMcount==0)
        warning(HDAname+"::WARNING::\nYou loaded a FumeFX VDB cache that is part of an NSim but was not able to find the other NSim caches in the folder.");

}