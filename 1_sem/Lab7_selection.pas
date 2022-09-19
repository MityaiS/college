program Lab5;
  var n, i, j, id_max, max: integer;
  A: array[1..10] of integer;
  fin, fout: Text;
begin
  assign(fin, 'in_lab7.txt');
  Reset(fin);
  read(fin, n);
  for i:=1 to n do 
    read(fin, A[i]);
  close(fin);
  assign(fout, 'out_lab7.txt');
  Rewrite(fout);
  j := n;
  while j > 1 do begin
      max := A[1];
      id_max := 1;
      for i := 2 to j do
          if A[i] > max then begin
              max := A[i];
              id_max := i
          end;
      A[id_max] := A[j];
      A[j] := max;
      for i:= 1 to n do
        write(fout, A[i]+' ');
      writeln(fout);
      j := j - 1
  end;
  for i:= 1 to n do
    write(fout, A[i]+' ');
  close(fout);
end.
  