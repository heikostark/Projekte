{ ********************************** Plane *********************************** }
{ +MESH }
procedure proc_calculate_plane (p1,macro : gtk_pointer); cdecl;
var c0,c1,g,h,len : integer;
    d,n : real;
    vmin,vmax,vcenter,a,b,c,normal,x1,x2,x3,x4 : hyper;
    xfactor,yfactor,xcounter,ycounter,min,max,raster : real;
    xstep,ystep,lx,ly : integer;
begin
     raster := _getreal (mesh_raster,macro,1);
     len := finput^.getpointlength;
     if raster > 0 then
     if len > 1 then
     begin
          _cursor_watch;
          dummy.clear;
          { calculate longest line_rows }
          d := ninfinity; h := 0; g := 0;
          for c0 := 1 to len-1 do
          begin
               for c1 := c0+1 to len do
               begin
                    n := getlength(finput^.getpoint(c0)-finput^.getpoint (c1));
                    if d < n then begin d := n; h := c0; g := c1; end;
               end;
               progress ('Calculate longest line',c0/(len-1));
          end;
          progress;
          { calculate farest point from line_rows }
          a := finput^.getpoint(h);
          b := norm(finput^.getpoint(g)-a); { vector along line_rows }
          d := ninfinity; h := 0;
          for c0 := 1 to len do
          begin
               n := getlength (cross(b,(finput^.getpoint(c0)-a),gh(0,0,0,1)))/getlength(b); { ignor t }
               if d < n then begin d := n; h := c0; end;
               progress ('Calculate farest point from line',c0/len);
          end;
          progress;
          n := scalar((finput^.getpoint(h)-a),b)/(sqr(getlength(b)));
          a := a+n*b;
          c := norm(finput^.getpoint(h)-a); { perpendicular vector to point}

          normal := norm(cross (b,c,gh(0,0,0,1)));

          vmin := finput^.min;
          vmax := finput^.max;
          min := -1*getlength(vmax-vmin)/2;
          max := getlength(vmax-vmin)/2;

          vcenter := finput^.center;

          dummy.newpoint (vcenter);
          dummy.newpoint (vcenter+(getlength(vmax-vmin)*normal)/20);
          dummy.newline (0); { newline }
          dummy.newobject ('plane_normal_vector');

          xstep := round((max-min)/raster);
          ystep := round((max-min)/raster);
          if (xstep > 1) and (ystep > 1) then
          begin
               xfactor := (max-min)/xstep;
               xcounter := min;
               for lx := 1 to xstep do
               begin
                    yfactor := (max-min)/ystep;
                    ycounter := min;
                    for ly := 1 to ystep do
                    begin
                         x1 := (vcenter+(b*(xcounter))+(c*(ycounter)));
                         x2 := (vcenter+(b*(xcounter+xfactor))+(c*(ycounter)));
                         x3 := (vcenter+(b*(xcounter))+(c*(ycounter+yfactor)));
                         x4 := (vcenter+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)));

                         dummy.newpoint (x1);
                         dummy.newpoint (x2);
                         dummy.newpoint (x4);
                         dummy.newpoint (x1);
                         dummy.newline (0); { newline }

                         dummy.newpoint (x4);
                         dummy.newpoint (x3);
                         dummy.newpoint (x1);
                         dummy.newpoint (x4);
                         dummy.newline (0); { newline }

                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
                    progress ('Search plane',lx/xstep);
               end;
               progress;
          end;
          dummy.newobject ('plane');
          cleanup (dummy);
          _cursor_arrow;
          tmacro(macro^).writeredo ('mesh.plane',getstring(raster));
     end;
end;

procedure proc_calculate_surface_o (raster : real;bool : boolean);
var c0,c1,g,h,len : integer;
    d,n : real;
    vmin,vmax,vcenter,a,b,c,normal,x1,x2,x3,x4 : hyper;
    xfactor,yfactor,xcounter,ycounter,min,max : real;
    xstep,ystep,lx,ly,erase : integer;
function look_for_near (normal,p : hyper) : hyper;
var r : integer;
    d,n,new : real;
    g,u : hyper;
begin
     if len > 0 then
     begin
          d := infinity; g := Hnorm;
          for r := 1 to len do
          begin
               u := finput^.getpoint (r);
               n := getlength(p-u);
               new := getlength ((p+(normal*n))-u);
               if d > new then begin d := new; g := u; end;
          end;
          look_for_near := g;
     end
     else look_for_near := p;
end;
begin
     len := finput^.getpointlength;
     if raster > 0 then
     if len > 1 then
     begin
          _cursor_watch;
          dummy.clear;
          { calculate longest line_rows }
          d := ninfinity; h := 0; g := 0;
          for c0 := 1 to len-1 do
          begin
               for c1 := c0+1 to len do
               begin
                    n := getlength(finput^.getpoint(c0)-finput^.getpoint (c1));
                    if d < n then begin d := n; h := c0; g := c1; end;
               end;
               progress ('Calculate longest line',c0/(len-1));
          end;
          progress;
          { calculate farest point from line_rows }
          a := finput^.getpoint(h);
          b := norm(finput^.getpoint(g)-a); { vector along line_rows }
          d := ninfinity; h := 0;
          for c0 := 1 to len do
          begin
               n := getlength (cross(b,(finput^.getpoint(c0)-a),gh(0,0,0,1)))/getlength(b); { ignor t }
               if d < n then begin d := n; h := c0; end;
               progress ('Calculate farest point from line',c0/len);
          end;
          progress;
          n := scalar((finput^.getpoint(h)-a),b)/(sqr(getlength(b)));
          a := a+n*b;
          c := norm(finput^.getpoint(h)-a); { perpendicular vector to point}

          normal := norm(cross (b,c,gh(0,0,0,1)));

          vmin := finput^.min;
          vmax := finput^.max;
          min := -1*getlength(vmax-vmin)/2;
          max := getlength(vmax-vmin)/2;

          vcenter := finput^.center;

          erase := 0;
          xstep := round((max-min)/raster);
          ystep := round((max-min)/raster);
          if (xstep > 1) and (ystep > 1) then
          begin
               xfactor := (max-min)/xstep;
               xcounter := min;
               for lx := 1 to xstep do
               begin
                    yfactor := (max-min)/ystep;
                    ycounter := min;
                    for ly := 1 to ystep do
                    begin
                         x1 := look_for_near (normal,vcenter+(b*(xcounter))+(c*(ycounter)));
                         x2 := look_for_near (normal,vcenter+(b*(xcounter+xfactor))+(c*(ycounter)));
                         x3 := look_for_near (normal,vcenter+(b*(xcounter))+(c*(ycounter+yfactor)));
                         x4 := look_for_near (normal,vcenter+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)));

                         if bool then
                         begin
                               if ((x1 <> x2) and (x2 <> x4) and (x4 <> x1)) then
                               begin
                                    dummy.newpoint (x1);
                                    dummy.newpoint (x2);
                                    dummy.newpoint (x4);
                                    dummy.newpoint (x1);
                                    dummy.newline (0); { newline }
                               end
                               else inc (erase);
                               if ((x4 <> x3) and (x3 <> x1) and (x1 <> x4)) then
                               begin
                                    dummy.newpoint (x4);
                                    dummy.newpoint (x3);
                                    dummy.newpoint (x1);
                                    dummy.newpoint (x4);
                                    dummy.newline (0); { newline }
                               end
                               else inc (erase);
                         end
                         else
                         begin
                              dummy.newpoint (x1);
                              dummy.newpoint (x2);
                              dummy.newpoint (x4);
                              dummy.newpoint (x1);
                              dummy.newline (0); { newline }
                              dummy.newpoint (x4);
                              dummy.newpoint (x3);
                              dummy.newpoint (x1);
                              dummy.newpoint (x4);
                              dummy.newline (0); { newline }
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
                    progress ('Search surface',lx/xstep);
               end;
               progress;
          end;
          dummy.newobject ('surface');
          writeln (getstring(erase)+' erased triangles!');
          cleanup (dummy);
          _cursor_arrow;
     end;
end;

procedure proc_calculate_surface (p1,macro : gtk_pointer); cdecl;
var raster : real;
begin
     raster := _getreal (mesh_raster,macro,1);
     proc_calculate_surface_o (raster,false);
     tmacro(macro^).writeredo ('mesh.surface',getstring(raster));
end;

procedure proc_calculate_clean_surface (p1,macro : gtk_pointer); cdecl;
var raster : real;
begin
     raster := _getreal (mesh_raster,macro,1);
     proc_calculate_surface_o (raster,true);
     tmacro(macro^).writeredo ('mesh.clean.surface',getstring(raster));
end;

