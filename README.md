# FFX import HDA for SideFX Houdini 16.5.x to 17.x.x
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_WELCOME.jpg)

FFX_import is a SideFX Houdini HDA to work with FumeFX caches inside Houdini in an easy and fun way. It works like "DOP import fields" node does for Pyro but instead of referencing a live DOP it will operate on simulation VDB caches done with FumeFX v5 and up. It will also give you the ability to quickly export a set of AOVs new vdb caches to load them back into 3DSMax ▸ FumeFX in one click.

FumeFX import was born during the production of this clip:
https://vimeo.com/264618048

Check the making of also:
https://vimeo.com/268214826

# Features List

- FFX_import HDA it’s FREE!
- UI inspired and designed with FumFX UI in mind.
- UI live FumeFX grid informations available at any time.
- UI Dynamically load and unload parameters based on the input FumeFX VDB cache selected.
- FumeFX Fields/Channels import selection.
- FumeFX Fields/Channels auto rename to follow the common Houdini nameing convention.
- Check for missing vector fields components. (Velocities wint only X or Colors with only R and G…)
- Load VDB caches as Fields or as BBOX for fast bounding preview.
- Load FumeFX Sub Frames if exported. (Check "Save Sub Frames" in the FumeFX simulation tab)
- Load NSims all at once. You must have saved all of them into the same folder (This include sub frames for each of them if they     have been exported. The Load sub frames option must be enabled). The tool is smart enough to check witch one of the caches present in the selected folder belong to an NSim and witch one does not.
- NSIM as ONE convert all NSims caches into one and prepare it to succesfully load it back into FumeFX if you desire so.
- Live Z-Depth manipulation for artistic control on the output values.
- String auto formatting and simple errors checking anywhere you can input either a field name, a prefix or a filename.
- Automated output file system and file naming. Just focus on crafting your work as quick as possible.

The following feature make use of the Automated output filesystem.
- Export a Normals/Positions/Z-Depth Field in one click to load it back into 3DSMax ▸ FumeFX or Maya ▸ FumeFX and render it with your scene.

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx.jpg)
`Image generated with FumeFX v5.0.2`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_powered_by.jpg)
`FFX import HDA as been almost entirely coded using HOM python and VEX`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_001.jpg)
`FFX import inside Houdini UI interface`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_002.jpg)
`FFX import HDA first level content`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_003.jpg)
`FFX import HDA Studio Network`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_004.jpg)
`FFX import HDA Studio Network :: Loading mechanism. Every FumeFX features: Single VDB Cache Sequence, SubFrames and NSim,
have been worked out separatly inside their proper SubNetwork. Every one its aware of each other to perform live feedback on the UI based on the user choises.`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_005.jpg)
`FFX import HDA come with a nice Help/Documentation. It does include also live web link to the online FumeFX documentation
anywhere a close correspondence of the feature you are using in order to set it correctly inside FumeFX to make it work.`
