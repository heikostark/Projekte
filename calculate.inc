{ **************************************************************************** }
{ ***************************** Calculate ************************************ }
{ **************************************************************************** }

procedure _help_getpolynom (o,l : integer;degree : byte;var linepoly : tpolynom4d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyhyper;
begin
     line := Default(tpolyhyper);

     len := finput^.getlinepointlength (o,l);
{ Filling }
     if finput^.getobject (o,l,1) <> finput^.getobject (o,l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,finput^.getobject (o,l,bl));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,finput^.getobject (o,l,len-1));
          first_len := getlength(finput^.getobject (o,l,len-1)-finput^.getobject (o,l,len));
          for bl := 1 to len do line.put (bl+1,finput^.getobject (o,l,bl));
          last_len := getlength (finput^.getobject (o,l,2)-finput^.getobject (o,l,1));
          line.put (len+2,finput^.getobject (o,l,2));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.getpolynom (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.getpolynom (line);
     end;

     line.done;
end;

procedure _help_getpolynom (l : integer;degree : byte;var linepoly : tpolynom4d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyhyper;
begin
     line := Default(tpolyhyper);

     len := finput^.getalllinepointlength(l);
{ Filling }
     if finput^.getline (l,1) <> finput^.getline (l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,finput^.getline (l,bl));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,finput^.getline (l,len-1));
          first_len := getlength(finput^.getline (l,len-1)-finput^.getline (l,len));
          for bl := 1 to len do line.put (bl+1,finput^.getline (l,bl));
          last_len := getlength (finput^.getline (l,2)-finput^.getline (l,1));
          line.put (len+2,finput^.getline (l,2));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.getpolynom (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.getpolynom (line);
     end;

     line.done;
end;

procedure _help_getpolynom_3d (l : integer;degree : byte;var linepoly : tpolynom3d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyvector;
begin
     line := Default(tpolyvector);

     len := finput^.getalllinepointlength(l);
{ Filling }
     if finput^.getline (l,1) <> finput^.getline (l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,htov(finput^.getline (l,bl)));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,htov(finput^.getline (l,len-1)));
          first_len := getlength(htov(finput^.getline (l,len-1))-htov(finput^.getline (l,len)));
          for bl := 1 to len do line.put (bl+1,htov(finput^.getline (l,bl)));
          last_len := getlength (htov(finput^.getline (l,2))-htov(finput^.getline (l,1)));
          line.put (len+2,htov(finput^.getline (l,2)));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.getpolynom (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.getpolynom (line);
     end;

     line.done;
end;

procedure _help_getfit (o,l : integer;degree : byte;var linepoly : tpolynom4d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyhyper;
begin
     line := Default(tpolyhyper);

     len := finput^.getlinepointlength (o,l);
{ Filling }
     if finput^.getobject (o,l,1) <> finput^.getobject (o,l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,finput^.getobject (o,l,bl));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,finput^.getobject (o,l,len-1));
          first_len := getlength(finput^.getobject (o,l,len-1)-finput^.getobject (o,l,len));
          for bl := 1 to len do line.put (bl+1,finput^.getobject (o,l,bl));
          last_len := getlength (finput^.getobject (o,l,2)-finput^.getobject (o,l,1));
          line.put (len+2,finput^.getobject (o,l,2));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.fit (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.fit (line);
     end;

     line.done;
end;

procedure _help_getfit (l : integer;degree : byte;var linepoly : tpolynom4d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyhyper;
begin
     line := Default(tpolyhyper);

     len := finput^.getalllinepointlength(l);
{ Filling }
     if finput^.getline (l,1) <> finput^.getline (l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,finput^.getline (l,bl));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,finput^.getline (l,len-1));
          first_len := getlength(finput^.getline (l,len-1)-finput^.getline (l,len));
          for bl := 1 to len do line.put (bl+1,finput^.getline (l,bl));
          last_len := getlength (finput^.getline (l,2)-finput^.getline (l,1));
          line.put (len+2,finput^.getline (l,2));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.fit (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.fit (line);
     end;

     line.done;
end;

procedure _help_getfit_3d (l : integer;degree : byte;var linepoly : tpolynom3d;var first_len,last_len : real);
var len,bl : integer;
    line : tpolyvector;
begin
     line := Default(tpolyvector);

     len := finput^.getalllinepointlength(l);
{ Filling }
     if finput^.getline (l,1) <> finput^.getline (l,len) then { no loop }
     begin
          line.init (len);
          first_len := 0;
          for bl := 1 to len do line.put (bl,htov(finput^.getline (l,bl)));
          last_len := 0;
     end
     else { loop }
     begin
          line.init (len+2);
          line.put (1,htov(finput^.getline (l,len-1)));
          first_len := getlength(htov(finput^.getline (l,len-1))-htov(finput^.getline (l,len)));
          for bl := 1 to len do line.put (bl+1,htov(finput^.getline (l,bl)));
          last_len := getlength (htov(finput^.getline (l,2))-htov(finput^.getline (l,1)));
          line.put (len+2,htov(finput^.getline (l,2)));
     end;
{ Fitting }
     if len < degree+1 then
     begin
          linepoly.init (len);
          linepoly.fit (line);
     end
     else
     begin
          linepoly.init (degree+1);
          linepoly.fit (line);
     end;

     line.done;
end;

{ **************************************************************************** }

procedure proc_center_point (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    center : hyper;
    c : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          center := Hzero; c := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   center := center + finput^.getobject(o,l,p);
                                   inc (c);
                              end;
                         end;
                    end;
               end;
          end;
          if c > 0 then center := finput^.searchallpoint(center/c);
          if center <> Hmin then
          begin
               dummy.newpoint (center);
               dummy.newline (0);
               dummy.newobject ('center_point');
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center.point');
     end;
end;

procedure proc_2_center_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    center : hyper;
    c : integer;
    points : tpolyhyper;
begin
     points := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          center := Hzero; c := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   center := center + finput^.getobject(o,l,p);
                                   inc (c);
                              end;
                         end;
                    end;
               end;
          end;
          if c > 0 then
          begin
               points.init (2);
               points := finput^.searchallpoints (center/c,2);
               if points.length > 0 then
               begin
                    for p := 1 to points.length do
                    begin
                         dummy.newpoint (points.get(p));
                         dummy.newline (0);
                    end;
                    dummy.newobject ('center_point');
               end;
               points.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.second.center.point');
     end;
end;

procedure proc_3_center_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    center : hyper;
    c : integer;
    points : tpolyhyper;
begin
     points := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          center := Hzero; c := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   center := center + finput^.getobject(o,l,p);
                                   inc (c);
                              end;
                         end;
                    end;
               end;
          end;
          if c > 0 then
          begin
               points.init (3);
               points := finput^.searchallpoints (center/c,3);
               if points.length > 0 then
               begin
                    for p := 1 to points.length do
                    begin
                         dummy.newpoint (points.get(p));
                         dummy.newline (0);
                    end;
                    dummy.newobject ('center_point');
               end;
               points.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.third.center.point');
     end;
end;

procedure proc_max_distance_points (p1,macro : gtk_pointer); cdecl;
var z,l,c : integer;
    d,n : real;
    my : tpolyreal;
    my1 : tpolynat;
begin
     my := Default(tpolyreal);
     my1 := Default(tpolynat);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          my.init (finput^.getpointlength);
          my1.init (finput^.getpointlength);
          l := 1;
          for z := 1 to finput^.getpointlength do
          begin
               if my.get (z) = 0 then { too avoid double calculations }
               begin
                    d := 0;
                    for c := 1 to finput^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((finput^.getpoint (z)-finput^.getpoint(c)));
                              if d < n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my.put (z,d);
                    my.put (l,d); { double calculation }
                    my1.put (z,l);
                    my1.put (l,z);
               end;
               progress ('Calculate neighbors (points)',z/finput^.getpointlength);
          end;
          progress;
          if my.max > 0 then
          begin
               l := my.maxpos;
               dummy.newpoint (finput^.getpoint (l));
               dummy.newpoint (finput^.getpoint (my1.get(l)));
               dummy.newline (0);
               dummy.newobject ('max_distance_point');
          end;
          cleanup (dummy);
          my1.done;
          my.done;
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.distance.point');
     end;
end;

procedure proc_max_n_distance_points (p1,macro : gtk_pointer); cdecl;
var z,l,c : integer;
    d,n,p : real;
    my : tpolyreal;
    help : tpolynat;
begin
     my := Default(tpolyreal);
     help := Default(tpolynat);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          p := _getreal(calculate_distance_points,macro,1);
          dummy.clear;
          my.init (finput^.getpointlength);
          l := 1;
          for z := 1 to finput^.getpointlength do
          begin
               d := 0;
               if my.get (z) = 0 then { too avoid double calculations }
               begin
                    for c := 1 to finput^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((finput^.getpoint (z)-finput^.getpoint(c)));
                              if d < n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my.put (z,d);
                    my.put (l,d); { double calculation }
                    progress ('Calculate neighbors (points)',z/finput^.getpointlength);
               end;
          end;
          my.sorthelp (help);
          help.flip;
          progress;
          if into (p/100,0,1) then
          begin
               c := round(finput^.getpointlength*p/100);
               if (my.max > 0) and (c > 0) then
               begin
                    for z := 1 to c do
                    begin
                         dummy.newpoint (finput^.getpoint (help.get(z)));
                         dummy.newline (0);
                    end;
                    dummy.newobject ('max_distance_point');
               end;
          end;
          cleanup (dummy);
          help.done;
          my.done;
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.distance.point',getstring(p));
     end;
end;

{ *************************** Calculate between ****************************** }

procedure proc_sum_between (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then dummy.newpoint(finput^.getobject(o,l,p)+finputedit^.getpoint(pe));
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sum.between');
     end;
end;

procedure proc_sum_between_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x+finputedit^.getpoint(pe).x,h.y,h.z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sum.between.x');
     end;
end;

procedure proc_sum_between_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y+finputedit^.getpoint(pe).y,h.z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sum.between.y');
     end;
end;

procedure proc_sum_between_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y,h.z+finputedit^.getpoint(pe).z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sum.between.z');
     end;
end;

procedure proc_sum_between_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y,h.z,h.t+finputedit^.getpoint(pe).t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sum.between.t');
     end;
end;

{ **** }

procedure proc_diff_between (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then dummy.newpoint(finput^.getobject(o,l,p)-finputedit^.getpoint(pe));
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.diff.between');
     end;
end;

procedure proc_diff_between_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x-finputedit^.getpoint(pe).x,h.y,h.z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.diff.between.x');
     end;
end;

procedure proc_diff_between_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y-finputedit^.getpoint(pe).y,h.z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.diff.between.y');
     end;
end;

procedure proc_diff_between_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y,h.z-finputedit^.getpoint(pe).z,h.t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.diff.between.z');
     end;
end;

procedure proc_diff_between_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,pe : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   pe := finput^.getpobject(o,l,p);
                                   if pe <= finputedit^.getpointlength then
                                   begin
                                        h := finput^.getobject(o,l,p);
                                        dummy.newpoint(gh(h.x,h.y,h.z,h.t-finputedit^.getpoint(pe).t));
                                   end;
                              end;
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject(finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.diff.between.t');
     end;
end;

{ ************************** Calculate to vectors **************************** }
{ +Calculate }
procedure proc_make_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (Hzero);
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.points.to.vectors');
     end;
end;

procedure proc_make_vectors_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              dummy.newpoint (finput^.getobject (o,l,p));
                              dummy.newpoint (finput^.getobject (o,l,p+1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.lines.to.vectors');
     end;
end;

{ *************************** To string vectors ****************************** }
{ +Calculate }
procedure proc_string_x_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_vectors,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (gh(count,0,0,0));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.x.vectors',getstring(raster));
     end;
end;

procedure proc_string_y_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_vectors,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (gh(0,count,0,0));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.y.vectors',getstring(raster));
     end;
end;

procedure proc_string_z_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_vectors,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (gh(0,0,count,0));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.z.vectors',getstring(raster));
     end;
end;

procedure proc_string_t_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_vectors,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (gh(0,0,0,count));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.t.vectors',getstring(raster));
     end;
end;

{ *************************** To string lines ******************************** }
{ +Calculate }
procedure proc_string_x_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_points,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(count,v.y,v.z,v.t));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.point.x',getstring(raster));
     end;
end;

procedure proc_string_y_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_points,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,count,v.z,v.t));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.point.y',getstring(raster));
     end;
end;

procedure proc_string_z_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_points,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,count,v.t));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.point.z',getstring(raster));
     end;
end;

procedure proc_string_t_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_points,macro,1);
          count := -1*(finput^.getpointlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,v.z,count));
                                   count := count + raster;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.point.t',getstring(raster));
     end;
end;


{ +Calculate }
procedure proc_string_x_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_lines,macro,1);
          count := -1*(finput^.getlinelength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(count,v.y,v.z,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                         count := count + raster;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.line.x',getstring(raster));
     end;
end;

procedure proc_string_y_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_lines,macro,1);
          count := -1*(finput^.getlinelength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,count,v.z,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                         count := count + raster;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.line.y',getstring(raster));
     end;
end;

procedure proc_string_z_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_lines,macro,1);
          count := -1*(finput^.getlinelength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,count,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                         count := count + raster;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.line.z',getstring(raster));
     end;
end;

procedure proc_string_t_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_lines,macro,1);
          count := -1*(finput^.getlinelength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,v.z,count));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                         count := count + raster;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.line.t',getstring(raster));
     end;
end;

{ +Calculate }
procedure proc_string_x_objects (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_objects,macro,1);
          count := -1*(finput^.getobjectlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(count,v.y,v.z,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               count := count + raster;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.object.x',getstring(raster));
     end;
end;

procedure proc_string_y_objects (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_objects,macro,1);
          count := -1*(finput^.getobjectlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,count,v.z,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               count := count + raster;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.object.y',getstring(raster));
     end;
end;

procedure proc_string_z_objects (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_objects,macro,1);
          count := -1*(finput^.getobjectlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,count,v.t));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               count := count + raster;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.object.z',getstring(raster));
     end;
end;

procedure proc_string_t_objects (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    raster,count : real;
    v : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          raster := _getreal(calculate_axis_raster_objects,macro,1);
          count := -1*(finput^.getobjectlength*raster)/2;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(v.x,v.y,v.z,count));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               count := count + raster;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.relative.object.t',getstring(raster));
     end;
end;

{ *************************** Calculate to lines ***************************** }
{ +CALCULATE }
procedure proc_make_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v,w : hyper;
begin
     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               for o := 1 to finput^.getobjectlength do
               begin
                    c := 0;
                    u := Hzero;
                    v := Hzero;
                    w := Hzero;
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              inc (c);
                              if c = 1 then
                              begin
                                   u := finput^.getobject (o,l,p);
                                   dummy.newpoint (u);
                              end
                              else if c = 2 then
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (v);
                              end
                              else if c > 2 then
                              begin
                                   w := finput^.getobject (o,l,p);
                                   if 2*getlength(u-v) < getlength(v-w) then dummy.newline (finput^.getmaterial (o,l));
                                   dummy.newpoint (w);
                                   u := v;
                                   v := w;
                              end;
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.step');
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_direction (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v,w : hyper;
begin
     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               for o := 1 to finput^.getobjectlength do
               begin
                    c := 0;
                    u := Hzero;
                    v := Hzero;
                    w := Hzero;
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              inc (c);
                              if c = 1 then
                              begin
                                   u := finput^.getobject (o,l,p);
                                   dummy.newpoint (u);
                              end
                              else if c = 2 then
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (v);
                              end
                              else if c > 2 then
                              begin
                                   w := finput^.getobject (o,l,p);
                                   if inv((u-v),(v-w)) then dummy.newline (finput^.getmaterial (o,l));
                                   dummy.newpoint (w);
                                   u := v;
                                   v := w;
                              end;
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.direction');
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_value (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    value1,w : hyper;
begin
     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               value1 := _gethyper (calculate_lines_by_value,macro,1);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              w := finput^.getobject (o,l,p);
                              if w = value1 then dummy.newline (finput^.getmaterial (o,l))
                                            else dummy.newpoint (w);
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.value',getstring(value1));
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_spacing (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,w : hyper;
    spacing : real;
begin
     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               spacing := _getreal (calculate_lines_by_spacing,macro,1);
               for o := 1 to finput^.getobjectlength do
               begin
                    c := 0;
                    u := Hzero;
                    w := Hzero;
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              inc (c);
                              if c = 1 then
                              begin
                                   u := finput^.getobject (o,l,p);
                                   dummy.newpoint (u);
                              end
                              else if c > 1 then
                              begin
                                   w := finput^.getobject (o,l,p);
                                   if getlength(w-u) > spacing then dummy.newline (finput^.getmaterial (o,l));
                                   dummy.newpoint (w);
                                   u := w;
                              end;
                          end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.spacing',getstring(spacing));
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_angle (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v,w : hyper;
    radian : real;
begin
     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               if format.degree then radian := _getreal (calculate_lines_by_angle,macro,1)*rad { input into radian }
                                else radian := _getreal (calculate_lines_by_angle,macro,1);
               for o := 1 to finput^.getobjectlength do
               begin
                    c := 0;
                    u := Hzero;
                    v := Hzero;
                    w := Hzero;
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              inc (c);
                              if c = 1 then
                              begin
                                   u := finput^.getobject (o,l,p);
                                   dummy.newpoint (u);
                              end
                              else if c = 2 then
                              begin
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (v);
                              end
                              else if c > 2 then
                              begin
                                   w := finput^.getobject (o,l,p);
                                   if getangle ((v-u),(v-w)) < radian then
                                   begin
                                        dummy.newline (finput^.getmaterial (o,l));
                                        dummy.newpoint (w);
                                        u := w;
                                        c := 1;
                                   end
                                   else
                                   begin
                                        dummy.newpoint (w);
                                        u := v;
                                        v := w;
                                   end;
                              end;
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               if format.degree then tmacro(macro^).writeredo ('calculate.split.lines.by.angle',getstring(radian*deg))
                                else tmacro(macro^).writeredo ('calculate.split.lines.by.angle',getstring(radian));
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_curvature (p1,macro : gtk_pointer); cdecl;
var o,l,c,len : integer;
    dk,r,curvature : real;
    p,pd,pdd : tpolyvector;
begin
     p := Default (tpolyvector);
     pd := Default (tpolyvector);
     pdd := Default (tpolyvector);

     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               curvature := _getreal (calculate_lines_by_curvature,macro,1);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         len := finput^.getlinepointlength (o,l);
                         p.init (len);
                         pd.init;
                         pdd.init;
                         if len > 0 then
                         begin
                              for c := 1 to len do p.put (c,htov(finput^.getobject (o,l,c)));
                              p.derivation(pd);
                              pd.derivation(pdd);
                              { |v' x v''| / |v'|³ }
                              for c := 1 to len do
                              begin
                                   dk := power (getlength( pd.get(c) ),3);
                                   if dk <> 0.0 then r := getlength(cross( pd.get(c),pdd.get(c) )) / dk
                                                else r := 0;
                                   if r > curvature then { split }
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,c));
                                        if c <> len then dummy.newline (finput^.getmaterial (o,l));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,c));
                              end;
                         end;
                         pdd.done;
                         pd.done;
                         p.done;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.curvature',getstring(curvature));
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

procedure proc_make_lines_by_torsion (p1,macro : gtk_pointer); cdecl;
var o,l,c,len : integer;
    dt,r,torsion : real;
    p,pd,pdd,pddd : tpolyvector;
begin
     p := Default (tpolyvector);
     pd := Default (tpolyvector);
     pdd := Default (tpolyvector);
     pddd := Default (tpolyvector);

     if finput^.getpointlength > 2 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               torsion := _getreal (calculate_lines_by_torsion,macro,1);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         len := finput^.getlinepointlength (o,l);
                         p.init (len);
                         pd.init;
                         pdd.init;
                         pddd.init;
                         if len > 0 then
                         begin
                              for c := 1 to len do p.put (c,htov(finput^.getobject (o,l,c)));
                              p.derivation(pd);
                              pd.derivation(pdd);
                              pdd.derivation(pddd);
                              { det(v',v'',v''') / |v' x v''|³ }
                              for c := 1 to len do
                              begin
                                   dt := sqr (getlength(cross( pd.get(c),pdd.get(c) )));
                                   if dt <> 0.0 then r := getlength(det ( pd.get(c),pdd.get(c),pddd.get(c) )) / dt
                                                else r := 0;
                                   if r > torsion then { split }
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,c));
                                        if c <> len then dummy.newline (finput^.getmaterial (o,l));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,c));
                              end;
                         end;
                         pddd.done;
                         pdd.done;
                         pd.done;
                         p.done;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.split.lines.by.torsion',getstring(torsion));
          end;
     end
     else proc_objects_to_one_line (p1,macro);
end;

{ **************************************************************************** }

procedure proc_group_lines_by_angle_mean (p1,macro : gtk_pointer); cdecl;
var l,p,oc,lc,c,w : integer;
    v,u : hyper;
    angle1 : real;
    lines : tpolynat;
begin
     lines := Default(tpolynat);

     if finput^.getpointlength > 1 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               angle1 := _getreal (calculate_group_lines_angle,macro,1);
               if angle1 <> 0 then oc := round(360/angle1) else oc := 0;
{ Calcaulte mean }
               u := Hzero;
               if finput^.getlinelength > 0 then
                  for l := 1 to finput^.getlinelength do
                  begin
                       if finput^.getalllinepointlength (l) > 1 then
                          for p := 1 to finput^.getalllinepointlength (l)-1 do
                          begin
                               u := u + (finput^.getline(l,p+1)-finput^.getline(l,p))
                          end;
                  end;
               u := norm (u);
 { Calculate angles }
               if oc > 0 then
               begin
                    lines.init (finput^.getlinelength);
                    if finput^.getlinelength > 0 then
                       for l := 1 to finput^.getlinelength do
                       begin
                            v := Hzero;
                            if finput^.getalllinepointlength (l) > 1 then
                               for p := 1 to finput^.getalllinepointlength (l)-1 do
                               begin
                                    v := v + (finput^.getline(l,p+1)-finput^.getline(l,p))
                               end;
                            w := round(minmax(0,pi,getangle(v,u),1,oc));
                            lines.put (l,w);
                       end;
               end;
{ Split lines }
               for c := 1 to oc do
               begin
                    lc := 0;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if lines.get (l) = c then
                           if finput^.getalllinepointlength (l) > 0 then
                           begin
                                for p := 1 to finput^.getalllinepointlength (l) do
                                begin
                                     dummy.newpoint (finput^.getline (l,p));
                                end;
                                dummy.newline (finput^.getallmaterial(l));
                                inc (lc);
                           end;
                    end;
                    if lc > 0 then dummy.newobject ('split_'+getstring(c));
               end;
               lines.done;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.group.lines.by.angle.mean',getstring(angle1));
          end;
     end;
end;

procedure proc_group_lines_by_angle (p1,macro : gtk_pointer); cdecl;
var l,p,oc,lc,c,w : integer;
    v,u : hyper;
    angle1 : real;
    lines : tpolynat;
begin
     lines := Default(tpolynat);

     if finput^.getpointlength > 1 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               angle1 := _getreal (calculate_group_lines_angle,macro,1);
               u := _gethyper (calculate_group_lines_vector,macro,2);
               if angle1 <> 0 then oc := round(360/angle1) else oc := 0;
{ Calculate angles }
               if oc > 0 then
               begin
                    lines.init (finput^.getlinelength);
                    if finput^.getlinelength > 0 then
                       for l := 1 to finput^.getlinelength do
                       begin
                            v := Hzero;
                            if finput^.getalllinepointlength (l) > 1 then
                               for p := 1 to finput^.getalllinepointlength (l)-1 do
                               begin
                                    v := v + (finput^.getline(l,p+1)-finput^.getline(l,p))
                               end;
                            w := round(minmax(0,pi,getangle(v,u),1,oc));
                            lines.put (l,w);
                       end;
               end;
{ Split lines }
               for c := 1 to oc do
               begin
                    lc := 0;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if lines.get (l) = c then
                           if finput^.getalllinepointlength (l) > 0 then
                           begin
                                for p := 1 to finput^.getalllinepointlength (l) do
                                begin
                                     dummy.newpoint (finput^.getline (l,p));
                                end;
                                dummy.newline (finput^.getallmaterial(l));
                                inc (lc);
                           end;
                    end;
                    if lc > 0 then dummy.newobject ('split_'+getstring(c));
               end;
               lines.done;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.group.lines.by.angle',getstring(angle1)+' '+getstring(u));
          end;
     end;
end;

procedure proc_group_lines_by_angle_xy (p1,macro : gtk_pointer); cdecl;
var l,p,oc,lc,c,w : integer;
    v : hyper;
    angle1 : real;
    lines : tpolynat;
begin
     lines := Default(tpolynat);

     if finput^.getpointlength > 1 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               angle1 := _getreal (calculate_group_lines_angle,macro,1);
               if angle1 <> 0 then oc := round(360/angle1) else oc := 0;
{ Calculate angles }
               if oc > 0 then
               begin
                    lines.init (finput^.getlinelength);
                    if finput^.getlinelength > 0 then
                       for l := 1 to finput^.getlinelength do
                       begin
                            v := Hzero;
                            if finput^.getalllinepointlength (l) > 1 then
                               for p := 1 to finput^.getalllinepointlength (l)-1 do
                               begin
                                    v := v + (finput^.getline(l,p+1)-finput^.getline(l,p))
                               end;
                            w := round(minmax(0,2*pi,fullangle(v,Hright,Hup),1,oc));
                            lines.put (l,w);
                       end;
               end;
{ Split lines }
               for c := 1 to oc do
               begin
                    lc := 0;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if lines.get (l) = c then
                           if finput^.getalllinepointlength (l) > 0 then
                           begin
                                for p := 1 to finput^.getalllinepointlength (l) do
                                begin
                                     dummy.newpoint (finput^.getline (l,p));
                                end;
                                dummy.newline (finput^.getallmaterial(l));
                                inc (lc);
                           end;
                    end;
                    if lc > 0 then dummy.newobject ('split_'+getstring(c));
               end;
               lines.done;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.group.lines.by.angle.xy',getstring(angle1));
          end;
     end;
end;

procedure proc_group_lines_by_angle_yz (p1,macro : gtk_pointer); cdecl;
var l,p,oc,lc,c,w : integer;
    v : hyper;
    angle1 : real;
    lines : tpolynat;
begin
     lines := Default(tpolynat);

     if finput^.getpointlength > 1 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               angle1 := _getreal (calculate_group_lines_angle,macro,1);
               if angle1 <> 0 then oc := round(360/angle1) else oc := 0;
{ Calculate angles }
               if oc > 0 then
               begin
                    lines.init (finput^.getlinelength);
                    if finput^.getlinelength > 0 then
                       for l := 1 to finput^.getlinelength do
                       begin
                            v := Hzero;
                            if finput^.getalllinepointlength (l) > 1 then
                               for p := 1 to finput^.getalllinepointlength (l)-1 do
                               begin
                                    v := v + (finput^.getline(l,p+1)-finput^.getline(l,p))
                               end;
                            w := round(minmax(0,2*pi,fullangle(v,Hup,Hfar),1,oc));
                            lines.put (l,w);
                       end;
               end;
{ Split lines }
               for c := 1 to oc do
               begin
                    lc := 0;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if lines.get (l) = c then
                           if finput^.getalllinepointlength (l) > 0 then
                           begin
                                for p := 1 to finput^.getalllinepointlength (l) do
                                begin
                                     dummy.newpoint (finput^.getline (l,p));
                                end;
                                dummy.newline (finput^.getallmaterial(l));
                                inc (lc);
                           end;
                    end;
                    if lc > 0 then dummy.newobject ('split_'+getstring(c));
               end;
               lines.done;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.group.lines.by.angle.yz',getstring(angle1));
          end;
     end;
end;

procedure proc_group_lines_by_angle_xz (p1,macro : gtk_pointer); cdecl;
var l,p,oc,lc,c,w : integer;
    v : hyper;
    angle1 : real;
    lines : tpolynat;
begin
     lines := Default(tpolynat);

     if finput^.getpointlength > 1 then
     begin
          if finput^.getobjectlength > 0 then
          begin
               _cursor_watch;
               dummy.clear;
               angle1 := _getreal (calculate_group_lines_angle,macro,1);
               if angle1 <> 0 then oc := round(360/angle1) else oc := 0;
{ Calculate angles }
               if oc > 0 then
               begin
                    lines.init (finput^.getlinelength);
                    if finput^.getlinelength > 0 then
                       for l := 1 to finput^.getlinelength do
                       begin
                            v := Hzero;
                            if finput^.getalllinepointlength (l) > 1 then
                               for p := 1 to finput^.getalllinepointlength (l)-1 do
                               begin
                                    v := v + (finput^.getline(l,p+1)-finput^.getline(l,p))
                               end;
                            w := round(minmax(0,2*pi,fullangle(v,Hright,Hfar),1,oc));
                            lines.put (l,w);
                       end;
               end;
{ Split lines }
               for c := 1 to oc do
               begin
                    lc := 0;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if lines.get (l) = c then
                           if finput^.getalllinepointlength (l) > 0 then
                           begin
                                for p := 1 to finput^.getalllinepointlength (l) do
                                begin
                                     dummy.newpoint (finput^.getline (l,p));
                                end;
                                dummy.newline (finput^.getallmaterial(l));
                                inc (lc);
                           end;
                    end;
                    if lc > 0 then dummy.newobject ('split_'+getstring(c));
               end;
               lines.done;
               cleanup (dummy);
               _cursor_arrow;
               tmacro(macro^).writeredo ('calculate.group.lines.by.angle.xz',getstring(angle1));
          end;
     end;
end;

{ **************************************************************************** }
{ +CALCULATE }
procedure proc_smooth_lines_angle (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    first_u,last_u,u,v,w : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    radian : real;
    line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter :real;
begin
     line := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     if format.degree then radian := _getreal(calculate_smooth_lines_radian,macro,2)*rad { input into radian }
                      else radian := _getreal(calculate_smooth_lines_radian,macro,2);
     step := 99;
     if (radian > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              _help_getpolynom (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                              begin
                                   factor := linepoly.pathlength/(step-1);
                                   counter := 0;
                                   u := linepoly.polynom (counter);
                                   last_u := u;
                                   dummy.newpoint (u);
                                   counter := counter + factor;
                                   v := linepoly.polynom (counter);
                                   w := Hzero;
                                   for bl := 1+1 to step-1 do
                                   begin
                                        counter := counter + factor;
                                        w := linepoly.polynom (counter);
                                        if getangle (v-last_u,w-v) > radian then
                                        begin
                                             dummy.newpoint (v);
                                             last_u := v;
                                        end;
                                        u := v;
                                        v := w;
                                   end;
                                   dummy.newpoint (w);
                              end
                              else
                              begin
                                   factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                   counter := first_len; { ignore first }
                                   u := linepoly.polynom (counter);
                                   first_u := u;
                                   last_u := u;
                                   dummy.newpoint (u);
                                   counter := counter + factor;
                                   v := linepoly.polynom (counter);
                                   for bl := 1+1 to step-1 do
                                   begin
                                        counter := counter + factor;
                                        w := linepoly.polynom (counter);
                                        if getangle (v-last_u,w-v) > radian then
                                        begin
                                             dummy.newpoint (v);
                                             last_u := v;
                                        end;
                                        u := v;
                                        v := w;
                                   end;
                                   dummy.newpoint (first_u); { go to first point }
                              end;
                              linepoly.done;
                              line.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          if format.degree then tmacro(macro^).writeredo ('calculate.smooth.lines.degree',getstring(method)+' '+getstring(radian*deg))
                           else tmacro(macro^).writeredo ('calculate.smooth.lines.degree',getstring(method)+' '+getstring(radian));
     end;
end;

procedure proc_smooth_lines_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter :real;
begin
     line := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     step := _getnat(calculate_smooth_lines_points,macro,2);
     if (step > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              _help_getpolynom (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              if step > 2 then
                              begin
                                   if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                   begin
                                        factor := linepoly.pathlength/(step-1);
                                        counter := 0;
                                        for bl := 1 to step do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                   end
                                   else
                                   begin
                                        factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                        counter := first_len; { ignore first }
                                        u := linepoly.polynom (counter);
                                        for bl := 1 to step-1 do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                        dummy.newpoint (u); { go to first point }
                                   end;
                              end
                              else if step = 2 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end
                              else if step = 1 then
                              begin
                                   dummy.newpoint ((finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2);
                              end;
                              linepoly.done;
                              line.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smooth.lines.points',getstring(method)+' '+getstring(step));
     end;
end;

procedure proc_smooth_lines_steps (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter,steps :real;
begin
     line := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     steps := _getreal(calculate_smooth_lines_steps,macro,2);
     if (steps > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              _help_getpolynom (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              step := round(linepoly.pathlength/steps)+1;
                              if step > 2 then
                              begin
                                   if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                   begin
                                        factor := linepoly.pathlength/(step-1);
                                        counter := 0;
                                        for bl := 1 to step do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                   end
                                   else
                                   begin
                                        factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                        counter := first_len; { ignore first }
                                        u := linepoly.polynom (counter);
                                        for bl := 1 to step-1 do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                        dummy.newpoint (u); { go to first point }
                                   end;
                              end
                              else if step = 2 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end
                              else if step = 1 then
                              begin
                                   dummy.newpoint ((finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2);
                              end;
                              linepoly.done;
                              line.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smooth.lines.steps',getstring(method)+' '+getstring(steps));
     end;
end;

procedure proc_smooth_lines_steps_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,ui : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    linepoly : tpolynom4d;
    factor,counter,steps,min,max,save,value : real;
begin
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     steps := _getreal(calculate_smooth_lines_steps_x,macro,2);
     if (steps > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              _help_getpolynom (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              min := round(finput^.getobject (o,l,1).x/steps)*steps;
                              max := round(finput^.getobject (o,l,p).x/steps)*steps;

                              step := round((max-min)/steps);
                              if abs(step) > 2 then
                              begin
                                   step := round(linepoly.pathlength/(steps*0.1))+1;
                                   if step > 0 then
                                   begin
                                        if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                        begin
                                             factor := linepoly.pathlength/(step-1);
                                             counter := 0;
                                             save := infinity;
                                             u := Hzero;
                                             ui := 0;
                                             for bl := 1 to step do
                                             begin
                                                  v := linepoly.polynom (counter);
                                                  counter := counter + factor;
                                                  value := round(v.x/steps)*steps;
                                                  if (save <> value) and (ui > 0) then
                                                  begin
                                                       u := u/ui;
                                                       dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                                       save := value;
                                                       u := Hzero;
                                                       ui := 0;
                                                  end;
                                                  u := u + gh(value,v.y,v.z,v.t);
                                                  inc (ui);
                                             end;
                                             if (ui > 0) then
                                             begin
                                                  u := u/ui;
                                                  dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                             end;
                                        end
                                        else
                                        begin
                                             factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                             counter := first_len;
                                             save := infinity;
                                             u := Hzero;
                                             ui := 0;
                                             for bl := 1 to step-1 do
                                             begin
                                                  v := linepoly.polynom (counter);
                                                  counter := counter + factor;
                                                  value := round(v.x/steps)*steps;
                                                  if (save <> value) and (ui > 0) then
                                                  begin
                                                       u := u/ui;
                                                       dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                                       save := value;
                                                       u := Hzero;
                                                       ui := 0;
                                                  end;
                                                  u := u + gh(value,v.y,v.z,v.t);
                                                  inc (ui);
                                             end;
                                             if (ui > 0) then
                                             begin
                                                  u := u/ui;
                                                  dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                             end;
                                        end;
                                   end;
                              end
                              else if abs(step) = 2 then
                              begin
                                   v := finput^.getobject (o,l,1);
                                   dummy.newpoint (gh(min,v.y,v.z,v.t));
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(max,v.y,v.z,v.t));
                              end
                              else if abs(step) = 1 then
                              begin
                                   v := (finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2;
                                   dummy.newpoint (gh(round(v.x/steps)*steps,v.y,v.z,v.t));
                              end;

                              linepoly.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              v := finput^.getobject (o,l,1);
                              dummy.newpoint (gh(round(v.x/steps)*steps,v.y,v.z,v.t));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smooth.lines.steps.x',getstring(method)+' '+getstring(steps));
     end;
end;

{ **************************************************************************** }

procedure proc_lines_interpolate (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v,u : hyper;
    bl : integer;
begin
     if (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              v := finput^.getobject (o,l,1);
                              for bl := 1 to p-1 do
                              begin
                                   dummy.newpoint (v);
                                   u := finput^.getobject (o,l,bl+1);
                                   dummy.newpoint ((v+u)/2);
                                   v := u;
                              end;
                              dummy.newpoint (finput^.getobject (o,l,p));
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              v := finput^.getobject (o,l,1);
                              dummy.newpoint (v);
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.lines.interpolate');
     end;
end;

{ **************************************************************************** }

{ +CALCULATE }
procedure proc_fit_lines_angle (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    first_u,last_u,u,v,w : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    radian : real;
    linepoly : tpolynom4d;
    factor,counter :real;
begin
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     if format.degree then radian := _getreal(calculate_smooth_lines_radian,macro,2)*rad { input to radian }
                      else radian := _getreal(calculate_smooth_lines_radian,macro,2);
     step := 99;
     if (radian > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if (p > 1) then
                         begin
                              _help_getfit (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                              begin
                                   factor := linepoly.pathlength/(step-1);
                                   counter := 0;
                                   u := linepoly.polynom (counter);
                                   last_u := u;
                                   dummy.newpoint (u);
                                   counter := counter + factor;
                                   v := linepoly.polynom (counter);
                                   w := Hzero;
                                   for bl := 1+1 to step-1 do
                                   begin
                                        counter := counter + factor;
                                        w := linepoly.polynom (counter);
                                        if getangle (v-last_u,w-v) > radian then
                                        begin
                                             dummy.newpoint (v);
                                             last_u := v;
                                        end;
                                        u := v;
                                        v := w;
                                   end;
                                   dummy.newpoint (w);
                              end
                              else
                              begin
                                   factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                   counter := first_len; { ignore first }
                                   u := linepoly.polynom (counter);
                                   first_u := u;
                                   last_u := u;
                                   dummy.newpoint (u);
                                   counter := counter + factor;
                                   v := linepoly.polynom (counter);
                                   for bl := 1+1 to step-1 do
                                   begin
                                        counter := counter + factor;
                                        w := linepoly.polynom (counter);
                                        if getangle (v-last_u,w-v) > radian then
                                        begin
                                             dummy.newpoint (v);
                                             last_u := v;
                                        end;
                                        u := v;
                                        v := w;
                                   end;
                                   dummy.newpoint (first_u); { go to first point }
                              end;
                              linepoly.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          if format.degree then tmacro(macro^).writeredo ('calculate.fit.lines.angle',getstring(method)+' '+getstring(radian*deg))
                           else tmacro(macro^).writeredo ('calculate.fit.lines.angle',getstring(method)+' '+getstring(radian));
     end;
end;

procedure proc_fit_lines_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    linepoly : tpolynom4d;
    factor,counter :real;
begin
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     step := _getnat(calculate_smooth_lines_points,macro,2);
     if (step > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if (p > 1) then
                         begin
                              _help_getfit (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              if step > 2 then
                              begin
                                   if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                   begin
                                        factor := linepoly.pathlength/(step-1);
                                        counter := 0;
                                        for bl := 1 to step do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                   end
                                   else
                                   begin
                                        factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                        counter := first_len; { ignore first }
                                        u := linepoly.polynom (counter);
                                        for bl := 1 to step-1 do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                        dummy.newpoint (u); { go to first point }
                                   end;
                              end
                              else if step = 2 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end
                              else if step = 1 then
                              begin
                                   dummy.newpoint ((finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2);
                              end;
                              linepoly.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.fit.lines.points',getstring(method)+' '+getstring(step));
     end;
end;

procedure proc_fit_lines_steps (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    linepoly : tpolynom4d;
    factor,counter,steps :real;
begin
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     steps := _getreal(calculate_smooth_lines_steps,macro,2);
     if (steps > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if  p > 1 then
                         begin
                              _help_getfit (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              step := round(linepoly.pathlength/steps)+1;
                              if step > 2 then
                              begin
                                   if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                   begin
                                        factor := linepoly.pathlength/(step-1);
                                        counter := 0;
                                        for bl := 1 to step do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                   end
                                   else
                                   begin
                                        factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                        counter := first_len; { ignore first }
                                        u := linepoly.polynom (counter);
                                        for bl := 1 to step-1 do
                                        begin
                                             v := linepoly.polynom (counter);
                                             dummy.newpoint (v);
                                             counter := counter + factor;
                                        end;
                                        dummy.newpoint (u); { go to first point }
                                   end;
                              end
                              else if step = 2 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end
                              else if step = 1 then
                              begin
                                   dummy.newpoint ((finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2);
                              end;
                              linepoly.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.fit.lines.steps',getstring(method)+' '+getstring(steps));
     end;
end;

procedure proc_fit_lines_steps_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,ui : integer;
    u,v : hyper;
    first_len,last_len : real;
    bl,method,step : integer;
    linepoly : tpolynom4d;
    factor,counter,steps,min,max,save,value : real;
begin
     linepoly := Default(tpolynom4d);

     method := _getitem(calculate_polynom_method,macro,1);
     steps := _getreal(calculate_smooth_lines_steps_x,macro,2);
     if (steps > 0) and (finput^.getobjectlength > 0) then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if (p > 1) then
                         begin
                              _help_getfit (o,l,method,linepoly,first_len,last_len); { get the polynom }

                              min := round(finput^.getobject (o,l,1).x/steps)*steps;
                              max := round(finput^.getobject (o,l,p).x/steps)*steps;

                              step := round((max-min)/steps);
                              if abs(step) > 2 then
                              begin
                                   step := round(linepoly.pathlength/(steps*0.1))+1;
                                   if step > 0 then
                                   begin
                                        if finput^.getobject (o,l,1) <> finput^.getobject (o,l,p) then { no loop }
                                        begin
                                             factor := linepoly.pathlength/(step-1);
                                             counter := 0;
                                             save := infinity;
                                             u := Hzero;
                                             ui := 0;
                                             for bl := 1 to step do
                                             begin
                                                  v := linepoly.polynom (counter);
                                                  counter := counter + factor;
                                                  value := round(v.x/steps)*steps;
                                                  if (save <> value) and (ui > 0) then
                                                  begin
                                                       u := u/ui;
                                                       dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                                       save := value;
                                                       u := Hzero;
                                                       ui := 0;
                                                  end;
                                                  u := u + gh(value,v.y,v.z,v.t);
                                                  inc (ui);
                                             end;
                                             if (ui > 0) then
                                             begin
                                                  u := u/ui;
                                                  dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                             end;
                                        end
                                        else
                                        begin
                                             factor := (linepoly.pathlength-first_len-last_len)/(step-1);
                                             counter := first_len;
                                             save := infinity;
                                             u := Hzero;
                                             ui := 0;
                                             for bl := 1 to step-1 do
                                             begin
                                                  v := linepoly.polynom (counter);
                                                  counter := counter + factor;
                                                  value := round(v.x/steps)*steps;
                                                  if (save <> value) and (ui > 0) then
                                                  begin
                                                       u := u/ui;
                                                       dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                                       save := value;
                                                       u := Hzero;
                                                       ui := 0;
                                                  end;
                                                  u := u + gh(value,v.y,v.z,v.t);
                                                  inc (ui);
                                             end;
                                             if (ui > 0) then
                                             begin
                                                  u := u/ui;
                                                  dummy.newpoint (gh(round(u.x/steps)*steps,u.y,u.z,u.t));
                                             end;
                                        end;
                                   end;
                              end
                              else if abs(step) = 2 then
                              begin
                                   v := finput^.getobject (o,l,1);
                                   dummy.newpoint (gh(min,v.y,v.z,v.t));
                                   v := finput^.getobject (o,l,p);
                                   dummy.newpoint (gh(max,v.y,v.z,v.t));
                              end
                              else if abs(step) = 1 then
                              begin
                                   v := (finput^.getobject (o,l,1)+finput^.getobject (o,l,p))/2;
                                   dummy.newpoint (gh(round(v.x/steps)*steps,v.y,v.z,v.t));
                              end;

                              linepoly.done;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end
{ for points }           else if p = 1 then
                         begin
                              v := finput^.getobject (o,l,1);
                              dummy.newpoint (gh(round(v.x/steps)*steps,v.y,v.z,v.t));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.fit.lines.steps.x',getstring(method)+' '+getstring(steps));
     end;
end;

{ ********************************* Renumber ********************************* }
{ +CALCULATE }
procedure proc_renumber_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(p,u.y,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.x');
     end;
end;

procedure proc_renumber_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,p,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.y');
     end;
end;

procedure proc_renumber_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,u.y,p,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.z');
     end;
end;

procedure proc_renumber_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject(o,l,p);
                         dummy.newpoint(gh(u.x,u.y,u.z,p));
                    end;
                    dummy.newline (finput^.getmaterial(o,l));
               end;
               dummy.newobject (finput^.getname(o));
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.t');
     end;
end;

{ **************************************************************************** }

{ +CALCULATE }
procedure proc_renumber_line_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(l,u.y,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.line.x');
     end;
end;

procedure proc_renumber_line_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,l,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.line.y');
     end;
end;

procedure proc_renumber_line_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,u.y,l,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.line.z');
     end;
end;

procedure proc_renumber_line_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject(o,l,p);
                         dummy.newpoint(gh(u.x,u.y,u.z,l));
                    end;
                    dummy.newline (finput^.getmaterial(o,l));
               end;
               dummy.newobject (finput^.getname(o));
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.line.t');
     end;
end;

{ **************************************************************************** }

{ +CALCULATE }
procedure proc_renumber_object_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(o,u.y,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.object.x');
     end;
end;

procedure proc_renumber_object_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,o,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.object.y');
     end;
end;

procedure proc_renumber_object_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          dummy.newpoint(gh(u.x,u.y,o,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.object.z');
     end;
end;

procedure proc_renumber_object_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject(o,l,p);
                         dummy.newpoint(gh(u.x,u.y,u.z,o));
                    end;
                    dummy.newline (finput^.getmaterial(o,l));
               end;
               dummy.newobject (finput^.getname(o));
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.renumber.object.t');
     end;
end;

{ **************************** Decrease points ******************************* }

procedure proc_decrease_points (p1,macro : gtk_pointer); cdecl;
var old,new : integer;
    percent,range,step : real;
    o,l,p : integer;
    lp,count : integer;
    line : tpolyhyper;
    dummy2 : tcloud;
begin
     line := Default(tpolyhyper);
     dummy2 := Default(tcloud);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          old := finput^.getlinelength;
          percent := limit (_getreal (calculate_crease_lines,macro,1),0,100); { macro }
          new := round(old*(1-(percent/100)));
          range := 1;
          step := 1;
          count := 0;
          dummy2.init;
          dummy2.replace(finput^);
          repeat
               if dummy2.getobjectlength > 0 then
               begin
                    dummy.clear;
                    for o := 1 to dummy2.getobjectlength do
                    begin
                         if dummy2.getobjectlinelength (o) > 0 then
                         begin
                               for l := 1 to dummy2.getobjectlinelength (o) do
                               begin
                                    if dummy2.getlinepointlength (o,l) > 0 then
                                    begin
                                         lp := dummy2.getlinepointlength (o,l);
                                         line.init (lp);
                                         for p := 1 to lp do
                                         begin
                                              line.put (p,dummy2.getobject(o,l,p));
                                         end;
                                         if lp = 1 then
                                         begin
                                              if not (dummy.searchline (0,line,range)) then
                                              begin
                                                   dummy.newpoint (dummy2.getobject (o,l,1));
                                                   dummy.newline (dummy2.getmaterial (o,l));
                                              end;
                                              inc (count);
                                         end
                                         else if lp = 2 then
                                         begin
                                              dummy.newpoint (dummy2.getobject (o,l,1));
                                              dummy.newpoint (dummy2.getobject (o,l,2));
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end
                                         else
                                         begin
                                              for p := 1 to lp do
                                              begin
                                                   dummy.newpoint (dummy2.getobject (o,l,p));
                                              end;
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end;
                                         line.done;
                                         progress ('Calculate neighbors. Step '+getstring(range,2)+' with now '+getstring((dummy2.getlinelength/old)*100,0)+'%',dummy.getlinelength/dummy2.getlinelength);
                                    end;
                               end;
                               dummy.newobject (dummy2.getname (o));
                         end;
                    end;
                    progress;
                    if (step > 0.01) then
                    begin
                         if (new > dummy.getlinelength) then
                         begin
                              range := range - step; { go back }
                              step := step / 2; { to fast }
                              range := range + step; { check new }
                         end
                         else
                         begin
                              if dummy.getlinelength = dummy2.getlinelength then step := 2 * step { not fast enough }
                                                                            else dummy2.replace (dummy);
                              range := range + step; { check new }
                         end;
                    end
                    else dummy2.replace (dummy);
               end;
          until (dummy2.getlinelength < new) {hard} or (abs((dummy2.getlinelength/old)-(new/old)) < 0.01) {range} or (step <= 0.01) {too far} or (count = 0) {no points};
          cleanup (dummy2);
          dummy2.done;
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.decrease.points',getstring(percent));
     end;
end;

{ **************************** Increase points ******************************* }

procedure proc_increase_points (_p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    s,c,z,q,t,r,g : integer;
    d,n,p1 : real;
    my : tpolyvector;
    v : vector;
begin
     my := Default(tpolyvector);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.replace (finput^);
          my.init (dummy.getpointlength);
          s := _getitem (calculate_crease_method_p,macro,1); { macro }
          case s of
                1 : t := round(dummy.getpointlength*0.75);
                2 : t := round(dummy.getpointlength*0.5);
                3 : t := round(dummy.getpointlength*0.25);
                4 : if dummy.getpointlength > 100000 then t := 100000 else t := dummy.getpointlength;
                5 : if dummy.getpointlength > 10000 then t := 10000 else t := dummy.getpointlength;
                6 : if dummy.getpointlength > 1000 then t := 1000 else t := dummy.getpointlength;
                7 : if dummy.getpointlength > 100 then t := 100 else t := dummy.getpointlength;
                else t := dummy.getpointlength;
          end;
          for o := 1 to dummy.getobjectlength do
          begin
               if dummy.getobjectlinelength (o) > 0 then
               for l := 1 to dummy.getobjectlinelength (o) do
               begin
                    if dummy.getlinepointlength (o,l) = 1 then
                    begin
                         z := dummy.getpobject (o,l,1);
                         if s <> 0 then
                         begin
                               d := infinity; g := 0;
                               for c := 1 to t do
                               begin
                                    r := random(dummy.getpointlength)+1;
                                    if r <> z then
                                    begin
                                         n := getlength((dummy.getobject (o,l,1)-dummy.getpoint (r)));
                                         if d > n then begin d := n; g := r; end;
                                    end;
                               end;
                         end
                         else
                         begin
                              d := infinity; g := 0;
                              for c := 1 to dummy.getpointlength do
                              begin
                                   if c <> z then
                                   begin
                                        n := getlength((dummy.getobject (o,l,1)-dummy.getpoint (c)));
                                        if d > n then begin d := n; g := c; end;
                                   end;
                              end;
                         end;
                         my.put (z,gv(z,g,d));
                         progress ('Calculate neighbors',z/dummy.getpointlength);
                    end;
               end;
          end;
          progress;

          my.sortz;

          p1 := limit(_getreal (calculate_crease_points,macro,2),0,1000000); { macro }
          q := round(dummy.getpointlength*(p1/100));
          if my.length > 0 then
          begin
               if my.length-q > 0 then
               begin
                    for z := my.length downto my.length-q do
                    begin
                         v := my.get (z);
                         if (v.x > 0) and (v.y > 0) then
                         begin
                               dummy.newpoint ((dummy.getpoint(round(v.x))+dummy.getpoint(round(v.y)))/2);
                               dummy.newline (0);
                         end;
                    end;
                    dummy.newobject ('increase');
               end
               else
               begin
                    for z := my.length downto 1 do
                    begin
                         v := my.get (z);
                         if (v.x > 0) and (v.y > 0) then
                         begin
                              dummy.newpoint ((dummy.getpoint(round(v.x))+dummy.getpoint(round(v.y)))/2);
                              dummy.newline (0);
                         end;
                    end;
                    dummy.newobject ('increase');
               end;
          end;
          my.done;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.increase.points',getstring(s)+' '+getstring(p1));
     end;
end;

{ **************************** Decrease vectors ****************************** }

procedure proc_decrease_vectors (p1,macro : gtk_pointer); cdecl;
var old,new : integer;
    percent,range,step : real;
    o,l,p : integer;
    lp,count : integer;
    line : tpolyhyper;
    dummy2 : tcloud;
begin
     line := Default(tpolyhyper);
     dummy2 := Default(tcloud);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          old := finput^.getlinelength;
          percent := limit (_getreal (calculate_crease_lines,macro,1),0,100); { macro }
          new := round(old*(1-(percent/100)));
          range := 1;
          step := 1;
          count := 0;
          dummy2.init;
          dummy2.replace(finput^);
          repeat
               if dummy2.getobjectlength > 0 then
               begin
                    dummy.clear;
                    for o := 1 to dummy2.getobjectlength do
                    begin
                         if dummy2.getobjectlinelength (o) > 0 then
                         begin
                               for l := 1 to dummy2.getobjectlinelength (o) do
                               begin
                                    if dummy2.getlinepointlength (o,l) > 0 then
                                    begin
                                         lp := dummy2.getlinepointlength (o,l);
                                         line.init (lp);
                                         for p := 1 to lp do
                                         begin
                                              line.put (p,dummy2.getobject(o,l,p));
                                         end;
                                         if lp = 1 then
                                         begin
                                              dummy.newpoint (dummy2.getobject (o,l,1));
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end
                                         else if lp = 2 then
                                         begin
                                              if not (dummy.searchline (0,line,range)) then
                                              begin
                                                   dummy.newpoint (dummy2.getobject (o,l,1));
                                                   dummy.newpoint (dummy2.getobject (o,l,2));
                                                   dummy.newline (dummy2.getmaterial (o,l));
                                              end;
                                              inc (count);
                                         end
                                         else
                                         begin
                                              for p := 1 to lp do
                                              begin
                                                   dummy.newpoint (dummy2.getobject (o,l,p));
                                              end;
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end;
                                         line.done;
                                         progress ('Calculate neighbors. Step '+getstring(range,2)+' with now '+getstring((dummy2.getlinelength/old)*100,0)+'%',dummy.getlinelength/dummy2.getlinelength);
                                    end;
                               end;
                               dummy.newobject (dummy2.getname (o));
                         end;
                    end;
                    progress;
                    if (step > 0.01) then
                    begin
                         if (new > dummy.getlinelength) then
                         begin
                              range := range - step; { go back }
                              step := step / 2; { to fast }
                              range := range + step; { check new }
                         end
                         else
                         begin
                              if dummy.getlinelength = dummy2.getlinelength then step := 2 * step { not fast enough }
                                                                            else dummy2.replace (dummy);
                              range := range + step; { check new }
                         end;
                    end
                    else dummy2.replace (dummy);
               end;
          until (dummy2.getlinelength < new) {hard} or (abs((dummy2.getlinelength/old)-(new/old)) < 0.01) {range} or (step <= 0.01) {too far} or (count = 0) {no vectors};
          cleanup (dummy2);
          dummy2.done;
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.decrease.vectors',getstring(percent));
     end;
end;

{ **************************** Increase vectors ****************************** }

procedure proc_increase_vectors (_p1,macro : gtk_pointer); cdecl;
var l,mymin : integer;
    s,c,q,t,r,g : integer;
    d,n,p1 : real;
    my : tpolyvector;
    v : vector;
    h,l11,l12,l21,l22 : hyper;
    store : thyper;
begin
     my := Default (tpolyvector);
     store := Default(thyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          my.init (finput^.getlinelength);
          s := _getitem (calculate_crease_method_l,macro,1); { macro }
          case s of
                1 : t := round(finput^.getlinelength*0.75);
                2 : t := round(finput^.getlinelength*0.5);
                3 : t := round(finput^.getlinelength*0.25);
                4 : if finput^.getlinelength > 100000 then t := 100000 else t := finput^.getlinelength;
                5 : if finput^.getlinelength > 10000 then t := 10000 else t := finput^.getlinelength;
                6 : if finput^.getlinelength > 1000 then t := 1000 else t := finput^.getlinelength;
                7 : if finput^.getlinelength > 100 then t := 100 else t := finput^.getlinelength;
                else t := finput^.getlinelength;
          end;
          store.init (finput^.getlinelength);
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength(l) > 0 then
               begin
                    h := finput^.getline(l,1);
                    h := h + finput^.getline(l,finput^.getalllinepointlength(l));
                    h := h / 2;
                    store.put (l,h);
               end;
          end;
          for l := 1 to finput^.getlinelength do
          begin
               if s <> 0 then
               begin
                     d := infinity; g := 0;
                     for c := 1 to t do
                     begin
                          r := random(finput^.getlinelength)+1;
                          if r <> l then
                          begin
                               n := getlength((store.get (l)-store.get (r)));
                               if d > n then begin d := n; g := r; end;
                          end;
                     end;
               end
               else
               begin
                    d := infinity; g := 0;
                    for c := 1 to finput^.getlinelength do
                    begin
                         if c <> l then
                         begin
                              n := getlength((store.get (l)-store.get (c)));
                              if d > n then begin d := n; g := c; end;
                         end;
                    end;
               end;
               my.put (l,gv(l,g,d));
               progress ('Calculate neighbors',l/store.length);
          end;
          progress;

          my.sortz;

          p1 := limit(_getreal (calculate_crease_lines,macro,2),0,1000000); { macro }
          q := round(store.length*(p1/100));
          if my.length > 0 then
          begin
               if my.length-q > 0 then
               begin
                    for l := my.length downto my.length-q do
                    begin
                         v := my.get (l);
                         if (v.x > 0) and (v.y > 0) then
                         begin
                              mymin := min (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                              if mymin > 1 then
                              begin
                                   l11 := finput^.getline (round(v.x),1);
                                   l12 := finput^.getline (round(v.x),finput^.getalllinepointlength(round(v.x)));
                                   l21 := finput^.getline (round(v.x),1);
                                   l22 := finput^.getline (round(v.x),finput^.getalllinepointlength(round(v.y)));
                                   if inv (l12-l11,l22-l21) then
                                   begin
                                        dummy.newpoint ((l11+l22)/2);
                                        dummy.newpoint ((l12+l21)/2);
                                        dummy.newline (0);
                                   end
                                   else
                                   begin
                                        dummy.newpoint ((l11+l21)/2);
                                        dummy.newpoint ((l12+l22)/2);
                                        dummy.newline (0);
                                   end;
                              end;
                         end;
                    end;
                    dummy.newobject ('increase');
               end
               else
               begin
                    for l := my.length downto 1 do
                    begin
                         v := my.get (l);
                         if (v.x > 0) and (v.y > 0) then
                         begin
                              mymin := min (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                              if mymin > 1 then
                              begin
                                   l11 := finput^.getline (round(v.x),1);
                                   l12 := finput^.getline (round(v.x),finput^.getalllinepointlength(round(v.x)));
                                   l21 := finput^.getline (round(v.y),1);
                                   l22 := finput^.getline (round(v.y),finput^.getalllinepointlength(round(v.y)));
                                   if inv (l12-l11,l22-l21) then
                                   begin
                                        dummy.newpoint ((l11+l22)/2);
                                        dummy.newpoint ((l12+l21)/2);
                                        dummy.newline (0);
                                   end
                                   else
                                   begin
                                        dummy.newpoint ((l11+l21)/2);
                                        dummy.newpoint ((l12+l22)/2);
                                        dummy.newline (0);
                                   end;
                              end;
                         end;
                    end;
                    dummy.newobject ('increase');
               end;
          end;
          store.done;
          my.done;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.increase.vectors',getstring(s)+' '+getstring(p1));
     end;
end;

{ **************************** Decrease lines ******************************* }

procedure proc_decrease_lines (p1,macro : gtk_pointer); cdecl;
var old,new : integer;
    percent,range,step : real;
    o,l,p : integer;
    lp,count : integer;
    line : tpolyhyper;
    dummy2 : tcloud;
begin
     line := Default(tpolyhyper);
     dummy2 := Default(tcloud);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          old := finput^.getlinelength;
          percent := limit (_getreal (calculate_crease_lines,macro,1),0,100); { macro }
          new := round(old*(1-(percent/100)));
          range := 1;
          step := 1;
          count := 0;
          dummy2.init;
          dummy2.replace(finput^);
          repeat
               if dummy2.getobjectlength > 0 then
               begin
                    dummy.clear;
                    for o := 1 to dummy2.getobjectlength do
                    begin
                         if dummy2.getobjectlinelength (o) > 0 then
                         begin
                               for l := 1 to dummy2.getobjectlinelength (o) do
                               begin
                                    if dummy2.getlinepointlength (o,l) > 0 then
                                    begin
                                         lp := dummy2.getlinepointlength (o,l);
                                         line.init (lp);
                                         for p := 1 to lp do
                                         begin
                                              line.put (p,dummy2.getobject(o,l,p));
                                         end;
                                         if lp = 1 then
                                         begin
                                              dummy.newpoint (dummy2.getobject (o,l,1));
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end
                                         else if lp = 2 then
                                         begin
                                              dummy.newpoint (dummy2.getobject (o,l,1));
                                              dummy.newpoint (dummy2.getobject (o,l,2));
                                              dummy.newline (dummy2.getmaterial (o,l));
                                         end
                                         else
                                         begin
                                              if not (dummy.searchline (0,line,range)) then
                                              begin
                                                   for p := 1 to lp do
                                                   begin
                                                        dummy.newpoint (dummy2.getobject (o,l,p));
                                                   end;
                                                   dummy.newline (dummy2.getmaterial (o,l));
                                              end;
                                              inc (count);
                                         end;
                                         line.done;
                                         progress ('Calculate neighbors. Step '+getstring(range,2)+' with now '+getstring((dummy2.getlinelength/old)*100,0)+'%',dummy.getlinelength/dummy2.getlinelength);
                                    end;
                               end;
                               dummy.newobject (dummy2.getname (o));
                         end;
                    end;
                    progress;
                    if (step > 0.01) then
                    begin
                         if (new > dummy.getlinelength) then
                         begin
                              range := range - step; { go back }
                              step := step / 2; { to fast }
                              range := range + step; { check new }
                         end
                         else
                         begin
                              if dummy.getlinelength = dummy2.getlinelength then step := 2 * step { not fast enough }
                                                                            else dummy2.replace (dummy);
                              range := range + step; { check new }
                         end;
                    end
                    else dummy2.replace (dummy);
               end;
          until (dummy2.getlinelength < new) {hard} or (abs((dummy2.getlinelength/old)-(new/old)) < 0.01) {range} or (step <= 0.01) {too far} or (count = 0) {no lines};
          cleanup (dummy2);
          dummy2.done;
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.decrease.lines',getstring(percent));
     end;
end;

{ **************************** Increase lines ******************************** }

{ TODO : Everything is wrong in increase lines  }

procedure proc_increase_lines (_p1,macro : gtk_pointer); cdecl;
var l,p,mymin,mymax : integer;
    s,c,q,t,r,g : integer;
    d,n,p1,factor,counter : real;
    my : tpolyvector;
    v : vector;
    h : hyper;
    store : thyper;
    line1,line2 : tpolyhyper;
    linepoly : tpolynom4d;
begin
     my := Default(tpolyvector);
     store := Default(thyper);
     line1 := Default(tpolyhyper);
     line2 := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          my.init (finput^.getlinelength);
          s := _getitem (calculate_crease_method_l,macro,1); { macro }
          case s of
                1 : t := round(finput^.getlinelength*0.75);
                2 : t := round(finput^.getlinelength*0.5);
                3 : t := round(finput^.getlinelength*0.25);
                4 : if finput^.getlinelength > 100000 then t := 100000 else t := finput^.getlinelength;
                5 : if finput^.getlinelength > 10000 then t := 10000 else t := finput^.getlinelength;
                6 : if finput^.getlinelength > 1000 then t := 1000 else t := finput^.getlinelength;
                7 : if finput^.getlinelength > 100 then t := 100 else t := finput^.getlinelength;
                else t := finput^.getlinelength;
          end;
          store.init (finput^.getlinelength);
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength(l) > 0 then
               begin
                    h := Hzero;
                    for p := 1 to finput^.getalllinepointlength(l) do
                    begin
                         h := h + finput^.getline(l,p);
                    end;
                    h := h / finput^.getalllinepointlength(l);
                    store.put (l,h);
               end;
          end;
          for l := 1 to finput^.getlinelength do
          begin
               if s <> 0 then
               begin
                     d := infinity; g := 0;
                     for c := 1 to t do
                     begin
                          r := random(finput^.getlinelength)+1;
                          if r <> l then
                          begin
                               n := getlength((store.get (l)-store.get (r)));
                               if d > n then begin d := n; g := r; end;
                          end;
                     end;
               end
               else
               begin
                    d := infinity; g := 0;
                    for c := 1 to finput^.getlinelength do
                    begin
                         if c <> l then
                         begin
                              n := getlength((store.get (l)-store.get (c)));
                              if d > n then begin d := n; g := c; end;
                         end;
                    end;
               end;
               my.put (l,gv(l,g,d));
               progress ('Calculate neighbors',l/store.length);
          end;
          progress;

          my.sortz;

          p1 := limit(_getreal (calculate_crease_lines,macro,2),0,1000000); { macro }
          q := round(store.length*(p1/100));
          if my.length > 0 then
          begin
                if my.length-q > 0 then
                begin
                     for l := my.length downto my.length-q do
                     begin
                          v := my.get (l);
                          if (v.x > 0) and (v.y > 0) then
                          begin
                               mymin := min (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                               mymax := max (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                               if (mymin > 1) and (mymax > 1) then
                               begin
                                    line1.init (finput^.getalllinepointlength(round(v.x)));
                                    for p := 1 to finput^.getalllinepointlength(round(v.x)) do line1.put (p,finput^.getline (round(v.x),p));
                                    linepoly.init (9);
                                    linepoly.getpolynom (line1);
                                    line1.done;
                                    line1.init (mymax);
                                    factor := linepoly.pathlength/(mymax-1);
                                    counter := 0;
                                    for p := 1 to mymax do
                                    begin
                                         h := linepoly.polynom (counter);
                                         counter := counter + factor;
                                         line1.put (p,h);
                                    end;
                                    linepoly.done;

                                    line2.init (finput^.getalllinepointlength(round(v.y)));
                                    for p := 1 to finput^.getalllinepointlength(round(v.y)) do line2.put (p,finput^.getline (round(v.y),p));
                                    linepoly.init (9);
                                    linepoly.getpolynom (line2);
                                    line2.done;
                                    line2.init (mymax);
                                    factor := linepoly.pathlength/(mymax-1);
                                    counter := 0;
                                    for p := 1 to mymax do
                                    begin
                                         h := linepoly.polynom (counter);
                                         counter := counter + factor;
                                         line2.put (p,h);
                                    end;
                                    linepoly.done;

                                    if inv (line1.get(mymax)-line1.get(1),line2.get(mymax)-line2.get(1)) then
                                    begin
                                         for p := 1 to mymax do
                                         begin
                                              dummy.newpoint ((line1.get(mymax-(p-1))+line2.get(p))/2);
                                         end;
                                         dummy.newline (0);
                                    end
                                    else
                                    begin
                                         for p := 1 to mymax do
                                         begin
                                              dummy.newpoint ((line1.get(p)+line2.get(p))/2);
                                         end;
                                         dummy.newline (0);
                                    end;
                                    line2.done;
                                    line1.done;
                               end;
                          end;
                     end;
                     dummy.newobject ('increase');
                end
                else
                begin
                     for l := my.length downto 1 do
                     begin
                          v := my.get (l);
                          if (v.x > 0) and (v.y > 0) then
                          begin
                               mymin := min (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                               mymax := max (finput^.getalllinepointlength(round(v.x)),finput^.getalllinepointlength(round(v.y)));
                               if (mymin > 1) and (mymax > 1) then
                               begin
                                    line1.init (finput^.getalllinepointlength(round(v.x)));
                                    for p := 1 to finput^.getalllinepointlength(round(v.x)) do line1.put (p,finput^.getline (round(v.x),p));
                                    linepoly.init (9);
                                    linepoly.getpolynom (line1);
                                    line1.done;
                                    line1.init (mymax);
                                    factor := linepoly.pathlength/(mymax-1);
                                    counter := factor;
                                    for p := 1 to mymax do
                                    begin
                                         h := linepoly.polynom (counter);
                                         counter := counter + factor;
                                         line1.put (p,h);
                                    end;
                                    linepoly.done;

                                    line2.init (finput^.getalllinepointlength(round(v.y)));
                                    for p := 1 to finput^.getalllinepointlength(round(v.y)) do line2.put (p,finput^.getline (round(v.y),p));
                                    linepoly.init (9);
                                    linepoly.getpolynom (line2);
                                    line2.done;
                                    line2.init (mymax);
                                    factor := linepoly.pathlength/(mymax-1);
                                    counter := factor;
                                    for p := 1 to mymax do
                                    begin
                                         h := linepoly.polynom (counter);
                                         counter := counter + factor;
                                         line2.put (p,h);
                                    end;
                                    linepoly.done;

                                    if inv (line1.get(mymax)-line1.get(1),line2.get(mymax)-line2.get(1)) then
                                    begin
                                         for p := 1 to mymax do
                                         begin
                                              dummy.newpoint ((line1.get(mymax-(p-1))+line2.get(p))/2);
                                         end;
                                         dummy.newline (0);
                                    end
                                    else
                                    begin
                                         for p := 1 to mymax do
                                         begin
                                              dummy.newpoint ((line1.get(p)+line2.get(p))/2);
                                         end;
                                         dummy.newline (0);
                                    end;
                                    line2.done;
                                    line1.done;
                               end;
                          end;
                     end;
                     dummy.newobject ('increase');
                end;
          end;
          store.done;
          my.done;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.increase.lines',getstring(s)+' '+getstring(p1));
     end;
end;

{ **************************************************************************** }
{ **************************************************************************** }
{ **************************************************************************** }

{ ********************************** Addup *********************************** }
{ +CALCULATE }
procedure proc_addup (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                u := Hzero; c := 0;
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u + finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;
                     if c > 0 then
                     begin
                          dummy.newpoint (u);
                          dummy.newline (finput^.getmaterial (o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.addup');
     end;
end;

procedure proc_addup_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.x);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.x,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(u.x,v.y+u.y,v.z+u.z,v.t+u.t));
                               end;
                          end;
                     end;
                     new.sortx;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.addup.x');
     end;
end;

procedure proc_addup_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.y);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.y,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x+u.x,u.y,v.z+u.z,v.t+u.t));
                               end;
                          end;
                     end;
                     new.sorty;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.addup.y');
     end;
end;

procedure proc_addup_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.z);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.z,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x+u.x,v.y+u.y,u.z,v.t+u.t));
                               end;
                          end;
                     end;
                     new.sortz;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.addup.z');
     end;
end;

procedure proc_addup_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.t);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.t,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x+u.x,v.y+u.y,v.z+u.z,u.t));
                               end;
                          end;
                     end;
                     new.sortt;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.addup.t');
     end;
end;

{ ********************************** Subtract ******************************** }
{ +CALCULATE }
procedure proc_subtract (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     u := Hzero; c := 0;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u - finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;
                     if c > 0 then
                     begin
                          dummy.newpoint(u);
                          dummy.newline  (finput^.getmaterial(o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.subtract');
     end;
end;

procedure proc_subtract_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.x);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.x,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(u.x,v.y-u.y,v.z-u.z,v.t-u.t));
                               end;
                          end;
                     end;
                     new.sortx;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.subtract.x');
     end;
end;

procedure proc_subtract_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.y);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.y,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x-u.x,u.y,v.z-u.z,v.t-u.t));
                               end;
                          end;
                     end;
                     new.sorty;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.subtract.y');
     end;
end;

procedure proc_subtract_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.z);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.z,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x-u.x,v.y-u.y,u.z,v.t-u.t));
                               end;
                          end;
                     end;
                     new.sortz;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.subtract.z');
     end;
end;

procedure proc_subtract_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.t);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.t,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x-u.x,v.y-u.y,v.z-u.z,u.t));
                               end;
                          end;
                     end;
                     new.sortt;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.subtract.t');
     end;
end;

{ ********************************** Multiply ******************************** }
{ +CALCULATE }
procedure proc_multiply (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     u := Hzero; c := 0;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u * finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;
                     if c > 0 then
                     begin
                          dummy.newpoint (u);
                          dummy.newline (finput^.getmaterial (o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.multiply');
     end;
end;

procedure proc_multiply_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.x);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.x,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(u.x,v.y*u.y,v.z*u.z,v.t*u.t));
                               end;
                          end;
                     end;
                     new.sortx;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.multiply.x');
     end;
end;

procedure proc_multiply_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.y);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.y,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x*u.x,u.y,v.z*u.z,v.t*u.t));
                               end;
                          end;
                     end;
                     new.sorty;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.multiply.y');
     end;
end;

procedure proc_multiply_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.z);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.z,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x*u.x,v.y*u.y,u.z,v.t*u.t));
                               end;
                          end;
                     end;
                     new.sortz;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.multiply.z');
     end;
end;

procedure proc_multiply_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.t);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.t,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x*u.x,v.y*u.y,v.z*u.z,u.t));
                               end;
                          end;
                     end;
                     new.sortt;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial (o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.multiply.t');
     end;
end;

{ ********************************** Divide ********************************** }
{ +CALCULATE }
procedure proc_divide (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     u := Hzero; c := 0;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u / finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;
                     if c > 0 then
                     begin
                          dummy.newpoint(u);
                          dummy.newline  (finput^.getmaterial(o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.divide');
     end;
end;

procedure proc_divide_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.x);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.x,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(u.x,v.y/u.y,v.z/u.z,v.t/u.t));
                               end;
                          end;
                     end;
                     new.sortx;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.divide.x');
     end;
end;

procedure proc_divide_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.y);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.y,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x/u.x,u.y,v.z/u.z,v.t/u.t));
                               end;
                          end;
                     end;
                     new.sorty;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.divide.y');
     end;
end;

procedure proc_divide_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.z);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.z,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x/u.x,v.y/u.y,u.z,v.t/u.t));
                               end;
                          end;
                     end;
                     new.sortz;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.divide.z');
     end;
end;

procedure proc_divide_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.t);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.t,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                    v := new.get(c);
                                    new.put (c,gh(v.x/u.x,v.y/u.y,v.z/u.z,u.t));
                               end;
                          end;
                     end;
                     new.sortt;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.divide.t');
     end;
end;

{ ********************************** Mean ************************************ }
{ +CALCULATE }
procedure proc_mean (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     u := Hzero; c := 0;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u + finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;
                     if c > 0 then
                     begin
                          dummy.newpoint(u/c);
                          dummy.newline  (finput^.getmaterial(o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.mean');
     end;
end;

procedure proc_mean_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.x);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.x,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                    new.put (c,new.get(c)+u);
                               end;
                          end;
                     end;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               new.put (p,new.get(p)/sorted.get(p).y);
                          end;
                     end;
                     new.sortx;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.mean.x');
     end;
end;

procedure proc_mean_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.y);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.y,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                    new.put (c,new.get(c)+u);
                               end;
                          end;
                     end;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               new.put (p,new.get(p)/sorted.get(p).y);
                          end;
                     end;
                     new.sorty;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.mean.y');
     end;
end;

procedure proc_mean_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.z);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.z,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                    new.put (c,new.get(c)+u);
                               end;
                          end;
                     end;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               new.put (p,new.get(p)/sorted.get(p).y);
                          end;
                     end;
                     new.sortz;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.mean.z');
     end;
end;

procedure proc_mean_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     sorted.init;
                     new.init;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := finput^.getobject (o,l,p);
                               c := sorted.searchx (u.t);
                               if c = 0 then
                               begin
                                    sorted.put (sorted.length+1,gc(u.t,1));
                                    new.put    (new.length+1,u);
                               end
                               else
                               begin
                                    sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                    new.put (c,new.get(c)+u);
                               end;
                          end;
                     end;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               new.put (p,new.get(p)/sorted.get(p).y);
                          end;
                     end;
                     new.sortt;
                     if sorted.length > 0 then
                     begin
                          for p := 1 to sorted.length do
                          begin
                               dummy.newpoint(new.get(p));
                               dummy.newline (finput^.getmaterial(o,1));
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     new.done;
                     sorted.done;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.mean.t');
     end;
end;

{ ********************************** SD ************************************** }
{ +CALCULATE }
procedure proc_sd (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v,a : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     u := Hzero; c := 0;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               u := u + finput^.getobject (o,l,p);
                               inc (c);
                          end;
                     end;

                     v := Hzero; a := Hzero;
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               v := finput^.getobject (o,l,p)-(u/c);
                               a := a + sqr(v);
                          end;
                     end;

                     if c > 0 then
                     begin
                          dummy.newpoint (u/c+sqrt(a/c));
                          dummy.newpoint (u/c);
                          dummy.newpoint (u/c-sqrt(a/c));
                          dummy.newline (finput^.getmaterial(o,1));
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sd');
     end;
end;

procedure proc_sd_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new,newa : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     newa := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.x);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.x,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              new.put (p,new.get(p)/sorted.get(p).y);
                         end;
                    end;
                    new.sortx;

                    newa.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.x);
                              v := sqr(u-(new.get(c)));
                              newa.put(c,newa.get(c) + v);
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := sqrt(newa.get(p)/sorted.get(p).y);
                              newa.put (p,gh(0,u.y,u.z,u.t));
                         end;
                    end;

                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint (new.get(p)+newa.get(p));
                              dummy.newpoint (new.get(p));
                              dummy.newpoint (new.get(p)-newa.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    newa.done;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sd.x');
     end;
end;

procedure proc_sd_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new,newa : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     newa := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.y);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.y,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              new.put (p,new.get(p)/sorted.get(p).y);
                         end;
                    end;
                    new.sorty;

                    newa.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.y);
                              v := sqr(u-(new.get(c)));
                              newa.put(c,newa.get(c) + v);
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := sqrt(newa.get(p)/sorted.get(p).y);
                              newa.put (p,gh(u.x,0,u.z,u.t));
                         end;
                    end;

                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint (new.get(p)+newa.get(p));
                              dummy.newpoint (new.get(p));
                              dummy.newpoint (new.get(p)-newa.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    newa.done;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sd.y');
     end;
end;

procedure proc_sd_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new,newa : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     newa := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.z);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.z,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              new.put (p,new.get(p)/sorted.get(p).y);
                         end;
                    end;
                    new.sortz;

                    newa.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.z);
                              v := sqr(u-(new.get(c)));
                              newa.put(c,newa.get(c) + v);
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := sqrt(newa.get(p)/sorted.get(p).y);
                              newa.put (p,gh(u.x,u.y,0,u.t));
                         end;
                    end;

                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint (new.get(p)+newa.get(p));
                              dummy.newpoint (new.get(p));
                              dummy.newpoint (new.get(p)-newa.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    newa.done;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sd.y');
     end;
end;

procedure proc_sd_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u,v : hyper;
    sorted : tpolycomplex;
    new,newa : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     newa := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.t);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.t,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              new.put (p,new.get(p)/sorted.get(p).y);
                         end;
                    end;
                    new.sortt;

                    newa.init;
                    if finput^.getobjectlinelength (o) > 0 then
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              c := sorted.searchx (u.t);
                              v := sqr(u-(new.get(c)));
                              newa.put(c,newa.get(c) + v);
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := sqrt(newa.get(p)/sorted.get(p).y);
                              newa.put (p,gh(u.x,u.y,u.z,0));
                         end;
                    end;

                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint (new.get(p)+newa.get(p));
                              dummy.newpoint (new.get(p));
                              dummy.newpoint (new.get(p)-newa.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    newa.done;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.sd.t');
     end;
end;

{ ********************************** RMS *********************************** }
{ Root (Mean (Square x)) }
{ +CALCULATE }
procedure proc_rms (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    u := Hzero; c := 0;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := u + sqr(finput^.getobject (o,l,p));
                              inc (c);
                         end;
                    end;
                    if c > 0 then
                    begin
                         dummy.newpoint(sqrt(u));
                         dummy.newline (finput^.getmaterial(o,1));
                         dummy.newobject (finput^.getname(o));
                    end;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.rms');
     end;
end;

procedure proc_rms_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(u.x,sqr(u.y),sqr(u.z),sqr(u.t));
                              c := sorted.searchx (u.x);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.x,1));
                                   new.put (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(u.x,sqrt(u.y),sqrt(u.z),sqrt(u.t)));
                         end;
                    end;
                    new.sortx;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.rms.x');
     end;
end;

procedure proc_rms_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqr(u.x),u.y,sqr(u.z),sqr(u.t));
                              c := sorted.searchx (u.y);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.y,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqrt(u.x),u.y,sqrt(u.z),sqrt(u.t)));
                         end;
                    end;
                    new.sorty;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.rms.y');
     end;
end;

procedure proc_rms_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqr(u.x),sqr(u.y),u.z,sqr(u.t));
                              c := sorted.searchx (u.z);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.z,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqrt(u.x),sqrt(u.y),u.z,sqrt(u.t)));
                         end;
                    end;
                    new.sortz;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.rms.z');
     end;
