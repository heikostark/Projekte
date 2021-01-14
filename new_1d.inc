{ ************************************* Polynom ****************************** }

procedure l_polynom_change (p1,macro : gtk_pointer); cdecl;
var step : integer;
    linepoly : tpolynom4d;
    factor,counter,steps,begins,ends :real;
    z,bl,poly : integer;
    s : utf16;
begin
     linepoly := Default (tpolynom4d);

     poly := _getitem (input_polynom_method,macro,1);
     steps := _getreal (polynom_step,macro,3);
     if (steps > 0) and (poly > 0) then
     begin
          _cursor_watch;
          begins := _getreal (polynom_begin,macro,2);
          ends := _getreal (polynom_end,macro,4);
          if poly > 9 then poly := 9;
          linepoly.init (poly+1);
          for z := 1 to poly+1 do
          begin
               linepoly.put (z,_gethyper (polynom[z-1],macro,4+z));
          end;
          if finput^.linecounter > 0 then finput^.markallline(finput^.linecounter);
          step := round((ends-begins)/steps);
          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (linepoly.polynom (counter));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('changed_polynom');
          end;
          s := '';
          if into (poly,0,9) then
          begin
               for step := 0 to poly
                   do s := s + getstring(linepoly.get(step+1)) + ' ';
          end;
          tmacro(macro^).writeredo ('formula.polynom.change',getstring(poly)+' '+getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+s);
          linepoly.done;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
     end;
end;

procedure l_polynom_new (p1,macro : gtk_pointer); cdecl;
var step : integer;
    linepoly : tpolynom4d;
    factor,counter,steps,begins,ends :real;
    z,bl,poly : integer;
    s : utf16;
begin
     linepoly := Default (tpolynom4d);

     poly := _getitem (input_polynom_method,macro,1);
     steps := _getreal (polynom_step,macro,3);
     if (steps > 0) and (poly > 0) then
     begin
          _cursor_watch;
          begins := _getreal (polynom_begin,macro,2);
          ends := _getreal (polynom_end,macro,4);
          if poly > 9 then poly := 9;
          linepoly.init (poly+1);
          for z := 1 to poly+1 do
          begin
               linepoly.put (z,_gethyper (polynom[z-1],macro,4+z));
          end;
          step := round((ends-begins)/steps);
          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (linepoly.polynom (counter));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('polynom');
          end;
          s := '';
          if into (poly,0,9) then
          begin
               for step := 0 to poly
                   do s := s + getstring(linepoly.get(step+1)) + ' ';
          end;
          tmacro(macro^).writeredo ('formula.polynom',getstring(poly)+' '+getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+s);
          linepoly.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
     end;
end;

{ Vector & Line }

procedure proc_vector (p1,macro : gtk_pointer); cdecl;
var normal,point : vector;
begin
     _cursor_watch;
     point := _getvector (formula_point,macro,1);
     normal := _getvector (formula_normal,macro,2);

     finput^.newpoint (gh(point,0));
     finput^.newpoint (gh(point+normal,0));
     finput^.newline (0); { newline }
     finput^.newobject ('new_vector');

     calculating;
     updating;
     drawing;
     _cursor_arrow;
     tmacro(macro^).writeredo ('formula.vector',getstring(point)+' '+getstring(normal));
end;

procedure proc_norm (p1,macro : gtk_pointer); cdecl;
var normal,point : vector;
begin
     _cursor_watch;
     point := _getvector (formula_point,macro,1);
     normal := norm(_getvector (formula_normal,macro,2));

     finput^.newpoint (gh(point,0));
     finput^.newpoint (gh(point+normal,0));
     finput^.newline (0); { newline }
     finput^.newobject ('new_norm');

     calculating;
     updating;
     drawing;
     _cursor_arrow;
     tmacro(macro^).writeredo ('formula.norm',getstring(point)+' '+getstring(normal));
end;

