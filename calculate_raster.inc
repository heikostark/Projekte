{ **************************************************************************** }
{ ***************************** Calculate ************************************ }
{ **************************************************************************** }

{ ****************************** Raster ************************************** }

procedure proc_calculate_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
var min,max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or ((tmacro(macro^).getparameter(1) = 'auto') and (tmacro(macro^).getparameter(2) = 'auto')) then { only command }
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          _setedit (calculate_dimension_min,getstring(min,3));

          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          _setedit (calculate_dimension_max,getstring(max,3));
     end
     else
     begin
          min := _gethyper (calculate_dimension_min,macro,1);
          max := _gethyper (calculate_dimension_max,macro,2);
     end;
     tmacro(macro^).writeredo ('raster.set.minmax','auto auto');
end;

procedure proc_calculate_set_dimension_min (p1,macro : gtk_pointer); cdecl;
var min : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then { only command }
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          _setedit (calculate_dimension_min,getstring(min,3));
     end
     else
     begin
          min := _gethyper (calculate_dimension_min,macro,1);
     end;
     tmacro(macro^).writeredo ('raster.set.min','auto');
end;

procedure proc_calculate_set_dimension_max (p1,macro : gtk_pointer); cdecl;
var max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then { only command }
     begin
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;    
          end;
          if max = Hmin then max := Hzero;
          _setedit (calculate_dimension_max,getstring(max,3));
     end
     else
     begin
          max := _gethyper (calculate_dimension_max,macro,1);
     end;
     tmacro(macro^).writeredo ('raster.set.max','auto');
end;

{ ********************************* Points *********************************** }

procedure proc_points (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
begin
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              d := norm (c)*raster;
                              for count := 0 to trunc(getlength (c/raster))+1 do
                              begin
                                   e := u+(count*d);
                                   w := round((e-min)/raster);
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                              end;
                         end
                         else if finput^.getlinepointlength (o,l) = 1 then
                         begin
                              c := htov (finput^.getobject (o,l,1));
                              w := round((c-min)/raster);
                              spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),0));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('points');
               spacecount.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.points',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_count_points (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
begin
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              d := norm (c)*raster;
                              for count := 0 to trunc(getlength (c/raster))+1 do
                              begin
                                   e := u+(count*d);
                                   w := round((e-min)/raster);
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get (w.x+1,w.y+1,w.z+1)+1);
                              end;
                         end
                         else if finput^.getlinepointlength (o,l) = 1 then
                         begin
                              c := htov (finput^.getobject (o,l,1));
                              w := round((c-min)/raster);
                              spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get (w.x+1,w.y+1,w.z+1)+1);
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),spacecount.get (x+1,y+1,z+1)));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('point_count');
               spacecount.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.point.count',getstring(raster)+' '+getstring(raster_min));
     end;
end;

{ ********************************* Line length ****************************** }

procedure proc_line_length (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r,len : real;
    newline : tpolyreal;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    begin
                         newline.init;
                         for l := 1 to finput^.getobjectlinelength(o) do
                         begin
                              len := 0;
                              if finput^.getlinepointlength (o,l) > 1 then
                              for p := 1 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   u := htov (finput^.getobject (o,l,p));
                                   v := htov (finput^.getobject (o,l,p+1));
                                   len := len + getlength(v-u);
                              end;
                              newline.put (newline.length+1,len);
                         end;

                         for l := 1 to finput^.getobjectlinelength(o) do
                         begin
                              len := newline.get (l);
                              if finput^.getlinepointlength (o,l) > 1 then
                              for p := 1 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   u := htov (finput^.getobject (o,l,p));
                                   v := htov (finput^.getobject (o,l,p+1));
                                   c := v-u;
                                   if not(c = Vzero) then
                                   begin
                                        d := norm (c)*raster;
                                        for count := 0 to trunc(getlength (c/raster))+1 do
                                        begin
                                             e := u+(count*d);
                                             w := round((e-min)/raster);
                                             spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                             space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+len);
                                        end;
                                   end;
                              end;
                         end;
                         newline.done;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('line_length');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.line.length',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_count_lines (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacebyte;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