end;

procedure proc_rms_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqr(u.x),sqr(u.y),sqr(u.z),u.t);
                              c := sorted.searchx (u.t);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.t,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqrt(u.x),sqrt(u.y),sqrt(u.z),u.t));
                         end;
                    end;
                    new.sortt;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.rms.t');
     end;
end;

{ ********************************** SMR ************************************* }
{ Square (Mean (Root x)) }
{ +CALCULATE }
procedure proc_smr (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    u := Hzero; c := 0;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := u + sqrt(finput^.getobject (o,l,p));
                              inc (c);
                         end;
                    end;
                    if c > 0 then
                    begin
                         dummy.newpoint(sqr(u));
                         dummy.newline (finput^.getmaterial(o,1));
                         dummy.newobject (finput^.getname(o));
                    end;
               end;
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smr');
     end;
end;

procedure proc_smr_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(u.x,sqrt(u.y),sqrt(u.z),sqrt(u.t));
                              c := sorted.searchx (u.x);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.x,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.x,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(u.x,sqr(u.y),sqr(u.z),sqr(u.t)));
                         end;
                    end;
                    new.sortx;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smr.x');
     end;
end;

procedure proc_smr_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqrt(u.x),u.y,sqrt(u.z),sqrt(u.t));
                              c := sorted.searchx (u.y);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.y,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.y,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqr(u.x),u.y,sqr(u.z),sqr(u.t)));
                         end;
                    end;
                    new.sorty;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smr.y');
     end;
