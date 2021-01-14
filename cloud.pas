program cloud;

{$mode objfpc}
{$H+}
{$WARN 2005 off : Comment level $1 found}

{define gtk}
{define threading}
{define debug}

{define free}
{$define Xmacro}
{$define cloud}

uses {$ifdef threading}{$ifdef unix}cthreads,{$endif}process,{$endif}
     sysutils,liball,libfunction,libpara,{$ifdef Xmacro}libmacro_gui,{$else}libmacro,{$endif}libpo,libgene,
     libpoly,libqueue, libcloud,libmesh,
     libfile,
     libtransfer,libcanvas,libvector,
     gdk2,libgtk2;

{$include icon-symbols.inc}
{$include icon-files.inc}
{$include icon-sets.inc}
{$include icon-arrows.inc}

{include cloudsplash.inc}

type pfilehyper = ^tfilehyper;
     ppolynat = ^tpolynat;

var para : tparameter;
    macro_self : tmacro;
    list : tpolynat;
    full,small,table_long{xy,zt},table_wide{xy,zt},table_special{xy,xz,xt} : boolean;
    runmacro : utf16;
    runrefresh,runexit,runask : boolean;
    count,count2 : integer;
    s,t : utf16;

    pre_buf,new_buf,post_buf : utf16;
    stop_change : boolean = false;

var stat : array[1..6] of tpolyreal;
    cstat : array[1..6] of tpolycomplex;
    statname,statobjects : utf16;
    stattype : byte;

var     finput,finputedit : pcloud;
        {rgb_buf : pointer;}
        splash,window : gtk_widget;
	image,area_xy,area_xz,area_yz,area_xt,area_zt,area_shot,mainnote,bclear,blog,bopen,bcog,brun,bkill : gtk_widget;
        note : gtk_widget;
        subnote_data,subnote_new,subnote_editing,subnote_boolean,subnote_transform,subnote_calculate,subnote_show,subnote_mesh,subnote_loco,subnote_info : gtk_widget;
        subnote_macro,viewport,viewport1 : gtk_widget;
        {timeout_id : integer;}

        red_label,green_label,blue_label,yellow_label,cyan_label,purple_label : gtk_widget;
        red2_label,green2_label,blue2_label,yellow2_label,cyan2_label,purple2_label : gtk_widget;

        red_button,green_button,blue_button,yellow_button,cyan_button,purple_button : gtk_widget;
        red2_button,green2_button,blue2_button,yellow2_button,cyan2_button,purple2_button : gtk_widget;

        state : array[1..6] of boolean;
        ref_state : array[1..6] of boolean;

        dummy,red,green,blue,yellow,cyan,purple : tcloud;

const   macro_length = 5;

var     macro_text : array[0..macro_length] of gtk_textbuffer;
        macro_text_count : array[0..macro_length] of gtk_textbuffer;
        syntax : gtk_textbuffer;
        start,ende,marke1,marke2 : tgtk_iteration;
        macro_widget : array[0..macro_length] of gtk_widget;
        macro_widget_count : array[0..macro_length] of gtk_widget;
        macro_filename : array[0..macro_length] of utf16chars;
        macro_save : array[0..macro_length] of boolean;
        {$ifdef threading}macro_process : array[0..macro_length] of tprocess;{$endif}
        x : integer;

        ifdraw : boolean;
        fix_x : boolean = false;
        fix_y : boolean  = false;
        incnote : byte = 0; { counter for notes }
        incnote_sub : byte = 0; { counter for subnotes }
        datanote_file : byte;
        datanote_inscribe : byte;
        boolnote : byte;
        scriptnote : byte;

{ Input }
  { File }
        {bfile,bdir,}fileed,workdir : gtk_widget;
        toggle_punctuation,toggle_format,toggle_exponent,toggle_deg_rad,load_ignore,export_trackvis_toggle_olddim : gtk_widget;
        export_obj_tube_size,export_amira_step,import_pdb,export_blender : gtk_widget;
        export_trigger_value,export_trigger_centre : gtk_widget;
        import_febio_mask,import_febio_from_time,import_febio_to_time,import_febio_from_step,import_febio_to_step : gtk_widget;
        import_febio_raster : gtk_widget;
  { Clipboard }
        clipboard : gtk_textbuffer;
        data_clipboard_digits : gtk_widget;
  { Microscribe }
        label_microscribe_input,edit_microscribe_keyboard_sensitivity : gtk_widget;
        m3dlabel,m3dstat : gtk_widget;
        m3dstat1 : gtk_textbuffer;
        keyred,keygreen,keyblue,keyyellow,keycyan,keypurple,keynewline,keynewobject : hyper;
        import_begin,import_end : gtk_widget;
        import_header,import_index : gtk_widget;
        export_trackvis : gtk_widget;
        toggle_seq_empty : gtk_widget;
  { Polynom }
        polynom : array[0..9] of gtk_widget;
        input_polynom_method,label_polynom_status,polynom_begin,polynom_end,polynom_step : gtk_widget;

        formula_xbegin,formula_xend,formula_xstep,formula_radius,formula_pitch : gtk_widget;
        formula_normal,formula_point : gtk_widget;

        formula2_xbegin,formula2_xend,formula2_xstep : gtk_widget;
        formula2_ybegin,formula2_yend,formula2_ystep : gtk_widget;

        formula2_normal,formula2_point : gtk_widget;

        formula3_xbegin,formula3_xend,formula3_xstep : gtk_widget;
        formula3_ybegin,formula3_yend,formula3_ystep : gtk_widget;
        formula3_zbegin,formula3_zend,formula3_zstep : gtk_widget;

        formula4_xbegin,formula4_xend,formula4_xstep : gtk_widget;
        formula4_ybegin,formula4_yend,formula4_ystep : gtk_widget;
        formula4_zbegin,formula4_zend,formula4_zstep : gtk_widget;
        formula4_tbegin,formula4_tend,formula4_tstep : gtk_widget;

        formula3_vector,togglerandomvector3,formula4_vector,togglerandomvector4 : gtk_widget;
{ Edit }
        edit_erase_single_numbers,edit_erase_single_neighbors,edit_scale,edit_near_duplicates,edit_mean_near_duplicates,edit_near,edit_polynom_method : gtk_widget;
        edit_axis1,edit_axis2 : gtk_widget;
        edit_vectors_range,edit_assign_ranged : gtk_widget;
        editl,editlp : gtk_widget;
        edit_vectors_direction,edit_lines_direction : gtk_widget;
        edit_name_pattern,edit_name_to : gtk_widget;
{ Bool }
        bool_points_dimension_min,bool_points_dimension_max,bool_segments_dimension_min,bool_segments_dimension_max,bool_lines_dimension_min,bool_lines_dimension_max : gtk_widget;
        l_bool_object_left,l_bool_object_right : gtk_widget;
        l_bool_subobject_left_p,l_bool_subobject_right_p : gtk_widget;
        l_bool_subobject_left_s,l_bool_subobject_right_s : gtk_widget;
        l_bool_subobject_left_l,l_bool_subobject_right_l : gtk_widget;
        l_bool_subobject2_left_l,l_bool_subobject2_right_l : gtk_widget;
        l_bool_subobject_left_mesh,l_bool_subobject_right_mesh : gtk_widget;
        l_bool_subobject_left_o,l_bool_subobject_right_o : gtk_widget;
        l_bool_subobject2_left_o,l_bool_subobject2_right_o : gtk_widget;
        bool_line_materials_left,bool_line_materials_right : gtk_widget;
        bool_object_named : gtk_widget;
        label_status_point,label_status_vector,label_status_line,label_status_object : gtk_widget;
        label_status_point2,label_status_line2,label_status_object2 : gtk_widget;
        bool_radius, bool_random, bool_icircle, bool_irectangle, bool_ocircle, bool_orectangle : gtk_widget;
        label_status_object3 : gtk_widget;
{ Transform }
        transform_rotation,transform_move,transform_scale,transform_scale2,transform_grow : gtk_widget;
        transform_rotate,transform_vector,transform_vector1,transform_vector2,transform_step_center,transform_log_exp_base : gtk_widget;
        transform_effects_center,transform_effects_direction,transform_effects_fallout_angle : gtk_widget;
        transform_c,transform_x,transform_x2,transform_x3 : gtk_widget;
        transform_norm_min,transform_norm_max : gtk_widget;
        transform_cardan,transform_euler : gtk_widget;
        transform_matrix_set,transform_matrix_set2,transform_matrix_rotation : gtk_widget;
        transform_matrix_1_1,transform_matrix_2_1,transform_matrix_3_1,transform_matrix_4_1 : gtk_widget;
        transform_matrix_1_2,transform_matrix_2_2,transform_matrix_3_2,transform_matrix_4_2 : gtk_widget;
        transform_matrix_1_3,transform_matrix_2_3,transform_matrix_3_3,transform_matrix_4_3 : gtk_widget;
        transform_matrix_1_4,transform_matrix_2_4,transform_matrix_3_4,transform_matrix_4_4 : gtk_widget;
        transform_clipboard_digits,transform_det : gtk_widget;
{ Calculate }
        calculate_axis_raster_points,calculate_axis_raster_vectors,calculate_axis_raster_lines,calculate_axis_raster_objects : gtk_widget;
        calculate_smooth_lines_radian,calculate_smooth_lines_points,calculate_smooth_lines_steps,calculate_smooth_lines_steps_x,calculate_smooth_method : gtk_widget;
        calculate_lines_by_value,calculate_lines_by_spacing,calculate_lines_by_angle,calculate_lines_by_curvature,calculate_lines_by_torsion : gtk_widget;
        calculate_group_lines_angle,calculate_group_lines_vector,calculate_distance_points : gtk_widget;
        calculate_crease_points,calculate_crease_vectors,calculate_crease_lines : gtk_widget;
        calculate_crease_method_p,calculate_crease_method_v,calculate_crease_method_l : gtk_widget;
        group_nearest,calculate_polynom_method : gtk_widget;
        calculate_dimension_min,calculate_dimension_max,calculate_raster,calculate_raster_minpoints,raster_polynom : gtk_widget;
        group_origin,group_step,group_from,group_to : gtk_widget;
{ Mesh }
        mesh_raster,mesh_origin_hull,mesh_raster_hull,mesh_distance_hull,mesh_hull,discrete,cleanup_factor : gtk_widget;
        outside : gtk_widget;
        mesh_dimension_min,mesh_dimension_max : gtk_widget;
        fill_holes,erase_bumps,mesh_dilating,solids,shells : gtk_widget;
        mesh_smoothing,mesh_smoothing_outside,mesh_smooth : gtk_widget;
        fem_raster,febio_time_steps,febio_step_size : gtk_widget;
        febio_geometry,febio_fibre,febio_fibre_direction,febio_shell_thickness : gtk_widget;
        febio_ref_isotropic_material,febio_ref_anisotropic_material : gtk_widget;
        febio_ref_prescribe_attr,febio_ref_fixed_attr,febio_ref_force_attr : gtk_widget;
        febio_isotropic_material,febio_anisotropic_material,febio_prescribe,febio_fixed,febio_force,febio_pressure : gtk_widget;
        febio_prescribe_attr,febio_fixed_attr,febio_force_attr,febio_distance : gtk_widget;
        febio_version,febio_solver,febio_plot,febio_print,togglefebiooutput : gtk_widget;
        torque_force,mean_radius : gtk_widget;
{ Show }
        text_report : gtk_textbuffer;
        togglegrouped,geometry_groups,togglelog : gtk_widget;
        show_povray_group,show_povray_threshold,show_povray_steps,show_povray_steps2,show_povray_resolution,show_povray_range,show_polynom_method : gtk_widget;
        editred,editgreen,editblue,edityellow,editcyan,editpurple : gtk_widget;
        editredmap,editgreenmap,editbluemap,edityellowmap,editcyanmap,editpurplemap : gtk_widget;
        editredradius,editgreenradius,editblueradius,edityellowradius,editcyanradius,editpurpleradius : gtk_widget;
        toggleaxisx,toggleaxisy,toggleaxisz,toggleaxis,togglecamera1,togglecamera2,togglecamera3 : gtk_widget;
        togglesky1,togglesky2,show_povray_sky : gtk_widget;
        editsky1,editsky2,editaxis,show_povray_camera : gtk_widget;
        editlight,togglepointlights,togglespotlights,togglepointlight,togglespotlight,togglearealights : gtk_widget;
        toggleticks,editticks,show_povray_ticks,show_povray_ticks_size,toggleraster,editraster : gtk_widget;
        show_povray_objects,show_povray_raster,show_povray_min,show_povray_max : gtk_widget;
  { Status }
        redtext,greentext,bluetext,yellowtext,cyantext,purpletext,alltext,memtext : gtk_textbuffer;
        tomuch_points,toggle_points,toggle_points_all,toggle_vectors,toggle_vectors_arrows,toggle_lines,toggle_lines_arrows,toggle_loops,toggle_loops_separation : gtk_widget;
        backlight,list_point_style,toggle_point_style_light,toggle_realsize,toggle_border,toggle_colorreduction,borderlight : gtk_widget;
        list_color,map_color,state_color,list_shadow,list_contrast,list_axes,list_scale : gtk_widget;
        t_snapshot_xsize,t_snapshot_ysize : gtk_widget;
{ ---- }
        minall,maxall,min_red,max_red,min_green,max_green,min_blue,max_blue : hyper;
        min_yellow,max_yellow,min_cyan,max_cyan,min_purple,max_purple : hyper;
        centerall,center_red,center_green,center_blue,center_yellow,center_cyan,center_purple : hyper;
        screen_xy,screen_xz,screen_yz,screen_xt,screen_zt : trgba;
        screen_histo : thistogram;
        screen,input,inputedit,inputmethod,brush : byte;

        global_center : hyper = (x:0;y:0;z:0;t:0);
        global_zoom : real = 1;

        {                * x               * y               * z               * t }
        xy : matrix4 = ((x:1;y:0;z:0;t:0),(x:0;y:1;z:0;t:0),(x:0;y:0;z:1;t:0),(x:0;y:0;z:0;t:-1));
        xz : matrix4 = ((x:1;y:0;z:0;t:0),(x:0;y:0;z:-1;t:0),(x:0;y:1;z:0;t:0),(x:0;y:0;z:0;t:1));
        xt : matrix4 = ((x:1;y:0;z:0;t:0),(x:0;y:0;z:0;t:-1),(x:0;y:0;z:-1;t:0),(x:0;y:1;z:0;t:0));

        yz : matrix4 = ((x:0;y:0;z:1;t:0),(x:1;y:0;z:0;t:0),(x:0;y:1;z:0;t:0),(x:0;y:0;z:0;t:-1));
        zt : matrix4 = ((x:0;y:0;z:1;t:0),(x:0;y:0;z:0;t:-1),(x:1;y:0;z:0;t:0),(x:0;y:1;z:0;t:0));

        _tcm : tcolormap;

{ **************************************************************************** }

procedure proc_push_red (p1,macro : gtk_pointer); cdecl;
{var old : pcloud;}
begin

end;

{ **************************************************************************** }

procedure proc_none (p1,macro : gtk_pointer); cdecl;
begin
end;

function fastcalc (v : hyper;m : matrix4) : hyper;
begin
     if m[1].x = 1.0 then { x... }
     begin
          if m[4].t < 0.0 then fastcalc := v { xy }
          else if m[4].t = 0.0 then { xt }
          begin
               fastcalc.x := v.x;
               fastcalc.y := v.t;
               fastcalc.z := -1*v.z;
               fastcalc.t := -1*v.y;
          end
          else { m[4].t > 0 } { xz }
          begin
               fastcalc.x := v.x;
               fastcalc.y := v.z;
               fastcalc.z := -1*v.y;
               fastcalc.t := v.t;
          end;
          { fastcalc := (v.x*v1)+(v.y*v2)+(v.z*v3)+(v.t*v4) }
     end
     else
     begin
          if m[4].t = 0.0 then { zt }
          begin
               fastcalc.x := v.z;
               fastcalc.y := v.t;
               fastcalc.z := v.x;
               fastcalc.t := -1*v.y;
          end
          else { yz }
          begin
               fastcalc.x := v.y;
               fastcalc.y := v.z;
               fastcalc.z := v.x;
               fastcalc.t := -1*v.t;
          end;
          { fastcalc := (v.x*v1)+(v.y*v2)+(v.z*v3)+(v.t*v4) }
     end;
end;


