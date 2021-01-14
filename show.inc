{ **************************************************************************** }
{ *********************************** show ********************************* }
{ **************************************************************************** }

var p_o_show : string;

{ ******************************** Sphere ************************************ }

procedure p_o_spheres;
var pov : twritepov;
    glob : string;
    cursor : pgdkcursor;
procedure run (f : tfilevector;radius : extended;color : vector);
var x : longint;
begin
     glob := '';
     if f.length > 0 then
     begin
          for x := 1 to f.length do
          begin
               glob := glob + pov.sphere (f.get(x),radius,'');
          end;
          pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     p_o_show := filename;
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     pov.incinit (p_o_show);
     run (f1,getreal(gtk_entry_get_text (pgtkentry(editredradius))),getvector(gtk_entry_get_text (pgtkentry(editred))));
     run (f2,getreal(gtk_entry_get_text (pgtkentry(editgreenradius))),getvector(gtk_entry_get_text (pgtkentry(editgreen))));
     run (f3,getreal(gtk_entry_get_text (pgtkentry(editblueradius))),getvector(gtk_entry_get_text (pgtkentry(editblue))));
     glob := '';
     pov.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

procedure proc_show_spheres; cdecl;
begin
     p_o_show := 'spheres.inc';
     _fileselection (p_o_show,@p_o_spheres);
end;


{ ******************************** Lines ************************************ }

procedure p_o_lines;
var pov : twritepov;
    glob : string;
    cursor : pgdkcursor;
procedure run (f : tfilevector;fl : tpolynat;radius : extended;color : vector);
var z,bl,l : longint;
begin
     glob := '';
     if f.length > 0 then
     begin
          for z := 1 to fl.length do
          begin
               if z <> fl.length then l := fl.get(z+1)-fl.get(z)
                                  else l := f.length-fl.get(z)+1;
               if l > 1 then
               begin
                    for bl := 0 to l-2 do
                    begin
                         glob := glob + pov.sphere (f.get(fl.get(z)+bl),radius,'');
                         glob := glob + pov.cylinder (f.get(fl.get(z)+bl),f.get(fl.get(z)+bl+1),radius,'');
                    end;
                    glob := glob + pov.sphere (f.get(fl.get(z)+l-1),radius,'');
               end
               else if l = 1 then glob := glob + pov.sphere (f.get(fl.get(z)),radius,'');
          end;
          pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     p_o_show := filename;
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     pov.incinit (p_o_show);
     run (f1,fl1,getreal(gtk_entry_get_text (pgtkentry(editredradius))),getvector(gtk_entry_get_text (pgtkentry(editred))));
     run (f2,fl2,getreal(gtk_entry_get_text (pgtkentry(editgreenradius))),getvector(gtk_entry_get_text (pgtkentry(editgreen))));
     run (f3,fl3,getreal(gtk_entry_get_text (pgtkentry(editblueradius))),getvector(gtk_entry_get_text (pgtkentry(editblue))));
     pov.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

procedure proc_show_lines; cdecl;
begin
     p_o_show := 'lines.inc';
     _fileselection (p_o_show,@p_o_lines);
end;

{ ******************************** Curves ************************************ }

procedure p_o_curves;
var pov : twritepov;
    glob : string;
    cursor : pgdkcursor;
procedure run (f : tfilevector;fl : tpolynat;radius : extended;color : vector);
var v,u : vector;
    z,bl,l : longint;
    line : tpolyvector;
    linepoly : tpolynom3d;
    factor,counter :extended;