end;

procedure proc_smr_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqrt(u.x),sqrt(u.y),u.z,sqrt(u.t));
                              c := sorted.searchx (u.z);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.z,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.z,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqr(u.x),sqr(u.y),u.z,sqr(u.t)));
                         end;
                    end;
                    new.sortz;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smr.z');
     end;
end;

procedure proc_smr_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              u := gh(sqrt(u.x),sqrt(u.y),sqrt(u.z),u.t);
                              c := sorted.searchx (u.t);
                              if c = 0 then
                              begin
                                   sorted.put (sorted.length+1,gc(u.t,1));
                                   new.put    (new.length+1,u);
                              end
                              else
                              begin
                                   sorted.put (c,gc(u.t,sorted.get(c).y+1));
                                   new.put (c,new.get(c)+u);
                              end;
                         end;
                    end;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(p)/sorted.get(p).y;
                              new.put (p,gh(sqr(u.x),sqr(u.y),sqr(u.z),u.t));
                         end;
                    end;
                    new.sortt;
                    if sorted.length > 0 then
                    begin
                         for p := 1 to sorted.length do
                         begin
                              dummy.newpoint(new.get(p));
                              dummy.newline (finput^.getmaterial(o,1));
                         end;
                         dummy.newobject (finput^.getname(o));
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.smr.t');
     end;