{ **************************** Calculate hull ******************************** }
{ +MESH } { after Graham 1972 }
procedure proc_convexhull_ok (axis : byte;origin : vector;raster,distance : real;method : integer;plane,closed,points : boolean);
var N, K : integer;
    C    : tpolynat;
    Mark : integer;
    intern : tpolyhyper;

  procedure p_set_x (x : real); { get all points of a plane with specific x value }
  var i : integer;
      v : hyper;
  begin
       intern.newlength (0);
       for i := 1 to finput^.getpointlength do
       begin
            v := finput^.getpoint(i);
            if into (v.x,x-raster,x+raster) then
               if plane then intern.push (gh(v.y,v.z,x,v.t))
                        else intern.push (gh(v.y,v.z,v.x,v.t));
       end;
  end;
  procedure p_set_y (y : real); { get all points of a plane with specific y value }
  var i : integer;
      v : hyper;
  begin
       intern.newlength (0);
       for i := 1 to finput^.getpointlength do
       begin
            v := finput^.getpoint(i);
            if into (v.y,y-raster,y+raster) then
               if plane then intern.push (gh(v.x,v.z,y,v.t))
                        else intern.push (gh(v.x,v.z,v.y,v.t));
       end;
  end;
  procedure p_set_z (z : real); { get all points of a plane with specific z value }
  var i : integer;
      v : hyper;
  begin
       intern.newlength (0);
       for i := 1 to finput^.getpointlength do
       begin
            v := finput^.getpoint(i);
            if into (v.z,z-raster,z+raster) then
               if plane then intern.push (gh(v.x,v.y,z,v.t))
                        else intern.push (gh(v.x,v.y,v.z,v.t));
       end;
  end;

  function p_length : integer; { how many points in a plane }
  begin p_length := intern.length; end;
  function p_get (n : integer) : complex; { get point of a plane }
  var v : hyper;
  begin v := intern.get(n); p_get.x := v.x; p_get.y := v.y; end;

  function Left (A, B, C : Complex) : real; { Z from the Vectorproduct - if negative of positive }
  begin Left := (A.X-B.X)*(C.Y-B.Y) - (A.Y-B.Y)*(C.X-B.X); end;

  function doit : integer; { convex hull calculation }
  var I, J : integer;
  begin
        c.put (1,1);
        for I := 1 to N do { calculate first point }
        begin
             if p_get(I).Y < p_get(c.get(1)).Y then c.put (1,I)
             else
             if (p_get(I).Y = p_get(c.get(1)).Y) and
                (p_get(I).X < p_get(c.get(1)).X) then c.put (1,I);
        end;
        Mark := C.get(1);
        K := 1;
        repeat
              J := c.get(1); { first point }
              for I := 1 to N do
              begin
                   if (Mark <> I) then
                      if Left(p_get(J), p_get(c.get(K)), p_get(I)) < 0 then J := I  { next point }
                      else { many next points - case selection }
                      begin
                           if (Left(p_get(J), p_get(c.get(K)), p_get(I)) = 0) and
                              (getlength(p_get(c.get(K))-p_get(I)) > getlength(p_get(C.get(K))-p_get(J))) then J := I;
                      end;
              end;
              Inc(K);
              C.put (K,J);
        until (C.get (K) = C.get(1)) or (K > N);
        doit := K;
  end;

  function searchnear (p : hyper) : hyper; { nearest neighbor calculation }
  var i : integer;
      l,v : real;
  begin
       i := finput^.getpointlength;
       searchnear := p;
       if i > 1 then
       begin
            v := infinity;
            for i := 1 to finput^.getpointlength do
            begin
                 l := getlength(finput^.getpoint(i)-p);
                 if v > l then
                 begin
                      searchnear := finput^.getpoint(i);
                      v := l;
                 end;
            end;
       end
       else if i = 1 then searchnear := finput^.getpoint(1);
  end;

  function convertx (h : hyper) : hyper;
  begin convertx := gh(h.z,h.x,h.y,h.t); end; { x,y,z -> y,z|x -> z,x,y }
  procedure p_write_x;
  var I, J, K : integer;
      L : real;
      fv,v,lv : hyper;
  begin
       n := p_length;
       if n > 2 then
       begin
            c.init (n);
            k := doit; { convex hull calculation }
            if k > 2 then
            begin
                  dummy.newpoint (convertx(intern.get(c.get(1))));
                  if points then dummy.newline (0);
                  for i := 2 to K do
                  begin
                       fv := convertx(intern.get(c.get(i-1)));
                       lv := convertx(intern.get(c.get(i)))-fv;
                       l := getlength (lv);
                       lv := norm (lv);
                       if l > distance then
                       begin
                            if method = 0 then { concave points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      v := searchnear (fv+((j*distance)*lv));{ nearest neighbor }
                                      if plane then v.x := fv.x; { for x-plane }
                                      dummy.newpoint (v);
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end
                            else { convex points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      dummy.newpoint (fv+((j*distance)*lv));
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end;
                       end;
                       dummy.newpoint (convertx(intern.get(c.get(i))));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if closed then
                  begin
                       dummy.newpoint (convertx(intern.get(c.get(1))));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if not points then dummy.newline (0);
             end;
             c.done;
        end;
  end;
  function converty (h : hyper) : hyper;
  begin converty := gh(h.x,h.z,h.y,h.t); end; { x,y,z -> x,z|y -> x,z,y }
  procedure p_write_y;
  var I, J, K : integer;
      L : real;
      fv,v,lv : hyper;
  begin
       n := p_length;
       if n > 2 then
       begin
            c.init (n);
            k := doit; { convex hull calculation }
            if k > 2 then
            begin
                  dummy.newpoint (converty(intern.get(c.get(1))));
                  if points then dummy.newline (0);
                  for i := 2 to K do
                  begin
                       fv := converty(intern.get(c.get(i-1)));
                       lv := converty(intern.get(c.get(i)))-fv;
                       l := getlength (lv);
                       lv := norm (lv);
                       if l > distance then
                       begin
                            if method = 0 then { concave points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      v := searchnear (fv+((j*distance)*lv));{ nearest neighbor }
                                      if plane then v.y := fv.y; { for y-plane }
                                      dummy.newpoint (v);
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end
                            else { convex points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      dummy.newpoint (fv+((j*distance)*lv));
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end;
                       end;
                       dummy.newpoint (converty(intern.get(c.get(i))));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if closed then
                  begin
                       dummy.newpoint (converty(intern.get(c.get(1))));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if not points then dummy.newline (0);
             end;
             c.done;
        end;
  end;
  procedure p_write_z;
  var I, J, K : integer;
      L : real;
      fv,v,lv : hyper;
  begin
       n := p_length;
       if n > 2 then
       begin
            c.init (n);
            k := doit; { convex hull calculation }
            if k > 2 then
            begin
                  dummy.newpoint (intern.get(c.get(1)));
                  if points then dummy.newline (0);
                  for i := 2 to K do
                  begin
                       fv := intern.get(c.get(i-1));
                       lv := intern.get(c.get(i))-fv;
                       l := getlength (lv);
                       lv := norm (lv);
                       if l > distance then
                       begin
                            if method = 0 then { concave points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      v := searchnear (fv+((j*distance)*lv));{ nearest neighbor }
                                      if plane then v.z := fv.z; { for z-plane }
                                      dummy.newpoint (v);
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end
                            else { convex points }
                            begin
                                 for j := 1 to trunc(l/distance) do
                                 begin
                                      dummy.newpoint (fv+((j*distance)*lv));
                                      if points then dummy.newline (0); { store only points }
                                 end;
                            end;
                       end;
                       dummy.newpoint (intern.get(c.get(i)));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if closed then
                  begin
                       dummy.newpoint (intern.get(c.get(1)));
                       if points then dummy.newline (0); { store only points }
                  end;
                  if not points then dummy.newline (0);
             end;
             c.done;
        end;
  end;

var x,y,z : integer;
{ Main }
begin
     C := Default(tpolynat);
     intern := Default(tpolyhyper);

     if finput^.getpointlength > 2 then
     begin
           if raster = 0 then raster := 1;
           dummy.clear;
           intern.init;
           if axis = 1 then { planes along x axis }
           begin
                for x := round((1/raster)*(minall.x-1)) to round((1/raster)*(maxall.x+1)) do
                begin
                     p_set_x (x*raster);{ get all points of a plane with specific x value }
                     if intern.length > 2 then p_write_x; { calculation and store }
                end;
                dummy.newobject ('along_x-axis');
           end;
           if axis = 2 then { planes along y axis }
           begin
                for y := round((1/raster)*(minall.y-1)) to round((1/raster)*(maxall.y+1)) do
                begin
                     p_set_y (y*raster);{ get all points of a plane with specific y value }
                     if intern.length > 2 then p_write_y; { calculation and store }
                end;
                dummy.newobject ('along_y-axis');
           end;
           if axis = 3 then { planes along z axis }
           begin
                for z := round((1/raster)*(minall.z-1)) to round((1/raster)*(maxall.z+1)) do
                begin
                     p_set_z (z*raster);{ get all points of a plane with specific z value }
                     if intern.length > 2 then p_write_z; { calculation and store }
                end;
                dummy.newobject ('along_z-axis');
           end;
           intern.done;
           cleanup (dummy);
     end;
end;

procedure proc_hull_x (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (1,origin,raster,distance,method,false,true,false);
     tmacro(macro^).writeredo ('mesh.hull.x',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_y (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (2,origin,raster,distance,method,false,true,false);
     tmacro(macro^).writeredo ('mesh.hull.y',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_z (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (3,origin,raster,distance,method,false,true,false);
     tmacro(macro^).writeredo ('mesh.hull.z',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_x_inplane (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (1,origin,raster,distance,method,true,true,false);
     tmacro(macro^).writeredo ('mesh.plane.hull.x',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_y_inplane (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (2,origin,raster,distance,method,true,true,false);
     tmacro(macro^).writeredo ('mesh.plane.hull.y',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_z_inplane (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (3,origin,raster,distance,method,true,true,false);
     tmacro(macro^).writeredo ('mesh.plane.hull.z',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_x_point (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (1,origin,raster,distance,method,false,false,true);
     tmacro(macro^).writeredo ('mesh.point.hull.x',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_y_point (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (2,origin,raster,distance,method,false,false,true);
     tmacro(macro^).writeredo ('mesh.point.hull.y',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

procedure proc_hull_z_point (p1,macro : gtk_pointer); cdecl;
var raster,distance : real;
    origin : vector;
    method : integer;
begin
     origin := _getvector (mesh_origin_hull,macro,1);
     raster := _getreal (mesh_raster_hull,macro,2);
     distance := _getreal (mesh_distance_hull,macro,3);
     method := _getitem (mesh_hull,macro,4);
     _cursor_watch;
     proc_convexhull_ok (3,origin,raster,distance,method,false,false,true);
     tmacro(macro^).writeredo ('mesh.point.hull.z',getstring(origin)+' '+getstring(raster)+' '+getstring(distance)+' '+getstring(method));
     _cursor_arrow;
end;

{ ********************************* Mesh outside ***************************** }

procedure proc_mesh_outside (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc : integer;
    listh : tpolyhyper;
    listc,listp : tpolynat;
    found : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
      begin
          _cursor_watch;

{ search and count same points }
          finput^.reference(listh,listc,listp);
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
          dummy.clear;
          if listh.length > 0 then
          begin
               if finput^.getobjectlength > 0 then
                  for oc := 1 to finput^.getobjectlength do
                  begin
                       if finput^.getobjectlinelength (oc) > 0 then
                       begin
                            for lc := 1 to finput^.getobjectlinelength (oc) do
                            begin
                                 if finput^.getlinepointlength (oc,lc) > 0 then
                                 begin
                                      found := false;
                                      for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                      begin
                                           if listc.get(listp.get(finput^.getpobject(oc,lc,pc))) <= 4 then found := true;
                                      end;
                                      if found then
                                      begin
                                           for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                           begin
                                                dummy.newpoint(finput^.getobject(oc,lc,pc));
                                           end;
                                           dummy.newline(finput^.getmaterial(oc,lc));
                                      end;
                                 end;
                            end;
                            dummy.newobject (finput^.getname(oc));
                       end;
                  end;
          end;
          listp.done;
          listc.done;
          listh.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.outside');
          _cursor_arrow;
     end;
end;

{ ********************************* Mesh split ******************************* }

procedure proc_mesh_split (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc,gc,g_p,last_g_p,global_points,global_new : integer;
    ch : integer;
    listh : tpolyhyper;
    listc,listp,points : tpolynat;
    found,ok : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);
     points := Default(tpolynat);

     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
      begin
          _cursor_watch;

{ search and count same points }
          finput^.reference(listh,listc,listp);
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
          dummy.clear;
          if listh.length > 0 then
          begin
               points.init (listh.length);
               global_points := 0;
{ check }
               ch := 0;
               repeat
                    ok := true;
                    inc (ch);
                    writeln ('check '+getstring(ch)+' ...');
                    if finput^.getobjectlength > 0 then
                       for oc := 1 to finput^.getobjectlength do
                       begin
                            if finput^.getobjectlinelength (oc) > 0 then
                            begin
                                 for lc := 1 to finput^.getobjectlinelength (oc) do
                                 begin
                                      if finput^.getlinepointlength (oc,lc) > 0 then
                                      begin
                                           found := false;
                                           global_new := 0;
                                           for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                           begin
                                                { check if connection to other object }
                                                g_p := points.get(listp.get(finput^.getpobject(oc,lc,pc)));
                                                if g_p > 0 then
                                                begin
                                                     found := true;
                                                     if global_new = 0 then global_new := g_p { recycling }
                                                                       else if global_new > g_p then global_new := g_p;
                                                end;
                                           end;
                                           if found then { yes - connect - mark with global_new }
                                           begin
                                                last_g_p := global_new;
                                                for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                begin
                                                     g_p := points.get(listp.get(finput^.getpobject(oc,lc,pc)));
                                                     if g_p > 0 then
                                                     begin
                                                          if last_g_p <> g_p then { no double mark }
                                                          begin
                                                               for gc := 1 to points.length do { mark missing }
                                                                   if points.get (gc) = g_p then
                                                                   begin
                                                                        points.put (gc,global_new);
                                                                        ok := false; { recheck }
                                                                   end;
                                                          end;
                                                          last_g_p := g_p;
                                                     end
                                                     else { if not marked }
                                                     begin
                                                          points.put(listp.get(finput^.getpobject(oc,lc,pc)),global_new);
                                                          ok := false; { recheck }
                                                     end;
                                                end;
                                           end
                                           else { no - own object - mark new }
                                           begin
                                                inc (global_points);
                                                for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                begin
                                                     points.put(listp.get(finput^.getpobject(oc,lc,pc)),global_points);
                                                end;
                                                ok := false; { recheck }
                                           end;
                                      end;
                                 end;
                            end;
                       end;
               until (global_points = 0) or ok;
{ reorder }
               if global_points > 0 then
                  for gc := 1 to global_points do
                  begin
                       found := false;
                       if finput^.getobjectlength > 0 then
                          for oc := 1 to finput^.getobjectlength do
                          begin
                               if finput^.getobjectlinelength (oc) > 0 then
                               begin
                                    for lc := 1 to finput^.getobjectlinelength (oc) do
                                    begin
                                         if finput^.getlinepointlength (oc,lc) > 0 then
                                         begin
                                              g_p := points.get(listp.get(finput^.getpobject(oc,lc,1)));
                                              if g_p = gc then
                                              begin
                                                   for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                   begin
                                                        dummy.newpoint(finput^.getobject(oc,lc,pc));
                                                   end;
                                                   dummy.newline(finput^.getmaterial(oc,lc));
                                                   found := true;
                                              end;
                                         end;
                                    end;
                               end;
                          end;
                       if found then dummy.newobject ('mesh_'+getstring(gc));
                  end;
               points.done;
          end;
          listp.done;
          listc.done;
          listh.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.split');
          _cursor_arrow;
     end;
end;

{ ********************************* Mesh inside ****************************** }

procedure proc_mesh_inside (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc : integer;
    listh : tpolyhyper;
    listc,listp : tpolynat;
    found : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
      begin
          _cursor_watch;

{ search and count same points }
          finput^.reference(listh,listc,listp);
{ smooth points > 4 | works for 3 and 4 points mesh and for 8 points mesh if it an inside }
          dummy.clear;
          if listh.length > 0 then
          begin
               if finput^.getobjectlength > 0 then
                  for oc := 1 to finput^.getobjectlength do
                  begin
                       if finput^.getobjectlinelength (oc) > 0 then
                       begin
                            for lc := 1 to finput^.getobjectlinelength (oc) do
                            begin
                                 if finput^.getlinepointlength (oc,lc) > 0 then
                                 begin
                                      found := true;
                                      for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                      begin
                                           if listc.get(listp.get(finput^.getpobject(oc,lc,pc))) <= 4 then found := false;
                                      end;
                                      if found then
                                      begin
                                           for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                           begin
                                                dummy.newpoint(finput^.getobject(oc,lc,pc));
                                           end;
                                           dummy.newline(finput^.getmaterial(oc,lc));
                                      end;
                                 end;
                            end;
                            dummy.newobject (finput^.getname(oc));
                       end;
                  end;
          end;
          listp.done;
          listc.done;
          listh.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.inside');
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }

procedure proc_mesh_split_xyz (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    a : array[1..3,1..3,1..3] of hyper;
procedure block (v1,v2,v3,v4,v5,v6,v7,v8 : hyper);
begin
     dummy.newpoint (v1);
     dummy.newpoint (v2);
     dummy.newpoint (v3);
     dummy.newpoint (v4);
     dummy.newpoint (v5);
     dummy.newpoint (v6);
     dummy.newpoint (v7);
     dummy.newpoint (v8);
end;
begin
     if finput^.getobjectlength > 0  then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) = 8 then
                         begin
                              a[1,3,3] := finput^.getobject(o,l,1);
                              a[3,3,3] := finput^.getobject(o,l,2);
                              a[3,1,3] := finput^.getobject(o,l,3);
                              a[1,1,3] := finput^.getobject(o,l,4);
                              a[1,3,1] := finput^.getobject(o,l,5);
                              a[3,3,1] := finput^.getobject(o,l,6);
                              a[3,1,1] := finput^.getobject(o,l,7);
                              a[1,1,1] := finput^.getobject(o,l,8);

                              a[2,2,1] := (a[1,1,1]+a[1,3,1]+a[3,1,1]+a[3,3,1])/4; {center z1}
                              a[2,2,2] := (a[1,1,1]+a[1,3,1]+a[3,1,1]+a[3,3,1]+a[1,1,3]+a[1,3,3]+a[3,1,3]+a[3,3,3])/8; {center z2}
                              a[2,2,3] := (a[1,1,3]+a[1,3,3]+a[3,1,3]+a[3,3,3])/4; {center z3}

                              a[1,2,2] := (a[1,1,1]+a[1,1,3]+a[1,3,1]+a[1,3,3])/4; {center x1}
                              a[3,2,2] := (a[3,1,1]+a[3,1,3]+a[3,3,1]+a[3,3,3])/4; {center x3}
                              a[2,1,2] := (a[1,1,1]+a[1,1,3]+a[3,1,1]+a[3,1,3])/4; {center y1}
                              a[2,3,2] := (a[1,3,1]+a[1,3,3]+a[3,3,1]+a[3,3,3])/4; {center y3}

                              a[1,2,1] := (a[1,1,1]+a[1,3,1])/2;
                              a[3,2,1] := (a[3,1,1]+a[3,3,1])/2;
                              a[2,1,1] := (a[1,1,1]+a[3,1,1])/2;
                              a[2,3,1] := (a[1,3,1]+a[3,3,1])/2;

                              a[1,1,2] := (a[1,1,1]+a[1,1,3])/2;
                              a[1,3,2] := (a[1,3,1]+a[1,3,3])/2;
                              a[3,1,2] := (a[3,1,1]+a[3,1,3])/2;
                              a[3,3,2] := (a[3,3,1]+a[3,3,3])/2;

                              a[1,2,3] := (a[1,1,3]+a[1,3,3])/2;
                              a[3,2,3] := (a[3,1,3]+a[3,3,3])/2;
                              a[2,1,3] := (a[1,1,3]+a[3,1,3])/2;
                              a[2,3,3] := (a[1,3,3]+a[3,3,3])/2;

                              block (a[1,2,2],a[2,2,2],a[2,1,2],a[1,1,2],a[1,2,1],a[2,2,1],a[2,1,1],a[1,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[1,3,2],a[2,3,2],a[2,2,2],a[1,2,2],a[1,3,1],a[2,3,1],a[2,2,1],a[1,2,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[2,2,2],a[3,2,2],a[3,1,2],a[2,1,2],a[2,2,1],a[3,2,1],a[3,1,1],a[2,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[2,3,2],a[3,3,2],a[3,2,2],a[2,2,2],a[2,3,1],a[3,3,1],a[3,2,1],a[2,2,1]);
                              dummy.newline(finput^.getmaterial(o,l));

                              block (a[1,2,3],a[2,2,3],a[2,1,3],a[1,1,3],a[1,2,2],a[2,2,2],a[2,1,2],a[1,1,2]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[1,3,3],a[2,3,3],a[2,2,3],a[1,2,3],a[1,3,2],a[2,3,2],a[2,2,2],a[1,2,2]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[2,2,3],a[3,2,3],a[3,1,3],a[2,1,3],a[2,2,2],a[3,2,2],a[3,1,2],a[2,1,2]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[2,3,3],a[3,3,3],a[3,2,3],a[2,2,3],a[2,3,2],a[3,3,2],a[3,2,2],a[2,2,2]);
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.split');
          _cursor_arrow;
     end;
end;

procedure proc_mesh_split_x (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    a : array[1..3,1..3,1..3] of hyper;
procedure block (v1,v2,v3,v4,v5,v6,v7,v8 : hyper);
begin
     dummy.newpoint (v1);
     dummy.newpoint (v2);
     dummy.newpoint (v3);
     dummy.newpoint (v4);
     dummy.newpoint (v5);
     dummy.newpoint (v6);
     dummy.newpoint (v7);
     dummy.newpoint (v8);
end;
begin
     if finput^.getobjectlength > 0  then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) = 8 then
                         begin
                              a[1,3,3] := finput^.getobject(o,l,1);
                              a[3,3,3] := finput^.getobject(o,l,2);
                              a[3,1,3] := finput^.getobject(o,l,3);
                              a[1,1,3] := finput^.getobject(o,l,4);
                              a[1,3,1] := finput^.getobject(o,l,5);
                              a[3,3,1] := finput^.getobject(o,l,6);
                              a[3,1,1] := finput^.getobject(o,l,7);
                              a[1,1,1] := finput^.getobject(o,l,8);

                              a[1,1,2] := (a[1,1,1]+a[1,1,3])/2;
                              a[1,3,2] := (a[1,3,1]+a[1,3,3])/2;
                              a[3,1,2] := (a[3,1,1]+a[3,1,3])/2;
                              a[3,3,2] := (a[3,3,1]+a[3,3,3])/2;

                              block (a[1,3,2],a[3,3,2],a[3,1,2],a[1,1,2],a[1,3,1],a[3,3,1],a[3,1,1],a[1,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[1,3,3],a[3,3,3],a[3,1,3],a[1,1,3],a[1,3,2],a[3,3,2],a[3,1,2],a[1,1,2]);
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.split.x');
          _cursor_arrow;
     end;
end;

procedure proc_mesh_split_y (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    a : array[1..3,1..3,1..3] of hyper;
procedure block (v1,v2,v3,v4,v5,v6,v7,v8 : hyper);
begin
     dummy.newpoint (v1);
     dummy.newpoint (v2);
     dummy.newpoint (v3);
     dummy.newpoint (v4);
     dummy.newpoint (v5);
     dummy.newpoint (v6);
     dummy.newpoint (v7);
     dummy.newpoint (v8);
end;
begin
     if finput^.getobjectlength > 0  then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) = 8 then
                         begin
                              a[1,3,3] := finput^.getobject(o,l,1);
                              a[3,3,3] := finput^.getobject(o,l,2);
                              a[3,1,3] := finput^.getobject(o,l,3);
                              a[1,1,3] := finput^.getobject(o,l,4);
                              a[1,3,1] := finput^.getobject(o,l,5);
                              a[3,3,1] := finput^.getobject(o,l,6);
                              a[3,1,1] := finput^.getobject(o,l,7);
                              a[1,1,1] := finput^.getobject(o,l,8);

                              a[1,2,1] := (a[1,1,1]+a[1,3,1])/2;
                              a[3,2,1] := (a[3,1,1]+a[3,3,1])/2;
                              a[1,2,3] := (a[1,1,3]+a[1,3,3])/2;
                              a[3,2,3] := (a[3,1,3]+a[3,3,3])/2;

                              block (a[1,3,3],a[3,3,3],a[3,2,3],a[1,2,3],a[1,3,1],a[3,3,1],a[3,2,1],a[1,2,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[1,2,3],a[3,2,3],a[3,1,3],a[1,1,3],a[1,2,1],a[3,2,1],a[3,1,1],a[1,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.split.y');
          _cursor_arrow;
     end;
end;

procedure proc_mesh_split_z (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
    a : array[1..3,1..3,1..3] of hyper;
procedure block (v1,v2,v3,v4,v5,v6,v7,v8 : hyper);
begin
     dummy.newpoint (v1);
     dummy.newpoint (v2);
     dummy.newpoint (v3);
     dummy.newpoint (v4);
     dummy.newpoint (v5);
     dummy.newpoint (v6);
     dummy.newpoint (v7);
     dummy.newpoint (v8);
end;
begin
     if finput^.getobjectlength > 0  then
     begin
          _cursor_watch;
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) = 8 then
                         begin
                              a[1,3,3] := finput^.getobject(o,l,1);
                              a[3,3,3] := finput^.getobject(o,l,2);
                              a[3,1,3] := finput^.getobject(o,l,3);
                              a[1,1,3] := finput^.getobject(o,l,4);
                              a[1,3,1] := finput^.getobject(o,l,5);
                              a[3,3,1] := finput^.getobject(o,l,6);
                              a[3,1,1] := finput^.getobject(o,l,7);
                              a[1,1,1] := finput^.getobject(o,l,8);

                              a[2,1,1] := (a[1,1,1]+a[3,1,1])/2;
                              a[2,3,1] := (a[1,3,1]+a[3,3,1])/2;
                              a[2,1,3] := (a[1,1,3]+a[3,1,3])/2;
                              a[2,3,3] := (a[1,3,3]+a[3,3,3])/2;

                              block (a[1,3,3],a[2,3,3],a[2,1,3],a[1,1,3],a[1,3,1],a[2,3,1],a[2,1,1],a[1,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                              block (a[2,3,3],a[3,3,3],a[3,1,3],a[2,1,3],a[2,3,1],a[3,3,1],a[3,1,1],a[2,1,1]);
                              dummy.newline(finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.split.z');
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }
{ ************************************ O ************************************* }

{ ********************************* Smooth o ********************************* }

procedure proc_mesh_smooth_single_o (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listp,listc : tpolynat;
    found,_outside : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
     begin
          _cursor_watch;
{ search and count same points }
          finput^.objectreference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
{ get smoothing points }
                         for oc := 1 to finput^.getobjectlength do
                         begin
                              if pos ('*',finput^.getname (oc)) <> 1 then
                              if finput^.getobjectlinelength(oc) > 0 then
                              begin
                                   for lc := 1 to finput^.getobjectlinelength(oc) do
                                   begin
                                        if finput^.getlinepointlength (oc,lc) > 0 then
                                        begin
                                             found := false;
                                             for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                             begin
                                                  if listp.get (finput^.getpobject (oc,lc,pc)) = ic then found := true;
                                             end;
                                             if found then
                                                for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                begin
                                                     v := v + finput^.getobject (oc,lc,pc);
                                                     inc (vc);
                                                end;
                                        end;
                                   end;
                              end;
                         end;
{ smooth }
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.smooth.single.o',getstring(_outside));
          _cursor_arrow;
     end;
end;

{ *********************************** S ************************************** }

{ ********************************* Smooth s ********************************* }

procedure proc_mesh_smooth_single_s (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listp,listc : tpolynat;
    found,_outside : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
     begin
          _cursor_watch;
{ search and count same points }
          finput^.objectreference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
{ get smoothing points }
                         for oc := 1 to finput^.getobjectlength do
                         begin
                              if pos ('*',finput^.getname (oc)) = 1 then
                              if finput^.getobjectlinelength(oc) > 0 then
                              begin
                                   for lc := 1 to finput^.getobjectlinelength(oc) do
                                   begin
                                        if finput^.getlinepointlength (oc,lc) > 0 then
                                        begin
                                             found := false;
                                             for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                             begin
                                                  if listp.get (finput^.getpobject (oc,lc,pc)) = ic then found := true;
                                             end;
                                             if found then
                                                for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                begin
                                                     v := v + finput^.getobject (oc,lc,pc);
                                                     inc (vc);
                                                end;
                                        end;
                                   end;
                              end;
                         end;
{ smooth }
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.smooth.single.s',getstring(_outside));
          _cursor_arrow;
     end;
end;

{ ***************************** Smooth sticky s ****************************** }

procedure proc_mesh_smooth_sticky_s (p1,macro : gtk_pointer); cdecl;
var oc,lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listc,listp : tpolynat;
    found,_outside : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
     begin
          _cursor_watch;
{ search and count same points }
          finput^.stickyreference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
{ get smoothing points }
                         for oc := 1 to finput^.getobjectlength do
                         begin
                              if pos ('*',finput^.getname (oc)) = 1 then
                              if finput^.getobjectlinelength(oc) > 0 then
                              begin
                                   for lc := 1 to finput^.getobjectlinelength(oc) do
                                   begin
                                        if finput^.getlinepointlength (oc,lc) > 0 then
                                        begin
                                             found := false;
                                             for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                             begin
                                                  if listp.get (finput^.getpobject (oc,lc,pc)) = ic then found := true;
                                             end;
                                             if found then
                                                for pc := 1 to finput^.getlinepointlength (oc,lc) do
                                                begin
                                                     v := v + finput^.getobject (oc,lc,pc);
                                                     inc (vc);
                                                end;
                                        end;
                                   end;
                              end;
                         end;
{ smooth }
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.smooth.sticky.s',getstring(_outside));
          _cursor_arrow;
     end;
end;

{ ************************************* O&S ********************************** }

{ ********************************* Smooth single os ************************* }

procedure proc_mesh_smooth_single_os (p1,macro : gtk_pointer); cdecl;
var lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listp,listc : tpolynat;
    found,_outside : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
     begin
          _cursor_watch;
{ search and count same points }
          finput^.objectreference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
                         for lc := 1 to finput^.getlinelength do
                         begin
                              if finput^.getalllinepointlength (lc) > 0 then
                              begin
                                   found := false;
                                   for pc := 1 to finput^.getalllinepointlength (lc) do
                                   begin
                                        if listp.get (finput^.getpline (lc,pc)) = ic then found := true;
                                   end;
                                   if found then
                                      for pc := 1 to finput^.getalllinepointlength (lc) do
                                      begin
                                           v := v + finput^.getline (lc,pc);
                                           inc (vc);
                                      end;
                              end;
                         end;
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

          cleanup (dummy);
          tmacro(macro^).writeredo ('mesh.smooth.single.os',getstring(_outside));
          _cursor_arrow;
     end;
end;

{ ***************************** Smooth sticky os ****************************** }

procedure proc_mesh_smooth_sticky_os (p1,macro : gtk_pointer); cdecl;
var lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listc,listp : tpolynat;
    found,_outside : boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
      begin
          _cursor_watch;
{ search and count same points }
          finput^.stickyreference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
                         for lc := 1 to finput^.getlinelength do
                         begin
                              if finput^.getalllinepointlength (lc) > 0 then
                              begin
                                   found := false;
                                   for pc := 1 to finput^.getalllinepointlength (lc) do
                                   begin
                                        if listp.get (finput^.getpline (lc,pc)) = ic then found := true;
                                   end;
                                   if found then
                                      for pc := 1 to finput^.getalllinepointlength (lc) do
                                      begin
                                           v := v + finput^.getline (lc,pc);
                                           inc (vc);
                                      end;
                              end;
                         end;
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

           cleanup (dummy);
           tmacro(macro^).writeredo ('mesh.smooth.sticky.os',getstring(_outside));
           _cursor_arrow;
      end;
end;

{ ********************************* Smooth mesh os *************************** }

procedure proc_mesh_smooth (p1,macro : gtk_pointer); cdecl;
var lc,pc,ip,ic,vc : integer;
    v : hyper;
    listh : tpolyhyper;
    listc,listp : tpolynat;
    found,_outside: boolean;
begin
     listh := Default(tpolyhyper);
     listc := Default(tpolynat);
     listp := Default(tpolynat);

     _outside := _getcheckbutton (outside,macro,1);
     if (finput^.getobjectlength > 0) and (finput^.getlinelength > 0) and (finput^.getpointlength > 1)  then
     begin
          _cursor_watch;
{ search and count same points }
          finput^.reference(listh,listc,listp);
          ip := listh.length;
{ smooth points }
          dummy.replace(finput^);
          if ip > 0 then
          begin
               for ic := 1 to ip do
               begin
{ smooth points <= 4 | works for 3 and 4 points mesh and for 8 points mesh if it an outside }
                    if  (not _outside) or (_outside and (listc.get (ic) <= 4)) then
                    begin
                         v := Hzero;
                         vc := 0;
                         for lc := 1 to finput^.getlinelength do
                         begin
                              if finput^.getalllinepointlength (lc) > 0 then
                              begin
                                   found := false;
                                   for pc := 1 to finput^.getalllinepointlength (lc) do
                                   begin
                                        if listp.get (finput^.getpline (lc,pc)) = ic then found := true;
                                   end;
                                   if found then
                                      for pc := 1 to finput^.getalllinepointlength (lc) do
                                      begin
                                           v := v + finput^.getline (lc,pc);
                                           inc (vc);
                                      end;
                              end;
                         end;
                         if vc > 0 then
                         begin
                              v := v / vc;
                              for lc := 1 to finput^.getlinelength do
                              begin
                                   if finput^.getalllinepointlength (lc) > 0 then
                                   begin
                                        for pc := 1 to finput^.getalllinepointlength (lc) do
                                        begin
                                             if listp.get (finput^.getpline (lc,pc)) = ic then dummy.putline(lc,pc,v);
                                        end;
                                   end;
                              end;
                         end;
                    end;
                    progress ('Smooth mesh',ic/ip);
                end;
                progress;
           end;
           listh.done;
           listc.done;
           listp.done;

           cleanup (dummy);
           tmacro(macro^).writeredo ('mesh.smooth',getstring(_outside));
           _cursor_arrow;
      end;
end;

{ **************************************************************************** }
{ **************************************************************************** }

procedure proc_mesh_uniform (p1,macro : gtk_pointer); cdecl;
var a : cube;
    h : hyper;
    mymin,mymax : vector;
    o,l,p : integer;
begin
{ Set mesh right }
     _cursor_watch;
     dummy.clear;
     if finput^.getobjectlength > 0 then
        for o := 1 to finput^.getobjectlength do
        begin
             if finput^.getobjectlinelength (o) > 0 then
             begin
                  for l := 1 to finput^.getobjectlinelength (o) do
                  begin
                       if finput^.getlinepointlength (o,l) = 8 then
                       begin
                            for p := 1 to 8 do
                            begin
                                 h := finput^.getobject(o,l,p);
                                 a[p] := gv(h.x,h.y,h.z);
                            end;
                            mymin := min(min(min(min(min(min(min (a[1],a[2]),a[3]),a[4]),a[5]),a[6]),a[7]),a[8]);
                            mymax := max(max(max(max(max(max(max (a[1],a[2]),a[3]),a[4]),a[5]),a[6]),a[7]),a[8]);
                            a := getminmaxcube (mymin,mymax);
                            swap (invupdown,a,downup); { from default to FEBIO }
                            dummy.newpoint (gh(a[1],finput^.getobject(o,l,1).t));
                            dummy.newpoint (gh(a[2],finput^.getobject(o,l,2).t));
                            dummy.newpoint (gh(a[3],finput^.getobject(o,l,3).t));
                            dummy.newpoint (gh(a[4],finput^.getobject(o,l,4).t));
                            dummy.newpoint (gh(a[5],finput^.getobject(o,l,5).t));
                            dummy.newpoint (gh(a[6],finput^.getobject(o,l,6).t));
                            dummy.newpoint (gh(a[7],finput^.getobject(o,l,7).t));
                            dummy.newpoint (gh(a[8],finput^.getobject(o,l,8).t));
                            dummy.newline (finput^.getmaterial(o,l));
                       end;
                  end;
                  dummy.newobject (finput^.getname(o));
             end;
        end;
     cleanup (dummy); { with updating }
     tmacro(macro^).writeredo ('mesh.uniform');
     _cursor_arrow;
end;

procedure proc_mesh_discrete (p1,macro : gtk_pointer); cdecl;
var raster : real;
    p : integer;
    h : hyper;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          raster := _getreal (discrete,macro,1);
          if raster <> 0.0 then
          begin
               for p := 1 to finput^.getpointlength do
               begin
                    h := finput^.getpoint(p);
                    finput^.putpoint(p,gh(raster*round(h.x/raster),raster*round(h.y/raster),raster*round(h.z/raster),h.t));
               end;
               calculating;
               updating;
               drawing;
               tmacro(macro^).writeredo ('mesh.discrete',getstring(raster));
          end;
          _cursor_arrow;
     end;
end;

{ ***** }

procedure proc_mesh_single (p1,macro : gtk_pointer); cdecl; {TODO : "mesh single" ... }
var plist : tpolyhyper;
    pcountlist,preflist : tpolynat;
begin
     plist := Default(tpolyhyper);
     pcountlist := Default(tpolynat);
     preflist := Default(tpolynat);

{ Set mesh right }
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          {finput^.reference (plist,pcountlist,preflist)} { init of plist, pcountlist and preflist }
          finput^.stickyreference (plist,pcountlist,preflist); { init of plist, pcountlist and preflist }
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.single');
          _cursor_arrow;
     end;
end;

procedure proc_mesh_cleanup (p1,macro : gtk_pointer); cdecl;
var a : cube;
    x : array[1..7] of real;
    error,o,l,p,c,d : integer;
    mean,meanlen,meanarea,meanvol,help : real;
    mean2,meanlen2,meanarea2,meanvol2,len : real;
    oh,h : hyper;
    erase : boolean;
    sub : array[0..5] of integer;
    factor : real;
begin
     _cursor_watch;
     factor := _getreal (cleanup_factor,macro,1);
     repeat
          for p := 0 to 10 do sub[p] := 0;
          mean := 0;
          meanlen := 0;
          meanarea := 0;
          meanvol := 0;
          c := 0;
          d := 0;
          if finput^.getobjectlength > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) = 8 then
                              begin
                                   h := Hzero;
                                   for p := 1 to 8 do
                                   begin
                                        oh := h;
                                        h :=  finput^.getobject(o,l,p);
                                        a[p] := gv(h.x,h.y,h.z);
                                        if oh <> HZero then
                                        begin
                                             mean := mean + getlength(oh-h);
                                             inc (c);
                                        end;
                                   end;
                                   swap (downup,a,invupdown);
                                   meanarea := meanarea + area (a);
                                   meanvol := meanvol + volume (a);
                                   inc (d);
                              end;
                              progress ('Calculate geometry parameters',finput^.getpobject(o,l,1)/finput^.getpointlength);
                         end;
                    end;
             end;
             progress;
          end;
          if d <> 0 then
          begin
               meanlen := (mean / d); { mean line_rows length }
               meanarea := (meanarea / d);
               meanvol := (meanvol / d);
          end;
          if c <> 0 then mean := (mean / c); { mean point distance }
     {     system.writeln (mean,' ',meanlen,' ',meanarea,' ',meanvol);}
          mean2 := mean * factor; { range (0.9*mean)-mean+(0.9*mean) }
          meanlen2 := meanlen * factor;
          meanarea2 := meanarea * factor;
          meanvol2 := meanvol * factor;
     { ***** }
          error := 0;
          if finput^.getobjectlength > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) = 8 then
                              begin
                                   h := Hzero;
                                   len := 0;
                                   for p := 1 to 7 do x[p] := 0;
                                   for p := 1 to 8 do
                                   begin
                                        oh := h;
                                        h :=  finput^.getobject(o,l,p);
                                        a[p] := gv(h.x,h.y,h.z);
                                        if oh <> HZero then
                                        begin
                                             x[p-1] := getlength(oh-h);
                                             len := len + x[p-1];
                                             inc (c);
                                        end;
                                   end;
                                   swap (downup,a,invupdown);
                                   erase := false;
     { Erase segments that not into range }
                                   for p := 1 to 7 do
                                       if not into(x[p],mean-mean2,mean+mean2) then erase := true;
     { Erase lengths that not into range }
                                   if not into(len,meanlen-meanlen2,meanlen+meanlen2) then erase := true;
     { Erase areas that not into range}
                                   help := area (a);
                                   if not into(help,meanarea-meanarea2,meanarea+meanarea2) then erase := true;
     { Erase volumes that not into range}
                                   help := volume (a);
                                   if meanvol >= 0 then
                                   begin
                                        if not into(help,meanvol-meanvol2,meanvol+meanvol2) then erase := true;
                                   end
                                   else if not into(help,meanvol+meanvol2,meanvol-meanvol2) then erase := true;
                                   p := negvolume (a);
                                   sub[p] := sub[p] + 1;
                                   if into (p,1,4) then erase := true;
     { If erase }
                                   if erase then
                                   begin
                                        finput^.markline(o,l);
                                        inc (error);
                                   end;
                              end;
                              progress ('Erase erroneous meshs',finput^.getpobject(o,l,1)/finput^.getpointlength);
                         end;
                    end;
               end;
               progress;
          end;
          writeln ('  Erased elements: '+getstring(error));
     {     for p := 0 to 5 do writeln ('Neg. volume '+getstring(p)+' : '+getstring(sub[p]));}
     { **** }
          finput^.erasemarked;
     until error = 0;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('mesh.cleanup',getstring(factor));
     _cursor_arrow;
end;

{ **************************************************************************** }
{ *********************************** FEM ************************************ }
{ **************************************************************************** }

procedure proc_mesh_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
var min,max : hyper;
begin
     if (tmacro(macro^).parameterlength = 0) or ((tmacro(macro^).getparameter(1) = 'auto') and (tmacro(macro^).getparameter(2) = 'auto')) then { only command }
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
          _setedit (mesh_dimension_min,getstring(gv(min.x,min.y,min.z),3));

          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          _setedit (mesh_dimension_max,getstring(gv(max.x,max.y,max.z),3));
     end
     else
     begin
          min := _gethyper (mesh_dimension_min,macro,1);
          max := _gethyper (mesh_dimension_max,macro,2);
     end;
     tmacro(macro^).writeredo ('mesh.set.minmax','auto auto');
end;

procedure proc_mesh_set_dimension_min (p1,macro : gtk_pointer); cdecl;
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
          _setedit (mesh_dimension_min,getstring(gv(min.x,min.y,min.z),3));
     end
     else
     begin
          min := _gethyper (mesh_dimension_min,macro,1);
     end;
     tmacro(macro^).writeredo ('mesh.set.min','auto');
end;

procedure proc_mesh_set_dimension_max (p1,macro : gtk_pointer); cdecl;
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
          _setedit (mesh_dimension_max,getstring(gv(max.x,max.y,max.z),3));
     end
     else
     begin
          max := _gethyper (mesh_dimension_max,macro,1);
     end;
     tmacro(macro^).writeredo ('mesh.set.max','auto');
end;

{ ********************************* Assign *********************************** }

procedure proc_assign_ref_isotropic_material (p1,macro : gtk_pointer); cdecl;
var o,l,p,w,m : integer;
    v,u : hyper;
    distance : real;
    found : boolean;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          distance := _getreal (febio_distance,macro,1);
          m := _getitem (febio_ref_isotropic_material,macro,2);
          case m of
               0 : w := 10;
               1 : w := 20;
               2 : w := 30;
               3 : w := 40;
               4 : w := 50;
               5 : w := 60;
               6 : w := 70;
               7 : w := 80;
               8 : w := 90;
               else w := 10;
          end;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              found := false;
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   u := finputedit^.searchallpoint(v);
                                   if getlength (u-v) < distance then found := true;
                              end;
                              if found then finput^.putmaterial(o,l,w);
                         end;
                         progress ('Search neighbors from object ('+getstring(o)+').',l/finput^.getobjectlinelength (o));
                    end;
               end;
          end;
          progress;
          updating;
          tmacro(macro^).writeredo ('mesh.assign.ref.isotropic.material',getstring(distance)+' '+getstring(m));
     end;
     _cursor_arrow;
end;

procedure proc_assign_ref_anisotropic_material (p1,macro : gtk_pointer); cdecl;
var o,l,p,w,m : integer;
    v,u : hyper;
    distance : real;
    found : boolean;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          distance := _getreal (febio_distance,macro,1);
          m := _getitem (febio_ref_anisotropic_material,macro,2);
          case m of
               0 : w := 45;
               1 : w := 55;
               2 : w := 46;
               3 : w := 56;
               4 : w := 100;
               5 : w := 110;
               else w := 45;
          end;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         if finput^.getlinepointlength (o,l) > 0 then
                         begin
                              found := false;
                              for p := 1 to finput^.getlinepointlength (o,l) do
                              begin
                                   v := finput^.getobject (o,l,p);
                                   u := finputedit^.searchallpoint(v);
                                   if getlength (u-v) < distance then found := true;
                              end;
                              if found then finput^.putmaterial(o,l,w);
                         end;
                         progress ('Search neighbors from object ('+getstring(o)+').',l/finput^.getobjectlinelength (o));
                    end;
               end;
          end;
          progress;
          updating;
          tmacro(macro^).writeredo ('mesh.assign.ref.anisotropic.material',getstring(distance)+' '+getstring(m));
     end;
     _cursor_arrow;
end;

procedure proc_assign_ref_prescribe (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    prescribe : vector;
    v,u : hyper;
    distance : real;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          distance := _getreal (febio_distance,macro,1);
          prescribe := _getvector (febio_ref_prescribe_attr,macro,2);
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
                                   v := finput^.getobject (o,l,p);
                                   u := finputedit^.searchallpoint(v);
                                   dummy.newpoint(v);
                                   if getlength (u-v) < distance then
                                   begin
                                        dummy.newpoint(v+gh(prescribe,0));
                                        dummy.newline (0);
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                         progress ('Search neighbors from object ('+getstring(o)+').',l/finput^.getobjectlinelength (o));
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          progress;
          finput^.replace(dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.ref.prescribing',getstring(distance)+' '+getstring(prescribe));
     end;
     _cursor_arrow;
end;

procedure proc_assign_ref_fixed (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    fixed : vector;
    v,u : hyper;
    distance : real;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          distance := _getreal (febio_distance,macro,1);
          fixed := _getvector (febio_ref_fixed_attr,macro,2);
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
                                   v := finput^.getobject (o,l,p);
                                   u := finputedit^.searchallpoint(v);
                                   dummy.newpoint(v);
                                   if getlength (u-v) < distance then
                                   begin
                                        dummy.newpoint(v+gh(fixed,0));
                                        dummy.newline (0);
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                         progress ('Search neighbors from object ('+getstring(o)+').',l/finput^.getobjectlinelength (o));
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          progress;
          finput^.replace(dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.ref.fixing',getstring(distance)+' '+getstring(fixed));
     end;
     _cursor_arrow;
end;

procedure proc_assign_ref_force (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    force : vector;
    v,u : hyper;
    distance : real;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          distance := _getreal (febio_distance,macro,1);
          force := _getvector (febio_ref_force_attr,macro,2);
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
                                   v := finput^.getobject (o,l,p);
                                   u := finputedit^.searchallpoint(v);
                                   dummy.newpoint(v);
                                   if getlength (u-v) < distance then
                                   begin
                                        dummy.newpoint(v+gh(force,0));
                                        dummy.newline (0);
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                         progress ('Search neighbors from object ('+getstring(o)+').',l/finput^.getobjectlinelength (o));
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          progress;
          finput^.replace(dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.ref.force',getstring(distance)+' '+getstring(force));
     end;
     _cursor_arrow;
end;

{ ******************************** Assign Objects **************************** }

procedure proc_assign_material (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         finput^.putmaterial(o,l,o);
                    end;
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('mesh.assign.material');
     end;
     _cursor_arrow;
end;

procedure proc_assign_isotropic_material (p1,macro : gtk_pointer); cdecl;
var o,l,w,m : integer;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          m := _getitem (febio_isotropic_material,macro,1);
          case m of
               0 : w := 1000000010;
               1 : w := 1000000020;
               2 : w := 1000000030;
               3 : w := 1000000040;
               4 : w := 1000000050;
               5 : w := 1000000060;
               6 : w := 1000000070;
               7 : w := 1000000080;
               8 : w := 1000000090;
               else w := 1000000010;
          end;
          o := finput^.objectcounter;
          if finput^.getobjectlinelength (o) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    finput^.putmaterial(o,l,w);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('mesh.assign.isotropic.material',getstring(m));
     end;
     _cursor_arrow;
end;

procedure proc_assign_anisotropic_material (p1,macro : gtk_pointer); cdecl;
var o,l,w,m : integer;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          m := _getitem (febio_anisotropic_material,macro,1);
          case m of
               0 : w := 1000000045;
               1 : w := 1000000055;
               2 : w := 1000000046;
               3 : w := 1000000056;
               4 : w := 1000000100;
               5 : w := 1000000110;
               else w := 1000000045;
          end;
          dummy.clear;
          o := finput^.objectcounter;
          if finput^.getobjectlinelength (o) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength (o) do
               begin
                    finput^.putmaterial(o,l,w);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('mesh.assign.anisotropic.material',getstring(m));
     end;
     _cursor_arrow;
end;

procedure proc_assign_sticky (p1,macro : gtk_pointer); cdecl;
var s : utf16;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          s := finput^.getname(finput^.objectcounter);
          if pos ('*',s) <> 1 then finput^.putname(finput^.objectcounter,'*'+s);
          updating;
          tmacro(macro^).writeredo ('mesh.assign.sticky');
     end;
     _cursor_arrow;
end;

procedure proc_assign_prescribe (p1,macro : gtk_pointer); cdecl;
var z,l,p : integer;
    prescribe : vector;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          prescribe := _getvector (febio_prescribe_attr,macro,1);
          dummy.clear;
          z := finput^.objectcounter;
          if finput^.getobjectlinelength (z) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength (z) do
               begin
                    if finput^.getlinepointlength (z,l) > 0 then
                    begin
                         for p := 1 to finput^.getlinepointlength (z,l) do
                         begin
                              dummy.newpoint(finput^.getobject (z,l,p));
                              dummy.newpoint(finput^.getobject (z,l,p)+gh(prescribe,0));
                              dummy.newline (0);
                         end;
                    end;
               end;
              dummy.newobject (finput^.getname(z));
          end;
          finputedit^.append (dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.prescribing',getstring(prescribe));
     end;
     _cursor_arrow;
end;

procedure proc_assign_fixed (p1,macro : gtk_pointer); cdecl;
var z,l,p : integer;
    fixed : vector;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          fixed := _getvector (febio_fixed_attr,macro,1);
          dummy.clear;
          z := finput^.objectcounter;
          if finput^.getobjectlinelength (z) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength (z) do
               begin
                    if finput^.getlinepointlength (z,l) > 0 then
                    begin
                         for p := 1 to finput^.getlinepointlength (z,l) do
                         begin
                              dummy.newpoint(finput^.getobject (z,l,p));
                              dummy.newpoint(finput^.getobject (z,l,p)+gh(fixed,0));
                              dummy.newline (0);
                         end;
                    end;
               end;
              dummy.newobject (finput^.getname(z));
          end;
          finputedit^.append (dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.fixing',getstring(fixed));
     end;
     _cursor_arrow;
end;

procedure proc_assign_force (p1,macro : gtk_pointer); cdecl;
var z,l,p : integer;
    force : vector;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          force := _getvector (febio_force_attr,macro,1);
          dummy.clear;
          z := finput^.objectcounter;
          if finput^.getobjectlinelength (z) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength (z) do
               begin
                    if finput^.getlinepointlength (z,l) > 0 then
                    begin
                         for p := 1 to finput^.getlinepointlength (z,l) do
                         begin
                              dummy.newpoint(finput^.getobject (z,l,p));
                              dummy.newpoint(finput^.getobject (z,l,p)+gh(force,0));
                              dummy.newline (0);
                         end;
                    end;
               end;
              dummy.newobject (finput^.getname(z));
          end;
          finputedit^.append (dummy); { ## ## }
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('mesh.assign.force',getstring(force));
     end;
     _cursor_arrow;
end;

{ ********************************* Solid ************************************ }

procedure proc_generate_solid (mymin,mymax,raster : vector;macro : pointer);
var x,y,z,l : integer;
    raster2 : vector;
    steps : vectornat;
    space : tspacebyte;
    u,v : hyper;
    w,w1,wv,wn : vectornat;
    v2,v3,v4,v5,v6 : boolean;
function hole_bump (hole,bump : boolean) : integer;
var x,y,z : integer;
    b : integer;
begin
     hole_bump := 0;
     for z := 0 to steps.z-1 do
         for y := 0 to steps.y-1 do
             for x := 0 to steps.x-1 do
             begin
                  b := 0;
                  if (space.get (x+1-1,y+1  ,z+1  ) > 0) then inc (b);
                  if (space.get (x+1+1,y+1  ,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1-1,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1+1,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1  ,z+1-1) > 0) then inc (b);
                  if (space.get (x+1  ,y+1  ,z+1+1) > 0) then inc (b);

                  if space.get (x+1,y+1,z+1) = 0  then
                  begin { hole }
                       if hole then
                          if b > 3 then begin space.put (x+1,y+1,z+1,1); inc (hole_bump); end;
                  end
                  else
                  begin { bump - inverse hole }
                       if bump then
                          if b < 3 then begin space.put (x+1,y+1,z+1,0); inc (hole_bump); end;
                  end;
             end;
end;
function ifneighbor (x,y,z : integer) : boolean;
var b : integer;
begin
     b := 0;
     if (space.get (x+1-1,y+1  ,z+1  ) = 1) then inc (b);
     if (space.get (x+1+1,y+1  ,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1-1,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1+1,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1  ,z+1-1) = 1) then inc (b);
     if (space.get (x+1  ,y+1  ,z+1+1) = 1) then inc (b);
     if b = 0 then ifneighbor := false
              else ifneighbor := true;
end;
function edge (x,y,z : integer) : hyper;
begin edge := gh(mymin.x+(x*raster.x)-raster2.x,mymin.y+(y*raster.y)-raster2.y,mymin.z+(z*raster.z)-raster2.z,0); end;
procedure insert (x,y,z,c : integer);
begin
     case c of
          1 : dummy.newpoint (edge (x  ,y  ,z  )); {1}
          2 : dummy.newpoint (edge (x+1,y  ,z  )); {2}
          3 : dummy.newpoint (edge (x+1,y  ,z+1)); {3}
          4 : dummy.newpoint (edge (x  ,y  ,z+1)); {4}
          5 : dummy.newpoint (edge (x  ,y+1,z  )); {5}
          6 : dummy.newpoint (edge (x+1,y+1,z  )); {6}
          7 : dummy.newpoint (edge (x+1,y+1,z+1)); {7}
          8 : dummy.newpoint (edge (x  ,y+1,z+1)); {8}
     end;
end;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          mymin := mymin - 2*raster;
          mymax := mymax + 2*raster;
          steps := round(trunc ((mymax-mymin)/raster)+4);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
writeln ('Generate array.');
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               for z := 1 to finput^.getlinelength do
               begin
                    l := finput^.getalllinepointlength (z);
                    if l > 1 then
                    begin
                         for x := 1 to l-1 do
                         begin
                              u := finput^.getline (z,x);
                              v := finput^.getline (z,x+1);
                              w := gvn (round((u.x-mymin.x)/raster.x),round((u.y-mymin.y)/raster.y),round((u.z-mymin.z)/raster.z));
                              w1 := gvn (round((v.x-mymin.x)/raster.x),round((v.y-mymin.y)/raster.y),round((v.z-mymin.z)/raster.z));
                              wv := w1-w;
                              if round(getlength (wv)) = 0 then space.put (w.x+1,w.y+1,w.z+1,1)
                              else if round(getlength (wv)) = 1 then
                              begin
                                   space.put (w.x+1,w.y+1,w.z+1,1);
                                   space.put (w1.x+1,w1.y+1,w1.z+1,1);
                              end
                              else
                              begin
                                   for y := 1 to round (getlength (wv))-1 do
                                   begin
                                        wn := round(w + y*norm(wv));
                                        space.put (wn.x+1,wn.y+1,wn.z+1,1);
                                   end;
                              end;
                         end;
                    end
                    else
                    begin
                         u := finput^.getline (z,1);
                         w := gvn (round((u.x-mymin.x)/raster.x),round((u.y-mymin.y)/raster.y),round((u.z-mymin.z)/raster.z));
                         space.put (w.x+1,w.y+1,w.z+1,1);
                    end;
                    progress ('Generate array',z/finput^.getlinelength);
               end;
               progress;
               l := 0;
               v2 := _getcheckbutton (fill_holes,macro,2);
               v3 := _getcheckbutton (erase_bumps,macro,3);
               if v2 or v3 then
               begin
                    writeln ('Fill holes and erase bumps in array.');
                    repeat
                          inc (l);
                          writeln ('Stage '+getstring(l)+' ...');
                    until (hole_bump (v2,v3) = 0) or (l > 100);
               end;
               v4 := _getcheckbutton (mesh_dilating,macro,4);
               if v4 then
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) = 0 then
                            begin
                                 if ifneighbor (x,y,z) then space.put (x+1,y+1,z+1,2);
                            end;
                       end;

               raster2 := raster/2;
v5 := _getcheckbutton (solids,macro,5);
if v5 then
begin
writeln ('Generate solid elements.');
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) > 0 then
                            begin
                                 insert (x,y,z,1);
                                 insert (x,y,z,2);
                                 insert (x,y,z,6);
                                 insert (x,y,z,5);
                                 insert (x,y,z,4);
                                 insert (x,y,z,3);
                                 insert (x,y,z,7);
                                 insert (x,y,z,8);
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('Solid_elements');
end;
v6 := _getcheckbutton (shells,macro,6);
if v6 then
begin
writeln ('Generate shell elements.');
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) > 0 then
                            begin
                                 if space.get (x+1-1,y+1  ,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,1); insert (x,y,z,5); insert (x,y,z,8); insert (x,y,z,4); insert (x,y,z,1); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1+1,y+1  ,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,2); insert (x,y,z,3); insert (x,y,z,7); insert (x,y,z,6); insert (x,y,z,2); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1-1,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,4); insert (x,y,z,3); insert (x,y,z,2); insert (x,y,z,1); insert (x,y,z,4); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1+1,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,8); insert (x,y,z,7); insert (x,y,z,6); insert (x,y,z,5); insert (x,y,z,8); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1  ,z+1-1) = 0 then
                                 begin
                                      insert (x,y,z,1); insert (x,y,z,2); insert (x,y,z,6); insert (x,y,z,5); insert (x,y,z,1); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1  ,z+1+1) = 0 then
                                 begin
                                      insert (x,y,z,3); insert (x,y,z,4); insert (x,y,z,8); insert (x,y,z,7); insert (x,y,z,3); dummy.newline (0); { newline }
                                 end;
                            end;
                       end;
               dummy.newobject ('Shell_elements');
end;
               space.done;
               cleanup (dummy);
               tmacro(macro^).writeredo ('mesh.fem.solid',getstring(raster)+' '+getstring(v2)+' '+getstring(v3)+' '+getstring(v4)+' '+getstring(v5)+' '+getstring(v6));

          end;
          _cursor_arrow;
     end;
end;

procedure proc_generate_smooth (mymin,mymax,raster : vector; macro : pointer);
var x,y,z,l,v6 : integer;
    raster2 : vector;
    steps : vectornat;
    space : tspacebyte;
    neighbors : tspacenat;
    points : tpolyhyper;
    u,v : hyper;
    w,w1,wv,wn : vectornat;
    v2,v3,v4,v5,v7,v8 : boolean;
function hole_bump (hole,bump : boolean) : integer;
var x,y,z : integer;
    b : integer;
begin
     hole_bump := 0;
     for z := 0 to steps.z-1 do
         for y := 0 to steps.y-1 do
             for x := 0 to steps.x-1 do
             begin
                  b := 0;
                  if (space.get (x+1-1,y+1  ,z+1  ) > 0) then inc (b);
                  if (space.get (x+1+1,y+1  ,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1-1,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1+1,z+1  ) > 0) then inc (b);
                  if (space.get (x+1  ,y+1  ,z+1-1) > 0) then inc (b);
                  if (space.get (x+1  ,y+1  ,z+1+1) > 0) then inc (b);

                  if space.get (x+1,y+1,z+1) = 0  then
                  begin { hole }
                       if hole then
                          if b > 3 then begin space.put (x+1,y+1,z+1,1); inc (hole_bump); end;
                  end
                  else
                  begin { bump - inverse hole }
                       if bump then
                          if b < 3 then begin space.put (x+1,y+1,z+1,0); inc (hole_bump); end;
                  end;
             end;
end;
function ifneighbor (x,y,z : integer) : boolean;
var b : integer;
begin
     b := 0;
     if (space.get (x+1-1,y+1  ,z+1  ) = 1) then inc (b);
     if (space.get (x+1+1,y+1  ,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1-1,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1+1,z+1  ) = 1) then inc (b);
     if (space.get (x+1  ,y+1  ,z+1-1) = 1) then inc (b);
     if (space.get (x+1  ,y+1  ,z+1+1) = 1) then inc (b);
     if b = 0 then ifneighbor := false
              else ifneighbor := true;
end;
function edge (x,y,z : integer) : hyper;
begin edge := gh(mymin.x+(x*raster.x)-raster2.x,mymin.y+(y*raster.y)-raster2.y,mymin.z+(z*raster.z)-raster2.z,0); end;

function getpoint (x,y,z : integer) : hyper;
var l : integer;
begin l := neighbors.get (x+1,y+1,z+1); if l > 0 then getpoint := points.get (l) else getpoint := Hzero; end;
procedure putpoint (x,y,z : integer;h : hyper);
var l : integer;
begin l := neighbors.get (x+1,y+1,z+1); if l > 0 then points.put (l,h); end;
procedure newpoint (x,y,z : integer);
begin if neighbors.get (x+1,y+1,z+1) = 0 then begin points.put (points.length+1,edge (x,y,z)); neighbors.put (x+1,y+1,z+1,points.length); end; end;

function getsmooth (x,y,z : integer) : hyper;
var l,x1,y1,z1 : integer;
    h,v : hyper;
begin
     l := 0; h := Hzero;
     for z1 := -1 to 1 do
     begin
          v := getpoint (x,y,z+z1);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     for y1 := -1 to 1 do
     begin
          v := getpoint (x,y+y1,z);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     for x1 := -1 to 1 do
     begin
          v := getpoint (x+x1,y,z);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     if l > 0 then getsmooth := h/l
              else getsmooth := Hzero;
end;
function getsmooth2 (x,y,z : integer) : hyper;
var l,x1,y1,z1 : integer;
    h,v : hyper;
begin
     l := 0; h := Hzero;
     for z1 := -1 to 1 do
     begin
          v := getpoint (x,y,z+z1);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     for y1 := -1 to 1 do
     begin
          v := getpoint (x,y+y1,z);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     for x1 := -1 to 1 do
     begin
          v := getpoint (x+x1,y,z);
          if v <> Hzero then begin h := h + v; inc (l); end;
     end;
     if l > 0 then
     begin
          if l = 9 then getsmooth2 := Hzero { inside }
                   else getsmooth2 := h/l; { outside }
     end
     else getsmooth2 := Hzero;
end;

procedure insert (x,y,z,c : integer);
begin
     case c of
          1 : dummy.newpoint (getpoint (x  ,y  ,z  )); {1}
          2 : dummy.newpoint (getpoint (x+1,y  ,z  )); {2}
          3 : dummy.newpoint (getpoint (x+1,y  ,z+1)); {3}
          4 : dummy.newpoint (getpoint (x  ,y  ,z+1)); {4}
          5 : dummy.newpoint (getpoint (x  ,y+1,z  )); {5}
          6 : dummy.newpoint (getpoint (x+1,y+1,z  )); {6}
          7 : dummy.newpoint (getpoint (x+1,y+1,z+1)); {7}
          8 : dummy.newpoint (getpoint (x  ,y+1,z+1)); {8}
     end;
end;
begin
     space := Default(tspacebyte);
     neighbors := Default(tspacenat);
     points := Default(tpolyhyper);

     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          mymin := mymin - 2*raster;
          mymax := mymax + 2*raster;
          steps := round(trunc ((mymax-mymin)/raster)+4);
          if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
          begin
writeln ('Generate array.');
               dummy.clear;
               space.init (steps.x,steps.y,steps.z);
               for z := 1 to finput^.getlinelength do
               begin
                    l := finput^.getalllinepointlength (z);
                    if l > 1 then
                    begin
                         for x := 1 to l-1 do
                         begin
                              u := finput^.getline (z,x);
                              v := finput^.getline (z,x+1);
                              w := gvn (round((u.x-mymin.x)/raster.x),round((u.y-mymin.y)/raster.y),round((u.z-mymin.z)/raster.z));
                              w1 := gvn (round((v.x-mymin.x)/raster.x),round((v.y-mymin.y)/raster.y),round((v.z-mymin.z)/raster.z));
                              wv := w1-w;
                              if round(getlength (wv)) = 0 then space.put (w.x+1,w.y+1,w.z+1,1)
                              else if round(getlength (wv)) = 1 then
                              begin
                                   space.put (w.x+1,w.y+1,w.z+1,1);
                                   space.put (w1.x+1,w1.y+1,w1.z+1,1);
                              end
                              else
                              begin
                                   for y := 1 to round (getlength (wv))-1 do
                                   begin
                                        wn := round(w + y*norm(wv));
                                        space.put (wn.x+1,wn.y+1,wn.z+1,1);
                                   end;
                              end;
                         end;
                    end
                    else
                    begin
                         u := finput^.getline (z,1);
                         w := gvn (round((u.x-mymin.x)/raster.x),round((u.y-mymin.y)/raster.y),round((u.z-mymin.z)/raster.z));
                         space.put (w.x+1,w.y+1,w.z+1,1);
                    end;
                    progress ('Generate array',z/finput^.getlinelength);
               end;
               progress;
               l := 0;
               v2 := _getcheckbutton (fill_holes,macro,2);
               v3 := _getcheckbutton (erase_bumps,macro,3);
               if v2 or v3 then
               begin
                    writeln ('Fill holes and erase bumps in array.');
                    repeat
                          inc (l);
                          writeln ('Stage '+getstring(l)+' ...');
                    until (hole_bump (v2,v3) = 0) or (l > 100);
               end;
               v4 := _getcheckbutton (mesh_dilating,macro,4);
               if v4 then
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) = 0 then
                            begin
                                 if ifneighbor (x,y,z) then space.put (x+1,y+1,z+1,2);
                            end;
                       end;

               neighbors.init (steps.x+1,steps.y+1,steps.z+1);
               points.init;
{ Neighbors }
writeln ('Generate smooth array.');
               raster2 := raster/2;
               for z := 0 to steps.z-1 do
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) > 0 then
                            begin
                                 newpoint (x  ,y  ,z  );
                                 newpoint (x+1,y  ,z  );
                                 newpoint (x+1,y  ,z+1);
                                 newpoint (x  ,y  ,z+1);

                                 newpoint (x  ,y+1,z  );
                                 newpoint (x+1,y+1,z  );
                                 newpoint (x+1,y+1,z+1);
                                 newpoint (x  ,y+1,z+1);
                            end;
                       end;
{ Smooth }
writeln ('Smoothing...');
               v5 := _getcheckbutton (mesh_smoothing_outside,macro,5);
               v6 := _getnat (mesh_smooth,macro,6);
               if not into (v6,1,99) then begin v6 := 3; _setedit (mesh_smooth,'3'); end;
               if not (v5) then
               for l := 1 to v6 do
                   for z := 0 to steps.z do
                       for y := 0 to steps.y do
                           for x := 0 to steps.x do
                           begin
                                v := getsmooth (x,y,z);
                                if v <> Hzero then putpoint (x,y,z,v);
                           end
               else
               for l := 1 to v6 do
                   for z := 0 to steps.z do
                       for y := 0 to steps.y do
                           for x := 0 to steps.x do
                           begin
                                v := getsmooth2 (x,y,z);
                                if v <> Hzero then putpoint (x,y,z,v);
                           end;
{ Elements }
v7 := _getcheckbutton (solids,macro,7);
if v7 then
begin
writeln ('Generate solid elements.');
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) > 0 then
                            begin
                                 insert (x,y,z,1);
                                 insert (x,y,z,2);
                                 insert (x,y,z,6);
                                 insert (x,y,z,5);
                                 insert (x,y,z,4);
                                 insert (x,y,z,3);
                                 insert (x,y,z,7);
                                 insert (x,y,z,8);
                                 dummy.newline (0); { newline }
                            end;
                       end;
               dummy.newobject ('Solid_elements');
end;
v8 := _getcheckbutton (shells,macro,8);
if v8 then
begin
writeln ('Generate shell elements.');
               for z := 0 to steps.z-1 do { Hex8 }
                   for y := 0 to steps.y-1 do
                       for x := 0 to steps.x-1 do
                       begin
                            if space.get (x+1,y+1,z+1) > 0 then
                            begin
                                 if space.get (x+1-1,y+1  ,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,1); insert (x,y,z,5); insert (x,y,z,8); insert (x,y,z,4); insert (x,y,z,1); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1+1,y+1  ,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,2); insert (x,y,z,3); insert (x,y,z,7); insert (x,y,z,6); insert (x,y,z,2); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1-1,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,4); insert (x,y,z,3); insert (x,y,z,2); insert (x,y,z,1); insert (x,y,z,4); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1+1,z+1  ) = 0 then
                                 begin
                                      insert (x,y,z,8); insert (x,y,z,7); insert (x,y,z,6); insert (x,y,z,5); insert (x,y,z,8); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1  ,z+1-1) = 0 then
                                 begin
                                      insert (x,y,z,1); insert (x,y,z,2); insert (x,y,z,6); insert (x,y,z,5); insert (x,y,z,1); dummy.newline (0); { newline }
                                 end;
                                 if space.get (x+1  ,y+1  ,z+1+1) = 0 then
                                 begin
                                      insert (x,y,z,3); insert (x,y,z,4); insert (x,y,z,8); insert (x,y,z,7); insert (x,y,z,3); dummy.newline (0); { newline }
                                 end;
                            end;
                       end;
               dummy.newobject ('Shell_elements');
end;
               points.done;
               neighbors.done;
               space.done;
               cleanup (dummy);
               tmacro(macro^).writeredo ('mesh.fem.smooth',getstring(raster)+' '+getstring(v2)+' '+getstring(v3)+' '+getstring(v4)+' '+
                                                 getstring(v5)+' '+getstring(v6)+' '+getstring(v7)+' '+getstring(v8));
          end;
          _cursor_arrow;
     end;
end;

procedure proc_generate (p1,macro : gtk_pointer); cdecl;
var mymin,mymax,raster : vector;
begin
     mymin := _getvector (mesh_dimension_min);
     mymax := _getvector (mesh_dimension_max);
     raster := _getvector (fem_raster,macro,1);
     if _getcheckbutton (mesh_smoothing) then
     begin
          tmacro(macro^).writeredo ('mesh.set.min',getstring (mymin));
          tmacro(macro^).writeredo ('mesh.set.max',getstring (mymax));
          proc_generate_smooth (mymin,mymax,raster,macro);
     end
     else
     begin
          tmacro(macro^).writeredo ('mesh.set.min',getstring (mymin));
          tmacro(macro^).writeredo ('mesh.set.max',getstring (mymax));
          proc_generate_solid (mymin,mymax,raster,macro);
     end;
end;

procedure proc_generate_smooth_help (p1,macro : gtk_pointer); cdecl;
var mymin,mymax,raster : vector;
begin
     mymin := _getvector (mesh_dimension_min);
     mymax := _getvector (mesh_dimension_max);
     raster := _getvector (fem_raster,macro,1);
     tmacro(macro^).writeredo ('mesh.set.min',getstring (mymin));
     tmacro(macro^).writeredo ('mesh.set.max',getstring (mymax));
     proc_generate_smooth (mymin,mymax,raster,macro);
end;

procedure proc_generate_solid_help (p1,macro : gtk_pointer); cdecl;
var mymin,mymax,raster : vector;
begin
     mymin := _getvector (mesh_dimension_min);
     mymax := _getvector (mesh_dimension_max);
     raster := _getvector (fem_raster,macro,1);
     tmacro(macro^).writeredo ('mesh.set.min',getstring (mymin));
     tmacro(macro^).writeredo ('mesh.set.max',getstring (mymax));
     proc_generate_solid (mymin,mymax,raster,macro);
end;

{ ************************************ FEBio ********************************* }

procedure FEBIO12_write_init (var xml : twritexml;var v02_solver,v03_plot,v04_print,v05_time_steps : integer;var v06_step_size : real;macro : pointer);
var fs,fp,fpr : utf16;
begin
     xml.writeln ('<?xml version="1.0" encoding="ISO-8859-1"?>');
     xml.writeln ('<!-- '+finput^.name+' -->');
     xml.writeln;
     xml.writeln ('<febio_spec version="1.2">');
     xml.writeln;
     v02_solver := _getitem (febio_solver,macro,2);
     case v02_solver of
          0 : fs := ''; {default - skyline}
          1 : fs := xml.subtag (2,'linear_solver type="pardiso"','');
          2 : fs := xml.subtag (2,'linear_solver type="superlu"','');
          3 : fs := xml.subtag (2,'linear_solver type="superlu_mt"','');
          4 : fs := xml.subtag (2,'linear_solver type="wsmp"','');
          5 : fs := xml.subtag (2,'linear_solver type="lusolver"','');
          else fs := ''; {default - skyline}
     end;
     v03_plot := _getitem (febio_plot,macro,3);
     case v03_plot of
          0 : fp := xml.subtag (2,'plot_level type="PLOT_NEVER"','');
          1 : fp := ''; {default PLOT_MAJOR_ITRS}
          2 : fp := xml.subtag (2,'plot_level type="PLOT_MINOR_ITRS"','');
          3 : fp := xml.subtag (2,'plot_level type="PLOT_MUST_POINTS"','');
          else fp := ''; {default PLOT_MAJOR_ITRS}
     end;
     v04_print := _getitem (febio_print,macro,4);
     case v04_print of
          0 : fpr := xml.subtag (2,'print_level type="PRINT_NEVER"','');
          1 : fpr := xml.subtag (2,'print_level type="PRINT_PROGRESS"','');
          2 : fpr := xml.subtag (2,'print_level type="PRINT_MAJOR_ITRS"','');
          3 : fpr := ''; {default PRINT_MINOR_ITRS}
          4 : fpr := xml.subtag (2,'print_level type="PRINT_MINOR_ITRS_EXP"','');
          else fpr := ''; {default PRINT_MINOR_ITRS}
     end;
     v05_time_steps := _getnat (febio_time_steps,macro,5);
     v06_step_size := _getreal (febio_step_size,macro,6);
     xml.write (xml.tag(1,'Control',xml.subtag(2,'title',finput^.name)+
                                    xml.subtag(2,'time_steps',getstring(v05_time_steps))+
                                    xml.subtag(2,'step_size',getstring(v06_step_size))+
                                    xml.subtag(2,'max_refs','15')+
                                    xml.subtag(2,'max_ups','10')+
                                    xml.subtag(2,'dtol','0.001')+
                                    xml.subtag(2,'etol','0.01')+
                                    xml.subtag(2,'rtol','1e+10')+
                                    xml.subtag(2,'lstol','0.9')+
                                    xml.tag(2,'time_stepper',xml.subtag(3,'dtmin','0.01')+
                                                             xml.subtag(3,'dtmax','0.1')+
                                                             xml.subtag(3,'max_retries','5')+
                                                             xml.subtag(3,'opt_iter','10'))+
                                    fs+fp+fpr));
     xml.writeln;
end;

procedure febio2_write_init (var xml : twritexml;var v02_solver,v03_plot,v04_print,v05_time_steps : integer;var v06_step_size : real;macro : pointer);
var fs,fp,fpr : utf16;
begin
     xml.writeln ('<?xml version="1.0" encoding="ISO-8859-1"?>');
     xml.writeln ('<!-- '+finput^.name+' -->');
     xml.writeln;
     xml.writeln ('<febio_spec version="2.0">');
     xml.writeln;
     xml.writeln ('<Module type="solid"/>');
     xml.writeln;
     v02_solver := _getitem (febio_solver,macro,2);
    case v02_solver of
          0 : fs := ''; {default - skyline}
          1 : fs := xml.subtag (2,'linear_solver type="pardiso"','');
          2 : fs := xml.subtag (2,'linear_solver type="superlu"','');
          3 : fs := xml.subtag (2,'linear_solver type="superlu_mt"','');
          4 : fs := xml.subtag (2,'linear_solver type="wsmp"','');
          5 : fs := xml.subtag (2,'linear_solver type="lusolver"','');
          else fs := ''; {default - skyline}
     end;
     v03_plot := _getitem (febio_plot,macro,3);
     case v03_plot of
          0 : fp := xml.subtag (2,'plot_level type="PLOT_NEVER"','');
          1 : fp := ''; {default PLOT_MAJOR_ITRS}
          2 : fp := xml.subtag (2,'plot_level type="PLOT_MINOR_ITRS"','');
          3 : fp := xml.subtag (2,'plot_level type="PLOT_MUST_POINTS"','');
          else fp := ''; {default PLOT_MAJOR_ITRS}
     end;
     v04_print := _getitem (febio_print,macro,4);
     case v04_print of
          0 : fpr := xml.subtag (2,'print_level type="PRINT_NEVER"','');
          1 : fpr := xml.subtag (2,'print_level type="PRINT_PROGRESS"','');
          2 : fpr := xml.subtag (2,'print_level type="PRINT_MAJOR_ITRS"','');
          3 : fpr := ''; {default PRINT_MINOR_ITRS}
          4 : fpr := xml.subtag (2,'print_level type="PRINT_MINOR_ITRS_EXP"','');
          else fpr := ''; {default PRINT_MINOR_ITRS}
     end;
     v05_time_steps := _getnat (febio_time_steps,macro,5);
     v06_step_size := _getreal (febio_step_size,macro,6);
     xml.write (xml.tag(1,'Control',xml.subtag(2,'title',finput^.name)+
                                    xml.subtag(2,'time_steps',getstring(v05_time_steps))+
                                    xml.subtag(2,'step_size',getstring(v06_step_size))+
                                    xml.subtag(2,'max_refs','15')+
                                    xml.subtag(2,'max_ups','10')+
                                    xml.subtag(2,'dtol','0.001')+
                                    xml.subtag(2,'etol','0.01')+
                                    xml.subtag(2,'rtol','1e+10')+
                                    xml.subtag(2,'lstol','0.9')+
                                    xml.tag(2,'time_stepper',xml.subtag(3,'dtmin','0.01')+
                                                             xml.subtag(3,'dtmax','0.1')+
                                                             xml.subtag(3,'max_retries','5')+
                                                             xml.subtag(3,'opt_iter','10'))+
                                    fs+fp+fpr));
     xml.writeln;
end;

procedure febio25_write_init (var xml : twritexml;var v02_solver,v03_plot,v04_print,v05_time_steps : integer;var v06_step_size : real;macro : pointer);
var fs,fp,fpr : utf16;
begin
     xml.writeln ('<?xml version="1.0" encoding="ISO-8859-1"?>');
     xml.writeln ('<!-- '+finput^.name+' -->');
     xml.writeln;
     xml.writeln ('<febio_spec version="2.5">');
     xml.writeln;
     xml.writeln ('<Module type="solid"/>');
     xml.writeln;
     v02_solver := _getitem (febio_solver,macro,2);
    case v02_solver of
          0 : fs := ''; {default - skyline}
          1 : fs := xml.subtag (2,'linear_solver type="pardiso"','');
          2 : fs := xml.subtag (2,'linear_solver type="superlu"','');
          3 : fs := xml.subtag (2,'linear_solver type="superlu_mt"','');
          4 : fs := xml.subtag (2,'linear_solver type="wsmp"','');
          5 : fs := xml.subtag (2,'linear_solver type="lusolver"','');
          else fs := ''; {default - skyline}
     end;
     v03_plot := _getitem (febio_plot,macro,3);
     case v03_plot of
          0 : fp := xml.subtag (2,'plot_level type="PLOT_NEVER"','');
          1 : fp := ''; {default PLOT_MAJOR_ITRS}
          2 : fp := xml.subtag (2,'plot_level type="PLOT_MINOR_ITRS"','');
          3 : fp := xml.subtag (2,'plot_level type="PLOT_MUST_POINTS"','');
          else fp := ''; {default PLOT_MAJOR_ITRS}
     end;
     v04_print := _getitem (febio_print,macro,4);
     case v04_print of
          0 : fpr := xml.subtag (2,'print_level type="PRINT_NEVER"','');
          1 : fpr := xml.subtag (2,'print_level type="PRINT_PROGRESS"','');
          2 : fpr := xml.subtag (2,'print_level type="PRINT_MAJOR_ITRS"','');
          3 : fpr := ''; {default PRINT_MINOR_ITRS}
          4 : fpr := xml.subtag (2,'print_level type="PRINT_MINOR_ITRS_EXP"','');
          else fpr := ''; {default PRINT_MINOR_ITRS}
     end;
     v05_time_steps := _getnat (febio_time_steps,macro,5);
     v06_step_size := _getreal (febio_step_size,macro,6);
     xml.write (xml.tag(1,'Control',xml.subtag(2,'title',finput^.name)+
                                    xml.subtag(2,'time_steps',getstring(v05_time_steps))+
                                    xml.subtag(2,'step_size',getstring(v06_step_size))+
                                    xml.subtag(2,'max_refs','15')+
                                    xml.subtag(2,'max_ups','10')+
                                    xml.subtag(2,'dtol','0.001')+
                                    xml.subtag(2,'etol','0.01')+
                                    xml.subtag(2,'rtol','1e+10')+
                                    xml.subtag(2,'lstol','0.9')+
                                    xml.tag(2,'time_stepper',xml.subtag(3,'dtmin','0.01')+
                                                             xml.subtag(3,'dtmax','0.1')+
                                                             xml.subtag(3,'max_retries','5')+
                                                             xml.subtag(3,'opt_iter','10'))+
                                    fs+fp+fpr));
     xml.writeln;
end;

procedure febio_write_material (var xml : twritexml;x,n : integer;macro : pointer);
var h : hyper;
begin
     h := _gethyper (febio_fibre_direction,macro,3);
     case n of
          1000000010 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="linear elastic"',
                          xml.subtag(3,'E','1000.0')+
                          xml.subtag(3,'v','0.45')));

          1000000020 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="St. Venant-Kirchhoff"',
                          xml.subtag(3,'E','1000.0')+
                          xml.subtag(3,'v','0.45')));

          1000000030 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="neo-Hookean"',
                          xml.subtag(3,'E','1000.0')+
                          xml.subtag(3,'v','0.45')));

          1000000040 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="Mooney-Rivlin"',
                          xml.subtag(3,'c1','1000.0')+
                          xml.subtag(3,'c2','2000.0')+
                          xml.subtag(3,'k','1000')));

          1000000050 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="Veronda-Westmann"',
                          xml.subtag(3,'c1','1000.0')+
                          xml.subtag(3,'c2','2000.0')+
                          xml.subtag(3,'k','1000')));

          1000000060 : begin
                    xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="poroelastic"',
                               xml.subtag(3,'perm','0.001')+
                               xml.subtag(3,'solid_id','???')));
               end;

          1000000070 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="rigid body"',
                          xml.subtag(3,'density','1.0')+
                          xml.subtag(3,'center_of_mass','0.0,0.0,0.0')));

          1000000080 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" name="cartilage" type="TC nonlinear orthotropic"',
                          xml.subtag(3,'c1','1.0')+
                          xml.subtag(3,'c2','0.0')+
                          xml.subtag(3,'k','100')+
                          xml.subtag(3,'beta','4.3,4.3,4.3')+
                          xml.subtag(3,'ksi','4525,4525,4525')+
                          xml.subtag(3,'mat_axis type="local"','0.0,0.0,0.0')));

          1000000090 : xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="Ogden"',
                               xml.subtag(3,'m1','2.4')+
                               xml.subtag(3,'c1','1')+
                               xml.subtag(3,'k','100')));

          1000000045 : begin
                    if _getitem (febio_fibre) = 0 then s := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                    xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="trans iso Mooney-Rivlin"',
                               xml.subtag(3,'c1','13.85')+
                               xml.subtag(3,'c2','0')+
                               xml.subtag(3,'c3','2.07')+
                               xml.subtag(3,'c4','61.44')+
                               xml.subtag(3,'c5','640.7')+
                               xml.subtag(3,'k','100')+
                               xml.subtag(3,'lam_max','1.03')+s));
               end;

          1000000055 : begin
                    if _getitem (febio_fibre) = 0 then s := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                    xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="trans iso Veronda-Westmann"',
                               xml.subtag(3,'c1','13.85')+
                               xml.subtag(3,'c2','0.0')+
                               xml.subtag(3,'c3','2.07')+
                               xml.subtag(3,'c4','61.44')+
                               xml.subtag(3,'c5','640.7')+
                               xml.subtag(3,'k','100.0')+
                               xml.subtag(3,'lam_max','1.03')+s));
               end;

          1000000100 : begin
                     if _getitem (febio_fibre) = 0 then s := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                     xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="muscle material"',
                                xml.subtag(3,'g1','500')+
                                xml.subtag(3,'g2','500')+
                                xml.subtag(3,'p1','0.05')+
                                xml.subtag(3,'p2','6.6')+
                                xml.subtag(3,'smax','300000')+
                                xml.subtag(3,'lofl','1.07')+
                                xml.subtag(3,'lam_max','1.4')+
                                xml.subtag(3,'k','1000000')+s));
                end;

          1000000110 : begin
                     if _getitem (febio_fibre) = 0 then s := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                     xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="tendon material"',
                                xml.subtag(3,'g1','50000')+
                                xml.subtag(3,'g2','50000')+
                                xml.subtag(3,'l1','2700000')+
                                xml.subtag(3,'l2','46.4')+
                                xml.subtag(3,'lam_max','1.03')+
                                xml.subtag(3,'k','10000000')+s));
                end;

          1000000046 : begin
                    s := xml.tag(3,'active_contraction lc="1"',xml.subtag(4,'ca0','4.35')+
                                                               xml.subtag(4,'beta','4.75')+
                                                               xml.subtag(4,'l0','1.58')+
                                                               xml.subtag(4,'refl','2.04'));
                    if _getitem (febio_fibre) = 0 then t := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                    xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="trans iso Mooney-Rivlin"',
                               xml.subtag(3,'c1','13.85')+
                               xml.subtag(3,'c2','0')+
                               xml.subtag(3,'c3','2.07')+
                               xml.subtag(3,'c4','61.44')+
                               xml.subtag(3,'c5','640.7')+
                               xml.subtag(3,'k','100')+
                               xml.subtag(3,'lam_max','1.03')+t+s));
               end;

          1000000056 : begin
                    s := xml.tag(3,'active_contraction lc="2"',xml.subtag(4,'ca0','4.35')+
                                                               xml.subtag(4,'beta','4.75')+
                                                               xml.subtag(4,'l0','1.58')+
                                                               xml.subtag(4,'refl','2.04'));
                    if _getitem (febio_fibre) = 0 then t := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                    xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="trans iso Veronda-Westmann"',
                               xml.subtag(3,'c1','13.85')+
                               xml.subtag(3,'c2','0.0')+
                               xml.subtag(3,'c3','2.07')+
                               xml.subtag(3,'c4','61.44')+
                               xml.subtag(3,'c5','640.7')+
                               xml.subtag(3,'k','100.0')+
                               xml.subtag(3,'lam_max','1.03')+t+s));
               end;

          1000000101 : begin
                     s := xml.tag(3,'active_contraction lc="3"',xml.subtag(4,'ca0','4.35')+
                                                                xml.subtag(4,'beta','4.75')+
                                                                xml.subtag(4,'l0','1.58')+
                                                                xml.subtag(4,'refl','2.04'));
                     if _getitem (febio_fibre) = 0 then t := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                     xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="muscle material"',
                                xml.subtag(3,'g1','500')+
                                xml.subtag(3,'g2','500')+
                                xml.subtag(3,'p1','0.05')+
                                xml.subtag(3,'p2','6.6')+
                                xml.subtag(3,'smax','300000')+
                                xml.subtag(3,'lofl','1.07')+
                                xml.subtag(3,'lam_max','1.4')+
                                xml.subtag(3,'k','1000000')+t+s));
                end;

          1000000111 : begin
                     if _getitem (febio_fibre) = 0 then s := xml.subtag(3,'fiber type="vector"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z));
                     xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="tendon material"',
                                xml.subtag(3,'g1','50000')+
                                xml.subtag(3,'g2','50000')+
                                xml.subtag(3,'l1','2700000')+
                                xml.subtag(3,'l2','46.4')+
                                xml.subtag(3,'lam_max','1.03')+
                                xml.subtag(3,'k','10000000')+s));
                end;

          else xml.write (xml.tag(2,'material id="'+getstring(x)+'" type="linear elastic"',
                          xml.subtag(3,'E','1000.0')+
                          xml.subtag(3,'v','0.45')));
     end;