procedure proc_newline (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends:real;
    bl : integer;
    normal,point : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := norm(_getvector (formula_normal,macro,5));

          step := round((ends-begins)/steps);

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (gh(point+(normal*counter),0));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('new_line');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.line',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                         getstring(point)+' '+getstring(normal));
     end;
end;

{ Circle }

procedure l_formula_circle (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends,radius :real;
    bl : integer;
    a,b,c,normal,point,first : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := _getvector (formula_normal,macro,5);
          radius := _getreal (formula_radius,macro,6);

          step := round((ends-begins)/steps);
          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               first := a+b*(radius*cos(counter))+c*(radius*sin(counter));
               for bl := 1 to step do
               begin
                    if bl = 1 then finput^.newpoint (gh(first,0))
                              else finput^.newpoint (gh(a+b*(radius*cos(counter))+c*(radius*sin(counter)),0));
                    counter := counter + factor;
               end;
               finput^.newpoint (gh(first,0)); { make loop }
               finput^.newline (0); { newline }
               finput^.newobject ('new_circle');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.circle',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                           getstring(point)+' '+getstring(normal)+' '+
                                           getstring(radius));
     end;
end;

procedure l_formula_rhelix (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends,radius,pitch : real;
    bl : integer;
    a,b,c,normal,point : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := _getvector (formula_normal,macro,5);
          radius := _getreal (formula_radius,macro,6);
          pitch := _getreal (formula_pitch,macro,7);

          step := round((ends-begins)/steps);
          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (a,normal));
          c := norm(cross (b,normal));
          a := point;

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (gh (a+b*(radius*cos(counter))+c*(radius*sin(counter))+normal*(pitch*counter),0));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('new_rhelix');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.helix.right',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                                getstring(point)+' '+getstring(normal)+' '+
                                                getstring(radius)+' '+getstring(pitch));
     end;
end;

procedure l_formula_lhelix (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends,radius,pitch :real;
    bl : integer;
    a,b,c,normal,point : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := _getvector (formula_normal,macro,5);
          radius := _getreal (formula_radius,macro,6);
          pitch := _getreal (formula_pitch,macro,7);

          step := round((ends-begins)/steps);
          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (a,normal));
          c := norm(cross (b,normal));
          a := point;

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (gh (a+b*(radius*cos(counter))+c*(radius*sin(counter))+normal*(-1*(pitch*counter)),0));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('new_lhelix');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.helix.left',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                               getstring(point)+' '+getstring(normal)+' '+
                                               getstring(radius)+' '+getstring(pitch));
     end;
end;

procedure l_formula_invrhelix (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends,radius,pitch :real;
    bl : integer;
    a,b,c,normal,point : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := _getvector (formula_normal,macro,5);
          radius := _getreal (formula_radius,macro,6);
          pitch := _getreal (formula_pitch,macro,7);

          step := round((ends-begins)/steps);
          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (a,normal));
          c := norm(cross (b,normal));
          a := point;

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (gh (a+b*(-1*radius*cos(counter))+c*(-1*radius*sin(counter))+normal*(-1*pitch*counter),0));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('new_inv_rhelix');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.inverse.helix.right',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                                        getstring(point)+' '+getstring(normal)+' '+
                                                        getstring(radius)+' '+getstring(pitch));
     end;
end;

procedure l_formula_invlhelix (p1,macro : gtk_pointer); cdecl;
var step : integer;
    factor,counter,steps,begins,ends,radius,pitch :real;
    bl : integer;
    a,b,c,normal,point : vector;
begin
     steps := _getreal (formula_xstep,macro,2);
     if steps > 0 then
     begin
          _cursor_watch;
          begins := _getreal (formula_xbegin,macro,1);
          ends := _getreal (formula_xend,macro,3);
          point := _getvector (formula_point,macro,4);
          normal := _getvector (formula_normal,macro,5);
          radius := _getreal (formula_radius,macro,6);
          pitch := _getreal (formula_pitch,macro,7);

          step := round((ends-begins)/steps);
          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (a,normal));
          c := norm(cross (b,normal));
          a := point;

          if step > 1 then
          begin
               factor := (ends-begins)/step;
               counter := begins;
               for bl := 1 to step+1 do
               begin
                    finput^.newpoint (gh (a+b*(-1*radius*cos(counter))+c*(-1*radius*sin(counter))+normal*(pitch*counter),0));
                    counter := counter + factor;
               end;
               finput^.newline (0); { newline }
               finput^.newobject ('new_inv_lhelix');
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('formula.inverse.helix.left',getstring(begins)+' '+getstring(steps)+' '+getstring(ends)+' '+
                                                       getstring(point)+' '+getstring(normal)+' '+
                                                       getstring(radius)+' '+getstring(pitch));
     end;
end;