begin
     glob := '';
     if f.length > 0 then
     begin
          for z := 1 to fl.length do
          begin
               if z <> fl.length then
               begin
                    l := fl.get(z+1)-fl.get(z);
                    v := f.get(fl.get(z)+((l-1) div 2));
               end
               else l := f.length-fl.get(z)+1;
               if l > 1 then
               begin
                    line.init (l);
                    for bl := 0 to l-1 do
                    begin
                         line.put (bl+1,f.get(fl.get(z)+bl));
                    end;
                    if l < 9 then
                    begin
                         linepoly.init (l);
                         linepoly.getpolynom (line);
                    end
                    else
                    begin
                         linepoly.init (9);
                         linepoly.getpolynom (line);
                    end;
                    l := getnat(gtk_entry_get_text (pgtkentry(show_povray_resolution)));
                    if l < 10 then l := 10;
                    factor := linepoly.pathlength/l;
                    counter := 0;
                    for bl := 1 to l-1 do
                    begin
                         v := linepoly.polynom (counter);
                         counter := counter + factor;
                         u := linepoly.polynom (counter);
                         glob := glob + pov.sphere (v,radius,'');
                         glob := glob + pov.cylinder (v,u,radius,'');
                    end;
                    glob := glob + pov.sphere (u,radius,'');
                    linepoly.done;
                    line.done;
               end
               else if l = 1 then glob := glob + pov.sphere (f.get(fl.get(z)),radius,'');
          end;
          pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     p_o_show := filename;
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     pov.incinit (p_o_show);
     run (f1,fl1,getreal(gtk_entry_get_text (pgtkentry(editredradius))),getvector(gtk_entry_get_text (pgtkentry(editred))));
     run (f2,fl2,getreal(gtk_entry_get_text (pgtkentry(editgreenradius))),getvector(gtk_entry_get_text (pgtkentry(editgreen))));
     run (f3,fl3,getreal(gtk_entry_get_text (pgtkentry(editblueradius))),getvector(gtk_entry_get_text (pgtkentry(editblue))));
     pov.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

procedure proc_show_curves; cdecl;
begin
     p_o_show := 'curves.inc';
     _fileselection (p_o_show,@p_o_curves);
end;

{ ******************************** Curvature ********************************* }

procedure p_o_curvature;
var pov : twritepov;
    r,g,b : vector;
    cursor : pgdkcursor;
function setcolor (c : extended) : vector;
var t,ll : extended;
    ra : range;
begin
     ra := liball.getrange (gtk_entry_get_text (pgtkentry(show_povray_range)));
     c := minmax (ra.min,ra.max,c,0,2);
     if c > 1 then
     begin
          ll := getlength(g-r);
          t := abs((1/c)/ll); if t > 1 then t := 1;
          setcolor := (maxnorm(r)*(1-t))+(maxnorm(g)*(t));
     end
     else if c = 1  then setcolor := maxnorm(g)
     else
     begin
          ll := getlength(g-b);
          t := abs(c/ll); if t > 1 then t := 1;
          setcolor := (maxnorm(b)*(1-t))+(maxnorm(g)*(t));
     end;
     setcolor := abs (setcolor);
     if setcolor.x > 1 then setcolor.x := 1;
     if setcolor.y > 1 then setcolor.y := 1;
     if setcolor.z > 1 then setcolor.z := 1;
end;
procedure run (f : tfilevector;fl : tpolynat;radius : extended);
var glob : string;
    v,u,color : vector;
    z,bl,l : longint;
    line : tpolyvector;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter,c :extended;
begin
     glob := '';
     if f.length > 0 then
     begin
          for z := 1 to fl.length do
          begin
               if z <> fl.length then
               begin
                    l := fl.get(z+1)-fl.get(z);
                    v := f.get(fl.get(z)+((l-1) div 2));
               end
               else l := f.length-fl.get(z)+1;
               if l > 1 then
               begin
                    line.init (l);
                    for bl := 0 to l-1 do
                    begin
                         line.put (bl+1,f.get(fl.get(z)+bl));
                    end;
                    if l < 9 then
                    begin
                         linepoly.init (l);
                         linepoly.getpolynom (line);
                    end
                    else
                    begin
                         linepoly.init (9);
                         linepoly.getpolynom (line);
                    end;
                    linefunc.init (linepoly);
                    l := getnat(gtk_entry_get_text (pgtkentry(show_povray_resolution)));
                    if l < 10 then l := 10;
                    factor := linepoly.pathlength/l;
                    counter := 0;
                    r := getvector(gtk_entry_get_text (pgtkentry(editred)));
                    g := getvector(gtk_entry_get_text (pgtkentry(editgreen)));
                    b := getvector(gtk_entry_get_text (pgtkentry(editblue)));
                    for bl := 1 to l-1 do
                    begin
                         v := linepoly.polynom (counter);
                         c := linefunc.curvature (counter);
                         color := setcolor (c);
                         glob := glob + pov.sphere (v,radius,pov.pigment(color));
                         counter := counter + factor;
                         u := linepoly.polynom (counter);
                         c := (c+linefunc.curvature (counter))/2;
                         color := setcolor (c);
                         glob := glob + pov.cylinder (v,u,radius,pov.pigment(color));
                    end;
                    counter := counter + factor;
                    v := linepoly.polynom (counter);
                    c := linefunc.curvature (counter);
                    color := setcolor (c);
                    glob := glob + pov.sphere (u,radius,pov.pigment(color));
                    linefunc.done;
                    linepoly.done;
                    line.done;
               end;
          end;
          pov.write (pov.union(glob));
     end;