end;

{ ********************************* Group ***********************************  }
{ +CALCULATE }
procedure proc_group_nearest (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               if getlength (u-v) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end
                                    else if ul <> vl then
                                    begin
                                         _dialog_message ('Grouping error!','Can''t group, because one point is in two groups. Please reduce group width!'{+#10+#10+
                                                   'Point 1 : '+getstring(u1)+' Group : '+getstring(ul)+#10+
                                                   'Point 2 : '+getstring(v1)+' Group : '+getstring(vl)+#10+
                                                   'Counter 1 : '+getstring(count)+' Counter 2 : '+getstring(counter)+#10+
                                                   'Actual group : '+getstring(group)+#10});
                                         sub.done;
                                         _cursor_arrow;
                                         exit;
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.nearest',getstring(group_n));
     end;
end;

procedure proc_hardgroup_nearest (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               if getlength (u-v) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.hardgroup.nearest',getstring(group_n));
     end;
end;

{ *** T *** }

procedure proc_group_nearest_t (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : vector;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := gv(u.x,u.y,u.z);
                               v1 := gv(v.x,v.y,v.z);
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end
                                    else if ul <> vl then
                                    begin
                                         _dialog_message ('Grouping error!','Can''t group, because one point is in two groups. Please reduce group width!'{+#10+#10+
                                                   'Point 1 : '+getstring(u1)+' Group : '+getstring(ul)+#10+
                                                   'Point 2 : '+getstring(v1)+' Group : '+getstring(vl)+#10+
                                                   'Counter 1 : '+getstring(count)+' Counter 2 : '+getstring(counter)+#10+
                                                   'Actual group : '+getstring(group)+#10});
                                         sub.done;
                                         _cursor_arrow;
                                         exit;
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.nearest.t',getstring(group_n));
     end;
end;

procedure proc_hardgroup_nearest_t (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : vector;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := gv(u.x,u.y,u.z);
                               v1 := gv(v.x,v.y,v.z);
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.hardgroup.nearest.t',getstring(group_n));
     end;
end;

{ *** Z *** }

procedure proc_group_nearest_z (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : complex;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := gc(u.x,u.y);
                               v1 := gc(v.x,v.y);
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end
                                    else if ul <> vl then
                                    begin
                                         _dialog_message ('Grouping error!','Can''t group, because one point is in two groups. Please reduce group width!'{+#10+#10+
                                                   'Point 1 : '+getstring(u1)+' Group : '+getstring(ul)+#10+
                                                   'Point 2 : '+getstring(v1)+' Group : '+getstring(vl)+#10+
                                                   'Counter 1 : '+getstring(count)+' Counter 2 : '+getstring(counter)+#10+
                                                   'Actual group : '+getstring(group)+#10});
                                         sub.done;
                                         _cursor_arrow;
                                         exit;
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.nearest.z',getstring(group_n));
     end;
end;

procedure proc_hardgroup_nearest_z (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : complex;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := gc(u.x,u.y);
                               v1 := gc(v.x,v.y);
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.hardgroup.nearest.z',getstring(group_n));
     end;
end;

{ *** Y *** }

procedure proc_group_nearest_y (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : real;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := u.x;
                               v1 := v.x;
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end
                                    else if ul <> vl then
                                    begin
                                         _dialog_message ('Grouping error!','Can''t group, because one point is in two groups. Please reduce group width!'{+#10+#10+
                                                   'Point 1 : '+getstring(u1)+' Group : '+getstring(ul)+#10+
                                                   'Point 2 : '+getstring(v1)+' Group : '+getstring(vl)+#10+
                                                   'Counter 1 : '+getstring(count)+' Counter 2 : '+getstring(counter)+#10+
                                                   'Actual group : '+getstring(group)+#10});
                                         sub.done;
                                         _cursor_arrow;
                                         exit;
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.nearest.y',getstring(group_n));
     end;
end;

procedure proc_hardgroup_nearest_y (p1,macro : gtk_pointer); cdecl;
var sub : tpolycomplexnat;
    count,counter,group,ul,vl : integer;
    group_n : real;
    u,v : hyper;
    u1,v1 : real;
    c,oldc : complexnat;
begin
     sub := Default(tpolycomplexnat);

     group_n := _getreal(group_nearest,macro,1);
     if group_n > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          if finput^.getpointlength > 1 then
          begin
               group := 1;
               sub.init (finput^.getpointlength);
                for count := 1 to finput^.getpointlength do
                begin
                     for counter := 1 to finput^.getpointlength do
                     begin
                          if count <> counter then
                          begin
                               u := finput^.getpoint (count);
                               v := finput^.getpoint (counter);
                               u1 := u.x;
                               v1 := v.x;
                               if getlength (u1-v1) <= group_n then
                               begin
                                    ul := sub.get (count).x;
                                    vl := sub.get (counter).x;
                                    if (ul = 0) and (vl = 0) then
                                    begin
                                         sub.put (count,gcn(group,count));
                                         sub.put (counter,gcn(group,counter));
                                         inc (group);
                                    end
                                    else if ul = 0 then
                                    begin
                                         sub.put (count,gcn(vl,count));
                                    end
                                    else if vl = 0 then
                                    begin
                                         sub.put (counter,gcn(ul,counter));
                                    end;
                               end;
                          end;
                     end;
                end;
               sub.sortx;
               oldc := sub.get(1);
               for count := 1 to sub.length do
               begin
                    c := sub.get(count);
                    if oldc.x <> c.x then
                    begin
                         dummy.newline (0);
                         dummy.newobject ('');
                    end;
                    dummy.newpoint (finput^.getpoint (c.y));
                    oldc := c;
               end;
               dummy.newline (0);
               dummy.newobject ('');
               sub.done;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.hardgroup.nearest.y',getstring(group_n));
     end;
end;

{ ******************************* Group Axis ********************************* }
{ +CALCULATE }
procedure proc_group_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    origin,step,value : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.x+origin)/step)*step-origin;
                          dummy.newpoint(gh(value,u.y,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.x',getstring(origin)+' '+getstring(step));
     end;
end;

procedure proc_group_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    origin,step,value : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.y+origin)/step)*step-origin;
                          dummy.newpoint(gh(u.x,value,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.y',getstring(origin)+' '+getstring(step));
     end;
end;

procedure proc_group_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    origin,step,value : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.z+origin)/step)*step-origin;
                          dummy.newpoint(gh(u.x,u.y,value,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.z',getstring(origin)+' '+getstring(step));
     end;
end;

procedure proc_group_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    origin,step,value : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject(o,l,p);
                         value := system.trunc((u.t+origin)/step)*step-origin;
                         dummy.newpoint(gh(u.x,u.y,u.z,value));
                    end;
                    dummy.newline (finput^.getmaterial(o,l));
               end;
               dummy.newobject (finput^.getname(o));
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.t',getstring(origin)+' '+getstring(step));
     end;
end;

{ ******************************* Group Axis [from to] ******************************** }
{ +CALCULATE }
procedure proc_group_only_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    w : complex;
    origin,step,_from,_to,value : real;
    sorted : tpolycomplex;
    new  : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
          _from := _getreal (group_from,macro,3);
          _to := _getreal (group_to,macro,4);
          for o := 1 to finput^.getobjectlength do
          begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.x+origin)/step)*step-origin;
                          dummy.newpoint(gh(value,u.y,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
          end;

           for o := 1 to dummy.getobjectlength do
           begin
                sorted.init;
                new.init;
                if dummy.getobjectlinelength (o) > 0 then
                for l := 1 to dummy.getobjectlinelength (o) do
                begin
                     if dummy.getlinepointlength (o,l) > 0 then
                     for p := 1 to dummy.getlinepointlength (o,l) do
                     begin
                          u := dummy.getobject (o,l,p);
                          c := sorted.searchx (u.x);
                          if c = 0 then sorted.put (sorted.length+1,gc(u.x,1))
                                   else sorted.put (c,gc(u.x,sorted.get(c).y+1));
                     end;
                end;
                new.sortx;
                if sorted.length > 0 then
                begin
                     if dummy.getobjectlinelength (o) > 0 then
                     for l := 1 to dummy.getobjectlinelength (o) do
                     begin
                          if dummy.getlinepointlength (o,l) > 0 then
                          for p := 1 to dummy.getlinepointlength (o,l) do
                          begin
                               u := dummy.getobject (o,l,p);
                               w := sorted.get (sorted.searchx (u.x));
                               if (w.y < _from) or (w.y > _to) then dummy.putobject (o,l,p,Hmax);
                          end;
                     end;
                end;
                new.done;
                sorted.done;
           end;
           dummy.erasemarked;

          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.only.x',getstring(origin)+' '+getstring(step)+' '+getstring(_from)+' '+getstring(_to));
     end;
end;

procedure proc_group_only_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    w : complex;
    origin,step,_from,_to,value : real;
    sorted : tpolycomplex;
    new  : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
          _from := _getreal (group_from,macro,3);
          _to := _getreal (group_to,macro,4);
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.y+origin)/step)*step-origin;
                          dummy.newpoint(gh(u.x,value,u.z,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;

           for o := 1 to dummy.getobjectlength do
           begin
                sorted.init;
                new.init;
                if dummy.getobjectlinelength (o) > 0 then
                for l := 1 to dummy.getobjectlinelength (o) do
                begin
                     if dummy.getlinepointlength (o,l) > 0 then
                     for p := 1 to dummy.getlinepointlength (o,l) do
                     begin
                          u := dummy.getobject (o,l,p);
                          c := sorted.searchx (u.y);
                          if c = 0 then sorted.put (sorted.length+1,gc(u.y,1))
                                   else sorted.put (c,gc(u.y,sorted.get(c).y+1));
                     end;
                end;
                new.sortx;
                if sorted.length > 0 then
                begin
                     if dummy.getobjectlinelength (o) > 0 then
                     for l := 1 to dummy.getobjectlinelength (o) do
                     begin
                          if dummy.getlinepointlength (o,l) > 0 then
                          for p := 1 to dummy.getlinepointlength (o,l) do
                          begin
                               u := dummy.getobject (o,l,p);
                               w := sorted.get (sorted.searchx (u.y));
                               if (w.y < _from) or (w.y > _to) then dummy.putobject (o,l,p,Hmax);
                          end;
                     end;
                end;
                new.done;
                sorted.done;
           end;
           dummy.erasemarked;

          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.only.y',getstring(origin)+' '+getstring(step)+' '+getstring(_from)+' '+getstring(_to));
     end;
end;

procedure proc_group_only_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    w : complex;
    origin,step,_from,_to,value : real;
    sorted : tpolycomplex;
    new  : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
          _from := _getreal (group_from,macro,3);
          _to := _getreal (group_to,macro,4);
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject(o,l,p);
                          value := system.trunc((u.z+origin)/step)*step-origin;
                          dummy.newpoint(gh(u.x,u.y,value,u.t));
                     end;
                     dummy.newline (finput^.getmaterial(o,l));
                end;
                dummy.newobject (finput^.getname(o));
           end;

           for o := 1 to dummy.getobjectlength do
           begin
                sorted.init;
                new.init;
                if dummy.getobjectlinelength (o) > 0 then
                for l := 1 to dummy.getobjectlinelength (o) do
                begin
                     if dummy.getlinepointlength (o,l) > 0 then
                     for p := 1 to dummy.getlinepointlength (o,l) do
                     begin
                          u := dummy.getobject (o,l,p);
                          c := sorted.searchx (u.z);
                          if c = 0 then sorted.put (sorted.length+1,gc(u.z,1))
                                   else sorted.put (c,gc(u.z,sorted.get(c).y+1));
                     end;
                end;
                new.sortx;
                if sorted.length > 0 then
                begin
                     if dummy.getobjectlinelength (o) > 0 then
                     for l := 1 to dummy.getobjectlinelength (o) do
                     begin
                          if dummy.getlinepointlength (o,l) > 0 then
                          for p := 1 to dummy.getlinepointlength (o,l) do
                          begin
                               u := dummy.getobject (o,l,p);
                               w := sorted.get (sorted.searchx (u.z));
                               if (w.y < _from) or (w.y > _to) then dummy.putobject (o,l,p,Hmax);
                          end;
                     end;
                end;
                new.done;
                sorted.done;
           end;
           dummy.erasemarked;

          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.only.z',getstring(origin)+' '+getstring(step)+' '+getstring(_from)+' '+getstring(_to));
     end;
end;

procedure proc_group_only_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    w : complex;
    origin,step,_from,_to,value : real;
    sorted : tpolycomplex;
    new  : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          origin := _getreal (group_origin,macro,1);
          step := _getreal (group_step,macro,2);
          _from := _getreal (group_from,macro,3);
          _to := _getreal (group_to,macro,4);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject(o,l,p);
                         value := system.trunc((u.t+origin)/step)*step-origin;
                         dummy.newpoint(gh(u.x,u.y,u.z,value));
                    end;
                    dummy.newline (finput^.getmaterial(o,l));
               end;
               dummy.newobject (finput^.getname(o));
          end;

           for o := 1 to dummy.getobjectlength do
           begin
                sorted.init;
                new.init;
                if dummy.getobjectlinelength (o) > 0 then
                for l := 1 to dummy.getobjectlinelength (o) do
                begin
                     if dummy.getlinepointlength (o,l) > 0 then
                     for p := 1 to dummy.getlinepointlength (o,l) do
                     begin
                          u := dummy.getobject (o,l,p);
                          c := sorted.searchx (u.t);
                          if c = 0 then sorted.put (sorted.length+1,gc(u.t,1))
                                   else sorted.put (c,gc(u.t,sorted.get(c).y+1));
                     end;
                end;
                new.sortx;
                if sorted.length > 0 then
                begin
                     if dummy.getobjectlinelength (o) > 0 then
                     for l := 1 to dummy.getobjectlinelength (o) do
                     begin
                          if dummy.getlinepointlength (o,l) > 0 then
                          for p := 1 to dummy.getlinepointlength (o,l) do
                          begin
                               u := dummy.getobject (o,l,p);
                               w := sorted.get (sorted.searchx (u.t));
                               if (w.y < _from) or (w.y > _to) then dummy.putobject (o,l,p,Hmax);
                          end;
                     end;
                end;
                new.done;
                sorted.done;
           end;
           dummy.erasemarked;

          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.group.only.t',getstring(origin)+' '+getstring(step)+' '+getstring(_from)+' '+getstring(_to));
     end;
end;

{ ******************************* Begin of lines ***************************** }
{ +Calculate }
procedure proc_move_begin_lines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                              finput^.markpoint (o,l,1);
                         end;
                    end;
                    dummy.newobject ('begin_lines_'+finput^.getname (o));
               end;
          end;
          finput^.erasemarked;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.begin.lines.move');
     end;
end;

procedure proc_begin_lines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                         end;
                    end;
                    dummy.newobject ('begin_lines_'+finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.begin.lines');
     end;
end;

procedure proc_middle_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,l1,l2 : integer;
    len : real;
    length : tpolyreal;
    v : hyper;
begin
     length := Default(tpolyreal);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 2 then
                         begin
                              length.init;
                              for p := 1  to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   length.put (length.length+1,getlength(finput^.getobject (o,l,p)-finput^.getobject (o,l,p+1)));
                              end;
                              l1 := 1; l2 := finput^.getlinepointlength (o,l)-1; len := 0;
                              repeat
                                   if len <= 0 then
                                   begin
                                        len := len + length.get (l1);
                                        inc (l1);
                                   end
                                   else
                                   begin
                                        len := len - length.get (l2);
                                        dec (l2);
                                   end;
                              until (l1 >= l2);
                              if len = 0 then dummy.newpoint (finput^.getobject (o,l,l1))
                              else if len < 0 then
                              begin
                                   v := abs(len)*norm(finput^.getobject (o,l,l1+1)-finput^.getobject (o,l,l1));
                                   dummy.newpoint (finput^.getobject (o,l,l1)+v);
                              end
                              else
                              begin
                                   v := len*norm(finput^.getobject (o,l,l1-1)-finput^.getobject (o,l,l1));
                                   dummy.newpoint (finput^.getobject (o,l,l1)+v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                              length.done;
                         end
                         else if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,2)-finput^.getobject (o,l,1);
                              len := getlength(v)/2;
                              dummy.newpoint (finput^.getobject (o,l,1)+(len*norm(v)));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                         end;
                    end;
                    dummy.newobject ('middle_lines_'+finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.middle.lines');
     end;
end;

procedure proc_end_lines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                         end;
                    end;
                    dummy.newobject ('end_lines_'+finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.end.lines');
     end;
end;


procedure proc_move_end_lines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                              finput^.markpoint(o,l,finput^.getlinepointlength (o,l));
                         end;
                    end;
                    dummy.newobject ('end_lines_'+finput^.getname (o));
               end;
          end;
          finput^.erasemarked;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.end.lines.move');
     end;
end;

{ *************************** Begin (vector) of lines ************************ }
{ +Calculate }
procedure proc_move_begin_lines_vector (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newpoint (finput^.getobject (o,l,2));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                              finput^.markpoint (o,l,1);
                              finput^.markpoint (o,l,2);
                         end;
                    end;
                    dummy.newobject ('begin_lines_'+finput^.getname (o));
               end;
          end;
          finput^.erasemarked;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.begin.vector.lines.move');
     end;
end;

procedure proc_begin_lines_vector (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newpoint (finput^.getobject (o,l,2));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                         end;
                    end;
                    dummy.newobject ('begin_lines_'+finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.begin.vector.lines');
     end;
end;

procedure proc_end_lines_vector (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)-1));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                         end;
                    end;
                    dummy.newobject ('end_lines_'+finput^.getname (o));
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.end.vector.lines');
     end;
end;


procedure proc_move_end_lines_vector (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)-1));
                              dummy.newline (finput^.getmaterial (o,l)); { newline }
                              finput^.markpoint(o,l,finput^.getlinepointlength (o,l));
                              finput^.markpoint(o,l,finput^.getlinepointlength (o,l)-1);
                         end;
                    end;
                    dummy.newobject ('end_lines_'+finput^.getname (o));
               end;
          end;
          finput^.erasemarked;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.end.vector.lines.move');
     end;
end;

{ ********************************** Min ************************************* }
{ +CALCULATE }
procedure proc_min (p1,macro : gtk_pointer); cdecl;
var o : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                u := finput^.objectmin (o);
                dummy.newpoint(u);
                dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.min');
     end;
end;

procedure proc_min_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.x,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).x = u.x then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmin);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmin);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.min.x');
     end;
end;

procedure proc_min_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.y,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).y = u.y then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmin);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmin);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.min.y');
     end;
end;

procedure proc_min_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.z,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).z = u.z then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmin);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmin);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.min.z');
     end;
end;

procedure proc_min_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.t,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).t = u.t then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmin);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmin);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.min.t');
     end;
end;

{ ********************************** Quantile ******************************** }

procedure proc_q (q : real);
var o,l,p : integer;
    u : hyper;
    vari : tpolyhyper;
    nq : real;
begin
     vari := Default(tpolyhyper);

     if into (q,0,1) then
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          vari.init;
          for o := 1 to finput^.getobjectlength do
          begin
               vari.newlength (0);
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) > 0 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         u := finput^.getobject (o,l,p);
                         vari.put (vari.length+1,u);
                    end;
               end;
               if vari.length > 3 then
               begin
                    vari.sort;
                    nq := vari.length*q;
                    if trunc(nq) <> nq then
                    begin
                         u := (vari.get (trunc(nq)) + vari.get (trunc(nq)+1))/2;
                    end
                    else u := vari.get (trunc(nq));
                    dummy.newpoint(u);
                    dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          vari.done;
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

procedure proc_q_x (q : real);
var o,l,p : integer;
    u : hyper;
    v : vector;
    sorted : tpolycomplex;
    new  : tpolyhyper;
    line : tpolyvector;
    x,nq : real;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyvector);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                sorted.init;
                new.init;
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject (o,l,p);
                          sorted.put (sorted.length+1,gc(u.x,sorted.length+1));
                          new.put    (new.length+1,u);
                     end;
                end;
                sorted.sortx;
                if sorted.length > 0 then
                begin
                     line.init;
                     x := ninfinity;
                     for p := 1 to sorted.length do
                     begin
                          u := new.get(round(sorted.get(p).y));
                          if line.length = 0 then
                          begin
                               line.put (1,gv(u.y,u.z,u.t)); x := u.x;
                          end
                          else if x = u.x then
                          begin
                               line.put (line.length+1,gv(u.y,u.z,u.t)); x := u.x;
                               if p = sorted.length then
                               begin
                                    if line.length > 3 then
                                    begin
                                         line.sort;
                                         nq := line.length*q;
                                         if trunc(nq) <> nq then
                                         begin
                                              v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                         end
                                         else v := line.get (trunc(nq));
                                         dummy.newpoint(gh(x,v));
                                         dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                         dummy.newobject (finput^.getname(o));
                                    end;
                               end;
                          end
                          else
                          begin
                               if line.length > 3 then
                               begin
                                    line.sort;
                                    nq := line.length*q;
                                    if trunc(nq) <> nq then
                                    begin
                                         v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                    end
                                    else v := line.get (trunc(nq));
                                    dummy.newpoint(gh(x,v));
                                    dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                    dummy.newobject (finput^.getname(o));
                               end;
                               line.newlength (0);
                               line.put (1,gv(u.y,u.z,u.t)); x := u.x;
                          end;
                     end;
                     line.done;
                end;
                new.done;
                sorted.done;
           end;
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

procedure proc_q_y (q : real);
var o,l,p : integer;
    u : hyper;
    v : vector;
    sorted : tpolycomplex;
    new : tpolyhyper;
    line : tpolyvector;
    y,nq : real;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyvector);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                sorted.init;
                new.init;
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject (o,l,p);
                          sorted.put (sorted.length+1,gc(u.y,sorted.length+1));
                          new.put    (new.length+1,u);
                     end;
                end;
                sorted.sortx;
                if sorted.length > 0 then
                begin
                     line.init;
                     y := infinity;
                     for p := 1 to sorted.length do
                     begin
                          u := new.get(round(sorted.get(p).y));
                          if line.length = 0 then
                          begin
                               line.put (1,gv(u.x,u.z,u.t)); y := u.y;
                          end
                          else if y = u.y then
                          begin
                               line.put (line.length+1,gv(u.x,u.z,u.t)); y := u.y;
                               if p = sorted.length then
                               begin
                                    if line.length > 3 then
                                    begin
                                         line.sort;
                                         nq := line.length*q;
                                         if trunc(nq) <> nq then
                                         begin
                                              v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                         end
                                         else v := line.get (trunc(nq));
                                         dummy.newpoint(gh(v.x,y,v.y,v.z));
                                         dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                         dummy.newobject (finput^.getname(o));
                                    end;
                               end;
                          end
                          else
                          begin
                               if line.length > 3 then
                               begin
                                    line.sort;
                                    nq := line.length*q;
                                    if trunc(nq) <> nq then
                                    begin
                                         v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                    end
                                    else v := line.get (trunc(nq));
                                    dummy.newpoint(gh(v.x,y,v.y,v.z));
                                    dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                    dummy.newobject (finput^.getname(o));
                               end;
                               line.newlength (0);
                               line.put (1,gv(u.x,u.z,u.t)); y := u.y;
                          end;
                     end;
                     line.done;
                end;
                new.done;
                sorted.done;
           end;
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

procedure proc_q_z (q : real);
var o,l,p : integer;
    u : hyper;
    v : vector;
    sorted : tpolycomplex;
    new : tpolyhyper;
    line : tpolyvector;
    z,nq : real;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyvector);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                sorted.init;
                new.init;
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject (o,l,p);
                          sorted.put (sorted.length+1,gc(u.z,sorted.length+1));
                          new.put    (new.length+1,u);
                     end;
                end;
                sorted.sortx;
                if sorted.length > 0 then
                begin
                     line.init;
                     z := infinity;
                     for p := 1 to sorted.length do
                     begin
                          u := new.get(round(sorted.get(p).y));
                          if line.length = 0 then
                          begin
                               line.put (1,gv(u.x,u.y,u.t)); z := u.z;
                          end
                          else if z = u.z then
                          begin
                               line.put (line.length+1,gv(u.x,u.y,u.t)); z := u.z;
                               if p = sorted.length then
                               begin
                                    if line.length > 3 then
                                    begin
                                         line.sort;
                                         nq := line.length*q;
                                         if trunc(nq) <> nq then
                                         begin
                                              v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                         end
                                         else v := line.get (trunc(nq));
                                         dummy.newpoint(gh(v.x,v.y,z,v.z));
                                         dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                         dummy.newobject (finput^.getname(o));
                                    end;
                               end;
                          end
                          else
                          begin
                               if line.length > 3 then
                               begin
                                    line.sort;
                                    nq := line.length*q;
                                    if trunc(nq) <> nq then
                                    begin
                                         v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                    end
                                    else v := line.get (trunc(nq));
                                    dummy.newpoint(gh(v.x,v.y,z,v.z));
                                    dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                    dummy.newobject (finput^.getname(o));
                               end;
                               line.newlength (0);
                               line.put (1,gv(u.x,u.y,u.t)); z := u.z;
                          end;
                     end;
                     line.done;
                end;
                new.done;
                sorted.done;
           end;
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

procedure proc_q_t (q : real);
var o,l,p : integer;
    u : hyper;
    v : vector;
    sorted : tpolycomplex;
    new : tpolyhyper;
    line : tpolyvector;
    t,nq : real;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyvector);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                sorted.init;
                new.init;
                if finput^.getobjectlinelength (o) > 0 then
                for l := 1 to finput^.getobjectlinelength (o) do
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     for p := 1 to finput^.getlinepointlength (o,l) do
                     begin
                          u := finput^.getobject (o,l,p);
                          sorted.put (sorted.length+1,gc(u.t,sorted.length+1));
                          new.put    (new.length+1,u);
                     end;
                end;
                sorted.sortx;
                if sorted.length > 0 then
                begin
                     line.init;
                     t := infinity;
                     for p := 1 to sorted.length do
                     begin
                          u := new.get(round(sorted.get(p).y));
                          if line.length = 0 then
                          begin
                               line.put (1,gv(u.x,u.y,u.z)); t := u.t;
                          end
                          else if t = u.t then
                          begin
                               line.put (line.length+1,gv(u.x,u.y,u.z)); t := u.t;
                               if p = sorted.length then
                               begin
                                    if line.length > 3 then
                                    begin
                                         line.sort;
                                         nq := line.length*q;
                                         if trunc(nq) <> nq then
                                         begin
                                              v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                         end
                                         else v := line.get (trunc(nq));
                                         dummy.newpoint(gh(v,t));
                                         dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                         dummy.newobject (finput^.getname(o));
                                    end;
                               end;
                          end
                          else
                          begin
                               if line.length > 3 then
                               begin
                                    line.sort;
                                    nq := line.length*q;
                                    if trunc(nq) <> nq then
                                    begin
                                         v := (line.get (trunc(nq)) + line.get (trunc(nq)+1))/2;
                                    end
                                    else v := line.get (trunc(nq));
                                    dummy.newpoint(gh(v,t));
                                    dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                                    dummy.newobject (finput^.getname(o));
                               end;
                               line.newlength (0);
                               line.put (1,gv(u.x,u.y,u.z)); t := u.t;
                          end;
                     end;
                     line.done;
                end;
                new.done;
                sorted.done;
           end;
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

