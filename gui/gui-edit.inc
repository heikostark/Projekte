{ ************************************* Edit ********************************* }

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
            _label ('<b>Destination</b>');
            _label ('Without destination.');
            _label ('Always replaced!');
            _separator;
            _label ('<i>Note: Only multiple selection of destinations have a focus.</i>');
            if table_long then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_wide then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_special then _label ('<i>Control + Click on screen (xy, xz, xt) to take a screenshot.</i>')
            else _label ('<i>Control + Click on screen (xy, xz, yz) to take a screenshot.</i>');
      _endbox;
_endbox;
_endpage;

_page ('Points ');
_vbox;
_expand;
      _hbox;
            _button (@xpm_left,@m3pl,@macro_self);
            _button (@xpm_leftleft,@m3pll,@macro_self);
            _button (@xpm_leftstop,@m3pls,@macro_self); macro_self.putprocedure ('previous.point',@m3pl);
            _eventbox;
                      _cursor_pressed (@proc_point_values,@macro_self);
                      label_status_point := _label;
                      _tooltip (label_status_point,'Edit point values');
                      macro_self.putprocedure ('edit.point.values',@proc_point_values_1);
            _endbox;
            _button (@xpm_rightstop,@m3prs,@macro_self);
            _button (@xpm_rightright,@m3prr,@macro_self);
            _button (@xpm_right,@m3pr,@macro_self);   macro_self.putprocedure ('next.point',@m3pr);
      _endbox;
      _separator;
      _hbox;
             command ('To vectors','edit.points.to.vectors','','','Make points to vectors',@proc_points_to_vectors);
      _endbox;
      _separator;
      _hbox;
            _label;
            _label('Number:'); edit_erase_single_numbers := _smalledit ('100');
            _label('Neighbors:'); edit_erase_single_neighbors := _tooltip(_smalledit ('1000'),'Random neighbors');
            _label;
      _endbox;
      _hbox;
            _label;
            command ('Erase single points','edit.erase.single.points','','','Erase (number) single points'+#10+'<i>Note: Looks only for random neighbors!</i>',@proc_erase_single_points);
            _label;
      _endbox;
      _separator;
      _hbox;
            command ('Assign layer','edit.assign.layer','','','Assign layer objects from source to points in destination',@proc_assign_layer);
      _endbox;
      _separator;
      _hbox;
            command ('Assign t','edit.assign.t','','','Assign t values from source to destination',@proc_assign_t);
            _label('Range:'); edit_assign_ranged := _smalledit ('1');
            command ('Ranged t','edit.assign.ranged.t','','','Assign t values only in range from source to destination',@proc_assign_ranged_t);
      _endbox;
_endbox;
_endpage;

_page ('Vectors ');
_vbox;
_expand;
      _hbox;
            _button (@xpm_left,@m3ll,@macro_self);
            _button (@xpm_leftleft,@m3lll,@macro_self);
            _button (@xpm_leftstop,@m3lls,@macro_self); { see line_rows }
            _eventbox;
                      _cursor_pressed (@proc_line_material,@macro_self);
                      label_status_vector := _label;
                      _tooltip (label_status_vector,'Edit vector (line) material');
                      { macro_self.putprocedure ('edit.line.material',@proc_line_material); } { see line_rows }
            _endbox;
            _button (@xpm_rightstop,@m3lrs,@macro_self);
            _button (@xpm_rightright,@m3lrr,@macro_self);
            _button (@xpm_right,@m3lr,@macro_self);   { see line_rows }
      _endbox;
      _separator;
      _hbox;
            command ('Clear origin','edit.vectors.clear','','','Clear axes to 0 for the origin',@proc_vector_clear_origin);
            command ('Clear x','edit.vectors.clear.x','','','Clear x-axis to 0 for the origin',@proc_vector_clear_x);
            command ('Clear y','edit.vectors.clear.y','','','Clear y-axis to 0 for the origin',@proc_vector_clear_y);
            command ('Clear z','edit.vectors.clear.z','','','Clear z-axis to 0 for the origin',@proc_vector_clear_z);
            command ('Clear t','edit.vectors.clear.t','','','Clear t-axis to 0 for the origin',@proc_vector_clear_t);
      _endbox;
      _separator;
      _hbox;
            command ('Norm','edit.vectors.norm','','','Norm vectors',@proc_edit_norm);
            command ('Normscale','edit.vectors.normscale','','','Norm and scale vectors',@proc_edit_normscale);
            command ('Scale','edit.vectors.scale','','','Scale vectors',@proc_edit_scale);
            command ('Invscale','edit.vectors.invscale','','','Scale vectors (1/factor)',@proc_edit_invscale);
            _label('Factor:');  edit_scale := _smalledit ('1');
            { ??? Move <x,y,z,t> ??? }
            { ??? Scale <x,y,z,t> ??? }
      _endbox;
      _hbox;
            command ('Minscale','edit.vectors.minscale','','','Scale vectors after norm(min)',@proc_edit_minscale);
            command ('Maxscale','edit.vectors.maxscale','','','Scale vectors after norm(max)',@proc_edit_maxscale);
            _label ('|');
            command ('Negate','edit.vectors.negate','','','-1*Vectors',@proc_edit_negate);
            command ('Invert','edit.vectors.invert','','','1/Vectors',@proc_edit_invert);
      _endbox;
      _separator;
      _hbox;
             _shrink;
             _tooltip (_label ('<b>Local:</b>'),'Local means, vectors with same origin in same objects');
             _expand;
             command ('Add','edit.local.add.vectors','','','Add local vectors (same origin)',@proc_local_add_vectors);
             command ('Subtract','edit.local.subtract.vectors','','','Subtract local vectors (same origin)',@proc_local_subtract_vectors);
             command ('Mean','edit.local.mean.vectors','','','Mean local vectors (same origin)',@proc_local_mean_vectors);
      _endbox;
      _hbox;
             _shrink;
             _tooltip (_label ('<b>Global:</b>'),'Global means, vectors in same objects');
             _expand;
             command ('Add','edit.global.add.vectors','','','Add global vectors (same object)',@proc_global_add_vectors);
             command ('Subtract','edit.global.subtract.vectors','','','Subtract global vectors (same object)',@proc_global_subtract_vectors);
             command ('Mean','edit.global.mean.vectors','','','Mean global vectors (same object)',@proc_global_mean_vectors);
      _endbox;
      _separator;
      _hbox;
            command ('Disperse','edit.vectors.disperse','','','Disperse vector',@proc_vectors_disperse);
            _label('Range:'); edit_vectors_range := _edit ('<1, 1, 1, 1>');
      _endbox;
      _separator;
      _hbox;
            command ('New direction','edit.vectors.direction','','','New vectors direction',@proc_vectors_direction);
            command ('New origin','edit.vectors.direction.origin','','','New vectors inverse direction',@proc_vectors_direction_origin);
            _label('Direction:'); edit_vectors_direction := _edit ('<1, 0, 0, 0>');
      _endbox;
      _separator;
      _label ('<i>Note: Vectors are special lines (two points). See also lines.</i>');
_endbox;
_endpage;

_page ('Lines ');
_vbox;
_expand;
      _hbox;
            _button (@xpm_left,@m3ll,@macro_self);
            _button (@xpm_leftleft,@m3lll,@macro_self);
            _button (@xpm_leftstop,@m3lls,@macro_self); macro_self.putprocedure ('previous.line',@m3ll);
            _eventbox;
                      _cursor_pressed (@proc_line_material,@macro_self);
                      label_status_line := _label;
                      _tooltip (label_status_line,'Edit line material');
                      macro_self.putprocedure ('edit.line.material',@proc_line_material_1);
            _endbox;
            _button (@xpm_rightstop,@m3lrs,@macro_self);
            _button (@xpm_rightright,@m3lrr,@macro_self);
            _button (@xpm_right,@m3lr,@macro_self); macro_self.putprocedure ('next.line',@m3lr);
      _endbox;
      _hbox;
            command ('Grow','edit.grow.left','','','Grow left side',@proc_grow_left);
            command ('Reduce','edit.reduce.left','','','Reduce left side',@proc_reduce_left);
            _label ('--');
            transform_grow := _smalledit ('10');
            _label ('--');
            command ('Reduce','edit.reduce.right','','','Reduce rigth side',@proc_reduce_right);
            command ('Grow','edit.grow.right','','','Grow right side',@proc_grow_right);
      _endbox;
      _hbox;
            _shrink;
             _label ('<b>Line:</b>');
             _expand;
             command ('To points','edit.line.to.points','','','Make line to points',@proc_line_to_points);
             command ('To vector','edit.line.to.vector','','','Make line to one vector',@proc_line_to_one_vector);
             command ('To vectors','edit.line.to.vectors','','','Make line to vectors',@proc_line_to_vectors);
             command ('To objects','edit.line.to.objects','','','Make line to objects',@proc_line_to_objects);
      _endbox;
      _separator;
      _hbox;
             command ('Erase ≺','edit.erase.short.lines','','','Erase short lines with length <',@proc_erase_short_lines);
             _hbox;
             _shrink;
                     editl := _smalledit ('10'); _label ('len');
             _endbox;
             command ('Erase ≻','edit.erase.long.lines','','','Erase long lines with length >',@proc_erase_long_lines);
             _label ('|');
             command ('Erase ≺','edit.erase.short.points','','','Erase short lines with points <',@proc_erase_short_plines);
             _hbox;
             _shrink;
                   editlp := _smalledit ('10'); _label ('pt');
             _endbox;
             command ('Erase ≻','edit.erase.long.points','','','Erase long lines with points >',@proc_erase_long_plines);

      _endbox;
      _hbox;
            command ('Trim begin','edit.trim.begin.lines','','','Trim lines from beginning to length',@proc_trim_begin_lines);
            command ('Trim both len','edit.trim.both.lines','','','Trim lines from beginning and end to length',@proc_trim_both_lines);
            command ('Trim end','edit.trim.end.lines','','','Trim lines from end to length',@proc_trim_end_lines);
            _label ('|');
            command ('Trim begin','edit.trim.begin.points','','','Trim points from beginning to n points',@proc_trim_begin_plines);
            command ('Trim both pt','edit.trim.both.points','','','Trim points from beginning and end to n points',@proc_trim_both_plines);
            command ('Trim end','edit.trim.end.points','','','Trim points from end to n points',@proc_trim_end_plines);
      _endbox;
      _separator;
      _hbox;
            command ('Lines flip','edit.lines.flip','','','New lines direction (point order)',@proc_lines_flip);
            command ('Direction flip','edit.lines.direction','','','New lines direction (only if not in direction - point order)',@proc_lines_direction);
            _label('Direction:'); edit_lines_direction := _edit ('<1, 0, 0, 0>');
      _endbox;
_endbox;
_endpage;

_page ('L≻ ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Points:</b>');
            _expand;
            command ('Number (t)','edit.lines.number','','','Store line point number in t',@proc_lines_number);
            command ('3D distance (t)','edit.lines.distance','','','Store point neighbor distance (only 3D) in t',@proc_lines_distance);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Lines (only 3D):</b>');
            _expand;
            _hbox;
                  _vbox;
                        command ('Length (t)','edit.lines.length','','','Store line length (only 3D) in t',@proc_lines_length);
                        command ('Length (mat)','edit.lines.length.material','','','Store line length (only 3D) in material',@proc_lines_length_material);
                        command ('Number (mat)','edit.lines.material','','','Store line number in material',@proc_lines_material);
                  _endbox;
                  _label;
                  _vbox;
                        command ('x Pennation (t)','edit.lines.pennation.x','','','Store x pennation angle (only 3D) in t',@proc_lines_pennation_x);
                        command ('y Pennation (t)','edit.lines.pennation.y','','','Store y pennation angle (only 3D) in t',@proc_lines_pennation_y);
                        command ('z Pennation (t)','edit.lines.pennation.z','','','Store z pennation angle (only 3D) in t',@proc_lines_pennation_z);
                  _endbox;
                  _label;
                  _vbox;
                        command ('xy Pennation (t)','edit.lines.pennation.xy','','','Store xy pennation angle (only 3D) in t',@proc_lines_pennation_xy); macro_self.putprocedure ('edit.lines.pennation.yx','','','Store yx pennation angle (only 3D) in t',@proc_pennation_xy);
                        command ('yz Pennation (t)','edit.lines.pennation.yz','','','Store yz pennation angle (only 3D) in t',@proc_lines_pennation_yz); macro_self.putprocedure ('edit.lines.pennation.zy','','','Store zy pennation angle (only 3D) in t',@proc_pennation_yz);
                        command ('zx Pennation (t)','edit.lines.pennation.zx','','','Store zx pennation angle (only 3D) in t',@proc_lines_pennation_zx); macro_self.putprocedure ('edit.lines.pennation.xz','','','Store xz pennation angle (only 3D) in t',@proc_pennation_zx);
                  _endbox;
                  _label;
                  _vbox;
                        command ('Tortuosity (t)','edit.lines.tortuosity','','','Store tortuosity (3D curve / line) in t',@proc_lines_tortuosity);
                        command ('Curvature (t)','edit.lines.curvature','','','Store curvature (only 3D) in t',@proc_lines_curvature);
                        command ('Torsion (t)','edit.lines.torsion','','','Store torsion (only 3D) in t',@proc_lines_torsion);
                  _endbox;
            _endbox;
      _endbox;
      _separator;
      _hbox;
            calculate_smooth_method := _combobox;
                                    _item ('Polynom (see degree)');
                                    _item ('Polynom fit (see degree)');
                                    _item ('Hard av. (l+r)/2');
                                    _item ('Average (l+m+r)/3');
                                    _item ('Soft av. (l+2*m+r)/4');
{                                   _item ('Moving average 1%');
                                    _item ('Moving average 2%');
                                    _item ('Moving average 3%');
                                    _item ('Moving average 5%');
                                    _item ('Moving average 7%');}
            _endcombobox (3);
            edit_polynom_method := _combobox;
                                    _item ('Degree  0');
                                    _item ('Degree  1');
                                    _item ('Degree  2');
                                    _item ('Degree  3');
                                    _item ('Degree  4');
                                    _item ('Degree  5');
                                    _item ('Degree  6');
                                    _item ('Degree  7');
                                    _item ('Degree  8');
                                    _item ('Degree  9');
                                    _item ('Degree 10');
                                    _item ('Degree 11');
                                    _item ('Degree 12');
                                    _item ('Degree 13');
                                    _item ('Degree 14');
                                    _item ('Degree 15');
                                    _item ('Degree 16');
                                    _item ('Degree 17');
                                    _item ('Degree 18');
                                    _item ('Degree 19');
            _endcombobox (19);
            {_tooltip (_label ('Window:'),'Window for the Savitzky–Golay filter');
            edit_polynom_window := _smalledit ('9');}
            command ('Smooth','edit.smooth.lines','','','Smooth lines (loops - only average)',@proc_smooth_lines);
      _endbox;
      _hbox;
            command ('Average x','edit.lines.average.x','','','Average local x values on lines',@proc_lines_average_x);
            command ('Average y','edit.lines.average.y','','','Average local y values on lines',@proc_lines_average_y);
            command ('Average z','edit.lines.average.z','','','Average local z values on lines',@proc_lines_average_z);
            command ('Average t','edit.lines.average.t','','','Average local t values on lines',@proc_lines_average_t);
      _endbox;
      _separator;
      _hbox;
            command ('Fillup t','edit.lines.fillup.t','','','Fillup t values on lines (fillup zeros)',@proc_lines_fillup_t);
            command ('Mean t','edit.lines.mean.t','','','Make mean of all t values on lines',@proc_lines_mean_t);
            command ('SD t','edit.lines.sd.t','','','Make sd of all t values on lines',@proc_lines_sd_t);
            command ('Min t','edit.lines.min.t','','','Make min of all t values on lines',@proc_lines_min_t);
            command ('Median t','edit.lines.median.t','','','Make median of all t values on lines',@proc_lines_median_t);
            command ('Max t','edit.lines.max.t','','','Make max of all t values on lines',@proc_lines_max_t);
      _endbox;
      _separator;
      _hbox;
            command ('Group connected','edit.lines.group','','','Group (make same material) connected lines',@proc_lines_group);
            command ('3D group connected','edit.lines.group.3d','','','Group (make same material) connected lines (only 3D duplicates)',@proc_lines_group_3d);
      _endbox;
_endbox;
_endpage;

_page ('Objects ');
_vbox;
_expand;
      _hbox;
            _button (@xpm_left,@m3ol,@macro_self);
            _button (@xpm_leftleft,@m3oll,@macro_self);
            _button (@xpm_leftstop,@m3ols,@macro_self); macro_self.putprocedure ('previous.object',@m3ol);
            _eventbox;
                      _cursor_pressed (@proc_object_name,@macro_self);
                      label_status_object := _label;
                      _tooltip (label_status_object,'Edit object name');
                      macro_self.putprocedure ('edit.object.name',@proc_object_name_1);
            _endbox;
            _button (@xpm_rightstop,@m3ors,@macro_self);
            _button (@xpm_rightright,@m3orr,@macro_self);
            _button (@xpm_right,@m3or,@macro_self); macro_self.putprocedure ('next.object',@m3or);
      _endbox;
      _hbox;
             _shrink;
             _label ('<b>Object:</b>');
             _expand;
             command ('To points','edit.object.to.points','','','Make in object lines to points (ignore points)',@proc_object_to_points);
             command ('To vectors','edit.object.to.vectors','','','Make in object lines to vectors (erase points)',@proc_object_to_vectors);
             command ('To one line','edit.object.to.one.line','','','Make in object all points, vectors and lines to one line',@proc_object_to_one_line);
      _endbox;
      _separator;
      _hbox;
             command ('To points','edit.objects.to.points','','','Make in all objects lines to points (ignore points)',@proc_objects_to_points);
             command ('To vectors','edit.objects.to.vectors','','','Make in all objects lines to vectors (erase points)',@proc_objects_to_vectors);
             command ('To loops','edit.objects.to.loops','','','Make in all objects lines to loops',@proc_objects_to_loops);
             command ('To lines','edit.objects.to.lines','','','Make in all objects loops to lines',@proc_objects_to_lines);
             command ('To one line','edit.objects.to.one.line','','','Make in all objects all points, vectors and lines to one line',@proc_objects_to_one_line);
             command ('To one object','edit.objects.to.one.object','','','Make all objects to one object',@proc_objects_to_one_object);
      _endbox;
      _separator;
      _hbox;
             command ('To one material','edit.material.to.one.object','','','Make all same materials to one object',@proc_material_to_one_object);
             command ('To one name','edit.name.to.one.object','','','Make all same names to one object',@proc_name_to_one_object);
             command ('To unique name','edit.name.to.unique','','','Make all names to unique names',@proc_name_to_unique);
      _endbox;
      _hbox;
            _label('Pattern:');  edit_name_pattern := _edit ('');
             command ('Replace name','edit.name.replace','','','Replace pattern with new pattern',@proc_name_replace);
             edit_name_to := _edit (''); _label(':To');
      _endbox;
      _separator;
      _hbox;
             _label;
             command ('Erase same','edit.erase.same','','','Erase points, vectors or lines at same position in objects',@proc_erase_same);
             command ('Clue same','edit.clue.same','','','Clue points, vectors or lines at same position in objects',@proc_clue_same);
             _label;
      _endbox;
      _separator;
      _hbox;
            command ('Mean near x','calculate.groups.mean.near.x','','','Mean near x values on groups',@proc_groups_mean_near_x);
            command ('... y','calculate.groups.mean.near.y','','','Mean near y values on groups',@proc_groups_mean_near_y);
            command ('... z','calculate.groups.mean.near.z','','','Mean near z values on groups',@proc_groups_mean_near_z);
            command ('... t','calculate.groups.mean.near.t','','','Mean near t values on groups',@proc_groups_mean_near_t);
            _label ('Range:'); edit_near := _smalledit ('5');
      _endbox;
_endbox;
_endpage;

_page ('Layer ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Erase:</b>');
            _expand;
            command ('Points','edit.erase.points','','','Erase only points',@proc_erase_points);
            command ('Vectors','edit.erase.vectors','','','Erase only vectors',@proc_erase_vectors);
            command ('Lines','edit.erase.lines','','','Erase only lines',@proc_erase_lines);
            command ('Loops','edit.erase.loops','','','Erase line loops (no backward direction)',@proc_erase_loops);
      _endbox;
      _separator;
      _hbox;
            command ('Erase duplicates','edit.erase.duplicates','','','Erase duplicate lines, vectors and points',@proc_erase_duplicates);
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _shrink;
                  _label ('<b>Erase near:</b>');
                  _expand;
                  _label ('Range:'); edit_near_duplicates := _smalledit ('0');
            _endbox;
            _hbox;
                  command ('Duplicates','edit.erase.near.duplicates','','','Erase near duplicate lines, vectors and points',@proc_erase_near_duplicates);
                  _label ('|');
                  command ('Begin','edit.erase.near.duplicates.begin','','','Erase near duplicate lines, vectors and points (only for the first point)',@proc_erase_near_duplicates_begin);
                  command ('Both','edit.erase.near.duplicates.ends','','','Erase near duplicate lines, vectors and points (only for the first and last point)',@proc_erase_near_duplicates_ends);
                  command ('End','edit.erase.near.duplicates.end','','','Erase near duplicate lines, vectors and points (only for the last point)',@proc_erase_near_duplicates_end);
            _endbox;
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Fillup:</b>');
            _expand;
            command ('Points','edit.fillup.points','','','Fillup points t value with values from 1...',@proc_edit_fillup_points);
            command ('Line ends with 1','edit.fillup.ends.one','','','Fillup vector/line/loop ends t values with value 1',@proc_edit_fillup_line_ends_one);
            command ('Line ends','edit.fillup.ends','','','Fillup vector/line/loop ends t values with values from 1...',@proc_edit_fillup_line_ends);
            {command ('Lines','edit.fillup.lines','','','Fillup lines with material from 1...',@proc_edit_fillup_lines);}  // doppelt
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _shrink;
                  _label ('<b>Mean near:</b>');
                  _expand;
                  _label ('Range:'); edit_mean_near_duplicates := _smalledit ('0');
            _endbox;
            _hbox;
                  command ('Duplicates','edit.mean.near.duplicates','','','Mean near duplicate points in lines, vectors and points',@proc_mean_near_duplicates);
                  command ('3D dup (n-≻t)','edit.mean.near.duplicates.n','','','Mean near duplicate points in lines, vectors and points (only 3D) and store number in t (is used as weighting for an extra run)',@proc_mean_near_duplicates_n);
                  command ('3D dup (material, n-≻t)','edit.mean.near.duplicates.material','','','Mean near duplicate points in lines, vectors and points (only 3D and for different materials) and store number in t (is used as weighting for an extra run)',@proc_mean_near_duplicates_material);
            _endbox;
            _hbox;
                  command ('3D dup','edit.mean.near.duplicates.3d','','','Mean near duplicate points in lines, vectors and points (only 3D duplicates)',@proc_mean_near_duplicates_3d);
                  command ('3D dup (t)','edit.mean.near.duplicates.t','','','Mean near duplicate points in lines, vectors and points (only 3D and for different t values)',@proc_mean_near_duplicates_t);
                  command ('3D dup (t ¬0)','edit.mean.near.duplicates.t.zero','','','Mean near duplicate points in lines, vectors and points (only 3D and for different t values – ignores 0)',@proc_mean_near_duplicates_t_zero);
                  command ('3D dup (material, t)','edit.mean.near.duplicates.t.material','','','Mean near duplicate points in lines, vectors and points (only 3D and for different t values and for different materials)',@proc_mean_near_duplicates_t_material);
            _endbox;
      _endbox;
_endbox;
_endpage;

{_page ('Raster '); deprecated  ->>
_vbox;
_expand;}
      {_hbox;
            command ('Clear x','edit.clear.x','','','Clear x-axis to 0',@proc_clear_x);
            command ('Clear y','edit.clear.y','','','Clear y-axis to 0',@proc_clear_y);
            command ('Clear z','edit.clear.z','','','Clear z-axis to 0',@proc_clear_z);
            command ('Clear t','edit.clear.t','','','Clear t-axis to 0',@proc_clear_t);
      _endbox;}
      macro_self.putprocedure ('edit.clear.x','','','Clear x-axis to 0',@proc_clear_x);
      macro_self.putprocedure ('edit.clear.y','','','Clear y-axis to 0',@proc_clear_y);
      macro_self.putprocedure ('edit.clear.z','','','Clear z-axis to 0',@proc_clear_z);
      macro_self.putprocedure ('edit.clear.t','','','Clear t-axis to 0',@proc_clear_t);
      {_separator;
      _hbox;
            command ('Swap x|y','edit.swap.xy','','','Swap x with y',@proc_swap_xy); macro_self.putprocedure ('edit.swap.yx','','','Swap y with x',@proc_swap_xy);
            command ('Swap x|z','edit.swap.xz','','','Swap x with z',@proc_swap_xz); macro_self.putprocedure ('edit.swap.zx','','','Swap z with x',@proc_swap_xz);
            command ('Swap y|z','edit.swap.yz','','','Swap y with z',@proc_swap_yz); macro_self.putprocedure ('edit.swap.zy','','','Swap z with y',@proc_swap_yz);
      _endbox;
      _hbox;
            command ('Swap x|t','edit.swap.xt','','','Swap x with t',@proc_swap_xt); macro_self.putprocedure ('edit.swap.tx','','','Swap t with x',@proc_swap_xt);
            command ('Swap y|t','edit.swap.yt','','','Swap y with t',@proc_swap_yt); macro_self.putprocedure ('edit.swap.ty','','','Swap t with y',@proc_swap_yt);
            command ('Swap z|t','edit.swap.zt','','','Swap z with t',@proc_swap_zt); macro_self.putprocedure ('edit.swap.tz','','','Swap t with z',@proc_swap_zt);
      _endbox;}
      macro_self.putprocedure ('edit.swap.xy','','','Swap x with y',@proc_swap_xy); macro_self.putprocedure ('edit.swap.yx','','','Swap y with x',@proc_swap_xy);
      macro_self.putprocedure ('edit.swap.xz','','','Swap x with z',@proc_swap_xz); macro_self.putprocedure ('edit.swap.zx','','','Swap z with x',@proc_swap_xz);
      macro_self.putprocedure ('edit.swap.yz','','','Swap y with z',@proc_swap_yz); macro_self.putprocedure ('edit.swap.zy','','','Swap z with y',@proc_swap_yz);
      macro_self.putprocedure ('edit.swap.xt','','','Swap x with t',@proc_swap_xt); macro_self.putprocedure ('edit.swap.tx','','','Swap t with x',@proc_swap_xt);
      macro_self.putprocedure ('edit.swap.yt','','','Swap y with t',@proc_swap_yt); macro_self.putprocedure ('edit.swap.ty','','','Swap t with y',@proc_swap_yt);
      macro_self.putprocedure ('edit.swap.zt','','','Swap z with t',@proc_swap_zt); macro_self.putprocedure ('edit.swap.tz','','','Swap t with z',@proc_swap_zt);
      {_separator;
      _hbox;
             command ('Mean','edit.mean','','','Mean all points in object',@proc_edit_mean);
             command ('Mean x','edit.mean.x','','','Mean from all points in object with the same x',@proc_edit_mean_x);
             command ('Mean y','edit.mean.y','','','Mean from all points in object with the same y',@proc_edit_mean_y);
             command ('Mean z','edit.mean.z','','','Mean from all points in object with the same z',@proc_edit_mean_z);
             command ('Mean t','edit.mean.t','','','Mean from all points in object with the same t',@proc_edit_mean_t);
      _endbox;}
      macro_self.putprocedure ('edit.mean','','','Mean all points in object',@proc_edit_mean);
      macro_self.putprocedure ('edit.mean.x','','','Mean from all points in object with the same x',@proc_edit_mean_x);
      macro_self.putprocedure ('edit.mean.y','','','Mean from all points in object with the same y',@proc_edit_mean_y);
      macro_self.putprocedure ('edit.mean.z','','','Mean from all points in object with the same z',@proc_edit_mean_z);
      macro_self.putprocedure ('edit.mean.t','','','Mean from all points in object with the same t',@proc_edit_mean_t);
{_endbox;
_endpage;}

_page ('Color ');
_vbox;
_expand;
      _hbox;
            command ('Dark material','edit.random.material.dark','','','Fill material with random $HHHHHH (all colors are shifted to darken)',@proc_edit_random_mat_dark);
            command ('Random material','edit.random.material','','','Fill material with random $HHHHHH (all colors are shifted to brighten)',@proc_edit_random_mat);
            command ('Bright material','edit.random.material.bright','','','Fill material with random $HHHHHH (all colors are shifted to brighten)',@proc_edit_random_mat_bright);
      _endbox;
      _hbox;
            command ('Remove material','edit.random.material.remove','','','Fill material with 0',@proc_edit_random_mat_remove);
      _endbox;
      _separator;
      _hbox;
            command ('Dark object','edit.random.object.dark','','','Fill object name with random $HHHHHH (all colors are shifted to darken)',@proc_edit_random_obj_dark);
            command ('Random object','edit.random.object','','','Fill object name with random $HHHHHH (all colors are shifted to brighten)',@proc_edit_random_obj);
            command ('Bright object','edit.random.object.bright','','','Fill object name with random $HHHHHH (all colors are shifted to brighten)',@proc_edit_random_obj_bright);
      _endbox;
      _hbox;
            command ('Remove color','edit.random.object.remove','','','Remove in object name (_$HHHHHH) on last position',@proc_edit_random_obj_remove);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Transfer:</b>');
            _expand;
            command ('T with material','edit.coloring.t','','','Fill t with material ($HHHHHH)',@proc_edit_coloring_mat_to_t);
            command ('T with object pattern','edit.coloring.t.direct','','','Fill t with object pattern ($HHHHHH)',@proc_edit_coloring_obj_to_t);
            command ('Material with object pattern','edit.coloring.material','','','Fill material with object pattern ($HHHHHH)',@proc_edit_coloring_obj_to_mat);
      _endbox;
_endbox;
_endpage;
