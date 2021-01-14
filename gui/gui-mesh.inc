{ ********************************** Mesh ************************************ }

_page ('Info ');
_eventbox;
_backcolor ($FFFF,$FFFF,$BFFF);
      _vbox;
            _label ('<b>Bold</b> - Single selection - LMB');
            _label ('<span foreground="#FF8000">Color</span> - Multiple selection - RMB');
            _separator;
            _label ('<b>Source</b>');
            _label ('All operations work on a single selected source.');
            _label;
            _label ('<b>Destination</b>  (=<i>Calculation</i>)');
            _label ('The calculation output is a single selected destination.');
            _label ('Same replaced! | Other appended!');
            _separator;
            _label ('<i>Note: Only multiple selection of destinations have a focus.</i>');
            if table_long then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_wide then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_special then _label ('<i>Control + Click on screen (xy, xz, xt) to take a screenshot.</i>')
            else _label ('<i>Control + Click on screen (xy, xz, yz) to take a screenshot.</i>');
      _endbox;
_endbox;
_endpage;

_page ('1D ');
_vbox;
_expand;
      _hbox;
            _vbox;
                  command ('Set','raster.set.minmax','','','Set min and max dimension',@proc_calculate_set_dimension_minmax);
            _endbox;
            _vbox;
                  command ('Set min','raster.set.min','','','Set min dimension size from actual objects',@proc_calculate_set_dimension_min);
                  command ('Set max','raster.set.max','','','Set max dimension size from actual objects',@proc_calculate_set_dimension_max);
            _endbox;
            _vbox;
                  _label ('Dimension (min):');
                  _label ('Dimension (max):');
            _endbox;
            _vbox;
                  calculate_dimension_min := _edit ('<-10, -10, -10>');
                  calculate_dimension_max := _edit ('<10, 10, 10>');
            _endbox;
      _endbox;
      _hbox;
            _tooltip (_label ('Raster (discret):'),'Grid/Raster'); calculate_raster := _edit ('<1, 1, 1>');
            _label ('Min. points:'); calculate_raster_minpoints := _edit ('1');
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  command ('Points','raster.scalar.points','','','Mark raster points',@proc_points);
                  command ('Count','raster.scalar.point.count','','','Count points',@proc_count_points);
                  command ('Lines','raster.line.length','','','Calculate lines length',@proc_line_length);
                  command ('Count','raster.scalar.line.count','','','Counts lines',@proc_count_lines);
            _endbox;
            _hbox;
                  command ('Pennation x','raster.scalar.pennation.x','','','Calculate pennation angle against x-axis'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_x);
                  command ('Pennation y','raster.scalar.pennation.y','','','Calculate pennation angle against y-axis'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_y);
                  command ('Pennation z','raster.scalar.pennation.z','','','Calculate pennation angle against z-axis'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_z);
            _endbox;
            _hbox;
                  command ('Pennation xy','raster.scalar.pennation.xy','','','Calculate pennation angle against x-y-plane'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_xy); macro_self.putprocedure ('raster.scalar.pennation.yx','','','Calculate pennation angle against y-x-plane',@proc_pennation_xy);
                  command ('Pennation yz','raster.scalar.pennation.yz','','','Calculate pennation angle against y-z-plane'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_yz); macro_self.putprocedure ('raster.scalar.pennation.zy','','','Calculate pennation angle against z-y-plane',@proc_pennation_yz);
                  command ('Pennation zx','raster.scalar.pennation.zx','','','Calculate pennation angle against z-x-plane'+#10+'<i>Note: For degree or radian see Data≻File!</i>',@proc_pennation_zx); macro_self.putprocedure ('raster.scalar.pennation.xz','','','Calculate pennation angle against x-z-plane',@proc_pennation_zx);
            _endbox;
            _hbox;
                  _vbox;
                        _hbox;
                              _shrink;
                              _label ('<b>Curvature:</b>');
                              _expand;
                              command ('Fit','raster.scalar.curvature.fit','','','Calculate local curvature with polynom fit',@proc_raster_curvature_fit);
                              command ('Smooth','raster.scalar.curvature','','','Calculate local curvature with polynom smooth',@proc_raster_curvature);
                        _endbox;
                        _hbox;
                              _shrink;
                              _label ('<b>Torsion:</b>');
                              _expand;
                              command ('Fit','raster.scalar.torsion.fit','','','Calculate local torsion with polynom fit',@proc_raster_torsion_fit);
                              command ('Smooth','raster.scalar.torsion','','','Calculate local torsion with polynom smooth',@proc_raster_torsion);
                        _endbox;
                  _endbox;
                  _vbox;
                        _hbox;
                              _tooltip(_label ('Polynom:'),'Polynominal degree: constant (0), linear (1), quadratic (2), ...');
                              raster_polynom := _smalledit ('99');
                        _endbox;
                  _endbox;
            _endbox;
            _label ('<i>Note: All calculated data are stored in ≺_,_,_,t≻ as scalar.</i>');
            _label ('<i>Your line step size should correspond to the grid/raster resolution.</i>');
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _label;
                  _tooltip (_label ('Vector field:'),'Calculate vectors in 3-dimension (min,max) with raster');
                  command ('Pennation','raster.vector.pennation','','','Calculate normalized vectors from a vector field or lines',@proc_pennation_vector);
                  _label;
            _endbox;
      _endbox;
_endbox;
_endpage;

_page ('2D ');
_vbox;
_expand;
      _hbox;
            _label('Origin:'); mesh_origin_hull := _edit ('<0, 0, 0, 0>');
            _tooltip (_label('Raster:'),'Grid/Raster from origin with steps (raster) and search width (+/-raster)'); mesh_raster_hull := _smalledit ('10');
      _endbox;
      _hbox;
            _tooltip(_label('Min. distance:'),'Minimum distance before searching for curving in or hollowed inward for concave'); mesh_distance_hull := _smalledit ('0.1');
            mesh_hull := _tooltip(_combobox,'Concave means curving in or hollowed inward, as opposed to convex');
                      _item ('Concave');
                      _item ('Convex');
            _endcombobox (1);
      _endbox;
      _hbox;
            command ('X hull','mesh.hull.x','','','Calculate convex/concave hull along x-axis',@proc_hull_x);
            command ('X plane hull','mesh.plane.hull.x','','','Calculate convex/concave hull along x-axis restricted to planes',@proc_hull_x_inplane);
            command ('X point hull','mesh.point.hull.x','','','Calculate convex/concave point hull along x-axis',@proc_hull_x_point);
      _endbox;
      _hbox;
            command ('Y hull','mesh.hull.y','','','Calculate convex/concave hull along y-axis',@proc_hull_y);
            command ('Y plane hull','mesh.plane.hull.y','','','Calculate convex/concave hull along y-axis restricted to planes',@proc_hull_y_inplane);
            command ('Y point hull','mesh.point.hull.y','','','Calculate convex/concave point hull along y-axis',@proc_hull_y_point);
      _endbox;
      _hbox;
            command ('Z hull','mesh.hull.z','','','Calculate convex/concave hull along z-axis',@proc_hull_z);
            command ('Z plane hull','mesh.plane.hull.z','','','Calculate convex/concavev hull along z-axis restricted to planes',@proc_hull_z_inplane);
            command ('Z point hull','mesh.point.hull.z','','','Calculate convex/concave point hull along z-axis',@proc_hull_z_point);
      _endbox;
      _separator;
      _hbox;
            command ('Plane','mesh.plane','','','Calculate plane from points',@proc_calculate_plane);
            command ('Surface','mesh.surface','','','Calculate surface from points',@proc_calculate_surface);
            command ('Clean surface','mesh.clean.surface','','','Calculate clean surface from points',@proc_calculate_clean_surface);
            _tooltip (_label('Raster:'),'Grid/Raster'); mesh_raster := _smalledit ('0.1');
      _endbox;
      _separator;
      _hbox;
            command ('Smooth','','','','Smooth mesh',@proc_mesh_smooth); {macro_self.putprocedure ('mesh.smooth','','','',@proc_mesh_smooth);} {see 3D}
            command ('Smooth objects','','','','Smooth mesh for every objects',@proc_mesh_smooth_single_os); {macro_self.putprocedure ('mesh.smooth.objects','','','',@proc_mesh_smooth_objects);} {see 3D}
            command ('Smooth sticky objects','','','','Smooth mesh for every objects',@proc_mesh_smooth_sticky_os); {macro_self.putprocedure ('mesh.smooth.sticky','','','',@proc_mesh_smooth_sticky);} {see 3D}
      _endbox;
_endbox;
_endpage;

_page ('FEM ');
_vbox;
_expand;
      _hbox;
            _vbox;
                  command ('Set','mesh.set.minmax','','','Set min and max dimension',@proc_mesh_set_dimension_minmax);
            _endbox;
            _vbox;
                  command ('Set min','mesh.set.min','','','Set min dimension from actual objects',@proc_mesh_set_dimension_min);
                  command ('Set max','mesh.set.max','','','Set max dimension from actual objects',@proc_mesh_set_dimension_max);
            _endbox;
            _vbox;
                  _label ('Dimension (min):');
                  _label ('Dimension (max):');
            _endbox;
            _vbox;
                  mesh_dimension_min := _edit ('<-10, -10, -10>');
                  mesh_dimension_max := _edit ('<10, 10, 10>');
            _endbox;
      _endbox;
      _hbox;
            _label;
            _tooltip (_label ('Raster (discret):'),'Grid/Raster'); fem_raster := _edit ('<1, 1, 1>');
            _label;
      _endbox;
      _separator;
      _hbox;
            fill_holes := _checkbutton ('Fill holes');
            _tooltip (fill_holes,'Fill holes');
            erase_bumps := _uncheckbutton ('Erase bumps');
            _tooltip (erase_bumps,'Erase bumps');
            mesh_dilating := _uncheckbutton ('Dilate');
            _tooltip (mesh_dilating,'Dilate mesh to prevent shrinking');
      _endbox;
      _hbox;
            mesh_smoothing := _checkbutton ('Smooth');
            _tooltip (mesh_smoothing,'Smooth elements');
            mesh_smoothing_outside := _uncheckbutton ('Outside');
            _tooltip (mesh_smoothing_outside,'Smooth only the outside');
            _label ('Smooth steps:'); mesh_smooth := _smalledit ('3');
      _endbox;
      _hbox;
            solids := _checkbutton ('Solids');
            _tooltip (solids,'Generate Hex8 solid elements');
            shells := _uncheckbutton ('Shells');
            _tooltip (shells,'Generate Quad4 shell elements');
            command ('Generate FEMesh','','','','Calculate FEMesh with solid or shell elements',@proc_generate);
            macro_self.putprocedure ('mesh.fem.solid','','','',@proc_generate_solid_help);
            macro_self.putprocedure ('mesh.fem.smooth','','','',@proc_generate_smooth_help);
      _endbox;
      _hbox;

      _endbox;
_endbox;
_endpage;

_page ('3D ');
_vbox;
_expand;
      _hbox;
            command ('Split voxel','mesh.split.xyz','','','Split mesh voxel into 8 subvoxels',@proc_mesh_split_xyz);
            command ('Split x','mesh.split.x','','','Split mesh voxel into two subvoxels along x-axis',@proc_mesh_split_x);
            command ('Split y','mesh.split.y','','','Split mesh along into two subvoxels y-axis',@proc_mesh_split_y);
            command ('Split z','mesh.split.z','','','Split mesh along into two subvoxels z-axis',@proc_mesh_split_z);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Points:</b>');
            _expand;
            command ('Uniform','mesh.uniform','','','Make 3d mesh uniform (deformed -≻ min-max cubes)',@proc_mesh_uniform);
            command ('Discrete','mesh.discrete','','','Make 3d mesh discrete (see also edit≻layer≻mean duplicates)',@proc_mesh_discrete);
            _tooltip (_label ('Range:'),'Discrete range'); discrete := _smalledit ('1');
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>Voxels:</b>');
            _expand;
            hidecommand ('Single','mesh.single','','','Cleanup from single elements',@proc_mesh_single);
            command ('Cleanup','mesh.cleanup','','','Cleanup 3d mesh from ≺ or ≻ mean elements - (segment, area, volume)*factor',@proc_mesh_cleanup);
            _tooltip (_label ('Factor:'),'Value range around then mean values'); cleanup_factor := _smalledit ('0.9');
      _endbox;
      _separator;
      _hbox;
            _label;
            command ('Get outside','mesh.outside','','','Get outside of mesh',@proc_mesh_outside);
            command ('Split into objects','mesh.split','','','Split mesh into objects',@proc_mesh_split);
            command ('Get inside','mesh.inside','','','Get inside of mesh',@proc_mesh_inside);
            _label;
      _endbox;
      _separator;
      _hbox;
            _vbox;
                  outside := _uncheckbutton ('Outside');
                  _label ('<b>Single:</b>');
                  _label ('<b>Sticky:</b>');
                  _label ('<b>All:</b>');
            _endbox;
            _vbox;
                  _label ('<b>Smooth</b>');
                  command ('O','mesh.smooth.single.o','','','Smooth for every objects without sticky',@proc_mesh_smooth_single_o);
                  _label ('');
                  _label ('');
            _endbox;
            _vbox;
                  _label ('<b>Smooth</b>');
                  command ('S','mesh.smooth.single.s','','','Smooth for every sticky without sticky',@proc_mesh_smooth_single_s);
                  command ('S','mesh.smooth.sticky.s','','','Smooth for every sticky with sticky',@proc_mesh_smooth_sticky_s);
                  _label ('');
            _endbox;
            _vbox;
                  _label ('<b>Smooth</b>');
                  command ('O&S','mesh.smooth.single.os','','','Smooth for every objects & sticky without sticky',@proc_mesh_smooth_single_os);
                  command ('O&S','mesh.smooth.sticky.os','','','Smooth for every objects & sticky with sticky',@proc_mesh_smooth_sticky_os);
                  command ('O&S','mesh.smooth','','','Smooth mesh',@proc_mesh_smooth);
            _endbox;
      _endbox;
_endbox;
_endpage;

_page ('Assign ');
_vbox;
_expand;
      _hbox;
            _button (@xpm_left,@m3ol,@macro_self);
            _button (@xpm_leftleft,@m3oll,@macro_self);
            _button (@xpm_leftstop,@m3ols,@macro_self);
            _eventbox;
                      _cursor_pressed (@proc_object_name,@macro_self);
                      label_status_object3 := _label;
                      _tooltip (label_status_object3,'Edit object name');
                      { macro_self.putprocedure ('edit.object.name','','','',@proc_object_name); } { see edit }
            _endbox;
            _button (@xpm_rightstop,@m3ors,@macro_self);
            _button (@xpm_rightright,@m3orr,@macro_self);
            _button (@xpm_right,@m3or,@macro_self);
      _endbox;
      _hbox;
            _vbox;
                  command ('Object is sticky','mesh.assign.sticky','','','Assign object is sticky',@proc_assign_sticky);
                  command ('Own material','mesh.assign.material','','','Assign every object his own material',@proc_assign_material);
            _endbox;
            _vbox;
                  command ('Assign obj iso mat','mesh.assign.isotropic.material','','','Assign material properties',@proc_assign_isotropic_material);
                  febio_isotropic_material := _combobox;
                                    _item ('Linear elastic'); {10}
                                    _item ('St. Venant-Kirchhoff'); {20}
                                    _item ('Neo-Hookean'); {30}
                                    _item ('Mooney-Rivlin'); {40}
                                    _item ('Veronada-Westmann'); {50}
                                    _item ('Poroelasticity'); {60}
                                    _item ('Rigid body'); {70}
                                    _item ('TC nonlinear ortho.'); {80}
                                    _item ('Ogden'); {90}
                  _endcombobox (0);
            _endbox;
            _vbox;
                  command ('Assign obj aniso mat','mesh.assign.anisotropic.material','','','Assign material properties (with fibre direction)',@proc_assign_anisotropic_material);
                  febio_anisotropic_material := _combobox;
                                    _item ('Mooney-Rivlin'); {45}
                                    _item ('Veronda-Westmann'); {55}
                                    _item ('Mooney-Rivlin & cont.'); {46}
                                    _item ('Veronda-West. & cont.'); {56}
                                    _item ('Muscle material'); {100}
                                    _item ('Tendon material'); {110}
                  _endcombobox (0);
            _endbox;
      _endbox;
      _separator;
      _hbox;
           command ('Object prescribing','mesh.assign.prescribing','','','Assign prescribing to source nodes',@proc_assign_prescribe);
           _label ('Displacement:'); febio_prescribe_attr := _edit ('<1, 0, 0>');
      _endbox;
      _separator;
      _hbox;
           command ('Object fixing','mesh.assign.fixing','','','Assign fixing to source nodes',@proc_assign_fixed);
           _label ('Direction:'); febio_fixed_attr := _edit ('<1, 1, 1>');
      _endbox;
      _separator;
      _hbox;
            command ('Object force','mesh.assign.force','','','Assign force to source nodes',@proc_assign_force);
            _label ('Force:'); febio_force_attr := _edit ('<1, 0, 0>');
      _endbox;
      _separator;
      _label ('<i>Note: All operations work on objects.</i>');
_endbox;
_endpage;

_page ('A≻ ','Assign...');
_vbox;
_expand;
      _hbox;
             _label;
             _label ('Distance to found points:'); febio_distance := _smalledit ('1');
             _label;
      _endbox;
      _separator;
      _hbox;
            _label;
            command ('Assign iso material','mesh.assign.ref.isotropic.material','','','Assign material properties',@proc_assign_ref_isotropic_material);
            febio_ref_isotropic_material := _combobox;
                              _item ('Linear elastic'); {10}
                              _item ('St. Venant-Kirchhoff'); {20}
                              _item ('Neo-Hookean'); {30}
                              _item ('Mooney-Rivlin'); {40}
                              _item ('Veronada-Westmann'); {50}
                              _item ('Poroelasticity'); {60}
                              _item ('Rigid body'); {70}
                              _item ('TC nonlinear orthotropic'); {80}
                              _item ('Ogden'); {90}
            _endcombobox (0);
            _label;
      _endbox;
      _hbox;
            _label;
            command ('Assign aniso material','mesh.assign.ref.anisotropic.material','','','Assign material properties (with fibre direction)',@proc_assign_ref_anisotropic_material);
            febio_ref_anisotropic_material := _combobox;
                              _item ('Mooney-Rivlin'); {45}
                              _item ('Veronda-Westmann'); {55}
                              _item ('Mooney-Rivlin & contraction'); {46}
                              _item ('Veronda-Westmann & contraction'); {56}
                              _item ('Muscle material'); {100}
                              _item ('Tendon material'); {110}
            _endcombobox (0);
            _label;
      _endbox;
      _separator;
      _hbox;
           command ('Source prescribing','mesh.assign.ref.prescribing','','','Assign prescribing to object nodes',@proc_assign_ref_prescribe);
           _label ('Displacement:'); febio_ref_prescribe_attr := _edit ('<1, 0, 0>');
      _endbox;
      _separator;
      _hbox;
           command ('Source fixing','mesh.assign.ref.fixing','','','Assign fixing to object nodes',@proc_assign_ref_fixed);
           _label ('Direction:'); febio_ref_fixed_attr := _edit ('<1, 1, 1>');
      _endbox;
      _separator;
      _hbox;
            command ('Source force','mesh.assign.ref.force','','','Assign force to object nodes',@proc_assign_ref_force);
            _label ('Force:'); febio_ref_force_attr := _edit ('<1, 0, 0>');
      _endbox;
      _separator;
      _label ('<i>Note: All operations work with reference from destination.</i>');
_endbox;
_endpage;

_page ('FEBio ');
_vbox;
_expand;
      _hbox;
            febio_version := _tooltip (_combobox,'Please look in the User Manual Chapter 3.2');
                         _item ('Version 1.2'); { first }
                         _item ('Version 2.0'); { Boundary section redesigned }
                         _item ('Version 2.5'); { Boundary section redesigned, by referencing the sets }
            _endcombobox (2);
            febio_solver := _combobox;
                         _item ('Skyline');
                         _item ('Pardiso');
                         _item ('SuperLU');
                         _item ('SuperLU MT');
                         _item ('WSMP');
                         _item ('Full-matrix');
            _endcombobox (1);
            febio_plot := _combobox;
                              _item ('Plot_Never');
                              _item ('Plot_Major_ITRS');
                              _item ('Plot_Minor_ITRS');
                              _item ('Plot_Must_Points');
            _endcombobox (1);
            febio_print := _combobox;
                              _item ('Print_Never');
                              _item ('Print_Progress');
                              _item ('Print_Major_ITRS');
                              _item ('Print_Minor_ITRS');
                              _item ('Print_Minor_ITRS_EXP');
            _endcombobox (3);
      _endbox;
      _hbox;
            _label ('Time steps:'); febio_time_steps := _smalledit ('10');
            _label ('Steps size:'); febio_step_size := _smalledit ('0.1');
      _endbox;
      _separator;
      _hbox;
            _tooltip (_vbox,'Hex8, Penta6 and Tet4 for solids are allowed.'+#10+'Quad4 and Tri3 for shells are allowed.'+#10+'<i>Note: If here no data founded, the default values were used!</i>');
                 _label ('Solid Elements:');
                 _label ('Shell Elements:');
            _endbox; {in tooltip}
            febio_geometry := _combobox;
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);
            _tooltip (_vbox,'Fibre direction (vector.(x,y,z)) for isotropic materials and solids.'+#10+'Shell thickness (point.t) for shells.'+#10+'<i>Note: If here no data founded, the default values were used!</i>');
                  _label ('Fibre direction:');
                  _label ('Shell thickness:');
            _endbox; {in tooltip}
            febio_fibre := _combobox;
                              _item ('None');
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);
      _endbox;
      _hbox;
            _label ('Fibres:'); febio_fibre_direction := _edit ('<1, 0, 0>');
            _label ('Shells:'); febio_shell_thickness := _smalledit ('0.1');
      _endbox;
      _separator;
      _hbox;
            _tooltip (_vbox,'Prescribed nodal degrees of freedom (displacements).');
                     _label ('Prescribe nodes:');
            _endbox; {in tooltip}
            febio_prescribe := _combobox;
                              _item ('None');
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);

            _tooltip (_vbox,'Fixed nodal degrees of freedom.');
                     _label ('Fix nodes:');
            _endbox; {in tooltip}
            febio_fixed := _combobox;
                              _item ('None');
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);
      _endbox;
      _hbox;
            _tooltip (_vbox,'Nodal forces are applied by the force element.');
                     _label ('Force interface:');
            _endbox; {in tooltip}
            febio_force := _combobox;
                              _item ('None');
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);

            _tooltip (_vbox,'Pressure forces are applied to the surface of the geometry.');
                     _label ('Pressure interface:');
            _endbox; {in tooltip}
            febio_pressure := _combobox;
                              _item ('None');
                              _item ('Red');
                              _item ('Green');
                              _item ('Blue');
                              _item ('Yellow');
                              _item ('Cyan');
                              _item ('Purple');
            _endcombobox (0);
      _endbox;
      _separator;
      _hbox;
            togglefebiooutput := _checkbutton ('Output plot');
            command ('Generate file','generate.febio','','','Generate FEBio-file',@proc_generate_febio,@proc_generate_febio12_help);
            command ('Generate sticky file','generate.split.febio','','','Generate FEBio-file with splited objects (without sticky)',@proc_generate_febio_sticky,@proc_generate_febio12_sticky_help);
            macro_self.putprocedure ('generate.febio2','','','',@proc_generate_febio2_help);
            macro_self.putprocedure ('generate.split.febio2','','','',@proc_generate_febio2_sticky_help);
            macro_self.putprocedure ('generate.febio25','','','',@proc_generate_febio25_help);
            macro_self.putprocedure ('generate.split.febio25','','','',@proc_generate_febio25_sticky_help);
      _endbox;
_endbox;
_endpage;