{ ********************************** Q.25 ************************************ }
{ +CALCULATE }
procedure proc_q25 (p1,macro : gtk_pointer); cdecl;
begin
     proc_q (0.25);
     tmacro(macro^).writeredo ('calculate.q25');
end;

procedure proc_q25_x (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_x (0.25);
     tmacro(macro^).writeredo ('calculate.q25.x');
end;

procedure proc_q25_y (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_y (0.25);
     tmacro(macro^).writeredo ('calculate.q25.y');
end;

procedure proc_q25_z (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_z (0.25);
     tmacro(macro^).writeredo ('calculate.q25.z');
end;

procedure proc_q25_t (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_t (0.25);
     tmacro(macro^).writeredo ('calculate.q25.t');
end;

{ ********************************** Median ********************************** }
{ +CALCULATE }
procedure proc_median (p1,macro : gtk_pointer); cdecl;
begin
     proc_q (0.5);
     tmacro(macro^).writeredo ('calculate.median');
end;

procedure proc_median_x (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_x (0.5);
     tmacro(macro^).writeredo ('calculate.median.x');
end;

procedure proc_median_y (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_y (0.5);
     tmacro(macro^).writeredo ('calculate.median.y');
end;

procedure proc_median_z (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_z (0.5);
     tmacro(macro^).writeredo ('calculate.median.z');
end;

procedure proc_median_t (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_t (0.5);
     tmacro(macro^).writeredo ('calculate.median.t');
end;

{ ********************************** Q.75 ************************************ }
{ +CALCULATE }
procedure proc_q75 (p1,macro : gtk_pointer); cdecl;
begin
     proc_q (0.75);
     tmacro(macro^).writeredo ('calculate.q75');
end;

procedure proc_q75_x (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_x (0.75);
     tmacro(macro^).writeredo ('calculate.q75.x');
end;

procedure proc_q75_y (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_y (0.75);
     tmacro(macro^).writeredo ('calculate.q75.y');
end;

procedure proc_q75_z (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_z (0.75);
     tmacro(macro^).writeredo ('calculate.q75.z');
end;

procedure proc_q75_t (p1,macro : gtk_pointer); cdecl;
begin
     proc_q_t (0.75);
     tmacro(macro^).writeredo ('calculate.q75.t');
end;

{ ********************************** Max ************************************* }
{ +CALCULATE }
procedure proc_max (p1,macro : gtk_pointer); cdecl;
var o : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                u := finput^.objectmax (o);
                dummy.newpoint(u);
                dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max');
     end;
end;

procedure proc_max_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.x,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).x = u.x then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmax);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmax);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.x');
     end;
end;

procedure proc_max_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.y,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).y = u.y then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmax);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmax);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.y');
     end;
end;

procedure proc_max_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.z,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).z = u.z then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmax);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmax);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.z');
     end;
end;

procedure proc_max_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.t,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).t = u.t then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint(line.dimmax);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint(line.dimmax);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.max.t');
     end;
end;

{ ********************************* Center *********************************** }
{ +CALCULATE }
procedure proc_center (p1,macro : gtk_pointer); cdecl;
var o : integer;
    u : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                u := (finput^.objectmin(o)+finput^.objectmax(o))/2;
                dummy.newpoint(u);
                dummy.newline (finput^.getmaterial (o,finput^.getobjectlinelength(o)));
                dummy.newobject (finput^.getname(o));
           end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center');
     end;
end;

procedure proc_center_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.x,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).x = u.x then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint((line.dimmin+line.dimmax)/2);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint((line.dimmin+line.dimmax)/2);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center.x');
     end;