end;

procedure febio_write_elements (var xml : twritexml;var myinput : pcloud;var matlist : tpolynat;var pcountlist : tpolynat;var preflist : tpolynat;var peraselist : tpolybyte);
var z,l,p,element : integer;
    procedure writedown (const s : utf16;max,side : integer);
    var test1,test2 : byte;
        count,count1 : integer;
    begin
{ Test for errors - resulting in Negative Jacobians }
         test1 := 0;
         for count := 1 to max do
         begin
              p := myinput^.getpline (z,count);
              if pcountlist.get(preflist.get(p)) > 1 then inc(test1);
         end;
         test2 := 0;
         for count := 1 to max-1 do
         begin
              for count1 := count+1 to max do
              begin
                   if preflist.get(myinput^.getpline (z,count)) = preflist.get(myinput^.getpline (z,count1)) then inc(test2);
              end;
         end;
         if test2 > 0 then { same vertex inside element }
         begin
              write (#13);
              writeln (fillup('  Error! Same vertex found in material ('+getstring(matlist.search(myinput^.getallmaterial (z)))+') after: '+getstring(element)+'. Now deleted!',length(liball.output_write),' '));
              peraselist.put (z,1);
         end
         else if test1 < side then { no side with connection }
         begin
              write (#13);
              writeln (fillup('  Error! Single unconnected element in material ('+getstring(matlist.search(myinput^.getallmaterial (z)))+') after: '+getstring(element)+'. Now deleted!',length(liball.output_write),' '));
              peraselist.put (z,1);
         end
         else
         begin
              inc (element);
              xml.write (#9+#9+#9+'<'+s+' id="'+getstring(element)+'" mat="'+getstring(matlist.search(myinput^.getallmaterial (z)))+'">');
              for count := 1 to max do
              begin
                   p := myinput^.getpline (z,count);
                   if count = max then xml.write (getstring(preflist.get(p)))
                                  else xml.write (getstring(preflist.get(p))+',');
              end;
              xml.writeln ('</'+s+'>');
         end;
    end;
begin
     { writeln -> progress }
     xml.writeln (#9+#9+'<Elements>');
     element := 0;
     for z := 1 to myinput^.getlinelength do
     begin
          l := myinput^.getalllinepointlength (z);
          if l = 8 then writedown ('hex8',8,4) { Hex8 }
          else if l = 6 then writedown ('penta6',6,3) { Penta6 }
          else if l = 5 then
          begin
               if myinput^.getline (z,1) = myinput^.getline (z,5) then writedown ('quad4',4,2); { Shell Quad4 }
          end
          else if l = 4 then
          begin
               if myinput^.getline (z,1) <> myinput^.getline (z,4) then writedown ('tet4',4,3) { Tet4 }
                                                                   else writedown ('tri3',3,2); { Shell Tri3 }
          end;
          progress ('Write elements',z/myinput^.getlinelength);
     end;
     progress;
     xml.writeln (#9+#9+'</Elements>');
end;

procedure febio2_write_elements (var xml : twritexml;var myinput : pcloud;var matlist : tpolynat;var pcountlist : tpolynat;var preflist : tpolynat;var peraselist : tpolybyte);
var z,l,p,element,mat,oldmat : integer;
    procedure writedown (const s : utf16;max,side : integer);
    var test1,test2 : byte;
        count,count1 : integer;
    begin
         mat := matlist.search(myinput^.getallmaterial (z));
         if mat <> oldmat then
         begin
              if oldmat <> -1 then xml.writeln (#9+#9+'</Elements>');
              xml.writeln (#9+#9+'<Elements type="'+s+'" mat="'+getstring(mat)+'" name="part'+getstring(mat)+'">');
              oldmat := mat;
         end;
{ Test for errors - resulting in Negative Jacobians }
         test1 := 0;
         for count := 1 to max do
         begin
              p := myinput^.getpline (z,count);
              if pcountlist.get(preflist.get(p)) > 1 then inc(test1);
         end;
         test2 := 0;
         for count := 1 to max-1 do
         begin
              for count1 := count+1 to max do
              begin
                   if preflist.get(myinput^.getpline (z,count)) = preflist.get(myinput^.getpline (z,count1)) then inc(test2);
              end;
         end;
         if test2 > 0 then { same vertex inside element }
         begin
              write (#13);
              writeln (fillup('  Error! Same vertex found in material ('+getstring(mat)+') after: '+getstring(element)+'. Now deleted!',length(liball.output_write),' '));
              peraselist.put (z,1);
         end
         else if test1 < side then { no side with connection }
         begin
              write (#13);
              writeln (fillup('  Error! Single unconnected element in material ('+getstring(mat)+') after: '+getstring(element)+'. Now deleted!',length(liball.output_write),' '));
              peraselist.put (z,1);
         end
         else
         begin
              inc (element);
              xml.write (#9+#9+#9+'<elem id="'+getstring(element)+'">');
              for count := 1 to max do
              begin
                   p := myinput^.getpline (z,count);
                   if count = max then xml.write (getstring(preflist.get(p)))
                                  else xml.write (getstring(preflist.get(p))+',');
              end;
              xml.writeln ('</elem>');
         end;
    end;
begin
     { writeln -> progress }
     element := 0;
     oldmat := -1;
     for z := 1 to myinput^.getlinelength do
     begin
          l := myinput^.getalllinepointlength (z);
          if l = 8 then writedown ('hex8',8,4) { Hex8 }
          else if l = 6 then writedown ('penta6',6,3) { Penta6 }
          else if l = 5 then
          begin
               if myinput^.getline (z,1) = myinput^.getline (z,5) then writedown ('quad4',4,2); { Shell Quad4 }
          end
          else if l = 4 then
          begin
               if myinput^.getline (z,1) <> myinput^.getline (z,4) then writedown ('tet4',4,3) { Tet4 }
                                                                   else writedown ('tri3',3,2) { Shell Tri3 }
          end;
          progress ('Write elements',z/myinput^.getlinelength);
     end;
     progress;
     xml.writeln (#9+#9+'</Elements>');
end;

procedure febio_write_boundary (var xml : twritexml;var my2input : pcloud;var plist : tpolyhyper;const s : utf16);
var z : integer;
    h,q : hyper;
    first : boolean;
begin
     if my2input <> nil then
     if my2input^.getlinelength > 0 then
     begin
{ Write prescribed datas }
{ x }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.x <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+'>');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'" bc="x"',getstring(h.x)));
               end;
               progress ('Write '+s+' x datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
{ y }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.y <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+'>');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'" bc="y"',getstring(h.y)));
               end;
               progress ('Write '+s+' y datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
{ z }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.z <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+'>');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'" bc="z"',getstring(h.z)));
               end;
               progress ('Write '+s+' z datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
     end;
end;

procedure febio2_write_boundary (var xml : twritexml;var my2input : pcloud;var plist : tpolyhyper;const s : utf16);
var z : integer;
    h,q : hyper;
    first : boolean;
begin
     if my2input <> nil then
     if my2input^.getlinelength > 0 then
     begin
{ Write prescribed datas }
{ x }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.x <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+' bc="x">');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'"',getstring(h.x)));
               end;
               progress ('Write '+s+' x datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
{ y }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.y <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+' bc="y">');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'"',getstring(h.y)));
               end;
               progress ('Write '+s+' y datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
{ z }     first := true;
          for z := 1 to plist.length do
          begin
               q := plist.get(z);
               h := my2input^.vector_at (q);
               if h <> Hmin then
               if h.z <> 0 then
               begin
                    if first then
                    begin
                         xml.writeln (#9+#9+'<'+s+' bc="z">');
                         first := false;
                    end;
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'"',getstring(h.z)));
               end;
               progress ('Write '+s+' z datas',z/plist.length);
          end;
          if not first then xml.writeln (#9+#9+'</'+s+'>');
          progress;
     end;
end;

procedure febio_write_end (var xml : twritexml;var v15_output : boolean;macro : pointer);
begin
     xml.writeln (xml.tag (1,'LoadData',
                  xml.tag (2,'loadcurve id="1" type="smooth"',
                          xml.subtag (3,'loadpoint','0,0')+
	                  xml.subtag (3,'loadpoint','1,1'))));
     xml.writeln (xml.tag (1,'LoadData',
                  xml.tag (2,'loadcurve id="2" type="smooth"',
                          xml.subtag (3,'loadpoint','0,0')+
	                  xml.subtag (3,'loadpoint','1,1'))));
     xml.writeln (xml.tag (1,'LoadData',
                  xml.tag (2,'loadcurve id="3" type="smooth"',
                          xml.subtag (3,'loadpoint','0,0')+
	                  xml.subtag (3,'loadpoint','1,1'))));

     v15_output := _getcheckbutton (togglefebiooutput,macro,15);
     if v15_output then
     xml.writeln (xml.tag (1,'Output',
                  xml.tag (2,'logfile',
                          xml.subtag (3,'node_data data="x;y;z;ux;uy;uz;p;vx;vy;vz" file="data.plot" delim=","','')+ { nodal position; nodal displacement; fluid pressure; solid velocity }
                          xml.subtag (3,'element_data data="sx;sy;sz;sxy;syz;sxz;Ex;Ey;Ez;Exy;Eyz;Exz" file="element.plot" delim=","','')+ { Cauchy stress; Green-Lagrange strain }
                          xml.subtag (3,'rigid_body_data data="x;y;z;qx;qy;qz;qw;Fx;Fy;Fz;Mx;My;Mz" file="rigid.plot" delim=","','')))); { center of mass; rotation quaternion; force; torque }
end;

var febio_filename : utf16chars7;

procedure p_proc_generate_febio (v01_version : integer;sticky : boolean;macro : pointer);
var xml : twritexml;
    h,q : hyper;
    plist : tpolyhyper;
    pcountlist,preflist : tpolynat;
    peraselist : tpolybyte;
    z,l,element : integer;
    myinput,my2input : pcloud;
    matlist : tpolynat;
    v02_solver,v03_plot,v04_print,v05_time_steps : integer;
    v07_geometry,v08_fibre,v11_prescribe,v12_fixed,v13_force,v14_pressure : integer;
    v06_step_size,v10_shell_thickness : real;
    v09_fibre_direction : vector;
    v15_output : boolean;
begin
     plist := Default(tpolyhyper);
     pcountlist := Default(tpolynat);
     preflist := Default(tpolynat);
     peraselist := Default(tpolybyte);
     matlist := Default(tpolynat);

     if febio_filename <> '' then
     begin
          _cursor_watch;
          if xml.save (febio_filename) then
begin
          matlist.init;
{ Init }
          writeln ('Write init section.');
          case v01_version of
               0 : FEBIO12_write_init (xml,v02_solver,v03_plot,v04_print,v05_time_steps,v06_step_size,macro);
               1 : FEBIO2_WRITE_INIT (xml,v02_solver,v03_plot,v04_print,v05_time_steps,v06_step_size,macro);
               2 : FEBIO25_WRITE_INIT (xml,v02_solver,v03_plot,v04_print,v05_time_steps,v06_step_size,macro);
          end;
          v07_geometry := _getitem (febio_geometry,macro,7);
          case v07_geometry of
               0 : myinput := @red;
               1 : myinput := @green;
               2 : myinput := @blue;
               3 : myinput := @yellow;
               4 : myinput := @cyan;
               5 : myinput := @purple;
               else myinput := @red;
          end;
          if myinput^.getpointlength > 0 then
          begin
{ Material }
               { look after materials }
               myinput^.getmateriallist (matlist);
               writeln ('Write materials.');
               if matlist.length > 0 then
               begin
                    l := 1;
                    xml.writeln (#9+'<Material>');
                    for z := 1 to matlist.length do
                    begin
                         case matlist.get(z) of
                              1000000010 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000010,macro); inc (l); end;
                              1000000020 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000020,macro); inc (l); end;
                              1000000030 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000030,macro); inc (l); end;
                              1000000040 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000040,macro); inc (l); end;
                              1000000050 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000050,macro); inc (l); end;
                              1000000045 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000045,macro); inc (l); end;
                              1000000055 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000055,macro); inc (l); end;
                              1000000046 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000046,macro); inc (l); end;
                              1000000056 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000056,macro); inc (l); end;
                              1000000060 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000060,macro); inc (l); end;
                              1000000070 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000070,macro); inc (l); end;
                              1000000080 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000080,macro); inc (l); end;
                              1000000100 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000100,macro); inc (l); end;
                              1000000110 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000110,macro); inc (l); end;
                              1000000090 : begin FEBIO_WRITE_MATERIAL (xml,l,1000000090,macro); inc (l); end;
                              else begin FEBIO_WRITE_MATERIAL (xml,l,matlist.get(z),macro); inc (l); end;
                         end;
                    end;
                    xml.writeln (#9+'</Material>');
               end;
               xml.writeln;
{ ****** }
               xml.writeln (#9+'<Geometry>');
               writeln ('Calculate geometry references (nodes, elements and elementdata).');
               if not sticky then myinput^.reference (plist,pcountlist,preflist) { init of plist, pcountlist and preflist }
                             else myinput^.stickyreference (plist,pcountlist,preflist); { init of plist, pcountlist and preflist }
{ ****** }

{ Write node - 1.2, 2.0 and 2.5 }
               writeln ('Write nodes.');
               xml.writeln (#9+#9+'<Nodes>');
               for z := 1 to plist.length do
               begin
                    h := plist.get (z);
                    xml.write (xml.subtag(3,'node id="'+getstring(z)+'"',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z)));
               end;
               xml.writeln (#9+#9+'</Nodes>');

{ Write elements }
               peraselist.init (preflist.length);
               case v01_version of
                    0 : FEBIO_WRITE_ELEMENTS (xml,myinput,matlist,pcountlist,preflist,peraselist);
                    1,2 : FEBIO2_WRITE_ELEMENTS (xml,myinput,matlist,pcountlist,preflist,peraselist);
               end;

               if v01_version < 2 then { for 2.5 problems with lid - local ids }
               begin
{ Write element datas - 1.2 and 2.0 }
                    { writeln -> progress }
                    v08_fibre := _getitem (febio_fibre,macro,8);
                    case v08_fibre of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    v09_fibre_direction := _getvector (febio_fibre_direction,macro,9);
                    v10_shell_thickness := _getreal (febio_shell_thickness,macro,10);
                    if my2input <> nil then
                    if my2input^.getlinelength > 0 then
                    begin
                         xml.writeln (#9+#9+'<ElementData>');
                         element := 0;
                         for z := 1 to myinput^.getlinelength do
                         begin
                              if peraselist.get(z) = 0 then
                              begin
                                   l := myinput^.getalllinepointlength (z);
                                   if l = 8 then { Hex8 }
                                   begin
                                        inc (element);
                                        q := (myinput^.getline(z,1)+myinput^.getline(z,2)+myinput^.getline(z,3)+myinput^.getline(z,4)+myinput^.getline(z,5)+myinput^.getline(z,6)+myinput^.getline(z,7)+myinput^.getline(z,8))/8;
                                        h := norm(my2input^.searchvector (q));
                                        if h = Hmin then h := gh(v09_fibre_direction,0);
                                        xml.write (xml.subtag(3,'element id = "'+getstring(element)+'"',
                                                   xml.subsubtag ('fiber',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z))));
                                   end
                                   else if l = 6 then { Penta6 }
                                   begin
                                        inc (element);
                                        q := (myinput^.getline(z,1)+myinput^.getline(z,2)+myinput^.getline(z,3)+myinput^.getline(z,4)+myinput^.getline(z,5)+myinput^.getline(z,6))/6;
                                        h := norm(my2input^.searchvector (q));
                                        if h = Hmin then h := gh(v09_fibre_direction,0);
                                        xml.write (xml.subtag(3,'element id = "'+getstring(element)+'"',
                                                   xml.subsubtag ('fiber',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z))));
                                   end
                                   else if l = 5 then
                                   begin
                                        if myinput^.getline (z,1) = myinput^.getline (z,5) then { Shell Quad4 }
                                        begin
                                             inc (element);
                                             q := (myinput^.getline(z,1)+myinput^.getline(z,2)+myinput^.getline(z,3)+myinput^.getline(z,4))/4;
                                             h := my2input^.search3dpoint (q);
                                             if h = Hmin then h := gh(0,0,0,v10_shell_thickness);
                                             xml.write (xml.subtag(3,'element id = "'+getstring(element)+'"',
                                                        xml.subsubtag ('thickness',getstring(h.t))));
                                        end;
                                   end
                                   else if l = 4 then
                                   begin
                                        if myinput^.getline (z,1) <> myinput^.getline (z,4) then { Tet4 }
                                        begin
                                             inc (element);
                                             q := (myinput^.getline(z,1)+myinput^.getline(z,2)+myinput^.getline(z,3)+myinput^.getline(z,4))/4;
                                             h := norm(my2input^.searchvector (q));
                                             if h = Hmin then h := gh(v09_fibre_direction,0);
                                             xml.write (xml.subtag(3,'element id = "'+getstring(element)+'"',
                                                        xml.subsubtag ('fiber',getstring(h.x)+','+getstring(h.y)+','+getstring(h.z))));
                                        end
                                        else { Shell Tri3 }
                                        begin
                                             inc (element);
                                             q := (myinput^.getline(z,1)+myinput^.getline(z,2)+myinput^.getline(z,3))/3;
                                             h := my2input^.search3dpoint (q);
                                             if h = Hmin then h := gh(0,0,0,v10_shell_thickness);
                                             xml.write (xml.subtag(3,'element id = "'+getstring(element)+'"',
                                                        xml.subsubtag ('thickness',getstring(h.t))));
                                        end;
                                   end;
                              end;
                              progress ('Write element datas',z/myinput^.getlinelength);
                         end;
                         xml.writeln (#9+#9+'</ElementData>');
                         progress;
                    end;
               end
               else if v01_version = 2 then
               begin
                    v08_fibre := _getitem (febio_fibre,macro,8);
                    v09_fibre_direction := _getvector (febio_fibre_direction,macro,9);
                    v10_shell_thickness := _getreal (febio_shell_thickness,macro,10);
{ Write node datas - 2.5 }
{                    v11_prescribe := _getitem (febio_prescribe,macro,11);
                    case v11_prescribe of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    if my2input <> nil then
                    if my2input^.getlinelength > 0 then
                    begin
                         xml.writeln (#9+#9+'<NodeData name="prescribe" node_set="set1">');
                         first := true;
                         for z := 1 to plist.length do
                         begin
                              q := plist.get(z);
                              h := my2input^.vector_at (q);
                              if h <> Hmin then
                              if h.x <> 0 then
                              begin
                                   if first then
                                   begin
                                        xml.writeln (#9+#9+'<'+s+'>');
                                        first := false;
                                   end;
                                   xml.write (xml.subtag(3,'node id="'+getstring(z)+'" bc="x"',getstring(h.x)));
                              end;
                              progress ('Write node datas',z/plist.length);
                         end;
                         if not first then xml.writeln (#9+#9+'</'+s+'>');
                         xml.writeln (#9+#9+'</NodeData>');
                         progress;
                    end;}
               end
               else
               begin
                    v08_fibre := _getitem (febio_fibre,macro,8);
                    v09_fibre_direction := _getvector (febio_fibre_direction,macro,9);
                    v10_shell_thickness := _getreal (febio_shell_thickness,macro,10);
               end;
               xml.writeln (#9+'</Geometry>');
               xml.writeln;

               if v01_version < 2 then { for 2.5 problems with lid - local ids }
               begin
{ Boundary }
                    xml.writeln (#9+'<Boundary>');
                    v11_prescribe := _getitem (febio_prescribe,macro,11);
                    case v11_prescribe of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    case v01_version of
                         0 : FEBIO_WRITE_BOUNDARY (xml,my2input,plist,'prescribe');
                         1 : FEBIO2_WRITE_BOUNDARY (xml,my2input,plist,'prescribe');
                    end;

                    v12_fixed := _getitem (febio_fixed,macro,12);
                    case v12_fixed of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    case v01_version of
                         0 : FEBIO_WRITE_BOUNDARY (xml,my2input,plist,'fix');
                         1 : FEBIO2_WRITE_BOUNDARY (xml,my2input,plist,'fix');
                    end;

{ Write force datas }
                    v13_force := _getitem (febio_force,macro,13);
                    case v13_force of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    case v01_version of
                         0 : FEBIO_WRITE_BOUNDARY (xml,my2input,plist,'force');
                         1 : FEBIO2_WRITE_BOUNDARY (xml,my2input,plist,'force');
                    end;

                    v14_pressure := 0; { dummy for pressure - 14 }
                    case v14_pressure of
                         1 : my2input := @red;
                         2 : my2input := @green;
                         3 : my2input := @blue;
                         4 : my2input := @yellow;
                         5 : my2input := @cyan;
                         6 : my2input := @purple;
                         else my2input := nil;
                    end;
                    case v01_version of
                         0 : FEBIO_WRITE_BOUNDARY (xml,my2input,plist,'pressure');
                         1 : FEBIO2_WRITE_BOUNDARY (xml,my2input,plist,'pressure');
                    end;

                    xml.writeln (#9+'</Boundary>');
                    xml.writeln;
               end
               else
               begin
                    v11_prescribe := _getitem (febio_prescribe,macro,11);
                    v12_fixed := _getitem (febio_fixed,macro,12);
                    v13_force := _getitem (febio_force,macro,13);
                    v14_pressure := 0; { dummy for pressure - 14 }
               end;

               peraselist.done;
               preflist.done;
               pcountlist.done;
               plist.done;

               FEBIO_WRITE_END (xml,v15_output,macro);
          end
          else { no constraints }
          begin
               v08_fibre := _getitem (febio_fibre,macro,8);
               v09_fibre_direction := _getvector (febio_fibre_direction,macro,9);
               v10_shell_thickness := _getreal (febio_shell_thickness,macro,10);
               v11_prescribe := _getitem (febio_prescribe,macro,11);
               v12_fixed := _getitem (febio_fixed,macro,12);
               v13_force := _getitem (febio_force,macro,13);
               v14_pressure := 0; { dummy for pressure - 14 }
          end;
          xml.writeln ('</febio_spec>');
          xml.done;
          matlist.done;
          case v01_version of
               0 : tmacro(macro^).writeredo ('generate.febio',getstring(v02_solver)+' '+getstring(v03_plot)+' '+getstring(v04_print)+' '+
                                                     getstring(v05_time_steps)+' '+getstring(v06_step_size)+' '+
                                                     getstring(v07_geometry)+' '+getstring(v08_fibre)+' '+getstring(v09_fibre_direction)+' '+getstring(v10_shell_thickness)+' '+
                                                     getstring(v11_prescribe)+' '+getstring(v12_fixed)+' '+getstring(v13_force)+' '+
                                                     getstring(v14_pressure)+' '+getstring(v15_output)+' '+'"'+febio_filename+'"');
               1 : tmacro(macro^).writeredo ('generate.febio2',getstring(v02_solver)+' '+getstring(v03_plot)+' '+getstring(v04_print)+' '+
                                                      getstring(v05_time_steps)+' '+getstring(v06_step_size)+' '+
                                                      getstring(v07_geometry)+' '+getstring(v08_fibre)+' '+getstring(v09_fibre_direction)+' '+getstring(v10_shell_thickness)+' '+
                                                      getstring(v11_prescribe)+' '+getstring(v12_fixed)+' '+getstring(v13_force)+' '+
                                                      getstring(v14_pressure)+' '+getstring(v15_output)+' '+'"'+febio_filename+'"');
               2 : tmacro(macro^).writeredo ('generate.febio25',getstring(v02_solver)+' '+getstring(v03_plot)+' '+getstring(v04_print)+' '+
                                                      getstring(v05_time_steps)+' '+getstring(v06_step_size)+' '+
                                                      getstring(v07_geometry)+' '+getstring(v08_fibre)+' '+getstring(v09_fibre_direction)+' '+getstring(v10_shell_thickness)+' '+
                                                      getstring(v11_prescribe)+' '+getstring(v12_fixed)+' '+getstring(v13_force)+' '+
                                                      getstring(v14_pressure)+' '+getstring(v15_output)+' '+'"'+febio_filename+'"');
          end;
end;
          _cursor_arrow;
     end;
end;

{ ****** }

procedure s_proc_generate_febio (macro : pointer);
begin
     p_proc_generate_febio (_getitem (febio_version),false,macro);
end;
procedure s_proc_generate_febio_sticky (macro : pointer);
begin
     p_proc_generate_febio (_getitem (febio_version),true,macro);
end;

{ ****** }

procedure proc_generate_febio (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := finput^.name;
     _savefile (febio_filename,'new-file','feb',@s_proc_generate_febio,macro);
end;

procedure proc_generate_febio_sticky (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := finput^.name;
     _savefile (febio_filename,'new-file','feb',@s_proc_generate_febio_sticky,macro);
end;

{ ************ }

procedure proc_generate_febio12_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (0,false,macro);
end;

procedure proc_generate_febio12_sticky_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (0,true,macro);
end;

{ ****** }

procedure proc_generate_febio2_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (1,false,macro);
end;

procedure proc_generate_febio2_sticky_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (1,true,macro);
end;

{ ****** }

procedure proc_generate_febio25_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (2,false,macro);
end;

procedure proc_generate_febio25_sticky_help (p1,macro : gtk_pointer); cdecl;
begin
     febio_filename := tmacro(macro^).getparameter(16);
     p_proc_generate_febio (2,true,macro);
end;

