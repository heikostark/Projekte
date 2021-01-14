{ **************************************************************************** }
{ ********************************* Edit ************************************* }
{ **************************************************************************** }

{ ***************************** Erase single points ************************** }
{ +EDIT }
procedure proc_erase_single_points (p1,macro : gtk_pointer); cdecl;
var count1,count2,numbers,neighbors,r : integer;
    d,n : real;
    my : tpolycomplex;
begin
     my := Default (tpolycomplex);

     numbers := _getnat (edit_erase_single_numbers,macro,1);
     neighbors := _getnat (edit_erase_single_neighbors,macro,2);
     if neighbors <= 0 then neighbors := 1000;
     if (numbers > 0) and (finput^.getpointlength > 0) then
     begin
           _cursor_watch;
           my.init (finput^.getpointlength);
           for count1 := 1 to finput^.getpointlength do
           begin
                d := infinity;
                for count2 := 1 to 1000 do
                begin
                     r := random(finput^.getpointlength)+1;
                     if r <> count1 then
                     begin
                          n := getlength((finput^.getpoint (count1)-finput^.getpoint (r)));
                          if d > n then d := n;
                     end;
                end;
                my.put (count1,gc(count1,d));
                progress ('Calculate neighbors',count1/finput^.getpointlength);
           end;
           progress;
           my.sorty;
           if numbers > 0 then
           begin
                for count1 := 0 to numbers-1 do
                begin
                     my.put (my.length-count1,gc(my.get(my.length-count1).x,0));
                     progress ('Erase points',count1/numbers);
                end;
                progress;
           end;
           for count1 := 1 to finput^.getpointlength do
               if my.get(count1).y = 0 then finput^.markallpoint(round(my.get(count1).x));
           finput^.erasemarked;
           my.done;
           calculating; { %% %% }
           updating;
           drawing;
           _cursor_arrow;
           tmacro(macro^).writeredo ('edit.erase.single.points',getstring(numbers)+' '+getstring(neighbors));
     end;
end;

{ **************************************************************************** }

procedure proc_points_to_vectors (p1,macro : gtk_pointer); cdecl;
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
                         if finput^.getlinepointlength (o,l) > 1 then { lines }
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do dummy.newpoint (finput^.getobject (o,l,p));
                              dummy.newline (finput^.getmaterial (o,l));
                         end
                         else if finput^.getlinepointlength (o,l) = 1 then { save point }
                         begin
                              dummy.newpoint (Hzero);
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;

                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.points.to.vectors');
     end;
end;

{ ******************************* Assign ************************************* }