begin
     space := Default(tspacebyte);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength(o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l)-1 do
                                   begin
                                        u := htov (finput^.getobject (o,l,p));
                                        v := htov (finput^.getobject (o,l,p+1));
                                        c := v-u;
                                        if not(c = Vzero) then
                                        begin
                                             d := norm (c)*raster;
                                             for count := 0 to trunc(getlength (c/raster))+1 do
                                             begin
                                                  e := u+(count*d);
                                                  w := round((e-min)/raster);
                                                  space.put (w.x+1,w.y+1,w.z+1,1);
                                             end;
                                        end;
                                   end;
                                   for z := 0 to steps.z-1 do
                                       for y := 0 to steps.y-1 do
                                           for x := 0 to steps.x-1 do
                                           begin
                                                if space.get (x+1,y+1,z+1) = 1 then spacecount.put (x+1,y+1,z+1,spacecount.get (x+1,y+1,z+1)+1);
                                           end;
                                   space.clear;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),spacecount.get (x+1,y+1,z+1)));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('line_count');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.line.count',getstring(raster)+' '+getstring(raster_min));
     end;
end;

{ ********************* Pennation angle between axis ************************* }

procedure proc_pennation_x (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not(c = Vzero) then
                              begin
                                   if format.degree then r := halfangle (c,gv(1,0,0))*deg
                                                    else r := halfangle (c,gv(1,0,0));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_x');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.x',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_pennation_y (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not(c = Vzero) then
                              begin
                                   if format.degree then r := halfangle (c,gv(0,1,0))*deg
                                                    else r := halfangle (c,gv(0,1,0));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_y');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.y',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_pennation_z (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not(c = Vzero) then
                              begin
                                   if format.degree then r := halfangle (c,gv(0,0,1))*deg
                                                    else r := halfangle (c,gv(0,0,1));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_z');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.z',getstring(raster)+' '+getstring(raster_min));
     end;
end;

{ ******************** Pennation angle between palne ************************* }

procedure proc_pennation_xy (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
      {    writeln (getstring(min)+' '+getstring(max)); }
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not(c = Vzero) then
                              begin
                                   if format.degree then r := 90-(halfangle (c,gv(0,0,1))*deg)
                                                    else r := 90-halfangle (c,gv(0,0,1));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_xy');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.xy',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_pennation_yz (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
       {   writeln (getstring(min)+' '+getstring(max));  }
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not (c = Vzero) then
                              begin
                                   if format.degree then r := 90-(halfangle (c,gv(1,0,0))*deg)
                                                    else r := 90-halfangle (c,gv(1,0,0));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_yz');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.yz',getstring(raster)+' '+getstring(raster_min));
     end;
end;

procedure proc_pennation_zx (p1,macro : gtk_pointer); cdecl;
var x,y,z,o,l,p,count,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    u,v,c,d,e : vector;
    w : vectornat;
    r : real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := htov (finput^.getobject (o,l,p));
                              v := htov (finput^.getobject (o,l,p+1));
                              c := v-u;
                              if not (c = Vzero) then
                              begin
                                   if format.degree then r := 90-(halfangle (c,gv(0,1,0))*deg)
                                                    else r := 90-halfangle (c,gv(0,1,0));
                                   d := norm (c)*raster;
                                   for count := 0 to trunc(getlength (c/raster))+1 do
                                   begin
                                        e := u+(count*d);
                                        w := round((e-min)/raster);
                                        spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                        space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+r);
                                   end;
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,z+1) >= raster_min then
                            begin
                                 r := space.get (x+1,y+1,z+1)/spacecount.get (x+1,y+1,z+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),r));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_angle_zx');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.pennation.zx',getstring(raster)+' '+getstring(raster_min));
     end;
end;

{ ***************************** Pennation vector ***************************** }

procedure proc_pennation_vector (p1,macro : gtk_pointer); cdecl;
var x,y,z,l,raster_min : integer;
    min,max,raster : vector;
    steps : vectornat;
    spacex,spacey,spacez : tspacereal;
    u,v,c : vector;
    w : vectornat;
    a : vector;