end;

procedure proc_center_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.y,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).y = u.y then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint((line.dimmin+line.dimmax)/2);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint((line.dimmin+line.dimmax)/2);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center.y');
     end;
end;

procedure proc_center_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.z,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).z = u.z then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint((line.dimmin+line.dimmax)/2);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint((line.dimmin+line.dimmax)/2);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center.z');
     end;
end;

procedure proc_center_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u : hyper;
    sorted : tpolycomplex;
    new,line : tpolyhyper;
begin
     sorted := Default(tpolycomplex);
     new := Default(tpolyhyper);
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    sorted.init;
                    new.init;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              u := finput^.getobject (o,l,p);
                              sorted.put (sorted.length+1,gc(u.t,sorted.length+1));
                              new.put    (new.length+1,u);
                         end;
                    end;
                    sorted.sortx;
                    if sorted.length > 0 then
                    begin
                         line.init;
                         for p := 1 to sorted.length do
                         begin
                              u := new.get(round(sorted.get(p).y));
                              if line.length = 0 then
                              begin
                                   line.put (1,u);
                              end
                              else if line.get(line.length).t = u.t then
                              begin
                                   line.put (line.length+1,u);
                                   if p = sorted.length then
                                   begin
                                        dummy.newpoint((line.dimmin+line.dimmax)/2);
                                        dummy.newline (finput^.getmaterial(o,1));
                                        dummy.newobject (finput^.getname(o));
                                   end;
                              end
                              else
                              begin
                                   dummy.newpoint((line.dimmin+line.dimmax)/2);
                                   dummy.newline (finput^.getmaterial(o,1));
                                   dummy.newobject (finput^.getname(o));
                                   line.newlength (0);
                                   line.put (1,u);
                              end;
                         end;
                         line.done;
                    end;
                    new.done;
                    sorted.done;
               end;
          end;
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('calculate.center.t');
     end;