end;
begin
     p_o_show := filename;
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     pov.incinit (p_o_show);
     run (f1,fl1,getreal(gtk_entry_get_text (pgtkentry(editredradius))));
     run (f2,fl2,getreal(gtk_entry_get_text (pgtkentry(editgreenradius))));
     run (f3,fl3,getreal(gtk_entry_get_text (pgtkentry(editblueradius))));
     pov.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

procedure proc_show_curvature; cdecl;
begin
     p_o_show := 'curvature.inc';
     _fileselection (p_o_show,@p_o_curvature);
end;

{ ******************************** Torsion *********************************** }

procedure p_o_torsion;
var pov : twritepov;
    r,g,b : vector;
    cursor : pgdkcursor;
function setcolor (c : extended) : vector;
var t,ll : extended;
    ra : range;
begin
     ra := liball.getrange (gtk_entry_get_text (pgtkentry(show_povray_range)));
     c := minmax (ra.min,ra.max,c,0,2);
     if c > 1 then
     begin
          ll := getlength(g-r);
          t := abs((1/c)/ll); if t > 1 then t := 1;
          setcolor := (maxnorm(r)*(1-t))+(maxnorm(g)*(t));
     end
     else if c = 1  then setcolor := maxnorm(g)
     else
     begin
          ll := getlength(g-b);
          t := abs(c/ll); if t > 1 then t := 1;
          setcolor := (maxnorm(b)*(1-t))+(maxnorm(g)*(t));
     end;
     setcolor := abs (setcolor);
     if setcolor.x > 1 then setcolor.x := 1;
     if setcolor.y > 1 then setcolor.y := 1;
     if setcolor.z > 1 then setcolor.z := 1;
end;
procedure run (f : tfilevector;fl : tpolynat;radius : extended);
var glob : string;
    v,u,color : vector;
    z,bl,l : longint;
    line : tpolyvector;
    linepoly : tpolynom3d;
    linefunc : tcurveproperty3d;
    factor,counter,c :extended;
begin
     glob := '';
     if f.length > 0 then
     begin
          for z := 1 to fl.length do
          begin
               if z <> fl.length then
               begin
                    l := fl.get(z+1)-fl.get(z);
                    v := f.get(fl.get(z)+((l-1) div 2));
               end
               else l := f.length-fl.get(z)+1;
               if l > 1 then
               begin
                    line.init (l);
                    for bl := 0 to l-1 do
                    begin
                         line.put (bl+1,f.get(fl.get(z)+bl));
                    end;
                    if l < 9 then
                    begin
                         linepoly.init (l);
                         linepoly.getpolynom (line);
                    end
                    else
                    begin
                         linepoly.init (9);
                         linepoly.getpolynom (line);
                    end;
                    linefunc.init (linepoly);
                    l := getnat(gtk_entry_get_text (pgtkentry(show_povray_resolution)));
                    if l < 10 then l := 10;
                    factor := linepoly.pathlength/l;
                    counter := 0;
                    r := getvector(gtk_entry_get_text (pgtkentry(editred)));
                    g := getvector(gtk_entry_get_text (pgtkentry(editgreen)));
                    b := getvector(gtk_entry_get_text (pgtkentry(editblue)));
                    for bl := 1 to l-1 do
                    begin
                         v := linepoly.polynom (counter);
                         c := linefunc.torsion (counter);
                         color := setcolor (c);
                         glob := glob + pov.sphere (v,radius,pov.pigment(color));
                         counter := counter + factor;
                         u := linepoly.polynom (counter);
                         c := (c+linefunc.torsion (counter))/2;
                         color := setcolor (c);
                         glob := glob + pov.cylinder (v,u,radius,pov.pigment(color));
                    end;
                    counter := counter + factor;
                    v := linepoly.polynom (counter);
                    c := linefunc.torsion (counter);
                    color := setcolor (c);
                    glob := glob + pov.sphere (u,radius,pov.pigment(color));
                    linefunc.done;
                    linepoly.done;
                    line.done;
               end;
          end;
          pov.write (pov.union(glob));
     end;