begin
     spacex := Default(tspacereal);
     spacey := Default(tspacereal);
     spacez := Default(tspacereal);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          steps := round (trunc((max-min)/raster)+2);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               spacex.init (steps.x,steps.y,steps.z);
               spacey.init (steps.x,steps.y,steps.z);
               spacez.init (steps.x,steps.y,steps.z);
               for z := 1 to finput^.getlinelength do
               begin
                    l := finput^.getalllinepointlength (z);
                    if l > 1 then
                    begin
                         for x := 1 to l-1 do
                         begin
                              u := htov (finput^.getline (z,x));
                              v := htov (finput^.getline (z,x+1));
                              a := v-u;
                              if not (a = Vzero) then
                              begin
                                   c := (u+v)/2;
                                   w := gvn (round((c.x-min.x)/raster.x),round((c.y-min.y)/raster.y),round((c.z-min.z)/raster.z));
                                   spacex.put (w.x+1,w.y+1,w.z+1,spacex.get(w.x+1,w.y+1,w.z+1)+a.x);
                                   spacey.put (w.x+1,w.y+1,w.z+1,spacey.get(w.x+1,w.y+1,w.z+1)+a.y);
                                   spacez.put (w.x+1,w.y+1,w.z+1,spacez.get(w.x+1,w.y+1,w.z+1)+a.z);
                              end;
                         end;
                    end;
               end;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            a := norm(gv(spacex.get(x+1,y+1,z+1),spacey.get(x+1,y+1,z+1),spacez.get(x+1,y+1,z+1)));
                            if a <> Vzero then
                            begin
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(z*raster.z),0));
                                 dummy.newpoint (gh(min.x+(x*raster.x)+a.x,min.y+(y*raster.y)+a.y,min.z+(z*raster.z)+a.z,0));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('pennation_vector');
               spacez.done;
               spacey.done;
               spacex.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.vector.pennation',getstring(raster)+' '+getstring(raster_min));
     end;
end;

{ ******************************* Curvature Torsion ************************** }

procedure proc_raster_curvature (p1,macro : gtk_pointer); cdecl;
var x,y,l,p,bl,poly,step,raster_min : integer;
    min,max,raster : vector;
    first_len,last_len : real;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    v : vector;
    w : vectornat;
    c : real;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter :real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);
     linepoly := Default(tpolynom3d);
     linefunc := Default(tcurveproperty3d);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          poly := abs(_getnat(raster_polynom,macro,3));

          steps := round (trunc((max-min)/raster)+2);
          step := round(getlength (steps));
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for l := 1 to finput^.getlinelength do
               begin
                    p := finput^.getalllinepointlength (l);
                    if (p > 1) then
                    begin
                         _help_getpolynom_3d (l,poly,linepoly,first_len,last_len); { get the polynom }
                         linefunc.init (linepoly);

                         if finput^.getline (l,1) <> finput^.getline (l,p) then { no loop }
                         begin
                              factor := linepoly.pathlength/(step-1);
                              counter := 0;
                              for bl := 1 to step do
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.curvature (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end
                         else
                         begin
                              factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                              counter := first_len; { ignore first }
                              for bl := 1 to step-1 do { ignore last }
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.curvature (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end;
                         linefunc.done;
                         linepoly.done;
                    end;
               end;
{ store }
               for l := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,l+1) > 0 then
                            begin
                                 c := space.get (x+1,y+1,l+1)/spacecount.get (x+1,y+1,l+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(l*raster.z),c));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('curvature');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.curvature',getstring(raster)+' '+getstring(raster_min)+' '+getstring(poly));
     end;
end;

procedure proc_raster_curvature_fit (p1,macro : gtk_pointer); cdecl;
var x,y,l,p,bl,poly,step,raster_min : integer;
    min,max,raster : vector;
    first_len,last_len : real;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    v : vector;
    w : vectornat;
    c : real;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter :real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);
     linepoly := Default(tpolynom3d);
     linefunc := Default(tcurveproperty3d);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          poly := abs(_getnat(raster_polynom,macro,3));

          steps := round (trunc((max-min)/raster)+2);
          step := round(getlength (steps));

          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for l := 1 to finput^.getlinelength do
               begin
                    p := finput^.getalllinepointlength (l);
                    if (p > 1) then
                    begin
                         _help_getfit_3d (l,poly,linepoly,first_len,last_len); { get the polynom }
                         linefunc.init (linepoly);

                         if finput^.getline (l,1) <> finput^.getline (l,p) then { no loop }
                         begin
                              factor := linepoly.pathlength/(step-1);
                              counter := 0;
                              for bl := 1 to step do
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.curvature (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end
                         else
                         begin
                              factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                              counter := first_len; { ignore first }
                              for bl := 1 to step-1 do { ignore last }
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.curvature (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end;
                         linefunc.done;
                         linepoly.done;
                    end;
               end;
{ store }
               for l := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,l+1) > 0 then
                            begin
                                 c := space.get (x+1,y+1,l+1)/spacecount.get (x+1,y+1,l+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(l*raster.z),c));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('curvature');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.curvature.fit',getstring(raster)+' '+getstring(raster_min)+' '+getstring(poly));
     end;
end;