end;

{ *********************** Lineedge angle & length **************************** }

procedure proc_calculate_lineedge_angle (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v,w : hyper;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 2 then
                         begin
                              w := finput^.getobject(o,l,1);
                              dummy.newpoint(gh(w.x,w.y,w.z,0));
                              for p := 2 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   w := finput^.getobject(o,l,p);
                                   u := finput^.getobject(o,l,p-1)-w;
                                   v := finput^.getobject(o,l,p+1)-w;
                                   if format.degree then dummy.newpoint (gh(w.x,w.y,w.z,getangle(gv(u.x,u.y,u.z),gv(v.x,v.y,v.z))*deg))
                                                    else dummy.newpoint (gh(w.x,w.y,w.z,getangle(gv(u.x,u.y,u.z),gv(v.x,v.y,v.z))));
                              end;
                              w := finput^.getobject(o,l,finput^.getlinepointlength (o,l));
                              dummy.newpoint(gh(w.x,w.y,w.z,0));
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                         end;
                         dummy.newline(finput^.getmaterial(o,l));
                    end;
               end;
               dummy.newobject(finput^.getname(o));
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.lineedge.angle');
     end;
     _cursor_arrow;
end;

procedure proc_calculate_lineedge_invangle (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v,w : hyper;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 2 then
                         begin
                              w := finput^.getobject(o,l,1);
                              dummy.newpoint(gh(w.x,w.y,w.z,0));
                              for p := 2 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   w := finput^.getobject(o,l,p);
                                   u := finput^.getobject(o,l,p-1)-w;
                                   v := finput^.getobject(o,l,p+1)-w;
                                   if format.degree then dummy.newpoint (gh(w.x,w.y,w.z,180-(getangle(gv(u.x,u.y,u.z),gv(v.x,v.y,v.z))*deg)))
                                                    else dummy.newpoint (gh(w.x,w.y,w.z,180-(getangle(gv(u.x,u.y,u.z),gv(v.x,v.y,v.z)))));
                              end;
                              w := finput^.getobject(o,l,finput^.getlinepointlength (o,l));
                              dummy.newpoint(gh(w.x,w.y,w.z,0));
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                         end;
                         dummy.newline(finput^.getmaterial(o,l));
                    end;
               end;
               dummy.newobject(finput^.getname(o));
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.lineedge.invangle');
     end;
     _cursor_arrow;
end;

procedure proc_calculate_lineedge_length (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    u,v : hyper;
    dl : real;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              u := finput^.getobject(o,l,1);
                              dl := 0;
                              dummy.newpoint(gh(u.x,u.y,u.z,dl));
                              for p := 2 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   dl := dl + getlength (v-u);
                                   dummy.newpoint (gh(v.x,v.y,v.z,dl));
                                   u := v;
                              end;
                         end
                         else
                         begin
                              v := finput^.getobject(o,l,1);
                              dummy.newpoint(gh(v.x,v.y,v.z,0));
                         end;
                         dummy.newline(finput^.getmaterial(o,l));
                    end;
               end;
               dummy.newobject(finput^.getname(o));
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.lineedge.length');
     end;
     _cursor_arrow;
end;

{ ******************************** Area ************************************** }

procedure proc_calculate_areax (p1,macro : gtk_pointer); cdecl;
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     _cursor_watch;
     if finput^.getpointlength > 0 then
     begin
          dummy.clear;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.x = v.x then rl := rl + (v.z+u.z)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         dummy.newpoint (gh(v.x,rl,sqrt(rl),0));
                    end;
               end;
          end;
          dummy.newline (0);
          dummy.newobject ('areas_along_x');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polygone.area.x');
     end;
     _cursor_arrow;
end;

procedure proc_calculate_areay (p1,macro : gtk_pointer); cdecl;
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     _cursor_watch;
     if finput^.getpointlength > 0 then
     begin
          dummy.clear;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.y = v.y then rl := rl + (v.x+u.x)*(u.z-v.z);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         dummy.newpoint (gh(rl,v.y,sqrt(rl),0));
                    end;
               end;
          end;
          dummy.newline (0);
          dummy.newobject ('areas_along_y');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polygone.area.y');
     end;
     _cursor_arrow;
end;

procedure proc_calculate_areaz (p1,macro : gtk_pointer); cdecl;
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     _cursor_watch;
     if finput^.getpointlength > 0 then
     begin
          dummy.clear;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.z = v.z then rl := rl + (v.x+u.x)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         dummy.newpoint (gh(rl,sqrt(rl),v.z,0));
                    end;
               end;
          end;
          dummy.newline (0);
          dummy.newobject ('areas_along_z');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polygone.area.z');
     end;
     _cursor_arrow;
end;

{ ********************************* Volume *********************************** }

procedure proc_calculate_volumex (p1,macro : gtk_pointer); cdecl;
var my : tpolycomplex;
    z,l,bl : integer;
    rl : real;
    u,v : hyper;
    cu,cv : complex;
begin
     my := Default(tpolycomplex);

     _cursor_watch;
     my.init;
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.x = v.x then rl := rl + (v.z+u.z)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.put (my.length+1,gc(v.x,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
     if my.length > 1 then
     begin
          cu := my.get (1);
          for l := 2 to my.length do
          begin
               cv := my.get(l);
               rl := (cv.x-cu.x)*((cv.y+cu.y)/2); { Mittelwert zwischen zwei Werten }
               dummy.newpoint (gh(cv.x,0,0,rl));
               cu := cv;
          end;
          dummy.newline (0);
          dummy.newobject ('volumes_along_x');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polyeder.volume.x');
     end;
     my.done;
     _cursor_arrow;
end;

procedure proc_calculate_volumey (p1,macro : gtk_pointer); cdecl;
var my : tpolycomplex;
    z,l,bl : integer;
    rl : real;
    u,v : hyper;
    cu,cv : complex;
begin
     my := Default(tpolycomplex);

     _cursor_watch;
     my.init;
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.y = v.y then rl := rl + (v.x+u.x)*(u.z-v.z);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.put (my.length+1,gc(v.y,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
     if my.length > 1 then
     begin
          cu := my.get (1);
          for l := 2 to my.length do
          begin
               cv := my.get(l);
               rl := (cv.x-cu.x)*((cv.y+cu.y)/2); { Mittelwert zwischen zwei Werten }
               dummy.newpoint (gh(0,cv.x,0,rl));
               cu := cv;
          end;
          dummy.newline (0);
          dummy.newobject ('volumes_along_y');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polyeder.volume.y');
     end;
     my.done;
     _cursor_arrow;
end;

procedure proc_calculate_volumez (p1,macro : gtk_pointer); cdecl;
var my : tpolycomplex;
    z,l,bl : integer;
    rl : real;
    u,v : hyper;
    cu,cv : complex;
begin
     my := Default(tpolycomplex);

     _cursor_watch;
     my.init;
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := finput^.getline (z,bl);
                         v := finput^.getline (z,bl+1);
                         if u.z = v.z then rl := rl + (v.x+u.x)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.put (my.length+1,gc(v.z,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
     if my.length > 1 then
     begin
          cu := my.get (1);
          for l := 2 to my.length do
          begin
               cv := my.get(l);
               rl := (cv.x-cu.x)*((cv.y+cu.y)/2); { Mittelwert zwischen zwei Werten }
               dummy.newpoint (gh(0,0,cv.x,rl));
               cu := cv;
          end;
          dummy.newline (0);
          dummy.newobject ('volumes_along_z');
          cleanup (dummy);
          tmacro(macro^).writeredo ('calculate.polyeder.volume.z');
     end;
     my.done;
     _cursor_arrow;
end;

{ *************************** First/Last Points/Lines ************************ }

procedure proc_move_first_object_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     l := 1;
                     if finput^.getlinepointlength (o,l) > 0 then
                     begin
                          p := 1;
                          dummy.newpoint(finput^.getobject (o,l,p));
                          finput^.markpoint (o,l,p);
                     end;
                     dummy.newline (finput^.getmaterial (o,l));
                end;
               dummy.newobject (finput^.getname (o));
           end;
           finput^.erasemarked;
           cleanup (dummy);
           tmacro(macro^).writeredo ('calculate.extract.first.points');
      end;
end;

procedure proc_move_last_object_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     l := 1;
                     p := finput^.getlinepointlength (o,l);
                     if p > 0 then
                     begin
                          dummy.newpoint(finput^.getobject (o,l,p));
                          finput^.markpoint (o,l,p);
                     end;
                     dummy.newline (finput^.getmaterial (o,l));
                end;
               dummy.newobject (finput^.getname (o));
           end;
           finput^.erasemarked;
           cleanup (dummy);
           tmacro(macro^).writeredo ('calculate.extract.last.points');
      end;
end;

procedure proc_move_first_object_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     l := 1;
                     if finput^.getlinepointlength (o,l) > 0 then
                     begin
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               dummy.newpoint(finput^.getobject (o,l,p));
                          end;
                     end;
                     dummy.newline (finput^.getmaterial (o,l));
                     finput^.markline (o,l);
                end;
               dummy.newobject (finput^.getname (o));
           end;
           finput^.erasemarked;
           cleanup (dummy);
           tmacro(macro^).writeredo ('calculate.extract.first.lines');
      end;
end;

procedure proc_move_last_object_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           dummy.clear;
           for o := 1 to finput^.getobjectlength do
           begin
                l := finput^.getobjectlinelength (o);
                if l > 0 then
                begin
                     if finput^.getlinepointlength (o,l) > 0 then
                     begin
                          for p := 1 to finput^.getlinepointlength (o,l) do
                          begin
                               dummy.newpoint(finput^.getobject (o,l,p));
                          end;
                     end;
                     dummy.newline (finput^.getmaterial (o,l));
                     finput^.markline (o,l);
                end;
               dummy.newobject (finput^.getname (o));
           end;
           finput^.erasemarked;
           cleanup (dummy);
           tmacro(macro^).writeredo ('calculate.extract.last.lines');
      end;
end;