procedure proc_assign_layer (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v,center : hyper;
procedure writeone (move : hyper);
var o,l,p : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
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
                                   h := finput^.getobject(o,l,p);
                                   dummy.newpoint (h+move);
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
     end;
end;

begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          center := finput^.center;
          dummy.clear;
          if finputedit^.getobjectlength > 0 then
          begin
               for o := 1 to finputedit^.getobjectlength do
               begin
                    if finputedit^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finputedit^.getobjectlinelength (o) do
                         begin
                              if finputedit^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finputedit^.getlinepointlength (o,l) do
                                   begin
                                        v := finputedit^.getobject(o,l,p);
                                        writeone (v-center);
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          finputedit^.replace(dummy);
          dummy.clear;
          calculating; { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.assign.layer');
     end;
end;

procedure proc_assign_t (p1,macro : gtk_pointer); cdecl;
var len,p : integer;
    v,u : hyper;
begin
     len := finputedit^.getpointlength;
     if len > 0 then
     begin
          _cursor_watch;
          for p := 1 to len do
          begin
               progress ('Search neighbors',p/len);
               v := finputedit^.getpoint (p);
               u := finput^.searchall3dpoint(v);
               if u <> Hmin then
               begin
                    v.t := u.t;
                    finputedit^.putpoint (p,v);
               end;
          end;
          progress;
          calculating; { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.assign.t');
     end;
end;

procedure proc_assign_ranged_t (p1,macro : gtk_pointer); cdecl;
var len,p,c : integer;
    v,u : hyper;
    range : real;
begin
     len := finputedit^.getpointlength;
     if len > 0 then
     begin
          _cursor_watch;
          c := 0;
          range := _getreal (edit_assign_ranged,macro,1);
          for p := 1 to len do
          begin
               progress ('Search neighbors',p/len);
               v := finputedit^.getpoint (p);
               u := finput^.searchall3dpoint(v,range);
               if u <> Hmin then
               begin
                    v.t := u.t;
                    finputedit^.putpoint (p,v);
                    inc (c);
               end;
          end;
          progress;
          writeln (getstring(c)+' values assigned ('+getstring(len)+').');
          calculating; { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.assign.ranged.t',getstring(range));
     end;
end;

{ ********************************** T values  ******************************* }

procedure proc_lines_fillup_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    s,t : real;
    v : hyper;
    bl,bm,count : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              s := 0;
                              t := 0;
                              count := 0;
                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   if v.t <> 0 then
                                   begin
                                        s := t;
                                        t := v.t;
                                        if count > 0 then
                                        begin
                                             if s = 0 then { fillup first }
                                             begin
                                                  for bm := count-1 downto 0 do
                                                  begin
                                                       v := finput^.getobject (o,l,bl-bm);
                                                       dummy.newpoint (gh(v.x,v.y,v.z,t));
                                                  end;
                                             end
                                             else { fillup middle }
                                             begin
                                                  for bm := count-1 downto 0 do
                                                  begin
                                                       v := finput^.getobject (o,l,bl-bm);
                                                       dummy.newpoint (gh(v.x,v.y,v.z,minmax(1,count,bm,s,t)));
                                                  end;
                                             end;
                                        end
                                        else
                                        begin
                                             dummy.newpoint (gh(v.x,v.y,v.z,t));
                                        end;
                                        count := 0;
                                   end
                                   else inc (count);
                              end;
                              if count > 0 then { fillup last }
                              begin
                                   for bm := count-1 downto 0 do
                                   begin
                                        v := finput^.getobject (o,l,p-bm);
                                        dummy.newpoint (gh(v.x,v.y,v.z,t));
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.fillup.t');
     end;
end;

procedure proc_lines_mean_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    t : real;
    v : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              t := 0; c := 0;
                              for bl := 1 to p do
                              begin
                                   t := t + finput^.getobject (o,l,bl).t;
                                   inc (c);
                              end;
                              if c > 0 then t := t / c; { mean }
                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   v.t := t;
                                   dummy.newpoint (v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.mean.t');
     end;
end;

procedure proc_lines_sd_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    mean,sd : real;
    v : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              mean := 0; c := 0;
                              for bl := 1 to p do
                              begin
                                   mean := mean + finput^.getobject (o,l,bl).t;
                                   inc (c);
                              end;
                              if c > 0 then mean := mean / c; { mean }
                              sd := 0; c := 0;
                              for bl := 1 to p do
                              begin
                                   sd := sd + sqr(finput^.getobject (o,l,bl).t-mean);
                                   inc (c);
                              end;
                              if c > 1 then sd := sqrt(sd / (c-1)) { sd }
                                       else sd := 0;

                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   v.t := sd;
                                   dummy.newpoint (v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.sd.t');
     end;
end;

procedure proc_lines_min_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    t : real;
    v : hyper;
    bl : integer;
    mymin : real;
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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              mymin := infinitynat;
                              for bl := 1 to p do
                              begin
                                   t := finput^.getobject (o,l,bl).t;
                                   if t < mymin then mymin := t;
                              end;
                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   v.t := mymin;
                                   dummy.newpoint (v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.min.t');
     end;
end;

procedure proc_lines_median_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    t : real;
    v : hyper;
    bl : integer;
    list : tpolyreal;
begin
     list := Default (tpolyreal);

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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              list.init;
                              for bl := 1 to p do
                              begin
                                   t := finput^.getobject (o,l,bl).t;
                                   list.push (t);
                              end;
                              t := list.median;
                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   v.t := t;
                                   dummy.newpoint (v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                              list.done;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.median.t');
     end;
end;

procedure proc_lines_max_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    t : real;
    v : hyper;
    bl : integer;
    mymax : real;
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
                         p := finput^.getlinepointlength (o,l);
                         if  p > 0 then
                         begin
                              mymax := ninfinitynat;
                              for bl := 1 to p do
                              begin
                                   t := finput^.getobject (o,l,bl).t;
                                   if t > mymax then mymax := t;
                              end;
                              for bl := 1 to p do
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   v.t := mymax;
                                   dummy.newpoint (v);
                              end;
                              dummy.newline (finput^.getmaterial (o,l)); {newline}
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.max.t');
     end;
end;

{ **************************************************************************** }

procedure proc_lines_group (p1,macro : gtk_pointer); cdecl;
var l,p,l2,p2,m,vp,vp2 : integer;
    v,w : hyper;
    mark : tpolybool;
begin
     mark := Default (tpolybool);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;

          for l := 1 to finput^.getlinelength do
          begin
               finput^.putallmaterial(l,l);
          end;

          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               m := finput^.getallmaterial(l);
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         v := finput^.getpoint(vp);
                         mark.put (vp,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        if getlength(v-w) = 0.0 then
                                        begin
                                             mark.put (vp2,true);
                                             finput^.putallmaterial(l2,m);
                                        end;
                                   end;
                              end;
                         end;
                         progress ('Find duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;

          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.group');
     end;
end;

procedure proc_lines_group_3d (p1,macro : gtk_pointer); cdecl;
var l,p,l2,p2,m,vp,vp2 : integer;
    v,w : hyper;
    mark : tpolybool;
begin
     mark := Default (tpolybool);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;

          for l := 1 to finput^.getlinelength do
          begin
               finput^.putallmaterial(l,l);
          end;

          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               m := finput^.getallmaterial(l);
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         v := finput^.getpoint(vp);
                         v.t := 0;
                         mark.put (vp,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        w.t := 0;
                                        if getlength(v-w) = 0.0 then
                                        begin
                                             mark.put (vp2,true);
                                             finput^.putallmaterial(l2,m);
                                        end;
                                   end;
                              end;
                         end;
                         progress ('Find duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;

          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.group.3d');
     end;
end;

{ **************************************************************************** }

procedure proc_lines_average_x (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v1,v2,v3 : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if p > 0 then
                         begin
                              if p > 2 then
                              begin
                                   { first }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { begin loop }
                                   begin
                                        v2 := finput^.getobject (o,l,1);
                                        dummy.newpoint (gh((finput^.getobject (o,l,p).x+v2.x+finput^.getobject (o,l,2).x)/3,v2.y,v2.z,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,1));
                                   v1 := finput^.getobject (o,l,1);
                                   v2 := finput^.getobject (o,l,2);
                                   for bl := 2 to p-1 do
                                   begin
                                        v3 := finput^.getobject (o,l,bl+1);
                                        dummy.newpoint (gh((v1.x+v2.x+v3.x)/3,v2.y,v2.z,v2.t));
                                        v1 := v2;
                                        v2 := v3;
                                   end;
                                   { last }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { end loop }
                                   begin
                                        v2 := finput^.getobject (o,l,p);
                                        dummy.newpoint (gh((finput^.getobject (o,l,p-1).x+v2.x+finput^.getobject (o,l,1).x)/3,v2.y,v2.z,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end
                              else { one or two points }
                              begin
                                   for bl := 1 to p do dummy.newpoint (finput^.getobject (o,l,bl));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.average.x');
     end;
end;

procedure proc_lines_average_y (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v1,v2,v3 : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if p > 0 then
                         begin
                              if p > 2 then
                              begin
                                   { first }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { begin loop }
                                   begin
                                        v2 := finput^.getobject (o,l,1);
                                        dummy.newpoint (gh(v2.x,(finput^.getobject (o,l,p).y+v2.y+finput^.getobject (o,l,2).y)/3,v2.z,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,1));
                                   v1 := finput^.getobject (o,l,1);
                                   v2 := finput^.getobject (o,l,2);
                                   for bl := 2 to p-1 do
                                   begin
                                        v3 := finput^.getobject (o,l,bl+1);
                                        dummy.newpoint (gh(v2.x,(v1.y+v2.y+v3.y)/3,v2.z,v2.t));
                                        v1 := v2;
                                        v2 := v3;
                                   end;
                                   { last }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { end loop }
                                   begin
                                        v2 := finput^.getobject (o,l,p);
                                        dummy.newpoint (gh(v2.x,(finput^.getobject (o,l,p-1).y+v2.y+finput^.getobject (o,l,1).y)/3,v2.z,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end
                              else { one or two points }
                              begin
                                   for bl := 1 to p do dummy.newpoint (finput^.getobject (o,l,bl));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.average.y');
     end;
end;

procedure proc_lines_average_z (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v1,v2,v3 : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if p > 0 then
                         begin
                              if p > 2 then
                              begin
                                   { first }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { begin loop }
                                   begin
                                        v2 := finput^.getobject (o,l,1);
                                        dummy.newpoint (gh(v2.x,v2.y,(finput^.getobject (o,l,p).z+v2.z+finput^.getobject (o,l,2).z)/3,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,1));
                                   v1 := finput^.getobject (o,l,1);
                                   v2 := finput^.getobject (o,l,2);
                                   for bl := 2 to p-1 do
                                   begin
                                        v3 := finput^.getobject (o,l,bl+1);
                                        dummy.newpoint (gh(v2.x,v2.y,(v1.z+v2.z+v3.z)/3,v2.t));
                                        v1 := v2;
                                        v2 := v3;
                                   end;
                                   { last }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { end loop }
                                   begin
                                        v2 := finput^.getobject (o,l,p);
                                        dummy.newpoint (gh(v2.x,v2.y,(finput^.getobject (o,l,p-1).z+v2.z+finput^.getobject (o,l,1).z)/3,v2.t));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end
                              else { one or two points }
                              begin
                                   for bl := 1 to p do dummy.newpoint (finput^.getobject (o,l,bl));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.average.z');
     end;
end;

procedure proc_lines_average_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v1,v2,v3 : hyper;
    bl : integer;
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
                         p := finput^.getlinepointlength (o,l);
                         if p > 0 then
                         begin
                              if p > 2 then
                              begin
                                   { first }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { begin loop }
                                   begin
                                        v2 := finput^.getobject (o,l,1);
                                        dummy.newpoint (gh(v2.x,v2.y,v2.z,(finput^.getobject (o,l,p).t+v2.t+finput^.getobject (o,l,2).t)/3));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,1));
                                   v1 := finput^.getobject (o,l,1);
                                   v2 := finput^.getobject (o,l,2);
                                   for bl := 2 to p-1 do
                                   begin
                                        v3 := finput^.getobject (o,l,bl+1);
                                        dummy.newpoint (gh(v2.x,v2.y,v2.z,(v1.t+v2.t+v3.t)/3));
                                        v1 := v2;
                                        v2 := v3;
                                   end;
                                   { last }
                                   if finput^.getobject (o,l,1) = finput^.getobject (o,l,p) then { end loop }
                                   begin
                                        v2 := finput^.getobject (o,l,p);
                                        dummy.newpoint (gh(v2.x,v2.y,v2.z,(finput^.getobject (o,l,p-1).t+v2.t+finput^.getobject (o,l,1).t)/3));
                                   end
                                   else dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end
                              else { one or two points }
                              begin
                                   for bl := 1 to p do dummy.newpoint (finput^.getobject (o,l,bl));
                                   dummy.newline (finput^.getmaterial (o,l)); {newline}
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.average.t');
     end;
end;

{ ******************************* near values  ******************************* }

procedure proc_groups_mean_near_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,bl,c : integer;
    v : hyper;
    r : real;
    points : tpolyhyper;
begin
     points := Default (tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (edit_near,macro,1);
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
                                   points.init;
                                   finput^.searchallpoints(v,c);
                                   if points.length > 0 then
                                   begin
                                        r := 0;
                                        for bl := 1 to points.length do r := r + points.get (bl).x;
                                        r := r / points.length;
                                        finput^.putobject(o,l,p,gh(r,v.y,v.z,v.t));
                                   end;
                                   points.done;
                              end;
                         end;
                    end;
               end;
          end;             { ## ## }
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.groups.mean.near.x',getstring(c));
     end;
end;

procedure proc_groups_mean_near_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,bl,c : integer;
    v : hyper;
    r : real;
    points : tpolyhyper;
begin
     points := Default (tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (edit_near,macro,1);
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
                                   points.init;
                                   finput^.searchallpoints(v,c);
                                   if points.length > 0 then
                                   begin
                                        r := 0;
                                        for bl := 1 to points.length do r := r + points.get (bl).y;
                                        r := r / points.length;
                                        finput^.putobject(o,l,p,gh(v.x,r,v.z,v.t));
                                   end;
                                   points.done;
                              end;
                         end;
                    end;
               end;
          end;             { ## ## }
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.groups.mean.near.y',getstring(c));
     end;
end;

procedure proc_groups_mean_near_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,bl,c : integer;
    v : hyper;
    r : real;
    points : tpolyhyper;
begin
     points := Default (tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (edit_near,macro,1);
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
                                   points.init;
                                   finput^.searchallpoints(v,c);
                                   if points.length > 0 then
                                   begin
                                        r := 0;
                                        for bl := 1 to points.length do r := r + points.get (bl).z;
                                        r := r / points.length;
                                        finput^.putobject(o,l,p,gh(v.x,v.y,r,v.t));
                                   end;
                                   points.done;
                              end;
                         end;
                    end;
               end;
          end;             { ## ## }
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.groups.mean.near.z',getstring(c));
     end;
end;

procedure proc_groups_mean_near_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,bl,c : integer;
    v : hyper;
    r : real;
    points : tpolyhyper;
begin
     points := Default (tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (edit_near,macro,1);
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
                                   points.init;
                                   finput^.searchallpoints(v,c);
                                   if points.length > 0 then
                                   begin
                                        r := 0;
                                        for bl := 1 to points.length do r := r + points.get (bl).t;
                                        r := r / points.length;
                                        finput^.putobject(o,l,p,gh(v.x,v.y,v.z,r));
                                   end;
                                   points.done;
                              end;
                         end;
                    end;
               end;
          end;             { ## ## }
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.groups.mean.near.t',getstring(c));
     end;
end;

{ ************************* Erase short lines ******************************** }
{ +EDIT }
procedure proc_erase_short_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c,len : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getreal (editl,macro,1);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              len := 0;
                              for p := 1 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                              end;
                              if len < c then finput^.markline (o,l);
                         end;
                    end;
               end;
          end;
          finput^.erasemarked;
          calculating;  { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.short.lines',getstring(c));
     end;
end;

{ ******************************* Erase long Lines *************************** }
{ +EDIT}
procedure proc_erase_long_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c,len : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getreal (editl,macro,1);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              len := 0;
                              for p := 1 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                              end;
                              if len > c then finput^.markline (o,l);
                         end;
                    end;
               end;
          end;
          finput^.erasemarked;
          calculating; { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.long.lines',getstring(c));
     end;
end;

{ ************************* Erase short Points ******************************** }
{ +EDIT }
procedure proc_erase_short_plines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    c : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (editlp,macro,1);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              if finput^.getlinepointlength(o,l) < c then finput^.markline (o,l);
                         end;
                    end;
               end;
          end;
          finput^.erasemarked;
          calculating;  { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.short.points',getstring(c));
     end;
end;

{ ******************************* Erase long Points *************************** }
{ +EDIT}
procedure proc_erase_long_plines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    c : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (editlp,macro,1);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              if finput^.getlinepointlength (o,l) > c then finput^.markline (o,l);
                         end;
                    end;
               end;
          end;
          finput^.erasemarked;
          calculating; { %% %% }
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.long.points',getstring(c));
     end;
end;

{ ************************* Trim lines begin ********************************* }
{ +EDIT }
procedure proc_trim_begin_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,n : integer;
    c,len : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          c := _getreal (editl,macro,1);
          if c > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   len := 0;
                                   n := 1;
                                   for p := finput^.getlinepointlength (o,l) downto 2 do
                                   begin
                                        len := len + getlength(finput^.getobject(o,l,p)-finput^.getobject(o,l,p-1));
                                        if len <= c then n := p-1;
                                   end;

                                   for p := n to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end;
                         end;
                         dummy.newobject(finput^.getname(o));
                    end;
               end;
               finput^.replace (dummy);
               dummy.clear;
               calculating;
               updating;
               drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.begin.lines',getstring(c));
     end;
end;

{ ************************* Trim lines both ********************************** }
{ +EDIT }
procedure proc_trim_both_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,n : integer;
    c,len,rest : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          c := _getreal (editl,macro,1);
          if c > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   { begin and end }
                                   len := 0;
                                   for p := 1 to finput^.getlinepointlength (o,l)-1 do
                                   begin
                                        len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                                   end;

                                   if len > c then
                                   begin
                                        rest := len-c;
                                        len := 0;
                                        n := 1;
                                        for p := finput^.getlinepointlength (o,l) downto 2 do
                                        begin
                                             len := len + getlength(finput^.getobject(o,l,p)-finput^.getobject(o,l,p-1));
                                             if len <= c+(rest/2) then n := p-1;
                                        end;

                                        { begin and end }
                                        len := 0;
                                        dummy.newpoint (finput^.getobject (o,l,n));
                                        for p := n to finput^.getlinepointlength (o,l)-1 do
                                        begin
                                             len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                                             if len <= c then dummy.newpoint (finput^.getobject (o,l,p+1));
                                        end;
                                   end
                                   else
                                   begin
                                        for p := 1 to finput^.getlinepointlength (o,l) do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end;
                         end;
                         dummy.newobject(finput^.getname(o));
                    end;
               end;
               finput^.replace (dummy);
               dummy.clear;
               calculating;
               updating;
               drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.both.lines',getstring(c));
     end;
end;

{ ************************* Trim lines end *********************************** }
{ +EDIT }
procedure proc_trim_end_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c,len : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          c := _getreal (editl,macro,1);
          if c > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   len := 0;
                                   for p := 1 to finput^.getlinepointlength (o,l)-1 do
                                   begin
                                        len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                                   end;

                                   if len > c then
                                   begin
                                        len := 0;
                                        dummy.newpoint (finput^.getobject (o,l,1));
                                        for p := 1 to finput^.getlinepointlength (o,l)-1 do
                                        begin
                                             len := len + getlength(finput^.getobject(o,l,p+1)-finput^.getobject(o,l,p));
                                             if len <= c then dummy.newpoint (finput^.getobject (o,l,p+1));
                                        end;
                                   end
                                   else
                                   begin
                                        for p := 1 to finput^.getlinepointlength (o,l) do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end;
                         end;
                         dummy.newobject(finput^.getname(o));
                    end;
               end;
               finput^.replace (dummy);
               dummy.clear;
               calculating;
               updating;
               drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.end.lines',getstring(c));
     end;
end;

{ ******************************* Trim Points begin **************************** }
{ +EDIT}
procedure proc_trim_begin_plines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (editlp,macro,1);
          if c > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   if finput^.getlinepointlength (o,l) > c then
                                   begin
                                        for p := finput^.getlinepointlength (o,l)-c+1 to finput^.getlinepointlength (o,l) do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end
                                   else
                                   begin
                                        for p := 1 to finput^.getlinepointlength (o,l) do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end;
                         end;
                         dummy.newobject(finput^.getname(o));
                    end;
               end;
               finput^.replace (dummy);
               dummy.clear;
               calculating;
               updating;
               drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.begin.points',getstring(c));
     end;
end;

{ ******************************* Trim Points both **************************** }
{ +EDIT}
procedure proc_trim_both_plines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c,c1,c2 : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (editlp,macro,1);
          if c > 0 then
          begin
                for o := 1 to finput^.getobjectlength do
                begin
                     if finput^.getobjectlinelength (o) > 0 then
                     begin
                          for l := 1 to finput^.getobjectlinelength (o) do
                          begin
                               if finput^.getlinepointlength (o,l) > 1 then
                               begin
                                    if finput^.getlinepointlength (o,l) > c then
                                    begin
                                         c1 := (finput^.getlinepointlength (o,l)-c) div 2;
                                         c2 := (finput^.getlinepointlength (o,l)-c) - c1;
                                         if (c1+1) <= (finput^.getlinepointlength (o,l)-c2) then
                                         for p := c1+1 to finput^.getlinepointlength (o,l)-c2 do
                                         begin
                                              dummy.newpoint (finput^.getobject (o,l,p));
                                         end;
                                    end
                                    else
                                    begin
                                         for p := 1 to finput^.getlinepointlength (o,l) do
                                         begin
                                              dummy.newpoint (finput^.getobject (o,l,p));
                                         end;
                                    end;
                                    dummy.newline (finput^.getmaterial (o,l)); { newline }
                               end
                               else if finput^.getlinepointlength (o,l) = 1 then
                               begin
                                    dummy.newpoint (finput^.getobject (o,l,1));
                                    dummy.newline (finput^.getmaterial (o,l)); { newline }
                               end;
                          end;
                          dummy.newobject(finput^.getname(o));
                     end;
                end;
                finput^.replace (dummy);
                dummy.clear;
                calculating;
                updating;
                drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.both.points',getstring(c));
     end;
end;

{ ******************************* Trim Points end **************************** }
{ +EDIT}
procedure proc_trim_end_plines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    c : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          c := _getnat (editlp,macro,1);
          if c > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   if finput^.getlinepointlength (o,l) > c then
                                   begin
                                        for p := 1 to c do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end
                                   else
                                   begin
                                        for p := 1 to finput^.getlinepointlength (o,l) do
                                        begin
                                             dummy.newpoint (finput^.getobject (o,l,p));
                                        end;
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l)); { newline }
                              end;
                         end;
                         dummy.newobject(finput^.getname(o));
                    end;
               end;
               finput^.replace (dummy);
               dummy.clear;
               calculating;
               updating;
               drawing;
          end
          else c := 0;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.trim.end.points',getstring(c));
     end;
end;

{ ******************************* Achsen löschen ***************************** }
{ +EDIT }
procedure proc_clear_x (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint (z);
               finput^.putpoint (z,gh(0,v.y,v.z,v.t));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.clear.x');
     end;
end;

procedure proc_clear_y (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint (z);
               finput^.putpoint (z,gh(v.x,0,v.z,v.t));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.clear.y');
     end;
end;

procedure proc_clear_z (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint (z);
               finput^.putpoint (z,gh(v.x,v.y,0,v.t));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.clear.z');
     end;
end;

procedure proc_clear_t (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint (z);
               finput^.putpoint (z,gh(v.x,v.y,v.z,0));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.clear.t');
     end;
end;

{ ************************* Vector Achsen löschen **************************** }
{ +EDIT }
procedure proc_vector_clear_origin (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) = 2 then
                    begin
                         v := finput^.getobject(o,l,1);
                         finput^.putobject(o,l,1,Hzero);
                         u := finput^.getobject(o,l,2);
                         finput^.putobject(o,l,2,gh(u.x-v.x,u.y-v.y,u.z-v.z,u.t-v.t));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.clear');
     end;
end;

procedure proc_vector_clear_x (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) = 2 then
                    begin
                         v := finput^.getobject(o,l,1);
                         finput^.putobject(o,l,1,gh(0,v.y,v.z,v.t));
                         u := finput^.getobject(o,l,2);
                         finput^.putobject(o,l,2,gh(u.x-v.x,u.y,u.z,u.t));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.clear.x');
     end;
end;

procedure proc_vector_clear_y (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) = 2 then
                    begin
                         v := finput^.getobject(o,l,1);
                         finput^.putobject(o,l,1,gh(v.y,0,v.z,v.t));
                         u := finput^.getobject(o,l,2);
                         finput^.putobject(o,l,2,gh(u.x,u.y-v.y,u.z,u.t));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.clear.y');
     end;
end;

procedure proc_vector_clear_z (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) = 2 then
                    begin
                         v := finput^.getobject(o,l,1);
                         finput^.putobject(o,l,1,gh(v.x,v.y,0,v.t));
                         u := finput^.getobject(o,l,2);
                         finput^.putobject(o,l,2,gh(u.x,u.y,u.z-v.z,u.t));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.clear.z');
     end;
end;

procedure proc_vector_clear_t (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    if finput^.getlinepointlength (o,l) = 2 then
                    begin
                         v := finput^.getobject(o,l,1);
                         finput^.putobject(o,l,1,gh(v.x,v.y,v.z,v.t));
                         u := finput^.getobject(o,l,2);
                         finput^.putobject(o,l,2,gh(u.x,u.y,u.z,u.t-v.t));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.clear.t');
     end;
end;

{ ****************************** Add vectors ********************************* }
{ +Edit }
procedure proc_local_add_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,l1 : integer;
    v,u : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Add local vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := Hzero; uc := 0;
                                   for l1 := 1 to finput^.getobjectlinelength (o) do
                                   begin
                                        if finput^.getlinepointlength (o,l1) = 2 then
                                        begin
                                             if v = finput^.getobject (o,l1,1) then
                                             begin
                                                  u := u + (finput^.getobject (o,l1,2)-finput^.getobject (o,l1,1));
                                                  inc (uc);
                                                  finput^.markpoint(o,l1,1);
                                                  finput^.markpoint(o,l1,2);
                                             end;
                                        end;
                                   end;
                                   if uc > 0 then
                                   begin
                                        finput^.putobject (o,l,1,v);
                                        finput^.putobject (o,l,2,v+u);
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.local.add.vectors');
     end;
end;

procedure proc_global_add_vectors (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u,w : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    u := Hzero; w := Hzero; uc := 0;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Add global vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := u + (finput^.getobject (o,l,2)-v);
                                   w := w + v;
                                   inc (uc);
                                   finput^.markpoint(o,l,1);
                                   finput^.markpoint(o,l,2);
                              end;
                         end;
                    end;
                    if uc > 0 then
                    begin
                         finput^.putobject (o,l,1,(w/uc));
                         finput^.putobject (o,l,2,(w/uc)+u);
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.global.add.vectors');
     end;
end;

{ ****************************** Subtract vectors **************************** }
{ +Edit }
procedure proc_local_subtract_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,l1 : integer;
    v,u : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Subtract local vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := Hzero; uc := 0;
                                   for l1 := 1 to finput^.getobjectlinelength (o) do
                                   begin
                                        if finput^.getlinepointlength (o,l1) = 2 then
                                        begin
                                             if v = finput^.getobject (o,l1,1) then
                                             begin
                                                  u := u - (finput^.getobject (o,l1,2)-finput^.getobject (o,l1,1));
                                                  inc (uc);
                                                  finput^.markpoint(o,l1,1);
                                                  finput^.markpoint(o,l1,2);
                                             end;
                                        end;
                                   end;
                                   if uc > 0 then
                                   begin
                                        finput^.putobject (o,l,1,v);
                                        finput^.putobject (o,l,2,v+u);
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.local.subtract.vectors');
     end;
end;

procedure proc_global_subtract_vectors (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u,w : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    u := Hzero; w := Hzero; uc := 0;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Subtract global vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := u - (finput^.getobject (o,l,2)-v);
                                   w := w + v;
                                   inc (uc);
                                   finput^.markpoint(o,l,1);
                                   finput^.markpoint(o,l,2);
                              end;
                         end;
                    end;
                    if uc > 0 then
                    begin
                         finput^.putobject (o,l,1,(w/uc));
                         finput^.putobject (o,l,2,(w/uc)+u);
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.global.subtract.vectors');
     end;
end;

{ ***************************** Mean vectors ********************************* }
{ +Edit }
procedure proc_local_mean_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,l1 : integer;
    v,u : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Mean local vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := Hzero; uc := 0;
                                   for l1 := 1 to finput^.getobjectlinelength (o) do
                                   begin
                                        if finput^.getlinepointlength (o,l1) = 2 then
                                        begin
                                             if v = finput^.getobject (o,l1,1) then
                                             begin
                                                  u := u + (finput^.getobject (o,l1,2)-finput^.getobject (o,l1,1));
                                                  inc (uc);
                                                  finput^.markpoint(o,l1,1);
                                                  finput^.markpoint(o,l1,2);
                                             end;
                                        end;
                                   end;
                                   if uc > 0 then
                                   begin
                                        finput^.putobject (o,l,1,v);
                                        finput^.putobject (o,l,2,v+(u/uc));
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.local.mean.vectors');
     end;
end;

procedure proc_global_mean_vectors (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    v,u,w : hyper;
    uc : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    u := Hzero; w := Hzero; uc := 0;
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         progress ('Mean global vectors',finput^.getpobject(o,l,2)/finput^.getpointlength);
                         if finput^.getlinepointlength (o,l) = 2 then
                         begin
                              v := finput^.getobject (o,l,1);
                              if v <> Hmax then { if not marked }
                              begin
                                   u := u + (finput^.getobject (o,l,2)-v);
                                   w := w + v;
                                   inc (uc);
                                   finput^.markpoint(o,l,1);
                                   finput^.markpoint(o,l,2);
                              end;
                         end;
                    end;
                    if uc > 0 then
                    begin
                         finput^.putobject (o,l,1,(w/uc));
                         finput^.putobject (o,l,2,(w/uc)+(u/uc));
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.global.mean.vectors');
     end;
end;

{ ************************* Subobject verlaengern **************************** }
{ +EDIT }
procedure make_longer (var line : tpolyhyper;long : real);
var linepoly : tpolynom4d;
    bl : integer;
    v : hyper;
    counter,factor : real;
begin
     linepoly := Default (tpolynom4d);

     if line.length > 1 then
     begin
          v := long*norm(line.get (line.length)-line.get (line.length-1));
          line.newlength (line.length+1);
          line.put (line.length,line.get (line.length-1)+v);
          if line.length < 9 then
          begin
               linepoly.init (line.length);
               linepoly.getpolynom (line);
          end
          else
          begin
               linepoly.init (9);
               linepoly.getpolynom (line);
          end;
          factor := (linepoly.pathlength)/(line.length-2);
          if factor > 0 then
          begin
               counter := 0;
               for bl := 0 to line.length-2 do
               begin
                    v := linepoly.polynom (counter);
                    counter := counter + factor;
                    line.put (bl+1,v);
               end;
          end;
          linepoly.done;
     end;
end;

procedure proc_grow_left (p1,macro : gtk_pointer); cdecl;
var bl,l : integer;
    line : tpolyhyper;
    len : real;
begin
     line := Default (tpolyhyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          len := _getreal (transform_grow,macro,1);
          l := finput^.getalllinepointlength(finput^.linecounter);
          if l > 1 then
          begin
               line.init (l);
               for bl := 1 to l do
               begin
                    line.put (bl,finput^.getline (finput^.linecounter,bl));
               end;
               make_longer (line,len);
               for bl := 1 to l do
               begin
                    finput^.putline (finput^.linecounter,bl,line.get(bl));
               end;
               line.done;
               calculating;
               updating;
               drawing;
          end;
          tmacro(macro^).writeredo ('edit.grow.left',getstring(len));
          _cursor_arrow;
     end;
end;

{ ************************* Subobject verkuerzen ***************************** }

procedure make_shorter (var line : tpolyhyper;short : real);
var linepoly : tpolynom4d;
    bl : integer;
    v,v1 : hyper;
    counter,factor : real;
begin
     linepoly := Default (tpolynom4d);

     if line.length > 1 then
     begin
          v := line.get (line.length)-line.get (line.length-1);
          if getlength (v) < short then
          begin
                v1 := short*norm(v);
                line.newlength (line.length+1);
                line.put (line.length,line.get (line.length-1)-v1);
                if line.length < 9 then
                begin
                     linepoly.init (line.length);
                     linepoly.getpolynom (line);
                end
                else
                begin
                     linepoly.init (9);
                     linepoly.getpolynom (line);
                end;
                factor := (linepoly.pathlength)/(line.length-2);
                if factor > 0 then
                begin
                     counter := 0;
                     for bl := 0 to line.length-2 do
                     begin
                          v := linepoly.polynom (counter);
                          counter := counter + factor;
                          line.put (bl+1,v);
                     end;
                end;
                linepoly.done;
          end;
     end;
end;

procedure proc_reduce_left (p1,macro : gtk_pointer); cdecl;
var bl,l : integer;
    line : tpolyhyper;
    len : real;
begin
     line := Default (tpolyhyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          len := _getreal (transform_grow,macro,1);
          l := finput^.getalllinepointlength(finput^.linecounter);
          if l > 1 then
          begin
               line.init (l);
               for bl := 1 to l do
               begin
                    line.put (bl,finput^.getline (finput^.linecounter,bl));
               end;
               make_shorter (line,len);
               for bl := 1 to l do
               begin
                    finput^.putline (finput^.linecounter,bl,line.get(bl));
               end;
               line.done;
               calculating;
               updating;
               drawing;
          end;
          tmacro(macro^).writeredo ('edit.reduce.left',getstring(len));
          _cursor_arrow;
     end;
end;

{ ************************* Subobject verlaengern **************************** }

procedure proc_grow_right (p1,macro : gtk_pointer); cdecl;
var bl,l : integer;
    line : tpolyhyper;
    len : real;
begin
     line := Default (tpolyhyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          len := _getreal (transform_grow,macro,1);
          l := finput^.getalllinepointlength(finput^.linecounter);
          if l > 1 then
          begin
               line.init (l);
               for bl := l downto 1 do
               begin
                    line.put (bl,finput^.getline (finput^.linecounter,l-bl+1));
               end;
               make_longer (line,len);
               for bl := l downto 1 do
               begin
                    finput^.putline (finput^.linecounter,l-bl+1,line.get(bl));
               end;
               line.done;
               calculating;
               updating;
               drawing;
          end;
          tmacro(macro^).writeredo ('edit.grow.right',getstring(len));
          _cursor_arrow;
     end;
end;

{ ************************* Subobject verkuerzen ***************************** }

procedure proc_reduce_right (p1,macro : gtk_pointer); cdecl;
var bl,l : integer;
    line : tpolyhyper;
    len : real;
begin
     line := Default (tpolyhyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          len := _getreal (transform_grow,macro,1);
          l := finput^.getalllinepointlength(finput^.linecounter);
          if l > 1 then
          begin
               line.init (l);
               for bl := l downto 1 do
               begin
                    line.put (bl,finput^.getline (finput^.linecounter,l-bl+1));
               end;
               make_shorter (line,len);
               for bl := l downto 1 do
               begin
                    finput^.putline (finput^.linecounter,l-bl+1,line.get(bl));
               end;
               line.done;
               calculating;
               updating;
               drawing;
          end;
          tmacro(macro^).writeredo ('edit.reduce.right',getstring(len));
          _cursor_arrow;
     end;
end;

{ **************************************** Vector **************************** }

procedure proc_edit_norm (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := norm(v-u);
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.norm');
     end;
end;

procedure proc_edit_normscale (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    r : real;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          r := _getreal (edit_scale,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := norm(v-u)*r;
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.normscale',getstring(r));
     end;
end;

procedure proc_edit_scale (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    r : real;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          r := _getreal (edit_scale,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := (v-u)*r;
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writereundo ('edit.vectors.scale',getstring(r),'edit.vectors.invscale',getstring(r));
     end;
end;

procedure proc_edit_invscale (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    r,newr : real;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          r := _getreal (edit_scale,macro,1);
          if r <> 0 then newr := 1/r
                    else newr := 0;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := (v-u)*newr;
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writereundo ('edit.vectors.invscale',getstring(r),'edit.vectors.scale',getstring(r));
     end;
end;

procedure proc_edit_minscale (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    r,min : real;
    l,pos : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          min := infinity;
          pos := 0;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    r := getlength(v-u);
                    if r < min then
                    begin
                         min := r;
                         pos := l;
                    end;
               end;
          end;
          if pos > 0 then
          begin
               r := 1/min;
               for l := 1 to finput^.getlinelength do
               begin
                    if finput^.getalllinepointlength (l) = 2 then
                    begin
                         u := finput^.getline (l,1);
                         v := finput^.getline (l,2);
                         z := (v-u)*r;
                         finput^.putline (l,2,u+z);
                    end;
               end;
               calculating;
               updating;
               drawing;
               tmacro(macro^).writeredo ('edit.vectors.minscale');
          end
          else tmacro(macro^).writeredo ('// edit.vectors.minscale // no vectors');
          _cursor_arrow;
     end;
end;

procedure proc_edit_maxscale (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    r,max : real;
    l,pos : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          max := ninfinity;
          pos := 0;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    r := getlength(v-u);
                    if r > max then
                    begin
                         max := r;
                         pos := l;
                    end;
               end;
          end;
          if pos > 0 then
          begin
               r := 1/max;
               for l := 1 to finput^.getlinelength do
               begin
                    if finput^.getalllinepointlength (l) = 2 then
                    begin
                         u := finput^.getline (l,1);
                         v := finput^.getline (l,2);
                         z := (v-u)*r;
                         finput^.putline (l,2,u+z);
                    end;
               end;
               calculating;
               updating;
               drawing;
               tmacro(macro^).writeredo ('edit.vectors.maxscale');
          end
          else tmacro(macro^).writeredo ('// edit.vectors.maxscale // no vectors');
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }

procedure proc_edit_negate (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := -1*(v-u);
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.negate');
     end;
end;

procedure proc_edit_invert (p1,macro : gtk_pointer); cdecl;
var u,v,z : hyper;
    l : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          for l := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength (l) = 2 then
               begin
                    u := finput^.getline (l,1);
                    v := finput^.getline (l,2);
                    z := 1/(v-u);
                    finput^.putline (l,2,u+z);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.invert');
     end;
end;

{ *********************************** Lines ********************************** }
{ +EDIT }
procedure proc_line_to_points (p1,macro : gtk_pointer); cdecl;
var o,l,p,fl : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          fl := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         inc (fl);
                         if fl = finput^.linecounter then { if selected }
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.line.to.points');
     end;
end;

procedure proc_line_to_one_vector (p1,macro : gtk_pointer); cdecl;
var o,l,p,fl : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          fl := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         inc (fl);
                         if fl = finput^.linecounter then { if selected }
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then { get vector }
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then { save point }
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then { save line_rows }
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.line.to.vector');
     end;
end;

procedure proc_line_to_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p,fl : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          fl := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         inc (fl);
                         if fl = finput^.linecounter then { if selected }
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then { split line_rows }
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l)-1 do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                        dummy.newpoint (finput^.getobject (o,l,p+1));
                                        dummy.newline (finput^.getmaterial (o,l));
                                   end;
                              end
                              else if finput^.getlinepointlength (o,l) = 1 then { save point }
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then  { save line_rows }
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.line.to.vectors');
     end;
end;

procedure proc_line_to_objects (p1,macro : gtk_pointer); cdecl;
var o,l,p,fl : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          fl := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         inc (fl);
                         if fl = finput^.linecounter then { if selected }
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                                   dummy.newobject (finput^.getname (o));
                              end;
                         end
                         else
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.line.to.objects');
     end;
end;

{ *********************************** Object ********************************* }
{ +EDIT }
procedure proc_object_to_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if o = finput^.objectcounter then
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,p));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                         dummy.newobject (finput^.getname (o));
                    end;
               end
               else
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                         dummy.newobject (finput^.getname (o));
                    end;
               end;
          end;
          o := finput^.objectcounter; { save objectcounter }
          finput^.replace (dummy);  { %% %% }
          finput^.objectcounter := o; { restore objectcounter }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.object.to.points');
     end;
end;

procedure proc_object_to_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if o = finput^.objectcounter then
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 1 then
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                         dummy.newobject (finput^.getname (o));
                    end;
               end
               else
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                         dummy.newobject (finput^.getname (o));
                    end;
               end;
          end;
          o := finput^.objectcounter; { save objectcounter }
          finput^.replace (dummy); { %% %% }
          finput^.objectcounter := o; { restore objectcounter }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.object.to.vectors');
     end;
end;

procedure proc_object_to_one_line (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if o = finput^.objectcounter then
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                         dummy.newobject (finput^.getname (o));
                    end;
               end
               else
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial (o,l));
                              end;
                         end;
                         dummy.newobject (finput^.getname (o));
                    end;
               end;
          end;
          o := finput^.objectcounter; { save objectcounter }
          finput^.replace (dummy); { %% %% }
          finput^.objectcounter := o; { restore objectcounter }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.object.to.one.line');
     end;
end;

{ *********************************** Objects ******************************** }
{ +EDIT }
procedure proc_objects_to_points (p1,macro : gtk_pointer); cdecl;
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
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              dummy.newpoint (finput^.getobject (o,l,p));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.points');
     end;
end;

procedure proc_objects_to_vectors (p1,macro : gtk_pointer); cdecl;
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
                              dummy.newpoint (finput^.getobject (o,l,finput^.getlinepointlength (o,l)));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.vectors');
     end;
end;

procedure proc_objects_to_loops (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
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
                                    dummy.newpoint (finput^.getobject (o,l,p));
                               end;
                               h := finput^.getobject (o,l,1);
                               if finput^.getobject (o,l,finput^.getlinepointlength (o,l)) <> h then dummy.newpoint (h);
                               dummy.newline (finput^.getmaterial (o,l));
                          end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.loops');
     end;
end;

procedure proc_objects_to_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
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
                         if finput^.getlinepointlength (o,l) > 1 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l)-1 do
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                              h := finput^.getobject (o,l,finput^.getlinepointlength (o,l));
                              if finput^.getobject (o,l,1) <> h then dummy.newpoint (h);
                              dummy.newline (finput^.getmaterial (o,l));
                         end
                         else
                         begin
                              dummy.newpoint (finput^.getobject (o,l,1));
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.lines');
     end;
end;

procedure proc_objects_to_one_line (p1,macro : gtk_pointer); cdecl;
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
                         for p := 1 to finput^.getlinepointlength (o,l) do
                         begin
                              dummy.newpoint (finput^.getobject (o,l,p));
                         end;
                    end;
                    dummy.newline (finput^.getmaterial (o,l));
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.one.line');
     end;
end;

procedure proc_objects_to_one_object (p1,macro : gtk_pointer); cdecl;
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
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                         end;
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
               end;
          end;
          dummy.newobject (finput^.getname (o));
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.objects.to.one.object');
     end;
end;

{ **************************************************************************** }

procedure proc_material_to_one_object (p1,macro : gtk_pointer); cdecl;
var o,l,p,lc,pc : integer;
    list : tpolybyte;
begin
     list := Default (tpolybyte);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          o := 1;
          list.init (finput^.getlinelength);
          for l := 1 to finput^.getlinelength do
          begin
               if list.get (l) = 0 then
               begin
                    if finput^.getalllinepointlength (l) > 0 then
                    begin
                         for p := 1 to finput^.getalllinepointlength (l) do
                         begin
                              dummy.newpoint (finput^.getline (l,p));
                         end;
                    end;
                    dummy.newline (finput^.getallmaterial (l));
                    list.put (l,1);
                    for lc := 1 to finput^.getlinelength do
                    begin
                         if list.get (lc) = 0 then
                         if finput^.getallmaterial(l) = finput^.getallmaterial(lc) then
                         begin
                              if finput^.getalllinepointlength (lc) > 0 then
                              begin
                                   for pc := 1 to finput^.getalllinepointlength (lc) do
                                   begin
                                        dummy.newpoint (finput^.getline (lc,pc));
                                   end;
                              end;
                              dummy.newline (finput^.getallmaterial (lc));
                              list.put (lc,1);
                         end;
                    end;
                    dummy.newobject (getstring(o));
                    inc (o);
               end;
          end;
          list.done;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.material.to.one.object');
     end;
end;

procedure proc_name_to_one_object (p1,macro : gtk_pointer); cdecl;
var o,l,p,oc,lc,pc : integer;
    list : tpolybyte;
begin
     list := Default (tpolybyte);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          list.init (finput^.getobjectlength);
          for o := 1 to finput^.getobjectlength do
          begin
               if list.get (o) = 0 then
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end;
                    list.put (o,1);
                    for oc := 1 to finput^.getobjectlength do  { look for the same name }
                    begin
                         if list.get (oc) = 0 then
                         if finput^.getname (o) = finput^.getname (oc) then
                         begin
                              if finput^.getobjectlinelength (oc) > 0 then
                              begin
                                   for lc := 1 to finput^.getobjectlinelength (oc) do
                                   begin
                                        if finput^.getlinepointlength (oc,lc) > 0 then
                                        begin
                                             for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                             begin
                                                  dummy.newpoint (finput^.getobject (oc,lc,pc));
                                             end;
                                        end;
                                        dummy.newline (finput^.getmaterial (oc,lc));
                                   end;
                              end;
                              list.put (oc,1);
                         end;
                    end;
                    dummy.newobject (finput^.getname (o));
               end;
          end;
          list.done;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.name.to.one.object');
     end;
end;

procedure proc_name_to_unique (p1,macro : gtk_pointer); cdecl;
var o,x : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               x := length(getstring(finput^.getobjectlength));
               finput^.putname(o,finput^.getname (o)+'_'+fillbefore(getstring(o),x,'0'));
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.name.to.unique');
     end;
end;

procedure proc_name_replace (p1,macro : gtk_pointer); cdecl;
var o : integer;
    p,s,t : utf16;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          p := _getedit (edit_name_pattern,macro,1);
          t := _getedit (edit_name_to,macro,2);
          for o := 1 to finput^.getobjectlength do
          begin
               s := finput^.getname (o);
               replace (s,p,t);
               finput^.putname(o,s);
          end;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.name.replace','"'+p+'" "'+t+'"');
     end;
end;

{ **************************************************************************** }

procedure proc_erase_same (p1,macro : gtk_pointer); cdecl;
var o,l,p,l2,p2 : integer;
    h : hyper;
    ecount : integer;
    bool : boolean;
begin
     if finput^.getobjectlength > 1 then
     begin
          _cursor_watch;
          ecount := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   h := finput^.getobject (o,l,p);
                                   if h <> Hmax then
                                   begin
                                        bool := false;
                                        for l2 := 1 to finput^.getobjectlinelength(o) do
                                        begin
                                             if finput^.getlinepointlength (o,l2) > 0 then
                                             begin
                                                  for p2 := 1 to finput^.getlinepointlength (o,l2) do
                                                  begin
                                                       if not ((l = l2) and (p = p2)) and (finput^.getobject (o,l2,p2) = h) then
                                                       begin
                                                            finput^.markpoint(o,l2,p2);
                                                            inc (ecount);
                                                            bool := true;
                                                       end;
                                                  end;
                                             end;
                                        end;
                                        if bool then
                                        begin
                                             finput^.markpoint(o,l,p);
                                             inc (ecount);
                                        end;
                                   end;
                                   progress ('Erase same',finput^.getpobject(o,l,p)/finput^.getpointlength);
                              end;
                         end;
                    end;
               end;
          end;
          progress;
          finput^.erasemarked;
          writeln ('  Erased points: '+getstring(ecount));
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.same');
     end;
end;

procedure proc_clue_same (p1,macro : gtk_pointer); cdecl;
var z,o,p : integer;
    max : integer;
begin
     if finput^.getobjectlength > 1 then
     begin
          _cursor_watch;
          dummy.clear;
          max := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > max then max := finput^.getobjectlinelength (o);
          end;

          if max > 0 then
          for z := 1 to max do
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         if into (z,1,finput^.getobjectlinelength (o)) then
                         begin
                              if finput^.getlinepointlength (o,z) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,z) do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,z,p));
                                   end;
                              end;
                         end;
                    end;
               end;
               dummy.newline (finput^.getmaterial (o,z));
          end;
          dummy.newobject ('clue_same');
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.clue.same');
     end;
end;

{ ******************************* Erase points *************************** }
{ +EDIT }
procedure proc_erase_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
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
                    if finput^.getlinepointlength (o,l) > 1 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         dummy.newpoint (finput^.getobject (o,l,p));
                    end;
                    dummy.newline (finput^.getmaterial (o,l));
               end;
               dummy.newobject (finput^.getname (o));
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.points');
     end;
end;

{ ******************************* Erase vectors ****************************** }
{ +EDIT }
procedure proc_erase_vectors (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
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
                    if finput^.getlinepointlength (o,l) <> 2 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         dummy.newpoint (finput^.getobject (o,l,p));
                    end;
                    dummy.newline (finput^.getmaterial (o,l));
               end;
               dummy.newobject (finput^.getname (o));
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.vectors');
     end;
end;

{ ******************************* Erase lines *************************** }
{ +EDIT }
procedure proc_erase_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
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
                    if finput^.getlinepointlength (o,l) > 2 then
                    for p := 1 to finput^.getlinepointlength (o,l) do
                    begin
                         dummy.newpoint (finput^.getobject (o,l,p));
                    end;
                    dummy.newline (finput^.getmaterial (o,l));
               end;
               dummy.newobject (finput^.getname (o));
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.lines');
     end;
end;

{ ******************************* Erase loops ******************************** }
{ +EDIT }
procedure proc_erase_loops (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    v,u : hyper;
    erase : boolean;
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
                    if finput^.getlinepointlength (o,l) > 1 then
                    begin
                         v := Hzero;
                         erase := false;
                         for p := 1 to finput^.getlinepointlength (o,l)-1 do
                         begin
                              u := finput^.getobject (o,l,p+1)-finput^.getobject (o,l,p);
                              v := v + u;
                              if inv (u,v) then erase := true;
                         end;
                         if not erase then
                         begin
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial (o,l));
                         end;
                    end
                    else
                    begin
                         dummy.newpoint (finput^.getobject (o,l,1));
                         dummy.newline (finput^.getmaterial (o,l));
                    end;
               end;
               dummy.newobject (finput^.getname (o));
          end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.loops');
     end;
end;

{ ************************** Vector & Line direction ************************* }
{ +EDIT }
procedure proc_vectors_direction_origin (p1,macro : gtk_pointer); cdecl;
var d,ld : hyper;
    z,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          d := _gethyper (edit_vectors_direction,macro,1);
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if l = 2 then
               begin
                    ld := finput^.getline (z,2)-finput^.getline (z,1);
                    if inv(ld,d) then
                    begin
                         ld := finput^.getline (z,1);
                         finput^.putline (z,1,finput^.getline (z,2));
                         finput^.putline (z,2,ld);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.direction.origin',getstring(d));
     end;
end;

{ +EDIT }
procedure proc_vectors_disperse (p1,macro : gtk_pointer); cdecl;
var d,d2,v : hyper;
    z,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          d := _gethyper (edit_vectors_range,macro,1);
          d2 := d/2;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if l = 2 then
               begin
                    v := gh (random*d.x,random*d.y,random*d.z,random*d.t)-d2;
                    finput^.putline (z,1,finput^.getline (z,1)+v);
                    finput^.putline (z,2,finput^.getline (z,2)+v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.disperse',getstring(d));
     end;
end;

{ +EDIT }
procedure proc_vectors_direction (p1,macro : gtk_pointer); cdecl;
var v,d,ld : hyper;
    z,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          d := _gethyper (edit_vectors_direction,macro,1);
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if l = 2 then
               begin
                    ld := finput^.getline (z,2)-finput^.getline (z,1);
                    if inv(ld,d) then
                    begin
                         v := finput^.getline (z,1);
                         finput^.putline (z,1,v);
                         finput^.putline (z,2,v+(-1*ld));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.vectors.direction',getstring(d));
     end;
end;

{ +EDIT }
procedure proc_lines_flip (p1,macro : gtk_pointer); cdecl;
var v : hyper;
    z,bl,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if l > 1 then
               begin
                    for bl := 1 to (l div 2) do
                    begin
                         v := finput^.getline (z,bl);
                         finput^.putline (z,bl,finput^.getline (z,l-bl+1));
                         finput^.putline (z,l-bl+1,v);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.flip');
     end;
end;

{ +EDIT }
procedure proc_lines_direction (p1,macro : gtk_pointer); cdecl;
var v,d,ld : hyper;
    z,bl,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          d := _gethyper (edit_lines_direction,macro,1);
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if l > 1 then
               begin
                    ld := Hzero;
                    for bl := 1 to l-1 do
                    begin
                         ld := ld + (finput^.getline (z,bl+1)-finput^.getline (z,bl));
                    end;
                    if inv(ld,d) then
                    begin
                         for bl := 1 to (l div 2) do
                         begin
                              v := finput^.getline (z,bl);
                              finput^.putline (z,bl,finput^.getline (z,l-bl+1));
                              finput^.putline (z,l-bl+1,v);
                         end;
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.direction',getstring(d));
     end;
end;

{ **************************************************************************** }

{ +EDIT }
procedure proc_lines_number (p1,macro : gtk_pointer); cdecl;
var v : hyper;
    z,bl,l : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 0) then
               begin
                    for bl := 1 to l do
                    begin
                         v := finput^.getline (z,bl);
                         v.t := bl;
                         finput^.putline (z,bl,v);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.number');
     end;
end;

{ +EDIT }
procedure proc_lines_distance (p1,macro : gtk_pointer); cdecl;
var v,d : hyper;
    z,bl,len : integer;
    ld : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               len := finput^.getalllinepointlength (z);
               if (len > 1) then
               begin
                    if (finput^.getline(z,1) = finput^.getline(z,len)) then { loop }
                    begin
                         for bl := 1 to len-1 do
                         begin
                              if (bl = 1) then { first and last are the same}
                              begin
                                   v := finput^.getline (z,1);
                                   v.t := 0;
                                   d := finput^.getline (z,2);
                                   d.t := 0;
                                   ld := getlength(v-d);
                                   d := finput^.getline (z,len-1);
                                   d.t := 0;
                                   ld := (ld + getlength(v-d)) / 2;
                                   finput^.putline (z,1,gh(v.x,v.y,v.z,ld));
                                   finput^.putline (z,len,gh(v.x,v.y,v.z,ld));
                              end
                              else
                              begin
                                   v := finput^.getline (z,bl);
                                   v.t := 0;
                                   d := finput^.getline (z,bl-1);
                                   d.t := 0;
                                   ld := getlength(v-d);
                                   d := finput^.getline (z,bl+1);
                                   d.t := 0;
                                   ld := (ld + getlength(v-d)) / 2;
                                   finput^.putline (z,bl,gh(v.x,v.y,v.z,ld));
                              end;
                         end;
                    end
                    else
                    begin
                         for bl := 1 to len do
                         begin
                              if (bl = 1) then { first }
                              begin
                                   v := finput^.getline (z,bl);
                                   v.t := 0;
                                   d := finput^.getline (z,bl+1);
                                   d.t := 0;
                                   ld := getlength(v-d);
                                   finput^.putline (z,bl,gh(v.x,v.y,v.z,ld));
                              end
                              else if (bl = len) then { last }
                              begin
                                   v := finput^.getline (z,bl);
                                   v.t := 0;
                                   d := finput^.getline (z,bl-1);
                                   d.t := 0;
                                   ld := getlength(v-d);
                                   finput^.putline (z,bl,gh(v.x,v.y,v.z,ld));
                              end
                              else
                              begin
                                   v := finput^.getline (z,bl);
                                   v.t := 0;
                                   d := finput^.getline (z,bl-1);
                                   d.t := 0;
                                   ld := getlength(v-d);
                                   d := finput^.getline (z,bl+1);
                                   d.t := 0;
                                   ld := (ld + getlength(v-d)) / 2;
                                   finput^.putline (z,bl,gh(v.x,v.y,v.z,ld));
                              end;
                         end;
                    end;
               end
               else if (len = 1) then
               begin
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.distance');
     end;
end;

{ +EDIT }
procedure proc_lines_length (p1,macro : gtk_pointer); cdecl;
var v,d : hyper;
    z,bl,l : integer;
    ld : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    ld := 0;
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
                    for bl := 2 to l do
                    begin
                         d := finput^.getline (z,bl);
                         d.t := 0;
                         ld := ld + getlength(v-d);
                         finput^.putline (z,bl,gh(d.x,d.y,d.z,ld));
                         v := d;
                    end;
               end
               else if (l = 1) then
               begin
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.length');
     end;
end;

{ +EDIT }
procedure proc_lines_length_material (p1,macro : gtk_pointer); cdecl;
var v,d : hyper;
    z,bl,l : integer;
    ld : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    ld := 0;
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
                    for bl := 2 to l do
                    begin
                         d := finput^.getline (z,bl);
                         d.t := 0;
                         ld := ld + getlength(v-d);
                         v := d;
                    end;
                    finput^.putallmaterial(z,round(ld));
               end
               else if (l = 1) then finput^.putallmaterial(z,0);
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.length.material');
     end;
end;

{ +EDIT }
procedure proc_lines_material (p1,macro : gtk_pointer); cdecl;
var z : integer;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               finput^.putallmaterial(z,z);
          end;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.material');
     end;
end;

{ **************************************************************************** }

procedure proc_lines_pennation_x (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := halfangle (c,gv(1,0,0))*deg
                                          else r := halfangle (c,gv(1,0,0));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.x');
     end;
end;

procedure proc_lines_pennation_y (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := halfangle (c,gv(0,1,0))*deg
                                          else r := halfangle (c,gv(0,1,0));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.y');
     end;
end;

procedure proc_lines_pennation_z (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := halfangle (c,gv(0,0,1))*deg
                                          else r := halfangle (c,gv(0,0,1));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.z');
     end;
end;

procedure proc_lines_pennation_xy (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := 90-(halfangle (c,gv(0,0,1))*deg)
                                          else r := 90-halfangle (c,gv(0,0,1));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.xy');
     end;
end;

procedure proc_lines_pennation_yz (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := 90-(halfangle (c,gv(1,0,0))*deg)
                                          else r := 90-halfangle (c,gv(1,0,0));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.yz');
     end;
end;

procedure proc_lines_pennation_zx (p1,macro : gtk_pointer); cdecl;
var v,u,c : vector;
    z,bl,l : integer;
    r : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
                    for bl := 2 to l do
                    begin
                         u := htov (finput^.getline (z,bl));
                         c := u-v;
                         if format.degree then r := 90-(halfangle (c,gv(0,1,0))*deg)
                                          else r := 90-halfangle (c,gv(0,1,0));
                         finput^.putline (z,bl,gh(u.x,u.y,u.z,r));
                         v := u;
                    end;
               end
               else if (l = 1) then
               begin
                    v := htov (finput^.getline(z,1));
                    finput^.putline (z,1,gh(v,0));
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.pennation.zx');
     end;
end;

{ **************************************************************************** }

{ +EDIT }
procedure proc_lines_tortuosity (p1,macro : gtk_pointer); cdecl;
var v,d : hyper;
    z,bl,l : integer;
    ld,le : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 2) then
               begin
                    ld := 0;
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
                    for bl := 2 to l do
                    begin
                         d := finput^.getline (z,bl);
                         d.t := 0;
                         ld := ld + getlength(v-d);
                         le := getlength(finput^.getline (z,1)-d);
                         if le > 0.0 then finput^.putline (z,bl,gh(d.x,d.y,d.z,ld/le))
                                     else finput^.putline (z,bl,gh(d.x,d.y,d.z,0));
                         v := d;
                    end;
               end
               else if (l = 2) then
               begin
                    v := finput^.getline(z,1);
                    v.t := 1;
                    finput^.putline (z,1,v);
               end
               else
               begin
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.tortuosity');
     end;
end;

procedure proc_lines_curvature (p1,macro : gtk_pointer); cdecl;
var z,bl,l : integer;
    r,dk : real;
    v : hyper;
    line,line1,line2 : tpolyvector;
begin
     line := Default (Tpolyvector);
     line1 := Default (Tpolyvector);
     line2 := Default (Tpolyvector);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    line.init (l);
                    for bl := 1 to l do line.put (bl,htov(finput^.getline(z,bl)));
                    line.derivation(line1);
                    line1.derivation(line2);
                    for bl := 1 to l do
                    begin
                         {write (getlength(line.get(bl))); write (' '); write (getlength(line1.get(bl))); write (' '); write (getlength(line2.get(bl))); writeln;}
                         dk := power (getlength( line1.get(bl) ),3);
                         if dk <> 0.0 then r := getlength(cross( line1.get(bl),line2.get(bl) )) / dk
                                      else r := 0;
                         v := gh(line.get(bl),r);
                         finput^.putline (z,bl,v);
                    end;
                    line.done;
               end
               else if (l = 1) then
               begin
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.curvature');
     end;
end;

procedure proc_lines_torsion (p1,macro : gtk_pointer); cdecl;
var z,bl,l : integer;
    r,dt : real;
    v : hyper;
    line,line1,line2,line3 : tpolyvector;
begin
     line := Default (tpolyvector);
     line1 := Default (tpolyvector);
     line2 := Default (tpolyvector);
     line3 := Default (tpolyvector);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          for z := 1 to finput^.getlinelength do
          begin
               l := finput^.getalllinepointlength (z);
               if (l > 1) then
               begin
                    line.init (l);
                    for bl := 1 to l do line.put (bl,htov (finput^.getline(z,bl)));
                    line.derivation(line1);
                    line1.derivation(line2);
                    line2.derivation(line3);
                    for bl := 1 to l do
                    begin
                         dt := sqr (getlength(cross( line1.get(bl),line2.get(bl) )));
                         if dt <> 0.0 then r := getlength(det ( line1.get(bl),line2.get(bl),line3.get(bl) )) / dt
                                      else r := 0;
                         v := gh(line.get(bl),r);
                         finput^.putline (z,bl,v);
                    end;
                    line.done;
               end
               else if (l = 1) then
               begin
                    v := finput^.getline(z,1);
                    v.t := 0;
                    finput^.putline (z,1,v);
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.lines.torsion');
     end;
end;

{ **************************** Smooth lines ********************************** }
{ +EDIT }
procedure proc_smooth_lines (p1,macro : gtk_pointer); cdecl;
var v : hyper;
    _z,_l : integer;
    s,s1 : integer;
procedure run0 (z,l : integer); { Polynom }
var line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter :real;
    bl : integer;
begin
     line := Default (tpolyhyper);
     linepoly := Default (tpolynom4d);

     line.init (l);
     for bl := 1 to l do
     begin
          line.put (bl,finput^.getline (z,bl));
     end;
     if l < s1+1 then
     begin
          linepoly.init (l);
          linepoly.getpolynom (line);
     end
     else
     begin
          linepoly.init (s1+1);
          linepoly.getpolynom (line);
     end;
     factor := linepoly.pathlength/l;
     counter := 0;
     for bl := 1 to l do
     begin
          v := linepoly.polynom (counter);
          finput^.putpoint (finput^.getpline (z,bl),v);
          counter := counter + factor;
     end;
     linepoly.done;
     line.done;
end;
procedure run1 (z,l : integer); { Polynom fit }
var line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter :real;
    bl : integer;
begin
     line := Default (tpolyhyper);
     linepoly := Default (tpolynom4d);

     line.init (l);
     for bl := 1 to l do
     begin
          line.put (bl,finput^.getline (z,bl));
     end;
     if l < s1+1 then linepoly.init (l)
                 else linepoly.init (s1+1);
     linepoly.fit (line);
     factor := linepoly.pathlength/l;
     counter := 0;
     for bl := 1 to l do
     begin
          v := linepoly.polynom (counter);
          finput^.putpoint (finput^.getpline (z,bl),v);
          counter := counter + factor;
     end;
     linepoly.done;
     line.done;
end;
procedure run2 (z,l : integer); {Hard average}
var v1,v2,v3 : hyper;
    bl : integer;
begin
     v1 := finput^.getline (z,1);
     v2 := finput^.getline (z,2);
     for bl := 2 to l-1 do
     begin
          v3 := finput^.getline (z,bl+1);
          finput^.putpoint (finput^.getpline (z,bl),(v1+v3)/2);
          v1 := v2;
          v2 := v3;
     end;
     if finput^.getline (z,1) = finput^.getline (z,l) then
     begin
          finput^.putpoint (finput^.getpline (z,1),(finput^.getline (z,1+1)+finput^.getline (z,l-1))/2);
          finput^.putpoint (finput^.getpline (z,l),finput^.getline (z,1));
     end;
end;
procedure run3 (z,l : integer); { Average }
var v1,v2,v3 : hyper;
    bl : integer;
begin
     v1 := finput^.getline (z,1);
     v2 := finput^.getline (z,2);
     for bl := 2 to l-1 do
     begin
          v3 := finput^.getline (z,bl+1);
          finput^.putpoint (finput^.getpline (z,bl),(v1+v2+v3)/3);
          v1 := v2;
          v2 := v3;
     end;
     if finput^.getline (z,1) = finput^.getline (z,l) then
     begin
          finput^.putpoint (finput^.getpline (z,1),(finput^.getline (z,1+1)+finput^.getline (z,l-1))/2);
          finput^.putpoint (finput^.getpline (z,l),finput^.getline (z,1));
     end;
end;
procedure run4 (z,l : integer); { Soft average }
var v1,v2,v3 : hyper;
    bl : integer;
begin
     v1 := finput^.getline (z,1);
     v2 := finput^.getline (z,2);
     for bl := 2 to l-1 do
     begin
          v3 := finput^.getline (z,bl+1);
          finput^.putpoint (finput^.getpline (z,bl),(v1+v2+v2+v3)/4);
          v1 := v2;
          v2 := v3;
     end;
     if finput^.getline (z,1) = finput^.getline (z,l) then
     begin
          finput^.putpoint (finput^.getpline (z,1),(finput^.getline (z,1+1)+finput^.getline (z,l-1))/2);
          finput^.putpoint (finput^.getpline (z,l),finput^.getline (z,1));
     end;
end;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          s := _getitem (calculate_smooth_method,macro,1);
          s1 := _getitem (edit_polynom_method,macro,2);
          for _z := 1 to finput^.getlinelength do
          begin
               _l := finput^.getalllinepointlength (_z);
               if _l > 2 then
               begin
                    case s of
                         0 : run0 (_z,_l); { Polynom }
                         1 : run1 (_z,_l); { Polynom fit }
                         2 : run2 (_z,_l); { Hard Average }
                         3 : run3 (_z,_l); { Average }
                         4 : run4 (_z,_l); { Soft average }
                         else run3 (_z,_l);
                    end;
               end;
               progress ('Smooth lines',_z/finput^.getlinelength);
          end;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.smooth.lines',getstring(s)+' '+getstring(s1));
     end;
end;

{ ****************************** Erase duplicates **************************** }

procedure proc_erase_duplicates (p1,macro : gtk_pointer); cdecl;
var l,lp : integer;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          for l := 1 to finput^.getlinelength do
          begin
               lp := finput^.getalllinepointlength (l);
               if lp > 0 then
               begin
                    if finput^.getline(l,1) <> Hmax then { not marked }
                    begin
                         if finput^.searchline (l) then finput^.markallline(l);
                    end;
               end;
               progress ('Erase duplicates',finput^.getpline(l,lp)/finput^.getpointlength);
          end;
          finput^.erasemarked;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.duplicates');
     end;
end;

procedure proc_erase_near_duplicates (p1,macro : gtk_pointer); cdecl;
var l,p,lp : integer;
    line : tpolyhyper;
    range : real;
begin
     line := Default (tpolyhyper);

     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          range := _getreal (edit_near_duplicates,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               lp := finput^.getalllinepointlength (l);
               if lp > 0 then
               begin
                    line.init (lp);
                    for p := 1 to lp do line.put (p,finput^.getline (l,p));
                    if finput^.searchline (l,line,range) then finput^.markallline(l);
                    line.done;
               end;
               progress ('Erase near duplicates',finput^.getpline (l,lp)/finput^.getpointlength);
          end;
          finput^.erasemarked;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.near.duplicates',getstring(range));
     end;
end;

procedure proc_erase_near_duplicates_ends (p1,macro : gtk_pointer); cdecl;
var l,lp : integer;
    range : real;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          range := _getreal (edit_near_duplicates,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               lp := finput^.getalllinepointlength (l);
               if lp > 0 then
               begin
                    if finput^.searchends (l,finput^.getline(l,1),range) then finput^.markallline (l);
                    progress ('Erase near duplicates',finput^.getpline(l,lp)/finput^.getpointlength);
                end;
          end;
          finput^.erasemarked;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.near.duplicates.ends',getstring(range));
     end;
end;

procedure proc_erase_near_duplicates_begin (p1,macro : gtk_pointer); cdecl;
var l,lp : integer;
    range : real;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          range := _getreal (edit_near_duplicates,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               lp := finput^.getalllinepointlength (l);
               if lp > 0 then
               begin
                    if finput^.searchbegin (l,finput^.getline(l,1),range) then finput^.markallline (l);
                    progress ('Erase near duplicates',finput^.getpline(l,lp)/finput^.getpointlength);
                end;
          end;
          finput^.erasemarked;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.near.duplicates.begin',getstring(range));
     end;
end;

procedure proc_erase_near_duplicates_end (p1,macro : gtk_pointer); cdecl;
var l,lp : integer;
    range : real;
begin
     if finput^.getlinelength > 0 then
     begin
          _cursor_watch;
          range := _getreal (edit_near_duplicates,macro,1);
          for l := 1 to finput^.getlinelength do
          begin
               lp := finput^.getalllinepointlength (l);
               if lp > 0 then
               begin
                    if finput^.searchend(l,finput^.getline(l,1),range) then finput^.markallline (l);
                    progress ('Erase near duplicates',finput^.getpline(l,lp)/finput^.getpointlength);
                end;
          end;
          finput^.erasemarked;
          progress;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.erase.near.duplicates.end',getstring(range));
     end;
end;

{ **************************************************************************** }

procedure proc_edit_fillup_points (p1,macro : gtk_pointer); cdecl;
var p : integer;
    m : integer;
    h : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          m := 1;
          for p := 1 to finput^.getpointlength do
          begin
               h := finput^.getpoint (p);
               finput^.putpoint (p,gh(h.x,h.y,h.z,m));
               inc (m);
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.fillup.points');
     end;
end;

procedure proc_edit_fillup_line_ends_one (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength(o,l) > 0 then
                         begin
                              h := finput^.getobject(o,l,1);
                              finput^.putobject (o,l,1,gh(h.x,h.y,h.z,1));
                              h := finput^.getobject(o,l,finput^.getlinepointlength(o,l));
                              finput^.putobject (o,l,finput^.getlinepointlength(o,l),gh(h.x,h.y,h.z,1));
                         end;
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.fillup.ends.one');
     end;
end;

procedure proc_edit_fillup_line_ends (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    m : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          m := 1;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength(o,l) > 0 then
                         begin
                              h := finput^.getobject(o,l,1);
                              finput^.putobject (o,l,1,gh(h.x,h.y,h.z,m));
                              inc (m);
                              h := finput^.getobject(o,l,finput^.getlinepointlength(o,l));
                              finput^.putobject (o,l,finput^.getlinepointlength(o,l),gh(h.x,h.y,h.z,m));
                              inc (m);
                         end;
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.fillup.ends');
     end;
end;

// doppelt
{procedure proc_edit_fillup_lines (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    m : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          m := 1;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         finput^.putmaterial(o,l,m);
                         inc (m);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.fillup.lines');
     end;
end;}

{ **************************************************************************** }

procedure proc_mean_near_duplicates (p1,macro : gtk_pointer); cdecl;
var p,p2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range : real;
    v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for p := 1 to finput^.getpointlength-1 do
          begin
               if not mark.get (p) then
               begin
                    ppos.init;
                    v := finput^.getpoint(p);
                    ppos.push (p);
                    mark.put (p,true);
                    for p2 := p+1 to finput^.getpointlength do
                    begin
                         if not mark.get (p2) then
                         begin
                              w := finput^.getpoint(p2);
                              if getlength(v-w) <= range then
                              begin
                                   ppos.push (p2);
                                   mark.put (p2,true);
                              end;
                         end;
                    end;
                    if ppos.length > 1 then
                    begin
                         w := Hzero;
                         for p2 := 1 to ppos.length do w := w + finput^.getpoint(ppos.get(p2));
                         w := w / ppos.length;
                         for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),w);
                    end;
                    ppos.done;
                    progress ('Mean near duplicates',p/finput^.getpointlength);
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_n (p1,macro : gtk_pointer); cdecl;
var p,p2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range,len : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for p := 1 to finput^.getpointlength-1 do
          begin
               if not mark.get (p) then
               begin
                    ppos.init;
                    v := finput^.getpoint(p);
                    v.t := 0;
                    ppos.push (p);
                    mark.put (p,true);
                    for p2 := p+1 to finput^.getpointlength do
                    begin
                         if not mark.get (p2) then
                         begin
                              w := finput^.getpoint(p2);
                              w.t := 0;
                              if getlength(v-w) <= range then
                              begin
                                   ppos.push (p2);
                                   mark.put (p2,true);
                              end;
                         end;
                    end;
                    if ppos.length > 1 then
                    begin
                         w := Hzero;
                         len := 0;
                         for p2 := 1 to ppos.length do
                         begin
                              u := finput^.getpoint(ppos.get(p2));
                              if u.t = 0 then
                              begin
                                   w := w + u;
                                   len := len + 1;
                              end
                              else
                              begin
                                   w := w + (u*u.t);
                                   len := len + u.t;
                              end;
                         end;
                         w := w / len; { mean }
                         for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),gh(w.x,w.y,w.z,ppos.length));
                    end;
                    ppos.done;
                    progress ('Mean near duplicates',p/finput^.getpointlength);
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.n',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_3d (p1,macro : gtk_pointer); cdecl;
var l,l2,p,p2,vp,vp2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         ppos.init;
                         v := finput^.getpoint(vp);
                         v.t := 0;

                         ppos.push (vp);
                         mark.put (vp,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        w.t := 0;
                                        if (getlength(v-w) <= range) then
                                        begin
                                             ppos.push (vp2);
                                             mark.put (vp2,true);
                                        end;
                                   end;
                              end;
                         end;

                         if ppos.length > 1 then
                         begin
                              w := Hzero;
                              for p2 := 1 to ppos.length do
                              begin
                                   u := finput^.getpoint(ppos.get(p2));
                                   w := w + u;
                              end;
                              w := w / ppos.length; { mean }
                              for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),w);
                         end;
                         ppos.done;
                         progress ('Mean near duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.3d',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_t (p1,macro : gtk_pointer); cdecl;
var l,l2,p,p2,vp,vp2,t1,t2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         ppos.init;
                         v := finput^.getpoint(vp);
                         t1 := round(v.t);
                         v.t := 0;

                         ppos.push (vp);
                         mark.put (vp,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        t2 := round(w.t);
                                        w.t := 0;
                                        if (getlength(v-w) <= range) and (t1 <> t2) then
                                        begin
                                             ppos.push (vp2);
                                             mark.put (vp2,true);
                                        end;
                                   end;
                              end;
                         end;

                         if ppos.length > 1 then
                         begin
                              w := Hzero;
                              t1 := round(finput^.getpoint(ppos.get(1)).t);
                              for p2 := 1 to ppos.length do
                              begin
                                   u := finput^.getpoint(ppos.get(p2));
                                   w := w + u;
                                   if u.t < t1 then t1 := round(u.t);
                              end;
                              w := w / ppos.length; { mean }
                              for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),gh(w.x,w.y,w.z,t1));
                         end;
                         ppos.done;
                         progress ('Mean near duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.t',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_t_zero (p1,macro : gtk_pointer); cdecl;
var l,l2,p,p2,vp,vp2,t1,t2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         ppos.init;
                         v := finput^.getpoint(vp);
                         t1 := round(v.t);
                         v.t := 0;
                         if (t1 > 0) then
                         begin
                              ppos.push (vp);
                              mark.put (vp,true);

                              for l2 := 1 to finput^.getlinelength do
                              begin
                                   for p2 := 1 to finput^.getalllinepointlength (l2) do
                                   begin
                                        vp2 := finput^.getpline(l2,p2);
                                        if (not mark.get (vp2)) then
                                        begin
                                             w := finput^.getpoint(vp2);
                                             t2 := round(w.t);
                                             w.t := 0;
                                             if (t2 > 0) and (getlength(v-w) <= range) and (t1 <> t2) then
                                             begin
                                                  ppos.push (vp2);
                                                  mark.put (vp2,true);
                                             end;
                                        end;
                                   end;
                              end;
                         end;

                         if ppos.length > 1 then
                         begin
                              w := Hzero;
                              t1 := round(finput^.getpoint(ppos.get(1)).t);
                              for p2 := 1 to ppos.length do
                              begin
                                   u := finput^.getpoint(ppos.get(p2));
                                   w := w + u;
                                   if u.t < t1 then t1 := round(u.t);
                              end;
                              w := w / ppos.length; { mean }
                              for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),gh(w.x,w.y,w.z,t1));
                         end;
                         ppos.done;
                         progress ('Mean near duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.t.zero',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_t_material (p1,macro : gtk_pointer); cdecl;
var l1,l2,p,p2,vp1,vp2,t1,t2,m1,m2  : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for l1 := 1 to finput^.getlinelength do
          begin
               m1 := finput^.getallmaterial(l1);
               for p := 1 to finput^.getalllinepointlength(l1) do
               begin
                    vp1 := finput^.getpline(l1,p);
                    {writeln (vp1);
                    writeln (mark.get (vp1));}
                    if not mark.get (vp1) then
                    begin
                         ppos.init;
                         v := finput^.getpoint(vp1);
                         t1 := round(v.t);
                         v.t := 0;

                         ppos.push (vp1);
                         mark.put (vp1,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              m2 := finput^.getallmaterial(l2);
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        t2 := round(w.t);
                                        w.t := 0;

                                        if (getlength(v-w) <= range) and (t1 <> t2) and (m1 <> m2) then  { different t and different material }
                                        begin
                                             ppos.push (vp2);
                                             mark.put (vp2,true);
                                        end;
                                   end;
                              end;
                         end;

                         if ppos.length > 1 then
                         begin
                              w := Hzero;
                              t1 := round(finput^.getpoint(ppos.get(1)).t);
                              for p2 := 1 to ppos.length do
                              begin
                                   u := finput^.getpoint(ppos.get(p2));
                                   w := w + u;
                                   if u.t < t1 then t1 := round(u.t);
                              end;
                              w := w / ppos.length; { mean }
                              for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),gh(w.x,w.y,w.z,t1));
                         end;
                         ppos.done;
                         progress ('Mean near duplicates',finput^.getpline(l1,p)/finput^.getpointlength);
                    end;
                    {writeln (vp1);
                    writeln (mark.get (vp1));}
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.t.material',getstring(range));
     end;
end;

procedure proc_mean_near_duplicates_material (p1,macro : gtk_pointer); cdecl;
var l,l2,p,p2,vp,vp2,m,m2 : integer;
    ppos : tpolynat;
    mark : tpolybool;
    range,len : real;
    u,v,w : hyper;
begin
     ppos := Default (tpolynat);
     mark := Default (tpolybool);

     if finput^.getpointlength > 1 then
     begin
          _cursor_watch;
          range := _getreal (edit_mean_near_duplicates,macro,1);
          mark.init (finput^.getpointlength);
          for l := 1 to finput^.getlinelength do
          begin
               m := finput^.getallmaterial(l);
               for p := 1 to finput^.getalllinepointlength(l) do
               begin
                    vp := finput^.getpline(l,p);
                    if not mark.get (vp) then
                    begin
                         ppos.init;
                         v := finput^.getpoint(vp);
                         v.t := 0;
                         ppos.push (vp);
                         mark.put (vp,true);

                         for l2 := 1 to finput^.getlinelength do
                         begin
                              m2 := finput^.getallmaterial(l2);
                              for p2 := 1 to finput^.getalllinepointlength (l2) do
                              begin
                                   vp2 := finput^.getpline(l2,p2);
                                   if (not mark.get (vp2)) and (m <> m2) then
                                   begin
                                        w := finput^.getpoint(vp2);
                                        w.t := 0;
                                        if getlength(v-w) <= range then
                                        begin
                                             ppos.push (vp2);
                                             mark.put (vp2,true);
                                        end;
                                   end;
                              end;
                         end;

                         if ppos.length > 1 then
                         begin
                              w := Hzero;
                              len := 0;
                              for p2 := 1 to ppos.length do
                              begin
                                   u := finput^.getpoint(ppos.get(p2));
                                   if u.t = 0 then
                                   begin
                                        w := w + u;
                                        len := len + 1;
                                   end
                                   else
                                   begin
                                        w := w + (u*u.t);
                                        len := len + u.t;
                                   end;
                              end;
                              w := w / len; { mean }
                              for p2 := 1 to ppos.length do finput^.putpoint(ppos.get(p2),gh(w.x,w.y,w.z,ppos.length));
                         end;
                         ppos.done;
                         progress ('Mean near duplicates',finput^.getpline(l,p)/finput^.getpointlength);
                    end;
               end;
          end;
          progress;
          mark.done;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.near.duplicates.material',getstring(range));
     end;
end;

{ ****************************** Swap Axis *********************************** }

procedure proc_swap_xy (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.y,v.x,v.z,v.t));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.xy');
     end;
end;

procedure proc_swap_xz (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.z,v.y,v.x,v.t));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.xz');
     end;
end;

procedure proc_swap_yz (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.x,v.z,v.y,v.t));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.yz');
     end;
end;

procedure proc_swap_xt (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.t,v.y,v.z,v.x));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.xt');
     end;
end;

procedure proc_swap_yt (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.x,v.t,v.z,v.y));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.yt');
     end;
end;

procedure proc_swap_zt (p1,macro : gtk_pointer); cdecl;
var z : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               finput^.putpoint (z,gh(v.x,v.y,v.t,v.z));
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('edit.swap.zt');
     end;
end;

{ *********************************** Axes *********************************** }

procedure proc_clear_axes (p1,macro : gtk_pointer); cdecl;
var z,r : integer;
    v : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          r := _getitem (edit_axis1);
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               case r of
                    0 : v := gh(0,v.y,v.z,v.t);
                    1 : v := gh(v.x,0,v.z,v.t);
                    2 : v := gh(v.x,v.y,0,v.t);
                    3 : v := gh(v.x,v.y,v.z,0);
               end;
               finput^.putpoint (z,v);
          end;
          calculating;
          updating;
          drawing;
     end;
end;

procedure proc_move_axes (p1,macro : gtk_pointer); cdecl;
var z,r,s : integer;
    v : hyper;
    t : real;
begin
     if finput^.getpointlength > 0 then
     begin
          r := _getitem (edit_axis1);
          s := _getitem (edit_axis2);
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               case r of
                    0 : begin t := v.x; v := gh(0,v.y,v.z,v.t); end;
                    1 : begin t := v.y; v := gh(v.x,0,v.z,v.t); end;
                    2 : begin t := v.z; v := gh(v.x,v.y,0,v.t); end;
                    3 : begin t := v.t; v := gh(v.x,v.y,v.z,0); end;
                    else t := 0;
               end;
               case s of
                    0 : v := gh(t,v.y,v.z,v.t);
                    1 : v := gh(v.x,t,v.z,v.t);
                    2 : v := gh(v.x,v.y,t,v.t);
                    3 : v := gh(v.x,v.y,v.z,t);
               end;
               finput^.putpoint (z,v);
          end;
          calculating;
          updating;
          drawing;
      end;
end;

procedure proc_copy_axes (p1,macro : gtk_pointer); cdecl;
var z,r,s : integer;
    v : hyper;
    t : real;
begin
     if finput^.getpointlength > 0 then
     begin
          r := _getitem (edit_axis1);
          s := _getitem (edit_axis2);
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               case r of
                    0 : t := v.x;
                    1 : t := v.y;
                    2 : t := v.z;
                    3 : t := v.t;
                    else t := 0;
               end;
               case s of
                    0 : v := gh(t,v.y,v.z,v.t);
                    1 : v := gh(v.x,t,v.z,v.t);
                    2 : v := gh(v.x,v.y,t,v.t);
                    3 : v := gh(v.x,v.y,v.z,t);
               end;
               finput^.putpoint (z,v);
          end;
          calculating;
          updating;
          drawing;
     end;
end;

procedure proc_swap_axes (p1,macro : gtk_pointer); cdecl;
var z,r,s : integer;
    v : hyper;
    t,u : real;
begin
     if finput^.getpointlength > 0 then
     begin
          r := _getitem (edit_axis1);
          s := _getitem (edit_axis2);
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint(z);
               case r of
                    0 : t := v.x;
                    1 : t := v.y;
                    2 : t := v.z;
                    3 : t := v.t;
                    else t := 0;
               end;
               case s of
                    0 : u := v.x;
                    1 : u := v.y;
                    2 : u := v.z;
                    3 : u := v.t;
                    else u := 0;
               end;
               case r of
                    0 : v := gh(u,v.y,v.z,v.t);
                    1 : v := gh(v.x,u,v.z,v.t);
                    2 : v := gh(v.x,v.y,u,v.t);
                    3 : v := gh(v.x,v.y,v.z,u);
               end;
               case s of
                    0 : v := gh(t,v.y,v.z,v.t);
                    1 : v := gh(v.x,t,v.z,v.t);
                    2 : v := gh(v.x,v.y,t,v.t);
                    3 : v := gh(v.x,v.y,v.z,t);
               end;
               finput^.putpoint (z,v);
          end;
          calculating;
          updating;
          drawing;
     end;
end;

{ ********************************** Mean ************************************ }

procedure proc_edit_mean (p1,macro : gtk_pointer); cdecl;
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
                     dummy.newpoint (u/c);
                     dummy.newline (finput^.getmaterial (o,1));
                     dummy.newobject (finput^.getname(o));
                end;
           end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean');
     end;
end;

procedure proc_edit_mean_x (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default (tpolycomplex);
     new := Default (tpolyhyper);

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
                          dummy.newline (finput^.getmaterial (o,1));
                     end;
                     dummy.newobject (finput^.getname(o));
                end;
                new.done;
                sorted.done;
           end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.x');
     end;
end;

procedure proc_edit_mean_y (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default (tpolycomplex);
     new := Default (tpolyhyper);

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
                          dummy.newline (finput^.getmaterial (o,1));
                     end;
                     dummy.newobject (finput^.getname(o));
                end;
                new.done;
                sorted.done;
           end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.y');
     end;
end;

procedure proc_edit_mean_z (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default (tpolycomplex);
     new := Default (tpolyhyper);

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
                          dummy.newline (finput^.getmaterial (o,1));
                     end;
                     dummy.newobject (finput^.getname(o));
                end;
                new.done;
                sorted.done;
           end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.z');
     end;
end;

procedure proc_edit_mean_t (p1,macro : gtk_pointer); cdecl;
var o,l,p,c : integer;
    u : hyper;
    sorted : tpolycomplex;
    new : tpolyhyper;
begin
     sorted := Default (tpolycomplex);
     new := Default (tpolyhyper);

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
                          dummy.newline (finput^.getmaterial (o,1));
                     end;
                     dummy.newobject (finput^.getname(o));
                end;
                new.done;
                sorted.done;
           end;
          finput^.replace (dummy); { %% %% }
          dummy.clear;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.mean.t');
     end;
end;

{ **************************************************************************** }

procedure proc_edit_random_mat_bright (p1,macro : gtk_pointer); cdecl;
var o,l,d : integer;
    c : vectornat;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         c := gvn(random (256),random (256),random (256));
                         d := max(max(c.x,c.y),c.z);
                         finput^.putmaterial (o,l,rgb2hex(c+(255-d)));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.material.bright');
     end;
end;

procedure proc_edit_random_mat (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         finput^.putmaterial (o,l,rgb2hex(gvn(random (256),random (256),random (256))));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.material');
     end;
end;

procedure proc_edit_random_mat_dark (p1,macro : gtk_pointer); cdecl;
var o,l,d : integer;
    c : vectornat;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         c := gvn(random (256),random (256),random (256));
                         d := min(min(c.x,c.y),c.z);
                         finput^.putmaterial (o,l,rgb2hex(c-d));
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.material.dark');
     end;
end;

procedure proc_edit_random_mat_remove (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         finput^.putmaterial (o,l,0);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.material.remove');
     end;
end;

{ ****** }

function remove_color (const s : utf16) : utf16;
begin
     if pos ('_$',s) = length(s)-7 then remove_color := copy (s,1,length(s)-8)
                                   else remove_color := s;
end;

procedure proc_edit_random_obj_bright (p1,macro : gtk_pointer); cdecl;
var o,d : integer;
    c : vectornat;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               c := gvn(random (256),random (256),random (256));
               d := max(max(c.x,c.y),c.z);
               finput^.putname (o,remove_color(finput^.getname(o))+'_$'+gethexcolor(c+(255-d)));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.object.bright');
     end;
end;

procedure proc_edit_random_obj (p1,macro : gtk_pointer); cdecl;
var o : integer;
    c : vectornat;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               c := gvn(random (256),random (256),random (256));
               finput^.putname (o,remove_color(finput^.getname(o))+'_$'+gethexcolor(c));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.object');
     end;
end;

procedure proc_edit_random_obj_dark (p1,macro : gtk_pointer); cdecl;
var o,d : integer;
    c : vectornat;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               c := gvn(random (256),random (256),random (256));
               d := min(min(c.x,c.y),c.z);
               finput^.putname (o,remove_color(finput^.getname(o))+'_$'+gethexcolor(c-d));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.object.dark');
     end;
end;

procedure proc_edit_random_obj_remove (p1,macro : gtk_pointer); cdecl;
var o : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               finput^.putname (o,remove_color(finput^.getname(o)));
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.random.object.remove');
     end;
end;

{ **************************************************************************** }

procedure proc_edit_coloring_mat_to_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    m : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         m := finput^.getmaterial(o,l);
                         if finput^.getlinepointlength(o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   h := finput^.getobject(o,l,p);
                                   finput^.putobject (o,l,p,gh(h.x,h.y,h.z,m));
                              end;
                         end;
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.coloring.t');
     end;
end;

procedure proc_edit_coloring_obj_to_t (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    s : utf16;
    m : integer;
    h : hyper;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               s := finput^.getname(o);
               if pos ('$',s) > 0 then
               begin
                    m := gethex (copy(s,pos('$',s)+1,6));
               end
               else m := $FFFFFF;
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if finput^.getlinepointlength(o,l) > 0 then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   h := finput^.getobject(o,l,p);
                                   finput^.putobject (o,l,p,gh(h.x,h.y,h.z,m));
                              end;
                         end;
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.coloring.t.direct');
     end;
end;

procedure proc_edit_coloring_obj_to_mat (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    s : utf16;
    m : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          for o := 1 to finput^.getobjectlength do
          begin
               s := finput^.getname(o);
               if pos ('$',s) > 0 then
               begin
                    m := gethex (copy(s,pos('$',s)+1,6));
               end
               else m := $FFFFFF;
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         finput^.putmaterial(o,l,m);
                    end;
               end;
          end;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('edit.coloring.material');
     end;
end;