function invfastcalc (v : hyper;m : matrix4) : hyper;
begin
     if m[1].x = 1.0 then { x... }
     begin
          if m[4].t < 0.0 then invfastcalc := v { xy }
          else if m[4].t = 0.0 then { xt }
          begin
               invfastcalc.x := v.x;
               invfastcalc.t := v.y;
               invfastcalc.z := -1*v.z;
               invfastcalc.y := -1*v.t;
          end
          else { m[4].t > 0 } { xz }
          begin
               invfastcalc.x := v.x;
               invfastcalc.z := v.y;
               invfastcalc.y := -1*v.z;
               invfastcalc.t := v.t;
          end;
     end
     else
     begin
          if m[4].t = 0.0 then { zt }
          begin
               invfastcalc.z := v.x;
               invfastcalc.t := v.y;
               invfastcalc.x := v.z;
               invfastcalc.y := -1*v.t;
          end
          else { yz }
          begin
               invfastcalc.y := v.x;
               invfastcalc.z := v.y;
               invfastcalc.x := v.z;
               invfastcalc.t := -1*v.t;
          end;
     end;
end;

var coord,coord_dim,coord_factor,coord_center,coord_min : hyper;
    coord_old : matrix4;

function proc_fix_x (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     fix_x := true;
     proc_fix_x := gtk_true;
end;

function proc_fix_y (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     fix_y := true;
     proc_fix_y := gtk_true;
end;

function proc_unfix (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     fix_x := false;
     fix_y := false;
     proc_unfix := gtk_true;
end;

procedure initcoord (c : complexnat;m : matrix4;realt : boolean);
var d1,d2 : hyper;
    sizex,sizey,sizez,sizet : integer;
begin
     coord_old := m;

     global_zoom := limit (global_zoom,0.1,10);

     sizex := c.x-1;
     sizey := c.y-1;
     sizez := $FFFF;
     sizet := round(min(sizex,sizey)/(2*10)); { factor 10 smaller }
     if global_zoom <= 1 then coord_dim := gethyper (sizex,sizey,sizez*global_zoom,sizet*global_zoom) { Definitionsbereichsvektor }
                         else coord_dim := gethyper (sizex,sizey,sizez/global_zoom,sizet/global_zoom); { Definitionsbereichsvektor }

     d2 := fastcalc ((maxall-minall)*1.05*global_zoom,m);
     if d2 = Hmax then d2 := Hnorm
     else if d2 = Hmin then d2 := -1*Hnorm;

{normal aspect ratio}
     if fix_x and not fix_y then
     begin
          d2.y := d2.x;
          sizey := sizex;
     end
     else if not fix_x and fix_y then
     begin
          d2.x := d2.y;
          sizex := sizey;
     end
     else
     begin
          if ((sizex/d2.x)*d2.y) <= sizey then
          begin { fix_x }
               d2.y := d2.x;
               sizey := sizex;
          end
          else  { fix_y }
          begin
               d2.x := d2.y;
               sizex := sizey;
          end;
     end;

     d1 := gethyper (sizex,-sizey,sizez,sizet);

     coord_factor := (d1/d2); { factor vector }

     global_center := limit (global_center,-1*(maxall-minall)*global_zoom,(maxall-minall)*global_zoom);
     coord_center := fastcalc ((centerall+global_center),m); { Centervektor }

     coord_min := fastcalc (minall,m); { Verschiebungsvektor }

     coord  :=  (coord_dim/2)-(coord_factor*(coord_center-coord_min));

     if realt then { override all }
     begin
          coord.t := 0;
          coord_factor.t := coord_factor.x;
          coord_min.t := 0;
     end;
end;

function getscreencoord (v :  hyper) : hypernat;
var value : hyper;
begin
     value := fastcalc (v,coord_old); { Wertevektor }
     try
        getscreencoord := round(coord + (coord_factor*(value-coord_min)));
     except
        getscreencoord := round(coord + (coord_factor*(Hzero-coord_min)));
     end;
end;

function getpointcoord (v : hyper) : hyper;
var value : hyper;
begin
     try
        value := ((v-coord)/coord_factor)+coord_min;
     except
        value := ((Hzero-coord)/coord_factor)+coord_min;;
     end;
     getpointcoord := invfastcalc(value,coord_old); { Wertevektor }
end;

function getpoint2coord (x,y : real) : hyper;
var value : hyper;
begin
     value := ((gh(x,y,0,0)-coord)/coord_factor)+coord_min;;
     getpoint2coord := invfastcalc(value,coord_old); { Wertevektor }
     case screen of { for hard bool }
          1 : getpoint2coord := gh (getpoint2coord.x,getpoint2coord.y,0,0);
          2 : getpoint2coord := gh (getpoint2coord.x,0,getpoint2coord.z,0);
          4 : getpoint2coord := gh (getpoint2coord.x,0,0,getpoint2coord.t);
          3 : getpoint2coord := gh (0,getpoint2coord.y,getpoint2coord.z,0);
          5 : getpoint2coord := gh (0,0,getpoint2coord.z,getpoint2coord.t);
          else getpoint2coord := HZero;
     end;
end;

{$include draw5.inc}

function Exposed_xy (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_xy.sizex <> gtk_widget(widget)^.allocation.width) or (screen_xy.sizey <> gtk_widget(widget)^.allocation.height)
        then newdraw (widget,xy,screen_xy,1)
        else newdraw2 (widget,xy,screen_xy,1);
     Exposed_xy := gtk_true;
end;

function Exposed_xz (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_xz.sizex <> gtk_widget(widget)^.allocation.width) or (screen_xz.sizey <> gtk_widget(widget)^.allocation.height)
        then newdraw (widget,xz,screen_xz,2)
        else newdraw2 (widget,xz,screen_xz,2);
     Exposed_xz := gtk_true;
end;

function Exposed_xt (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_xt.sizex <> gtk_widget(widget)^.allocation.width) or (screen_xt.sizey <> gtk_widget(widget)^.allocation.height)
        then newdraw (widget,xt,screen_xt,4)
        else newdraw2 (widget,xt,screen_xt,4);
     Exposed_xt := gtk_true;
end;

function Exposed_yz (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_yz.sizex <> gtk_widget(widget)^.allocation.width) or (screen_yz.sizey <> gtk_widget(widget)^.allocation.height)
        then newdraw (widget,yz,screen_yz,3)
        else newdraw2 (widget,yz,screen_yz,3);
     Exposed_yz := gtk_true;
end;

function Exposed_zt (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_zt.sizex <> gtk_widget(widget)^.allocation.width) or (screen_zt.sizey <> gtk_widget(widget)^.allocation.height)
        then newdraw (widget,zt,screen_zt,5)
        else newdraw2 (widget,zt,screen_zt,5);
     Exposed_zt := gtk_true;
end;

function Exposed_histo(Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (screen_histo.sizex <> gtk_widget(widget)^.allocation.width) or (screen_histo.sizey <> gtk_widget(widget)^.allocation.height) then
     begin
          {screen_histo.resize(widget^.allocation.width,widget^.allocation.height);
          screen_histo.render;}
          screen_histo.done;;
          screen_histo.init (gtk_widget(widget)^.allocation.width,gtk_widget(widget)^.allocation.height);
          case stattype of
               1 :
               begin
                    if _getcheckbutton (togglegrouped) then
                    begin
                         screen_histo.left ('grouped '+statobjects);
                         screen_histo.bottom (statname+' [units]');
                         screen_histo.setstyle (2);
                         if _getnat (geometry_groups) > 1 then
                         screen_histo.grouped (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred,_getnat(geometry_groups));
                         screen_histo.render;
                    end
                    else
                    begin
                         screen_histo.left (statname+' [units]');
                         screen_histo.bottom ('sorted '+statobjects);
                         screen_histo.setstyle (5);
                         screen_histo.histogram (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
                         screen_histo.render;
                    end;
               end;
               2,3 :
               begin
                    screen_histo.left (statname+' [units]');
                    screen_histo.bottom (statobjects);
                    screen_histo.setstyle (5);
                    screen_histo.histogram (cstat[6],cstat[5],cstat[4],cstat[3],cstat[2],cstat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
                    screen_histo.render;
               end;
          end;
          newdraw3 (widget,screen_histo.field);
     end
     else newdraw3 (widget,screen_histo.field);
     Exposed_histo := gtk_true;
end;

procedure calculating;
var x : integer;
begin
     min_red := red.min;
     min_green := green.min;
     min_blue := blue.min;
     min_yellow := yellow.min;
     min_cyan := cyan.min;
     min_purple := purple.min;

     max_red := red.max;
     max_green := green.max;
     max_blue := blue.max;
     max_yellow := yellow.max;
     max_cyan := cyan.max;
     max_purple := purple.max;

     minall := Hmax;
     if ref_state[1] then minall := min(minall,min_red);
     if ref_state[2] then minall := min(minall,min_green);
     if ref_state[3] then minall := min(minall,min_blue);
     if ref_state[4] then minall := min(minall,min_yellow);
     if ref_state[5] then minall := min(minall,min_cyan);
     if ref_state[6] then minall := min(minall,min_purple);

     maxall := Hmin;
     if ref_state[1] then maxall := max(maxall,max_red);
     if ref_state[2] then maxall := max(maxall,max_green);
     if ref_state[3] then maxall := max(maxall,max_blue);
     if ref_state[4] then maxall := max(maxall,max_yellow);
     if ref_state[5] then maxall := max(maxall,max_cyan);
     if ref_state[6] then maxall := max(maxall,max_purple);

     if minall = Hmax then minall := gh (-10,-10,-10,-10);
     if maxall = Hmin then maxall := gh (10,10,10,10);

{ Too small areas }
     if minall.x = maxall.x then begin minall.x:= minall.x-1; maxall.x:= maxall.x+1; end;
     if minall.y = maxall.y then begin minall.y:= minall.y-1; maxall.y:= maxall.y+1; end;
     if minall.z = maxall.z then begin minall.z:= minall.z-1; maxall.z:= maxall.z+1; end;
     if minall.t = maxall.t then begin minall.t:= minall.t-1; maxall.t:= maxall.t+1; end;
{ Center }
     if (min_red <> Hmax) and (max_red <> Hmin) then center_red := (min_red+max_red)/2 else center_red := Hzero;
     if (min_green <> Hmax) and (max_green <> Hmin) then center_green := (min_green+max_green)/2 else center_green :=  Hzero;
     if (min_blue <> Hmax) and (max_blue <> Hmin) then center_blue := (min_blue+max_blue)/2 else center_blue :=  Hzero;
     if (min_yellow <> Hmax) and (max_yellow <> Hmin) then center_yellow := (min_yellow+max_yellow)/2 else center_yellow :=  Hzero;
     if (min_cyan <> Hmax) and (max_cyan <> Hmin) then center_cyan := (min_cyan+max_cyan)/2 else center_cyan :=  Hzero;
     if (min_purple <> Hmax) and (max_purple <> Hmin) then center_purple := (min_purple+max_purple)/2 else center_purple :=  Hzero;
     centerall := (minall+maxall)/2;

     if ref_state[1] then
        if red.objectcounter > 0 then
           for x := 1 to red.objectcounter do
           begin
                red.objectmin (x);
                red.objectmax (x);
           end;
     if ref_state[2] then
        if green.objectcounter > 0 then
           for x := 1 to green.objectcounter do
           begin
                green.objectmin (x);
                green.objectmax (x);
           end;
     if ref_state[3] then
        if blue.objectcounter > 0 then
           for x := 1 to blue.objectcounter do
           begin
                blue.objectmin (x);
                blue.objectmax (x);
           end;
     if ref_state[4] then
        if yellow.objectcounter > 0 then
           for x := 1 to yellow.objectcounter do
           begin
                yellow.objectmin (x);
                yellow.objectmax (x);
           end;
     if ref_state[5] then
        if cyan.objectcounter > 0 then
           for x := 1 to cyan.objectcounter do
           begin
                cyan.objectmin (x);
                cyan.objectmax (x);
           end;
     if ref_state[6] then
        if purple.objectcounter > 0 then
           for x := 1 to purple.objectcounter do
           begin
                purple.objectmin (x);
                purple.objectmax (x);
           end;
end;

procedure refreshdir;
var s : utf16;
begin
     s := getshortdir(finput^.name,60);
     if s = '' then s := ' <i>Empty</i> ';
     if finput^.change then _setlabel (fileed,'<b>*</b>'+s)
                       else _setlabel (fileed,s);
     s := getshortdir(getcurrentdir,60);
     _setlabel (workdir,s);
end;

procedure updating;
var z,l,bl,poly : integer;
    mc,mt,minc,mint,maxc,maxt,counter,factor,d : real;
    line : tpolyhyper;
    linepoly : tpolynom4d;
    line_3d : tpolyvector;
    line_3dpoly : tpolynom3d;
    line_3dfunc : tcurveproperty3d;
    m4 : matrix4;
    heap : TFPCHeapStatus;
{    heap1 : TFPCHeapStatus;}
    heap2 : THeapStatus;
    procedure my_input_button (w : gtk_widget);
    begin
         case input of
              1 : _setlabel (w,'Red layer');
              2 : _setlabel (w,'Green layer');
              3 : _setlabel (w,'Blue layer');
              4 : _setlabel (w,'Yellow layer');
              5 : _setlabel (w,'Cyan layer');
              else _setlabel (w,'Purple layer');
         end;
    end;
    procedure my_input2_button (w : gtk_widget);
    begin
         case input of
              1 : _setlabel (w,'Red');
              2 : _setlabel (w,'Green');
              3 : _setlabel (w,'Blue');
              4 : _setlabel (w,'Yellow');
              5 : _setlabel (w,'Cyan');
              else _setlabel (w,'Purple');
         end;
    end;
    procedure my_inputedit_button (w : gtk_widget);
    begin
         case inputedit of
              1 : _setlabel (w,'Red');
              2 : _setlabel (w,'Green');
              3 : _setlabel (w,'Blue');
              4 : _setlabel (w,'Yellow');
              5 : _setlabel (w,'Cyan');
              else _setlabel (w,'Purple');
         end;
    end;
    procedure my_point (w : gtk_widget);
    begin
         _setlabel (w,getstring(finput^.pointcounter)+'. point (from '+getstring(finput^.getpointlength)+' points)');
    end;
    procedure my_line (w : gtk_widget);
    begin
         _setlabel (w,getstring(finput^.linecounter)+'. line (from '+getstring(finput^.getlinelength)+' lines)');
    end;
    procedure my_line2 (w : gtk_widget);
    begin
         _setlabel (w,getstring(finput^.linecounter)+'. line (from '+getstring(finput^.getlinelength)+' lines)'+#10+'material: '+getstring(finput^.getallmaterial(finput^.linecounter)));
    end;
    procedure my_object (w : gtk_widget);
    var s : utf16;
    begin
         s := finput^.getname(finput^.objectcounter);
         if length(s) > 20 then s := '..' + copy (s,length(s)-20,length(s));
         _setlabel (w,getstring(finput^.objectcounter)+'. object (from '+getstring(finput^.getobjectlength)+' objects)'+#10+'name: '+s);
    end;
    procedure my_status (t : gtk_textbuffer;line : tcloud;center,min,max : hyper);
    var s : utf16;
        count{,count2} : integer;
    begin
         s := '';
         if line.getobjectlength > 0 then
         begin
              for count := 1 to line.getobjectlength do
              begin
                   s := s + getstring(count) + ': ' + line.getname(count)  + ' | lines: ' + getstring(line.getobjectlinelength(count)) + ' | points: ' + getstring(line.getobjectpointlength(count)) + #10;
                   {if line.getobjectlinelength(count) > 0 then
                   begin
                        for count2 := 1 to line.getobjectlinelength(count) do
                        begin
                             s := s + getstring(count2) + ': ' + getstring(line.getmaterial(count,count2)) + #10;
                        end;
                   end;}
              end;
         end;
         {if line.getlinelength > 0 then
         begin
              for count := 1 to line.getlinelength do
              begin
                   s := s + getstring(count) + ': ' + getstring(line.getallmaterial(count)) + #10;
              end;
         end;        }
         if min = Hmax then min := Hzero;
         if max = Hmin then max := Hzero;
         _settext (t,'Dir : '+getdir(line.name)+#10+
                     'File : '+getfile(line.name)+#10+' '+#10+
                     'Points : '+getstring(line.getpointlength)+#10+
                     'Lines : '+getstring(line.getlinelength)+#10+
                     'Objects : '+getstring(line.getobjectlength)+#10+' '+#10+
                     'Center : '+getstring(center,3)+#10+
                     'Minimum : '+getstring(min,3)+#10+
                     'Maximum : '+getstring(max,3)+#10+
                     'Max-Min : '+getstring(max-min,3)+#10+' '+#10+
                     s);
    end;
begin
     line := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);
     line_3d := Default(tpolyvector);
     line_3dpoly := Default(tpolynom3d);
     line_3dfunc := Default(tcurveproperty3d);
     heap := Default(TFPCHeapStatus);
{    heap1 := Default(TFPCHeapStatus);}
     heap2 := Default(THeapStatus);

{ upper Layer }
     if input = 1 then begin if state[1] then begin _backcolor (red_button,$FFFF,$8000,$8000); _setlabel (red_label,'<span background="#FF8080"> <b><u>R</u>ed</b> </span>') end else begin _reset_backcolor (red_button); _setlabel (red_label,' <b><u>R</u>ed</b> '); end; end
                  else begin if state[1] then begin _backcolor (red_button,$FFFF,$8000,$8000); _setlabel (red_label,'<span background="#FF8080"> <u>R</u>ed </span>') end else begin _reset_backcolor (red_button); _setlabel (red_label,' <u>R</u>ed '); end; end;
     if input = 2 then begin if state[2] then begin _backcolor (green_button,$8000,$FFFF,$8000); _setlabel (green_label,'<span background="#80FF80"> <b><u>G</u>reen</b> </span>') end else begin _reset_backcolor (green_button); _setlabel (green_label,' <b><u>G</u>reen</b> '); end; end
                  else begin if state[2] then begin _backcolor (green_button,$8000,$FFFF,$8000); _setlabel (green_label,'<span background="#80FF80"> <u>G</u>reen </span>') end else begin _reset_backcolor (green_button); _setlabel (green_label,' <u>G</u>reen '); end; end;
     if input = 3 then begin if state[3] then begin _backcolor (blue_button,$8000,$8000,$FFFF); _setlabel (blue_label,'<span background="#8080FF"> <b><u>B</u>lue</b> </span>') end else begin _reset_backcolor (blue_button); _setlabel (blue_label,' <b><u>B</u>lue</b> '); end; end
                  else begin if state[3] then begin _backcolor (blue_button,$8000,$8000,$FFFF); _setlabel (blue_label,'<span background="#8080FF"> <u>B</u>lue </span>') end else begin _reset_backcolor (blue_button); _setlabel (blue_label,' <u>B</u>lue '); end; end;
     if input = 4 then begin if state[4] then begin _backcolor (yellow_button,$FFFF,$FFFF,$8000); _setlabel (yellow_label,'<span background="#FFFF80"> <b><u>Y</u>ellow</b> </span>') end else begin _reset_backcolor (yellow_button); _setlabel (yellow_label,' <b><u>Y</u>ellow</b> '); end; end
                  else begin if state[4] then begin _backcolor (yellow_button,$FFFF,$FFFF,$8000); _setlabel (yellow_label,'<span background="#FFFF80"> <u>Y</u>ellow </span>') end else begin _reset_backcolor (yellow_button); _setlabel (yellow_label,' <u>Y</u>ellow '); end; end;
     if input = 5 then begin if state[5] then begin _backcolor (cyan_button,$8000,$FFFF,$FFFF); _setlabel (cyan_label,'<span background="#80FFFF"> <b><u>C</u>yan</b> </span>') end else begin _reset_backcolor (cyan_button); _setlabel (cyan_label,' <b><u>C</u>yan</b> '); end; end
                  else begin if state[5] then begin _backcolor (cyan_button,$8000,$FFFF,$FFFF); _setlabel (cyan_label,'<span background="#80FFFF"> <u>C</u>yan </span>') end else begin _reset_backcolor (cyan_button); _setlabel (cyan_label,' <u>C</u>yan '); end; end;
     if input = 6 then begin if state[6] then begin _backcolor (purple_button,$FFFF,$8000,$FFFF); _setlabel (purple_label,'<span background="#FF80FF"> <b><u>P</u>urple</b> </span>') end else begin _reset_backcolor (purple_button); _setlabel (purple_label,' <b><u>P</u>urple</b> '); end; end
                  else begin if state[6] then begin _backcolor (purple_button,$FFFF,$8000,$FFFF); _setlabel (purple_label,'<span background="#FF80FF"> <u>P</u>urple </span>') end else begin _reset_backcolor (purple_button); _setlabel (purple_label,' <u>P</u>urple '); end; end;
{ lower Layer }
     if inputedit = 1 then begin if ref_state[1] then begin _backcolor (red2_button,$FFFF,$8000,$8000); _setlabel (red2_label,'<span background="#FF8080"> <b><span underline="double">R</span>ed</b> </span>') end else begin _reset_backcolor (red2_button); _setlabel (red2_label,' <b><span underline="double">R</span>ed</b> '); end; end
                      else begin if ref_state[1] then begin _backcolor (red2_button,$FFFF,$8000,$8000); _setlabel (red2_label,'<span background="#FF8080"> <span underline="double">R</span>ed </span>') end else begin _reset_backcolor (red2_button); _setlabel (red2_label,' <span underline="double">R</span>ed '); end; end;
     if inputedit = 2 then begin if ref_state[2] then begin _backcolor (green2_button,$8000,$FFFF,$8000); _setlabel (green2_label,'<span background="#80FF80"> <b><span underline="double">G</span>reen</b> </span>') end else begin _reset_backcolor (green2_button); _setlabel (green2_label,' <b><span underline="double">G</span>reen</b> '); end; end
                      else begin if ref_state[2] then begin _backcolor (green2_button,$8000,$FFFF,$8000); _setlabel (green2_label,'<span background="#80FF80"> <span underline="double">G</span>reen </span>') end else begin _reset_backcolor (green2_button); _setlabel (green2_label,' <span underline="double">G</span>reen '); end; end;
     if inputedit = 3 then begin if ref_state[3] then begin _backcolor (blue2_button,$8000,$8000,$FFFF); _setlabel (blue2_label,'<span background="#8080FF"> <b><span underline="double">B</span>lue</b> </span>') end else begin _reset_backcolor (blue2_button); _setlabel (blue2_label,' <b><span underline="double">B</span>lue</b> '); end; end
                      else begin if ref_state[3] then begin _backcolor (blue2_button,$8000,$8000,$FFFF); _setlabel (blue2_label,'<span background="#8080FF"> <span underline="double">B</span>lue </span>') end else begin _reset_backcolor (blue2_button); _setlabel (blue2_label,' <span underline="double">B</span>lue '); end; end;
     if inputedit = 4 then begin if ref_state[4] then begin _backcolor (yellow2_button,$FFFF,$FFFF,$8000); _setlabel (yellow2_label,'<span background="#FFFF80"> <b><span underline="double">Y</span>ellow</b> </span>') end else begin _reset_backcolor (yellow2_button); _setlabel (yellow2_label,' <b><span underline="double">Y</span>ellow</b> '); end; end
                      else begin if ref_state[4] then begin _backcolor (yellow2_button,$FFFF,$FFFF,$8000); _setlabel (yellow2_label,'<span background="#FFFF80"> <span underline="double">Y</span>ellow </span>') end else begin _reset_backcolor (yellow2_button); _setlabel (yellow2_label,' <span underline="double">Y</span>ellow '); end; end;
     if inputedit = 5 then begin if ref_state[5] then begin _backcolor (cyan2_button,$8000,$FFFF,$FFFF); _setlabel (cyan2_label,'<span background="#80FFFF"> <b><span underline="double">C</span>yan</b> </span>') end else begin _reset_backcolor (cyan2_button); _setlabel (cyan2_label,' <b><span underline="double">C</span>yan</b> '); end; end
                      else begin if ref_state[5] then begin _backcolor (cyan2_button,$8000,$FFFF,$FFFF); _setlabel (cyan2_label,'<span background="#80FFFF"> <span underline="double">C</span>yan </span>') end else begin _reset_backcolor (cyan2_button); _setlabel (cyan2_label,' <span underline="double">C</span>yan '); end; end;
     if inputedit = 6 then begin if ref_state[6] then begin _backcolor (purple2_button,$FFFF,$8000,$FFFF); _setlabel (purple2_label,'<span background="#FF80FF"> <b><span underline="double">P</span>urple</b> </span>') end else begin _reset_backcolor (purple2_button); _setlabel (purple2_label,' <b><span underline="double">P</span>urple</b> '); end; end
                      else begin if ref_state[6] then begin _backcolor (purple2_button,$FFFF,$8000,$FFFF); _setlabel (purple2_label,'<span background="#FF80FF"> <span underline="double">P</span>urple </span>') end else begin _reset_backcolor (purple2_button); _setlabel (purple2_label,' <span underline="double">P</span>urple '); end; end;
{
 upper Layer
     if input = 1 then begin if state[1] then begin _backcolor (red_button,$FFFF,$8000,$8000); _setlabel (red_label,' <b><u>R</u>ed</b> ') end else begin _reset_backcolor (red_button); _setlabel (red_label,' <b><u>R</u>ed</b> '); end; end
                  else begin if state[1] then begin _backcolor (red_button,$FFFF,$8000,$8000); _setlabel (red_label,' <u>R</u>ed ') end else begin _reset_backcolor (red_button); _setlabel (red_label,' <u>R</u>ed '); end; end;
     if input = 2 then begin if state[2] then begin _backcolor (green_button,$8000,$FFFF,$8000); _setlabel (green_label,' <b><u>G</u>reen</b> ') end else begin _reset_backcolor (green_button); _setlabel (green_label,' <b><u>G</u>reen</b> '); end; end
                  else begin if state[2] then begin _backcolor (green_button,$8000,$FFFF,$8000); _setlabel (green_label,' <u>G</u>reen ') end else begin _reset_backcolor (green_button); _setlabel (green_label,' <u>G</u>reen '); end; end;
     if input = 3 then begin if state[3] then begin _backcolor (blue_button,$8000,$8000,$FFFF); _setlabel (blue_label,' <b><u>B</u>lue</b> ') end else begin _reset_backcolor (blue_button); _setlabel (blue_label,' <b><u>B</u>lue</b> '); end; end
                  else begin if state[3] then begin _backcolor (blue_button,$8000,$8000,$FFFF); _setlabel (blue_label,' <u>B</u>lue ') end else begin _reset_backcolor (blue_button); _setlabel (blue_label,' <u>B</u>lue '); end; end;
     if input = 4 then begin if state[4] then begin _backcolor (yellow_button,$FFFF,$FFFF,$8000); _setlabel (yellow_label,' <b><u>Y</u>ellow</b> ') end else begin _reset_backcolor (yellow_button); _setlabel (yellow_label,' <b><u>Y</u>ellow</b> '); end; end
                  else begin if state[4] then begin _backcolor (yellow_button,$FFFF,$FFFF,$8000); _setlabel (yellow_label,' <u>Y</u>ellow ') end else begin _reset_backcolor (yellow_button); _setlabel (yellow_label,' <u>Y</u>ellow '); end; end;
     if input = 5 then begin if state[5] then begin _backcolor (cyan_button,$8000,$FFFF,$FFFF); _setlabel (cyan_label,' <b><u>C</u>yan</b> ') end else begin _reset_backcolor (cyan_button); _setlabel (cyan_label,' <b><u>C</u>yan</b> '); end; end
                  else begin if state[5] then begin _backcolor (cyan_button,$8000,$FFFF,$FFFF); _setlabel (cyan_label,' <u>C</u>yan ') end else begin _reset_backcolor (cyan_button); _setlabel (cyan_label,' <u>C</u>yan '); end; end;
     if input = 6 then begin if state[6] then begin _backcolor (purple_button,$FFFF,$8000,$FFFF); _setlabel (purple_label,' <b><u>P</u>urple</b> ') end else begin _reset_backcolor (purple_button); _setlabel (purple_label,' <b><u>P</u>urple</b> '); end; end
                  else begin if state[6] then begin _backcolor (purple_button,$FFFF,$8000,$FFFF); _setlabel (purple_label,' <u>P</u>urple ') end else begin _reset_backcolor (purple_button); _setlabel (purple_label,' <u>P</u>urple '); end; end;
 lower Layer
     if inputedit = 1 then begin if ref_state[1] then begin _backcolor (red2_button,$FFFF,$8000,$8000); _setlabel (red2_label,' <b><span underline="double">R</span>ed</b> ') end else begin _reset_backcolor (red2_button); _setlabel (red2_label,' <b><span underline="double">R</span>ed</b> '); end; end
                      else begin if ref_state[1] then begin _backcolor (red2_button,$FFFF,$8000,$8000); _setlabel (red2_label,' <span underline="double">R</span>ed ') end else begin _reset_backcolor (red2_button); _setlabel (red2_label,' <span underline="double">R</span>ed '); end; end;
     if inputedit = 2 then begin if ref_state[2] then begin _backcolor (green2_button,$8000,$FFFF,$8000); _setlabel (green2_label,' <b><span underline="double">G</span>reen</b> ') end else begin _reset_backcolor (green2_button); _setlabel (green2_label,' <b><span underline="double">G</span>reen</b> '); end; end
                      else begin if ref_state[2] then begin _backcolor (green2_button,$8000,$FFFF,$8000); _setlabel (green2_label,' <span underline="double">G</span>reen ') end else begin _reset_backcolor (green2_button); _setlabel (green2_label,' <span underline="double">G</span>reen '); end; end;
     if inputedit = 3 then begin if ref_state[3] then begin _backcolor (blue2_button,$8000,$8000,$FFFF); _setlabel (blue2_label,' <b><span underline="double">B</span>lue</b> ') end else begin _reset_backcolor (blue2_button); _setlabel (blue2_label,' <b><span underline="double">B</span>lue</b> '); end; end
                      else begin if ref_state[3] then begin _backcolor (blue2_button,$8000,$8000,$FFFF); _setlabel (blue2_label,' <span underline="double">B</span>lue ') end else begin _reset_backcolor (blue2_button); _setlabel (blue2_label,' <span underline="double">B</span>lue '); end; end;
     if inputedit = 4 then begin if ref_state[4] then begin _backcolor (yellow2_button,$FFFF,$FFFF,$8000); _setlabel (yellow2_label,' <b><span underline="double">Y</span>ellow</b> ') end else begin _reset_backcolor (yellow2_button); _setlabel (yellow2_label,' <b><span underline="double">Y</span>ellow</b> '); end; end
                      else begin if ref_state[4] then begin _backcolor (yellow2_button,$FFFF,$FFFF,$8000); _setlabel (yellow2_label,' <span underline="double">Y</span>ellow ') end else begin _reset_backcolor (yellow2_button); _setlabel (yellow2_label,' <span underline="double">Y</span>ellow '); end; end;
     if inputedit = 5 then begin if ref_state[5] then begin _backcolor (cyan2_button,$8000,$FFFF,$FFFF); _setlabel (cyan2_label,' <b><span underline="double">C</span>yan</b> ') end else begin _reset_backcolor (cyan2_button); _setlabel (cyan2_label,' <b><span underline="double">C</span>yan</b> '); end; end
                      else begin if ref_state[5] then begin _backcolor (cyan2_button,$8000,$FFFF,$FFFF); _setlabel (cyan2_label,' <span underline="double">C</span>yan ') end else begin _reset_backcolor (cyan2_button); _setlabel (cyan2_label,' <span underline="double">C</span>yan '); end; end;
     if inputedit = 6 then begin if ref_state[6] then begin _backcolor (purple2_button,$FFFF,$8000,$FFFF); _setlabel (purple2_label,' <b><span underline="double">P</span>urple</b> ') end else begin _reset_backcolor (purple2_button); _setlabel (purple2_label,' <b><span underline="double">P</span>urple</b> '); end; end
                      else begin if ref_state[6] then begin _backcolor (purple2_button,$FFFF,$8000,$FFFF); _setlabel (purple2_label,' <span underline="double">P</span>urple ') end else begin _reset_backcolor (purple2_button); _setlabel (purple2_label,' <span underline="double">P</span>urple '); end; end;
}
{ from edit }
     my_input2_button (l_bool_object_left);
     my_inputedit_button (l_bool_object_right);
{ from bool }
     my_input2_button (l_bool_subobject_left_p);
     my_inputedit_button (l_bool_subobject_right_p);

     my_input2_button (l_bool_subobject_left_s);
     my_inputedit_button (l_bool_subobject_right_s);

     my_input2_button (l_bool_subobject_left_l);
     my_inputedit_button (l_bool_subobject_right_l);
     my_input2_button (l_bool_subobject2_left_l);
     my_inputedit_button (l_bool_subobject2_right_l);

     my_input2_button (l_bool_subobject_left_mesh);
     my_inputedit_button (l_bool_subobject_right_mesh);

     my_input2_button (l_bool_subobject_left_o);
     my_inputedit_button (l_bool_subobject_right_o);
     my_input2_button (l_bool_subobject2_left_o);
     my_inputedit_button (l_bool_subobject2_right_o);
{ from input }
     my_line (label_polynom_status);
     my_point (label_status_point);
     my_line2 (label_status_vector);
     my_line2 (label_status_line);
     my_object (label_status_object);
     my_point (label_status_point2);
     my_line2 (label_status_line2);
     my_object (label_status_object2);
{$ifndef free}
     my_object (label_status_object3);
{$endif}
{ Microscribe }
     my_line (m3dstat);
     if input = 4 then
     begin
          _setlabel (label_microscribe_input,'');
          _settext (m3dstat1,'');
     end
     else
     case inputmethod of
          1 : begin
                   _setlabel (label_microscribe_input,'Points');
                   _settext (m3dstat1,'Points : '+getstring(finput^.getpointlength));
              end;
          2 : begin
                   _setlabel (label_microscribe_input,'Distances');
                   z := finput^.linecounter;
                   if z > 0 then
                   begin
                        l := finput^.getalllinepointlength (z);
                        if l < 2 then
                        begin
                             _settext (m3dstat1,'Points : '+getstring(l)+' - '+
                                                'Length : 0');
                        end
                        else
                        begin
                             d := getlength (finput^.getline (z,1)-finput^.getline (z,l));
                             _settext (m3dstat1,'Points : 2 (farthest)'+' - '+
                                                'Length : '+getstring(d,3));
                        end;
                   end
                   else _settext (m3dstat1,'Points : 0');
              end;
          3 : begin
                   _setlabel (label_microscribe_input,'Lines');
                   z := finput^.linecounter;
                   if z > 0 then
                   begin
                        l := finput^.getalllinepointlength (z);
                        d := 0;
                        if l > 1 then
                        for bl := 1 to l-1 do
                        begin
                             d := d + getlength (finput^.getline(z,bl) - finput^.getline(z,bl+1));
                        end;
                        _settext (m3dstat1,'Points : '+getstring(l)+' - '+
                                           'Length : '+getstring(d,3));
                   end
                   else _settext (m3dstat1,'Points : 0');
               end;
          else
              begin
                   _setlabel (label_microscribe_input,'Curves');
                   z := finput^.linecounter;
                   if z > 0 then
                   begin
                        l := finput^.getalllinepointlength (z);
                        if l > 1 then
                        begin
                             line_3d.init (l);
                             for bl := 1 to l do line_3d.put (bl,htov(finput^.getline (z,bl)));
                             if l < 10 then line_3dpoly.init (l)
                                       else line_3dpoly.init (10);
                             line_3dpoly.fit (line_3d); { fit }
                             line_3dfunc.init (line_3dpoly);
                             factor := line_3dpoly.pathlength/100;
                             counter := 0;
                             d := 0;
                             mc := 0; minc := infinity; maxc := ninfinity;
                             mt := 0; mint := infinity; maxt := ninfinity;
                             for bl := 1 to 100 do
                             begin
                                  d := d + getlength (line_3dpoly.polynom (counter+factor)-line_3dpoly.polynom (counter));
                                  mc := mc + line_3dfunc.curvature (counter);
                                  if line_3dfunc.curvature (counter) < minc then minc := line_3dfunc.curvature (counter);
                                  if line_3dfunc.curvature (counter) > maxc then maxc := line_3dfunc.curvature (counter);
                                  mt := mt + line_3dfunc.torsion (counter);
                                  if line_3dfunc.torsion (counter) < mint then mint := line_3dfunc.torsion (counter);
                                  if line_3dfunc.torsion (counter) > maxt then maxt := line_3dfunc.torsion (counter);
                                  counter := counter + factor;
                             end;
                             mc := mc + line_3dfunc.curvature (counter);
                             if line_3dfunc.curvature (counter) < minc then minc := line_3dfunc.curvature (counter);
                             if line_3dfunc.curvature (counter) > maxc then maxc := line_3dfunc.curvature (counter);
                             mc := mc / 100.0;
                             mt := mt + line_3dfunc.torsion (counter);
                             if line_3dfunc.torsion (counter) < mint then mint := line_3dfunc.torsion (counter);
                             if line_3dfunc.torsion (counter) > maxt then maxt := line_3dfunc.torsion (counter);
                             mt := mt / 100.0;
                             line_3dfunc.done;
                             line_3dpoly.done;
                             line_3d.done;
                        end
                        else
                        begin
                             d := 0;
                             mc := 0; minc := 0; maxc := 0;
                             mt := 0; mint := 0; maxt := 0;
                        end;
                                                                                           
                        _settext(m3dstat1,'Points : '+getstring(l)+' - '+
                                          'Length : '+getstring(d,3)+#10+
                                          'Curvature : '+getstring(mc,3)+' ('+getstring(minc,3)+' .. '+getstring(maxc,3)+')'+' - '+
                                          'Torsion : '+getstring(mt,3)+' ('+getstring(mint,3)+' .. '+getstring(maxt,3)+')');
                   end
                   else _settext(m3dstat1,'Points : 0');
              end;
     end;
{ Polynom }
     z := finput^.linecounter;
     if z > 0 then
     begin
          l := finput^.getalllinepointlength (z);
          poly := _getitem (input_polynom_method)+1;
          if (l > 1) then
          begin
               line.init (l);
               for bl := 1 to l do line.put (bl,finput^.getline (z,bl));
               if  into(poly,1,10) then
               begin
                    if l < poly then linepoly.init (l)
                                else linepoly.init (poly);
                    linepoly.getpolynom (line);
                    for bl := 1 to poly do _setedit (polynom[bl-1],getstring(linepoly.get(bl),5));
                    if poly < 10 then
                       for bl := poly+1 to 10 do _setedit (polynom[bl-1],'no data');
                    _setedit (polynom_begin,'0');
                    _setedit (polynom_step,getstring(linepoly.pathlength/line.length,5));
                    _setedit (polynom_end,getstring(linepoly.pathlength,5));
                    linepoly.done;
                    line.done;
               end
               else
               begin
                    if l < 10 then linepoly.init (l)
                              else linepoly.init (10);
                    linepoly.fit (line);
                    for bl := 1 to linepoly.length do _setedit (polynom[bl-1],getstring(linepoly.get(bl),5));
                    if linepoly.length < 10 then
                       for bl := linepoly.length+1 to 10 do _setedit (polynom[bl-1],'no data');
                    _setedit (polynom_begin,'0');
                    _setedit (polynom_step,getstring(linepoly.pathlength/line.length,5));
                    _setedit (polynom_end,getstring(linepoly.pathlength,5));
                    linepoly.done;
                    line.done;
               end;
          end;
      end
      else
      begin
           for bl := 1 to 10 do _setedit (polynom[bl-1],'no data');
           _setedit (polynom_begin,'0');
           _setedit (polynom_step,'0');
           _setedit (polynom_end,'0');
      end;
{ Status }
     my_status (redtext,red,center_red,min_red,max_red);
     my_status (greentext,green,center_green,min_green,max_green);
     my_status (bluetext,blue,center_blue,min_blue,max_blue);

     my_status (yellowtext,yellow,center_yellow,min_yellow,max_yellow);
     my_status (cyantext,cyan,center_cyan,min_cyan,max_cyan);
     my_status (purpletext,purple,center_purple,min_purple,max_purple);

     _settext (alltext,'All layers'+#10+#13+#10+
                         'Points : '+getstring(red.getpointlength+green.getpointlength+blue.getpointlength+yellow.getpointlength+cyan.getpointlength+purple.getpointlength)+#10+
                         'Lines : '+getstring(red.getlinelength+green.getlinelength+blue.getlinelength+yellow.getlinelength+cyan.getlinelength+purple.getlinelength)+#10+
                         'Objects : '+getstring(red.getobjectlength+green.getobjectlength+blue.getobjectlength+yellow.getobjectlength+cyan.getobjectlength+purple.getobjectlength)+#10+' '+#10+
                         'Center : '+getstring(centerall,3)+#10+
                         'Minimum : '+getstring(minall,3)+#10+
                         'Maximum : '+getstring(maxall,3)+#10+
                         'Max-Min : '+getstring(maxall-minall,3)
                         );

     heap := GetFPCHeapStatus;
{     heap1 := SysGetFPCHeapStatus; default fpc heap manager }
     heap2 := GetHeapStatus;
     _settext (memtext,'Red layer: '+getstring(red.memsize,true)+' bytes ('+getstring(red.dynamicmemsize,true)+' bytes)'+#10+
                       'Green layer: '+getstring(green.memsize,true)+' bytes ('+getstring(green.dynamicmemsize,true)+' bytes)'+#10+
                       'Blue layer: '+getstring(blue.memsize,true)+' bytes ('+getstring(blue.dynamicmemsize,true)+' bytes)'+#10+
                       'Yellow layer: '+getstring(yellow.memsize,true)+' bytes ('+getstring(yellow.dynamicmemsize,true)+' bytes)'+#10+
                       'Cyan layer: '+getstring(cyan.memsize,true)+' bytes ('+getstring(cyan.dynamicmemsize,true)+' bytes)'+#10+
                       'Purple layer: '+getstring(purple.memsize,true)+' bytes ('+getstring(purple.dynamicmemsize,true)+' bytes)'+#10+' '+#10+
                       'HEAP MEMORY'+#10+
                       'Maximum allowed size for the heap: '+getstring(heap.MaxHeapSize,true)+' bytes'+#10+
                       'Maximum used size for the heap: '+getstring(heap.MaxHeapUsed,true)+' bytes'+#10+
                       'Current heap size: '+getstring(heap.CurrHeapSize,true)+' bytes'+#10+
                       'Currently used heap size: '+getstring(heap.CurrHeapUsed,true)+' bytes'+#10+
                       'Currently free memory on heap: '+getstring(heap.CurrHeapFree,true)+' bytes'+#10+' '+#10+
{                       'HEAP MEMORY'+#10+
                       'Maximum allowed size for the heap: '+getstring(heap1.MaxHeapSize,true)+' bytes'+#10+
                       'Maximum used size for the heap: '+getstring(heap1.MaxHeapUsed,true)+' bytes'+#10+
                       'Current heap size: '+getstring(heap1.CurrHeapSize,true)+' bytes'+#10+
                       'Currently used heap size: '+getstring(heap1.CurrHeapUsed,true)+' bytes'+#10+
                       'Currently free memory on heap: '+getstring(heap1.CurrHeapFree,true)+' bytes'+#10+' '+#10+}
                       'SYSTEM MEMORY'+#10+
                       'Total amount of available addressable memory: '+getstring(heap2.TotalAddrSpace,true)+' bytes'+#10+
                       'Total amount of uncommitted memory: '+getstring(heap2.TotalUncommitted,true)+' bytes'+#10+
                       'Total amount of committed memory: '+getstring(heap2.TotalCommitted,true)+' bytes'+#10+
                       'Total amount of allocated memory: '+getstring(heap2.TotalAllocated,true)+' bytes'+#10+
                       'Total amount of free memory: '+getstring(heap2.TotalFree,true)+' bytes'+#10+
                       'Total amount of free small memory blocks: '+getstring(heap2.FreeSmall,true)+' bytes'+#10+
                       'Total amount of free large memory blocks: '+getstring(heap2.FreeBig,true)+' bytes'+#10+
                       'Total amount of free process memory: '+getstring(heap2.Unused,true)+' bytes'+#10+
                       'Total bytes of overhead by memory manager : '+getstring(heap2.Overhead,true)+' bytes'+#10+
                       'Last heap error code: '+getstring(heap2.HeapErrorCode)
                       );
     refreshdir;
     m4[1].x := _getreal (transform_matrix_1_1);
     m4[1].y := _getreal (transform_matrix_1_2);
     m4[1].z := _getreal (transform_matrix_1_3);
     m4[1].t := _getreal (transform_matrix_1_4);

     m4[2].x := _getreal (transform_matrix_2_1);
     m4[2].y := _getreal (transform_matrix_2_2);
     m4[2].z := _getreal (transform_matrix_2_3);
     m4[2].t := _getreal (transform_matrix_2_4);

     m4[3].x := _getreal (transform_matrix_3_1);
     m4[3].y := _getreal (transform_matrix_3_2);
     m4[3].z := _getreal (transform_matrix_3_3);
     m4[3].t := _getreal (transform_matrix_3_4);

     m4[4].x := _getreal (transform_matrix_4_1);
     m4[4].y := _getreal (transform_matrix_4_2);
     m4[4].z := _getreal (transform_matrix_4_3);
     m4[4].t := _getreal (transform_matrix_4_4);
     _setedit (transform_det,getstring(det(m4),5));
end;

procedure set_punctuation (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_punctuation,true); end;

procedure unset_punctuation (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_punctuation,false); end;

procedure check_punctuation (p1,macro : gtk_pointer); cdecl;
begin
     if _getcheckbutton(toggle_punctuation) then format.decimal_separator := true else format.decimal_separator := false;
     updating;
     if _getcheckbutton(toggle_punctuation) then tmacro(macro^).writereundo('set.punctuation','unset.punctuation')
                                            else tmacro(macro^).writereundo('unset.punctuation','set.punctuation');
end;

procedure set_format (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_format,true); end;

procedure unset_format (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_format,false); end;

procedure check_format (p1,macro : gtk_pointer); cdecl;
begin
     if _getcheckbutton(toggle_format) then format.vector := true else format.vector := false;
     updating;
     if _getcheckbutton(toggle_format) then tmacro(macro^).writereundo('set.format','unset.format')
                                       else tmacro(macro^).writereundo('unset.format','set.format');
end;

procedure set_exponent (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_exponent,true); end;

procedure unset_exponent (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_exponent,false); end;

procedure check_exponent (p1,macro : gtk_pointer); cdecl;
begin
     if _getcheckbutton(toggle_exponent) then format.scientific_notation := true else format.scientific_notation := false;
     updating;
     if _getcheckbutton(toggle_exponent) then tmacro(macro^).writereundo('set.exponent','unset.exponent')
                                         else tmacro(macro^).writereundo('unset.exponent','set.exponent');
end;

procedure set_degree (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_deg_rad,true); end;

procedure set_radian (p1,macro : gtk_pointer); cdecl;
begin _setcheckbutton(toggle_deg_rad,false); end;

procedure check_deg_rad (p1,macro : gtk_pointer); cdecl;
begin
     if _getcheckbutton(toggle_deg_rad) then format.degree := true else format.degree := false;
     updating;
     if _getcheckbutton(toggle_deg_rad) then tmacro(macro^).writereundo('set.degree','set.radian')
                                        else tmacro(macro^).writereundo('set.radian','set.degree');
end;

{ ************************************** Draw ******************************** }

procedure drawing;
begin
     if ifdraw then
     if small then
     begin
          case _getpage (mainnote) of
               0 :
               begin
                    newdraw (area_xy,xy,screen_xy,1);
                    eraser (area_xy);
                    screen_xz.done;
                    screen_xz.init;
                    screen_yz.done;
                    screen_yz.init;
               end;
               1 :
               begin
                    newdraw (area_xz,xz,screen_xz,2);
                    eraser (area_xz);
                    screen_xy.done;
                    screen_xy.init;
                    screen_yz.done;
                    screen_yz.init;
               end;
               2 :
               begin
                    newdraw (area_yz,yz,screen_yz,3);
                    eraser (area_yz);
                    screen_xy.done;
                    screen_xy.init;
                    screen_xz.done;
                    screen_xz.init;
               end;
               else
               begin
                    screen_xy.done;
                    screen_xy.init;
                    screen_xz.done;
                    screen_xz.init;
                    screen_yz.done;
                    screen_yz.init;
               end;
          end;
     end
     else
     begin
          if area_xy <> nil then
          begin
               newdraw (area_xy,xy,screen_xy,1);
               eraser (area_xy);
          end;

          if area_xz <> nil then
          begin
               newdraw (area_xz,xz,screen_xz,2);
               eraser (area_xz);
          end;

          if area_xt <> nil then
          begin
               newdraw (area_xt,xt,screen_xt,4);
               eraser (area_xt);
          end;

          if area_yz <> nil then
          begin
               newdraw (area_yz,yz,screen_yz,3);
               eraser (area_yz);
          end;

          if area_zt <> nil then
          begin
               newdraw (area_zt,zt,screen_zt,5);
               eraser (area_zt);
          end;
     end;
end;

procedure short_drawing (single : boolean);
begin
     if ifdraw then
     if small then
     begin
          case _getpage (mainnote) of
               0 :
               begin
                    newdraw2 (area_xy,xy,screen_xy,1);
                    eraser (area_xy);
               end;
               1 :
               begin
                    newdraw2 (area_xz,xz,screen_xz,2);
                    eraser (area_xz);
               end;
               2 :
               begin
                    newdraw2 (area_yz,yz,screen_yz,3);
                    eraser (area_yz);
               end;
          end;
     end
     else
     begin
          if single then
          case screen of
              1 :
              begin
                   newdraw2 (area_xy,xy,screen_xy,1);
                   eraser (area_xy);
              end;
              2 :
              begin
                   newdraw2 (area_xz,xz,screen_xz,2);
                   eraser (area_xz);
              end;
              4 :
              begin
                   newdraw2 (area_xt,xt,screen_xt,4);
                   eraser (area_xt);
              end;
              3 :
              begin
                   newdraw2 (area_yz,yz,screen_yz,3);
                   eraser (area_yz);
              end;
              5 :
              begin
                   newdraw2 (area_zt,zt,screen_zt,5);
                   eraser (area_zt);
              end;
          end
          else
          begin
               if area_xy <> nil then
               begin
                    newdraw (area_xy,xy,screen_xy,1);
                    eraser (area_xy);
               end;

               if area_xz <> nil then
               begin
                    newdraw (area_xz,xz,screen_xz,2);
                    eraser (area_xz);
               end;

               if area_xt <> nil then
               begin
                    newdraw (area_xt,xt,screen_xt,4);
                    eraser (area_xt);
               end;

               if area_yz <> nil then
               begin
                    newdraw (area_yz,yz,screen_yz,3);
                    eraser (area_yz);
               end;

               if area_zt <> nil then
               begin
                    newdraw (area_zt,zt,screen_zt,5);
                    eraser (area_zt);
               end;
          end;
     end;
end;

function draw_show (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     ifdraw := true;
     draw_show := gtk_true;
end;

function draw_hide (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     ifdraw := false;
     draw_hide := gtk_true;
end;

function draw_update (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if ifdraw then
     begin
          calculating;
          updating;
          drawing;
          _update;
     end
     else
     begin
          ifdraw := true;
          calculating;
          updating;
          drawing;
          _update;
          ifdraw := false;
     end;
     draw_update := gtk_true;
end;

{ **************************************************************************** }

{ Destination }

function proc_red2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_red2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.red','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'1 '+getstring(ref_state[1]));
          inputedit := 1; finputedit := @red;
          if not ref_state[1] then
          begin
               ref_state[1] := true;
               calculating;
               updating;
               if red.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[1] then
          begin
               ref_state[1] := false;
               calculating;
               updating;
               if red.getpointlength > 0 then drawing;
          end
          else updating;
          tmacro(macro^).writereundo ('unset.ref.red','set.ref.red');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[1] then ref_state[1] := false else ref_state[1] := true;
          calculating;
          updating;
          if red.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('toogle.ref.red','toogle.ref.red');
     end
     else proc_red2 := gtk_false;
end;

procedure setrefred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_red2 (nil,@event,macro); end;

procedure unsetrefred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_red2 (nil,@event,macro); end;

procedure tooglerefred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_red2 (nil,@event,macro); end;

function proc_green2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_green2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.green','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'2 '+getstring(ref_state[2]));
          inputedit := 2; finputedit := @green;
          if not ref_state[2] then
          begin
               ref_state[2] := true;
               calculating;
               updating;
               if green.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[2] then
          begin
               ref_state[2] := false;
               calculating;
               updating;
               if green.getpointlength > 0 then drawing;
               tmacro(macro^).writereundo ('unset.ref.green','set.ref.green');
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[2] then ref_state[2] := false else ref_state[2] := true;
          calculating;
          updating;
          if green.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('toogle.ref.green','toogle.ref.green');
     end
     else proc_green2 := gtk_false;
end;

procedure setrefgreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_green2 (nil,@event,macro); end;

procedure unsetrefgreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_green2 (nil,@event,macro); end;

procedure tooglerefgreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_green2 (nil,@event,macro); end;

function proc_blue2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_blue2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.blue','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'3 '+getstring(ref_state[3]));
          inputedit := 3; finputedit := @blue;
          if not ref_state[3] then
          begin
               ref_state[3] := true;
               calculating;
               updating;
               if blue.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[3] then
          begin
               ref_state[3] := false;
               calculating;
               updating;
               if blue.getpointlength > 0 then drawing;
               tmacro(macro^).writereundo ('unset.ref.blue','set.ref.blue');
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[3] then ref_state[3] := false else ref_state[3] := true;
          calculating;
          updating;
          if blue.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('toogle.ref.blue','toogle.ref.blue');
     end
     else proc_blue2 := gtk_false;
end;

procedure setrefblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_blue2 (nil,@event,macro); end;

procedure unsetrefblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_blue2 (nil,@event,macro); end;

procedure tooglerefblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_blue2 (nil,@event,macro); end;

function proc_yellow2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_yellow2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.yellow','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'4 '+getstring(ref_state[4]));
          inputedit := 4; finputedit := @yellow;
          if not ref_state[4] then
          begin
               ref_state[4] := true;
               calculating;
               updating;
               if yellow.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[4] then
          begin
               ref_state[4] := false;
               calculating;
               updating;
               if yellow.getpointlength > 0 then drawing;
               tmacro(macro^).writereundo ('unset.ref.yellow','set.ref.yellow');
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[4] then ref_state[4] := false else ref_state[4] := true;
          calculating;
          updating;
          if yellow.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('toogle.ref.yellow','toogle.ref.yellow');
     end
     else proc_yellow2 := gtk_false;
end;

procedure setrefyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_yellow2 (nil,@event,macro); end;

procedure unsetrefyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_yellow2 (nil,@event,macro); end;

procedure tooglerefyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_yellow2 (nil,@event,macro); end;

function proc_cyan2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_cyan2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.cyan','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'5 '+getstring(ref_state[5]));
          inputedit := 5; finputedit := @cyan;
          if not ref_state[5] then
          begin
               ref_state[5] := true;
               calculating;
               updating;
               if cyan.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[5] then
          begin
               ref_state[5] := false;
               calculating;
               updating;
               if cyan.getpointlength > 0 then drawing;
               tmacro(macro^).writereundo ('unset.ref.cyan','set.ref.cyan');
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[5] then ref_state[5] := false else ref_state[5] := true;
          calculating;
          updating;
          if cyan.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('unset.ref.cyan','unset.ref.cyan');
     end
     else proc_cyan2 := gtk_false;
end;

procedure setrefcyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_cyan2 (nil,@event,macro); end;

procedure unsetrefcyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_cyan2 (nil,@event,macro); end;

procedure tooglerefcyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_cyan2 (nil,@event,macro); end;

function proc_purple2 (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_purple2 := gtk_true;
     if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.ref.purple','','set.ref',getstring(inputedit)+' '+getstring(ref_state[inputedit])+' '+'6 '+getstring(ref_state[6]));
          inputedit := 6; finputedit := @purple;
          if not ref_state[6] then
          begin
               ref_state[6] := true;
               calculating;
               updating;
               if purple.getpointlength > 0 then drawing;
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          if ref_state[6] then
          begin
               ref_state[6] := false;
               calculating;
               updating;
               if purple.getpointlength > 0 then drawing;
               tmacro(macro^).writereundo ('unset.ref.purple','set.ref.purple');
          end
          else updating;
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if ref_state[6] then ref_state[6] := false else ref_state[6] := true;
          calculating;
          updating;
          if purple.getpointlength > 0 then drawing;
          tmacro(macro^).writereundo ('unset.ref.purple','unset.ref.purple');
     end
     else proc_purple2 := gtk_false;
end;

procedure setrefpurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_purple2 (nil,@event,macro); end;

procedure unsetrefpurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_purple2 (nil,@event,macro); end;

procedure tooglerefpurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_purple2 (nil,@event,macro); end;

procedure setrefall (p1,macro : gtk_pointer); cdecl;
begin
     setrefred (p1,macro);
     setrefgreen (p1,macro);
     setrefblue (p1,macro);
     setrefyellow (p1,macro);
     setrefcyan (p1,macro);
     setrefpurple (p1,macro);
end;

procedure unsetrefall (p1,macro : gtk_pointer); cdecl;
begin
     unsetrefred (p1,macro);
     unsetrefgreen (p1,macro);
     unsetrefblue (p1,macro);
     unsetrefyellow (p1,macro);
     unsetrefcyan (p1,macro);
     unsetrefpurple (p1,macro);
end;

procedure setrefnext (p1,macro : gtk_pointer); cdecl;
begin
     inc (inputedit);
     if inputedit > 6 then inputedit := 6;
     case input of
          1 : setrefred (p1,macro);
          2 : setrefgreen (p1,macro);
          3 : setrefblue (p1,macro);
          4 : setrefyellow (p1,macro);
          5 : setrefcyan (p1,macro);
          6 : setrefpurple (p1,macro);
     end;
end;

procedure unsetrefnext (p1,macro : gtk_pointer); cdecl;
begin
     inc (inputedit);
     if inputedit > 6 then inputedit := 6;
     case input of
          1 : unsetrefred (p1,macro);
          2 : unsetrefgreen (p1,macro);
          3 : unsetrefblue (p1,macro);
          4 : unsetrefyellow (p1,macro);
          5 : unsetrefcyan (p1,macro);
          6 : unsetrefpurple (p1,macro);
     end;
end;

procedure proc_set_ref (p1,macro : gtk_pointer); cdecl;
var old,new : integer;
    oldstate,newstate : boolean;
    event : TGdk_EventButton;
begin
     old := getnat(tmacro(macro^).getparameter (1));
     oldstate := getboolean(tmacro(macro^).getparameter (2));
     new := getnat(tmacro(macro^).getparameter (3));
     newstate := getboolean(tmacro(macro^).getparameter (4));
     case old of
          1 : begin event.button := 1; proc_red2 (nil,@event,macro); end;
          2 : begin event.button := 1; proc_green2 (nil,@event,macro); end;
          3 : begin event.button := 1; proc_blue2 (nil,@event,macro); end;
          4 : begin event.button := 1; proc_yellow2 (nil,@event,macro); end;
          5 : begin event.button := 1; proc_cyan2 (nil,@event,macro); end;
          6 : begin event.button := 1; proc_purple2 (nil,@event,macro); end;
     end;
     if not oldstate then
     case old of
          1 : begin event.button := 3; proc_red2 (nil,@event,macro); end;
          2 : begin event.button := 3; proc_green2 (nil,@event,macro); end;
          3 : begin event.button := 3; proc_blue2 (nil,@event,macro); end;
          4 : begin event.button := 3; proc_yellow2 (nil,@event,macro); end;
          5 : begin event.button := 3; proc_cyan2 (nil,@event,macro); end;
          6 : begin event.button := 3; proc_purple2 (nil,@event,macro); end;
     end;
     if not newstate then
     case new of
          1 : begin event.button := 3; proc_red2 (nil,@event,macro); end;
          2 : begin event.button := 3; proc_green2 (nil,@event,macro); end;
          3 : begin event.button := 3; proc_blue2 (nil,@event,macro); end;
          4 : begin event.button := 3; proc_yellow2 (nil,@event,macro); end;
          5 : begin event.button := 3; proc_cyan2 (nil,@event,macro); end;
          6 : begin event.button := 3; proc_purple2 (nil,@event,macro); end;
     end;
end;

{ Source }

function proc_red (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_red := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefred (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefred (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.red','','set',getstring(input)+' '+getstring(state[input])+' '+'1 '+getstring(state[1]));
          input := 1; finput := @red;
          state[1] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[1] := false;
          updating;
          tmacro(macro^).writereundo ('unset.red','set.red');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[1] then state[1] := false else state[1] := true;
          updating;
          tmacro(macro^).writereundo ('toogle.red','toogle.red');
     end
     else proc_red := gtk_false;
end;

procedure setred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_red (nil,@event,macro); end;

procedure unsetred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_red (nil,@event,macro); end;

procedure tooglered (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_red (nil,@event,macro); end;

procedure setredred (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_red (nil,@event,macro); end;

function proc_green (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_green := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefgreen (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefgreen (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.green','','set',getstring(input)+' '+getstring(state[input])+' '+'2 '+getstring(state[2]));
          input := 2; finput := @green;
          if not state[2] then state[2] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[2] := false;
          updating;
          tmacro(macro^).writereundo ('unset.green','set.green');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[2] then state[2] := false else state[2] := true;
          updating;
          tmacro(macro^).writereundo ('unset.green','unset.green');
     end
     else proc_green := gtk_false;
end;

procedure setgreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_green (nil,@event,macro); end;

procedure unsetgreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_green (nil,@event,macro); end;

procedure tooglegreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_green (nil,@event,macro); end;

procedure setgreengreen (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_green (nil,@event,macro); end;

function proc_blue (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_blue := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefblue (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefblue (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.blue','','set',getstring(input)+' '+getstring(state[input])+' '+'3 '+getstring(state[3]));
          input := 3; finput := @blue;
          if not state[3] then state[3] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[3] := false;
          updating;
          tmacro(macro^).writereundo ('unset.blue','set.blue');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[3] then state[3] := false else state[3] := true;
          updating;
          tmacro(macro^).writereundo ('unset.blue','unset.blue');
     end
     else proc_blue := gtk_false;
end;

procedure setblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_blue (nil,@event,macro); end;

procedure unsetblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_blue (nil,@event,macro); end;

procedure toogleblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_blue (nil,@event,macro); end;

procedure setblueblue (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_blue (nil,@event,macro); end;

function proc_yellow (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_yellow := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefyellow (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefyellow (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.yellow','','set',getstring(input)+' '+getstring(state[input])+' '+'4 '+getstring(state[4]));
          input := 4; finput := @yellow;
          if not state[4] then state[4] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[4] := false;
          updating;
          tmacro(macro^).writereundo ('unset.yellow','set.yellow');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[4] then state[4] := false else state[4] := true;
          updating;
          tmacro(macro^).writereundo ('unset.yellow','unset.yellow');
     end
     else proc_yellow := gtk_false;
end;

procedure setyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_yellow (nil,@event,macro); end;

procedure unsetyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_yellow (nil,@event,macro); end;

procedure toogleyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_yellow (nil,@event,macro); end;

procedure setyellowyellow (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_yellow (nil,@event,macro); end;

function proc_cyan (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_cyan := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefcyan (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefcyan (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.cyan','','set',getstring(input)+' '+getstring(state[input])+' '+'5 '+getstring(state[5]));
          input := 5; finput := @cyan;
          if not state[5] then state[5] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[5] := false;
          updating;
          tmacro(macro^).writereundo ('unset.cyan','set.cyan');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[5] then state[5] := false else state[5] := true;
          updating;
          tmacro(macro^).writereundo ('unset.cyan','unset.cyan');
     end
     else proc_cyan := gtk_false;
end;

procedure setcyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_cyan (nil,@event,macro); end;

procedure unsetcyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_cyan (nil,@event,macro); end;

procedure tooglecyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_cyan (nil,@event,macro); end;

procedure setcyancyan (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_cyan (nil,@event,macro); end;

function proc_purple (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     proc_purple := gtk_true;
     if TGdk_EventButton(event^)._type = GDK_2BUTTON_PRESS then
     begin
          if TGdk_EventButton(event^).button = 1 then setrefpurple (widget,macro)
          else if TGdk_EventButton(event^).button = 3 then unsetrefpurple (widget,macro);
     end
     else if TGdk_EventButton(event^).button = 1 then
     begin
          tmacro(macro^).writereundo ('set.purple','','set',getstring(input)+' '+getstring(state[input])+' '+'6 '+getstring(state[6]));
          input := 6; finput := @purple;
          if not state[6] then state[6] := true;
          updating; short_drawing (false);
     end
     else if TGdk_EventButton(event^).button = 2 then
     begin
          state[6] := false;
          updating;
          tmacro(macro^).writereundo ('unset.purple','set.purple');
     end
     else if TGdk_EventButton(event^).button = 3 then
     begin
          if state[6] then state[6] := false else state[6] := true;
          updating;
          tmacro(macro^).writereundo ('unset.purple','unset.purple');
     end
     else proc_purple := gtk_false;
end;

procedure setpurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 1; proc_purple (nil,@event,macro); end;

procedure unsetpurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 2; proc_purple (nil,@event,macro); end;

procedure tooglepurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event.button := 3; proc_purple (nil,@event,macro); end;

procedure setpurplepurple (p1,macro : gtk_pointer); cdecl;
var event : TGdk_EventButton;
begin event._type := GDK_2BUTTON_PRESS; event.button := 1; proc_purple (nil,@event,macro); end;

procedure setall (p1,macro : gtk_pointer); cdecl;
begin
     setred (p1,macro);
     setgreen (p1,macro);
     setblue (p1,macro);
     setyellow (p1,macro);
     setcyan (p1,macro);
     setpurple (p1,macro);
end;

procedure unsetall (p1,macro : gtk_pointer); cdecl;
begin
     unsetred (p1,macro);
     unsetgreen (p1,macro);
     unsetblue (p1,macro);
     unsetyellow (p1,macro);
     unsetcyan (p1,macro);
     unsetpurple (p1,macro);
end;

procedure setnext (p1,macro : gtk_pointer); cdecl;
begin
     inc (input);
     if input > 6 then input := 6;
     case input of
          1 : setred (p1,macro);
          2 : setgreen (p1,macro);
          3 : setblue (p1,macro);
          4 : setyellow (p1,macro);
          5 : setcyan (p1,macro);
          6 : setpurple (p1,macro);
     end;
end;

procedure unsetnext (p1,macro : gtk_pointer); cdecl;
begin
     inc (input);
     if input > 6 then input := 6;
     case input of
          1 : unsetred (p1,macro);
          2 : unsetgreen (p1,macro);
          3 : unsetblue (p1,macro);
          4 : unsetyellow (p1,macro);
          5 : unsetcyan (p1,macro);
          6 : unsetpurple (p1,macro);
     end;
end;

procedure proc_set (p1,macro : gtk_pointer); cdecl;
var old,new : integer;
    oldstate,newstate : boolean;
    event : TGdk_EventButton;
begin
     old := getnat(tmacro(macro^).getparameter (1));
     oldstate := getboolean(tmacro(macro^).getparameter (2));
     new := getnat(tmacro(macro^).getparameter (3));
     newstate := getboolean(tmacro(macro^).getparameter (4));
     case old of
          1 : begin event.button := 1; proc_red (nil,@event,macro); end;
          2 : begin event.button := 1; proc_green (nil,@event,macro); end;
          3 : begin event.button := 1; proc_blue (nil,@event,macro); end;
          4 : begin event.button := 1; proc_yellow (nil,@event,macro); end;
          5 : begin event.button := 1; proc_cyan (nil,@event,macro); end;
          6 : begin event.button := 1; proc_purple (nil,@event,macro); end;
     end;
     if not oldstate then
     case old of
          1 : begin event.button := 3; proc_red (nil,@event,macro); end;
          2 : begin event.button := 3; proc_green (nil,@event,macro); end;
          3 : begin event.button := 3; proc_blue (nil,@event,macro); end;
          4 : begin event.button := 3; proc_yellow (nil,@event,macro); end;
          5 : begin event.button := 3; proc_cyan (nil,@event,macro); end;
          6 : begin event.button := 3; proc_purple (nil,@event,macro); end;
     end;
     if not newstate then
     case new of
          1 : begin event.button := 3; proc_red (nil,@event,macro); end;
          2 : begin event.button := 3; proc_green (nil,@event,macro); end;
          3 : begin event.button := 3; proc_blue (nil,@event,macro); end;
          4 : begin event.button := 3; proc_yellow (nil,@event,macro); end;
          5 : begin event.button := 3; proc_cyan (nil,@event,macro); end;
          6 : begin event.button := 3; proc_purple (nil,@event,macro); end;
     end;
end;

{ ******************************* Counter ************************************ }

procedure m3pl (p1,macro : gtk_pointer); cdecl;
begin
     finput^.decpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('previous.point','next.point');
end;

procedure m3pr (p1,macro : gtk_pointer); cdecl;
begin
     finput^.incpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('next.point','previous.point');
end;

procedure m3pll (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.decpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastprevious.point','fastnext.point');
end;

procedure m3prr (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.incpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastnext.point','fastprevious.point');
end;

procedure m3pls (p1,macro : gtk_pointer); cdecl;
begin
     finput^.firstpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('first.point','');
end;

procedure m3prs (p1,macro : gtk_pointer); cdecl;
begin
     finput^.lastpointcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('last.point','');
end;

{ ***** }

procedure m3ll (p1,macro : gtk_pointer); cdecl;
begin
     finput^.declinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('previous.line','next.line');
end;

procedure m3lr (p1,macro : gtk_pointer); cdecl;
begin
     finput^.inclinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('next.line','previous.line');
end;

procedure m3lll (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.declinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastprevious.line','fastnext.line');
end;

procedure m3lrr (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.inclinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastnext.line','fastprevious.line');
end;

procedure m3lls (p1,macro : gtk_pointer); cdecl;
begin
     finput^.firstlinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('first.line','');
end;

procedure m3lrs (p1,macro : gtk_pointer); cdecl;
begin
     finput^.lastlinecounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('last.line','');
end;

{ ***** }

procedure m3ol (p1,macro : gtk_pointer); cdecl;
begin
     finput^.decobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('previous.object','next.object');
end;

procedure m3or (p1,macro : gtk_pointer); cdecl;
begin
     finput^.incobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('next.object','previous.object');
end;

procedure m3oll (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.decobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastprevious.object','fastnext.object');
end;

procedure m3orr (p1,macro : gtk_pointer); cdecl;
var x : integer;
begin
     for x := 1 to 10 do finput^.incobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('fastnext.object','fastprevious.object');
end;

procedure m3ols (p1,macro : gtk_pointer); cdecl;
begin
     finput^.firstobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('first.object','');
end;

procedure m3ors (p1,macro : gtk_pointer); cdecl;
begin
     finput^.lastobjectcounter;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('last.object','');
end;

{ ***** }

function proc_point_values (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : hyper;
begin
     if finput^.pointcounter > 0 then
     begin
          s := finput^.getpoint(finput^.pointcounter);
          t := gethyper(_dialog_getinput ('Values for point '+getstring(finput^.pointcounter),getstring(s)));
          finput^.putpoint (finput^.pointcounter,t);
          tmacro(macro^).writereundo ('edit.point.values',getstring(t),'edit.point.values',getstring(s));
          calculating;
          updating;
          drawing;
     end;
     proc_point_values := gtk_true;
end;

function proc_point_values_1 (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : hyper;
begin
     if finput^.pointcounter > 0 then
     begin
          s := finput^.getpoint(finput^.pointcounter);
          t := gethyper(tmacro(macro^).getparameter(1));
          finput^.putpoint (finput^.pointcounter,t);
          calculating;
          updating;
          drawing;
          tmacro(macro^).writereundo ('edit.point.values',getstring(t),'edit.point.values',getstring(s));
     end;
     proc_point_values_1 := gtk_true;
end;

function proc_line_material (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : integer;
begin
     if finput^.linecounter > 0 then
     begin
          s := finput^.getallmaterial(finput^.linecounter);
          t := getnat(_dialog_getinput ('Material for line '+getstring(finput^.linecounter),getstring(s)));
          finput^.putallmaterial (finput^.linecounter,t);
          calculating;
          updating;
          tmacro(macro^).writereundo ('edit.line.material',getstring(t),'edit.line.material',getstring(s));
     end;
     proc_line_material := gtk_true;
end;

function proc_line_material_1 (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : integer;
begin
     if finput^.linecounter > 0 then
     begin
          s := finput^.getallmaterial(finput^.linecounter);
          t := getnat(tmacro(macro^).getparameter(1));
          finput^.putallmaterial (finput^.linecounter,t);
          calculating;
          updating;
          tmacro(macro^).writereundo ('edit.line.material',getstring(t),'edit.line.material',getstring(s));
     end;
     proc_line_material_1 := gtk_true;
end;

function proc_object_name (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : utf16;
begin
     if finput^.objectcounter > 0 then
     begin
          s := finput^.getname(finput^.objectcounter);
          t := _dialog_getinput ('Name for object '+getstring(finput^.objectcounter),s);
          t := killfirst (killlast(t,' '),' ');
          replace (t,' ','_');
          finput^.putname (finput^.objectcounter,t);
          calculating;
          updating;
          tmacro(macro^).writereundo ('edit.object.name','"'+t+'"','edit.object.name','"'+s+'"');
     end;
     proc_object_name := gtk_true;
end;

function proc_object_name_1 (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl;
var s,t : utf16;
begin
     if finput^.objectcounter > 0 then
     begin
          s := finput^.getname(finput^.objectcounter);
          t := tmacro(macro^).getparameter(1);
          t := killfirst (killlast(t,' '),' ');
          replace (t,' ','_');
          finput^.putname (finput^.objectcounter,t);
          calculating;
          updating;
          tmacro(macro^).writereundo ('edit.object.name','"'+t+'"','edit.object.name','"'+s+'"');
     end;
     proc_object_name_1 := gtk_true;
end;

{ ********************************* Brush ************************************ }

procedure proc_bic (p1,macro : gtk_pointer); cdecl;
begin
     _unsetbutton (bool_icircle);
     _setbutton (bool_irectangle);
     _setbutton (bool_ocircle);
     _setbutton (bool_orectangle);
     brush := 1;
     tmacro(macro^).writeredo ('bool.inside.circle');
end;

procedure proc_bir (p1,macro : gtk_pointer); cdecl;
begin
     _setbutton (bool_icircle);
     _unsetbutton (bool_irectangle);
     _setbutton (bool_ocircle);
     _setbutton (bool_orectangle);
     brush := 2;
     tmacro(macro^).writeredo ('bool.inside.rectangle');
end;

procedure proc_boc (p1,macro : gtk_pointer); cdecl;
begin
     _setbutton (bool_icircle);
     _setbutton (bool_irectangle);
     _unsetbutton (bool_ocircle);
     _setbutton (bool_orectangle);
     brush := 11;
     tmacro(macro^).writeredo ('bool.outside.circle');
end;

procedure proc_bor (p1,macro : gtk_pointer); cdecl;
begin
     _setbutton (bool_icircle);
     _setbutton (bool_irectangle);
     _setbutton (bool_ocircle);
     _unsetbutton (bool_orectangle);
     brush := 12;
     tmacro(macro^).writeredo ('bool.outside.rectangle');
end;

{ **************************************************************************** }

procedure cleanup (var a : tcloud);
begin
     if input = inputedit then finputedit^.replace (a)
                          else finputedit^.append (a);
     dummy.clear;
     calculating;
     updating;
     drawing;
end;

procedure cleanupedit (var a : tcloud);
begin
     finputedit^.replace (a);
     dummy.clear;
     calculating;
     updating;
     drawing;
end;

procedure set_buttons;
begin
     _setbutton (bclear);
     _setbutton (blog);
     _setbutton (bopen);
     _setbutton (bcog);
     _unsetbutton (bkill);
end;

procedure reset_buttons;
begin
     _unsetbutton (bclear);
     _unsetbutton (blog);
     _unsetbutton (bopen);
     _unsetbutton (bcog);
     _setbutton (bkill);
end;

{ **************************************************************************** }

{$Include data_file.inc}
{$Include data_input.inc}

{$Include new_1d.inc}
{$Include new_2d.inc}
{$Include new_3d.inc}
{$Include new_4d.inc}

{$Include edit.inc}

{$Include bool.inc}

{$Include transform.inc}

{$Include calculate.inc} { cleanup ok ! }
{$Include calculate_raster.inc} { cleanup ok ! }

{$Include mesh.inc} { cleanup - assign error! }
{$Include loco.inc}

{$Include show_geometry.inc}
{$Include show_povray.inc}

{$Include script.inc}

{ ************************************** Exit ******************************** }

function soft2_quit : boolean;
var s : utf16;
begin
     if macro_save[0] or macro_save[1] or macro_save[2] or macro_save[3] or macro_save[4] or macro_save[5] then
     begin
          s := '';
          if macro_save[0] then s := 'Macro1';
          if macro_save[1] then if s <> '' then s := s+', Macro2' else s := 'Macro2';
          if macro_save[2] then if s <> '' then s := s+', Macro3' else s := 'Macro3';
          if macro_save[3] then if s <> '' then s := s+', Macro4' else s := 'Macro4';
          if macro_save[4] then if s <> '' then s := s+', Macro5' else s := 'Macro5';
          if macro_save[5] then if s <> '' then s := s+', Macro6' else s := 'Macro6';
          soft2_quit := _dialog_yes_no ('Unsaved data!','Unsaved data at ('+s+')','Really quit?');
     end
     else soft2_quit := true;
end;

function soft_quit : boolean;
var s : utf16;
begin
     if red.change or green.change or blue.change or yellow.change or cyan.change or purple.change then
     begin
          s := '';
          if red.change then s := 'red';
          if green.change then if s <> '' then s := s+', green' else s := 'green';
          if blue.change then if s <> '' then s := s+', blue' else s := 'blue';
          if yellow.change then if s <> '' then s := s+', yellow' else s := 'yellow';
          if cyan.change then if s <> '' then s := s+', cyan' else s := 'cyan';
          if purple.change then if s <> '' then s := s+', purple' else s := 'purple';
          if length (s) <= 6 then s := s+') layer' else s := s+') layers';
          soft_quit := soft2_quit and _dialog_yes_no ('Unsaved data!','Unsaved data at ('+s+ '!','Really quit?');
     end
     else soft_quit := soft2_quit;
end;

{ Close application ? }
function close_application (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl; { delete_event }
begin
     { true = nothing
       false = emit signal destroy}
     if (tmacro(macro^).running) then
        if _dialog_yes_no ('Kill macro!','Running macro!','Really quit?') then tmacro(macro^).kill;
     if soft_quit then close_application := gtk_false
                  else close_application := gtk_true;
end;

function quit (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl; { command -> close_application }
begin
     if soft_quit then _quit;
     quit := gtk_false;
end;

function hardquit (p1,p2,macro : gtk_pointer) : gtk_boolean; cdecl; { command -> hard close_application }
begin
     _quit;
     hardquit := gtk_false;
end;

{ Destroy application } { destroy }
function destroy (p1,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     _quit;
     destroy := gtk_false;
end;

{ ************************************** Screen ****************************** }

{$I screen.inc}

{ ************************************* Keyboard ***************************** }

{$include keys.inc}

procedure my_undo;
var i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          {writeln ('>:'+pre_buf+'|'+new_buf+'|'+post_buf);}
          post_buf := new_buf;
          new_buf := pre_buf;
          {pre_buf ––– nothing }
          {writeln ('<:'+pre_buf+'|'+new_buf+'|'+post_buf);}
          stop_change := true;
          _setedittext (macro_text[i],new_buf);
          stop_change := false;
     end;
end;

procedure my_redo;
var i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          {writeln ('>:'+pre_buf+'|'+new_buf+'|'+post_buf);}
          pre_buf := new_buf;
          new_buf := post_buf;
          { post_buf ––– nothing }
          {writeln ('<:'+pre_buf+'|'+new_buf+'|'+post_buf);}
          stop_change := true;
          _setedittext (macro_text[i],new_buf);
          stop_change := false;
     end;
end;

procedure proc_setred (p1,macro : gtk_pointer); cdecl;
begin
     keyred := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setgreen (p1,macro : gtk_pointer); cdecl;
begin
     keygreen := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setblue (p1,macro : gtk_pointer); cdecl;
begin
     keyblue := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setyellow (p1,macro : gtk_pointer); cdecl;
begin
     keyyellow := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setcyan (p1,macro : gtk_pointer); cdecl;
begin
     keycyan := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setpurple (p1,macro : gtk_pointer); cdecl;
begin
     keypurple := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setnewline (p1,macro : gtk_pointer); cdecl;
begin
     keynewline := finput^.getpoint (finput^.getpointlength);
end;

procedure proc_setnewobject (p1,macro : gtk_pointer); cdecl;
begin
     keynewobject := finput^.getpoint (finput^.getpointlength);
end;

function keypress (widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
var e : TGdk_EventButton;
    v : hyper;
begin
     keypress := gtk_true;

     { Special --- File -- Mircoscribe  or  Small - Mainnote }
     if ((_getpage (note) = datanote_file) and (_getpage (subnote_data) = datanote_inscribe)) or ((small) and (_getpage (mainnote) <> 3)) then
     begin
          case TGdk_EventKey(event^).keyval  of
               GDK_p,GDK_Capital_P,GDK_numbersign {#} :
                    begin
                         _setlabel (m3dlabel,minput);
                         v := gethyper (minput);
                         minput := '';
                         if v = Hzero then
                         else if (keyred <> Hzero) and (getlength(keyred-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 1; updating; drawing; end
                         else if (keygreen <> Hzero) and (getlength(keygreen-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 2; updating; drawing; end
                         else if (keyblue <> Hzero) and (getlength(keyblue-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 3; updating; drawing; end
                         else if (keyyellow <> Hzero) and (getlength(keyyellow-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 4; updating; drawing; end
                         else if (keycyan <> Hzero) and (getlength(keycyan-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 5; updating; drawing; end
                         else if (keypurple <> Hzero) and (getlength(keypurple-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin input := 6; updating; drawing; end
                         else if (keynewline <> Hzero) and (getlength(keynewline-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin proc_mic_newline (nil,macro); updating; drawing; end
                         else if (keynewobject <> Hzero) and (getlength(keynewline-v) < _getreal (edit_microscribe_keyboard_sensitivity)) then begin proc_mic_newobject (nil,macro); updating; drawing; end
                         else
                         begin
                              finput^.newpoint (v);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               GDK_l,GDK_Capital_L,GDK_space : begin proc_mic_newline (nil,macro); updating; drawing; end;
               GDK_o,GDK_Capital_O,GDK_return : begin proc_mic_newobject (nil,macro); updating; drawing; end;
               GDK_minus,GDK_plus_key,GDK_0..GDK_9,GDK_period,GDK_colon,GDK_semicolon :
                    begin
                         minput := minput + getutf16(TGdk_EventKey(event^).keyval mod 128);
                         _setlabel (m3dlabel,minput);
                    end;
               gdk_f1 : begin screen := 1; updating; drawing; end;
               gdk_f2 : begin screen := 2; updating; drawing; end;
               gdk_f4 : begin screen := 4; updating; drawing; end;
               gdk_f3 : begin screen := 3; updating; drawing; end;
               gdk_f5 : begin screen := 5; updating; drawing; end;
               gdk_f11 : _togglefullscreen;
               gdk_f12 : _togglemaximize;
               gdk_escape : quit (widget,event,macro);
               else keypress := gtk_false;
          end;
     end
     else if ((_getpage (note) = scriptnote)) then
     begin
          case (TGdk_EventKey(event^).state and $F) of { only first four bits }
               GDK_SHIFT_MASK : keypress := gtk_false { Shift };
               GDK_LOCK_MASK :  keypress := gtk_false { Shift Lock };

               GDK_CONTROL_MASK :  { Strg }
               begin
                    case TGdk_EventKey(event^).keyval of
                         GDK_z, GDK_Capital_Z : begin my_undo; end;
                         else keypress := gtk_false;
                    end;
               end;
               (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
               begin
                    case TGdk_EventKey(event^).keyval of
                         gdk_z, GDK_Capital_Z : begin my_redo; end;
                         else keypress := gtk_false;
                    end;
               end
               else { Rest }
               begin
                    {writeln (getstring(event^.keyval));}
                    case TGdk_EventKey(event^).keyval  of
                         gdk_f1 : begin screen := 1; updating; drawing; end;
                         gdk_f2 : begin screen := 2; updating; drawing; end;
                         gdk_f4 : begin screen := 4; updating; drawing; end;
                         gdk_f3 : begin screen := 3; updating; drawing; end;
                         gdk_f5 : begin screen := 5; updating; drawing; end;
                         gdk_f11 : _togglefullscreen;
                         gdk_f12 : _togglemaximize;
                         gdk_escape : quit (widget,event,macro);
                         else keypress := gtk_false;
                    end;
               end;
          end;
     end
     else
     begin
          case (TGdk_EventKey(event^).state and $F) of { only first four bits }
               GDK_SHIFT_MASK : keypress := gtk_false { Shift };
               GDK_LOCK_MASK :  keypress := gtk_false { Shift Lock };

               GDK_CONTROL_MASK :  { Strg }
               begin
                    case TGdk_EventKey(event^).keyval of
                         GDK_KP_Subtract : begin global_zoom := 1.5 * global_zoom; drawing; end;
                         GDK_KP_Add : begin global_zoom := global_zoom / 1.5; drawing; end;
                         GDK_KP_Multiply,GDK_KP_Divide : begin global_zoom := 1; drawing; end;

                         GDK_KP_5 : begin global_center := Hzero; drawing; end;
                         GDK_KP_4 : begin global_center := global_center + gh ((maxall.x-minall.x)/10,0,0,0); drawing; end;
                         GDK_KP_6 : begin global_center := global_center - gh ((maxall.x-minall.x)/10,0,0,0); drawing; end;
                         GDK_KP_8 : begin global_center := global_center - gh (0,(maxall.y-minall.y)/10,0,0); drawing; end;
                         GDK_KP_2 : begin global_center := global_center + gh (0,(maxall.y-minall.y)/10,0,0); drawing; end;
                         GDK_KP_9 : begin global_center := global_center - gh (0,0,(maxall.z-minall.z)/10,0); drawing; end;
                         GDK_KP_3 : begin global_center := global_center + gh (0,0,(maxall.z-minall.z)/10,0); drawing; end;
                         GDK_KP_7 : begin global_center := global_center - gh (0,0,0,(maxall.t-minall.t)/10); drawing; end;
                         GDK_KP_1 : begin global_center := global_center + gh (0,0,0,(maxall.t-minall.t)/10); drawing; end;

                         GDK_z, GDK_Capital_Z : begin tmacro(macro^).undo; end;
                         else keypress := gtk_false;
                    end;
               end;
               (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
               begin
                    case TGdk_EventKey(event^).keyval of
                         gdk_z, GDK_Capital_Z : begin tmacro(macro^).redo; end;
                         else keypress := gtk_false;
                    end;
               end;
               GDK_MOD1_MASK : { Alt }
               begin
                    case TGdk_EventKey(event^).keyval of
                         GDK_p,GDK_Capital_P : m3pr (widget,macro);
                         GDK_l,GDK_Capital_L : m3lr (widget,macro);
                         GDK_o,GDK_Capital_O : m3or (widget,macro);

                         GDK_r,GDK_Capital_R : begin e.button := 1; proc_red (nil,@e,macro); end;
                         GDK_g,GDK_Capital_G : begin e.button := 1; proc_green (nil,@e,macro); end;
                         GDK_b,GDK_Capital_B : begin e.button := 1; proc_blue (nil,@e,macro); end;
                         GDK_y,GDK_Capital_Y : begin e.button := 1; proc_yellow (nil,@e,macro); end;
                         GDK_c,GDK_Capital_C : begin e.button := 1; proc_cyan (nil,@e,macro); end;
                         GDK_e,GDK_Capital_E : begin e.button := 1; proc_purple (nil,@e,macro); end;
                         else keypress := gtk_false;
                    end;
               end;
               (GDK_SHIFT_MASK or GDK_MOD1_MASK) : { Shift + Alt }
               begin
                    case TGdk_EventKey(event^).keyval of
                         GDK_p,GDK_Capital_P : m3pl (widget,macro);
                         GDK_l,GDK_Capital_L : m3ll (widget,macro);
                         GDK_o,GDK_Capital_O : m3ol (widget,macro);

                         GDK_r,GDK_Capital_R : begin e.button := 1; proc_red2 (nil,@e,macro); end;
                         GDK_g,GDK_Capital_G : begin e.button := 1; proc_green2 (nil,@e,macro); end;
                         GDK_b,GDK_Capital_B : begin e.button := 1; proc_blue2 (nil,@e,macro); end;
                         GDK_y,GDK_Capital_Y : begin e.button := 1; proc_yellow2 (nil,@e,macro); end;
                         GDK_c,GDK_Capital_C : begin e.button := 1; proc_cyan2 (nil,@e,macro); end;
                         GDK_e,GDK_Capital_E : begin e.button := 1; proc_purple2 (nil,@e,macro); end;
                         else keypress := gtk_false;
                    end;
               end;
               else { Rest }
               begin
                    {writeln (getstring(event^.keyval));}
                    case TGdk_EventKey(event^).keyval of
                         gdk_f1 : begin screen := 1; updating; drawing; end;
                         gdk_f2 : begin screen := 2; updating; drawing; end;
                         gdk_f4 : begin screen := 4; updating; drawing; end;
                         gdk_f3 : begin screen := 3; updating; drawing; end;
                         gdk_f5 : begin screen := 5; updating; drawing; end;

                         gdk_f11 : _togglefullscreen;
                         gdk_f12 : _togglemaximize;
                         gdk_escape : quit (widget,event,macro);
                         else keypress := gtk_false;
                    end;
               end;
          end;
     end;
end;

var progress_dialog : gtk_widget;

procedure progress;
begin
     if output_state = 0 then
     begin
          progress_dialog := _progress ('Progress',#10+fillcenter(output_progress,40)+#10,0.1,output_state,(output_pleasewait = 0));
          _cursor_watch (progress_dialog);
     end
     else
     begin
          if progress_dialog <> nil then
          if output_state < 1 then
          begin
               _set_progress (0.1,output_state,(output_pleasewait = 0));
          end
          else
          begin
               _set_progress (0.1,1,(output_pleasewait = 0));
               _update;
               _destroy (progress_dialog);
               progress_dialog := nil;
          end;
     end;
     _update;
end;

{ **************************************************************************** }

{function gettext (const s : utf16) : utf16; { replacer for libpo }
begin
     gettext := s;
end;}

function command (xpm : pointer;const c,i,o,h : utf16;func : cprocpp) : gtk_widget; { icon }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (xpm,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (xpm,func,@macro_self),'Code: '+c+' '+i);
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (xpm,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (xpm,func,@macro_self),'Code: '+c);
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func);
     end
     else command := _tooltip (_button (xpm,func,@macro_self),gettext(h));
end;

function command (xpm : pointer;const c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { icon - split }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (xpm,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (xpm,func,@macro_self),'Code: '+c+' '+i);
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (xpm,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (xpm,func,@macro_self),'Code: '+c);
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func1);
     end
     else command := _tooltip (_button (xpm,func,@macro_self),gettext(h));
end;

function command (xpm : pointer;const n,c,i,o,h : utf16;func : cprocpp) : gtk_widget; { icon + text }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (xpm,' '+n,func,@macro_self),'Code: '+c+' '+i);
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (xpm,' '+n,func,@macro_self),'Code: '+c);
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func);
     end
     else command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h));
end;

function command (xpm : pointer;const n,c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { icon + text - split }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (xpm,' '+n,func,@macro_self),'Code: '+c+' '+i);
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (xpm,' '+n,func,@macro_self),'Code: '+c);
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func1);
     end
     else command := _tooltip (_button (xpm,' '+n,func,@macro_self),gettext(h));
end;

function command (const n,c,i,o,h : utf16;func : cprocpp) : gtk_widget; { text }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (n,func,@macro_self),'Code: '+c+' '+i);
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (n,func,@macro_self),'Code: '+c);
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func);
     end
     else command := _tooltip (_button (n,func,@macro_self),gettext(h));
end;

function command (const n,c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { text - split }
begin
     if c <> '' then
     begin
          if i <> '' then
          begin
               if h <> '' then command := _tooltip (_button (n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c+' '+i)
                          else command := _tooltip (_button (n,func,@macro_self),'Code: '+c+' '+i)
          end
          else
          begin
               if h <> '' then command := _tooltip (_button (n,func,@macro_self),gettext(h)+#10+#10+'Code: '+c)
                          else command := _tooltip (_button (n,func,@macro_self),'Code: '+c)
          end;
          macro_self.putprocedure (c,i,o,gettext(h),func1);
     end
     else command := _tooltip (_button (n,func,@macro_self),gettext(h));
end;

function hidecommand (xpm : pointer;const c,i,o,h : utf16;func : cprocpp) : gtk_widget; { hide icon }
begin
     hidecommand := _tooltip (_hidebutton (xpm,func,@macro_self),gettext(h));
end;

function hidecommand (xpm : pointer;const c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { hide icon - split }
begin
     hidecommand := _tooltip (_hidebutton (xpm,func,@macro_self),gettext(h));
end;

function hidecommand (xpm : pointer;const n,c,i,o,h : utf16;func : cprocpp) : gtk_widget; { hide icon+text }
begin
     hidecommand := _tooltip (_hidebutton (xpm,' '+n,func,@macro_self),gettext(h));
end;

function hidecommand (xpm : pointer;const n,c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { hide icon+text - split }
begin
     hidecommand := _tooltip (_hidebutton (xpm,' '+n,func,@macro_self),gettext(h));
end;

function hidecommand (const n,c,i,o,h : utf16;func : cprocpp) : gtk_widget; { hide text }
begin
     hidecommand := _tooltip (_hidebutton (n,func,@macro_self),gettext(h));
end;

function hidecommand (const n,c,i,o,h : utf16;func,func1 : cprocpp) : gtk_widget; { hide text - split }
begin
     hidecommand := _tooltip (_hidebutton (n,func,@macro_self),gettext(h));
end;

{ ***************************** Hauptprogramm ******************************** }

function exposed_splash (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
var splash : trgb;
    phong : Tphong_shader;
    x,y,r : integer;
    d : utf8;
    year,month,day : integer;
    _name,_copyright : utf16;
procedure mycircle (x,y,r : integer);
begin
     splash.value := gvn ($D0,$D0,$FF);
     splash.sphere (x,y,r,phong); {fullcircle (x,y,r);}
     splash.value := gvn ($C0,$C0,$FF);
     splash.circle (x,y,r);
end;
begin
     splash := Default(trgb);
     phong := Default(tphong_shader);
     splash.init(image^.allocation.width,image^.allocation.height);
     splash.background := gvn ($FF,$FF,$FF);
     splash.clear;
{ cloud }
     x := 176;
     y := -572+119;
     r  := 80;
     phong.init;
     phong.light := gv(-10*r,-10*r,10*r);
     phong.light_range := 64;
     phong.ambient := 0.1;
     phong.diffuse := 0.5;
     phong.specular := 0.4;
     mycircle (x+118,y+677,80);
     mycircle (x+-19,y+750,80);
     mycircle (x+298,y+750,80);
     mycircle (x+273,y+698,80);
     mycircle (x+199,y+750,80);
     mycircle (x+82,y+738,80);
     mycircle (x+76,y+638,80);
     mycircle (x+207,y+614,80);
     phong.light_range := 32+16;
     splash.value := gvn ($D0,$D0,$FF);
     splash.sphere (x+128,y+750,80,phong);
     splash.sphere (x+254,y+750,80,phong);
     splash.sphere (x+71,y+750,80,phong);
     splash.sphere (x+128,y+750,80,phong);
     splash.sphere (x+160,y+670,80,phong);
     phong.done;
{ copyright }
     splash.value := gvn ($00,$00,$00);
     d := {$I %date%};
     year := liball.getnat (copy(d,1,4));
     month := liball.getnat (copy(d,6,2));
     day := liball.getnat (copy(d,9,2));
     _name := 'Version '+liball.getstring(year-2005)+'.'+liball.getstring(month)+'.'+liball.getstring(day)+' for '+{$I %fpctargetos%}+' ('+{$I %fpctargetcpu}+')';
     _copyright := 'Copyright (c) '+liball.getstring(2005)+'-'+liball.getstring(year)+' by Heiko Stark';
     splash.write(640,480-16,getreplace(_name,'_','-'),9);
     splash.write(640,480,_copyright,9);
{ titel }
     splash.setfont(2); { bold }
     splash.value := gvn ($E0,$E0,$E0);
     splash.setfontsize (3*8+3,3*16+3);
     splash.write (640 div 2,480 div 2,'Cloud^2',5);
     splash.value := gvn ($C0,$C0,$C0);
     splash.setfontsize (3*8+2,3*16+2);
     splash.write (640 div 2,480 div 2,'Cloud^2',5);
     splash.value := gvn ($A0,$A0,$A0);
     splash.setfontsize (3*8+1,3*16+1);
     splash.write (640 div 2,480 div 2,'Cloud^2',5);
     splash.value := gvn ($00,$00,$00);
     splash.setfontsize (3*8,3*16);
     splash.write (640 div 2,480 div 2,'Cloud^2',5);
     splash.setfont(0); { normal }
{ smooth }
     splash.smooth (640 div 2 -100,480 div 2-100,640 div 2 +100,480 div 2 +100);
     splash.smooth (640 div 2 -100,480 div 2-100,640 div 2 +100,480 div 2 +100);
     splash.unsharpmasking (640 div 2 -100,480 div 2-100,640 div 2 +100,480 div 2 +100);
{     splash.save ('test.png');}
     _drawrgb (image^.window,splash);
     splash.done;
     exposed_splash := gtk_true;
end;

procedure commands;
begin
     note := _notebook;

          incnote := 0;
          incnote_sub := 0;
          _page ('Data ');
          subnote_data := _notebook;
              {$include gui/gui-data.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('New ');
          subnote_new := _notebook;
              {$include gui/gui-new.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('Edit ');
          subnote_editing := _notebook;
              {$include gui/gui-edit.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          boolnote := incnote;
          incnote_sub := 0;
          _page ('Bool ');
          _hbox;
          _fill;
                subnote_boolean := _notebook;
                {$include gui/gui-bool.inc}
                _endnotebook;
          _shrink;
                {$include gui/gui-bool-toolbox.inc}
          _endbox;
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('Trans ');
          subnote_transform := _notebook;
                {$include gui/gui-transform.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('Calc ');
          subnote_calculate := _notebook;
               {$include gui/gui-calc.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('Mesh ');
          subnote_mesh := _notebook;
               {$include gui/gui-mesh.inc}
          _endnotebook;
          _endpage;

{$ifndef free}
          inc(incnote);
          incnote_sub := 0;
          _page ('Motion ');
          subnote_loco := _notebook;
               {$include gui/gui-loco.inc}
          _endnotebook;
          _endpage;
{$endif}

          inc(incnote);
          incnote_sub := 0;
          _page ('Show ');
          subnote_show := _notebook;
               {$include gui/gui-show.inc}
          _endnotebook;
          _endpage;

          inc(incnote);
          scriptnote := incnote;
          incnote_sub := 0;
          _page ('Script ');
               {$include gui/gui-script.inc}
          _endpage;

          inc(incnote);
          incnote_sub := 0;
          _page ('State ');
          subnote_info := _notebook;
               {$include gui/gui-state.inc}
          _endnotebook;
          _endpage;

     _endnotebook;
end;

{ **************************************************************************** }

{$R *.res}

begin
     para := Default(tparameter);
     fillbyte (macro_self,sizeof(tmacro),0);
     list := Default (tpolynat);

     for x := 1 to 6 do stat[x] := Default (tpolyreal);
     for x := 1 to 6 do cstat[x] := Default (tpolycomplex);

     dummy := Default(tcloud);
     red := Default(tcloud);
     green := Default(tcloud);
     blue := Default(tcloud);
     yellow := Default(tcloud);
     cyan := Default(tcloud);
     purple := Default(tcloud);

     screen_xy := Default(trgba);
     screen_xz := Default(trgba);
     screen_yz := Default(trgba);
     screen_xt := Default(trgba);
     screen_zt := Default(trgba);
     screen_histo := Default(thistogram);

     checkcurrentdir;

     para.init ('Cloud2','Heiko Stark',2005,'http://download.stark-jena.de/cloud2');
     para.usage('cloud2');
{$ifndef free}
     para.getlicence;
{$endif}
     para.topic ('Widget');
     full := para.getboolean ('full',true,'Full window');
     small := para.getboolean ('small',false,'Small (tabed) window');
     table_long := para.getboolean ('long',false,'Long xy and zt view');
     table_wide := para.getboolean ('wide',false,'Wide xy and zt view');
     table_special := para.getboolean ('special',false,'Special xy, xz and xt view');

     para.topic ('Macro');
     runmacro := killfirst (killlast (killfirst (killlast (para.getlaststring ('macro','','Run script (macro) file'),'"'),'"'),''''),'''');
     runrefresh := para.getboolean ('refresh',false,'Refresh gui at runtime');
     runexit := para.getboolean ('exit',false,'Exit gui after run');
     runask := para.getboolean ('ask',true,'Ask on exit for unsaved data');

     para.topic ('Language');
     generate_po (para.getstring('make_po','','Make po file'));
     use_po (para.getstring('use_po','','Use po file'));

     para.example('cloud2 -macro=my.macro');

     macro_self.init;
     macro_self.use_all;

     pre_buf := '';
     new_buf := '';
     post_buf := '';

     if para.pair_length > 0 then
     begin
          for x := 1  to para.pair_length do
          begin
               para.getpair (x,s,t);
               macro_self.putconstant('parameter.'+s,t);
          end;
     end;

     para.done;

if _gtk then
begin
     _begin_splash;
     splash := _subwindow ('Cloud2',640,480);
            _border (splash, 0);
            _decor (splash, gtk_FALSE);
            _resize (splash, gtk_FALSE);
            _center (splash);
            image := _canvas;
            _exposed (image,@exposed_splash,nil);
     _endsubwindow;
     _end_splash;
     _update;

     macro_self.putconstant ('point.length','0');
     macro_self.putconstant ('point.count','0');
     macro_self.putconstant ('line.length','0');
     macro_self.putconstant ('line.count','0');
     macro_self.putconstant ('line.material','0');
     macro_self.putconstant ('object.length','0');
     macro_self.putconstant ('object.count','0');
     macro_self.putconstant ('object.name','');

     macro_self.putprocedure ('quit','','','Quit program',@quit);
     macro_self.putprocedure ('hardquit','','','Quit program without promt',@hardquit);
     macro_self.putprocedure ('fixx',@proc_fix_x);
     macro_self.putprocedure ('fixy',@proc_fix_y);
     macro_self.putprocedure ('unfix',@proc_unfix);

     screen_xy.init;
     screen_xz.init;
     screen_yz.init;
     screen_xt.init;
     screen_zt.init;
     screen_histo.init;

     dummy.init;
     red.init;
     green.init;
     blue.init;
     yellow.init;
     cyan.init;
     purple.init;

     screen := 1;

     input := 1;
     finput := @red;

     inputedit := 1;
     finputedit := @red;

     brush := 1;

     state[1] := true;
     state[2] := false;
     state[3] := false;
     state[4] := false;
     state[5] := false;
     state[6] := false;

     ref_state[1] := true;
     ref_state[2] := false;
     ref_state[3] := false;
     ref_state[4] := false;
     ref_state[5] := false;
     ref_state[6] := false;

     macro_self.putprocedure ('set',@proc_set);
     macro_self.putprocedure ('set.ref',@proc_set_ref);

     inputmethod := 3;
     
     minall := gethyper (-1,-1,-1,-1);
     maxall := gethyper (1,1,1,1);
     centerall := Hzero;

     keyred := Hzero;
     keygreen := Hzero;
     keyblue := Hzero;
     keyyellow := Hzero;
     keycyan := Hzero;
     keypurple := Hzero;
     keynewline := Hzero;

     minput := '';

     for x := 1 to 6 do stat[x].init;
     for x := 1 to 6 do cstat[x].init;
     statname := '';
     statobjects := '';
     stattype := 0; { 0=none 1=real 2=complex }

     for x := 0 to macro_length do
     begin
          macro_save[x] := false;
          {$ifdef threading}macro_process[x] := Tprocess.Create(nil);{$endif}
          macro_filename[x] := 'Macro'+getstring(x+1);
     end;

     ifdraw := true;
     macro_self.putprocedure ('draw.show',@draw_show);
     macro_self.putprocedure ('draw.hide',@draw_hide);
     macro_self.putprocedure ('draw.update',@draw_update);

window := _window;
        if not(small) and full then _maximize;
        _over (splash,window);
        _update;
        if not(small) then
        begin
             _table (2,2);
                    if table_long then
                    begin
                         _cell (0,1,0,2);
                         _shrink;
                               _framebox {('X-Y screen (F1)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xy_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xy_scrolled,@macro_self);
                                                _cursor_moved (@screen_xy_moved,@macro_self);
                                                area_xy := _canvas;
                                                _exposed (area_xy,@Exposed_xy,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (1,2,0,1);
                         _shrink;
                               _framebox {('Z-T screen (F5)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_zt_pressed,@macro_self);
                                                _cursor_scrolled (@screen_zt_scrolled,@macro_self);
                                                _cursor_moved (@screen_zt_moved,@macro_self);
                                                area_zt := _canvas;
                                                _exposed (area_zt,@Exposed_zt,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                    end
                    else if table_wide then
                    begin
                         _cell (0,2,0,1);
                         _shrink;
                               _framebox {('X-Y screen (F1)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xy_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xy_scrolled,@macro_self);
                                                _cursor_moved (@screen_xy_moved,@macro_self);
                                                area_xy := _canvas;
                                                _exposed (area_xy,@Exposed_xy,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (0,1,1,2);
                         _shrink;
                               _framebox {('Z-T screen (F5)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_zt_pressed,@macro_self);
                                                _cursor_scrolled (@screen_zt_scrolled,@macro_self);
                                                _cursor_moved (@screen_zt_moved,@macro_self);
                                                area_zt := _canvas;
                                                _exposed (area_zt,@Exposed_zt,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                    end
                    else if table_special then
                    begin
                         _cell (0,1,0,1);
                         _shrink;
                               _framebox {('X-Y screen (F1)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xy_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xy_scrolled,@macro_self);
                                                _cursor_moved (@screen_xy_moved,@macro_self);
                                                area_xy := _canvas;
                                                _exposed (area_xy,@Exposed_xy,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (1,2,0,1);
                         _shrink;
                               _framebox {('X-Z screen (F2)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xz_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xz_scrolled,@macro_self);
                                                _cursor_moved (@screen_xz_moved,@macro_self);
                                                area_xz := _canvas;
                                                _exposed (area_xz,@Exposed_xz,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (0,1,1,2);
                         _shrink;
                               _framebox {('X-T screen (F4)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xt_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xt_scrolled,@macro_self);
                                                _cursor_moved (@screen_xt_moved,@macro_self);
                                                area_xt := _canvas;
                                                _exposed (area_xt,@Exposed_xt,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                    end
                    else
                    begin
                         _cell (0,1,0,1);
                         _shrink;
                               _framebox {('X-Y screen (F1)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xy_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xy_scrolled,@macro_self);
                                                _cursor_moved (@screen_xy_moved,@macro_self);
                                                area_xy := _canvas;
                                                _exposed (area_xy,@Exposed_xy,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (1,2,0,1);
                         _shrink;
                               _framebox {('X-Z screen (F2)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_xz_pressed,@macro_self);
                                                _cursor_scrolled (@screen_xz_scrolled,@macro_self);
                                                _cursor_moved (@screen_xz_moved,@macro_self);
                                                area_xz := _canvas;
                                                _exposed (area_xz,@Exposed_xz,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                         _cell (0,1,1,2);
                         _shrink;
                               _framebox {('Y-Z screen (F3)')};
                                      _eventbox;
                                                _cursor_pressed (@screen_yz_pressed,@macro_self);
                                                _cursor_scrolled (@screen_yz_scrolled,@macro_self);
                                                _cursor_moved (@screen_yz_moved,@macro_self);
                                                area_yz := _canvas;
                                                _exposed (area_yz,@Exposed_yz,@macro_self);
                                      _endbox;
                               _endbox;
                         _endcell;
                    end;
                    _cell (1,2,1,2);
                    _shrink;
                          _vbox;
                          _shrink;
                              {$include gui/gui-source.inc}
                          _fill;
                              commands; { all commands }
                          _shrink;
                              {$include gui/gui-destination.inc}
                          _endbox;
                    _endcell;
             _endtable;
        end
        else { if small }
        begin
{$ifndef free}
        _vpanedbox;
{$endif}
             mainnote := _notebook;
                       _page (' X-Y screen (F1) ');
                             _eventbox;
                                       _cursor_pressed (@screen_xy_pressed,@macro_self);
                                       _cursor_scrolled (@screen_xy_scrolled,@macro_self);
                                       _cursor_moved (@screen_xy_moved,@macro_self);
                                       area_xy := _canvas;
                                       _exposed (area_xy,@Exposed_xy,@macro_self);
                             _endbox;
                       _endpage;
                       _page (' X-Z screen (F2) ');
                             _eventbox;
                                       _cursor_pressed (@screen_xz_pressed,@macro_self);
                                       _cursor_scrolled (@screen_xz_scrolled,@macro_self);
                                       _cursor_moved (@screen_xz_moved,@macro_self);
                                       area_xz := _canvas;
                                       _exposed (area_xz,@Exposed_xz,@macro_self);
                             _endbox;
                       _endpage;
                       _page (' Y-Z screen (F3) ');
                             _eventbox;
                                       _cursor_pressed (@screen_yz_pressed,@macro_self);
                                       _cursor_scrolled (@screen_yz_scrolled,@macro_self);
                                       _cursor_moved (@screen_yz_moved,@macro_self);
                                       area_yz := _canvas;
                                       _exposed (area_yz,@Exposed_yz,@macro_self);
                             _endbox;
                       _endpage;
                       _page (' Main ');
                          _vbox;
                          _shrink;
                              {$include gui/gui-source.inc}
                          _fill;
                              commands; { all commands }
                          _shrink;
                              {$include gui/gui-destination.inc}
                          _endbox;
                       _endpage;
             _endnotebook;
{$ifndef free}
             _vbox;
             _expand;
                   _hbox;
                         _buttonbox (@proc_input,@macro_self);
                                 label_microscribe_input := _label ('');
                                 _tooltip (label_microscribe_input,'Choice points, distances, lines or curves');
                         _endbox;
                          command ('New point','','','','Make a new point',@proc_mic_newpoint);
                          command ('New line','','','','Make a new line',@proc_mic_newline);
                          command ('New object','','','','Make a new object',@proc_mic_newobject);
                   _endbox;
                   _framebox ('Status');
                          _vbox;
                          _expand;
                                _hbox;
                                      _button (@xpm_left,@m3ll,@macro_self);
                                      _button (@xpm_leftleft,@m3lll,@macro_self);
                                      _button (@xpm_leftstop,@m3lls,@macro_self);
                                      m3dstat := _label ('');
                                      _button (@xpm_rightstop,@m3lrs,@macro_self);
                                      _button (@xpm_rightright,@m3lrr,@macro_self);
                                      _button (@xpm_right,@m3lr,@macro_self);
                                _endbox;
                                _hbox;
                                _fill;
                                      _scrollbox;
                                                 _text (m3dstat1,'');
                                      _endbox;
                                _endbox;
                          _endbox;
                   _endbox;
             _endbox;
{$endif}
{$ifndef free}
        _endbox;
{$endif}
        end;

        for x := 0 to macro_length do _changed (macro_text[x],@set_changed,@macro_self);

        _switched (subnote_macro,@set_switched,@macro_self);

        _key_press (window,@keypress,@macro_self);
        _delete (window,@close_application,@macro_self);
        _destroy (window,@destroy,@macro_self);

        output_gui := @progress;

        calculating;
        updating;

        macro_self.writeredo ('set.red');
        macro_self.writeredo ('set.ref.red');

        if runmacro <> '' then
        begin
             _show_all (_mainwindow);
             _update;
{$ifndef free}
             _setpage (note,8);
{$else}
             _setpage (note,7);
{$endif}
             _setpage (subnote_macro,0);
             load_macro (runmacro,@macro_self);
             _update;
             _destroy (splash);
             _update;
             if runrefresh then run_macro (nil,@macro_self)
                           else run_hide_macro (nil,@macro_self);

             if runexit then
             begin
                  if runask then {for asking}
                  begin
                       if not _func_emit_signal (window,'delete_event') then halt (0);
                  end
                  else halt (0);
             end;
        end
        else
        begin
             _update;
             _destroy (splash);
             _update;
        end;
_endwindow;

{$ifdef threading}
        for x := 0 to macro_length do
        begin
             macro_process[x].Free;
        end;
{$endif}

       for x := 6 downto 1 do cstat[x].done;
       for x := 6 downto 1 do stat[x].done;

        purple.done;
        cyan.done;
        yellow.done;
        blue.done;
        green.done;
        red.done;
        dummy.done;

        screen_histo.done;
        screen_zt.done;
        screen_xt.done;
        screen_yz.done;
        screen_xz.done;
        screen_xy.done;

        macro_self.done;
end;
end.