end;
begin
     p_o_show := filename;
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     pov.incinit (p_o_show);
     run (f1,fl1,getreal(gtk_entry_get_text (pgtkentry(editredradius))));
     run (f2,fl2,getreal(gtk_entry_get_text (pgtkentry(editgreenradius))));
     run (f3,fl3,getreal(gtk_entry_get_text (pgtkentry(editblueradius))));
     pov.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

procedure proc_show_torsion; cdecl;
begin
     p_o_show := 'torsion.inc';
     _fileselection (p_o_show,@p_o_torsion);
end;

{ **************************************************************************** }
{ ******************************** Report ************************************ }
{ **************************************************************************** }

procedure _make_visible (name,objects : string;var my1,my2,my3 : tpolyreal);
var s : string;
procedure run (n : string;my : tpolyreal);
var m : extended;
begin
     if my.length > 0 then
     begin
          s := s + n + ' '+name+' ->' + '   ';
          s := s + 'N: '+getstring(my.length)+#10;

          s := s + 'Average: '+getstring(my.average,10,5)+'   ';
          s := s + 'SD: '+getstring(my.sd,10,5)+'   ';
          s := s + 'Varianz: '+getstring(sqr(my.sd),10,5) + #10;

          s := s + 'Min: '+getstring(my.min,10,5)+'   ';
          m := my.length / 4;
          if system.trunc(m) = m then s := s + 'Q.25: '+getstring((my.get(my.length div 4)+my.get(my.length div 4+1))/2,10,5)+#10
                                 else s := s + 'Q.25: '+getstring(my.get(my.length div 4),10,5)+#10;

          if odd(my.length) then s := s + 'Median: '+getstring(my.get(my.length div 2 + 1),10,5)+#10
                            else s := s + 'Median: '+getstring((my.get(my.length div 2)+my.get(my.length div 2 + 1))/2,10,5)+#10;

          m := 3*(my.length / 4);
          if system.trunc(m) = m then s := s + 'Q.75: '+getstring((my.get(3*my.length div 4)+my.get(3*my.length div 4+1))/2,10,5)+'   '
                                 else s := s + 'Q.75: '+getstring(my.get(3*my.length div 4),10,5)+'   ';
          s := s + 'Max: '+getstring(my.max,10,5)+#10+#10;
     end;
end;
begin
     { Report }
     s := '';
     run ('Red',my3);
     run ('Green',my2);
     run ('Blue',my1);
     if s = '' then gtk_label_set_text (gtk_label(l_show_report),pchar('No data!'))
               else gtk_label_set_text (gtk_label(l_show_report),pchar(s));
     gdk_flush;
{ Graph }
     if gtk_toggle_button_get_active (gtk_toggle_button(togglegrouped)) then
     begin
          screen4.done;
          screen4.init (area4^.allocation.width,area4^.allocation.height);
          screen4.left('grouped '+objects);
          screen4.down(name+' [units]');
          screen4.grouped(my1,my2,my3,Vblue,Vgreen,Vred);
     end
     else
     begin
          screen4.done;
          screen4.init (area4^.allocation.width,area4^.allocation.height);
          screen4.left(name+' [units]');
          screen4.down('sorted '+objects);
          screen4.histogram(my1,my2,my3,Vblue,Vgreen,Vred);
     end;
     gtk_notebook_set_current_page (pgtknotebook(subnote4),1);