procedure proc_raster_torsion (p1,macro : gtk_pointer); cdecl;
var x,y,l,p,bl,poly,step,raster_min : integer;
    min,max,raster : vector;
    first_len,last_len : real;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    v : vector;
    w : vectornat;
    c : real;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter :real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);
     linepoly := Default(tpolynom3d);
     linefunc := Default(tcurveproperty3d);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          poly := abs(_getnat(raster_polynom,macro,3));

          steps := round (trunc((max-min)/raster)+2);
          step := round(getlength (steps));
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for l := 1 to finput^.getlinelength do
               begin
                    p := finput^.getalllinepointlength (l);
                    if (p > 1) then
                    begin
                         _help_getpolynom_3d (l,poly,linepoly,first_len,last_len); { get the polynom }
                         linefunc.init (linepoly);

                         if finput^.getline (l,1) <> finput^.getline (l,p) then { no loop }
                         begin
                              factor := linepoly.pathlength/(step-1);
                              counter := 0;
                              for bl := 1 to step do
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.torsion (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end
                         else
                         begin
                              factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                              counter := first_len; { ignore first }
                              for bl := 1 to step-1 do { ignore last }
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.torsion  (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end;
                         linefunc.done;
                         linepoly.done;
                    end;
               end;
{ store }
               for l := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,l+1) > 0 then
                            begin
                                 c := space.get (x+1,y+1,l+1)/spacecount.get (x+1,y+1,l+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(l*raster.z),c));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('torsion');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.torsion',getstring(raster)+' '+getstring(raster_min)+' '+getstring(poly));
     end;
end;

procedure proc_raster_torsion_fit (p1,macro : gtk_pointer); cdecl;
var x,y,l,p,bl,poly,step,raster_min : integer;
    min,max,raster : vector;
    first_len,last_len : real;
    steps : vectornat;
    space : tspacereal;
    spacecount : tspacenat;
    v : vector;
    w : vectornat;
    c : real;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter :real;
begin
     space := Default(tspacereal);
     spacecount := Default(tspacenat);
     linepoly := Default(tpolynom3d);
     linefunc := Default(tcurveproperty3d);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _getvector (calculate_dimension_min);
          max := _getvector (calculate_dimension_max);
          raster := _getvector (calculate_raster,macro,1);
          raster_min := _getnat (calculate_raster_minpoints,macro,2);
          if raster_min <= 0 then raster_min := 1;
          poly := abs(_getnat(raster_polynom,macro,3));

          steps := round (trunc((max-min)/raster)+2);
          step := round(getlength (steps));
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               spacecount.init (steps.x,steps.y,steps.z);
               for l := 1 to finput^.getlinelength do
               begin
                    p := finput^.getalllinepointlength (l);
                    if (p > 1) then
                    begin
                         _help_getfit_3d (l,poly,linepoly,first_len,last_len); { get the polynom }
                         linefunc.init (linepoly);

                         if finput^.getline (l,1) <> finput^.getline (l,p) then { no loop }
                         begin
                              factor := linepoly.pathlength/(step-1);
                              counter := 0;
                              for bl := 1 to step do
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.torsion (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end
                         else
                         begin
                              factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                              counter := first_len; { ignore first }
                              for bl := 1 to step-1 do { ignore last }
                              begin
                                   v := linepoly.polynom (counter);
                                   c := linefunc.torsion (counter);
                                   w := gvn (round((v.x-min.x)/raster.x),round((v.y-min.y)/raster.y),round((v.z-min.z)/raster.z));
                                   spacecount.put (w.x+1,w.y+1,w.z+1,spacecount.get(w.x+1,w.y+1,w.z+1)+1);
                                   space.put (w.x+1,w.y+1,w.z+1,space.get(w.x+1,w.y+1,w.z+1)+c);
                                   counter := counter + factor;
                              end;
                         end;
                         linefunc.done;
                         linepoly.done;
                    end;
               end;
{ store }
               for l := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if spacecount.get (x+1,y+1,l+1) > 0 then
                            begin
                                 c := space.get (x+1,y+1,l+1)/spacecount.get (x+1,y+1,l+1);
                                 dummy.newpoint (gh(min.x+(x*raster.x),min.y+(y*raster.y),min.z+(l*raster.z),c));
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('torsion');
               spacecount.done;
               space.done;
               cleanup (dummy);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('raster.set.min',getstring (min));
          tmacro(macro^).writeredo ('raster.set.max',getstring (max));
          tmacro(macro^).writeredo ('raster.scalar.torsion.fit',getstring(raster)+' '+getstring(raster_min)+' '+getstring(poly));
     end;
end;