end;

procedure proc_show_pdistance; cdecl;
var my1,my2,my3 : tpolyreal;
    cursor : pgdkcursor;
procedure run (f : tfilevector;var my : tpolyreal);
var z,r,c : longint;
    d,n : extended;
begin
     if f.length > 0 then
     begin
          for z := 1 to f1.length do
          begin
               d := infinity;
               for c := 1 to (f1.length div 10) do
               begin
                    r := random(f.length)+1;
                    if r <> z then
                    begin
                         n := getlength((f.get (z)-f.get(r)));
                         if d > n then d := n;
                    end;
               end;
               my.put (my.length+1,d);
               progress ('Calculate neighbors (points)',z/f.length);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     my1.init;
     my2.init;
     my3.init;

     run (f1,my1);
     run (f2,my2);
     run (f3,my3);
     _make_visible ('point distances','points',my3,my2,my1);

     my3.done;
     my2.done;
     my1.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

{ *************************** Neighbor distances (lines) ********************* }

procedure proc_show_ldistance; cdecl;
var my1,my2,my3 : tpolyreal;
    cursor : pgdkcursor;
procedure run (f : tfilevector;fl : tpolynat;var my : tpolyreal);
var z,r,c,l,bl : longint;
    d,n : extended;
    my1 : tpolyreal;
begin
     if f.length > 0 then
     begin
          my1.init;
          for z := 1 to f1.length do
          begin
               d := infinity;
               for c := 1 to (f1.length div 10) do
               begin
                    r := random(f.length)+1;
                    if r <> z then
                    begin
                         n := getlength((f.get (z)-f.get(r)));
                         if d > n then d := n;
                    end;
               end;
               my1.put (my1.length+1,d);
               progress ('Calculate neighbors (points)',z/f.length);
          end;
          my.newlength (fl.length);
          for z := 1 to fl.length do
          begin
               if z <> fl.length then
               begin
                    l := fl.get(z+1)-fl.get(z);
               end
               else l := f.length-fl.get(z)+1;
               if l > 0 then
               begin
                    for bl := 0 to l-1 do
                    begin
                         my.put (z,my.get(z)+my1.get(fl.get(z)+bl));
                    end;
               end;
          end;
          my1.done;
          my.sort;
     end;
end;
begin
{ Neighbors }
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     my1.init;
     my2.init;
     my3.init;

     run (f1,fl1,my1);
     run (f2,fl2,my2);
     run (f3,fl3,my3);
     _make_visible ('line distances','lines',my3,my2,my1);

     my3.done;
     my2.done;
     my1.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;

{ *********************** Show length **************************************** }

procedure proc_show_llength; cdecl;
var my1,my2,my3 : tpolyreal;
    cursor : pgdkcursor;
procedure run (f : tfilevector;fl : tpolynat;var my : tpolyreal);
var z,l,bl : longint;
    rl : extended;
begin
     if f.length > 0 then
     begin
          for z := 1 to fl.length do
          begin
               if z <> fl.length then l := fl.get(z+1)-fl.get(z)
                                 else l := f.length-fl.get(z)+1;
               if l > 2 then { lines }
               begin
                    rl := 0;
                    for bl := fl.get(z) to fl.get(z)+l-2 do
                    begin
                         rl := rl + getlength(f.get (bl)-f.get (bl+1));
                    end;
                    my.put (my.length+1,rl);
               end
               else if l = 2 then  { vectors }
               begin
                    rl := getlength(f.get (fl.get(z))-f.get (fl.get(z)+1));
                    my.put (my.length+1,rl);
               end
               else my.put (my.length+1,0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
     cursor := gdk_cursor_new(GDK_WATCH);
     gdk_window_set_cursor (window^.window,cursor);
     gdk_flush;

     my1.init;
     my2.init;
     my3.init;

     run (f1,fl1,my1);
     run (f2,fl2,my2);
     run (f3,fl3,my3);
     _make_visible ('line lengths','lines',my3,my2,my1);

     my3.done;
     my2.done;
     my1.done;

     gdk_window_set_cursor (window^.window,nil);
     gdk_cursor_destroy (cursor);
end;
